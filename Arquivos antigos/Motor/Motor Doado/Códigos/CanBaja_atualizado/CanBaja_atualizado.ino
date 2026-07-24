#include <SPI.h>
#include <mcp2515.h>
#include<string.h>

struct can_frame canMsg;
struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

void setup() {
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
  int can_id = 00010000;
  int can_dlc = 8;
  
  canMsg1.can_id  = 0x2;  //Edrv_Act_1 -> TX
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x00;
  canMsg1.data[1] = 0x80;
  canMsg1.data[2] = 0x6B;
  canMsg1.data[3] = 0x1F;
  canMsg1.data[4] = 0xE8;
  canMsg1.data[5] = 0x03;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = 0x7D;

  canMsg2.can_id  = 0xD;  // Eem_Edrv_Lim_1 -> RX
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 8;
  canMsg2.data[1] = 13;
  canMsg2.data[2] = 49;
  canMsg2.data[3] = 01;
  canMsg2.data[4] = 76;
  canMsg2.data[5] = 78;
  canMsg2.data[6] = 34;
  canMsg2.data[7] = 05;
  
  while (!Serial);
  Serial.begin(115200);
  
  Serial.println("Example: Write to CAN");

}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
      
  if(((canMsg.data[1],HEX) == 80) && ((canMsg.data[2],HEX) == 03)){ // Verifica se é permitido prosseguir com o start-up
    Serial.print("Conecte os 48V no motor");
    }

   mcp2515.sendMessage(&canMsg1);
   mcp2515.sendMessage(&canMsg2);

  Serial.println("Messages sent");
  
  delay(100);

  String mensagem,a,b,c,d,e,f,g,h;

  for (int i = 0; i<canMsg1.can_dlc; i++)  {  // print the data
      canMsg2.data[i] = canMsg1.data[i];
                       
                       // Byte 1
       if (canMsg2.data[i] == canMsg2.data[0]){      // Byte 1
         if (String(canMsg2.data[i],BIN).length() == 8){
            a = String(canMsg2.data[i],BIN);
            //Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 7){
            a = "0" + String(canMsg2.data[i],BIN);
            //Serial.print(mensagem.length());
         }
        if (String(canMsg2.data[i],BIN).length() == 6){
           a =  "00" + String(canMsg2.data[i],BIN);
            //Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 5){
           a =  "000" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 4){
           a = "0000"  + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 3){
           a = "00000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 2){
           a = "000000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 1){
          a = "0000000"  + String(canMsg2.data[i],BIN);
          }
       // mensagem = a;
 
       }
                               // Byte 2
       if (canMsg2.data[i] == canMsg2.data[1]){ 
         if (String(canMsg2.data[i],BIN).length() == 8){
             b = String(canMsg2.data[i],BIN);
            //Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 7){
             b = "0" + String(canMsg2.data[i],BIN);
            //Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 6){
            b =  "00"+ String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
         if (String(canMsg2.data[i],BIN).length() == 5){
            b =  "000" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
         if (String(canMsg2.data[i],BIN).length() == 4){
            b = "0000"  + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
         if (String(canMsg2.data[i],BIN).length() == 3){
            b = "00000" + String(canMsg2.data[i],BIN);
          }
         if (String(canMsg2.data[i],BIN).length() == 2){
            b = "000000" + String(canMsg2.data[i],BIN);
          }
         if (String(canMsg2.data[i],BIN).length() == 1){
            b = "0000000"  + String(canMsg2.data[i],BIN) ;
          } 
       //  mensagem = mensagem + b;
       }
                        // Byte 3
        if (canMsg2.data[i] == canMsg2.data[2]){       
         
         if (String(canMsg2.data[i],BIN).length() == 8){
             c = String(canMsg2.data[i],BIN);
            //Serial.print(mensagem.length());
           }
         if (String(canMsg2.data[i],BIN).length() == 7){
             c = "0" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
         }
        if (String(canMsg2.data[i],BIN).length() == 6){
            c =  "00" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 5){
            c =  "000" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 4){
           c = "0000" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 3){
          String c = "00000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 2){
            c = "000000"  + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 1){
            c = "0000000" + String(canMsg2.data[i],BIN) ;
          }
       // mensagem = mensagem + c; 
       }
                         // Byte 4
       if (canMsg2.data[i] == canMsg2.data[3]){      
         if (String(canMsg2.data[i],BIN).length() == 8){
            d = String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 7){
            d = "0" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
         }
        if (String(canMsg2.data[i],BIN).length() == 6){
            d =  "00" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 5){
            d =  "000" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 4){
            d = "0000" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 3){
           d = "00000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 2){
            d = "000000"+ String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 1){
            d = "0000000" + String(canMsg2.data[i],BIN) ;
          }
       //  mensagem = mensagem + d; 
       }
                        // Byte 5
       if (canMsg2.data[i] == canMsg2.data[4]){       
         if (String(canMsg2.data[i],BIN).length() == 8){
            e = String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 7){
             e = "0" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
         }
        if (String(canMsg2.data[i],BIN).length() == 6){
            e =  "00" + String(canMsg2.data[i],BIN);
            //Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 5){
           String e =  "000" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 4){
            e = "0000" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 3){
           e = "00000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 2){
            e = "000000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 1){
            e = "0000000" + String(canMsg2.data[i],BIN) ;
          }
      //  mensagem = mensagem + e; 
       }
                        // Byte 6
       if (canMsg2.data[i] == canMsg2.data[5]){       
         if (String(canMsg2.data[i],BIN).length() == 8){
            f =  String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 7){
             f = "0" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
         }
        if (String(canMsg2.data[i],BIN).length() == 6){
            f =  "00" + String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 5){
            f =  "000" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 4){
            f = "0000" + String(canMsg2.data[i],BIN);
          // Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 3){
           f = "00000"  + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 2){
            f = "000000"  + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 1){
            f = "0000000" + String(canMsg2.data[i],BIN) ;
          }
       // mensagem = mensagem + f; 
       }
                        // Byte 7
       if (canMsg2.data[i] == canMsg2.data[6]){       
         if (String(canMsg2.data[i],BIN).length() == 8){
            g = String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 7){
             g = "0" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
         }
        if (String(canMsg2.data[i],BIN).length() == 6){
            g =  "00" + String(canMsg2.data[i],BIN);
         //   Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 5){
            g =  "000" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 4){
            g = "0000" + String(canMsg2.data[i],BIN);
         //   Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 3){
           g = "00000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 2){
            g = "000000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 1){
            g = "0000000" + String(canMsg2.data[i],BIN) ;
          }
        //mensagem = mensagem + g; 
       }

                        // Byte 8
       if (canMsg2.data[i] == canMsg2.data[7]){       
         if (String(canMsg2.data[i],BIN).length() == 8){
            h = String(canMsg2.data[i],BIN);
           // Serial.print(mensagem.length());
         }
         if (String(canMsg2.data[i],BIN).length() == 7){
             h = "0" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
         }
        if (String(canMsg2.data[i],BIN).length() == 6){
            h =  "00" + String(canMsg2.data[i],BIN);
          //  Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 5){
            h =  "000" + String(canMsg2.data[i],BIN);
         //   Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 4){
            h = "0000" + String(canMsg2.data[i],BIN);
         //   Serial.print(mensagem.length());
          }
        if (String(canMsg2.data[i],BIN).length() == 3){
           h = "00000"  + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 2){
            h = "000000" + String(canMsg2.data[i],BIN);
          }
        if (String(canMsg2.data[i],BIN).length() == 1){
            h = "0000000" + String(canMsg2.data[i],BIN) ;
          }
        //mensagem = mensagem + h; 
       }
     delay(200);
     
    }

}

/*void Inicializacao_Concluida(){  // Verifica se a inicialização foi concluída
    if(h == 10){ 
        Serial.print("Inicialização finalizada");
    }
}*/

 //TX (Transmitted from BRM)

 // Primeira mensagem 
void Edrv_Act_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){  // ID / cycle  => 0x2 / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };

struct signalCan Edrv_Act_1_msg[8]{  

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Edrv_nrChksAct"; 
  Edrv_Act_1_msg[0].signalName = "Checksum actual torque";
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 8;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 255;
  Edrv_Act_1_msg[0].unit = "";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_nrAlvCntrAct";
  Edrv_Act_1_msg[1].signalName = "Alive counter actual torque";
  Edrv_Act_1_msg[1].startBit = 8;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";
  
  //Terceiro Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_stRunAct";
  Edrv_Act_1_msg[1].signalName = "Actual run state ";
  Edrv_Act_1_msg[1].startBit = 12;
  Edrv_Act_1_msg[1].lenght = 2;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 3;
  Edrv_Act_1_msg[1].unit = "";
 
  //Quarto Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_stOperModAct";
  Edrv_Act_1_msg[1].signalName = "Actual operation mode";
  Edrv_Act_1_msg[1].startBit = 14;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";
  
  //Quinto Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_tqAct";
  Edrv_Act_1_msg[1].signalName = "Actual torque";
  Edrv_Act_1_msg[1].startBit = 18;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
  
  //Sexto Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_nAct";
  Edrv_Act_1_msg[1].signalName = "Actual speed";
  Edrv_Act_1_msg[1].startBit = 30;
  Edrv_Act_1_msg[1].lenght = 13;
  Edrv_Act_1_msg[1].scale = 6;
  Edrv_Act_1_msg[1].offset = -24000;
  Edrv_Act_1_msg[1].minValue = -24000;
  Edrv_Act_1_msg[1].maxValue = 25146;
  Edrv_Act_1_msg[1].unit = "rpm";
 
  //Sétimo Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_uAct";
  Edrv_Act_1_msg[1].signalName = "Actual DC voltage";
  Edrv_Act_1_msg[1].startBit = 44;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 0.0625;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 63.9375;
  Edrv_Act_1_msg[1].unit = "V";
  
  //Oitavo Sinal  
  Edrv_Act_1_msg[1].nameArray = "Edrv_iAct";
  Edrv_Act_1_msg[1].signalName = "Actual DC current";
  Edrv_Act_1_msg[1].startBit = 54;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = -500;
  Edrv_Act_1_msg[1].minValue = -500;
  Edrv_Act_1_msg[1].maxValue = 523;
  Edrv_Act_1_msg[1].unit = "A";

 };
}
 
// Segunda mensagem
void Edrv_Req_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){   // ID / cycle  => 0x4 / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
struct signalCan Edrv_Req_1_msg[10]{

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Edrv_nrChksReq"; 
  Edrv_Act_1_msg[0].signalName = "Checksum request";
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 8;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 255;
  Edrv_Act_1_msg[0].unit = "";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_nrAlvCntrReq";   
  Edrv_Act_1_msg[1].signalName = "Alive counter request";
  Edrv_Act_1_msg[1].startBit = 8;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";
  
  //Terceiro Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_tqReq";
  Edrv_Act_1_msg[1].signalName = "Torque calculation EEM"; 
  Edrv_Act_1_msg[1].startBit = 12;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
 
  //Quarto Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_nReq";  
  Edrv_Act_1_msg[1].signalName = "Speed calculation EEM";
  Edrv_Act_1_msg[1].startBit = 24;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 6;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 24570;
  Edrv_Act_1_msg[1].unit = "rpm";
  
  //Quinto Sinal    OBS!!!!!
  Edrv_Act_1_msg[1].nameArray = "Edrv_stFltId"; 
  Edrv_Act_1_msg[1].signalName = "Failure identification";
  Edrv_Act_1_msg[1].startBit = 36;
  Edrv_Act_1_msg[1].lenght = 9;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 511;
  Edrv_Act_1_msg[1].unit = "";
 
  //Sexto Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_flgMilReqd"; 
  Edrv_Act_1_msg[1].signalName = "Malfunction indicator lamp request";
  Edrv_Act_1_msg[1].startBit = 45;
  Edrv_Act_1_msg[1].lenght = 1;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 1;
  Edrv_Act_1_msg[1].unit = "";
  
  //Sétimo Sinal  
  Edrv_Act_1_msg[1].nameArray = "Edrv_ratTCritMac"; 
  Edrv_Act_1_msg[1].signalName = "Machine temperature state";
  Edrv_Act_1_msg[1].startBit = 46;
  Edrv_Act_1_msg[1].lenght = 6;
  Edrv_Act_1_msg[1].scale = 2;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 126;
  Edrv_Act_1_msg[1].unit = "%";

 //Oitavo Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_ratTCritIvtr"; // SG_ Edrv_ratTCritIvtr : 52|6@1+ (2,0) [0|126] "%"  PT
  Edrv_Act_1_msg[1].signalName = "Inverter temperature state";
  Edrv_Act_1_msg[1].startBit = 52;
  Edrv_Act_1_msg[1].lenght = 6;
  Edrv_Act_1_msg[1].scale = 2;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 126;
  Edrv_Act_1_msg[1].unit = "%";
  
  //Nono Sinal  
  Edrv_Act_1_msg[1].nameArray = "Edrv_stTq"; 
  Edrv_Act_1_msg[1].signalName = "Torque plausibilisation state";
  Edrv_Act_1_msg[1].startBit = 60;
  Edrv_Act_1_msg[1].lenght = 2;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 3;
  Edrv_Act_1_msg[1].unit = "";
  
  //Décimo Sinal  
  Edrv_Act_1_msg[1].nameArray = "Edrv_stStrtPsbl"; 
  Edrv_Act_1_msg[1].signalName = "Start possible state";
  Edrv_Act_1_msg[1].startBit = 58;
  Edrv_Act_1_msg[1].lenght = 2;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 3;
  Edrv_Act_1_msg[1].unit = "";
  };
}  
 

