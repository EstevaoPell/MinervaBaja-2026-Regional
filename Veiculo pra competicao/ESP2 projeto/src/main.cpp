#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- CONFIGURAÇÕES DO DISPLAY OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
// Inicializa o display nos pinos I2C padrão do ESP32 (SDA = 21, SCL = 22)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- ESTRUTURA DE DADOS (Deve ser IDÊNTICA ao ESP 1) ---
typedef struct StructPainel {
  float velocidadeKmH;
  float tensaoBateria;
  int nivelCombustivel;
  bool alertaTempAlta; 
} StructPainel;

StructPainel dadosRecebidos;

// Flag de controle: avisa o loop() que chegou um pacote novo
volatile bool telaPrecisaAtualizar = false; 

// --- FUNÇÃO DE RECEBIMENTO (CALLBACK) ---
// Executada automaticamente em background pelo rádio quando chega mensagem
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  // Copia os bytes recebidos para a nossa estrutura
  memcpy(&dadosRecebidos, incomingData, sizeof(dadosRecebidos));
  
  // Levanta a bandeira para o loop principal desenhar na tela
  telaPrecisaAtualizar = true; 
}

// --- SETUP ---
void setup() {
  Serial.begin(115200);

  // 1. Inicializa o Display OLED (Endereço I2C 0x3C é o padrão da maioria)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Falha ao iniciar o display OLED"));
    for(;;); // Trava o ESP aqui se a tela não ligar
  }
  
  // Tela de Boot da Equipe
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(15, 25);
  display.print("MINERVA BAJA SAE");
  display.setCursor(20, 40);
  display.print("Iniciando radio...");
  display.display();
  delay(2000); // Aguarda 2 segundos para o piloto ler

  // 2. Inicializa o Wi-Fi e ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }
  
  // Diz ao ESP-NOW qual função chamar quando chegar dado
  esp_now_register_recv_cb(OnDataRecv);
}

// --- LOOP PRINCIPAL ---
void loop() {
  // O processador fica ocioso a maior parte do tempo. 
  // Só desenha quando o rádio avisa que tem novidade.
  if (telaPrecisaAtualizar) {
    
    display.clearDisplay(); 

    // --- LÓGICA DE ALERTA DE TEMPERATURA ---
    // Se a temperatura do motor passar do limite, pisca um aviso gigante 
    // e esconde o resto das informações para forçar a atenção do piloto.
    if (dadosRecebidos.alertaTempAlta) {
      display.setTextSize(2);
      display.setCursor(10, 20);
      display.print("TEMP ALTA!");
      display.setTextSize(1);
      display.setCursor(10, 45);
      display.print("Tire o pe do acelerador!");
    } 
    // Se a temperatura estiver OK, desenha o painel normal
    else {
      // Bateria (Topo Esquerdo)
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("BAT: "); 
      display.print(dadosRecebidos.tensaoBateria, 1); 
      display.print("V");

      // Combustível (Topo Direito)
      display.setCursor(75, 0);
      display.print("COMB: "); 
      display.print(dadosRecebidos.nivelCombustivel); 
      display.print("%");

      // Linha separadora
      display.drawLine(0, 10, 128, 10, WHITE);

      // Velocidade (Centro, Gigante)
      display.setTextSize(3);
      display.setCursor(25, 20); // Centralizado no olhômetro
      // Mostra sem casas decimais para não confundir o piloto
      display.print((int)dadosRecebidos.velocidadeKmH); 
      
      display.setTextSize(1);
      display.setCursor(85, 35);
      display.print("km/h");
    }

    // Manda os dados do buffer interno para os LEDs da tela
    display.display();
    
    // Abaixa a bandeira e espera o próximo pacote
    telaPrecisaAtualizar = false;
  }
}