#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// --- PINOS DOS SENSORES LOCAIS ---
#define PIN_BAT_ADC 34       // Divisor de Tensão
#define PIN_COMB_ADC 35      // Sensor Capacitivo
#define PIN_FREIO_CEBOLINHA 4 // Cebolinhas 3-RHO

uint8_t mac_painel[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // MAC do ESP 2

// --- ESTRUTURAS DE DADOS ---

// Essa struct vai no código do ESP 3 e do ESP 1
typedef struct StructCaixaPreta {
  float velocidadeGPS;
  float posicaoLatitude;
  float posicaoLongitude;
  float aceleracaoX;
  float aceleracaoY;
} StructCaixaPreta;

// Essa struct vai no código do ESP 1 e do ESP 2
typedef struct StructPainel {
  float velocidade;          // O ESP 1 escolhe se manda a do GPS ou a da Roda
  float rpmMotor;            // Lido pelo ESP 1
  float tensaoBateria;       // Lido pelo ESP 1
  int nivelCombustivel;      // Lido pelo ESP 1
  float temperaturaCVT;      // Lido pelo ESP 1
} StructPainel;

StructCaixaPreta dadosRecebidosCaixaPreta;
StructPainel pacoteParaPainel;
esp_now_peer_info_t peerInfo;

// Callback: Quando a Caixa Preta manda dados
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&dadosRecebidosCaixaPreta, incomingData, sizeof(dadosRecebidosCaixaPreta));
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_FREIO_CEBOLINHA, INPUT_PULLUP);
  analogReadResolution(12);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv); // Escuta a Caixa Preta
  
  memcpy(peerInfo.peer_addr, mac_painel, 6); // Registra o Painel
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  // 1. Lê a Bateria (Divisor de Tensão com R1=47k, R2=10k)
  int adcBat = analogRead(PIN_BAT_ADC);
  float voltagemNoPino = (adcBat * 3.3) / 4095.0; 
  pacoteParaPainel.tensaoBateria = voltagemNoPino * ((47000.0 + 10000.0) / 10000.0);

  // 2. Lê a Cebolinha de Freio
  pacoteParaPainel.freioAcionado = (digitalRead(PIN_FREIO_CEBOLINHA) == LOW);

  // 3. Pega a velocidade que veio da Caixa Preta
  pacoteParaPainel.velocidade = dadosRecebidosCaixaPreta.velocidadeGPS;

  // 4. Manda o pacote final para o Painel
  esp_now_send(mac_painel, (uint8_t *) &pacoteParaPainel, sizeof(pacoteParaPainel));

  delay(200); // Roda a 5Hz
}