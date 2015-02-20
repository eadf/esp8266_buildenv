/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <Bounce2.h>
#include <SerialCommand.h>

SerialCommand serialCmd;   

const static int IN_1 = 10; // -> 9
const static int IN_2 = 11; // -> 8
const static int IN_3 = 12; // -> 7
const static int IN_4 = 13; // -> 6
const static int IN_5 = A0; // -> 5
const static int IN_6 = A1; // -> 4
const static int IN_7 = A2; // -> 3
//const static int IN_8 = A3; // -> 2

const static int OUT_1 = 9;
const static int OUT_2 = 8;
const static int OUT_3 = 7;
const static int OUT_4 = 6;
const static int OUT_5 = 5;
const static int OUT_6 = 4;
const static int OUT_7 = 3;
//const static int OUT_8 = 2;

const static int ESP_RSTPIN = A5;
const static int RELAY_PIN = A4;  

const static int pushButton = A3;
const static int buttonPressFlashPeriod = 1000;

bool buttonJustPressed = true;

// Instantiate a Bounce object :
Bounce debouncer = Bounce(); 

void setup() {  
  cli();//stop interrupts

  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();//allow interrupts

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // make the pushbutton's pin an input with pullup:
  pinMode(pushButton, INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(pushButton);
  debouncer.interval(50);
  
  pinMode(RELAY_PIN, OUTPUT);
  //digitalWrite(RELAY_PIN,HIGH);
  analogWrite(RELAY_PIN,255);
  
  pinMode(IN_1, INPUT);
  pinMode(IN_2, INPUT);
  pinMode(IN_3, INPUT);
  pinMode(IN_4, INPUT);
  pinMode(IN_5, INPUT);
  pinMode(IN_6, INPUT);
  pinMode(IN_7, INPUT);
  
  pinMode(OUT_1, OUTPUT);
  pinMode(OUT_2, OUTPUT);
  pinMode(OUT_3, OUTPUT);
  pinMode(OUT_4, OUTPUT);
  pinMode(OUT_5, OUTPUT);
  pinMode(OUT_6, OUTPUT);
  pinMode(OUT_7, OUTPUT);
  
  pinMode(ESP_RSTPIN, OUTPUT);
  analogWrite(ESP_RSTPIN,255);
  
  serialCmd.addCommand("toggle",toggleRelay);  // toggle relay
  serialCmd.addCommand("reset",resetPulse);  // pulse a reset
  serialCmd.addCommand("bypass",bypassModeOn);  // set bypass mode
  serialCmd.addCommand("normal",bypassModeOff);  // set normal mode
  
  serialCmd.addDefaultHandler(unrecognized); // Handler for command that isn't matched  (says "What?") 
}
  
// the loop routine runs over and over again forever:
void loop() {
  
  serialCmd.readSerial();
  debouncer.update(); 
     
  if(debouncer.fell()) {
    resetPulse();
    buttonJustPressed = true; 
  }
  
  if ((!debouncer.read()) && debouncer.duration() >= buttonPressFlashPeriod && buttonJustPressed) {
    toggleRelay();
    buttonJustPressed = false; 
  }  
  delay(1); // delay in between reads for stability
}

void resetPulse() {
  // Normal reset esp8266
  Serial.print("Pulsing reset "); 
  digitalWrite(ESP_RSTPIN, LOW);
  delay(100);
  digitalWrite(ESP_RSTPIN, HIGH);
  delay(100);
  Serial.println(".. done"); 
}

void toggleRelay() {
  Serial.print("Toggle relay .. start");
  if (!digitalRead(RELAY_PIN)) {
    bypassModeOff();
  } else {
    bypassModeOn();
  }
  Serial.println("Toggle relay .. done"); 
}

void bypassModeOn() {
  Serial.println(" setting bypass mode on"); 
  digitalWrite(RELAY_PIN,LOW);
  delay(200);
  digitalWrite(ESP_RSTPIN, LOW);
  delay(100);
  digitalWrite(ESP_RSTPIN, HIGH);
  delay(100);
}

void bypassModeOff() {
  Serial.println(" setting bypass mode off"); 
  digitalWrite(RELAY_PIN,HIGH);
}

// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized() {
  Serial.println("What?"); 
}

ISR(TIMER2_COMPA_vect){//timer1 interrupt 8kHz 
  digitalWrite(OUT_1, digitalRead(IN_1));
  digitalWrite(OUT_2, digitalRead(IN_2));
  digitalWrite(OUT_3, digitalRead(IN_3));
  digitalWrite(OUT_4, digitalRead(IN_4));
  digitalWrite(OUT_5, digitalRead(IN_5));
  digitalWrite(OUT_6, digitalRead(IN_6));
  digitalWrite(OUT_7, digitalRead(IN_7));
}
