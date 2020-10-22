bool S1 = 0;

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(7, INPUT);
  digitalWrite(13, HIGH);
}

void loop()
{
  S1 = digitalRead(7);
  if(S1)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
}