/* DS18B20 1-Wire digital temperature sensor with Arduino example code. More info: https://www.makerguides.com */


// Include the required Arduino libraries:
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

int PChauf = 6;
int cooling_water = 5;
int SV = 40;//consigne
float e; //l'erreur
float Kp_chauf=0.8,Kp_cool=20;//le gain
int delay1,delay2;


// Define to which pin of the Arduino the 1-Wire bus is connected:


// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

void System(String o){
  if (o=="ON"){
    digitalWrite(PChauf,HIGH);
    digitalWrite(cooling_water,LOW);  
  }
  if (o=="OFF"){
    digitalWrite(PChauf,LOW);
    digitalWrite(cooling_water,HIGH);
  }
}






void setup() {
  // Begin serial communication at a baud rate of 9600:
  pinMode(PChauf,OUTPUT);
  digitalWrite(PChauf,HIGH);
  
  pinMode(cooling_water,OUTPUT);
  digitalWrite(cooling_water,LOW);
  
  
  
  Serial.begin(9600);
  
  // Start up the library:
  sensors.begin();
}

void loop() {
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();

  // Fetch the temperature in degrees Celsius for device index:
  float tempC = sensors.getTempCByIndex(0); // the index 0 refers to the first device
  // Fetch the temperature in degrees Fahrenheit for device index:
  

  // Print the temperature in Celsius in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" , ");
  Serial.print(SV);
  //Serial.print("°C"); // shows degree symbol
  

  
   
  e=SV-tempC;

  
  
  delay1=e*Kp_chauf*1000;
  delay2=e*Kp_cool*1000;

  
  //Serial.print(" the error is ");
  //Serial.print(e);
  //Serial.print(" °C ");
  Serial.print(" delay1: "); // shows degree symbol
  Serial.print(delay1);
  Serial.print(" delay2: ");
  Serial.println(delay2);
  
  System("ON");
  if (tempC>=SV-0.3){
    if (delay1<0){
      delay(0);
    }
    else{
      delay(delay1);
    }
    System("OFF");
    if (delay2<0){
      delay(-delay2);
    }
    else{
      delay(delay2);
    }
  }
  
  else{
    delay(1000);
  }
   
  
}
