//multiplexor variables******************************//

int choose_chan[4] = {3,4,5,6};
int right_comb[4];
char t_or_f;
int SIG = 7,x,channel;
int multiplex_table [16][4]{
//   3   4   5   6
    {0,  0,  0,  0}, // 0
    {1,  0,  0,  0}, // 1
    {0,  1,  0,  0}, // 2
    {1,  1,  0,  0}, // 3
    {0,  0,  1,  0}, // 4
    {1,  0,  1,  0}, // 5
    {0,  1,  1,  0}, // 6
    {1,  1,  1,  0}, // 7
    {0,  0,  0,  1}, // 8
    {1,  0,  0,  1}, // 9
    {0,  1,  0,  1}, // 10
    {1,  1,  0,  1}, // 11
    {0,  0,  1,  1}, // 12
    {1,  0,  1,  1}, // 13
    {0,  1,  1,  1}, // 14
    {1,  1,  1,  1}  // 15
};

//*******************************************//
//7 segemnt display variables
int A=0;
int B=1;
int C=2;
int D=3;
int E=4;
int F=5;
int G=6;
int DP=7;
int D1=8;
int D2=9;
int D3=10;
int D4=11;
int one_num;
float tempC=26.52;
int tempC_int;
int tempC_D1;
int tempC_D2;
int tempC_D3;
int tempC_D4;
int time_of_dis;
float temp_to_disp;

//***************************************//

//multiplex function
void multiplex(int channel){ 
  for (int i=0; i<4; i++){
    right_comb[i] = multiplex_table[channel][i];
    //Serial.println(right_comb[i]);
    if (right_comb[i]==0){
      t_or_f=LOW;
    }
    else{
      t_or_f=HIGH;
    }
    digitalWrite(choose_chan[i],t_or_f);    
  }
  digitalWrite(SIG,HIGH);  
}

//*****************************************************//
//7 segement dispay functions

void Single_digit(int one_num){
  if (one_num==0){
    multiplex(A);
    multiplex(B);
    multiplex(C);
    multiplex(D);
    multiplex(E);
    multiplex(F);
    }
  if (one_num==1) {
    multiplex(B);
    multiplex(C);    
  }
  if (one_num==2) {
    multiplex(A);
    multiplex(B);
    multiplex(G);
    multiplex(D);
    multiplex(E);    
  }
  if (one_num==3) {
    multiplex(A);
    multiplex(B);
    multiplex(C);
    multiplex(D);
    multiplex(G);    
  }
  if (one_num==4) {
    multiplex(B);
    multiplex(C);
    multiplex(G);
    multiplex(F);   
  }
  if (one_num==5) {
    multiplex(A);
    multiplex(G);
    multiplex(C);
    multiplex(D);
    multiplex(F);   
  }
  if (one_num==6) {
    multiplex(A);
    multiplex(G);
    multiplex(C);
    multiplex(D);
    multiplex(E);
    multiplex(F);
  }
  if (one_num==7) {
    multiplex(A);
    multiplex(B);
    multiplex(C);
  }
  if (one_num==8) {
    multiplex(A);
    multiplex(B);
    multiplex(C);
    multiplex(D);
    multiplex(E);
    multiplex(F);
    multiplex(G);
  }
  if (one_num==9) {
    multiplex(A);
    multiplex(B);
    multiplex(C);
    multiplex(D);
    multiplex(G);
    multiplex(F);
  }    
}

void cleaar() {
  digitalWrite(A,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  digitalWrite(E,LOW);
  digitalWrite(F,LOW);
  digitalWrite(G,LOW);
  digitalWrite(DP,LOW);
  
}





void display_full(float tempC){
  time_of_dis=1;
  while (time_of_dis<500) {
    digitalWrite(D1,LOW);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,HIGH);
    digitalWrite(D4,HIGH);
    
    Single_digit(tempC_D1);
    delay(1);
    cleaar();
  
    digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
    digitalWrite(D3,HIGH);
    digitalWrite(D4,HIGH);
    digitalWrite(DP,HIGH);
    
    Single_digit(tempC_D2);
    delay(1);
    cleaar();
    
    digitalWrite(D1,HIGH);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,LOW);
    digitalWrite(D4,HIGH);
   
    Single_digit(tempC_D3);
    delay(1);
    cleaar();
    
    digitalWrite(D1,HIGH);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,HIGH);
    digitalWrite(D4,LOW);
    Single_digit(tempC_D4);    
    delay(1);
    cleaar();
    
    time_of_dis+=1;    
  }
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int u=0; u<4; u++){
    pinMode(choose_chan[u],OUTPUT);
  }
  pinMode(SIG,OUTPUT);



  
}

void loop() {
  // put your main code here, to run repeatedly:
  tempC_int=tempC;
  tempC_D1=tempC_int/10;
  tempC_D2=tempC_int-(tempC_D1*10);
  tempC_D3=(tempC*10)-(tempC_int*10);
  tempC_D4=(tempC*100)-(((tempC_int*10)+tempC_D3)*10);
  
  //display_full(tempC);
  Serial.print("tempC_D1: ");
  Serial.print(tempC_D1);
  Serial.print(" tempC_D2: ");
  Serial.print(tempC_D2);
  Serial.print(" tempC_D3: ");
  Serial.print(tempC_D3);
  Serial.print(" tempC_D4: ");
  Serial.println(tempC_D4);
  
  multiplex(8);
  Single_digit(2);
  delay(1000);









  
}
