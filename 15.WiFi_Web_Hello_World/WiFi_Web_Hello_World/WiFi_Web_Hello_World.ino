#include <SoftwareSerial.h>

#define DEBUG true
 
SoftwareSerial ESP8266(9,8); // make RX Arduino line is pin 9, make TX Arduino line is pin 8.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 9
                             // and the RX line from the esp to the Arduino's pin 8

boolean FAIL_8266 = false;

String my_AP_SSID = "MyAP";
String my_AP_Pass = "abcdefg00";

void setup() 
{
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
 
     int connectionId = ESP8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48

     Serial.print("New connection ID: ");
     Serial.println(connectionId);
     
     String webpage = "<h1>Hello</h1><h2>World!</h2><button>LED1</button>";
     
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
     delay(2000);
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

