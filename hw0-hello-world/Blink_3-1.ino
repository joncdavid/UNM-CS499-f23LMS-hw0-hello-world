/*
  Blink
  Turns on an LED on for one-half second, then off for one-half second, repeat three times.
  Then off for one second
  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Start");
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.print("1");
  delay(500);               // wait for 1/2 second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.print("2");
  delay(500);               // wait for 1/2 second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("3");
  delay(500);               // wait for 1/2 second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for one second
}
