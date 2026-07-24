//-------------------------------------------------------------------Código que abre a "Purge Valve" por um período de tempo------------------------------------------------------------------ 


//DEFINIÇÃO DE VARIÁVEIS :

//inputs: 
//bool PurgeValve;  //FC Purge Valve - OPENED or CLOSED
//bool FcRelay; //FC Relay - OPENED or CLOSED 
float FcCurrent; //(Amps) Corrente da STACK
unsigned long CurrentTime; //(Sec) System clock time
//------------------------------------------------------------------------------------
//Outputs:
//char OpenPurgeValve; //Open Purge Valve Command
//------------------------------------------------------------------------------------

//Constants:
unsigned long PURGE_INTERVAL = 2300000; //(Amp-miliSec) Intervalo entre as aberturas das válvulas ou (2300 amp-sec)
float PURGE_DURATION = 300.0; //(miliSec) Tempo em que a válvula fica aberta
unsigned long LOOP_TIME; //(Sec) Controller loop period
float RESET_TIME = 3000.0; //(miliSec) Tempo para resetar as variáveis estáticas 
//------------------------------------------------------------------------------------
 
//Local Static Variables:
unsigned long LastCallTime; //(Sec) Horário do sistema em que essa função foi chamada pela última vez 
unsigned long AmpSecSincePurge; //(Amp-Sec) FC ampsec desde a ultima purgada
float PurgeOpenCounter; //(Sec) Controller loop period
//------------------------------------------------------------------------------------

int porta_purga = 4; //Define a porta de comando para a válvula purga
int PurgeValve; //Define a situação atual da válvula purga 
int OpenPurgeValve; //Irá ditar o comando para a abertura ou fechamento da válvula
int pino_FcCurrent = A5; //Define o pino para entrada do sinal de corrente




void setup(){
  
  Serial.begin(38400); //Inicializa a serial
  pinMode(porta_purga,OUTPUT); //Define a porta_purga como porta de saída
  PurgeValve = LOW; //Define o estado da PurgeValve como fechado inicialmente
  LOOP_TIME = 0; //Inicializa o loop time como 0 
  PurgeOpenCounter = 5.94; //Joga um valor inicial para PurgeOpenCounter
   
 
}

void loop(){
  
  unsigned long tempo_inicio_loop_purge = millis(); //Marca o tempo do inicio do loop

  CurrentTime = millis(); //Calculo do tempo atual
  Serial.print("CurrentTime : ");Serial.println(CurrentTime);

  //float valor_teste = CurrentTime - LastCallTime; 
  
  // If function hasn’t been called in RESET_TIME, Reset Local Static Variables
  if(CurrentTime - LastCallTime >= RESET_TIME){ //Se o tempo passado desde a ultima chamada da função for maior/igual que reset time, reseta essas variáveis
    AmpSecSincePurge = 0; //Reseta AmpSecSincePurge
    PurgeOpenCounter = 0.0; //Reseta PurgeOpenCounter
  }

  LastCallTime = millis(); //Atualiza o tempo da última chamada da função para agora
  Serial.print("LastCallTime : ");Serial.println(LastCallTime);
  
  float FcCurrent_1023 = analogRead(pino_FcCurrent); //Leitura do sinal de corrente 
  FcCurrent = map(FcCurrent_1023,0,1023,0,75); //Converte o sinal de corrente (0 - 1023) para amperes (0 - 75)
  
  //Se a válvula purga está fechada, reseta o contador. Mas caso esteja fechada, incrementa o vaor AmpSecSincePurge
  
  if(PurgeValve == HIGH){ //Caso a válvula esteja aberta: 
    Serial.println("A válvula está no segundo if"); 
    AmpSecSincePurge = 0; //Reseta o contador
  }
  
  if(PurgeValve == LOW){ //Caso a válvula esteja fechada
    Serial.println("A válvula está no terceiro if");
    AmpSecSincePurge = AmpSecSincePurge + (FcCurrent * LOOP_TIME); //Incremento do tempo para verificação
    Serial.print("AmpSecSincePurge : ");Serial.println(AmpSecSincePurge);
  }

   //Caso o tempo PURGE_INTERVAL for excedido, abre a válvula e define o contador para manter aberto a válvula
  Serial.print("LOOP_TIME : ");Serial.println(LOOP_TIME);
  
  //PurgeOpenCounter = PURGE_DURATION/LOOP_TIME;
  
  if(AmpSecSincePurge >= PURGE_INTERVAL){ //Verifica se o tempo estipulado foi alcançado
    Serial.println("A válvula está no quarto if");
    OpenPurgeValve = HIGH; //Abre a válvula
    //PurgeValve = HIGH;
    digitalWrite(porta_purga,HIGH); //Envia o sinal de abertura
    PurgeOpenCounter = PURGE_DURATION/LOOP_TIME; //Contador do tempo que a válvula ficará aberta
  }
  
  else{
  

  //Se o contador for maior que 0, mantenha o válvula aberta e decrementa o contador
  //Se o contador for 0 ou menos, fecha a válvula

 
    
    if(PurgeOpenCounter > 0.0){ //Caso o contador for maior que 0
      Serial.println("A válvula está no quinto if");
      OpenPurgeValve = HIGH; //permanece aberto
      //PurgeValve = HIGH;
      //digitalWrite(porta_purga,HIGH);
      Serial.print("PurgeOpenCounter : ");Serial.println(PurgeOpenCounter);
      PurgeOpenCounter = (PurgeOpenCounter - 1.0); //Decremento do contador
      } //decremento no tempo 
      
    
  
    if(PurgeOpenCounter <=0.0){  //Caso o contador for menor que 0
      Serial.println("A válvula está no sexto if");
      OpenPurgeValve = LOW; //A válvula deve fechar
      //PurgeValve = LOW;
      //digitalWrite(porta_purga,LOW);
      //PurgeOpenCounter = PURGE_DURATION/LOOP_TIME;
    }
  }


    delay(100);
    
    digitalWrite(porta_purga,OpenPurgeValve); //Envia o sinal de abertura ou fechamento da válvula
    
    if (OpenPurgeValve == HIGH){ //Se o sinal for de abertura, atualiza a situação da purge valve para aberta
      PurgeValve = HIGH;
      }
    else{ //Se o sinal for de fechamento, atualiza a situação da purge valve para fechada
      PurgeValve = LOW;
      }
    unsigned long tempo_fim_loop_purge = millis(); //Marca o tempo do fim do loop
    
    
    
    LOOP_TIME = (tempo_fim_loop_purge - tempo_inicio_loop_purge); //Duração do loop
  
}
