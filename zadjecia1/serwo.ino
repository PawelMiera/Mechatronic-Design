#include<Servo.h>

Servo Servo1;

void setup()
{
  Servo1.attach(3);
}

void loop()
{
  for(int i = 0; i < 180; i++)
  {
    Servo1.write(i);
    delay(10);
  }
  for(int i = 180; i > 0; i--)
  {
    Servo1.write(i);
    delay(10);
  }
}