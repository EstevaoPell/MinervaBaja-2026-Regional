

#include <Thermistor.h> //Inclui a biblioteca para a leitura do termistor

//////////////////////////////////////////////////
//////////Código da Purge no Run//////////////////
//////////////////////////////////////////////////

//DEFINIÇÃO DE VARIÁVEIS :

//inputs: 
//bool PurgeValve;  //FC Purge Valve - OPENED or CLOSED
//bool FcRelay; //FC Relay - OPENED or CLOSED 
float FcCurrent; //(Amps) Stack Current
unsigned long CurrentTime; //(Sec) System clock time
//------------------------------------------------------------------------------------
//Outputs:
//char OpenPurgeValve; //Open Purge Valve Command
//------------------------------------------------------------------------------------

//Constants:
unsigned long PURGE_INTERVAL = 2300000; //(Amp-miliSec) Interval between purges ou (2300 amp-sec)
float PURGE_DURATION = 300.0; //(miliSec) How long the purge valve opens for
unsigned long LOOP_TIME; //(Sec) Controller loop period
float RESET_TIME = 3000.0; //(miliSec) Rest Static Variables delay timer 
//------------------------------------------------------------------------------------
 
//Local Static Variables:
unsigned long LastCallTime; //(Sec) System time of last call of this function 
unsigned long AmpSecSincePurge; //(Amp-Sec) FC ampsec since previous purge
unsigned long PurgeOpenCounter; //(Sec) Controller loop period
//------------------------------------------------------------------------------------

int porta_purga = 4; //Define a porta de comando para a válvula purga
int PurgeValve; //Define a situação atual da válvula purga 
int OpenPurgeValve; //Irá ditar o comando para a abertura ou fechamento da válvula

/////////////////////////////////////////////////////////////
/////////////////Código da corrente do Run///////////////////
////////////////////////////////////////////////////////////

//Definição de veriáveis:

//Inputs:
float CurrentRequest; //Corrente solicitada
//unsigned long CurrentTime; //Horário do sistema atual 
//-----------------------------------------------------------------------------------

//Outputs:
float CurrentCmd; //Comando para a alimentação de corrente
//-----------------------------------------------------------------------------------

//Constants:
float FC_MAX_CURRENT = 65.3; //Corrente máxima da stack
float FC_MIN_CURRENT = 7.3; //Corrente minima da Stack
float CURRENT_UP_RATE = 0.002; //taxa máxima de aumento da corrente com relação ao tempo
float CURRENT_DN_RATE = 0.001; //taxa mínima de aumento da corrente com relação ao tempo
//-----------------------------------------------------------------------------------

//Local Static Variables:
//unsigned long LastCallTime; //Horário da última vez que esse função foi chamada
float LastCurrentCmd; //O comando de corrente do último loop
//-----------------------------------------------------------------------------------

int pino_corrente = A5;
int pino_supply = 7;



///////////////////////////////////////////////////////////////
////////////////////Código do Fan no Run///////////////////////
//////////////////////////////////////////////////////////////

float FcTemp;           //(°C) Stack temperature 
//float FcCurrent;        //(Amps) Stack current
float PreviousFanCmd;   //(%) Fan command from the last iteration
//int potpincorrente = A5;  //Definição do pino que entra a informação de corrente
int pino_temp = A4; //Definição do pino que entra a informação de temperatura
int pinoPWM = 6 ; //Definição do pino que sai a o sinal para o PWM.

float OptTemp;         //(°C) Temperatura ótima da stack - é função da corrente (fcn(current))
float UpdatedFanCmd;   //(%) Comando para o fan

float MAX_FAN_CMD = 100.0;  //(%) Máximo cmd permitioo para o FAN
float MIN_FAN_CMD = 15.0;   //(%) Mínimo cmd permitido para o FAN
float P_CONST = 0.7;        // Proportion Term Constant
float I_CONST = 0.6;        // Integral Term Constant
float D_CONST = 0.05;       // Derivative Term Constant
//double LOOP_TIME = 0.0;     //(Sec) Controller Loop Period
//float LastCallTime = 0.0;  //(Sec) tempo do sistema em que essa funçõ foi chamada pela última vez.
float LastITerm = 0.0;     //I‐Term do loop anterior.
float LastTempDiff = 0.0;  //(°C) TempDiff do loop anterior.
float PTerm; float ITerm; float DTerm;
float TempDiff; //(°C) FcTemp – OptTemp - Erro de temperatura - diferença de quanto está e quanto deveria estar.


