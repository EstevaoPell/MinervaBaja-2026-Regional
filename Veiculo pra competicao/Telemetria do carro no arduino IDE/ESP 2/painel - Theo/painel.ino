// Código para o ESP32 LoRa V2

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();     // Invoke custom library
#define TFT_GREY 0x5AEB

#define BOTAO_L 38
#define BOTAO_R 39


//altura do medidor
float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = 120, osy = 120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update
int old_analog =  -999; // Value last displayed
int old_digital = -999; // Value last displayed
int value[6] = {0, 0, 0, 0, 0, 0};
int old_valueArray[6] = { -1, -1, -1, -1, -1, -1};
int old_value = -200;
int d = 0;
static int lastRPMValue = -1;
int velocidade =80;   //variavel de velocidade
int rotacao = 2000;           // Para o medidor de RPM
int nivelBateria = 60;      // Para o medidor de bateria
int tempOleo = 120;          // Para temperatura do óleo
int tempCVT = 90;
int countFuel = 0;
bool f_high;
bool f_mid;
bool f_low;

//testes
unsigned long ultimoTempoAlternacao = 0;
const unsigned long INTERVALO_ALTERNACAO = 5000; // 3 segundos


enum MedidorEstado {
  RPM,
  BATERIA,
  TEMPERATURA_OLEO,
  TEMPERATURA_CVT,
  COMBUSTIVEL
};

bool debouncing(int botaoPin) 
{
  const int debounceDelay = 50;
  static unsigned long lastPressTime[2] = {0, 0};
  int buttonState = digitalRead(botaoPin);
  
  if (buttonState == LOW && millis() - lastPressTime[botaoPin] > debounceDelay) {
    lastPressTime[botaoPin] = millis();
    return true;
  }
  return false;
}

MedidorEstado estadoEsquerda = RPM;
MedidorEstado estadoDireita = TEMPERATURA_OLEO;


// Declarações das funções
void analogMeter();
void plotLinear(char *label, bool lado, char* texto, uint16_t corInf);
void plotPointer(int i, int value, int valueMin, int valueMax, uint16_t corPonteiro);
void plotNeedle(int value, byte ms_delay);
void drawLeds(int count, bool lado);
void drawRPMMeter(int value, bool lado);
void drawRPMBorder(bool lado);
void RedesenharMedidores();
void atualizarMedidores();
void alternarMedidoresAutomaticamente();


//>>>>>>>>>>>>>>>>>>>>>> RPM para teste<<<<<<<<<<<<<<<<<<<<<<<<<
int generateRPMValue() 
{
  static unsigned long lastTime = 0;
  static float rpm = 0;
  static bool increasing = true;
  
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 50) {  // Atualiza a cada 50ms
    if (increasing) {
      rpm += 2;  // Aumenta 50 RPM
      if (rpm >= 80) {
        increasing = false;
      }
    } else {
      rpm -= 2;  // Diminui 50 RPM
      if (rpm <= 2) {
        increasing = true;
      }
    }
    lastTime = currentTime;
  }
  
  return (int)rpm;
}

void setup(void) {
  //Botões Volante
  pinMode(BOTAO_L, INPUT_PULLUP);
  pinMode(BOTAO_R, INPUT_PULLUP);
  
  //inicializa display
  tft.init();
  tft.setRotation(1);
  Serial.begin(57600); // For debug
  tft.fillScreen(TFT_WHITE);
  tft.invertDisplay(1);
  
  // Desenha o medidor analógico
  analogMeter();
  
  // Desenha os medidores iniciais
  redesenharMedidores();
  
  updateTime = millis(); // Next update time
}

void loop() {
    //alternarMedidoresAutomaticamente();  //comentar para desligar 
    //Variáveis combustível, atualizar para entrada dos capacitores
    bool f_high = 0;
    bool f_mid = 0;
    bool f_low = 0;

  //>>>>>>>>>>  VARIAVEIS DOS SENSORES <<<<<<<<<<<
    //countFuel = f_high + f_low + f_mid;
    countFuel=3;

    //checa rpm
    //rotacao = generateRPMValue();
    //variavel velocidade
    //velocidade = analogRead(A0);
    //nivel bateria

    atualizarMedidores();
  switch(estadoEsquerda) {

    case RPM:
      drawRPMMeter(generateRPMValue()*30, 0);

      break;

    case BATERIA:
      plotPointer(0, generateRPMValue(), 0, 100, TFT_OLIVE); // 
      break;

    case TEMPERATURA_OLEO:

      plotPointer(0, generateRPMValue(), 20, 175, TFT_RED);
      break;

    case TEMPERATURA_CVT:

      plotPointer(0, generateRPMValue(), 20, 100, TFT_RED);
      break;
    
    case COMBUSTIVEL:
      drawLeds(countFuel, 0);
      break;

  }
  
  switch(estadoDireita) {
    
    case RPM:
      drawRPMMeter(generateRPMValue()*30, 1);
      break;

    case BATERIA:
      plotPointer(1, generateRPMValue(), 0, 100, TFT_OLIVE); // 
      break;

    case TEMPERATURA_OLEO:
      plotPointer(1, generateRPMValue(), 20, 175, TFT_RED);
      break;

    case TEMPERATURA_CVT:
      plotPointer(1, generateRPMValue(), 20, 100, TFT_RED);
      break;
    
    case COMBUSTIVEL:
      drawLeds(countFuel, 1);
      break;

  }
        plotNeedle(generateRPMValue(), 0); // It takes between 2 and 12ms to replot the needle with zero delay
}
// Funções de implementação

