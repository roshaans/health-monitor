#include <LiquidCrystal_I2C.h>

//11/26/18
//hello
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
  bool flagger = false;

void setup()
{

	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
  //lcd.print("Hello, world!");
}

void loop()
{
  if(flagger == false) {
  lcd.print("Hello, world!");
      delay(1000);
      flagger = true;
  } else if (flagger == true){
    lcd.clear();
      lcd.print("BYE!!");
  
    flagger = false;
    delay(1000);

  }
  
  //lcd.print("Hello, world!");
}
