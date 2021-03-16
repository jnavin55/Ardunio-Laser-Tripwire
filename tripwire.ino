#include <LiquidCrystal.h>

#define sensor 12
#define button 9
#define speaker 13
#define led1 10
#define led2 11

LiquidCrystal lcd(3,4,5,6,7,8);

int sensorVal = LOW;
int buttonVal = LOW;
int buttonSet = LOW;
bool clearBool = true;
bool intBool = true;
bool ledBool = false;

void setup() {
  pinMode(sensor,INPUT);
  pinMode(button,INPUT);
  pinMode(speaker,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  lcd.begin(16,1);
}

void loop() {
  buttonVal = digitalRead(button);
  if(buttonVal == HIGH){
    if(buttonSet == LOW){
      buttonSet = HIGH;
    } else {
      buttonSet = LOW;
    }
  }
  
  sensorVal = digitalRead(sensor);
  if(sensorVal == buttonSet){
    allClear();
  } else {
    intruder();
  }
  delay(200);
}

void allClear(){
  intBool = true;
  if (clearBool){
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    lcd.clear();
    lcd.print("All Clear");
    noTone(speaker);
  } 
  clearBool = false;
}

void intruder(){
  clearBool = true;
  if (intBool){
    lcd.clear(); 
    lcd.print("Intruder Alert!");
  }
  if(ledBool){
    ledBool = false;
    tone(speaker,2000);
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
  } else {
    ledBool = true;
    tone(speaker,1000);
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
  }
  intBool = false;
}
