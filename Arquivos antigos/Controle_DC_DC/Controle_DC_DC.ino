int PinoSaida=11,PinoGiraPara=8,PinoInversor1=6,PinoInversor2=7,ComandoSaida=0,TensaoEntrada=0,TensaoSaida=0,CorrenteEntrada=0,CorrenteSaida=0,countloop=1,Luz=0,LedVerde=2,LedAmarelo=3,LedVermelho=4,nmed=10000,iprint,iCalibTensao;
float ComandoSaidaVolts=0.0,TensaoEntradaVolts=0.0,TensaoSaidaVolts=0.0,CorrenteEntradaVolts=0.0,CorrenteSaidaVolts=0.0,CorrenteEntradaAmps=0.0,CorrenteSaidaAmps=0.0,SetPoint,SetPointCorr=0.0,SetPointStartUp=5.0,Mult=0.0;
float elptime=0.0,elptimeo=0.0,told=0.0,dt=0.0,pi=3.1415926,R,fcorte=0.2,OffsetCorrEntrada=0.0,OffsetCorrSaida=0.0,TensaoBateriaVazio=0.0,CapacidadeCargaInicial=0.0,EnergiaArmazenada=0.0,CapacidadeCarga=0.0,PatamarBateria=6.3,EstadoCargaInicial=0.0;
float VariacaoEnergia=0.0,CorrenteSaidaAmpsfAnt=0.0,CapacidadeCarga100=9.0,EstadoCarga=0.0,DeltaVolts=0.0,Vref=0.0,RefTensaoSaida=0.0,OffsetTensaoSaida=0.0,CorrDescarga=0.0,SetPointCorr0=2.25;
float TensaoSaidaVoltsf=0.0,TensaoSaidaVoltsfold=0.0,CorrenteEntradaAmpsf=0.0,CorrenteSaidaAmpsf=0.0,CorrenteEntradaAmpsfold=0.0,CorrenteSaidaAmpsfold=0.0,TensaoEntradaVoltsf=0.0,TensaoEntradaVoltsfold=0.0,ComandoAcelf=0.0,ComandoAcelfold=0.0;
float ErroCorrente=0.0,ErroCorrenteold=0.0,ErroCorrenteInt=0.0,ComandoAcel=0.0,GanpCorr=5.0,GaniCorr=10.0;

