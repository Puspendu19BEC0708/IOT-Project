#include <SoftwareSerial.h>

SoftwareSerial SIM900(2, 3);




int Flame = 6;

void setup() {
  Serial.begin(9600);
  pinMode(Flame, INPUT_PULLUP);
 
}

void loop() {
  if(digitalRead(Flame) == 1)
   SIM900.print("AT+CMGF=1\r");// AT command to send SMS message
      Serial.print("AT+CMGF=1\r" );
      delay(100);
      SIM900.println("AT + CMGS = \"+919609022562\"");// recipient's mobile number, in international format
      Serial.print("AT + CMGS = \"+919609022562\"" );
  
      delay(100);
      SIM900.println("fire detected.");        // message to send
      Serial.print("fire  detected." );
      delay(100);
      SIM900.println((char)26);// End AT command with a ^Z, ASCII code 26
      Serial.print((char)26);
      delay(100);
      SIM900.println();
      delay(5000);                                     // give module time to send SMS
     
      //do {} while (1
  
  
}
