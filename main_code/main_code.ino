#include <ArduinoJson.h>
#include <iarduino_SensorPulse.h>
#include <SoftwareSerial.h>

iarduino_SensorPulse Pulse(A0,1);      
SoftwareSerial BTserial(2, 3); // RX(TXD) | TX(RXD)

String stringBuffer;
char* secret = "5fd7979573adacd6a75f82681e27d8b7\0";

void setup()
{ 
  Serial.begin(4800);
  BTserial.begin(9600);
  BTserial.write("AT+NAMEHealthKit(ProtoV0.1)"); 
  Pulse.begin(); 
}

void loop()
{ 
  if (BTserial.available()) {
    stringBuffer = "";
    
    while (BTserial.available()) {
      delay(10);
      stringBuffer += (char) BTserial.read();
    } 

    Serial.println(stringBuffer);
    authorize(stringBuffer);
  }  
  
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    
    int state = Pulse.check(ISP_VALID);
    root["state"] = state;
    
    if (state == ISP_CONNECTED) {
      root["pulse"] = Pulse.check(ISP_PULSE);
    }

    root.printTo(BTserial);
    BTserial.print("\r\n");
    
   // root["sensor"] = "gps";
   // root["time"] = 1351824120;
   //root.prettyPrintTo(Serial);
    //root.printTo(BTserial);
    
      //byte incomingByte = BTserial.read();
      //if (incomingByte == 1) digitalWrite(13, HIGH);
  
      
         //if (Pulse.check(ISP_VALID)==ISP_CONNECTED){
         // Serial.println(Pulse.check(ISP_PULSE));
         //} else {
         // Serial.println(-1);
         //}
  
     //    BTserial.print("{ \"key\": 5 }\n");
  delay(50);
}

void authorize(String raw) {
  StaticJsonBuffer<200> jsonInput;
  JsonObject& input = jsonInput.parseObject(raw);
  input.printTo(Serial);
  
  StaticJsonBuffer<200> jsonOutput;
  JsonObject& output = jsonOutput.createObject();

  output["success"]= true;
  output["response"] = isTokenConfirmed(input["executed"]);
  output.printTo(BTserial);
  BTserial.println();
}

bool isTokenConfirmed(String token) {
  return true;
}

