#include<LiquidCrystal.h>

LiquidCrystal lcd(10, 11, 12, 2, 3, 4, 5);

void setup()
{
	
}

void loop()
{
	lcd.begin(16,1);
  	lcd.print("hello, world!");
  	delay(100);
}