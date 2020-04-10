#include <Servo.h> // including servo library
#include<LiquidCrystal.h> //lcd
const int rs=12, en=11,d4=5,d5=4,d6=3,d7=2;

LiquidCrystal lcd(1,2,3,4,5,6,7);

const int trigP = 2;  //D4 Or GPIO-2 of nodemcu//uts
const int echoP = 0;  //D3 Or GPIO-0 of nodemcu

long duration;
int distance;

int ledPin = 12; // choose pin for the LED//irs
int inputPin = 13; // choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status

Servo servo_1; // Giving name to servo1.
Servo servo_2;//Giving name to servo2

int mot1=3;//linefollowing
int mot2=4;
int mot3=5;
int mot4=6;

int left=13;
int right=12;

int Left=0;
int Right=0;

void LEFT (void);
void RIGHT (void);
void STOP (void);

void setup()
{
  lcd.begin(16,2);//lcd
  pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output//uts
  pinMode(echoP, INPUT);   // Sets the echoPin as an Input
  Serial.begin(9600);      // Open serial channel at 9600 baud rate

   pinMode(ledPin, OUTPUT); // declare LED as output //irs
   pinMode(inputPin, INPUT); // declare Infrared sensor as input

    servo_1.attach(0); // Attaching Servo to D1
  servo_2.attach(1);//Attaching servo to D2

   pinMode(mot1,OUTPUT);//linefollowing
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);

  pinMode(left,INPUT);
  pinMode(right,INPUT);

  digitalWrite(left,HIGH);
  digitalWrite(right,HIGH);
  
}
void loop()
{
  lcd.print("HELLO PEOPLE");//lcd
  delay(3000);
  lcd.setCursor(2,1);
  lcd.print("START");
  delay(3000);
  lcd.clear();

  lcd.setCursor(4,1);
  lcd.print("TAKING LEFT");
  delay(3000);
  lcd.clear();

  lcd.setCursor(5,1);
  lcd.print("TAKING RIGHT");
  delay(3000);
  lcd.clear();

  lcd.setCursor(6,1);
  lcd.print("STOP");
  delay(3000);
  lcd.clear();

  digitalWrite(trigP, LOW);   // Makes trigPin low//uts
  delayMicroseconds(2);       // 2 micro second delay 

  digitalWrite(trigP, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trigP, LOW);   // trigPin low

  duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
  distance= duration*0.034/2;        //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor 
  Serial.println(distance);
  delay(3000);                        //Pause for 3 seconds and start measuring distance again

  
   val = digitalRead(inputPin); // read input value //irs
   if (val == HIGH)
   { // check if the input is HIGH
      digitalWrite(ledPin, LOW); // turn LED OFF   
   } 
   else 
   { 
      digitalWrite(ledPin, HIGH); // turn LED ON 
   }


   servo_1.write (45); // Servo will move to 45 degree angle.
  delay (1000);
  servo_1.write (90);  // servo will move to 90 degree angle.
  delay (1000);
  servo_2.write (45);
  delay(1000);
  servo_2.write(90);
  
   analogWrite(mot1,255);
   analogWrite(mot2,0);
   analogWrite(mot3,255);
   analogWrite(mot4,0);

while(1)
{
  Left=digitalRead(left);
  Right=digitalRead(right);
  
  if((Left==0 && Right==1)==1)
  LEFT();
  else if((Right==0 && Left==1)==1)
  RIGHT();
}

}
void LEFT (void)
{
   analogWrite(mot3,0);
   analogWrite(mot4,30);
   
   
   while(Left==0)
   {
    Left=digitalRead(left);
    Right=digitalRead(right);
    if(Right==0)
    {
      int lprev=Left;
      int rprev=Right;
      STOP();
      while(((lprev==Left)&&(rprev==Right))==1)
      {
         Left=digitalRead(left);
         Right=digitalRead(right);
      }
    }
    analogWrite(mot1,255);
    analogWrite(mot2,0); 
   }
   analogWrite(mot3,255);
   analogWrite(mot4,0);
}

void RIGHT (void)
{
   analogWrite(mot1,0);
   analogWrite(mot2,30);

   while(Right==0)
   {
    Left=digitalRead(left);
    Right=digitalRead(right);
    if(Left==0)
    {
      int lprev=Left;
      int rprev=Right;
     STOP();
      while(((lprev==Left)&&(rprev==Right))==1)
      {
         Left=digitalRead(left);
         Right=digitalRead(right);
      }
    }
    analogWrite(mot3,255);
    analogWrite(mot4,0);
    }
   analogWrite(mot1,255);
   analogWrite(mot2,0);
}
void STOP (void)
{
analogWrite(mot1,0);
analogWrite(mot2,0);
analogWrite(mot3,0);
analogWrite(mot4,0);
  
}

