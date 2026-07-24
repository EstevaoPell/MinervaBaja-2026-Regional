//
int red = 3;

long redInterval = 200; 

void setup()
{
  pinMode(red,OUTPUT);
  Serial.begin(9600);
  //digitalWrite(red,LOW);
  
  
}

void loop(){

    //delay(6000);
    unsigned long currentMillis = millis();
   

    while((currentMillis) <= redInterval){
      digitalWrite(red,LOW);
      Serial.println(currentMillis);
      currentMillis = millis();
      Serial.print("O código está no loop");
      }
    Serial.print("O código não está no loop");
    digitalWrite(red,HIGH);
    /*delay(1000);
    digitalWrite(red,HIGH);*/
 
    
  }
