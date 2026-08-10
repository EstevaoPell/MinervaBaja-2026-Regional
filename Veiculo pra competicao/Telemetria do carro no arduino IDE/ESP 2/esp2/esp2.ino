// ==============================================================================
// SISTEMA DE TELEMETRIA BAJA SAE - PAINEL (ESP 2)
// Função: Receber telemetria e gerar dashboard avançado no TFT.
// ==============================================================================

#include <SPI.h>
#include <TFT_eSPI.h> 
#include <esp_now.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();     
#define TFT_GREY 0x5AEB

#define BOTAO_L 38
#define BOTAO_R 39

// --- DADOS DE RÁDIO (ESP-NOW) ---
typedef struct StructPainel {
  float velocidade;          
  float rpmMotor;            
  float tensaoBateria;       
  int nivelCombustivel;      
  float temperaturaCVT;      
} StructPainel;

StructPainel dadosRecebidos;
volatile bool novoDadoRecebido = false;

// --- VARIÁVEIS GRÁFICAS ---
float ltx = 0;    
uint16_t osx = 120, osy = 120; 
int old_analog =  -999; 
int old_valueArray[6] = { -1, -1, -1, -1, -1, -1};
static int lastRPMValue = -1;

enum MedidorEstado {
  RPM,
  BATERIA,
  TEMPERATURA_OLEO,
  TEMPERATURA_CVT,
  COMBUSTIVEL
};

MedidorEstado estadoEsquerda = RPM;
MedidorEstado estadoDireita = TEMPERATURA_CVT;

// ==============================================================================
// DECLARAÇÃO DE FUNÇÕES GRÁFICAS
// ==============================================================================
void analogMeter();
void plotLinear(char *label, bool lado, char* texto, uint16_t corInf);
void plotPointer(int i, int value, int valueMin, int valueMax, uint16_t corPonteiro);
void plotNeedle(int value, byte ms_delay);
void drawLeds(int count, bool lado);
void drawRPMMeter(int value, bool lado);
void drawRPMBorder(bool lado);
void redesenharMedidores();
void atualizarBotoes();

// ==============================================================================
// INTERRUPÇÕES E CALLBACKS
// ==============================================================================
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&dadosRecebidos, incomingData, sizeof(dadosRecebidos));
  novoDadoRecebido = true;
}

bool debouncing(int botaoPin) {
  const int debounceDelay = 50;
  static unsigned long lastPressTime[2] = {0, 0};
  int buttonState = digitalRead(botaoPin);
  
  if (buttonState == LOW && millis() - lastPressTime[botaoPin] > debounceDelay) {
    lastPressTime[botaoPin] = millis();
    return true;
  }
  return false;
}

