#include <mcp_can.h>
#include <SPI.h>
//#include <Vector.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128]; // Array to store serial string

#define CAN0_INT 2 // Set INT to pin 2
MCP_CAN CAN0(10); // Set CS to pin 10

int ledpin = 5;
int OnState_Counter = 0;
int tps = A5;

// Variáveis de dados CAN definidas no escopo global
byte SetVoltCurr_data[8] = {0xA0, 0x82, 0x48, 0x01, 0x7D, 0x32, 0xA0, 0x0F}; // Dados de exemplo
byte IniOn_data[8] = {0x00, 0x50, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00}; // Dados de exemplo
byte ShutDown_data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00}; // Dados de exemplo

// Speed Mode
                      ///          0xE4, 0x67        0x11, 0x10   -- >   2 Nm    678 rpm
                      ///          0x30, 0x08        0xE1, 0x12   -- > 9,6 Nm   4998 rpm   
                      ///          0xA8, 0x07        0x11, 0x0E   -- >  -4 Nm  -2394 rpm
                      ///          0x16, 0x08                     -- >   7 Nm

byte TrqMd1_data[7] = {0x00, 0x60, 0x16, 0x08, 0x7C, 0xE1, 0x12}; //  7 Nm   4998 rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0x30, 0x08, 0x7C, 0xE1, 0x12}; //  9,6 Nm   4998 rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0x16, 0x08, 0x7C, 0x11, 0x10}; //  7 Nm    678 rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0xA8, 0x07, 0x7C, 0x11, 0x0E}; // -4 Nm  -2394 rpm
//byte TrqMd1_data[7] = {0x00, 0x60, 0x16, 0x08, 0x7C, 0x11, 0x0E}; //  7 Nm  -2394 rpm



// Variáveis de sinais CAN definidas no escopo global
int Edrv_nrChksAct[] = {0,8,1,0,0,255}; // Checksum actual torque / ''
int Edrv_nrAlvCntrAct[] = {8,4,1,0,0,15}; // Alive counter actual torque / ''
int Edrv_stRunAct[] = {12,2,1,0,0,3}; // Actual run state / ''
int Edrv_stOperModAct[] = {14,4,1,0,0,15}; // Actual operation mode / ''
int Edrv_tqAct[] = {18,12,0.1,-200,-200,209.5}; // Actual torque(Nm) / ''
int Edrv_nAct[] = {30,13,6,-24000,-24000,25146}; // Actual speed(rpm) / ''
int Edrv_uAct[] = {44,10,0.0625,0,0,63.9375}; // Actual DC voltage(V)
int Edrv_iAct[] = {54,10,1,-500,-500,523}; // Actual DC current(A)

// Função para criar a matriz de bits a partir do buffer CAN
byte* CanMatrix(int length, unsigned char* buffer) {
    // Calcula o número total de bits necessários
    int numBits = length * 8;
    
    // Aloca memória para a matriz de bits
    byte* bitsMatrix = (byte*)malloc(numBits * sizeof(byte));
    
    if (bitsMatrix == NULL) {
        Serial.println("Erro ao alocar memória para BitsMatrix");
        return NULL;
    }

    // Preenche a matriz com os bits dos dados do buffer
    int bitIndex = 0;
    for (int i = 0; i < length; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            bitsMatrix[bitIndex++] = bitRead(buffer[i], bit);
        }
    }

    return bitsMatrix;
}

// Função para liberar a memória alocada
void freeMatrix(byte* matrix) {
    free(matrix);
}

void setup() {
    Serial.begin(115200);  
    if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK)
        Serial.println("MCP2515 Initialized Successfully!");
    else
        Serial.println("Error Initializing MCP2515...");  
    
    CAN0.setMode(MCP_NORMAL); // Set operation mode to normal so the MCP2515 sends acks to received data.
    pinMode(CAN0_INT, INPUT); // Configuring pin for /INT input

    pinMode(ledpin, OUTPUT);
    pinMode(tps, INPUT);
}

void loop() {
    if (!digitalRead(CAN0_INT)) { // If CAN0_INT pin is low, read receive buffer
        CAN0.readMsgBuf(&rxId, &len, rxBuf); // Read data: len = data length, buf = data byte(s)

        if (rxId == 2) {
            byte* BitsMatrix = CanMatrix(len, rxBuf);
            
            if (BitsMatrix != NULL) {
                // Process BitsMatrix
                String Actual_run_state = ""; 
                int bit_Actual_run_state = Edrv_stRunAct[0] + Edrv_stRunAct[1] - 1;
                for (int m = Edrv_stRunAct[0]; m < Edrv_stRunAct[0] + Edrv_stRunAct[1]; m++) {
                    Actual_run_state.concat(String(BitsMatrix[bit_Actual_run_state]));
                    bit_Actual_run_state = bit_Actual_run_state - 1;
                }
                Serial.print("Actual_run_state= ");
                if (Actual_run_state == "00") {
                    Serial.print("Pre-Run");
                    digitalWrite(ledpin, HIGH);
                    delay(100);
                    digitalWrite(ledpin, LOW);
                    delay(100);
                }
                if (Actual_run_state == "01") {
                    Serial.print("Run");
                    digitalWrite(ledpin, HIGH);
                }
                if (Actual_run_state == "10") {
                    Serial.print("Post-Run");
                    digitalWrite(ledpin, LOW);
                }
                if (Actual_run_state == "11") {
                    Serial.print("Post-Run finished");
                }
                Serial.print("  /  ");

                // Processamento similar para outros dados...

                Serial.println();
                
                // Liberar a memória
                freeMatrix(BitsMatrix);
            }
        }
    }

    // Transmissao de dados
    byte IniOn = CAN0.sendMsgBuf(0x10, 0, 8, IniOn_data);
    byte SetVoltCurr = CAN0.sendMsgBuf(0xD, 0, 8, SetVoltCurr_data);
    delay(5);
    if (IniOn == CAN_OK) {
        //Serial.println("IniOn Sent Successfully!");
    } else {
        Serial.println("Error Sending IniOn...");
    }

    float valor_tps = analogRead(tps);
    Serial.print("  Valor TPS: ");
    Serial.print(valor_tps);
    if (valor_tps > 90) {
        byte TrqMd1 = CAN0.sendMsgBuf(0x1, 0, 7, TrqMd1_data);
        delay(10);
        if (TrqMd1 == CAN_OK) {
            //Serial.println("TrqMd1 Sent Successfully!");
        } else {
            Serial.println("Error Sending TrqMd1...");
        }
        OnState_Counter = 1;
    }

    if (valor_tps < 90) {
        if (OnState_Counter == 1) {
            byte ShutDown = CAN0.sendMsgBuf(0x10, 0, 8, ShutDown_data);
            delay(10);
            if (ShutDown == CAN_OK) {
                //Serial.println("ShutDown Sent Successfully!");
            } else {
                Serial.println("Error Sending ShutDown...");
            }
            OnState_Counter = 0;
        }
    }
}
