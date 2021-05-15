#include <SoftwareSerial.h>
int LED = 7;
String BT_msg;
String USB_msg;
SoftwareSerial BTSerial(10,11);//  RX--10 et TX--11
 



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("enter command : ");
  BTSerial.begin(9600);
  
  pinMode(LED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
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
