#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
// Futuramente, você fará os #includes aqui: <Wire.h>, <SPI.h>, <SD.h>, <TinyGPS++.h>, etc.

// --- MAPEAMENTO DE PINOS ---
#define PIN_BAT_ADC 34
#define PIN_COMB_ADC 35
#define PIN_RPM_RODA 4
#define PIN_RPM_MOTOR 25

// --- MAC DO PAINEL (Preencher depois) ---
uint8_t mac_painel[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// --- ESTRUTURAS DE DADOS ---

// 1. Dados completos para o Cartão SD (Caixa Preta)
typedef struct StructCaixaPreta {
  float rpmMotor;
  float velocidadeKmH;
  float tensaoBateria;
  int nivelCombustivel;
  float tempMotorTermopar;
  float tempCVTInfravermelho;
  float gpsLatitude;
  float gpsLongitude;
  float acelerometroX;
  float acelerometroY;
} StructCaixaPreta;

// 2. Dados filtrados para o Volante (Painel)
typedef struct StructPainel {
  float velocidadeKmH;
  float tensaoBateria;
  int nivelCombustivel;
  bool alertaTempAlta; 
} StructPainel;

StructCaixaPreta dadosCompletos;
StructPainel pacoteEnvio;
esp_now_peer_info_t peerInfo;

// --- VARIÁVEIS DE INTERRUPÇÃO (RPM) ---
volatile unsigned long pulsosRoda = 0;
volatile unsigned long pulsosMotor = 0;
unsigned long tempoAnterior = 0;
const unsigned long INTERVALO_LEITURA = 100; // Lê e envia a cada 100ms (10Hz)

// --- FUNÇÕES DE INTERRUPÇÃO ---
void IRAM_ATTR contaPulsoRoda() { pulsosRoda++; }
void IRAM_ATTR contaPulsoMotor() { pulsosMotor++; }

// --- MÓDULOS DE LEITURA (PREPARE AQUI PARA O FUTURO) ---

void lerRPMeVelocidade() {
  noInterrupts();
  unsigned long pulsosR = pulsosRoda;
  unsigned long pulsosM = pulsosMotor;
  pulsosRoda = 0;
  pulsosMotor = 0;
  interrupts();

  // Quando tiver a geometria do carro, coloque a matemática real aqui
  dadosCompletos.rpmMotor = pulsosM * 10.0; // Falso para teste
  dadosCompletos.velocidadeKmH = pulsosR * 2.5; // Falso para teste
}

void lerBateriaCombustivel() {
  // Bateria
  int adcBat = analogRead(PIN_BAT_ADC);
  dadosCompletos.tensaoBateria = (adcBat * 3.3 / 4095.0) * 5.0; // Multiplicador de teste

  // Combustível
  int adcComb = analogRead(PIN_COMB_ADC);
  dadosCompletos.nivelCombustivel = map(adcComb, 0, 4095, 0, 100);
}

void lerTemperaturas() {
  // No futuro, chamará as bibliotecas do SPI (Termopar) e I2C (Infravermelho)
  dadosCompletos.tempMotorTermopar = 90.0; // Falso
  dadosCompletos.tempCVTInfravermelho = 60.0; // Falso
}

void lerGPSeAcelerometro() {
  // No futuro, fará a leitura da Serial2 e do I2C
  dadosCompletos.gpsLatitude = -22.0; // Falso
  dadosCompletos.acelerometroX = 1.2; // Falso
}

void salvarNoSD() {
  // Futura rotina para pegar tudo que está em 'dadosCompletos' 
  // e gravar em formato CSV no cartão SD.
}

// --- SETUP ---
void setup() {
  Serial.begin(115200);

  // Configuração Pinos Básicos
  pinMode(PIN_RPM_RODA, INPUT_PULLUP);
  pinMode(PIN_RPM_MOTOR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_RPM_RODA), contaPulsoRoda, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_RPM_MOTOR), contaPulsoMotor, RISING);
  analogReadResolution(12);

  // Inicializa Wi-Fi e ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro no ESP-NOW");
    return;
  }
  
  // Registra o Painel
  memcpy(peerInfo.peer_addr, mac_painel, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

// --- LOOP PRINCIPAL ---
void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= INTERVALO_LEITURA) {
    
    // 1. Atualiza todos os dados brutos nos submódulos
    lerRPMeVelocidade();
    lerBateriaCombustivel();
    lerTemperaturas();
    lerGPSeAcelerometro();

    // 2. Salva a "Caixa Preta" no Cartão SD
    salvarNoSD();

    // 3. Prepara o pacote mastigado para o Volante
    pacoteEnvio.velocidadeKmH = dadosCompletos.velocidadeKmH;
    pacoteEnvio.tensaoBateria = dadosCompletos.tensaoBateria;
    pacoteEnvio.nivelCombustivel = dadosCompletos.nivelCombustivel;
    pacoteEnvio.alertaTempAlta = (dadosCompletos.tempMotorTermopar > 110.0);

    // 4. Dispara via Rádio
    esp_now_send(mac_painel, (uint8_t *) &pacoteEnvio, sizeof(pacoteEnvio));

    tempoAnterior = tempoAtual;
  }
}