/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <Debounce.h>
#include <SerialCommand.h>

SerialCommand serialCmd;   

// Connected from arduino to ESP8266

const static int ESP_GPIO0PIN = 10;
const static int ESP_GPIO2PIN = 12;
const static int ESP_CH_PDPIN = 13;
const static int ESP_RSTPIN = A0;

// digital pin 2 has a pushbutton attached to it. Give it a name:
const static int pushButton = 2;
const static int BYPASS_0_PIN = 3;
const static int BYPASS_1_PIN = 4;
const static int BYPASS_2_PIN = 5;

const static int led1Pin = 9;
const static int ground1Pin = 8;

const static int led2Pin = 7;
const static int ground2Pin = 6;


const static int buttonPressFlashPeriod = 1000;

unsigned long timeSample;
unsigned long startedPressingButtonAt;
bool lastButtonState = false;
Debounce debouncer = Debounce( 20 , pushButton);


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
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(led1Pin, OUTPUT);
  pinMode(ground1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(ground2Pin, OUTPUT);
  pinMode(BYPASS_0_PIN, OUTPUT);
  pinMode(BYPASS_1_PIN, OUTPUT);
  pinMode(BYPASS_2_PIN, OUTPUT);
  digitalWrite(BYPASS_0_PIN,HIGH);
  digitalWrite(BYPASS_1_PIN,HIGH);
  digitalWrite(BYPASS_2_PIN,HIGH);

  digitalWrite(led1Pin,true);
  digitalWrite(ground1Pin,false);
  digitalWrite(led2Pin,true);
  digitalWrite(ground2Pin,false);
  pinMode(ESP_GPIO0PIN, INPUT);
  pinMode(ESP_GPIO2PIN, INPUT);
  
  pinMode(ESP_RSTPIN, OUTPUT);
  pinMode(ESP_CH_PDPIN, OUTPUT);
  digitalWrite(ESP_RSTPIN,true);
  digitalWrite(ESP_CH_PDPIN,true);
  
  serialCmd.addCommand("flash",flashPulse);  // pulse a flash
  serialCmd.addCommand("reset",resetPulse);  // pulse a reset
  serialCmd.addCommand("bypass",bypassModeOn);  // set bypass mode
  serialCmd.addCommand("normal",bypassModeOff);  // set normal mode
  
  serialCmd.addDefaultHandler(unrecognized); // Handler for command that isn't matched  (says "What?") 
  timeSample = millis();
}
  
// the loop routine runs over and over again forever:
void loop() {
  
  serialCmd.readSerial();
  debouncer.update();
  
  // read the input pin:
  bool buttonState = debouncer.read();
  
  if (buttonState != lastButtonState) {
    Serial.print("Button = ");
    Serial.println(buttonState);
     
    if (!buttonState) {
      startedPressingButtonAt = millis();
      resetPulse();
    }
  }
  unsigned long period = millis() - startedPressingButtonAt;
  
  
  if (!buttonState &&  period > buttonPressFlashPeriod && period < buttonPressFlashPeriod*2) {
    flashPulse();
  }
  

  lastButtonState = buttonState;
  delay(1);        // delay in between reads for stability
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

void flashPulse() {
  Serial.print(""); 
  // Show how we are setting GPIO bits
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, HIGH);
  bypassModeOn();
  delay(300);
  // Reset esp8266
  digitalWrite(ESP_RSTPIN, LOW);
  delay(200);
  digitalWrite(ESP_RSTPIN, HIGH);
  delay(700);
  
  bypassModeOff();
  Serial.println("Pulsing flash .. done"); 
}

void bypassModeOn() {
  Serial.println(" setting bypass mode on"); 
  digitalWrite(BYPASS_0_PIN,LOW);
  digitalWrite(BYPASS_1_PIN,LOW);
  digitalWrite(BYPASS_2_PIN,LOW);
  delay(200);
}

void bypassModeOff() {
  Serial.println(" setting bypass mode off"); 
  digitalWrite(BYPASS_0_PIN,HIGH);
  digitalWrite(BYPASS_1_PIN,HIGH);
  digitalWrite(BYPASS_2_PIN,HIGH);
}

// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized() {
  Serial.println("What?"); 
}

ISR(TIMER2_COMPA_vect){//timer1 interrupt 8kHz 
  digitalWrite(led1Pin, digitalRead(ESP_GPIO0PIN));
  digitalWrite(led2Pin, digitalRead(ESP_GPIO2PIN));
}
