int buzzer = 4;
int led = 5;
int button = 2;

//LCD
#include <Wire.h>      //To include pre-saved library
#include "rgb_lcd.h"   //To include pre-saved library
rgb_lcd lcd;
const int colorR = 0;  //variables to store the color intensity for red, green and blue respectively
const int colorG = 255;
const int colorB = 0;

void setup() {
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(button, INPUT);

  Serial.begin(9600);

  lcd.begin(16, 2); //Initiate LCD display into 2 rows and 16 column
  lcd.setRGB(colorR, colorG, colorB);  // Setting the backlit color according to the value store in the variable
}

void loop() {
  digitalWrite(led, HIGH); 
  digitalWrite(buzzer,LOW);

  //lcd  
  lcd.setCursor(0,0);
  lcd.print("BPM = 92");
  lcd.setCursor(0,1);
  lcd.print("Your heart rate is NORMAL. Keep It Up!");
  lcd.setRGB(0, 255, 0); 
  delay(2000);

  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(150);
  }  

  while (digitalRead(button) == HIGH) {
    digitalWrite(led, LOW);
    delay(10000000);
  }
}