void alternarMedidoresAutomaticamente() {
  // Verifica se já se passaram 3 segundos desde a última alternância
  if (millis() - ultimoTempoAlternacao >= INTERVALO_ALTERNACAO) {
    // Simula pressionar o botão esquerdo
    estadoEsquerda = (MedidorEstado)((estadoEsquerda + 1) % 5);
    redesenharMedidores();
    
    // Simula pressionar o botão direito
    estadoDireita = (MedidorEstado)((estadoDireita + 1) % 5);
    redesenharMedidores();
    
    // Atualiza o tempo da última alternância
    ultimoTempoAlternacao = millis();
  }
}


void atualizarMedidores() {
  // Verifica botão esquerdo
  if (debouncing(BOTAO_L)) {
    estadoEsquerda = (MedidorEstado)((estadoEsquerda + 1) % 5);
    redesenharMedidores();
  }
  
  // Verifica botão direito
  if (debouncing(BOTAO_R)) {
    estadoDireita = (MedidorEstado)((estadoDireita + 1) % 5);
    redesenharMedidores();
  }
}

void desenharRetanguloInferior() {
  // Define as dimensões do retângulo
  const int alturaRetangulo = 300;  // Altura do retângulo em pixels
  const int yInicial = 128;        // Posição Y inicial (depois do medidor analógico)
  
  // Desenha o retângulo branco
  tft.fillRect(0, yInicial, 480, alturaRetangulo, TFT_WHITE);
}
void redesenharMedidores() {
  desenharRetanguloInferior();
  // Desenha medidores baseados nos estados atuais
  switch(estadoEsquerda) {

    case RPM:
      drawRPMBorder(0);
      break;

    case BATERIA:
      plotLinear("BATERIA", 0, "PORCENTAGEM", TFT_OLIVE);
      break;

    case TEMPERATURA_OLEO:
      plotLinear("TEMPERATURA", 0, "OLEO", TFT_RED);

      break;

    case TEMPERATURA_CVT:
      plotLinear("TEMPERATURA", 0, "CVT", TFT_RED);

      break;
    
    case COMBUSTIVEL:
      drawLeds(countFuel, 0);
      break;

  }
  
  switch(estadoDireita) {
    
    case RPM:
      drawRPMBorder(1);
      break;

    case BATERIA:
      plotLinear("BATERIA", 1, "PORCENTAGEM", TFT_OLIVE);

      break;

    case TEMPERATURA_OLEO:
      plotLinear("TEMPERATURA", 1, "OLEO", TFT_RED);
      break;

    case TEMPERATURA_CVT:
      plotLinear("TEMPERATURA", 1, "CVT", TFT_RED);
      break;
    
    case COMBUSTIVEL:
      drawLeds(countFuel, 1);
      break;

  }
}

void analogMeter() {
  // Calcula a posição centralizada e 75% da largura
  const int centerX = 240;  // Metade de 480px
  const int width = 360;    // 75% de 480px
  const int offsetX = centerX - (width / 2);  // Deslocamento para centralização
  
  // Meter outline
  tft.fillRect(offsetX, 0, width, 126, TFT_GREY);
  tft.fillRect(offsetX + 5, 3, width - 10, 119, TFT_BLACK);
  tft.setTextColor(TFT_BLACK);  // Text colour
  
  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 25;  // Aumentado de 15 para 25
    // Coordinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (100 + tl) + centerX;
    uint16_t y0 = sy * (100 + tl) + 140;
    uint16_t x1 = sx * 100 + centerX;
    uint16_t y1 = sy * 100 + 140;
    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (100 + tl) + centerX;
    int y2 = sy2 * (100 + tl) + 140;
    int x3 = sx2 * 100 + centerX;
    int y3 = sy2 * 100 + 140;
    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    //}
    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_MAGENTA);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_MAGENTA);
    }
    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_BLUE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_BLUE);
    }
    // Short scale tick length
    if (i % 25 != 0) tl = 15;  // Marcadores menores mantidos em 15
    // Recalculate coords incase tick lenght changed
    x0 = sx * (100 + tl) + centerX;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + centerX;
    y1 = sy * 100 + 140;
    // Draw tick
    tft.drawLine(x0, y0, x1, y1, TFT_WHITE);
    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (100 + tl + 10) + centerX;
      y0 = sy * (100 + tl + 10) + 140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("25", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("50", x0, y0 - 6, 2); break;
        case 1: tft.drawCentreString("75", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("100", x0, y0 - 12, 2); break;
      }
    }
    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 100 + centerX;
    y0 = sy * 100 + 140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("BAJA", offsetX +  + (width - 10) - 40, 119 - 20, 2); // Units at bottom right
  //tft.drawCentreString("KM/h", centerX, 70, 4); // Comment out to avoid font 4
  tft.drawRect(offsetX + 5, 3, width - 10, 119, TFT_BLACK); // Draw bezel line
  plotNeedle(0, 0); // Put meter needle at 0
}

