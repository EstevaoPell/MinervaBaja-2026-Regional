#include <Arduino.h>
#include <Wire.h> // Biblioteca para comunicação I2C (MPU e RM3100)
#include <HardwareSerial.h> // Para ler o GPS no UART

// Pinos I2C padrão do ESP32 para o MPU6050 e RM3100
#define I2C_SDA 21
#define I2C_SCL 22

// Pinos do GPS (Ajuste conforme a solda na PCB de vocês)
#define RX_GPS 16
#define TX_GPS 17
HardwareSerial gpsSerial(2); // Usa a porta Serial 2 do ESP32

void setup() {
  Serial.begin(115200); // Monitor Serial do PC
  
  // 1. Inicializa o barramento I2C para falar com a plaquinha azul (MPU6050) e a preta (RM3100)
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.println("Barramento I2C Iniciado.");
  
  // 2. Inicializa a comunicação com o GPS
  gpsSerial.begin(9600, SERIAL_8N1, RX_GPS, TX_GPS);
  Serial.println("GPS Iniciado.");
  
  // (Aqui no futuro entra a inicialização do MPU6050, RM3100 e LoRa)
}

void loop() {
  // Apenas lê o que o GPS está mandando e joga na tela do PC para testar a solda
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    Serial.print(c);
  }
  
  // O código real dessa caixa vai ler o I2C (Aceleração, Giro, Magnetismo) 
  // e o GPS (Velocidade, Latitude) numa frequência altíssima (ex: 50 vezes por segundo)
  // e então repassar isso via Módulo LoRa para uma antena montada na tenda da Minerva.
}