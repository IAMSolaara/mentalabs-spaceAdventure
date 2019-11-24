#include <LiquidCrystal.h>

//analog pins
#define JOYV A0
#define JOYH A1

//digital pins
#define BTN 5

LiquidCrystal lcd(2,3,4,6,7,8,9,10,11,12,13);

float x = 14;
float y = 1;

float dir = 1;

void setup(){
  pinMode(BTN, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
   lcd.print("Please come to");
  lcd.setCursor(0,1);
  lcd.print("brazil.");
}

void loop(){
  int xAxis = analogRead(JOYH);
  int yAxis = analogRead(JOYV);

//DEADZONE
  if ((xAxis < 0x220 && xAxis > 0x200) || (yAxis < 0x220 && yAxis > 0x200)) Serial.println("DEADZONE");

//RIGHT
  if (xAxis < 0x320 && xAxis > 0x220) {x += 0.5; dir = 1;}
  else if (xAxis > 0x320) {x += 1; dir = 1;}


//DOWN
  else if (yAxis < 0x300 && yAxis > 0x220) y += 0.5;
  else if (yAxis > 0x300) y += 1;


//LEFT
  if (xAxis < 0x200 && xAxis > 0x180) {x -= 0.5; dir = -1;}
  else if (xAxis < 0x180) {x -= 1; dir = -1;}


//UP
  if (yAxis < 0x200 && yAxis > 0x180) y -= 0.5;
  else if (yAxis < 0x180) y -= 1;

  y = 1;

  lcd.clear();

  lcd.setCursor((int)x, (int)y);
  lcd.print("#");

  if (digitalRead(BTN)) doShoot();
   
  delay(100);
}

void doShoot() {
  for (int i = 1; i < 5; i++) {
    lcd.setCursor( (int)x + (i * dir), (int)y);
    lcd.print("-");
    delay(200);
  }  
}