/////////////////////////////////////////////
////////////Temporizadores///////////////////
/////////////////////////////////////////////
long intervalo_StartUp = 300.0;
long intervalo_Startfan = 3000.0;
long standby_dalay_time = 10000.0;
float incrementa_tempo;
float timer_start_time;


Thermistor temp(pino_temp);


enum states{ //Definição de todos os estados possíveis
  Check_alarms,
  System,
  FC,
  FC_Standby,
  FC_StartUp,
  FC_Run,
  FC_Alarm,
  FC_Shutdown,
  StartUp_fan_spoolup,
  StartUp_Purge,
  StartUp_End};   

  uint8_t top_state = Check_alarms;
  uint8_t state = FC_Standby;
  uint8_t substate = StartUp_fan_spoolup;
  
void setup() {

  Serial.begin(9600);
  pinMode (pino_supply,OUTPUT);  
  digitalWrite (pino_supply,LOW);
  pinMode(porta_purga,OUTPUT);
  digitalWrite(porta_purga,LOW);
  PurgeValve = LOW;
  LOOP_TIME = 0.0;
  PurgeOpenCounter = 5.94;
  pinMode (pino_corrente,INPUT);
  float incrementa_tempo = 0;
  pinMode(pinoPWM,OUTPUT); //Define o pino PWM como pino de saída
  //pinMode(potpincorrente,INPUT); //Define o potpincorrente como pino de entrada
  pinMode(pino_temp,INPUT); //Defino o potpintempo como pino de entrada
  
  

}

void loop() {
  maquina_estados_finitos();
}

void maquina_estados_finitos(){
  
    
  switch (top_state){
    
    case  Check_alarms :{
      
     
      top_state =  System ;
      Serial.println("O top_state é Check_alarms");
      }
      break;
      
      
    case  System:
      top_state =  FC ;
      Serial.println("O top_state é System");
      
      break;

    case  FC :
      Serial.println("O top_state é FC/ ");
      top_state = Check_alarms;

      switch(state){

        case  FC_Standby :{
          
         
          timer_start_time = millis();
          Serial.println("O state é FC_Standby --> ");
          //Serial.println("A válvula está fechada ");
          digitalWrite(pino_supply,LOW);
          digitalWrite(porta_purga,LOW); 
          //float current_time_standby = millis();
          float delta_tempo_standby = millis(); - timer_start_time;
          incrementa_tempo = incrementa_tempo + delta_tempo_standby;
          analogWrite(pinoPWM,0);
          
          Serial.println(incrementa_tempo);
          if (incrementa_tempo >= standby_dalay_time){
            state = FC_StartUp;
            Serial.println("primeiro if");
            }
          else{
            state = FC_Standby;
            Serial.println("segundo if");
            }
        
          }
        
          break;
          
        case  FC_StartUp :{

          Serial.println("O state é FC_StartUp/ ");
          
          switch(substate){
            
            case  StartUp_fan_spoolup:{
              //state = FC_StartUp;
              
              Serial.print("O substate é StartUp_fan_spoolup --> ");
              //Serial.println("A válvula está fechada ");
              digitalWrite(pino_supply,LOW);
              digitalWrite(porta_purga,LOW);
              
              //FAN NO MÁXIMO
              Fan_StartUp();
              //FAN NO MÍNIMO }
              state = FC_StartUp;
              
              }
              break;
              
            case StartUp_Purge :{

              
              //state = FC_StartUp;  
              //Serial.print("O substate é StartUp_Purge -->");
              //Serial.println("A válvula está aberta ");  
              digitalWrite(pino_supply,HIGH);
              
              Purge_StartUp();
              
              }
              
       
              break;
              
            case  StartUp_End :{
            
                           
               
              Serial.print("O substate é StartUp_End -->");
              //Serial.println("A válvula está aberta ");
              
              digitalWrite(pino_supply,HIGH);
              digitalWrite(porta_purga,LOW);
              analogWrite(pinoPWM,40.0);
              state = FC_Run ;
              }
              break;
              }
        } 
        break;
            
            
        case FC_Run :{
          
          unsigned long comeca_loop = millis();
          //state = FC_Run ;
          //Serial.print("O state é Run -->");
          //Serial.println("A válvula supply está aberta ");
          
          digitalWrite(pino_supply,LOW);
          Purge_Run();
          Fan_Run();
          Current_Run();
          unsigned long fim_loop = millis();
          LOOP_TIME = fim_loop - comeca_loop;
          }
          
          break;
      
        case  FC_Shutdown :{
          delay(100);
        
          //state =  FC_Alarm ;
          //Serial.print("O state é FC_Shutdown -->");
          //Serial.println("A válvula supply está fechada ");
          //Serial.println("A válvula Purge está fechada ");
          
          digitalWrite(pino_supply,LOW);
          digitalWrite(porta_purga,LOW);
          PurgeValve = LOW;
          analogWrite(pinoPWM,0.0);
          }
          break;

        case  FC_Alarm :{
          delay(2000);
          state = FC_Alarm ;
          Serial.print("O state é FC_Alarm -->");
          Serial.println("A válvula supply está fechada ");
          Serial.println("A válvula Purge está fechada ");
          digitalWrite(pino_supply,LOW);
          digitalWrite(porta_purga,LOW);
          analogWrite(pinoPWM,0.0);
          }
          break;
    
      }
    break;
  }
  
}

