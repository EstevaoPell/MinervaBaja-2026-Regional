#include <stdio.h>
#include <stdlib.h>

//void Edrv_Act_1_msg(){




  struct signalCan {
    int id;
    char mensagem[30];
    char signalName[30];
    char alias[30];
    int startBit;
    int lenght;
    int scale;
    float offset;
    float minValue;
    float maxValue;
    char unit[10];
    float physical_atual;
    };    

  //TX
  //Sinais Edrv_Act_1
  
  signalCan Edrv_nrChksAct = {2,"Edrv_Act_1_msg","Edrv_nrChksAct","Checksum actual torque",0,8,1,0,0,255,"-"};
  signalCan Edrv_nrAlvCntrAct = {2,"Edrv_Act_1_msg","Edrv_nrAlvCntrAct","Alive counter actual torque",8,4,1,0,0,15,"-"};
  signalCan Edrv_stRunAct = {2,"Edrv_Act_1_msg","Edrv_stRunAct","Actual run state",12,2,1,0,0,3,"-"};
  signalCan Edrv_stOperModAct = {2,"Edrv_Act_1_msg","Edrv_stOperModAct","Actual operation mode",14,4,1,0,0,15,"-"};
  signalCan Edrv_tqAct = {2,"Edrv_Act_1_msg","Edrv_tqAct","Actual torque",18,12,0.1,-200,-200,209.5,"Nm"};
  signalCan Edrv_nAct = {2,"Edrv_Act_1_msg","Edrv_nAct","Actual speed",30,13,6,-24000,-24000,25146,"rpm"};
  signalCan Edrv_uAct = {2,"Edrv_Act_1_msg","Edrv_uAct","Actual DC voltage",44,10,0.0625,0,0,63.9375,"V"};
  signalCan Edrv_iAct = {2,"Edrv_Act_1_msg","Edrv_iAct","Actual DC current",54,10,1,-500,-500,523,"A"}; 

  char *mensagem[] = {"Edrv_nrChksAct","Edrv_nrAlvCntrAct","Edrv_nrChksAct","Checksum actual torque"};
  char *startBit[] = {"0","2"};
  char *lenght[] = {"8","1"};
  char *raw_value_decimal[] = {};
void setup() {   
  Serial.begin(115200);
  
}
void loop() {
  // put your main code here, to run repeatedly:
  
 

 Edrv_nrAlvCntrAct.physical_atual = 10;
 
 String mensagem  = String(mensagem[2]);
 int soma = mensagem.toInt(); 
 //Serial.println(soma);
 String mensagem_final;
 //Serial.println(edrv_nrChksAct[2]);]
 String sinal = mensagem_final.substring(startBit[0],lenght[0]);
 Serial.println(lenght[0]);
 //String raw_value_decimall = String(sinal,DEC);
// float raw_value_decimal = raw_value_decimall.toInt();
 //  if(soma == 2){
   //   String sinal = mensagem.substring(startBit[i],lenght[i]);
     // for(int i=0; i<8; i++){
       // int physical_value = offset[i] + scale[i]*raw_value_decimal;
        //}
  //String raw_value_decimal = mensagem.substring(,64);
  //Edrv_nrChksAct.physical_atual = Edrv_nrChksAct.offset + (Edrv_nrChksAct.scale* ;
  //Serial.println(edrv_nrChksAct[1]);
  }

  

 
 //physical_value = offset + scale * raw_value_decimal
   



 
   // signalCan signalCan Edrv_Act_1_msg[8] = {"Pt_stIgnSwt","Ignition switch state",12,3,1,0,0,7};
 // struct signalCan Edrv_Act_1_msg[8]{
  //  Edrv_Act_1_msg[0].nameArray = "Edrv_nrChksAct"
  //  };
    //Edrv_Act_1_msg[0].nameArray = "Edrv_nrChksAct"; 
    //Edrv_Act_1_msg[0].nameArray = "Edrv_nrChksAct"; 
  /* Serial.println(A.nameArray);
   Serial.println(A.signalName);
   Serial.println(A.startBit);*/







/*{   

  
  //Primeiro sinal
  Edrv_Act_1_msg.nameArray = "Pt_stIgnSwt"; 
  Edrv_Act_1_msg[0].signalName = "Ignition switch state";
  Edrv_Act_1_msg[0].startBit = 12;
  Edrv_Act_1_msg[0].lenght = 3;
  Edrv_Act_1_msg[0].scale = 1;
  Edrv_Act_1_msg[0].offset = 0;
  Edrv_Act_1_msg[0].minValue = 0;
  Edrv_Act_1_msg[0].maxValue = 7;
  //Edrv_Act_1_msg[0].unit = "";

 
}*/
