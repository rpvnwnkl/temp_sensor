//   Temp Sensor
//   Richard Hawthorn
//   Cambridge Hackspace
//   2015-11-21
//
//   7 segment led pixels
//
//    _____         __A__
//   |     |       F     B
//   |_____|  -->  |--G--|
//   |     |       E     C
//   |_____|       |__D__|
//
//   Characters
//    _____     _____     _____     _____ 
//   |     |   |     | . |     | o |     |
//   |_____|   |_____|   |_____|   |_____|
//   |     |   |     | . |     |   |     |
//   |_____| o |_____| o |_____| o |_____| o
//      1         2         3         4
//

//how long to pause between drawing each character
int displayPause = 1;

//define Pins
int segmentD = 5;
int segmentE = 6;
int segmentF = 7;
int segmentA = 2;
int segmentB = 3;
int segmentC = 4;
int segmentG = 8;
int digitOne = 10;
int digitTwo = 11;
int digitThree = 12;
int digitFour = 13;
int selectButton = A0;
int degs = A1;
int decimal = A2;

//current temperature
int temp = 0;

//temperature units
char unit = 'f';

//counter for re-checking the temperature
long count = 0;

//how frequently should we re-check the temperature, in minutes
int minutes = 1;

//setup the one wire sensor
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//setup
void setup() {

  //pin modes
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(digitOne, OUTPUT);
  pinMode(digitTwo, OUTPUT);
  pinMode(digitThree, OUTPUT);
  pinMode(digitFour, OUTPUT);
  pinMode(decimal, OUTPUT);
  pinMode(degs, OUTPUT);

  //turn off the degrees symbol on boot
  digitalWrite(degs,HIGH);
  
  //buttons (with pullups)
  pinMode(selectButton, INPUT_PULLUP);
  
  //setup serial line for debugging
  Serial.begin(9600);
  Serial.println("Temperature Sensor Starting...");

  //start the temp sensor
  sensors.begin();
  
}


//get the current temperature
void getTemp(){

  if (count == 0){
    
    count = (minutes * 13000);
    resetNumbers();
    sensors.requestTemperatures();

    if (unit == 'c'){
      temp = sensors.getTempCByIndex(0) * 100;  
    } else {
      temp = sensors.getTempFByIndex(0) * 100;  
    }
    
  } else {
    count--;
  }
 
}



//check the buttons
void checkButtons(){
  
  //select button pressed
  while (digitalRead(selectButton) == LOW) {

    resetNumbers();
    printLetter(1, 1, false);
    delay(displayPause);
  resetNumbers();
    printLetter(2, 2, false);
    delay(displayPause);
  resetNumbers();
    printLetter(3, 3, false);
    delay(displayPause);
  resetNumbers();
    printLetter(4, 4, true);
    delay(displayPause);
  resetNumbers();

//    if (unit == 'c'){
//      unit = 'f';
//      count = 0;
//    } else {
//      unit = 'f';
//      count = 0;
//    }
  } 

}

//display the temperature
void showNum(int n) {

  //display digit 1
  int n1 = (n%10000)/1000;
  printNumber(n1, 1, false); 
  delay(displayPause);
  resetNumbers();

  //digit 2
  int n2 = (n%1000)/100;
  printNumber(n2, 2, true); 
  delay(displayPause);
  resetNumbers();

  //digit 3
  int n3 = (n%100)/10;
  printNumber(n3, 3, false);
  delay(displayPause);
  resetNumbers();

  //digit 4
  printNumber(unit, 4, false); 
  delay(displayPause);
  resetNumbers();

}

//reset the screen, so everything is off
void resetNumbers(){
  
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,LOW);
    digitalWrite(decimal,HIGH);
    digitalWrite(degs,HIGH);
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);  
  
}

//output a specific number in a specific position
//n = number, d = position
void printNumber(int n, int d, int dec) {
  
  if ((d > 4) || (d < 1)){
    return;  
  }

  //so we only light up the degrees led for the same time as the other leds
  if (d == 1){
    digitalWrite(degs,LOW); 
  }

  if (dec){
    digitalWrite(decimal,LOW); 
  }
  
  //d is the display to illuminate
  if(d==1)  {
    digitalWrite(digitOne,HIGH);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,LOW);
  } 

  if(d==2) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,HIGH);
    digitalWrite(digitThree, LOW);
    digitalWrite(digitFour,LOW);
  }

  if(d==3) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,HIGH);
    digitalWrite(digitFour,LOW);
  }

  if(d==4) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,HIGH);
  }
 
  //n is for the number/character to be displayed
  switch(n) {
  case 0:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,HIGH);
    break;
    

  case 1:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

  case 2:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,LOW);
    break;

  case 3:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,LOW);
    break;

  case 4:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 5:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 6:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 7:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

  case 8:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 9:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 'c':
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,HIGH);
    break;

  case 'f':
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;
  }
}