//Definição de funções do RUN: 
void Purge_Run(){
  
  //unsigned long tempo_inicio_loop_purge = millis(); //Marca o tempo do inicio do loop

  CurrentTime = millis(); //Calculo do tempo atual
  //Serial.print("CurrentTime : ");Serial.println(CurrentTime);

  float valor_teste = CurrentTime - LastCallTime;
  
  // If function hasn’t been called in RESET_TIME, Reset Local Static Variables
  if(CurrentTime - LastCallTime >= RESET_TIME){ //Se o tempo passado desde a ultima chamada da função for maior/igual que reset time, reseta essas variáveis
    AmpSecSincePurge = 0;
    PurgeOpenCounter = 0.0;
  }

  LastCallTime = millis(); //Atualiza o tempo da última chamada da função para agora
  //Serial.print("LastCallTime : ");Serial.println(LastCallTime);
  
  float FcCurrent_1023 = analogRead(pino_corrente);
  FcCurrent = map(FcCurrent_1023,0,1023,0,100) - 13.0;
  Serial.print("FC CURRENT : ");Serial.println(FcCurrent);
  
  // If the Purge Valve is open, Reset the counter. If the purge valve is closed, add AmpSec
  if(PurgeValve == LOW){
    //Serial.println("A válvula está no segundo if");
    AmpSecSincePurge = 0;
  }
  
  if(PurgeValve == HIGH){
    Serial.println("A válvula está no terceiro if");
    AmpSecSincePurge = AmpSecSincePurge + (FcCurrent * LOOP_TIME); //Incremento do tempo para verificação
    Serial.println(" ");
    Serial.print("AmpSecSincePurge : ");Serial.println(AmpSecSincePurge);
    Serial.println(" ");
  }

// If PURGE_INTERVAL is exceed, open the Purge Valve and set the counter for the number of loops
// to keep it open for.
  //Serial.print("LOOP_TIME : ");Serial.println(LOOP_TIME);
  //PurgeOpenCounter = PURGE_DURATION/LOOP_TIME;
  
  if(AmpSecSincePurge >= PURGE_INTERVAL){ //Verifica se o tempo estipulado foi alcançado
    //Serial.println("A válvula está no quarto if");
    OpenPurgeValve = LOW; //Abre a válvula
    //PurgeValve = HIGH;
    digitalWrite(porta_purga,LOW);
    PurgeOpenCounter = PURGE_DURATION/LOOP_TIME; //Contador do tempo que a válvula ficará aberta
    //Serial.print("PURGE OPEN COUNTER :");Serial.println(PurgeOpenCounter);
  }
  
  
  
  else{
  
// If the counter is greater than 0, keep the Purge Valve open and decrement the counter.
// If the counter is 0, close the purge valve

    
    if(PurgeOpenCounter > 0.0){
      //Serial.println("A válvula está no quinto if");
      OpenPurgeValve = LOW; //permanece aberto
      //PurgeValve = HIGH;
      //digitalWrite(porta_purga,HIGH);
      //Serial.print("PurgeOpenCounter 1: ");Serial.println(PurgeOpenCounter);
      PurgeOpenCounter = (PurgeOpenCounter - 1.0);
      //Serial.print("PurgeOpenCounter 2: ");Serial.println(PurgeOpenCounter);
      } //decremento no tempo 
     
    
  
    if(PurgeOpenCounter <=0.0){ 
      //Serial.println("A válvula está no sexto if");
      OpenPurgeValve = HIGH; //A válvula deve fechar
      //PurgeValve = LOW;
      digitalWrite(porta_purga,HIGH);
      PurgeOpenCounter = PURGE_DURATION/LOOP_TIME;
    }
  }


    //delay(1000);
    //Serial.print("OPENPURGEVALVE : ");Serial.println(OpenPurgeValve);
    digitalWrite(porta_purga,OpenPurgeValve);
    
    if (OpenPurgeValve == LOW){
      PurgeValve = LOW;
      }
    else{
      PurgeValve = HIGH;
      }
    unsigned long tempo_fim_loop_purge = millis(); //Marca o tempo do fim do loop
    
    
    //LOOP_TIME = (tempo_fim_loop_purge - tempo_inicio_loop_purge); //Duração do loop  
  }

