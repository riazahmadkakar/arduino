#include <DHT.h>//DHT sensor Library
#include <LiquidCrystal.h>//LCD Library 
#define DHTPIN A0 //Define sensor pin(pin 12)
#define DHTTYPE DHT11 //What sensor use
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
RTC_DS1307 RTC;

DHT dht(DHTPIN, DHTTYPE);//Create sensor object
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);//Create lcd object using this pins 8,9,4,6,7

boolean a=LOW,b=HIGH;
float h=0,t=0;
const int ledPin = 3; //LED pins for temperature control 
const int ledPin2 = 2;
long previousMillis = 0;
long interval = 500; //Read sensor each 2 seconds

void setup() {
lcd.begin(16, 2);              //Start lcd 
lcd.setCursor(0,0);            //Set in position 0,0
// set the digital pin as output:
pinMode(ledPin, OUTPUT);//Change to output my pins
pinMode(ledPin2, OUTPUT);
dht.begin();//Start DHT22 sensor
digitalWrite(ledPin2,LOW);//Turn off LED
digitalWrite(ledPin,LOW);//Turn off LED
lcd.print("    BUETK  FYP");// print in lcd this word 
lcd.setCursor(0,1);//Change cursor position
lcd.print("Temp  maint system");// print in lcd this word 
Serial.begin(9600);
Wire.begin();
RTC.begin();


pinMode(8,OUTPUT);

if (! RTC.isrunning()) {
Serial.println("RTC is NOT running!");
// following line sets the RTC to the date & time this sketch was compiled
RTC.adjust(DateTime(__DATE__, __TIME__));
}
}

void loop()
{
  unsigned long currentMillis = millis();//time elapsed
  if(currentMillis - previousMillis > interval) //Comparison between the elapsed time and the time in which the action is to be executed
  {
    previousMillis = currentMillis; //"Last time is now"

     h = dht.readHumidity();//humidity value
     t = dht.readTemperature();//temperature value centigrades if you want farenheit change to
     t = dht.readTemperature(true);
     //Below is for print data sensors in lcd 
     lcd.setCursor(0,0);//Change cursor position
     lcd.print("Temp:");// print in lcd this word 
     lcd.setCursor(0,1);//Change cursor position
     lcd.print("Hum:");// print in lcd this word 
     lcd.setCursor(10,0);
     lcd.print(t);
     lcd.setCursor(10,1);
     lcd.print(h);
    
    if(h>=6)//if temperature above of 6 degrees
    {
      digitalWrite(ledPin,HIGH);//Active air conditioner
      digitalWrite(ledPin2,LOW);
      a=HIGH;
      b=LOW;
     
    }
    else if(h<6)//if temperature is under 6 degrees
    {
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin,LOW);//Turn off air conditioner
      a=LOW;
      b=HIGH;
    }
    
  }
 delay(3000); 
 lcd.clear();
  DateTime now = RTC.now();
lcd.setCursor(0,0);//Change cursor position
lcd.print("date:");  
lcd.setCursor(10, 0);
lcd.print(now.day(), DEC);
lcd.print('/');
lcd.print(now.month(), DEC);
lcd.print('/');
lcd.print(now.year(), DEC);
lcd.print(' ');
lcd.setCursor(0,1);//Change cursor position
lcd.print("time:");
lcd.setCursor(8, 1);
if (now.hour()<10)
lcd.print('0');
lcd.print(now.hour(), DEC);
lcd.print(':');
if (now.minute()<10)
lcd.print('0');
lcd.print(now.minute(), DEC);
lcd.print(':');
if (now.second()<10)
lcd.print('0');
lcd.print(now.second(), DEC);
delay(1000);
lcd.clear();
}
