//calculates bpm + displays on lcd
//11/26/18

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//const int OUTPUT_TYPE = PROCESSING_VUSUALIZER;

int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 2;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.
int count = 0;
int savedBPM = 0;
int arrayBPM[] = {};

/* Global declarations for whisker switch variables */
int switchPin = 9;    // select the input pin for the voltage divider input
int flag = 0;         // the flag variable is used in the 'if statement' conditional test
long starttime = 0;   // variable to store the time at which the switch is pressed
long endtime = 0;     // variable to store the time at which the switch is released
float elapsedtime = 0; // variable to store the amount of time the switch is pressed
int switchonoff = 0;



int powersensorPin = 4;

//int stored_bpm = [];


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


// The SetUp Function:
void setup() {
  pinMode(LED13, OUTPUT);        // pin that will blink to your heartbeat!
  pinMode(powersensorPin, OUTPUT);
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
  pinMode(switchPin, INPUT);   // set up the digital I/O pin 8 to be an input
  delay(100);                  // short delay

  // initialize the LCD
  lcd.begin();
  lcd.backlight();
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
  }
  lcd.print("BPM:");

}

// The Main Loop Function
void loop() {
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
  // Assign this value to the "Signal" variable.

  //Serial.println(Signal);                    // Send the Signal value to Serial Plotter.


  if (Signal > Threshold) {                        // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
    digitalWrite(LED13, HIGH);
  } else {
    digitalWrite(LED13, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
  }

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  // "myBPM" hold this BPM value now.

  //Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
  lcd.setCursor(13, 0);
  lcd.print((myBPM));// Print the value inside of myBPM.
  lcd.print("   ");
  lcd.setCursor(13, 0);
  lcd.print((myBPM));

  delay(200);


  /* whisker switch*/
  switchonoff = digitalRead(switchPin);   // read the current state of the switch
  if (switchonoff == HIGH) {  // 1st test - is the switch on/off, 1/0, HIGH/LOW?
    if (flag == 0) {
      savedBPM = myBPM;
      //Serial.print(savedBPM);
      flag = 1;               // change the flag's "state"
      delay(50);
    }
  }
  if (switchonoff == LOW && flag == 1) {       // 1st & 2nd tests together (not nested)
    flag = 0;          //print the elapsed time to serial monitor
  }

  
  //Serial.println(switchonoff);
  lcd.setCursor(13, 1);
  lcd.print((savedBPM));// Print the value inside of myBPM.
  lcd.print("   ");
  lcd.setCursor(13, 1);
  lcd.print((savedBPM));
  arrayBPM[count] = savedBPM;
  count = count + 1;
  //int i = 0;
//  for (int i = 0; i<=count; i++){
//      Serial.println(arrayBPM[i]);
//   }
}
