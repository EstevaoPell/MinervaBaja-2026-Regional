#include <Arduino.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <esp_now.h>
#include <WiFi.h>

// --- PINOS ---
#define RX_GPS 16
#define TX_GPS 17

// --- MÓDULOS ---
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;
Adafruit_MPU6050 mpu;

// --- DADOS PARA O ESP 1 (Central) ---
uint8_t mac_esp1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Colocar o MAC do ESP 1 aqui

typedef struct StructCaixaPreta {
  float velocidadeGPS;
  float aceleracaoX;
  float aceleracaoY;
} StructCaixaPreta;

StructCaixaPreta dadosDinâmicos;
esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, RX_GPS, TX_GPS);

  // Inicializa I2C (MPU6050 e RM3100)
  Wire.begin(21, 22);
  if (!mpu.begin()) {
    Serial.println("Falha ao iniciar MPU6050");
  }

  // Inicializa ESP-NOW para mandar pro ESP 1
  WiFi.mode(WIFI_STA);
  esp_now_init();
  memcpy(peerInfo.peer_addr, mac_esp1, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  // 1. Lê o GPS
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
  if (gps.speed.isUpdated()) {
    dadosDinâmicos.velocidadeGPS = gps.speed.kmph();
  }

  // 2. Lê o MPU6050 (Acelerômetro)
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  dadosDinâmicos.aceleracaoX = a.acceleration.x;
  dadosDinâmicos.aceleracaoY = a.acceleration.y;

  // 3. Envia para o ESP 1 (Central)
  esp_now_send(mac_esp1, (uint8_t *) &dadosDinâmicos, sizeof(dadosDinâmicos));
  
  delay(100); // Roda a 10Hz
}