char SupplyValve;
int pino_supply = 2;

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

 /*har top_state = Check_alarms;
  char state = 'FC_Standby';
  char substate = 'StartUp_fan_spoolup';*/
  
void setup() {

  Serial.begin(9600);
  pinMode (pino_supply,OUTPUT); 
  //pinMode (pino_supply,OUTPUT); 
  digitalWrite (pino_supply,LOW);
  /*char top_state = 'Check_alarms';
  char state = 'FC_Standby';
  char substate = 'StartUp_fan_spoolup';*/

}

void loop() {
  
  switch (top_state){
    case  Check_alarms :
      delay(2000);
      top_state =  System ;
      Serial.print("O top_state é Check_alarms");
   
      break;
      
      
    case  System:
      delay(2000);
      top_state =  FC ;
      Serial.print("O top_state é System");
      
      break;

    case  FC :
      Serial.print("O top_state é FC/ ");

      switch(state){

        case  FC_Standby :
          delay(2000);
          //SupplyValve = 'false' ;
          state =  FC_StartUp ;
          Serial.print("O state é FC_Standby --> ");
          Serial.print("A válvula está fechada ");
          digitalWrite(pino_supply,LOW);  
          break;
          
        case  FC_StartUp :

          Serial.print("O state é FC_StartUp/ ");
          
          switch(substate){
            
            case  StartUp_fan_spoolup:
              delay(2000);
              //SupplyValve =  false ;
              substate = StartUp_Purge ;
              Serial.print("O substate é StartUp_fan_spoolup --> ");
              Serial.print("A válvula está fechada ");
              digitalWrite(pino_supply,LOW);
              break;
              
            case StartUp_Purge :
              delay(2000);
              //SupplyValve =  'true' ;
              substate = StartUp_End ;
              Serial.print("O substate é StartUp_Purge -->");
              Serial.print("A válvula está aberta ");  
              digitalWrite(pino_supply,HIGH);
              break;
              
            case  StartUp_End :
              delay(2000);
              //SupplyValve = 'true' ;
              state = FC_Run ; 
              Serial.print("O substate é StartUp_End -->");
              Serial.print("A válvula está aberta ");
              digitalWrite(pino_supply,HIGH);
              break;
              }
                
          break;
            
            
        case FC_Run :
          delay(2000);
          //SupplyValve =  'true' ;
          state = FC_Shutdown ;
          Serial.print("O state é Run -->");
          Serial.print("A válvula está aberta ");
          digitalWrite(pino_supply,HIGH);
          break;
      
        case  FC_Shutdown :
          delay(2000);
          //SupplyValve =  'false';
          state =  FC_Alarm ;
          Serial.print("O state é FC_Shutdown -->");
          Serial.print("A válvula está fechada ");
          digitalWrite(pino_supply,LOW);
         
          break;

        case  FC_Alarm :
          delay(2000);
          //SupplyValve =  'false ';
          state = FC_Alarm ;
          Serial.print("O state é FC_Alarm -->");
          Serial.print("A válvula está fechada "); 
          digitalWrite(pino_supply,LOW);
          break;
        }
        
    break;
    }

  /*rial.println(top_state );
   Serial.println(state);
   Serial.println(topstate);*/

   /*if (SupplyValve = 'true' ){
    digitalWrite(pino_supply,LOW);}
   if (SupplyValve =  'false' ){
    digitalWrite(pino_supply,HIGH);
    }*/
    
   //Serial.println(SupplyValve);
   //digitalWrite (pino_supply,SupplyValve);


}
    
