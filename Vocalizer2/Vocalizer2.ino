#include<SoftwareSerial.h>

SoftwareSerial mySerial(3,2);

const int flex1 = A0;
const int flex2 = A1;

const int xpin = A2;                  // x-axis of the accelerometer
const int ypin = A3;                  // y-axis
const int zpin = A4; 

int button = 10;
int motor = 11;

int intro = 0;
int sorry = 0;
int thankyou = 0;
int beauty = 0;
int one = 0;
int lastintro = 0;
int lastsorry = 0;
int lastthankyou = 0;
int lastbeauty = 0;
int lastone = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
  pinMode(button, INPUT);
  digitalWrite(13,LOW);
  digitalWrite(motor,LOW);
  delay(5000);
  digitalWrite(13,HIGH);
}

void loop() {
  
  int flex1val = analogRead(flex1);
  int flex2val = analogRead(flex2);
  int xaxisval = analogRead(xpin);
  int yaxisval = analogRead(ypin);
  int zaxisval = analogRead(zpin);

//  Serial.print(flex1val);
//  Serial.print("\t");
//  
//  Serial.print(flex2val);
//  Serial.print("\t");
//  
//  Serial.print(xaxisval);
//  Serial.print("\t");
//  
//  Serial.print(yaxisval);
//  Serial.print("\t");
//  
//  Serial.print(zaxisval);
//  Serial.println();
  
  int val1 = map(flex1val, 500, 580, 0, 9);
  int val2 = map(flex2val, 700, 780, 0, 9);
  int val3 = map(xaxisval, 295, 340, 0, 9);
  int val4 = map(yaxisval, 270, 420, 0, 9);
  int val5 = map(zaxisval, 285, 360, 0, 9);

  Serial.print(val1);
  Serial.print(" ");
  
  Serial.print(val2);
  Serial.print(" ");
  
  Serial.print(val3);
  Serial.print(" ");
  
  Serial.print(val4);
  Serial.print(" ");
  
  Serial.print(val5);
  Serial.println();

  if(val1<=2 && val2<=3 && val3>=8 && val5>5){
    //Serial.println("Introduction");
    intro = 1;
    //mySerial.println("Hi my name is Arduino I am speaking through bluetooth");
  }else if(val1<=2 && val2>=8 && val3>=8 && val5>5){
    //Serial.println("Fine/Sorry");
    sorry=1;
    //mySerial.println("I am sorry");
  }else if(val1<=2 && val2<=3 && val3>=8 && val5<=5){
    //Serial.println("Thank you very much");
    thankyou = 1;
    //mySerial.println("Thank you very much");
  }else if(val1>=2 && val2>=7 && val3>=8 && val5<=5 ){
    //Serial.println("Beautiful");
    beauty = 1;
    //mySerial.println("Beautiful");
  }else if(val1>=5 && val2<=4 && val3>=8 && val5<=5 ){
     one = 1;
  }


  if (intro != lastintro) {
    if (intro == 1) {
      mySerial.println("Hi my name is MURALI");
      sorry = 0;
      thankyou = 0;
      beauty = 0;
      one = 0;
    } 
  }
  lastintro = intro;

  if (sorry != lastsorry) {
    if (sorry == 1) {
      mySerial.println("I am sorry");
      intro = 0;
      thankyou = 0;
      beauty = 0;
      one = 0;
    } 
  }
  lastsorry = sorry;

  if (thankyou != lastthankyou) {
    if (thankyou == 1) {
      mySerial.println("Thank you very much");
      intro = 0;
      sorry = 0;
      beauty = 0;
      one = 0;
    } 
  }
  lastthankyou = thankyou;

  if (beauty != lastbeauty) {
    if (beauty == 1) {
      mySerial.println("I am Fine");
      intro = 0;
      sorry = 0;
      thankyou = 0;
      one = 0;
    } 
  }
  lastbeauty = beauty;

  if (one != lastone) {
    if (one == 1) {
      mySerial.println("One moment please");
      intro = 0;
      sorry = 0;
      thankyou = 0;
      beauty = 0;
    } 
  }
  lastone = one;
  
  if(digitalRead(button)==HIGH || digitalRead(button)==1){
    digitalWrite(12,LOW);
    delay(500);
    digitalWrite(12,HIGH);
    digitalWrite(motor,HIGH);
    delay(500);
    digitalWrite(motor, LOW);
  }

  if(mySerial.available()){
    while(mySerial.available()){ 
      char c = mySerial.read();
      Serial.print(c);  
    }
    Serial.println();
  }
  // delay before next reading:
  delay(500);
}
