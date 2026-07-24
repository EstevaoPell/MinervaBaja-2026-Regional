// CAN Receive Example
//

// CAN Receive Example

#include <mcp_can.h>
#include <SPI.h>
#include <string.h> 


long unsigned int rxId;
unsigned char len = 8, flag_frame;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

//const int pot = A0;

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
 Serial.begin(9600);

  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input

  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  //Serial.println(digitalRead(CAN0_INT));
  if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    //CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    CAN0.readMsgBuf(&rxId, &flag_frame, &len, rxBuf); 

   /* if(rxId == 2){     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    }
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    Serial.print(msgString);
  
    if(rxId == 4){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }*/
    //Serial.println();
    Serial.println(rxId);
    //delay(200);
    //Serial.println(rxBuf);  
    /*if(rxId != 0){
      Serial.println("entrou");
    }
    else{
      Serial.println("não entrou");
    }*/
    
  }
  
  
}

 /* bool checkRunStateFunction(unsigned char rxBuf[]) {
  bool linha[8];
  byte2bit(linha, rxBuf[1], 8, 1);
  if (linha[2] == 0 && linha[3] == 1) {
    return true;
  } else {
    return false;
  }
}

void byte2bit(bool bits[], int n_decimal, int length, int invert = 0){
  for(int i = 0;i<length;i++){
    bits[i] = 0;
  }
  for(int i = 0; n_decimal>0; i++){
    if(n_decimal%2 == 0) bits[i] = 0;
    else bits[i] = 1;
    n_decimal=n_decimal/2;
  }
  if(invert == 1){
    reverse(bits, length);
  }
}

CAN0.readMsgBuf(&rxId, &flag_frame, &len, rxBuf); 
if (rxId == 2 && !checkRunState) {
      return;
    }*/
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