void setup() 
{   
   pinMode(PinoInversor1,INPUT_PULLUP); // Recebe sinal externo (ground) para ligar e desligar o inversor no pino 6 - Bit 1
   pinMode(PinoInversor2,INPUT_PULLUP); // Recebe sinal externo (ground) para ligar e desligar o inversor no pino 7 - Bit 2
   pinMode(PinoGiraPara,OUTPUT); // Liga e desliga o inversor no pino digital 8
   pinMode(PinoSaida,OUTPUT); // Saida de tensão PWM no pino digital 11
   pinMode(A0,INPUT); // Medida de tensão na saida
   pinMode(A3,INPUT); // Medida de tensão na entrada
   pinMode(A4,INPUT); // Medida de corrente na entrada
   pinMode(A5,INPUT); // Medida de corrente na saida
   pinMode(LedVerde,OUTPUT); // Liga e desliga o led no pino digital 2
   pinMode(LedAmarelo,OUTPUT); // Liga e desliga o led no pino digital 3
   pinMode(LedVermelho,OUTPUT); // Liga e desliga o led no pino digital 4
  
   Serial.begin(9600);  
   digitalWrite(PinoGiraPara,HIGH); // Inicia com o inversor desligado
 
// Ofsset da corrente de saida

   while (countloop <= nmed) {
     TensaoSaida          = analogRead(A0); // Le o valor da tensão na saida da ponte DC pino A0
     CorrenteEntrada      = analogRead(A4); // Le o valor da corrente na entrada pino A4 
     CorrenteSaida        = analogRead(A5); // Le o valor da corrente na saida pino A5 
     TensaoSaidaVolts     = 15.844*(TensaoSaida*5.0/1023); // Converte a tensão de saida em Volts 
     TensaoBateriaVazio   = TensaoBateriaVazio + TensaoSaidaVolts ; // Acumula a corrente de saida para obter o valor medio
     CorrenteEntradaVolts = CorrenteEntrada*5.0/1023; // Converte a corrente de entrada em Volts
     OffsetCorrEntrada    = OffsetCorrEntrada+CorrenteEntradaVolts*1000/42; // Acumula a corrente de entrada para obter o valor medio
     CorrenteSaidaVolts   = CorrenteSaida*5.0/1023; // Converte a corrente na saida em Volts
     OffsetCorrSaida      = OffsetCorrSaida+CorrenteSaidaVolts*1000/42; // Acumula a corrente de saida para obter o valor medio
     countloop = countloop + 1;
   }   
   TensaoBateriaVazio     = TensaoBateriaVazio/nmed; 
   OffsetCorrEntrada      = OffsetCorrEntrada/nmed;
   OffsetCorrSaida        = OffsetCorrSaida/nmed;  

// Calibração da tensão de entrada

   iCalibTensao = 1;
   iprint = 1;
   if (iCalibTensao==1) {
      RefTensaoSaida      = 25.2; // Se desejar calibrar coloque aqui o valor da tensão inicial da bateria medido por um multimetro
      OffsetTensaoSaida   = TensaoBateriaVazio-RefTensaoSaida;
   } else {
      OffsetTensaoSaida   = 3.3;
   }
      
   TensaoBateriaVazio     = TensaoBateriaVazio-OffsetTensaoSaida;  
   Vref                   = TensaoBateriaVazio;
   CapacidadeCargaInicial = 3.9677*TensaoBateriaVazio-93.69; // Curva linear para a capacidade de carga em função da voltagem em vazio obtida do fabricante em Ah - 2 baterias de 12 V - 9Ah
   EnergiaArmazenada      = TensaoBateriaVazio*CapacidadeCargaInicial; // Energia armazenada inicial
   EstadoCargaInicial     = CapacidadeCargaInicial/CapacidadeCarga100*100;

   if (iprint==1) {
     Serial.print("OffsetTensaoSaida: ");
     Serial.print(OffsetTensaoSaida,1);
     Serial.print(" (V) - OffsetCorrSaida: ");
     Serial.print(OffsetCorrSaida,3);
     Serial.print(" (A) - OffsetCorrEntrada: ");
     Serial.print(OffsetCorrEntrada,3);
     Serial.print(" (A) - TensaoBateriaVazio: ");
     Serial.print(TensaoBateriaVazio,3);
     Serial.print(" (V) - CapacidadeCargaInicial: ");
     Serial.print(CapacidadeCargaInicial,3);
     Serial.print(" (Ah) - EnergiaArmazenadaInicial: ");
     Serial.print(EnergiaArmazenada,3); 
     Serial.print(" (Wh) - EstadoCargaInicial: ");
     Serial.print(EstadoCargaInicial,1); 
     Serial.println(" (%)");
   }
   
   elptimeo = micros()/1000000.0;
   told     = -0.00001; 
}

