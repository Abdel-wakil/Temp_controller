
float temp;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  /*pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);*/

}

void loop() {
  // put your main code here, to run repeatedly:
  temp = analogRead(A0);
  temp = temp * 0.48828125;
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  delay(1000);
  /*if (temp>=25) {
    digitalWrite(13,HIGH);
    delay(200);
    digitalWrite(13,LOW);
    delay(200);
  } else {
    digitalWrite(8,HIGH);
    delay(200);
    digitalWrite(8,LOW);
    delay(200);
  }*/




  

}