// Terceira mensagem
void Edrv_Pred_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){   // ID / cycle  => 0x6 / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
struct signalCan Edrv_Pred_1_msg[7]{

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Edrv_nrChksLim";
  Edrv_Act_1_msg[0].signalName = "Checksum available torque";
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 8;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 255;
  Edrv_Act_1_msg[0].unit = "";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_nrAlvCntrLim";   
  Edrv_Act_1_msg[1].signalName = "Alive counter available torque";
  Edrv_Act_1_msg[1].startBit = 8;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";
  
  //Terceiro Sinal
  Edrv_Act_1_msg[1].nameArray = "Edrv_tqMaxEemPrdn "; 
  Edrv_Act_1_msg[1].signalName = "Maximum limited torque"; 
  Edrv_Act_1_msg[1].startBit = 12;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
 
  //Quarto Sinal
   Edrv_Act_1_msg[1].nameArray = "Edrv_tqMaxAvl"; 
  Edrv_Act_1_msg[1].signalName = "Maximum available torque"; 
  Edrv_Act_1_msg[1].startBit = 24;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
  
  //Quinto Sinal
   Edrv_Act_1_msg[1].nameArray = "Edrv_tqMinEemPrdn"; 
  Edrv_Act_1_msg[1].signalName = "Minimum limited torque"; 
  Edrv_Act_1_msg[1].startBit = 36;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
 
  //Sexto Sinal
   Edrv_Act_1_msg[1].nameArray = "Edrv_tqMinAvl"; 
  Edrv_Act_1_msg[1].signalName = "Minimum available torque"; 
  Edrv_Act_1_msg[1].startBit = 48;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
  
  //Sétimo Sinal  
  Edrv_Act_1_msg[1].nameArray = "Edrv_stActDern"; 
  Edrv_Act_1_msg[1].signalName = "Actual derating state";
  Edrv_Act_1_msg[1].startBit = 60;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";

  };
} 

