int pinoSinal_1 = 3; //PINO DIGITAL UTILIZADO PELO SENSOR 1
int pinoSinal_2 = 4; //PINO DIGITAL UTILIZADO PELO SENSOR 2
//const int pinoSinal_3 = 11; //PINO DIGITAL UTILIZADO PELO SENSOR 3

int memoria_1 = 0;
int memoria_2 = 0;

//const int pinoLed_AZUL  = 3; //PINO DIGITAL UTILIZADO PELO LED
const int pinoLed_VERDE  = 2; //PINO DIGITAL UTILIZADO PELO LED
const int pinoLed_AMARELO  = 5; //PINO DIGITAL UTILIZADO PELO LED
const int pinoLed_VERMELHO  = 6; //PINO DIGITAL UTILIZADO PELO LED

//AcceleroMMA7361 accelero; //CRIA UMA INSTÂNCIA
int x; //VARIÁVEL QUE ARMAZENA A LEITURA DO EIXO X
int y; //VARIÁVEL QUE ARMAZENA A LEITURA DO EIXO Y
int z; //VARIÁVEL QUE ARMAZENA A LEITURA DO EIXO Z
 
void setup(){
 
   
  //for (int i=12;i<14;i++){
  //  pinMode(i, INPUT); //DEFINE OS PINOS DO SENSOR CAPACITIVO COMO ENTRADA
 // }

  for (int i=0;i<3;i++){
    pinMode(i, OUTPUT); //DEFINE OS PINOS DO LED COMO SAÍDA
  }
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600); //INICIALIZA A SERIAL
 // accelero.begin(10, 9, 8, 7, A0, A1, A2); //INICIALIZA O ACELERÔMETRO E PASSA OS PINOS COMO PARÂMETRO
 // accelero.setARefVoltage(3.3); //DEFINE 3.3V COMO TENSÃO DE REFERÊNCIA
 // accelero.setSensitivity(LOW); //DEFINE A SENSIBILIDADE PARA +/-6G
 // accelero.calibrate(); //INICIALIZA A CALIBRAÇÃO DO SENSOR

  //digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul;
  digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde;
  digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo;
  digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho;
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS 
  
  //digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS 
  digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS 
  digitalWrite(pinoLed_AMARELO, LOW); //ACENDE O LED amarelo
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS 
  digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS 

  digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS  
  digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS 
  //digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS 
  
  
}
 
