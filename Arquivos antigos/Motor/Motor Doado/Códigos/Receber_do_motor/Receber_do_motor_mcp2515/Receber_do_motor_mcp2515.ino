#include <SPI.h>
#include <mcp2515.h>
#include<string.h>
struct can_frame canMsg;
struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

int can_id = 00010000;
 char *mensagem[] = {"Edrv_nrChksAct","Edrv_nrAlvCntrAct","Edrv_nrChksAct","Checksum actual torque"};
 char *startBit[] = {"14","2"};
 char *lenght[] = {"4","1"};
 char *offset[] ={"0"};
 char *scale[] ={"1"};
 //char *raw_value_decimal[]={};
// Raw_value_decimal[0] = "12";
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
  
  Serial.print("Example: Write to CAN");
 // Serial.println(canMsg1.data[1], HEX);

}
//byte dados[8] = {00000000,10000000,00000011,00000000,00000000,00000000,10000000,00000000};
void loop() {
  /*if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }
  */
  /*if (int teste == 1) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }
    Serial.println();      
  }*/
  int test=1;
  if (test == 1) {
   // Serial.print(canMsg1.can_id); // print ID
    Serial.print(" "); 
   // Serial.print(canMsg1.can_dlc); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg1.can_dlc; i++)  {  // print the data
      //Serial.print(canMsg1.data[i]);
      Serial.print(" ");
    }
    Serial.println();      
  }

  if(((canMsg.data[1],HEX) == 80) && ((canMsg.data[2],HEX) == 03)){ // Verifica se é permitido prosseguir com o start-up
    Serial.print("Conecte os 48V no motor");
    }
  unsigned char v_inicializacao = (canMsg.data[1],HEX);
