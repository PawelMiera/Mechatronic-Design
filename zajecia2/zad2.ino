String s = "";
int a,b;
char dzialanie;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  Serial.println("Podaj pierwsza liczbe:");
  
  while (Serial.available() < 1)
  {
    delay(100);
  }
  
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    s+=c;
    a = s.toInt();
  }
    s="";

  Serial.println("Podaj druga liczbe:");
  
  while (Serial.available() < 1)
  {
    delay(100);
  }
  
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    s+=c;
    b = s.toInt();
  }
    s="";

  Serial.println("Podaj dzialanie(+,-,/,*):");
  
  while (Serial.available() < 1)
  {
    delay(100);
  }
  
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    if(c != '\n') dzialanie = c;
  }
  
  if(dzialanie == '+')
  {
    Serial.print("Wynik to: ");
    Serial.println(int(a+b));
  }
  else if(dzialanie == '-')
  {
    Serial.print("Wynik to: ");
    Serial.println(int(a-b));
  }
  else if(dzialanie == '*')
  {
    Serial.print("Wynik to: ");
    Serial.println(int(a*b));
  }
  else if(dzialanie == '/')
  {
    if(b == 0)  Serial.println("Nie dziel przez 0!");
    else
    {
    Serial.print("Wynik to: ");
    Serial.println(float(a/b));
    }
  }
  else
  {
    Serial.println("Wybrano zle dzialanie");
  }
  
}
