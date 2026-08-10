// ==============================================================================
// SISTEMA DE TELEMETRIA BAJA SAE - CENTRAL DAQ (ESP 1)
// Função: Gerenciar leituras locais, agrupar dados do chassi e transmitir ao painel.
// ==============================================================================

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// --- PINOS DE SENSORES ---
#define PIN_BAT_ADC 34
#define PIN_COMB_ADC 35
#define PIN_RPM_RODA 4
#define PIN_RPM_MOTOR 25

// --- DADOS DE RÁDIO (ESP-NOW) ---
uint8_t mac_painel[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Substituir pelo MAC do ESP 2

typedef struct StructCaixaPreta {
  float velocidadeGPS;
  float posicaoLatitude;
  float posicaoLongitude;
  float aceleracaoX;
  float aceleracaoY;
} StructCaixaPreta;

typedef struct StructPainel {
  float velocidade;          
  float rpmMotor;            
  float tensaoBateria;       
  int nivelCombustivel;      
  float temperaturaCVT;      
} StructPainel;

StructCaixaPreta dadosRecebidosCP;
StructPainel pacoteParaPainel;
esp_now_peer_info_t peerInfo;

// --- VARIÁVEIS DE CONTROLE DINÂMICO ---
volatile unsigned long pulsosRoda = 0;
volatile unsigned long pulsosMotor = 0;
unsigned long tempoAnterior = 0;
const unsigned long INTERVALO_LEITURA = 200; 

const int PULSOS_POR_VOLTA_MOTOR = 1; 
const int PULSOS_POR_VOLTA_RODA = 4;
const float PERIMETRO_PNEU_METROS = 1.75; 

// ==============================================================================
// INTERRUPÇÕES E CALLBACKS
// ==============================================================================
void IRAM_ATTR contaPulsoRoda() { pulsosRoda++; }
void IRAM_ATTR contaPulsoMotor() { pulsosMotor++; }

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&dadosRecebidosCP, incomingData, sizeof(dadosRecebidosCP));
}

// ==============================================================================
// SETUP
// ==============================================================================
void setup() {
  Serial.begin(115200);

  // Configuração de Pinos Locais
  pinMode(PIN_RPM_RODA, INPUT_PULLUP);
  pinMode(PIN_RPM_MOTOR, INPUT_PULLUP);
  analogReadResolution(12);

  attachInterrupt(digitalPinToInterrupt(PIN_RPM_RODA), contaPulsoRoda, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_RPM_MOTOR), contaPulsoMotor, RISING);

  // Configuração do Rádio (ESP-NOW)
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ALERTA: Erro ao iniciar ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv); 
  
  memcpy(peerInfo.peer_addr, mac_painel, 6); 
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

// ==============================================================================
// LOOP PRINCIPAL
// ==============================================================================
void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= INTERVALO_LEITURA) {
    
    // 1. Processamento de Rotação (RPM)
    noInterrupts();
    unsigned long pulsosR = pulsosRoda;
    unsigned long pulsosM = pulsosMotor;
    pulsosRoda = 0;
    pulsosMotor = 0;
    interrupts();

    pacoteParaPainel.rpmMotor = (pulsosM * (1000.0 / INTERVALO_LEITURA) * 60.0) / PULSOS_POR_VOLTA_MOTOR;

    // 2. Processamento Analógico (Bateria e Combustível)
    int adcBat = analogRead(PIN_BAT_ADC);
    float voltagemNoPino = (adcBat * 3.3) / 4095.0; 
    pacoteParaPainel.tensaoBateria = voltagemNoPino * ((47000.0 + 10000.0) / 10000.0);

    int adcComb = analogRead(PIN_COMB_ADC);
    pacoteParaPainel.nivelCombustivel = map(adcComb, 500, 3500, 0, 100);
    pacoteParaPainel.nivelCombustivel = constrain(pacoteParaPainel.nivelCombustivel, 0, 100);

    // 3. Processamento Térmico
    pacoteParaPainel.temperaturaCVT = 75.5; // (Placeholder do Sensor SPI/I2C)

    // 4. Agrupamento de Dados Dinâmicos da Caixa Preta
    pacoteParaPainel.velocidade = dadosRecebidosCP.velocidadeGPS; 

    // 5. Transmissão para o Volante (Painel)
    esp_now_send(mac_painel, (uint8_t *) &pacoteParaPainel, sizeof(pacoteParaPainel));

    tempoAnterior = tempoAtual;
  }
}
