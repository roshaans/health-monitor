//
// This program gathers input from a sensor through 
// analog pin 0 and passes the output to the serial connection.
//

int analogPin = 0;          // identify analog pin to be used 
int val = 0;                // variable to store the value read

void setup() {  
  Serial.begin(115200);      //  setup serial baud rate
                             //  you may choose to use 115200 if you have trouble 
  delay(1000);
}

void loop() {
  val = analogRead(analogPin);    // read the input pin
  //Serial.print(micros());         // print time to serial
  //Serial.print(" ");
  Serial.println(val);            // print value to serial monitor
}