void loop()
{
// Controle do intervalo de tempo

   elptime = micros()/1000000.0-elptimeo;
   dt = elptime-told;
   told = elptime;

// Aplicação de filtro digital de primeira ordem
// Setup dos filtros

   R  = exp(-2*pi*(fcorte/(1/dt)));

// Liga o inversor

   if (digitalRead(PinoInversor1)==HIGH) {
      digitalWrite(PinoGiraPara,HIGH);
      Mult =0;
      DeltaVolts = 0.0;
   } else {
      digitalWrite(PinoGiraPara,LOW);
      Mult =1;
      DeltaVolts = 2.3;
   }
  
// Leitura dos sinais analógicos de entrada

   TensaoSaida     = analogRead(A0); // Le o valor da tensão na saida da ponte DC pino A0
   TensaoEntrada   = analogRead(A3); // Le o valor da tensão na entrada do DC-DC pino A3 
   CorrenteEntrada = analogRead(A4); // Le o valor da corrente na entrada pino A4 
   CorrenteSaida   = analogRead(A5); // Le o valor da corrente na saida pino A5 

// Conversão dos parâmetros para unidades de engenharia

   TensaoSaidaVolts     = 15.844*(TensaoSaida*5.0/1023)-OffsetTensaoSaida-DeltaVolts-0.23; // Converte a tensão de saida em Volts
   TensaoEntradaVolts   = 3.48*(TensaoEntrada*5.0/1023)/(7500.0/(7500.0+30000.0))-DeltaVolts; // Converte a tensão de entrada em Volts (Divisor R1 30000 - R2 7500 / Divisor (R1 20000 - R2 10000)
   CorrenteEntradaVolts = CorrenteEntrada*5.0/1023; // Converte a corrente de entrada em Volts
   CorrenteEntradaAmps  = CorrenteEntradaVolts*1000/42-OffsetCorrEntrada; // Converte a corrente de entrada em MiliVolts e aplica a sensibilidade do sensor para corrente em amperes que e de 38 mV/A e remove o offset
   CorrenteSaidaVolts   = CorrenteSaida*5.0/1023; // Converte a corrente de saida em Volts
   CorrenteSaidaAmps    = CorrenteSaidaVolts*1000/42-OffsetCorrSaida; // Converte a corrente de saida em MiliVolts e aplica a sensibilidade do sensor para corrente em amperes que e de 38.0 mV/A e remove o offset

// Lowpass fiter on signals

   TensaoEntradaVoltsf     = R*TensaoEntradaVoltsfold+TensaoEntradaVolts*(1-R);
   TensaoEntradaVoltsfold  = TensaoEntradaVoltsf;
   TensaoSaidaVoltsf       = R*TensaoSaidaVoltsfold+TensaoSaidaVolts*(1-R);
   TensaoSaidaVoltsfold    = TensaoSaidaVoltsf;
   CorrenteEntradaAmpsf    = R*CorrenteEntradaAmpsfold+CorrenteEntradaAmps*(1-R);
   CorrenteEntradaAmpsfold = CorrenteEntradaAmpsf;
   CorrenteSaidaAmpsf      = R*CorrenteSaidaAmpsfold+CorrenteSaidaAmps*(1-R);
   CorrenteSaidaAmpsfold   = CorrenteSaidaAmpsf;
   
// Target de corrente para carregamento da bateria
// Integração da energia armazenada

   VariacaoEnergia       = ((CorrenteSaidaAmpsf+CorrenteSaidaAmpsfAnt)*dt/2)/3600*Vref; // Converte de Ampere-seg para Ampere-hora e trasforma em Wh
   CorrenteSaidaAmpsfAnt = CorrenteSaidaAmpsf;
   EnergiaArmazenada     = EnergiaArmazenada+VariacaoEnergia;
   CapacidadeCarga       = EnergiaArmazenada/Vref; // Transforma a energia armazenada em capacidade de Carga (Ah)
   EstadoCarga           = CapacidadeCarga/CapacidadeCarga100*100;

// Leds indicadores de estado e mensagens de erro
   
   if(EstadoCarga>40 & EstadoCarga<71) {
      digitalWrite(LedVerde, HIGH);
      digitalWrite(LedAmarelo, LOW);
      digitalWrite(LedVermelho, LOW);
   } 
   if(EstadoCarga<=40 & EstadoCarga>25) {
      digitalWrite(LedVerde, LOW);
      digitalWrite(LedAmarelo, HIGH);
      digitalWrite(LedVermelho, LOW);
   } 
   if(EstadoCarga>=71) {
      digitalWrite(LedVerde, HIGH);
      digitalWrite(LedAmarelo, HIGH);
      digitalWrite(LedVermelho, LOW);
   } 
   if(EstadoCarga<=25) {
      digitalWrite(LedVerde, LOW);
      digitalWrite(LedAmarelo, LOW);
      digitalWrite(LedVermelho, HIGH);
   }
   if(CorrenteSaidaAmpsf<-2 & TensaoSaidaVoltsf<21.6) {
      digitalWrite(LedVerde, LOW);
      digitalWrite(LedAmarelo, LOW);
      digitalWrite(LedVermelho, HIGH);
   }
   if(TensaoEntradaVoltsf<27.0 || TensaoEntradaVoltsf>45.5) {
      digitalWrite(LedVerde, LOW);
      digitalWrite(LedAmarelo, HIGH);
      digitalWrite(LedVermelho, HIGH);
   }

// Calcula o setpoint para a corrente de saida
  
   if(CapacidadeCarga<PatamarBateria) { // Patamar da bateria e o valor maximo de capacidade de carga em que a maxima corrente de carga pode ser aplicada (Ah)
      SetPointCorr = SetPointCorr0;  // Região plana - 2 baterias de 12 V - 9Ah
   }
   else {
      SetPointCorr = 86.861*pow(2.7182818285,-0.58*CapacidadeCarga);  // Regiao exponencial - 2 baterias de 12 V - 9Ah
   }

// Não carrega a bateria se a capacidade de carga for maior que a do patamar da bateria e houver consumo de corrente da celula igual ao dobro do setpoint do patamar

   if (CorrenteEntradaAmpsf>2.0*SetPointCorr & CapacidadeCarga>0.95*PatamarBateria) {
     SetPointCorr = CorrDescarga;
   }

   if (digitalRead(PinoInversor2)==LOW) {
  
  // Controlador de corrente - Condição Startup

     if (Luz==0) {
       ErroCorrente    = 0.0;
       ErroCorrenteInt = 0.0;
       ErroCorrenteold = 0.0;
       Luz=1;   
     }
     ErroCorrente    = Mult*(SetPointStartUp-CorrenteEntradaAmpsf);
     ErroCorrenteInt = Mult*(ErroCorrenteInt+(ErroCorrenteold+ErroCorrente)*dt/2);
     ErroCorrenteold = ErroCorrente;
     SetPoint        = SetPointStartUp;   
   } else { 
  
  // Controlador de corrente - Condição Run 

     if (Luz==1) {
       ErroCorrente    = 0.0;
       ErroCorrenteInt = 0.0;
       ErroCorrenteold = 0.0;
       Luz=0;      
     }
     ErroCorrente    = Mult*(SetPointCorr-CorrenteSaidaAmpsf);
     ErroCorrenteInt = Mult*(ErroCorrenteInt+(ErroCorrenteold+ErroCorrente)*dt/2);
     ErroCorrenteold = ErroCorrente;
     SetPoint        = SetPointCorr;  
   }

// Sinal de comando para o acelerador
   
   ComandoAcel = Mult*(GanpCorr*ErroCorrente+GaniCorr*ErroCorrenteInt);
   
// Limitação do sinal de comando

   if (ComandoAcel<0) {
      ComandoAcel = 0;
   }
   if (ComandoAcel>100) {
      ComandoAcel = 100;
   }

// Conversão para PWM e limitação do sinal de comando na saida para ruido 
   
   ComandoSaida = 2.4449*ComandoAcel+12.547;
   if (ComandoAcel<0.0) {
      ComandoSaida = 0;
   }
   if (ComandoAcel>98) {
      ComandoSaida = 255;
   }

   analogWrite(PinoSaida,ComandoSaida); // Escreve o valor de saida no PinoSaida
   
   ComandoSaidaVolts = ComandoSaida*5.0/255; // Converte a tensão de saida em Volts

   if (elptime>=15) {
     if (iprint==1) {
       Serial.print(elptime-15,5);
       Serial.print(",");
     }
     Serial.print(ComandoAcel,2);
     Serial.print(",");
     Serial.print(TensaoEntradaVoltsf,2);
     Serial.print(",");
     Serial.print(TensaoSaidaVoltsf,2);
     Serial.print(",");
     if (iprint==1) {
       Serial.print(Vref,2);
       Serial.print(",");
     }
     Serial.print(SetPoint,3);
     Serial.print(",");
     Serial.print(CorrenteEntradaAmpsf,3);
     Serial.print(",");
     Serial.print(CorrenteSaidaAmpsf,3);
     Serial.print(",");
     Serial.print(CapacidadeCarga,4);
     Serial.print(",");
     if (iprint==1) {
       Serial.print(EnergiaArmazenada,3);
       Serial.print(",");
       Serial.print(EstadoCarga,3);
     }
//     Serial.print(",");
//     Serial.print(ErroCorrente,3);
//     Serial.print(",");
//     Serial.println(ErroCorrenteInt,3);
     Serial.println();
   }
}
