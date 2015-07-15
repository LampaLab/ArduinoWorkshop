#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
#define ONE_WIRE_BUS 3

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float temp;
 
void setup() 
{
    // устанавливаем размер (количество столбцов и строк) экрана
    lcd.begin(16, 2);
    Serial.begin(9600);
    sensors.begin();
    lcd.print("Temp = ");
    
}
 
void loop() 
{
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);

  Serial.print("Temp = ");
  Serial.println(temp);

  lcd.setCursor(7,0);
  lcd.print(temp);
 
  delay(1000);
}

