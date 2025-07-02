// Declare the variables
int buzzer = 2;
int led = 5;
int button = 4;

//LCD
#include <Wire.h>      //To include pre-saved library
#include "rgb_lcd.h"   //To include pre-saved library
rgb_lcd lcd;
const int colorR = 0;  //variables to store the color intensity for red, green and blue respectively
const int colorG = 0;
const int colorB = 0;

//heart rate sensor lib
#define LED 8//indicator, Grove - LED is connected with D4 of Arduino
boolean led_state = LOW;//state of LED, each time an external interrupt 
                                //will change the state of LED
unsigned char counter;
unsigned long temp[21];
unsigned long sub;
bool data_effect=true;
unsigned int heart_rate;//the measurement result of heart rate
const int max_heartpluse_duty = 2000;//you can change it follow your system's request.
                        //2000 meams 2 seconds. System return error 
                        //if the duty overtrip 2 second.
void setup() {
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(button, INPUT);

  Serial.begin(9600);

  lcd.begin(16, 2); //Initiate LCD display into 2 rows and 16 column
  lcd.setRGB(colorR, colorG, colorB);  // Setting the backlit color according to the value store in the variable
}

void loop() {
  if(heart_rate<100){
    void less_than_100();
  }

  else{
    void more_than_100();
  }


}

void less_than_100(){
  lcd.setRGB(0, 255, 0);  // Setting the backlit color according to the value store in the variable

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

void more_than_100(){
  lcd.setRGB(255,0,0);  // Setting the backlit color according to the value store in the variable

  digitalWrite(led, HIGH); 
  digitalWrite(buzzer,HIGH);
  delay(5000);
  digitalWrite(buzzer,LOW);

  //lcd  
  lcd.setCursor(0,0);
  lcd.print("BPM = 101 BPM");
  lcd.setCursor(0,1);
  lcd.print("BPM too HIGH. Stand up and stretch.");
  lcd.setRGB(255, 0, 0); 
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

void sum() {
  if(data_effect) {
    heart_rate=1200000/(temp[20]-temp[0]);//60*20*1000/20_total_time 
    Serial.print("Heart_rate_is:\t");
    Serial.println(heart_rate);
  }
    data_effect=1;//sign bit
}

//Function: Interrupt service routine.Get the sigal from the external interrupt/
void interrupt() {
    temp[counter]=millis();
    Serial.println(counter,DEC);
    Serial.println(temp[counter]);
    switch(counter)
    {
        case 0:
            sub=temp[counter]-temp[20];
            Serial.println(sub);
            break;
        default:
            sub=temp[counter]-temp[counter-1];
            Serial.println(sub);
            break;
    }
    if(sub>max_heartpluse_duty)//set 2 seconds as max heart pluse duty
    {
        data_effect=0;//sign bit
        counter=0;
        Serial.println("Heart rate measure error,test will restart!" );
        arrayInit();
    }
    if (counter==20&&data_effect)
    {
        counter=0;
        sum();
    }
    else if(counter!=20&&data_effect)
    counter++;
    else 
    {
        counter=0;
        data_effect=1;
    }    
}

//Function: Initialization for the array(temp)/

void arrayInit() {
    for(unsigned char i=0;i < 20;i ++)
    {
        temp[i]=0;
    }
    temp[20]=millis();
}