void Current_Run(){
  
  //float tempo_1_current_ramp = millis();

  float valor_potenciometro = analogRead(pino_corrente);
  CurrentRequest = map(valor_potenciometro,0,1023,0,100) - 13.0;
  CurrentTime = millis();
  //Serial.println(" ");
  //Serial.print("CurrentRequest : ");Serial.println(CurrentRequest);
  //Serial.print("CURRENT TIME");Serial.println(CurrentTime);
  //Serial.print("LAST CALL TIME");Serial.println(LastCallTime);
  if(CurrentTime - LastCallTime >= RESET_TIME){ //Verifica se o tempo decorrido entre duas chamadas de função é maior ou igual que RESET_TIME
    LastCurrentCmd = FC_MIN_CURRENT; //Se a condição for verdadeira, o valor da corrente retornado pela função da última vez que foi chamada assume o valor mínimo
    //Serial.println("-----------------------------------");
    } 

  //CurrentTime = millis();
  LastCallTime = millis();; //Atualiza o horário em que a função foi chamada pela última vez para o tempo atual
  
  //Serial.print("LastCurrentCmd : ");Serial.println(LastCurrentCmd);
  if(CurrentRequest >= LastCurrentCmd){ //Verifica se a corrente requisitada é maior que o valor da corrente retornado pela função na última fez em que foi chamada

    CurrentCmd = LastCurrentCmd + (CURRENT_UP_RATE*LOOP_TIME); //A corrente que irá ser retornada será igual o valor da corrente retornado pela função na última fez em que foi chamada acrescido de um valor de corrente
  
    if(CurrentCmd >= CurrentRequest){ //Verifica se a corrente que irá ser retornada já é maior ou igual a corrente requisitada
      CurrentCmd = CurrentRequest; //A corrente que irá ser retornada assume o valor da corrente requisitada
      }

    else if(CurrentCmd >= FC_MAX_CURRENT){  //Verifica se a corrente que irá ser retornada não ultrapassou o valor máximo
      CurrentCmd = FC_MAX_CURRENT; //Atualiza o valor da corrente que irá ser retornada como o valor máximo possível
      }

    else if(CurrentCmd <= FC_MIN_CURRENT){ //Verifica se a corrente que irá ser retornada não ultrapassou o valor mínimo
      CurrentCmd = FC_MIN_CURRENT; //Atualiza o valor da corrente que irá ser retornada como o valor mínimo possível
      }

  }

  else{ //Se a corrente requisitada é menor que o valor da corrente retornado pela função na última fez em que foi chamada


    CurrentCmd = LastCurrentCmd - (CURRENT_DN_RATE*LOOP_TIME); //A corrente que irá ser retornada será igual o valor da corrente retornado pela função na última fez em que foi chamada decrescido de um valor de corrente

    if(CurrentCmd <= CurrentRequest){ //Verifica se a corrente que irá ser retornada já é menor ou igual a corrente requisitada
      CurrentCmd = CurrentRequest; //A corrente que irá ser retornada assume o valor da corrente requisitada
    }

    else if (CurrentCmd <= FC_MIN_CURRENT){ //Verifica se a corrente que irá ser retornada não ultrapassou o valor mínimo
      CurrentCmd = FC_MIN_CURRENT; //Atualiza o valor da corrente que irá ser retornada como o valor mínimo possível
    }

  }
  //Serial.print("Current_uo_rate * looptime");Serial.println(CURRENT_UP_RATE*LOOP_TIME);
  //Serial.println("Corrente enviada: ");Serial.println(CurrentCmd);
  LastCurrentCmd = CurrentCmd;
  //delay(200);
  //float tempo_2_current_ramp = millis();
  //LOOP_TIME = (tempo_2_current_ramp - tempo_1_current_ramp);
  
  //Serial.println("CURRENT_UP_RATE : ");Serial.println(CURRENT_UP_RATE);
  //Serial.print("LOOP TIME TOTAL : ");Serial.println(LOOP_TIME);
  Serial.println(" ");
  
  
  
}
  