//>>>>>>>>>>>>>>>>>>>>>>>>>> NÍVEL DE COMBUSTIVEL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void drawLeds(int count, bool lado) {
    //lado= 0 esquerda, lado= 1 direita
    int x;
    if (lado==0){
       x= 60;
      }
    else if (lado == 1) {
       x= 280;
    }

    int colors[4] = {TFT_RED, TFT_RED, TFT_ORANGE, TFT_GREEN}; // Definição das cores conforme o número de sinais HIGH
    const int circleCenterY = 195;
    tft.drawRect(x - 35 , circleCenterY - 60, 210, 145, TFT_BLACK);
    tft.drawRect(x - 36 , circleCenterY - 61, 212, 149, TFT_BLACK);
    tft.drawRect(x- 37 , circleCenterY - 62, 214, 153, TFT_BLACK);    

    // Exibe o texto "COMBUSTIVEL"
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawCentreString("COMBUSTIVEL", x + 70  ,circleCenterY - 50, 4);
    
    // Exibe a mensagem "NIVEL CRITICO" se necessário
    if (count == 0){
        tft.setTextColor(TFT_RED, TFT_WHITE);
        tft.drawCentreString("!!NIVEL CRITICO!!", x+ 70, circleCenterY + 50, 4);
    }
     // Desenha os LEDs
    for (int i = 0; i < 4; i++) {
        if (i <= count) {
            // Para countFuel = 3, todos ficam verdes
            if (count == 3) {
                tft.fillCircle(x + i * 45, circleCenterY, 20, TFT_GREEN);
            }
            // Para countFuel = 2, 3 ficam laranjas
            else if (count== 2) {
                tft.fillCircle(x + i * 45, circleCenterY, 20, TFT_ORANGE);
            }
            // Para countFuel = 1, 2 ficam vermelhos
            else if (count == 1) {
                tft.fillCircle(x + i * 45, circleCenterY, 20, TFT_RED);
            }
            // Para countFuel = 0, 1 piscante vermelho
            else if (count == 0 && i == 0) {
                static bool blinkState = false;
                static unsigned long lastBlinkTime = 0;
                const unsigned long BLINK_INTERVAL = 200;
                unsigned long currentTime = millis();
                if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
                    lastBlinkTime = currentTime;
                    blinkState = !blinkState;
                    
                    tft.fillCircle(x + i * 45, circleCenterY, 20,
                                 blinkState ? TFT_RED : TFT_WHITE);
                }
            }
        } else {
            // LEDs apagados
            tft.drawCircle(x + i * 45, circleCenterY, 20, TFT_WHITE);
        }
    }
}

void drawRPMBorder(bool lado) {
    // Posição e dimensões da barra
    int x; 
    if (lado==1){
      x=220;
    }
    else if (lado== 0){
       x=30;
    }
    const int y = 190;         // Posição Y
    const int width = 200;     // Largura total
    const int height = 35;     // Altura

    // Desenhar as bordas do medidor
    tft.drawRect(x, y, width, height, TFT_BLACK); // Borda externa
    tft.drawRect(x + 1, y + 1, width - 2, height - 2, TFT_BLACK); // Borda interna
}

