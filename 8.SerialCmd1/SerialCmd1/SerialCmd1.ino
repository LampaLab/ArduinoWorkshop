
// pins for the LEDs:
const int led = 13;

int new_led_state = LOW;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(led, OUTPUT);
}

void loop() {
  
  if(read_led_state())
    digitalWrite(led, new_led_state);
    
}
 

int read_led_state()
{
  int success = 0;
  int tmp = 255;

  if(Serial.available())
  {
    tmp = Serial.parseInt();
    if(tmp == 0 || tmp == 1)
    {
       new_led_state = tmp;  
       success = 1;  
    }  
    
    while(Serial.available())
      tmp = Serial.read();
  }
  
  return success;
}