// ==============================================================================
// SETUP
// ==============================================================================
void setup(void) {
  pinMode(BOTAO_L, INPUT_PULLUP);
  pinMode(BOTAO_R, INPUT_PULLUP);
  
  Serial.begin(115200); 

  // Inicialização do TFT
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
  tft.invertDisplay(1);
  
  // Renderização inicial
  analogMeter();
  redesenharMedidores();

  // Inicialização do Rádio (ESP-NOW)
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ALERTA: Erro ao iniciar ESP-NOW no Painel");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

// ==============================================================================
// LOOP PRINCIPAL
// ==============================================================================
void loop() {
  atualizarBotoes();

  if (novoDadoRecebido) {
    
    // 1. Medidor Analógico Central (Velocidade)
    plotNeedle((int)dadosRecebidos.velocidade, 0); 

    // 2. Renderização do Lado Esquerdo
    switch(estadoEsquerda) {
      case RPM: drawRPMMeter((int)dadosRecebidos.rpmMotor, 0); break;
      case BATERIA: plotPointer(0, (int)(dadosRecebidos.tensaoBateria * 10), 90, 145, TFT_OLIVE); break;
      case TEMPERATURA_OLEO: plotPointer(0, 80, 20, 175, TFT_RED); break; 
      case TEMPERATURA_CVT: plotPointer(0, (int)dadosRecebidos.temperaturaCVT, 20, 120, TFT_RED); break;
      case COMBUSTIVEL: drawLeds(map(dadosRecebidos.nivelCombustivel, 0, 100, 0, 3), 0); break;
    }
  
    // 3. Renderização do Lado Direito
    switch(estadoDireita) {
      case RPM: drawRPMMeter((int)dadosRecebidos.rpmMotor, 1); break;
      case BATERIA: plotPointer(1, (int)(dadosRecebidos.tensaoBateria * 10), 90, 145, TFT_OLIVE); break;
      case TEMPERATURA_OLEO: plotPointer(1, 80, 20, 175, TFT_RED); break;
      case TEMPERATURA_CVT: plotPointer(1, (int)dadosRecebidos.temperaturaCVT, 20, 120, TFT_RED); break;
      case COMBUSTIVEL: drawLeds(map(dadosRecebidos.nivelCombustivel, 0, 100, 0, 3), 1); break;
    }

    novoDadoRecebido = false;
  }
}

// ==============================================================================
// FUNÇÕES GRÁFICAS E CONTROLES (IMPLEMENTAÇÕES)
// ==============================================================================
void atualizarBotoes() {
  if (debouncing(BOTAO_L)) {
    estadoEsquerda = (MedidorEstado)((estadoEsquerda + 1) % 5);
    redesenharMedidores();
  }
  if (debouncing(BOTAO_R)) {
    estadoDireita = (MedidorEstado)((estadoDireita + 1) % 5);
    redesenharMedidores();
  }
}

void redesenharMedidores() {
  tft.fillRect(0, 128, 480, 300, TFT_WHITE);
  
  switch(estadoEsquerda) {
    case RPM: drawRPMBorder(0); break;
    case BATERIA: plotLinear("BATERIA", 0, "VOLTS", TFT_OLIVE); break;
    case TEMPERATURA_OLEO: plotLinear("TEMPERATURA", 0, "OLEO", TFT_RED); break;
    case TEMPERATURA_CVT: plotLinear("TEMPERATURA", 0, "CVT", TFT_RED); break;
    case COMBUSTIVEL: drawLeds(3, 0); break; // Apenas desenha interface de fundo
  }
  
  switch(estadoDireita) {
    case RPM: drawRPMBorder(1); break;
    case BATERIA: plotLinear("BATERIA", 1, "VOLTS", TFT_OLIVE); break;
    case TEMPERATURA_OLEO: plotLinear("TEMPERATURA", 1, "OLEO", TFT_RED); break;
    case TEMPERATURA_CVT: plotLinear("TEMPERATURA", 1, "CVT", TFT_RED); break;
    case COMBUSTIVEL: drawLeds(3, 1); break; // Apenas desenha interface de fundo
  }
}

void analogMeter() {
  const int centerX = 240;  
  const int width = 360;    
  const int offsetX = centerX - (width / 2);  
  
  tft.fillRect(offsetX, 0, width, 126, TFT_GREY);
  tft.fillRect(offsetX + 5, 3, width - 10, 119, TFT_BLACK);
  tft.setTextColor(TFT_BLACK);  
  
  for (int i = -50; i < 51; i += 5) {
    int tl = 25;  
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (100 + tl) + centerX;
    uint16_t y0 = sy * (100 + tl) + 140;
    uint16_t x1 = sx * 100 + centerX;
    uint16_t y1 = sy * 100 + 140;
    
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (100 + tl) + centerX;
    int y2 = sy2 * (100 + tl) + 140;
    int x3 = sx2 * 100 + centerX;
    int y3 = sy2 * 100 + 140;

    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_MAGENTA);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_MAGENTA);
    }
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_BLUE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_BLUE);
    }
    if (i % 25 != 0) tl = 15;  
    x0 = sx * (100 + tl) + centerX;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + centerX;
    y1 = sy * 100 + 140;
    tft.drawLine(x0, y0, x1, y1, TFT_WHITE);
    
    if (i % 25 == 0) {
      x0 = sx * (100 + tl + 10) + centerX;
      y0 = sy * (100 + tl + 10) + 140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("30", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("60", x0, y0 - 6, 2); break;
        case 1: tft.drawCentreString("90", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("120", x0, y0 - 12, 2); break;
      }
    }
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 100 + centerX;
    y0 = sy * 100 + 140;
    if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("BAJA", offsetX + (width - 10) - 40, 119 - 20, 2); 
  tft.drawRect(offsetX + 5, 3, width - 10, 119, TFT_BLACK); 
  plotNeedle(0, 0); 
}

void drawLeds(int count, bool lado) {
    int x = (lado == 0) ? 60 : 280;
    const int circleCenterY = 195;
    tft.drawRect(x - 35 , circleCenterY - 60, 210, 145, TFT_BLACK);
    tft.drawRect(x - 36 , circleCenterY - 61, 212, 149, TFT_BLACK);
    tft.drawRect(x- 37 , circleCenterY - 62, 214, 153, TFT_BLACK);    

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawCentreString("COMBUSTIVEL", x + 70, circleCenterY - 50, 4);
    
    if (count == 0){
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.drawCentreString("!!VAZIO!!", x + 70, circleCenterY + 50, 4);
    }
    for (int i = 0; i < 4; i++) {
        if (i <= count) {
            uint16_t cor = (count == 3) ? TFT_GREEN : ((count == 2) ? TFT_ORANGE : TFT_RED);
            tft.fillCircle(x + i * 45, circleCenterY, 20, cor);
        } else {
            tft.drawCircle(x + i * 45, circleCenterY, 20, TFT_WHITE);
        }
    }
}

