#include <iarduino_SensorPulse.h>

int val;
int LED = 13;

iarduino_SensorPulse Pulse(A0,1);      

void setup()
{
  Serial.begin(9600);
  Pulse.begin();   
}

void loop()
{ 
  if (Serial.available())
  {
    byte incomingByte = Serial.read();

    if (incomingByte == 1) digitalWrite(13, HIGH);
       //if (Pulse.check(ISP_VALID)==ISP_CONNECTED){
       // Serial.println(Pulse.check(ISP_PULSE));
       //} else {
       // Serial.println(-1);
       //}

       Serial.print("{ \"key\": 5 }\n");
       delay(10);
  }
}
