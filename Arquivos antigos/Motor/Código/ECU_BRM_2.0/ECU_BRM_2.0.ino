#include <mcp_can.h>
#include <SPI.h>
#include <OperCan.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10

int ledpin = 5;
int OnState_Counter = 0;
int tps = A5;

//------------------------------------------------------------------------------
byte BitCounter(int x){ //Conta o número de bits
  for (int bit = 15; bit >= 0; bit--){
    if (bitRead(x, bit)){
      return bit + 1;
    }
  }
  return 0;
  }
//------------------------------------------------------------------------------
int stringtoint(String val){
  int valorint = atoi(val.c_str());
  return valorint;
}
//------------------------------------------------------------------------------


void setup()
{
  Serial.begin(115200);  
  // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");  
    
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.
  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input

  pinMode(ledpin, OUTPUT);
  pinMode(tps,INPUT);
}

//byte SetVoltCurr_data[8] = {0x00, 0x03, 0x48, 0x01, 0x7D, 0x32, 0xD8, 0x0F}; //Seta Voltaem min,max e corrente min,max
//byte SetVoltCurr_data[8] = {0x50, 0xC3, 0x4B, 0x01, 0x7D, 0x09, 0xA0, 0x0F}; //Seta Voltaem min,max(47V,53v) e corrente min,max(0A,9A)
byte SetVoltCurr_data[8] = {0xA0, 0x82, 0x48, 0x01, 0x7D, 0x32, 0xA0, 0x0F}; //Seta Voltaem min,max(34V,42v) e corrente min,max(0A,50A)
byte IniOn_data[8] = {0x00, 0x50, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00}; // Inition On
//byte TrqMd1_data[7] = {0x00, 0x10, 0xDA, 0xC7, 0x5D, 0xA0, 0x0F}; //Torque Mode - 1Nm
//byte TrqMd1_data[7] = {0x00, 0x10, 0xDA, 0xC7, 0x5D, 0xED, 0x10}; //Torque Mode - 1Nm - 1998rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0xDA, 0xC7, 0x5D, 0xED, 0x10}; //Speed Mode - 1Nm - 1998rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0xDA, 0xC7, 0x5D, 0x47, 0x10}; //Speed Mode - 1Nm - 1000rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0xE4, 0x67, 0x7C, 0xED, 0x10}; //Speed Mode - 2Nm - 1998rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0xE4, 0x67, 0x7C, 0x47, 0x10}; //Speed Mode - 2Nm - 1002rpm
byte TrqMd1_data[7] = {0x00, 0x60, 0xE4, 0x67, 0x7C, 0xE1, 0x12}; //Speed Mode - 2Nm - 5000rpm
//byte TrqMd1_data[7] = {0x00, 0x10, 0x3E, 0x68, 0x7C, 0x47, 0x10};//Torque Mode - 11Nm
byte ShutDown_data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00}; //ShutDownown Inition Off

