// Include the required Arduino libraries:
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define ONE_WIRE_BUS 2

int PChauf = 6,one_time;
int cooling_water = 5;
int SV=40;//consigne
int new_SV;
float e_now,e_before=0; //l'erreur

float Kp_chauf=6.50,Kp_cool=0.4;//le gain propor
float Kd_chauf=12.00,Kd_cool=9.00;//le gain derivée
float Ki_chauf=1.2;
float delay1_total,delay1_prop,delay1_deriv,delay1_integral_now,delay1_integral=0,delay2_total,delay2_prop,delay2_deriv;

float tempC,off_set=0;
String password,SV_string,code,z="True",Kp_chauf_string,Kp_cool_string,Kd_chauf_string,Kd_cool_string,Ki_chauf_string,off_set_string;

unsigned long time_now,time_before;
double duration;

// Define to which pin of the Arduino the 1-Wire bus is connected:


// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);


SoftwareSerial BTSerial(10,11);//  RX--10 et TX--11


// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);


LiquidCrystal_I2C lcd(0x27,16,2);
/////////////////functions///////////////
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
//***********************//
void lcd_display(float x){
  
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(4,1);
  lcd.print(x);
  lcd.print("\337C");
}
//**********************//
/*void Fix_temp_here(){
  if (e_now<=e_before){
    System("OFF");
    delay(2000);
  }

  if (e_now>e_before){
    System("ON"); 
    delay(2000);   
  }  
}*/
//**********************//
void check_for_commands(){
  while (BTSerial.available()){
    password=BTSerial.readStringUntil('\n');
    //BTSerial.println(password);
    z="True";
    if (password=="*0000*"){
      //BTSerial.println("yo password checked in"); 
      lcd.clear();    
      while (z=="True"){       
        lcd.setCursor(0,0);
        lcd.print("Mode confi active");
        lcd.setCursor(2,1);
        lcd.print("Entrer code:");
        if (BTSerial.available()){
          code=BTSerial.readStringUntil('\n');
          if (code=="*0"){
            lcd.clear();
            while (z=="True"){
              lcd.setCursor(3,0);
              lcd.print("Entrer la");
              lcd.setCursor(0,1);
              lcd.print("nouvelle consigne:");  
              if (BTSerial.available()){
                SV_string=BTSerial.readStringUntil('\n');
                new_SV=SV_string.toFloat();
                lcd.clear();
                while (z=="True"){
                  lcd.setCursor(0,0);
                  lcd.print("Nouvelle consign");
                  lcd.setCursor(0,1);
                  lcd.print("est:");
                  lcd.setCursor(6,1);
                  lcd.print(new_SV);
                  lcd.print("\337C");
                  SV=new_SV;
                  z="False";
                  delay(3000);
                  lcd.clear();
                }
              }   
            }       
          }
          else if (code=="*1") {
            lcd.clear();
            while (z=="True"){
              lcd.setCursor(0,0);
              lcd.print("Kp_chauf=");
              lcd.print(Kp_chauf);
              lcd.setCursor(0,1);
              lcd.print("Entrer Kp_chauf");
              if (BTSerial.available()){
                Kp_chauf_string=BTSerial.readStringUntil('\n');
                Kp_chauf=Kp_chauf_string.toFloat();
                lcd.clear();
                while (z=="True"){
                  lcd.setCursor(0,0);
                  lcd.print("Nouveau Kp_chauf");
                  lcd.setCursor(0,1);
                  lcd.print("est:");
                  lcd.setCursor(6,1);
                  lcd.print(Kp_chauf);
                  z="False";
                  delay(3000);
                  lcd.clear();
                }
              } 
            } 
          }
          else if (code=="*2"){
            lcd.clear();
            while (z=="True"){
              lcd.setCursor(0,0);
              lcd.print("Kp_cool=");
              lcd.print(Kp_cool);
              lcd.setCursor(0,1);
              lcd.print("Entrer Kp_cool");
              if (BTSerial.available()){
                Kp_cool_string=BTSerial.readStringUntil('\n');
                Kp_cool=Kp_cool_string.toFloat();
                lcd.clear();
                while (z=="True"){
                  lcd.setCursor(0,0);
                  lcd.print("Nouveau Kp_cool");
                  lcd.setCursor(0,1);
                  lcd.print("est:");
                  lcd.setCursor(6,1);
                  lcd.print(Kp_cool);
                  z="False";
                  delay(3000);
                  lcd.clear();
                }
              } 
            }
          }
          else if (code=="*3"){
          lcd.clear();
            while (z=="True"){
              lcd.setCursor(0,0);
              lcd.print("Kd_chauf=");
              lcd.print(Kd_chauf);
              lcd.setCursor(0,1);
              lcd.print("Entrer Kd_chauf");
              if (BTSerial.available()){
                Kd_chauf_string=BTSerial.readStringUntil('\n');
                Kd_chauf=Kd_chauf_string.toFloat();
                lcd.clear();
                while (z=="True"){
                  lcd.setCursor(0,0);
                  lcd.print("Nouveau Kd_chauf");
                  lcd.setCursor(0,1);
                  lcd.print("est:");
                  lcd.setCursor(6,1);
                  lcd.print(Kd_chauf);
                  z="False";
                  delay(3000);
                  lcd.clear();
                }
              } 
            }
          }
          else if (code=="*4"){
          lcd.clear();
            while (z=="True"){
              lcd.setCursor(0,0);
              lcd.print("Kd_cool=");
              lcd.print(Kd_cool);
              lcd.setCursor(0,1);
              lcd.print("Entrer Kd_cool");
              if (BTSerial.available()){
                Kd_cool_string=BTSerial.readStringUntil('\n');
                Kd_cool=Kd_cool_string.toFloat();
                lcd.clear();
                while (z=="True"){
                  lcd.setCursor(0,0);
                  lcd.print("Nouveau Kd_cool");
                  lcd.setCursor(0,1);
                  lcd.print("est:");
                  lcd.setCursor(6,1);
                  lcd.print(Kd_cool);
                  z="False";
                  delay(3000);
                  lcd.clear();
                }
              } 
            }
          }
          else if (code=="*5"){
          lcd.clear();
            while (z=="True"){
              lcd.setCursor(0,0);
              lcd.print("Ki_chauf=");
              lcd.print(Ki_chauf);
              lcd.setCursor(0,1);
              lcd.print("Entrer Ki_chauf");
              if (BTSerial.available()){
                Ki_chauf_string=BTSerial.readStringUntil('\n');
                Ki_chauf=Ki_chauf_string.toFloat();
                lcd.clear();
                while (z=="True"){
                  lcd.setCursor(0,0);
                  lcd.print("Nouveau Ki_chauf");
                  lcd.setCursor(0,1);
                  lcd.print("est:");
                  lcd.setCursor(6,1);
                  lcd.print(Ki_chauf);
                  z="False";
                  delay(3000);
                  lcd.clear();
                }
              } 
            }
          }
          else if (code=="*6"){
          lcd.clear();
            while (z=="True"){
              lcd.setCursor(0,0);
              lcd.print("Calibrer capteur");          
              lcd.setCursor(2,1);
              lcd.print("off_set=");
              lcd.print(off_set);
              if (BTSerial.available()){
                off_set_string=BTSerial.readStringUntil('\n');
                off_set=off_set_string.toFloat();
                lcd.clear();
                while (z=="True"){
                  lcd.setCursor(0,0);
                  lcd.print("Calibrer capteur");
                  lcd.setCursor(2,1);
                  lcd.print("off_set=");           
                  lcd.print(off_set);
                  z="False";
                  delay(3000);
                  lcd.clear();
                }
              } 
            }
          }    
            
          


          
           
        }
      }   
    }
  } 
}
//*********************************//
void SV_start(){
  z="True";
  one_time=0;
  while (z=="True"){
    lcd.setCursor(1,0);
    lcd.print("Enter consigne");
    if (BTSerial.available()){
      lcd.clear();
      SV_string=BTSerial.readStringUntil('\n');
      SV=SV_string.toInt();
      while (z=="True"){
        lcd.setCursor(0,0);
        lcd.print("La consigne est:");
        lcd.setCursor(6,1);
        lcd.print(SV);
        lcd.print("\337C");
        z="False";
        delay(3000);
        lcd.clear();
        one_time+=1;
      }
    }
  }  
}

