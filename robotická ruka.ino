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










//alternativa jen na joystick sečtení surových hodnot z joysticku
#include <Servo.h>

Servo Servo1;
byte pozice = 90;

int Y = A1;
int hodnotaY;
int X = A0;
int hodnotaX;
// ZMĚNA: Tlačítko přesunuto na pin 2, aby nekolidovalo se servem na pinu 9
int SW = 2; 
int hodnotaSW;

void setup() {
  // pinMode(8, OUTPUT); // Pokud k pinu 8 nic nemáš, tohle není potřeba
  pinMode(Y, INPUT);
  pinMode(X, INPUT);
  pinMode(SW, INPUT_PULLUP);

  Servo1.attach(9);      // Servo je připojeno na pin 9
  Servo1.write(pozice);  // Pošleme servo do výchozí pozice (90 stupňů)

  Serial.begin(9600);
}

void loop() {
  hodnotaX = analogRead(X);
  hodnotaY = analogRead(Y);
  hodnotaSW = digitalRead(SW);

  // ZMĚNA: Místo mapování použijeme hrubé hodnoty. Střed je cca 512.
  // Pokud pohneme joystickem na jednu stranu (hodnota klesne pod 400)
  if(hodnotaX < 400 && pozice > 0) {
    pozice--;
  }
  
  // Pokud pohneme joystickem na druhou stranu (hodnota stoupne nad 600)
  if(hodnotaX > 600 && pozice < 180) {
    pozice++;
  }

  // OPRAVA: Tento příkaz chyběl! Skutečně fyzicky pohne servem na novou pozici.
  Servo1.write(pozice);

  // OPRAVA: Krátká pauza, aby mělo servo čas na přejezd a pohyb byl plynulý.
  // Změnou tohoto čísla (např. 10 až 30) můžeš zrychlovat nebo zpomalovat pohyb serva.
  delay(15); 
}
