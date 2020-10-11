/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
int ldr=A0;
int val=0;
#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8);



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  SIM900.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
   val = analogRead(ldr);
  // print out the value you read:
  if(val==975){
    SIM900.print("AT+CMGF=1\r");// AT command to send SMS message
      Serial.print("AT+CMGF=1\r" );
      delay(100);
      SIM900.println("AT + CMGS = \"+919609022562\"");// recipient's mobile number, in international format
      Serial.print("AT + CMGS = \"+919609022562\"" );
  
      delay(100);
      SIM900.println("two train on the same track.");        // message to send
      Serial.print("two trains are on same track  ." );
      delay(100);
      SIM900.println((char)26);// End AT command with a ^Z, ASCII code 26
      Serial.print((char)26);
      delay(100);
      SIM900.println();
      delay(5000);                                     // give module time to send SMS
     
      //do {} while (1);
      
     
    
    
    }
  //Serial.println(val);
  //delay(1);        // delay in between reads for stability
}
