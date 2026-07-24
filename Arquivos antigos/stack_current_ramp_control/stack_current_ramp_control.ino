//Fc - Function - Stack Current Ramp Control - Função que realiza o controle da corrente da Stack

//Definição de veriáveis:

//Inputs:
float CurrentRequest; //Corrente solicitada
unsigned long CurrentTime; //Horário do sistema atual 
//-----------------------------------------------------------------------------------

//Outputs:
float CurrentCmd; //Comando para a alimentação de corrente
//-----------------------------------------------------------------------------------

//Constants:
float FC_MAX_CURRENT = 65.3; //Corrente máxima da stack
float FC_MIN_CURRENT = 7.3; //Corrente minima da Stack
float CURRENT_UP_RATE = 0.002; //taxa máxima de aumento da corrente com relação ao tempo
float CURRENT_DN_RATE = 0.001; //taxa mínima de aumento da corrente com relação ao tempo
unsigned long LOOP_TIME = 0; //Tempo do loop do controlador
float RESET_TIME = 3000.0; //tempo de delay para resetar as variáveis estáticas
//-----------------------------------------------------------------------------------

//Local Static Variables:
unsigned long LastCallTime; //Horário da última vez que esse função foi chamada
float LastCurrentCmd; //O comando de corrente do último loop
//-----------------------------------------------------------------------------------

int pino_corrente = A3; //Define o pino de entrada do sinal de corrente

void setup(){
  Serial.begin(9600); //Inicializa a serial
  pinMode (pino_corrente,INPUT); //Define o pino de corrente como entrada
  }

void loop() {
  
  float tempo_1_current_ramp = millis(); //marca o tempo de ínicio de loop

  float valor_potenciometro = analogRead(pino_corrente); //Lê o valor de corrente
  CurrentRequest = map(valor_potenciometro,0,1023,0,75); //Mapeia o valor de sinal para Amperes
  Serial.print("CurrentRequest : ");Serial.println(CurrentRequest);
 
  if(CurrentTime - LastCallTime >= RESET_TIME){ //Verifica se o tempo decorrido entre duas chamadas de função é maior ou igual que RESET_TIME
    LastCurrentCmd = FC_MIN_CURRENT; //Se a condição for verdadeira, o valor da corrente retornado pela função da última vez que foi chamada assume o valor mínimo
    } 

  CurrentTime = millis();
  LastCallTime = CurrentTime; //Atualiza o horário em que a função foi chamada pela última vez para o tempo atual
  
  Serial.print("LastCurrentCmd : ");Serial.println(LastCurrentCmd);
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
  Serial.println("Corrente enviada: ");Serial.println(CurrentCmd);
  
  LastCurrentCmd = CurrentCmd;//Atualiza o valor de LastCurrentCmd que será utilizado no próximo loop
  delay(200);
  
  float tempo_2_current_ramp = millis(); //Define o tempo do fim do loop;
  LOOP_TIME = (tempo_2_current_ramp - tempo_1_current_ramp); //tempo do loop;
  

}
