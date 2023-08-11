#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial mySerial(11,10); // RX, TX
unsigned char data[4]={};
float distance,d,tempc;
float x, y, z;
int r,g,b;
    #define S0 4
    #define S1 5
    #define S2 6
    #define S3 7
    #define sensorOut 8
    int frequency = 0;
void setup()
{
        pinMode(S0, OUTPUT);
      pinMode(S1, OUTPUT);
      pinMode(S2, OUTPUT);
      pinMode(S3, OUTPUT);
      pinMode(sensorOut, INPUT);
      
      // Setting frequency-scaling to 20%
      digitalWrite(S0,HIGH);
      digitalWrite(S1,LOW);

 Serial.begin(9600);
 mySerial.begin(9600); 
 sensors.begin();
 sensors.requestTemperatures();

}

void loop()
{
   // Setting red filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      //Remaping the value of the frequency to the RGB Model of 0 to 255
      frequency = map(frequency, 25,72,255,0);
      // Printing the value on the serial monitor
      r = frequency;
      delay(100);
      // Setting Green filtered photodiodes to be read
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      //Remaping the value of the frequency to the RGB Model of 0 to 255
      frequency = map(frequency, 30,90,255,0);
      // Printing the value on the serial monitor
      g = frequency;
      delay(100);
      // Setting Blue filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      //Remaping the value of the frequency to the RGB Model of 0 to 255
      frequency = map(frequency, 25,70,255,0);
      // Printing the value on the serial monitor
      b = frequency;
      delay(100);
  x = analogRead(1) / 330.000;       
  y = analogRead(2) / 330.000;       
  z = analogRead(3) / 330.000;
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);
  tempc = sensors.getTempCByIndex(0);
  mySerial.flush();
  if(x>1.0)
  {
  if(data[0]==0xff)
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
        if(distance>30)
          {
            if((r>=255&g>=255&b>=255)|(r<-1000&g<-1000&b<-1000))
            {
              Serial.print("Colour less - Water");
              Serial.print(" ");
              }
            else{
              Serial.print("This is not water");
              Serial.print(" ");
            }
           //Serial.print(distance/10);
           d = (distance/10)*(331.3+0.606*tempc)/343;
           //Serial.print(" ");
           if(d>=9.0){
            Serial.println("The container is empty");
           }
           else if(d<=3.0){
            Serial.println("The level is: 400ml");
           }
           else if(d<=3.2){
            Serial.println("The level is: 390ml");
           }
           else if(d<=3.7){
            Serial.println("The level is: 350ml");
           }
           else if(d<=3.9){
            Serial.println("The level is: 300ml");
           }
           else if(d<=4.1){
            Serial.println("The level is: 270ml");
           }
                      else if(d<=4.3){
            Serial.println("The level is: 250ml");
           }
                      else if(d<=5){
            Serial.println("The level is: 200ml");
                      }
                       else if(d<=5.5){
            Serial.println("The level is: 150ml");
                       }
                       else if(d<=6){
            Serial.println("The level is: 100ml");
                       }
                       else if(d<=7){
            Serial.println("The level is: 50ml");
                       }
                       else if(d<=9){
            Serial.println("Time to Refill");
                       }
           }
          }
      }
     }
    else{
    Serial.println("The Bottle is inclined");
  
  }
  delay(100);
}