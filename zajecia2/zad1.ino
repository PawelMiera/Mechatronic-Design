bool last_S1 = false;
bool start = false;
int start_ind = 0;
  
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  bool S1 = digitalRead(2);
  
  if(S1 == HIGH && S1 != last_S1)
  {
    start = !start;
    if(start == true)
    {
      start_ind++;
      Serial.println(start_ind);
    }
  }
  
  if(start)
  {
    if(digitalRead(3))
    {
      digitalWrite(11,HIGH);
      digitalWrite(10,LOW); 
    }
    else if(digitalRead(4))
    {
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW); 
    }
    else
    {
      digitalWrite(11,LOW);
      digitalWrite(10,LOW); 
    }
  }
  else
  {
    digitalWrite(11,LOW);
    digitalWrite(10,LOW); 
  }
  last_S1 = S1;
}