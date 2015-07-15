#include <SoftwareSerial.h>

#define DEBUG true
 
SoftwareSerial ESP8266(9,8); // make RX Arduino line is pin 9, make TX Arduino line is pin 8.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 9
                             // and the RX line from the esp to the Arduino's pin 8

boolean FAIL_8266 = false;
int LED = 13;

String my_AP_SSID = "MyAP";
String my_AP_Pass = "abcdefg00";

void setup() 
{
  pinMode(LED, OUTPUT);
  
  do{
    Serial.begin(9600);
    ESP8266.begin(9600);
  
    //Wait Serial Monitor to start
    while(!Serial);
    Serial.println("--- Start ---");

    ESP8266.println("AT+RST");
    
    delay(1000);
    
    if(ESP8266.find("ready"))
    {
      FAIL_8266 = false;
      Serial.println("Module is ready");
      sendData("AT+CWSAP=\"" + my_AP_SSID + "\",\"" + my_AP_Pass + "\",9,4\r\n", 1000, DEBUG);
      sendData("AT+CWMODE=2\r\n", 1000, DEBUG);                                               //Configuring as access point
      sendData("AT+CIFSR\r\n", 1000, DEBUG);                                                  //Get IP 
      sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);                                               //Set multiple connections
      sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);                                         //Create webserver
      Serial.println("Server setup finish");
      
    }else{
      Serial.println("Module have no response.");
      delay(500);
      FAIL_8266 = true;
    }
  }while(FAIL_8266);  
}

void loop() 
{
  if(ESP8266.available()) // check if the esp is sending a message 
  {
    if(ESP8266.find("+IPD,"))
    {
     delay(100);

     String action;
 
     int connectionId = ESP8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48

     Serial.print("New connection ID: ");
     Serial.println(connectionId);

     ESP8266.find("led=");
     char s = ESP8266.read();
     if(s=='0'){
        digitalWrite(LED, LOW);
        action = "Turning LED off";
        Serial.println(action);
     }else if(s=='1'){
        action = "Turning LED on";
        digitalWrite(LED, HIGH);
         Serial.println(action);
     }

     delay(1000);
     
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,1000,DEBUG);
    }
  }
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    ESP8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(ESP8266.available())
      {
        char c = ESP8266.read(); 
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

