int Flame = 2; // connect ir sensor to arduino pin 2
#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);
TinyGPS gps;




void setup() 
{



  pinMode (Flame, INPUT); // sensor pin INPUT
  
}

void loop()
{
  //int statusSensor = digitalRead (IRSensor);
  
  if (digitalRead(Flame) == 1){
      
     bool newData = false;
     unsigned long chars;
     unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }

  if (newData)      //If newData is true
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);   
    SIM900.print("AT+CMGF=1\r"); 
    delay(400);
    SIM900.println("AT + CMGS = \"+91xxxxxxxxxx\"");// recipient's mobile number with country code
    delay(300);
    SIM900.print("Latitude = ");
    SIM900.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    SIM900.print(" Longitude = ");
    SIM900.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(200);
    SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    SIM900.println();
    

  }
 
  Serial.println(failed);
 // if (chars == 0)
   // Serial.println("** No characters received from GPS: check wiring **");
    
    
    
    
    
 
}
    
  }
  
  
  