// Quarta mensagem  OBS!!!!!
void Edrv_Status_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){   // ID / cycle  => 0x8 / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
struct signalCan Edrv_Status_1_msg[1]{

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Edrv_sMask ";
  Edrv_Act_1_msg[0].signalName = "Internal status mask";
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 64;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 1.84467440737096E+019;
  Edrv_Act_1_msg[0].unit = "";

  }; 
} 

/*
  
  int par_bin[10];  //AJEITAR DEPOIS


  //Cria array com os bits ordenados
  int can_frame_matrix[10];
  int index = 0;
  for(int i = 0; i< 8; i++){
    for(int j = -1; j <-9; j--){
 
      can_frame_matrix[index++] = par_bin[i][j];
      
      }
    
    }
  
  //Converte a base de dados de binario para valores físicos
  can_bin_data[10];
  index = 0;
  for(int i =0; i < 8; i++){
    char bin_data[10] = "";
    int startbit = Edrv_Act_1_msg[i].startBit;
    int finalbit = (startbit + Edrv_Act_1_msg[i].lenght);
    for(int j = startbit; j<finalbit;j++){
      bin_data = bin_data + can_frame_matrix[j];
      }
    can_bin_data[index++] = bin_data;
    bin_data = "";
    } 
*/

  //  Edrv_Act_1_msg = [Edrv_nrChksAct,Edrv_nrAlvCntrAct,Edrv_stRunAct,Edrv_stOperModAct,Edrv_tqAct,Edrv_nAct,Edrv_uAct,Edrv_iAct]
  


 //RX (Received by BRM)

 // Primeira mensagem
