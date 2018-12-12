//Cleaned Code

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <SD.h>       // library for SD card functions
#include <SPI.h>      // library for SPI communication (for uSD reader/writer)

#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);


int PulseSensorPurplePin = 0;
bool isFirstTime = true;
int enrollButton = 7;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550; //PULSE SENSOR
bool isBPM = false;
int savedBPM = 0;


const int chipSelect = 8;   // clock signal is on pin D8

//int currentUserId = 0; //Stores users ID


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int currentUserId = 0;
bool scanFinger = false;
uint8_t id;
int i = 0;

/* Global declarations for whisker switch variables */
int switchPin = 6;    // select the input pin for the voltage divider input
int flag = 0;         // the flag variable is used in the 'if statement' conditional test

int switchonoff = 0;


bool firstTime = true;



LiquidCrystal_I2C lcd(0x27, 16, 2);


PulseSensorPlayground pulseSensor;
int enrollButtonState = 0;         // variable for reading the pushbutton status

void setup() {

  Serial.print("STARTING..");
  Serial.begin(9600);
  pinMode(switchPin, INPUT);   // set up the digital I/O pin 8 to be an input
  pinMode(chipSelect, OUTPUT);
  delay(100);                  // short delay

  lcd.begin();
  lcd.backlight();
    lcd.clear();
 lcd.print("Get started by");
 lcd.setCursor(0, 1);
 lcd.print("pressing Button");
  pinMode(enrollButton, INPUT);
  
//   if (pulseSensor.begin()) {
//      Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
//       }
//    lcd.print("BPM:"); //displays on displayboard

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {

//  File dataFile = SD.open("DATA.txt", FILE_WRITE);
//
//
//  String dataString = "";
//  //dataString += "";
//  dataString += String(savedBPM);


  enrollButtonState = digitalRead(enrollButton);

  switchonoff = digitalRead(switchPin);
  // if (switchonoff == LOW and firstTime == true) {
  //
  //   firstTime = false;
  //   }
 if (enrollButtonState == HIGH and firstTime == true) {
   lcd.clear();
 lcd.print("Scan Your Finger!");
 lcd.setCursor(1, 1);
 lcd.print(":) :0 :) :0 :) ");
    Serial.println("FingerPrint Scanner ON!");
    setUpFingerprintModule();
    scanFinger = true;
    
    firstTime = false;

  }

 
  if (scanFinger == true ) {
    getFingerprintIDez();
    delay(50);            //don't ned to run this at full speed.


    //   if (getFingerprintIDez() != -1) {
    //      break;
    //    }


  }

  if (currentUserId != 0) {

    scanFinger = false;
    isBPM = true;

  }

  


  while (isBPM == true) {
    if (isFirstTime == true) {
    lcd.clear();
 lcd.print("Scan your Heart");
 lcd.setCursor(5, 1);
 lcd.print("Rate!");
 delay(3000);
  lcd.clear();

 isFirstTime = false;
    }
    BPMSensor();
  }
  //if (pulseSensor.begin()) {
  //    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
  //  }
}


void BPMSensor() {

  Serial.begin(9600);
  if (pulseSensor.begin()) {
    lcd.print("BPM:");

    //Serial.println("We created a pulseSensor Object");
  }
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".


  File dataFile = SD.open("DATA.txt", FILE_WRITE);


  String dataString = "";
  //dataString += "";
  dataString += String(savedBPM);



  Serial.println(myBPM);
  /* whisker switch*/
  switchonoff = digitalRead(switchPin);   // read the current state of the switch
  if (switchonoff == HIGH) {  // 1st test - is the switch on/off, 1/0, HIGH/LOW?
    if (flag == 0) {
      i = i + 1;
      savedBPM = myBPM;
      Serial.println(savedBPM);
      flag = 1;               // change the flag's "state"
      delay(50);
    }

  }

  if (switchonoff == LOW && flag == 1) {       // 1st & 2nd tests together (not nested)
    flag = 0;          //print the elapsed time to serial monitor
  }




  /*Saving BPM and printing it on lcd*/
  //while (isBPM == true) {
  //Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
  lcd.setCursor(13, 0);
  lcd.print((myBPM));// Print the value inside of myBPM.
  lcd.print("   ");
  lcd.setCursor(13, 0);
  lcd.print((myBPM));

  delay(200);

  lcd.setCursor(13, 1);
  lcd.print((savedBPM));// Print the value inside of myBPM.
  lcd.print("   ");
  lcd.setCursor(13, 1);
  lcd.print((savedBPM));

  if (switchonoff == HIGH ) {
    dataFile.print(currentUserId);
    dataFile.print(" ");
    dataFile.println(savedBPM);
    dataString += "  "  ;
  } else {
    //dataFile.print(0);

  }

  dataFile.flush();
  dataFile.close();

}


//Serial.println(switchonoff);

//Serial.println(savedBPM);


//}
void setUpFingerprintModule() {

  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}
uint8_t getFingerprintID() {
  
    uint8_t p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println("No finger detected");
        return p;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        return p;
      default:
        Serial.println("Unknown error");
        return p;
    }

    // OK success!

    p = finger.image2Tz();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return p;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
      case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return p;
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return p;
      default:
        Serial.println("Unknown error");
        return p;
    }
   
    // OK converted!
    p = finger.fingerFastSearch();
    if (p == FINGERPRINT_OK) {
      Serial.println("Found a print match!");
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Communication error");
      return p;
    } else if (p == FINGERPRINT_NOTFOUND) {
      Serial.println("Did not find a match");
      return p;
    } else {
      Serial.println("Unknown error");
      return p;
    }

    // found a match!
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);
    currentUserId = id;
    return finger.fingerID;
  
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!

  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  currentUserId = finger.fingerID;


  return finger.fingerID;

}


uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
