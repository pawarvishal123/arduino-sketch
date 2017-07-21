
#include <NewPing.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN  12  
#define ECHO_PIN     11  
#define MAX_DISTANCE 200 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

SoftwareSerial bluetooth(9,8);

Servo myservo;  // create servo object to control a servo

//dc motor
int dir1PinB = 7;
int dir2PinB = 6;
int speedPinB = 5;


int pos = 0;    // variable to store the servo position
char command;

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600); 
    myservo.attach(10); 

  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);

}

void loop() {
  delay(100);                      
  unsigned int uS = sonar.ping(); 
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); 
  Serial.println("cm");

if(bluetooth.available())
{
  
  //read command from bluetooth
  Serial.print("Bluetooth : ");
  command=bluetooth.read();
  Serial.println(command);

  //write distance to bluetooth
  bluetooth.print("Distance: ");
  bluetooth.print(uS / US_ROUNDTRIP_CM); 
  bluetooth.println("cm");
  //read temperature
  int val = analogRead(1);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;
  bluetooth.print("Temp: ");
  bluetooth.print(cel);
  bluetooth.println("*c");
 
  //control servo
  if(command=='1')
  {
  myservo.write(40);
  }
  if(command=='2')
  {
  myservo.write(140);
  }
  if(command=='0')
  {
    myservo.write(90);
  }
  if(command=='3')
  {
    analogWrite(speedPinB, 100);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, HIGH);
    delay(100);
    Serial.print("Motor forward..");
  }
  if(command=='4')
  {
    analogWrite(speedPinB, 100);
    digitalWrite(dir1PinB, HIGH);
    digitalWrite(dir2PinB, LOW);
    delay(100);
    Serial.print("Motor backward..");
  }
  if(command=='5')
  {
    //analogWrite(speedPinB, 100);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, LOW);
    Serial.print("Motor stopped..");
  }
 }
    
}