void drawRPMBorder(bool lado) {
    int x = (lado == 1) ? 220 : 30;
    const int y = 190;         
    const int width = 200;     
    const int height = 35;     
    tft.drawRect(x, y, width, height, TFT_BLACK); 
    tft.drawRect(x + 1, y + 1, width - 2, height - 2, TFT_BLACK); 
}

void drawRPMMeter(int value, bool lado) {
  int x = (lado == 1) ? 220 : 30;
  if (value == lastRPMValue) return;  
  lastRPMValue = value;
  
  const uint16_t backgroundColor = TFT_WHITE;
  const uint16_t meterColor = TFT_OLIVE;
  const uint16_t textColorRPM = TFT_OLIVE;
  
  const int y = 190;          
  const int width = 200;      
  const int height = 35;      
  
  float relativeValue = map(value, 0, 5000, 0, width); 
  int currentWidth = constrain(relativeValue, 0, width);
  
  tft.fillRect(x + 2, y + 2, width - 4, height - 4, backgroundColor);
  tft.fillRect(x + 2, y + 2, currentWidth - 4, height - 4, meterColor);
  
  char textBuffer[10];
  sprintf(textBuffer, "%d RPM", value);
  tft.setTextColor(textColorRPM, backgroundColor);
  tft.drawString(textBuffer, x + 40, 160, 4);
}

void plotNeedle(int value, byte ms_delay) {
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawCentreString(buf, 195, 90 - 20, 4);  

  int needleMin = 0;
  int needleMax = 120;
  
  if (value < needleMin) value = needleMin; 
  if (value > needleMax) value = needleMax;
  
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;
    if (ms_delay == 0) old_analog = value; 

    float sdeg = map(old_analog, needleMin, needleMax, -140, 10); 
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);
    float tx = tan((sdeg + 90) * 0.0174532925);
    
    tft.drawLine(240 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_BLACK);
    tft.drawLine(240 + 20 * ltx, 140 - 20, osx, osy, TFT_BLACK);
    tft.drawLine(240 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_BLACK);
    
    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString("KM/h", 255, 70, 4); 
    
    ltx = tx;
    osx = sx * 98 + 240;  
    osy = sy * 98 + 140;
    
    tft.drawLine(240 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_CYAN);
    tft.drawLine(240 + 20 * ltx, 140 - 20, osx, osy, TFT_GREEN);
    tft.drawLine(240 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_CYAN);
    
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;
    delay(ms_delay);
  }
}

void plotLinear(char *label, bool lado, char *texto, uint16_t corInf) {
    int x = (lado == 0) ? 60 : 300;
    int h = 155;
    int y = 135;
    int w = 110; 
    tft.drawRect(x, y, w, h, TFT_GREY);
    tft.fillRect(x+2, y + 19, w-3, h - 38, TFT_BLACK);

    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawCentreString(label, x + w / 2, y + 2, 2);

    for (int i = 0; i < 110; i += 10) {
        tft.drawFastHLine(x + 20, y + 27 + i, 40, TFT_WHITE);
    }
    for (int i = 0; i < 110; i += 50) {
        tft.drawFastHLine(x + 20, y + 27 + i, 60, TFT_WHITE);
    }
    tft.setTextColor (corInf, TFT_WHITE);
    tft.drawCentreString(texto, x + w / 2, y + h - 18, 2); 
}

void plotPointer(int i, int value, int valueMin, int valueMax, uint16_t corPonteiro) {
    int dx = 63 + 240 * i;  
    byte ph = 28;  
    byte pw = 20;  
    int dy = 168;

    if (value < valueMin) value = valueMin;
    if (value > valueMax) value = valueMax;

    dy = map(value, valueMin, valueMax, 264, 168);

    int old_dy = map(old_valueArray[i], valueMin, valueMax, 264, 168);
    tft.fillTriangle(dx, old_dy, dx, old_dy - ph / 2, dx + pw, old_dy, TFT_BLACK);
    tft.fillTriangle(dx, dy, dx, dy - ph / 2, dx + pw, dy, corPonteiro);

    old_valueArray[i] = value;

    tft.setTextColor(corPonteiro, TFT_WHITE);
    char buf[8];
    dtostrf(value, 4, 0, buf);
    tft.drawCentreString(buf, i * 240 + 35, 200, 4);
}
