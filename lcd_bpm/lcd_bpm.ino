//calculates bpm + displays on lcd
//11/26/18

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
   // initialize the LCD
  lcd.begin();
  lcd.backlight();

}

// The Main Loop Function
void loop() {

//delay(10);
   int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 //Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 //lcd.print("Heart Rate:");                        // Print phrase "BPM: " 
 lcd.println(myBPM);                        // Print the value inside of myBPM. 
}

delay(20);



}
