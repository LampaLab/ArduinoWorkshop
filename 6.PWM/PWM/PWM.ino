int led = 13;           // the pin that the LED is attached to
int brightness = 10;    // how bright the LED is

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 13 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 13:
  analogWrite(led, brightness);
  while(1);
}

