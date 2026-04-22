//robotická ruka s jednim servem a krokovým motorem

#include <Servo.h>
#include <Stepper.h>

Servo Servo1;

const int Joystick_x = A1;
const int Joystick_y = A0;
const int Joystick_sw = 12;

int hodnotaX;
int hodnotaY;
bool hodnotaSW;

byte pozice = 90; 

const int krokyNaOtacku = 2048; 

Stepper Motor(krokyNaOtacku, 7, 5, 6, 4);

void setup() {

  Serial.begin(9600);

Servo1.attach(9);

Motor.setSpeed(15); 

pinMode(Joystick_x, INPUT);
pinMode(Joystick_y, INPUT);
pinMode(Joystick_sw, INPUT_PULLUP);

}

void loop() {
 hodnotaX =  analogRead(Joystick_x);
 hodnotaY = analogRead(Joystick_y);
 hodnotaSW =  digitalRead(Joystick_sw);

hodnotaX = map(hodnotaX, 0, 1023, 0, 3);


Serial.print("Hodnota X: ");
Serial.print(hodnotaX);
Serial.print(", Hodnota Y: ");
Serial.print(hodnotaY);
Serial.print(", Hodnota SW: ");
Serial.println(!hodnotaSW);


if(hodnotaX == 0 && pozice > 0)
{

  pozice--;
}
if(hodnotaX == 2 && pozice < 180)
{
  pozice++;
}


if (hodnotaY < 400) {
    Motor.step(-10);
  } 
  else if (hodnotaY > 600) {
    Motor.step(10);  
  }

Serial.println("Pozice: ");
Serial.println(pozice);


Servo1.write(pozice);
delay(15);
}