//  Inicializacao_Concluida(v_inicializacao);  

   mcp2515.sendMessage(&canMsg1);
   mcp2515.sendMessage(&canMsg2);

  Serial.println("Messages sent");
  
  delay(100);
  
 
 // canMsg2.data[2] =  (canMsg1.data[1]);
  //String c = a += ";";
  //String d = c += b;
  //char sinal[2];
  //char sinal[]= a;
  //sinal[2]= a;  */
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
    
   /*String inverter = mensagem.substring(0,8);
  
  char str[9];
  inverter.toCharArray(str, 9);
  int i=0, aux, fim, tam = inverter.length();
  // inverte o sinal para leitura
    fim = tam - 1; // índice do último caracter
    for(i = 0; i < tam/2; i++){
        aux = str[i];
        str[i] = str[fim];
        str[fim] = aux;
        fim--;
    }*/
   
   mensagem = a+b+c+d+e+f+g+h;
    //har *myStrings[2] = {canMsg2.data[0]};
  //  for (int i = 0; i < 2; i++) {
   // Serial.print(arr[i]);
    //delay(500);
  // }
  //string pega ={mensagem};
  Serial.println(mensagem);
  //Serial.println(e);
  // Separa o sinal desejado da mensagem

  // Separa o byte 1 da mensagem
  //Serial.println(mensagem.substring(0,8));
         
          //inverte Byte 1
  String inverter_a = mensagem.substring(0,8);
  char str_a[9];
  inverter_a.toCharArray(str_a, 9);
  int n_a = 0, aux_a, fim_a, tam_a = inverter_a.length();
  // inverte o sinal para leitura
    fim_a = tam_a - 1; // índice do último caracter
    for(n_a = 0; n_a < tam_a/2; n_a++){
        aux_a = str_a[n_a];
        str_a[n_a] = str_a[fim_a];
        str_a[fim_a] = aux_a;
        fim_a--;
    }
  Serial.println(str_a);
  
  // Separa o byte 2 da mensagem
  //Serial.println(mensagem.substring(8,16));
            //inverte byte 2
  String inverter_b = mensagem.substring(8,16);
  char str_b[9];
  inverter_b.toCharArray(str_b, 9);
  int n_b=0, aux_b, fim_b, tam_b = inverter_b.length();
  // inverte o sinal para leitura
    fim_b = tam_b - 1; // índice do último caracter
    for(n_b = 0; n_b < tam_b/2; n_b++){
        aux_b = str_b[n_b];
        str_b[n_b] = str_b[fim_b];
        str_b[fim_b] = aux_b;
        fim_b--;
    }
    Serial.println(str_b);

     // Separa o byte 3 da mensagem
  //Serial.println(mensagem.substring(16,24));
            //inverte byte 3
  String inverter_c = mensagem.substring(16,24);
  char str_c[9];
  inverter_c.toCharArray(str_c, 9);
  int n_c=0, aux_c, fim_c, tam_c = inverter_c.length();
  // inverte o sinal para leitura
    fim_c = tam_c - 1; // índice do último caracter
    for(n_c = 0; n_c < tam_c/2; n_c++){
        aux_c = str_c[n_c];
        str_c[n_c] = str_c[fim_c];
        str_c[fim_c] = aux_c;
        fim_c--;
    }
   Serial.println(str_c);

      // Separa o byte 4 da mensagem
  //Serial.println(mensagem.substring(24,32));
            //inverte byte 4
  String inverter_d = mensagem.substring(24,32);
  char str_d[9];
  inverter_d.toCharArray(str_d, 9);
  int n_d=0, aux_d, fim_d, tam_d = inverter_d.length();
  // inverte o sinal para leitura
    fim_d = tam_d - 1; // índice do último caracter
    for(n_d = 0; n_d < tam_d/2; n_d++){
        aux_d = str_d[n_d];
        str_d[n_d] = str_d[fim_d];
        str_d[fim_d] = aux_d;
        fim_d--;
    }
    Serial.println(str_d);

          // Separa o byte 5 da mensagem
  //Serial.println(mensagem.substring(32,40));
            //inverte byte 5
  String inverter_e = mensagem.substring(32,40);
  char str_e[9];
  inverter_e.toCharArray(str_e, 9);
  int n_e=0, aux_e, fim_e, tam_e = inverter_e.length();
  // inverte o sinal para leitura
    fim_e = tam_e - 1; // índice do último caracter
    for(n_e = 0; n_e < tam_e/2; n_e++){
        aux_e = str_e[n_e];
        str_e[n_e] = str_e[fim_e];
        str_e[fim_e] = aux_e;
        fim_e--;
    }
    Serial.println(str_e);

            // Separa o byte 6 da mensagem
 // Serial.println(mensagem.substring(40,48));
            //inverte byte 6
  String inverter_f = mensagem.substring(40,48);
  char str_f[9];
  inverter_f.toCharArray(str_f, 9);
  int n_f =0, aux_f, fim_f, tam_f = inverter_f.length();
  // inverte o sinal para leitura
    fim_f = tam_f - 1; // índice do último caracter
    for(n_f = 0; n_f < tam_f/2; n_f++){
        aux_f = str_f[n_f];
        str_f[n_f] = str_f[fim_f];
        str_f[fim_f] = aux_f;
        fim_f--;
    }
    Serial.println(str_f);

             // Separa o byte 7 da mensagem
 // Serial.println(mensagem.substring(48,56));
            //inverte byte 7
  String inverter_g = mensagem.substring(48,56);
  char str_g[9];
  inverter_g.toCharArray(str_g, 9);
  int n_g =0, aux_g, fim_g, tam_g = inverter_g.length();
  // inverte o sinal para leitura
    fim_g = tam_g - 1; // índice do último caracter
    for(n_g = 0; n_g < tam_g/2; n_g++){
        aux_g = str_g[n_g];
        str_g[n_g] = str_g[fim_g];
        str_g[fim_g] = aux_g;
        fim_g--;
    }
    Serial.println(str_g);

       // Separa o byte 8 da mensagem
  //Serial.println(mensagem.substring(56,64));
            //inverte byte 8
  String inverter_h = mensagem.substring(56,64);
  char str_h[9];
  inverter_h.toCharArray(str_h, 9);
  int n_h =0, aux_h, fim_h, tam_h = inverter_h.length();
  // inverte o sinal para leitura
    fim_h = tam_h - 1; // índice do último caracter
    for(n_h = 0; n_h < tam_h/2; n_h++){
        aux_h = str_h[n_h];
        str_h[n_h] = str_h[fim_h];
        str_h[fim_h] = aux_h;
        fim_h--;
    }
    Serial.println(str_h);

   // Junta os bytes invertidos e forma a mensagem
   #define MAX 64
   char buffer[MAX];
    strcat(strcpy(buffer, str_a), str_b);
    strcat(strcpy(buffer, buffer), str_c);
    strcat(strcpy(buffer, buffer), str_d);
    strcat(strcpy(buffer, buffer), str_e);
    strcat(strcpy(buffer, buffer), str_f);
    strcat(strcpy(buffer, buffer), str_g);
    strcat(strcpy(buffer, buffer), str_h);
    
    String mensagem_final = buffer;
  // Serial.println(mensagem_final.length());
    Serial.println(mensagem_final);