//output a specific letter in a specific position
//letter = number, d = position
void printLetter(int letter, int d, int dec) {
  
  if ((d > 4) || (d < 1)){
    return;  
  }

  //so we only light up the degrees led for the same time as the other leds
  //if (d == 1){
    //digitalWrite(degs,LOW); 
  //}

  if (dec){
    digitalWrite(decimal,LOW); 
  }
  
  //d is the display to illuminate
  if(d==1)  {
    digitalWrite(digitOne,HIGH);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,LOW);
  } 

  if(d==2) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,HIGH);
    digitalWrite(digitThree, LOW);
    digitalWrite(digitFour,LOW);
  }

  if(d==3) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,HIGH);
    digitalWrite(digitFour,LOW);
  }

  if(d==4) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,HIGH);
  }
 
  //n is for the number/character to be displayed
  switch(letter) {
  case 1:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;
    

  case 2:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,LOW);
    break;

  case 3:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,LOW);
    break;

  case 4:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

//  case 4:
//    digitalWrite(segmentA,HIGH);
//    digitalWrite(segmentB,LOW);
//    digitalWrite(segmentC,LOW);
//    digitalWrite(segmentD,HIGH);
//    digitalWrite(segmentE,HIGH);
//    digitalWrite(segmentF,LOW);
//    digitalWrite(segmentG,LOW);
//    break;
//
//  case 5:
//    digitalWrite(segmentA,LOW);
//    digitalWrite(segmentB,HIGH);
//    digitalWrite(segmentC,LOW);
//    digitalWrite(segmentD,LOW);
//    digitalWrite(segmentE,HIGH);
//    digitalWrite(segmentF,LOW);
//    digitalWrite(segmentG,LOW);
//    break;
//
//  case 6:
//    digitalWrite(segmentA,LOW);
//    digitalWrite(segmentB,HIGH);
//    digitalWrite(segmentC,LOW);
//    digitalWrite(segmentD,LOW);
//    digitalWrite(segmentE,LOW);
//    digitalWrite(segmentF,LOW);
//    digitalWrite(segmentG,LOW);
//    break;
//
//  case 7:
//    digitalWrite(segmentA,LOW);
//    digitalWrite(segmentB,LOW);
//    digitalWrite(segmentC,LOW);
//    digitalWrite(segmentD,HIGH);
//    digitalWrite(segmentE,HIGH);
//    digitalWrite(segmentF,HIGH);
//    digitalWrite(segmentG,HIGH);
//    break;
//
//  case 8:
//    digitalWrite(segmentA,LOW);
//    digitalWrite(segmentB,LOW);
//    digitalWrite(segmentC,LOW);
//    digitalWrite(segmentD,LOW);
//    digitalWrite(segmentE,LOW);
//    digitalWrite(segmentF,LOW);
//    digitalWrite(segmentG,LOW);
//    break;
//
//  case 9:
//    digitalWrite(segmentA,LOW);
//    digitalWrite(segmentB,LOW);
//    digitalWrite(segmentC,LOW);
//    digitalWrite(segmentD,LOW);
//    digitalWrite(segmentE,HIGH);
//    digitalWrite(segmentF,LOW);
//    digitalWrite(segmentG,LOW);
//    break;
//
//  case 'c':
//    digitalWrite(segmentA,LOW);
//    digitalWrite(segmentB,HIGH);
//    digitalWrite(segmentC,HIGH);
//    digitalWrite(segmentD,LOW);
//    digitalWrite(segmentE,LOW);
//    digitalWrite(segmentF,LOW);
//    digitalWrite(segmentG,HIGH);
//    break;
//
//  case 'f':
//    digitalWrite(segmentA,LOW);
//    digitalWrite(segmentB,HIGH);
//    digitalWrite(segmentC,HIGH);
//    digitalWrite(segmentD,HIGH);
//    digitalWrite(segmentE,LOW);
//    digitalWrite(segmentF,LOW);
//    digitalWrite(segmentG,LOW);
//    break;
  }
}

//main loop
void loop() {
 
  getTemp();
  showNum(temp);
  checkButtons();
  
}