//Definição das funções do StartUp
  
void Fan_StartUp(){
  
  unsigned long currentMillis_StartUpFan = 0;
  //Serial.println(currentMillis_StartUpFan);
  float tempo_inicial_startup_fan = millis();
  
  while((currentMillis_StartUpFan) <= intervalo_Startfan){
  digitalWrite(porta_purga,HIGH);
  analogWrite(pinoPWM,204.0);
  //Serial.println(currentMillis_StartUpFan);
  currentMillis_StartUpFan = millis() - tempo_inicial_startup_fan;
  Serial.println("dentro do while do Fan_StartUp");
  }
  substate = StartUp_Purge;
}

void Purge_StartUp(){
  unsigned long currentMillis_StartUpPurge = 0;
  Serial.println(currentMillis_StartUpPurge);
  float tempo_inicial_startup_purge = millis();
  while((currentMillis_StartUpPurge) <= intervalo_StartUp){
  digitalWrite(porta_purga,HIGH);
  analogWrite(pinoPWM,204);  
  Serial.println(currentMillis_StartUpPurge);
  currentMillis_StartUpPurge = millis() - tempo_inicial_startup_purge;
   Serial.println("dentro do while da Purge_StartUp");
    }
    digitalWrite(porta_purga,LOW); 
    substate = StartUp_End;
}

/*void verifica_standby(){
  
  timer_start_time = millis();
  if (fc_on == HIGH){
    float tempo_decorrido = millis() - timer_start_time;
    
  }
}*/


