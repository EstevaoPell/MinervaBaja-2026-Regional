#include <CAN.h> //Inclui a biblioteca CAN

void setup() {
  Serial.begin(9600); //inicia a serial para debug
  while (!Serial);

  Serial.println("Transmissor CAN");

  // Inicia o barramento CAN a 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Falha ao iniciar o controlador CAN"); //caso não seja possível iniciar o controlador
    while (1);
  }
}