void Pt_Edrv_Des_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){   // ID / cycle  => 0x1 / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
 struct signalCan Pt_Edrv_Des_1_msg[6]{

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Pt_nrChksAct"; 
  Edrv_Act_1_msg[0].signalName = "Checksum torque request";
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 8;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 255;
  Edrv_Act_1_msg[0].unit = "";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Pt_nrAlvCntrAct";   
  Edrv_Act_1_msg[1].signalName = "Alive counter torque request";
  Edrv_Act_1_msg[1].startBit = 8;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";
  
  //Terceiro Sinal
  Edrv_Act_1_msg[1].nameArray = "Pt_stOperModDesEdrv";
  Edrv_Act_1_msg[1].signalName = "Operation mode request"; 
  Edrv_Act_1_msg[1].startBit = 12;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";
 
  //Quarto Sinal
  Edrv_Act_1_msg[1].nameArray = "Pt_tqDesEdrv";  
  Edrv_Act_1_msg[1].signalName = "Torque request & Maximum allowed torque"; 
  Edrv_Act_1_msg[1].startBit = 16;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
  
  //Quinto Sinal    OBS!!!!!
  Edrv_Act_1_msg[1].nameArray = "Pt_tqMinEdrv"; 
  Edrv_Act_1_msg[1].signalName = "Minimum allowed torque";
  Edrv_Act_1_msg[1].startBit = 28;
  Edrv_Act_1_msg[1].lenght = 12;
  Edrv_Act_1_msg[1].scale = 0.1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 209.5;
  Edrv_Act_1_msg[1].unit = "Nm";
 
  //Sexto Sinal
  Edrv_Act_1_msg[1].nameArray = "Pt_nDesEdrv"; 
  Edrv_Act_1_msg[1].signalName = "Speed request";
  Edrv_Act_1_msg[1].startBit = 40;
  Edrv_Act_1_msg[1].lenght = 13;
  Edrv_Act_1_msg[1].scale = 6;
  Edrv_Act_1_msg[1].offset = -24000;
  Edrv_Act_1_msg[1].minValue = -24000;
  Edrv_Act_1_msg[1].maxValue = 25146;
  Edrv_Act_1_msg[1].unit = "rpm";
  };
 }

 // Segunda mensagem
