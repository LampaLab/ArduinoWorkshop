#include <LiquidCrystal.h>
 
// Инициализируем объект-экран, передаём использованные 
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

String str_to_lcd;
 
void setup() 
{
    // устанавливаем размер (количество столбцов и строк) экрана
    lcd.begin(16, 2);
    // печатаем первую строку
    lcd.print("Hello world!");
    // устанавливаем курсор в колонку 0, строку 1. То есть на
    // самом деле это вторая строка, т.к. нумерация начинается с нуля
    lcd.setCursor(0, 1);
    // печатаем вторую строку
    lcd.print("foo bar baz");
    Serial.begin(9600);
}
 
void loop() 
{
  if( read_string(str_to_lcd) )
  {
    lcd.clear();
    lcd.print(str_to_lcd);  
  }
  delay(1000);
}

int read_string(String& str_from_ser)
{
  int sucess = 0;
  char len = 0;

  if(len = Serial.available())
  {
    sucess = 1;
    str_from_ser = "";
    for(int i = 0; i < len; i++)
      str_from_ser += (char)Serial.read(); 
  }
   
  return sucess;
}