void Fan_Run(){
  
//float tempo_1_fan = millis(); //Cálculo do tempo que a função começa 

  
  float FcCurrent_pot = analogRead(pino_corrente); //Leitura dos valores de corrente (0-1023)
  float FcCurrent = map(FcCurrent_pot,0,1023,0,100) - 13.0; //Faz a conversão entre os valores lidos de corrente para graus celsius (0 - 75)

  FcCurrent = temp.getTemp(); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(FcCurrent); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  Serial.println("ºC"); //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(1); //INTERVALO DE 1 SEGUNDO
  
  //float FcTemp_pot = analogRead(potpintemp); //Leitura dos valores de temperatura da stack (0-1023)
  //float FcTemp = map(FcTemp_pot,0,1023,0,100); //Faz a conversão entre os valores lidos de temperatura para graus celsius (0 - 75)
  
// calculo de OptTemp baseado no FcCurrent:
   //OptTemp = ((7.64)*FcCurrent) + 354.64;
  OptTemp = (0.53)*FcCurrent + (26.01);  // FcCurrent = stack current
  Serial.println(" ");
  Serial.print("OPT TEMP ");Serial.println(OptTemp);
  Serial.println(" ");

  

// Calcula o erro de temperatura
  TempDiff = FcTemp - OptTemp;
  Serial.println("TempDiff : ");Serial.println(TempDiff);

//Se a função não foi chamada dentro do tempo (RESET_TIME), resenta as variáveis locais estáticas
  float CurrentTime = millis(); //Faz o cálculo do horário atual do sistema 
  
  if(CurrentTime - LastCallTime >=  RESET_TIME){ //CurrentTime - LastCallTime = diferenção de tempo entre o tempo atual e o tempo em que a função foi chamada pela última vez
    LastITerm = PreviousFanCmd; //Define o ultimo ITerm como o último cmd 
    LastTempDiff = TempDiff; //Define o último erro de temperatura como o erro atual
    Serial.println("Primeiro IF");
   }
  
  //LastCallTime = CurrentTime;
  LastCallTime = millis();  //Define o horário dessa função, que será usuada no próximo loop

// Calcula o Proportional Term (PTerm)
  PTerm = (P_CONST * TempDiff); //Definido como a constante P multiplicado pelo erro.
  Serial.println("P term : ");Serial.println(PTerm);

// Calcula o Integral Term (ITerm), e limita o máximo e o mínimo para o FAN cmd

  ITerm = (I_CONST * TempDiff * (LOOP_TIME) + LastITerm) ; //Definido como a constante I multiplicado pelo erro e pelo LOOP_TIME e incrementado do ultimo ITerm
  LastITerm = ITerm; //Atualiza o LastIterm, que será usado no próximo loop
  Serial.println("I term 1: ");Serial.println(ITerm);
  
  if (ITerm > MAX_FAN_CMD){ //Caso o Iterm passe o limite máximo de cmd:
    //Serial.println("Segundo IF");
    ITerm = MAX_FAN_CMD; //Define como o valor máximo (100%)
    float LastIterm = MAX_FAN_CMD; //Atualiza o valor de LastIterm
    Serial.println("I term 2: ");Serial.println(ITerm);
  } 
  
  if (ITerm < MIN_FAN_CMD){ //Caso o Iterm passe o limite mínimo de cmd:
    /////////////////////////////////////////////////
    /////Pode  acontecer quando a temperatura//////// 
    /////da pilha estiver mais baixa do que deveria//
    
    //Serial.println("Terceiro IF");
    ITerm = MIN_FAN_CMD; //Define como o valor mínimo (15%)
    float LastIterm = MIN_FAN_CMD; //Atualiza o valor de LastIterm
    Serial.println("I term 3: ");Serial.println(ITerm);
  }
 

// Calcula o Derivative Term (Dterm)

  DTerm = D_CONST *((TempDiff - LastTempDiff) * LOOP_TIME); //Definido como a constante D multiplicado pela diferença de erro entre 2 loops e pelo LOOP_TIME
  
  //Serial.println("D term : ");Serial.println(DTerm);
  //Serial.print("LastTempDiff 1 :");Serial.println(LastTempDiff);
  //LastTempDiff = FcTemp - OptTemp; //Redefinição do LastTempoDiff para ser utilizado no próximo loop.
  //Serial.print("LastTempDiff 2 :");Serial.println(LastTempDiff);


// Combine Terms, and limit to max and min fan command
  UpdatedFanCmd  = (PTerm + ITerm + DTerm); //Calculo do sinal para o FAN em porcentagem: Definido como a soma entre os três termos do PID.
  //Serial.print("P I D : ");Serial.println(UpdatedFanCmd);
  if (UpdatedFanCmd  > MAX_FAN_CMD){ //Caso o valor do sinal ultrapasse o valor máximo:
    //Serial.println("Quarto IF");
    UpdatedFanCmd  = MAX_FAN_CMD; //Define o sinal como o valor máximo
  }

  if (UpdatedFanCmd  < MIN_FAN_CMD){ //Caso o valor do sinal ultrapasse o valor mínimo:
    //Serial.println("Quinto IF");
    UpdatedFanCmd  = MIN_FAN_CMD; //Define o sinal como o valor mínimo
  }
    
  delay(20);
  
  //float tempo_2_fan = millis(); //Cálculo do tempo que a função termina
  //LOOP_TIME = (tempo_2_fan - tempo_1_fan)/1000.0; //Define o valor do loop_time como a diferença entre o tempo em que começou e o tempo que terminou a função em segundos (/1000). 
  float LOOP_TIME_FAN = LOOP_TIME / 1000.0;
  //Serial.print("LOOP_TIME FAN :");
  //Serial.println(LOOP_TIME_FAN);
  
  float valor_pwm = (UpdatedFanCmd * 255.0)/100.0; //O updated fan retorna uma porcentagem, basta multiplicar por 255 para ter o valor do sinal PWM 
  analogWrite(pinoPWM,valor_pwm); //Envia o sinal para o pino PWM
  //Serial.print("valor_pwm");
  //Serial.println(valor_pwm);
  //delay(2000);


}