void Eem_Edrv_Pred_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){   // ID / cycle  => 0x5 / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
 struct signalCan Eem_Edrv_Pred_1_msg[4]{ 
                                                                                 

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Eem_uMaxPredEdrv"; 
  Edrv_Act_1_msg[0].signalName = "Predicted maximum DC voltage";
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 8;
  Edrv_Act_1_msg[0].scale = 0.25;
  Edrv_Act_1_msg[0].offset = 10;
  Edrv_Act_1_msg[0].minValue = 10;
  Edrv_Act_1_msg[0].maxValue = 73.75;
  Edrv_Act_1_msg[0].unit = "V";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_uMinPredEdrv ";   
  Edrv_Act_1_msg[1].signalName = "Predicted minimum DC voltage";
  Edrv_Act_1_msg[1].startBit = 8;
  Edrv_Act_1_msg[1].lenght = 8;
  Edrv_Act_1_msg[1].scale = 0.25;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 63.75;
  Edrv_Act_1_msg[1].unit = "V";
  
  //Terceiro Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_iMinPredEdrv";
  Edrv_Act_1_msg[1].signalName = "Predicted minimum DC current"; 
  Edrv_Act_1_msg[1].startBit = 16;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = -800;
  Edrv_Act_1_msg[1].minValue = -800;
  Edrv_Act_1_msg[1].maxValue = 223;
  Edrv_Act_1_msg[1].unit = "A";
 
  //Quarto Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_iMaxPredEdrv";  
  Edrv_Act_1_msg[1].signalName = "Predicted maximum DC current"; 
  Edrv_Act_1_msg[1].startBit = 26;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = -200;
  Edrv_Act_1_msg[1].minValue = -200;
  Edrv_Act_1_msg[1].maxValue = 823;
  Edrv_Act_1_msg[1].unit = "A";
  };
 }
