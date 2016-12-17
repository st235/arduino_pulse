#include <iarduino_SensorPulse.h>
#include <SoftwareSerial.h>

int val;
int LED = 13;

iarduino_SensorPulse Pulse(A0,1);      
SoftwareSerial BTserial(2, 3); // RX | TX

void setup()
{
  BTserial.begin(9600);
  BTserial.write("AT+NAMEHealthKit(ProtoV0.1)");
  
  Pulse.begin();   
}

void loop()
{ 
  if (BTserial.available())
  {
    byte incomingByte = BTserial.read();

    if (incomingByte == 1) digitalWrite(13, HIGH);
       //if (Pulse.check(ISP_VALID)==ISP_CONNECTED){
       // Serial.println(Pulse.check(ISP_PULSE));
       //} else {
       // Serial.println(-1);
       //}

       BTserial.print("{ \"key\": 5 }\n");
       delay(10);
  }
}
