


const int echoPin = 2; // Echo Pin of Ultrasonic Sensor
const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);

TinyGPS gps; 


                    
void setup() 
{
  Serial.begin(9600); // Starting Serial Communication
   SIM900.begin(9600);
  pinMode(pingPin, OUTPUT); // initialising pin 3 as output
  pinMode(echoPin, INPUT); // initialising pin 2 as input
}

void loop()
{
  long duration, inches, cm;
  
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(pingPin, LOW);

  
  duration = pulseIn(echoPin, HIGH); // using pulsin function to determine total time
  
  cm = microsecondsToCentimeters(duration); // calling method
  
 
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
  if(cm==313)
  {
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

long microsecondsToInches(long microseconds) // method to covert microsec to inches 
{
 return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) // method to covert microsec to centimeters
{
   return microseconds / 29 / 2;
}