//>>>>>>>>>>>>> RPM <<<<<<<<<<<<<<<<<<
void drawRPMMeter(int value, bool lado) {
  int x;
  if (lado==1){
      x=220;
    }
    else if (lado== 0){
       x=30;
    }
  // Verifica se o valor mudou
  if (value == lastRPMValue) {
    return;  // Sai da função sem fazer nada
  }
  
  // Armazena o último valor
  lastRPMValue = value;
  
  // Definir cores
  const uint16_t backgroundColor = TFT_WHITE;
  const uint16_t meterColor = TFT_OLIVE;
  const uint16_t textColorRPM = TFT_OLIVE;
  
  // Posição e dimensões da barra
  const int y = 190;          // Posição Y
  const int width = 200;      // Largura total
  const int height = 35;      // Altura
  
  // Calcular largura atual da barra
  float relativeValue = map(value, 1500, 4000, 0, width);
  int currentWidth = constrain(relativeValue, 0, width);
  
  // Desenha o fundo branco
  tft.fillRect(x + 2, y + 2, width - 4, height - 4, backgroundColor);
  
  // Desenha a barra olive
  tft.fillRect(x + 2, y + 2, currentWidth - 4, height - 4, meterColor);
  
  // Atualiza o texto
  char textBuffer[10];
  sprintf(textBuffer, "%d RPM", value);
  tft.setTextColor(textColorRPM, backgroundColor);
  tft.drawString(textBuffer, x + 40, 160, 4);
}
//--------------------> PONTEIRO VELOCIMETRO <--------------------
void plotNeedle(int value, byte ms_delay) {
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawCentreString(buf, 195, 90 - 20, 4);  // Ajustado para 240px

    int needleMin = 0;
    int needleMax = 120;
  
  if (value < needleMin) value = needleMin; // Limit value to emulate needle end stops
  if (value > needleMax) value = needleMax;
  
  // Move the needle util new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;
    if (ms_delay == 0) old_analog = value; // Update immediately id delay is 0


    
    float sdeg = map(old_analog, needleMin, needleMax, -140, 10); // Map value to angle
    // Calculate tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);
    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);
    
    // Erase old needle image
    tft.drawLine(240 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_BLACK);
    tft.drawLine(240 + 20 * ltx, 140 - 20, osx, osy, TFT_BLACK);
    tft.drawLine(240 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_BLACK);
    
    // Re-plot text under needle
    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString("KM/h", 255, 70, 4); // Ajustado para 240px
    
    // Store new needle end coords for next erase
    ltx = tx;
    osx = sx * 98 + 240;  // Ajustado para 240px
    osy = sy * 98 + 140;
    
    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(240 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_CYAN);
    tft.drawLine(240 + 20 * ltx, 140 - 20, osx, osy, TFT_GREEN);
    tft.drawLine(240 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_CYAN);
    
    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;
    
    // Wait before next update
    delay(ms_delay);
  }
}
void plotLinear(char *label, bool lado, char *texto, uint16_t corInf) {
    int x;
    if(lado== 0){
      x=60;
    } else if (lado ==1){
      x= 300;
    }

    int h = 155;
    int y = 135;
    int w = 110; //largura do medidor linear
    tft.drawRect(x, y, w, h, TFT_GREY);
    tft.fillRect(x+2, y + 19, w-3, h - 38, TFT_BLACK);

    //TEXTO CABEÇALHO
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawCentreString(label, x + w / 2, y + 2, 2);

    for (int i = 0; i < 110; i += 10) {
        tft.drawFastHLine(x + 20, y + 27 + i, 40, TFT_WHITE);
    }
    for (int i = 0; i < 110; i += 50) {
        tft.drawFastHLine(x + 20, y + 27 + i, 60, TFT_WHITE);
    }
    tft.setTextColor (corInf, TFT_WHITE);
    tft.drawCentreString(texto, x + w / 2, y + h - 18, 2); //texto no inferior do medidor
}
//---------------------------------------> PONTEIRO LINEAR <---------------------------------
void plotPointer(int i, int value, int valueMin, int valueMax, uint16_t corPonteiro) {
    // 0 = esquerda 1 = direita
    int dx = 63 + 240 * i;  // Posição horizontal do ponteiro
    byte ph = 28;  // largura do ponteiro
    byte pw = 20;  // altura do ponteiro (base do triângulo)
    int dy = 168;

    // Limita o valor dentro da faixa permitida
    if (value < valueMin) value = valueMin;
    if (value > valueMax) value = valueMax;

    // Mapeia a posição do valor para a altura correta
    dy = map(value, valueMin, valueMax, 264, 168);

    // Apaga o ponteiro anterior desenhando um triângulo da cor do fundo sobre ele
    int old_dy = map(old_valueArray[i], valueMin, valueMax, 264, 168);
    tft.fillTriangle(dx, old_dy, dx, old_dy - ph / 2, dx + pw, old_dy, TFT_BLACK);
    
    // Desenha o novo ponteiro apontando para a direita
    tft.fillTriangle(dx, dy, dx, dy - ph / 2, dx + pw, dy, corPonteiro);

    // Atualiza o valor armazenado
    old_valueArray[i] = value;

    // Desenha o valor numérico
    tft.setTextColor(corPonteiro, TFT_WHITE);
    char buf[8];
    dtostrf(value, 4, 0, buf);
    tft.drawCentreString(buf, i * 240 + 35, 200, 4);
}