void loop(){
  //Base de dados dos sinais do ID: 0x2
  //Signal = [startbit, lenght, scale, offset, minimum value, maximum value]
  int Edrv_nrChksAct[] = {0,8,1,0,0,255}; //Checksum actual torque / ''
  int Edrv_nrAlvCntrAct[] = {8,4,1,0,0,15}; //Alive counter actual torque / ''
  int Edrv_stRunAct[] = {12,2,1,0,0,3}; //Actual run state / ''
  int Edrv_stOperModAct[] = {14,4,1,0,0,15}; //Actual operation mode / ''
  int Edrv_tqAct[] = {18,12,0.1,-200,-200,209.5}; //Actual torque(Nm) / ''
  int Edrv_nAct[] = {30,13,6,-24000,-24000,25146}; //Actual speed(rpm) / ''
  int Edrv_uAct[] = {44,10,0.0625,0,0,63.9375}; //Actual DC voltage(V)
  int Edrv_iAct[] = {54,10,1,-500,-500,523}; //Actual DC current(A)
  
  if(!digitalRead(CAN0_INT)){ // If CAN0_INT pin is low, read receive buffer
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

//--------------------------------------------------------------------------------------
    if (rxId == 2){
      BitsMatrix = CanMatrix(len, rxBuf);
//--------------------------------------------------------------------------------------
      String Actual_run_state = ""; 
      int bit_Actual_run_state = Edrv_stRunAct[0]+Edrv_stRunAct[1]-1;
      for(int m=Edrv_stRunAct[0]; m<Edrv_stRunAct[0]+Edrv_stRunAct[1]; m++){
        Actual_run_state.concat(String(BitsMatrix[bit_Actual_run_state]));
        bit_Actual_run_state = bit_Actual_run_state-1;
      }
      Serial.print("Actual_run_state= ");
      if (Actual_run_state=="00"){
        Serial.print("Pre-Run");
        digitalWrite(ledpin, HIGH);
        delay(100);
        digitalWrite(ledpin, LOW);
        delay(100);
      }
      if (Actual_run_state=="01"){
        Serial.print("Run");
        digitalWrite(ledpin, HIGH);
      }
      if (Actual_run_state=="10"){
        Serial.print("Post-Run");
        digitalWrite(ledpin, LOW);
      }
      if (Actual_run_state=="11"){
        Serial.print("Post-Run finished");
      }
      
      Serial.print("  /  ");
    //-----------------------------------------------------------------------------
      String Actual_operation_mode = ""; 
      int bit_Actual_operation_mode = Edrv_stOperModAct[0]+Edrv_stOperModAct[1]-1;
      for(int m=Edrv_stOperModAct[0]; m<Edrv_stOperModAct[0]+Edrv_stOperModAct[1]; m++){
        Actual_operation_mode.concat(String(BitsMatrix[bit_Actual_operation_mode]));
        bit_Actual_operation_mode = bit_Actual_operation_mode-1;
      }
      Serial.print("Actual_operation_mode= ");
      if (Actual_operation_mode=="1110"){
        Serial.print("Standby");
      }
      if (Actual_operation_mode=="0000"){
        Serial.print("Idle");
      }
      if (Actual_operation_mode=="0001"){
        Serial.print("Torque Mode");
      }
      if (Actual_operation_mode=="0100"){
        Serial.print("Voltage Mode");
      }
      if (Actual_operation_mode=="0110"){
        Serial.print("Speed Mode");
      }
      if (Actual_operation_mode=="1011"){
        Serial.print("Start Mode");
      }
      if (Actual_operation_mode=="1111"){
        Serial.print("Failure");
      }
      Serial.print("  /  ");
//-----------------------------------------------------------------------------
      String Actual_DC_Voltage = "";
      int bit_Actual_DC_Voltage = Edrv_uAct[0]+Edrv_uAct[1]-1;
      for(int m=Edrv_uAct[0]; m<Edrv_uAct[0]+Edrv_uAct[1]; m++){
        Actual_DC_Voltage.concat(String(BitsMatrix[bit_Actual_DC_Voltage]));
        bit_Actual_DC_Voltage = bit_Actual_DC_Voltage-1;
      }
      //Serial.print("Actual_DC_Voltage= ");
      //Serial.print(Actual_DC_Voltage);
      //Serial.print("  /  ");
//-----------------------------------------------------------------------------
      String Actual_DC_Current = "";
      int bit_Actual_DC_Current = Edrv_iAct[0]+Edrv_iAct[1]-1;
      for(int m=Edrv_iAct[0]; m<Edrv_iAct[0]+Edrv_iAct[1]; m++){
        Actual_DC_Current.concat(String(BitsMatrix[bit_Actual_DC_Current]));
        bit_Actual_DC_Current = bit_Actual_DC_Current-1;
      }
      //Serial.print("Actual_DC_Current= ");
      //Serial.print(Actual_DC_Current);
      //Serial.print("  /  ");
//-----------------------------------------------------------------------------
      String Actual_speed = "";
      int bit_Actual_speed = Edrv_nAct[0]+Edrv_nAct[1]-1;
      for(int m=Edrv_nAct[0]; m<Edrv_nAct[0]+Edrv_nAct[1]; m++){
        //Actual_speed[m]=BitsMatrix[bit_Actual_speed];
        Actual_speed.concat(String(BitsMatrix[bit_Actual_speed]));
        bit_Actual_speed = bit_Actual_speed-1;
      }
      //Serial.print("Actual_speed= ");
      //Serial.print(Actual_speed);
      //Serial.print("  /  ");
//-----------------------------------------------------------------------------
        
    Serial.println();
  }
}
//---------------------------Transmissao de dados------------------------------
  byte IniOn = CAN0.sendMsgBuf(0x10, 0, 8, IniOn_data);
  byte SetVoltCurr = CAN0.sendMsgBuf(0xD, 0, 8, SetVoltCurr_data);
      delay(5);
      if(IniOn == CAN_OK){
      //Serial.println("IniOn Sent Successfully!");
      } else {
      Serial.println("Error Sending IniOn...");
      }
      
  float valor_tps = analogRead(tps);
  Serial.print("  Valor TPS: ");Serial.print(valor_tps);
  if (valor_tps > 500) {
      byte TrqMd1 = CAN0.sendMsgBuf(0x1, 0, 7, TrqMd1_data);
      delay(10);
      if(TrqMd1 == CAN_OK){
      //Serial.println("TrqMd1 Sent Successfully!");
      } else {
      Serial.println("Error Sending TrqMd1...");
      }
      OnState_Counter = 1;
  }
  
  if (valor_tps < 500) {
    if (OnState_Counter==1){
      byte ShutDown = CAN0.sendMsgBuf(0x10, 0, 8, ShutDown_data);
      delay(10);
      if(ShutDown == CAN_OK){
      //Serial.println("ShutDown Sent Successfully!");
      } else {
      Serial.println("Error Sending Ss...");
      }
      OnState_Counter = 0;
    }
  }
//-----------------------------------------------------------------------------
}

//Por: JV