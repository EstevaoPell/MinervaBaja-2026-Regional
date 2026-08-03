#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Essa struct vai no código do ESP 1 e do ESP 2
typedef struct StructPainel {
  float velocidade;          // O ESP 1 escolhe se manda a do GPS ou a da Roda
  float rpmMotor;            // Lido pelo ESP 1
  float tensaoBateria;       // Lido pelo ESP 1
  int nivelCombustivel;      // Lido pelo ESP 1
  float temperaturaCVT;      // Lido pelo ESP 1
} StructPainel;

StructPainel dadosRecebidos;
volatile bool telaPrecisaAtualizar = false; 

// Callback: Quando a Central (ESP 1) manda dados
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&dadosRecebidos, incomingData, sizeof(dadosRecebidos));
  telaPrecisaAtualizar = true; 
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Falha OLED"));
    for(;;); 
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(10, 25);
  display.print("MINERVA BAJA SAE");
  display.display();
  delay(2000);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  if (telaPrecisaAtualizar) {
    display.clearDisplay(); 

    // Desenha a Bateria
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("BAT: "); display.print(dadosRecebidos.tensaoBateria, 1); display.print("V");

    // Indicador de Freio
    if (dadosRecebidos.freioAcionado) {
      display.setCursor(90, 0);
      display.print("[FREIO]");
    }

    display.drawLine(0, 10, 128, 10, WHITE);

    // Desenha Velocidade (Agora vindo do GPS da Caixa Preta!)
    display.setTextSize(3);
    display.setCursor(25, 20); 
    display.print((int)dadosRecebidos.velocidade); 
    
    display.setTextSize(1);
    display.setCursor(85, 35);
    display.print("km/h");

    display.display();
    telaPrecisaAtualizar = false;
  }
}