// if(2 == 2){
   
     //for(int i=0; i<8; i++){
       String start  = String(startBit[0]);
       String tamanho  = String(lenght[0]);
       String offset  = String(offset[0]);
       String scale  = String(scale[0]);
       //String raw_s  = String(Raw_value_decimal[0]);
       
       int st = start.toInt();
       int ta = tamanho.toInt();
       int of = offset.toInt();
       int sc = scale.toInt();
      // int raw_i = raw.toInt();
       
       String sinal = mensagem_final.substring(st,st+ta);
       

       char str_i[5];
       sinal.toCharArray(str_i, 5);
       int n_i =0, aux_i, fim_i, tam_i = sinal.length();
       // inverte o sinal para leitura
       fim_i = tam_i - 1; // índice do último caracter
       for(n_i = 0; n_i < tam_i/2; n_i++){
         aux_i = str_i[n_i];
         str_i[n_i] = str_i[fim_i];
         str_i[fim_i] = aux_i;
         fim_i--;
       }
       
       String sinal_invertido =  str_i;
       int sinal_decimal = sinal_invertido.toInt();
       //int n_decimal = converte_para_decimal(sinal_decimal);
        int n_decimal = converte(sinal_decimal);
      // String raw_value = String(n_decimal + 1);
      //int raw_value_decimal = raw_value.toInt();
      int raw_value_decimal = n_decimal;
       int physical_value = of + sc * raw_value_decimal;
     //}
 
 Serial.println(sinal_decimal);
 Serial.println(physical_value);
 String raw_value_decimall = String(B0111,DEC);
 int k = raw_value_decimall.toInt();
 Serial.println(k);
 
  /*if((canMsg1.data[1] == 80) && (canMsg1.data[2] == 03)){ // Verifica se é permitido prosseguir com o start-up
    Serial.print("Conecte os 48V no motor");
    }*/
}



int converte(int binario){
  
   int dec = 0, i;
    for(i = 0; binario > 0; i++)
    {
        dec = dec + pow(2, i) * (binario % 10);
        binario = binario / 10;
    }
    
    return dec;
  
  }


int converte_para_decimal(int binario)
{
 
int decimal = 0;
int decimal_an = 0;
int cont =7; //9 depois estoura
double divisor = 1*(pow(10,cont));
int elevado = 0;
int razao = 0;

for(cont ;cont>=0; cont--){

razao = binario/divisor;

if(binario>=divisor){
    if(razao==1){
    elevado = pow(2,cont);
    decimal = decimal_an+elevado;
    decimal_an = decimal;
    }
    binario = binario-divisor;
}
divisor=divisor/10;
}

return decimal;
 
}
