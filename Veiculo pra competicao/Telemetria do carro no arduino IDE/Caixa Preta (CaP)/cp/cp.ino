// ==============================================================================
// SISTEMA DE TELEMETRIA BAJA SAE - CAIXA PRETA (ESP 3)
// Função: Ler sensores dinâmicos (GPS/IMU) e transmitir para a Central.
// ==============================================================================

#include <TinyGPSPlus.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <esp_now.h>
#include <WiFi.h>

// --- PINOS E MÓDULOS ---
#define RX_GPS 16
#define TX_GPS 17

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;
Adafruit_MPU6050 mpu;

// --- DADOS DE RÁDIO (ESP-NOW) ---
uint8_t mac_esp1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Substituir pelo MAC do ESP 1

typedef struct StructCaixaPreta {
  float velocidadeGPS;
  float posicaoLatitude;
  float posicaoLongitude;
  float aceleracaoX;
  float aceleracaoY;
} StructCaixaPreta;

StructCaixaPreta dadosDinamicos;
esp_now_peer_info_t peerInfo;

// ==============================================================================
// SETUP
// ==============================================================================
void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, RX_GPS, TX_GPS);

  // Inicialização do Barramento I2C
  Wire.begin(21, 22);
  if (!mpu.begin()) {
    Serial.println("ALERTA: Falha ao iniciar MPU6050");
  }

  // Inicialização do Rádio (ESP-NOW)
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ALERTA: Erro no ESP-NOW");
    return;
  }
  
  memcpy(peerInfo.peer_addr, mac_esp1, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

// ==============================================================================
// LOOP PRINCIPAL
// ==============================================================================
void loop() {
  // 1. Processamento do GPS
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
  
  if (gps.speed.isUpdated()) {
    dadosDinamicos.velocidadeGPS = gps.speed.kmph();
  }
  if (gps.location.isUpdated()) {
    dadosDinamicos.posicaoLatitude = gps.location.lat();
    dadosDinamicos.posicaoLongitude = gps.location.lng();
  }

  // 2. Processamento do Acelerômetro (MPU6050)
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  dadosDinamicos.aceleracaoX = a.acceleration.x;
  dadosDinamicos.aceleracaoY = a.acceleration.y;

  // 3. Transmissão para a Central (ESP 1)
  esp_now_send(mac_esp1, (uint8_t *) &dadosDinamicos, sizeof(dadosDinamicos));
  
  delay(100); // Taxa de atualização: 10Hz
}