void loop(){
 
  
  x = analogRead(A5); //VARIÁVEL RECEBE A LEITURA DO EIXO X
  y = analogRead(A4); //VARIÁVEL RECEBE A LEITURA DO EIXO Y
 // z = accelero.getZAccel(); //VARIÁVEL RECEBE A LEITURA DO EIXO Z
 
  Serial.println(""); //QUEBRA DE LINHA
  Serial.print("Eixo X: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(x); //IMPRIME NO MONITOR SERIAL A LEITURA DO EIXO X
  Serial.print(" / Eixo Y: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(y); //IMPRIME NO MONITOR SERIAL A LEITURA DO EIXO Y
  Serial.print(" / Eixo Z: "); //IMPRIME O TEXTO NA SERIAL
  //Serial.print(z); //IMPRIME NO MONITOR SERIAL A LEITURA DO EIXO Z
  Serial.print(" / G*10^-2"); //IMPRIME O TEXTO NA SERIAL*/
 //delay(500); //INTERVALO DE 500 MILISSEGUNDOS 

 if  (((x >= -2) && (x <= 2))  && ((y >= -2) && (y <= 2 ))){
   Serial.print("ENTREI AQUI NO CERTOOOO");
    memoria_1= digitalRead(3);
    memoria_2= digitalRead(4);
    
    digitalWrite(pinoLed_VERDE, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  
   }
 if ( ((x >= -10) && (x <= 10  ))&& ( y >=-10 && y <= -2) ) {
    
     if ((digitalRead(3) == HIGH) && (digitalRead(4) == HIGH))  { //SE A LEITURA DE TODOS OS PINOS FOR IGUAL HIGH, FAZ 
            //digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul
            digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde
            digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
            digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
            Serial.print("ENTROUUUU----11111");
      }
      if((digitalRead(3) == LOW) && (digitalRead(4) == HIGH))  {

           // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
            digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
            digitalWrite(5, HIGH); //ACENDE O LED amarelo
            digitalWrite(0, HIGH); //ACENDE O LED vermelho
            Serial.print("ENTROUUUU --- 222222");
      }

      if ((digitalRead(3) == LOW) && (digitalRead(4)) == LOW)  {

           // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
            digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
            digitalWrite(5, LOW); //ACENDE O LED amarelo
            digitalWrite(0, HIGH); //ACENDE O LED vermelho
            Serial.print("ENTROUUUU----33333");
      }

      else{//SENÃO, FAZ
          digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
          digitalWrite(pinoLed_AMARELO, LOW); //ACENDE O LED amarelo
          digitalWrite(pinoLed_VERMELHO, LOW); //ACENDE O LED vermelho
          Serial.print("ENTROUUUU----44444");
      }
  }
  
   if ((x >= -10) && (x <= 10) && ( y > 2 )) {
     Serial.print("ENTROU ERRADOOOOOOOO 111111");
        
        if (memoria_1 == digitalRead(3) == HIGH && memoria_2 == digitalRead(4)){
                Serial.println("ENTROU ERRADOOOOOOOO 000000");
                Serial.print(memoria_1);
              // digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul
              digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde
              digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
              digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
        }         
         if ((memoria_1 != digitalRead(3)) && (memoria_2 == digitalRead(4))){
           Serial.print("ENTROU ERRADOOOOOOOO 2222222");
         // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
          digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
          digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
          digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
       }
       if ( (memoria_1 == digitalRead(3) == LOW) && (memoria_2 == digitalRead(4) == HIGH)){
           Serial.print("ENTROU ERRADOOOOOOOO 3333333");
 // COM PROBLEMA         // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
          digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
          digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
          digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED 

       }
       if (( memoria_1 == digitalRead(3) == LOW) && (memoria_2 != digitalRead(4))){
             Serial.print("ENTROU ERRADOOOOOOOO 4444444");
         // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
          digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
          digitalWrite(pinoLed_AMARELO, LOW); //ACENDE O LED amarelo
          digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED 

       }
       if (( memoria_1 == digitalRead(3) == LOW) && (memoria_2 == digitalRead(4) == LOW)){
           Serial.print("ENTROU ERRADOOOOOOOO 5555555");
         // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
          digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
          digitalWrite(pinoLed_AMARELO, LOW); //ACENDE O LED amarelo
          digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED 
       }
   }
   if ( (x >= -10 && x <= 10) && (  y > 10  )) { 
        Serial.print("Pega pega ");
      if (digitalRead(3) == HIGH){
          if ( memoria_1 == digitalRead(3) && memoria_2 == digitalRead(4)){
            Serial.print("Pega 11111111");
           //digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
            digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde
            digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
            digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
            Serial.print("Pega 11111111");
          }
      }
      if ( memoria_1 != digitalRead(3) && memoria_2 == digitalRead(4)){
           Serial.print("Pega 222222");
        //  digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
          digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde
          digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
          digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho

      }
      if ( digitalRead(3) == LOW && digitalRead(4) == HIGH){
          if ( memoria_1 == digitalRead(3) && memoria_2 == digitalRead(4)){
            Serial.print("Pega 3333333");
             // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
            digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
            digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
            digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
          }
      }
    
      if ( memoria_1 == (digitalRead(3) == LOW) && memoria_2 != digitalRead(4)){
          Serial.print("Pega 4444444");
          Serial.print(memoria_1);
          Serial.print(memoria_2);
        // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
          digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
          digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
          digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho

      }
      if (digitalRead(4) == LOW){
        if  (memoria_1 == digitalRead(3)  && memoria_2 == digitalRead(4)){
            Serial.print("Pega 555555555");
            Serial.print(memoria_1);
            Serial.print(memoria_2);
          // digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
            digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
            digitalWrite(pinoLed_AMARELO, LOW); //ACENDE O LED amarelo
            digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
        }
    
      }
     
   } 
   if (( y >= -10 && y <= 10  ) && ( x > 10 )) {
           Serial.print("ERRADOOO eeeeeeeee");
         if (digitalRead(3) == HIGH){
           if ( (memoria_1 == digitalRead(3)) && (memoria_2 == digitalRead(4))){
              Serial.print("ERRADOOO 000000000");
              // digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul
              digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde
              digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
              digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
           }
         }
          if (digitalRead(3) == LOW){
              if ( (memoria_1 != digitalRead(3)) && (memoria_2 == digitalRead(4))){
              Serial.print("ERRADOOO 111111");
          //  digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul
               digitalWrite(pinoLed_VERDE, HIGH); //ACENDE O LED verde
               digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
               digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
              }
        
          }
          if (digitalRead(3) == LOW && digitalRead(4) == HIGH){
            if ( (memoria_1 == digitalRead(3)) && (memoria_2 == digitalRead(4))){
        
              Serial.print("ERRADOOO 222222");
          // digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul
              digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
              digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
              digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
            }
         }
         if (memoria_1 == digitalRead(3) && digitalRead(4) == HIGH){
            if ( (digitalRead(3) == LOW) && (memoria_2 != digitalRead(4))){
               Serial.print("ERRADOOO 33333333");
         //     digitalWrite(pinoLed_AZUL, LOW); //ACENDE O LED azul
               digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
               digitalWrite(pinoLed_AMARELO, HIGH); //ACENDE O LED amarelo
               digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
            }
         }
         if (digitalRead(3) == LOW && digitalRead(4) == LOW){
            if ( (memoria_1 == digitalRead(3)) && (memoria_2 == digitalRead(4))){
               Serial.print("ERRADOOO 4444444444");
            // digitalWrite(pinoLed_AZUL, HIGH); //ACENDE O LED azul
               digitalWrite(pinoLed_VERDE, LOW); //ACENDE O LED verde
               digitalWrite(pinoLed_AMARELO, LOW); //ACENDE O LED amarelo
               digitalWrite(pinoLed_VERMELHO, HIGH); //ACENDE O LED vermelho
            }
         }
    
      
   } 
      
                                                                
 }                                                                
     
 

 
