/*  Using Arduino/Atmega uC and common anode 7-segment 4 digit display
*   Simple digital clock program using timer.
*/

#include "TimerOne.h"

// For common anode 7-seg
#define ON LOW
#define OFF HIGH

// Arduino pins
int a=1,b=2,c=3,d=4,e=5,f=6,g=7;
int d4=8,d3=9,d2=10,d1=11;

const int digits[]    = {d1,d2,d3,d4};
const int segments[]  = {a,b,c,d,e,f,g};
const int zero[]      = {1,1,1,1,1,1,0};
const int one[]       = {0,1,1,0,0,0,0};
const int two[]       = {1,1,0,1,1,0,1};
const int three[]     = {1,1,1,1,0,0,1};
const int four[]      = {0,1,1,0,0,1,1};
const int five[]      = {1,0,1,1,0,1,1};
const int six[]       = {1,0,1,1,1,1,1};
const int seven[]     = {1,1,1,0,0,0,0};
const int eight[]     = {1,1,1,1,1,1,1};
const int nine[]      = {1,1,1,1,0,1,1};

const int del = 5; // Refresh delay in milliseconds

// Variables
String t = "00:00:00";
int seconds = 0;
int minutes = 0;
int hours = 0;
int sec = 0;
int m1 = 0;
int m2 = 0;
int h1 = 0;
int h2 = 0;

void setup() {
//  Serial.begin(9600);
  for(int i=0; i<7; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for(int i=0; i<4; i++) {
    pinMode(digits[i], OUTPUT);
  }
  
  blank();
  t = __TIME__; // System time from PC
  hours = t.substring(0,2).toInt();
  minutes = t.substring(3,5).toInt();
  seconds = t.substring(6,8).toInt();
  h1 = t.substring(0,1).toInt();
  h2 = t.substring(1,2).toInt();
  m1 = t.substring(3,4).toInt();
  m2 = t.substring(4,5).toInt();
  Timer1.initialize(1000000); // 1 second
  Timer1.attachInterrupt(timeKeeper);
}

void loop() {
  if(hours < 10) {
    h1 = 0;
    h2 = hours % 10;
  } else {
    h1 = (int) hours / 10;
    h2 = hours % 10;
  }

  if(minutes < 10) {
    m1 = 0;
    m2 = minutes % 10;
  } else {
    m1 = (int) minutes / 10;
    m2 = minutes % 10;
  }
  selectDigitAndPrintNum(4,h1);
  delay(del);
  selectDigitAndPrintNum(3,h2);
  delay(del);
  selectDigitAndPrintNum(2,m1);
  delay(del);
  selectDigitAndPrintNum(1,m2);
  delay(del);
}

// Timer vector to update time each second
void timeKeeper() {
  if(seconds < 59) {
    seconds++;
  } else {
    seconds = 0;
    if(minutes < 59) {
      minutes++;
    } else {
      minutes = 0;
      if(hours < 23) {
        hours++;
      } else {
        hours = 0;
      }
    }
  }
}

// Clears all LED segments
void blank() {
  for(int i=0; i<7; i++) {
    digitalWrite(segments[i], OFF);
  }
  for(int i=0; i<4; i++) {
    digitalWrite(digits[i], OFF);
  }
}

// Turns on LED segments to show a number
void printNumber(int digi) {
  switch(digi) {
    case 0:
      for(int z=0; z<7; z++)
        if(zero[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 1:
      for(int z=0; z<7; z++)
        if(one[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 2:
      for(int z=0; z<7; z++)
        if(two[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 3:
      for(int z=0; z<7; z++)
        if(three[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 4:
      for(int z=0; z<7; z++)
        if(four[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 5:
      for(int z=0; z<7; z++)
        if(five[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 6:
      for(int z=0; z<7; z++)
        if(six[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 7:
      for(int z=0; z<7; z++)
        if(seven[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 8:
      for(int z=0; z<7; z++)
        if(eight[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    case 9:
      for(int z=0; z<7; z++)
        if(nine[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
    default:
      for(int z=0; z<7; z++)
        if(zero[z]==1) digitalWrite(segments[z], ON); else digitalWrite(segments[z], OFF);
      break;
  }
}

// Selects one of four digits and print a number
void selectDigitAndPrintNum(int digit, int num) {
  if(digit > 4 || digit < 1)
    return;
  if(num > 9 || num < 0)
    return;

  blank();
  for(int i=0; i<4; i++) {
    if(i==digit-1) digitalWrite(digits[i], HIGH); else digitalWrite(digits[i], LOW);
  }
  printNumber(num);
}