/*
 // Terceira mensagem
void Eem_Edrv_Des_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp71){   // ID / cycle  => 0xB / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
 struct signalCan Eem_Edrv_Des_1_msg[4]{ 
                                                                                 
  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Eem_nrChksAct"; 
  Edrv_Act_1_msg[0].signalName = "Checksum charging voltage request";   
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 8;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 255;
  Edrv_Act_1_msg[0].unit = "";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_nrAlvCntrAct";   
  Edrv_Act_1_msg[1].signalName = "Alive counter charging voltage request";
  Edrv_Act_1_msg[1].startBit = 8;
  Edrv_Act_1_msg[1].lenght = 4;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 15;
  Edrv_Act_1_msg[1].unit = "";
  
  //Terceiro Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_uDesEdrv";
  Edrv_Act_1_msg[1].signalName = "Charging voltage request"; 
  Edrv_Act_1_msg[1].startBit = 12;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 0.0625;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 63.9375;
  Edrv_Act_1_msg[1].unit = "V";
 
  //Quarto Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_stRlyMvbEdrv";  
  Edrv_Act_1_msg[1].signalName = "48V-battery relay state";  
  Edrv_Act_1_msg[1].startBit = 22;
  Edrv_Act_1_msg[1].lenght = 2;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 3;
  Edrv_Act_1_msg[1].unit = "";
  };
 }

 // Quarta mensagem
void Eem_Edrv_Lim_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){   // ID / cycle  => 0xD / 10 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
 struct signalCan Eem_Edrv_Lim_1_msg[6]{   

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Eem_uMaxEdrv"; 
  Edrv_Act_1_msg[0].signalName = "Maximum allowed DC voltage";
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 10;
  Edrv_Act_1_msg[0].scale = 0.0625;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 63.9375;
  Edrv_Act_1_msg[0].unit = "V";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_uMinEdrv";   
  Edrv_Act_1_msg[1].signalName = "Minimum allowed DC voltage";
  Edrv_Act_1_msg[1].startBit = 10;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 0.0625;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 63.9375;
  Edrv_Act_1_msg[1].unit = "V";
  
  //Terceiro Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_rMvbEdrv";
  Edrv_Act_1_msg[1].signalName = "Estimated 48V-battery resistance"; 
  Edrv_Act_1_msg[1].startBit = 20;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 0.001;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 1.023;
  Edrv_Act_1_msg[1].unit = "Ohm";

  //Quarto Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_iReqEdrv";  
  Edrv_Act_1_msg[1].signalName = "Current calculation EEM"; 
  Edrv_Act_1_msg[1].startBit = 30;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = -500;
  Edrv_Act_1_msg[1].minValue = -500;
  Edrv_Act_1_msg[1].maxValue = 523;
  Edrv_Act_1_msg[1].unit = "A";
  
  //Quinto Sinal   
  Edrv_Act_1_msg[1].nameArray = "Eem_iMaxEdrv"; 
  Edrv_Act_1_msg[1].signalName = "Maximum allowed DC current";
  Edrv_Act_1_msg[1].startBit = 40;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 1023;
  Edrv_Act_1_msg[1].unit = "A";
 
  //Sexto Sinal
  Edrv_Act_1_msg[1].nameArray = "Eem_iMinEdrv"; 
  Edrv_Act_1_msg[1].signalName = "Minimum allowed DC current";
  Edrv_Act_1_msg[1].startBit = 50;
  Edrv_Act_1_msg[1].lenght = 10;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = -1000;
  Edrv_Act_1_msg[1].minValue = -1000;
  Edrv_Act_1_msg[1].maxValue = 23;
  Edrv_Act_1_msg[1].unit = "A";
  };
 }

 // Quinta mensagem
void Pt_Veh_1(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7){   // ID / cycle  => 0x10 / 100 ms
  

  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  };
 struct signalCan Pt_Veh_1_msg[2]{   

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Pt_stIgnSwt"; 
  Edrv_Act_1_msg[0].signalName = "Ignition switch state";
  Edrv_Act_1_msg[0].startBit = 12;
  Edrv_Act_1_msg[0].lenght = 3;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 7;
  Edrv_Act_1_msg[0].unit = "";

  //Segundo Sinal
  Edrv_Act_1_msg[1].nameArray = "Pt_flgCrash";   
  Edrv_Act_1_msg[1].signalName = "Crash flag";
  Edrv_Act_1_msg[1].startBit = 62;
  Edrv_Act_1_msg[1].lenght = 1;
  Edrv_Act_1_msg[1].scale = 1;
  Edrv_Act_1_msg[1].offset = 0;
  Edrv_Act_1_msg[1].minValue = 0;
  Edrv_Act_1_msg[1].maxValue = 1;
  Edrv_Act_1_msg[1].unit = "";
 };
}

 // Sexta mensagem
/*void Pt_Obd_2(char * tp0,char * tp1,char * tp2,char * tp3,char * tp4,char * tp5,char * tp6,char * tp7) {   // ID / cycle  => 0x11 / 200 ms
  
  struct signalCan {
    char nameArray[30];
    char signalName[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
  }
 struct signalCan Pt_Obd_2_msg[1]{   

  //Primeiro sinal
  Edrv_Act_1_msg[0].nameArray = "Pt_tiSnceEngStrtd"; 
  Edrv_Act_1_msg[0].signalName = "Time since engine started"; //SG_ Pt_tiSnceEngStrtd : 0|16@1- (1,0) [0|65535] "s"  
  Edrv_Act_1_msg[0].startBit = 0;
  Edrv_Act_1_msg[0].lenght = 16;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 65535;
  Edrv_Act_1_msg[0].unit = "s";
 }
}*/
