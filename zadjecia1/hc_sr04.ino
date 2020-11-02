
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  Serial.begin(9600); 
}

void loop()
{
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  
  long duration = pulseIn(3, HIGH); 
  
  Serial.print("Pomiar: "); 
  Serial.println(duration*.0343/2); 
  delay(100); 
}