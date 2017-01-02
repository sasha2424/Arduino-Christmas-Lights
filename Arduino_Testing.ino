/*
 * Author:
 * Alexander Ivanov
 * 
 * Christmas Lights Project Requirements:
 * - Arduino
 * - 4 relays connected to sockets
 * - optional liquid crystal display
 */


#include <Wire.h>
#include <LiquidCrystal_I2C.h> // -optional-

LiquidCrystal_I2C lcd(0x3F,20,4);    // 0x27 // -optional-


unsigned long onTime = 10800000; //3 hours
unsigned long SCALE = 1; // by how to speed up time cycle


int patternTimer = 0; // timer for pattern transitions
int patternRates[] = {random(2,20),random(2,20),random(2,20),random(2,20)};

int pins[] = {28,26,24,22}; // pins where relays are connected
int states[] = {LOW,LOW,LOW,LOW}; // states of individual sockets High = OFF Low = ON

int Timer = 0; // timer for heartbeat light
int ledState = LOW; // state of heartbeat light
int led = 13; //hearbeat light pin

void setup() 
{
  lcd.begin(); // turn on screen -optional-
  lcd.backlight();// -optional-
  
  pinMode(led,OUTPUT); // set pin modes for heartbeat

  for(int i = 0; i < 4; i++){
    pinMode(pins[i],OUTPUT);
  }
  
}

void loop() {
  // heart beat led blinker
  if (millis() - Timer > 1000) {
    Timer = (long) millis();
    ledState = (LOW + HIGH) - ledState;
    digitalWrite(led, ledState);   // set the led state to current state
  }
  
  
  if(millis()%(86400000 / SCALE) < onTime/SCALE){
    // turn on relays acording to states
    for(int i = 0; i < 4; i++){
      digitalWrite(pins[i],states[i]); // set relay out puts to current out put
    }
    
    patternTimer ++;
    for(int i = 0; i < 4; i++){
      if(patternTimer % patternRates[i] == 0){
        states[i] = (LOW + HIGH) - states[i]; // switches relay states
      }
    } 

  lcd.setCursor(0, 0);// -optional-
  lcd.print("ON ");// print "ON" on the display -optional-
  
  } else {
    // turn all of
    for(int i = 0; i < 4; i++){
      digitalWrite(pins[i],HIGH); // turn off all relays
    }

  lcd.setCursor(0, 0);// -optional-
  lcd.print("OFF"); // print "OFF" on the display -optional-
  }
  
  delay(300); // delay each cycle so blinking is slower
}
