int pushButton = 2;
int led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  digitalWrite(led, buttonState);
  delay(10);        // delay in between reads for stability
}



