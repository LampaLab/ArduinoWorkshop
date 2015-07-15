
// pins for the LEDs:
const int led = 13;

int new_bright = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(led, OUTPUT);
}

void loop() {
  
  if(read_led_state())
    analogWrite(led, new_bright);
    
}
 
int read_led_state()
{
  int success = 0;
  int tmp = 1;

  if(Serial.available())
  {
    tmp = Serial.parseInt();
    
    if(tmp)
    {
       new_bright = tmp;  
       success = 1;  
    }  
    
    while(Serial.available())
      tmp = Serial.read();
  }
  
  return success;
}

