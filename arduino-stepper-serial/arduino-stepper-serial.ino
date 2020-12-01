/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(100);  // 10 rpm   

  colorWipe(strip.Color(75,255,0),50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
     Serial.println("Reading serial...");

    // look for the next valid integer in the incoming serial stream:
    int amount = Serial.parseInt();


    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {
      Serial.println("Moving...");
      if (amount > 0) {
        colorWipe(strip.Color(255,255,255),0);
        myMotor->step(amount, FORWARD, MICROSTEP); 
        colorWipe(strip.Color(75,255,0),0);
      } else {
        colorWipe(strip.Color(255,255,255),0);
      myMotor->step(-amount, BACKWARD, MICROSTEP);  
      colorWipe(strip.Color(75,255,0),0);  
      }
    }
  }
}




