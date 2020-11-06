#include <Wire.h>
#include <VL53L0X.h>
#include <SoftwareSerial.h>
#include <PID_v1.h>

double SetpointY, InputY, OutputY;
double SetpointX, InputX, OutputX;



double Kpy=0.1 , Kiy=1, Kdy=0.01;
double Kpx=0.1 , Kix=1, Kdx=0.01;
PID myPIDy(&InputY, &OutputY, &SetpointY, Kpy, Kiy, Kdy, DIRECT);
PID myPIDx(&InputX, &OutputX, &SetpointX, Kpx, Kix, Kdx, DIRECT);

#include <ps2.h>
PS2 mouse(7, 4);
#define L1 5 
#define L2 6
#define P1 11
#define P2 10
VL53L0X sensor;
SoftwareSerial mySerial(9, 8); // RX, TX

int b,VY,VX;
int degreeToTurn;
int dist;
char a;
int vc=50;
int r=0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(1000);
  b= (analogRead(0)+analogRead(1))/2;
  b=b-30;
  delay(2000);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(P1,OUTPUT);
  pinMode(P2,OUTPUT);
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();

  InputY = 0;
  InputX = 0;
  SetpointY = 0;
  SetpointX = 0;

  myPIDy.SetMode(AUTOMATIC);
  myPIDx.SetMode(AUTOMATIC);

  myPIDy.SetOutputLimits(-100, 100);
  myPIDx.SetOutputLimits(-100, 100);
}

void loop()
{
  if (mySerial.available()) {
  a=mySerial.read();
  mySerial.write("o");
  }
  if(a=='r'){
    if (mySerial.available()) {
    a=mySerial.read();
    r = a - '0';   
  }
  
  }
  
if(r==0){

  
}
 
if(r==1) 
      { 
        Serial.println(a);
        myPIDy.SetMode(MANUAL);
        myPIDx.SetMode(MANUAL);
        sterowanieReczne();
     }
  dist = sensor.readRangeContinuousMillimeters();
  jazda(OutputY, OutputX);

  char mstat;
  char mx;
  char my;


  mouse.write(0xeb);
  mouse.read();     
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();


  

  InputY = my;
  myPIDy.Compute();
  InputX =  mx;
  myPIDx.Compute();
}


 void predkosc (int a,int b,int v,bool kier){
 if(kier){
    analogWrite(a,2.55*v);  
    digitalWrite(b,LOW);   
    }
 else {
    digitalWrite(a,LOW);
    analogWrite(b,2.55*v);
      }
  }

  void jazda(int v, int omega)
  {
    bool kierL = true;
    bool kierR = true;
    int vL = v-omega;
    int vR = v+omega;
    if(v-omega < 0) 
    {
      kierL = false;
      vL = abs(v-omega);
      
    }
    if(v+omega < 0)
    {
      kierR = false;
      vR = abs(v+omega);
      
    }
    if(vL > 100) vL = 100;
    if(vR > 100) vL = 100;
    predkosc(L1,L2,vL,kierL);
    predkosc(P1,P2,vR,kierR);
  }

void mouse_init()
{
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);
}

void prosto(int v, bool kier){
    predkosc(L1,L2,v,kier);
    predkosc(P1,P2,v,kier);
  }

void sterowanieReczne(){
  if(a=='v'){
    if (mySerial.available()) {
    a=mySerial.read();
    vc = a - '0';
    vc=(vc+1)*10;
  }
  }
  if(a=='w'){
    prosto(vc,true);
  }
    if(a=='a'){
       predkosc(L1,L2,vc,false);
       predkosc(P1,P2,vc,true);
  }
    if(a=='s'){
       prosto(vc,false);
  }
    if(a=='d'){
       predkosc(L1,L2,vc,true);
       predkosc(P1,P2,vc,false);
  }
    if(a=='q'){
      predkosc(L1,L2,vc/4,true);
      predkosc(P1,P2,vc,true);
  }
    if(a=='e'){
      predkosc(L1,L2,vc,true);
      predkosc(P1,P2,vc/4,true);
  }
    if(a=='z'){
      predkosc(L1,L2,vc/4,false);
      predkosc(P1,P2,vc,false);
  }
    if(a=='x'){
      predkosc(L1,L2,vc,false);
      predkosc(P1,P2,vc/4,false);
  }
    if(a=='n'){
      predkosc(L1,L2,0,true);
      predkosc(P1,P2,0,false);
  }
  }
    
