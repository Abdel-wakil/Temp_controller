#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

int LED = 7;
String BT_msg;
String USB_msg;
SoftwareSerial BTSerial(10,11);//  RX--10 et TX--11
 
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("enter command : ");
  BTSerial.begin(9600);
  
  pinMode(LED,OUTPUT);
  sensors.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  
  delay(1000);
  BTSerial.println(tempC);
  
  
  
  
  while (BTSerial.available()){
    BT_msg = BTSerial.readString();
    Serial.println(BT_msg);

    }
  while (Serial.available()){
      USB_msg = Serial.readString();
      BTSerial.println(USB_msg);
    
     
  }
  if (BT_msg == "ON\r\n"){
    digitalWrite(LED,HIGH);
    }
  if (BT_msg == "OFF\r\n"){
    digitalWrite(LED,LOW);  
  }
      

    
}