///////////////END functions////////////////




void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  
  lcd.init(); 
  lcd.backlight();
 
  BTSerial.begin(9600);
  
  pinMode(PChauf,OUTPUT);
  digitalWrite(PChauf,HIGH);
  
  pinMode(cooling_water,OUTPUT);
  digitalWrite(cooling_water,LOW);
  
  sensors.begin();       // Start up the library DS18B20  
}




void loop() {
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();

  // Fetch the temperature in degrees Celsius for device index:
  float tempC_brut = sensors.getTempCByIndex(0); // the index 0 refers to the first device
  // Fetch the temperature in degrees Fahrenheit for device index:
  tempC=tempC_brut+off_set;
  /*while (tempC==-127.00){
    sensors.requestTemperatures();
    tempC = sensors.getTempCByIndex(0);
  }*/

  
 /* if (one_time==0){
    SV_start();  
  }*/
  

  // Print the temperature in Celsius in the Serial Monitor:
  BTSerial.print("Temperature: ");
  BTSerial.print(tempC);
  BTSerial.print(" , ");
  BTSerial.println(SV);
  e_now=SV-tempC;

  time_now=micros();
  
  
  lcd_display(tempC);

  check_for_commands();
  
/////////////////Calculation bloc////////////   
  delay1_prop=(e_now*Kp_chauf)*500.00;
  delay1_deriv=(Kd_chauf*(e_now-e_before))*500;
  
  duration=(time_now-time_before)/1000000;
  delay1_integral_now=Ki_chauf*(e_now*duration);
  delay1_integral=delay1_integral_now+delay1_integral;

  
  delay1_total=(delay1_prop+delay1_deriv+delay1_integral);
  /*BTSerial.print(" duration is: ");
  BTSerial.print(duration);
  BTSerial.print(" delay1_prop is: ");
  BTSerial.print(delay1_prop);
  BTSerial.print(" delay1_deriv is: ");
  BTSerial.print(delay1_deriv);
  BTSerial.print(" delay1_int is: ");
  BTSerial.print(delay1_integral);
  BTSerial.print(" delay1_total is: ");
  BTSerial.println(delay1_total);*/
  
  delay2_prop=e_now*Kp_cool*500; 
  delay2_deriv=Kd_cool*(e_before-e_now)*500; 
  
  /*if (delay2_prop<0){
    delay2_prop=-delay2_prop;
  }
  else {
    delay2_prop=delay2_prop;
  }*/
  
  delay2_total=(delay2_prop+delay2_deriv);

  /*BTSerial.print(" the delay1_tot is: ");
  BTSerial.print(delay1_total);
  BTSerial.print(" past delay2_yoy is: ");
  BTSerial.println(delay2_total);*/
  

///////////////regulation bloc///////////////
  System("ON");
  if (tempC>=SV-2.5){
    if (delay1_total<0){
      delay(0);
    }
    else{
      delay(delay1_total);
    }
    System("OFF");
    if (delay2_total<0){
      delay(0);
    }
    else{
      delay(delay2_total);
    }
  }
  
  else{
    delay(1000);
  }
 
  
  e_before=e_now;
  time_before=time_now;
    
}
