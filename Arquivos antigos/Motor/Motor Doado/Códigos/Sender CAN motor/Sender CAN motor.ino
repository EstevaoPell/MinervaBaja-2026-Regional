// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  //CAN.setPins(rx, tx); // rx - new CRX pin to use, defaults to 4. tx - new CTX pin to use, defaults to 5.

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");
  
  byte data[7] = {0, 0,0xD0, 0xC7, 0x5D, 0xA0, 0x0F};
  
  CAN.beginPacket(0x1); 
  CAN.write(data[7]); 
  CAN.endPacket();

  Serial.println("done");

  delay(1000);
}