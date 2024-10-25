#include "DHT.h"
#include<LiquidCrystal.h>

#define TempPin1 A0
#define DHTPIN A1
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // sets the interfacing pins
int Twophase [] = {0x0e, 0x0c, 0x0d, 0x09, 0x0b, 0x03, 0x07, 0x06};
//{0x06,0x07,0x03,0x0b,0x09,0x0d,0x0c,0x0e}
//{0x0e, 0x0c, 0x0d, 0x09, 0x0b, 0x03, 0x07, 0x06}
//{0x0c, 0x09, 0x03, 0x06}
String Message;

//flags
bool motorOn = false;
bool motorClockwise = true;
int step_delay = 100;

int firstCommaIndex;
int secondCommaIndex;
int thirdCommaIndex;
int forthCommaIndex;


String firstValue;
String secondValue;
String thirdValue;
String forthValue;
String fifthValue;

int cycleNumber = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  DDRB = 0xFF;
  Serial.println("AT+CMGF = 1");
  Serial.println("AT+CNMI = 1,2,0,0,0");


}

void loop() {

  int val1;
  val1 = analogRead(TempPin1);

  float LM35_Temperature = ((val1 / 1024.0) * 5000) / 10;
  //float cell = mv1/10;

  Serial.print("AT+CMGF=1");
  Serial.print('\r');//carriage return
  Serial.print('\n');// LineFeed return
  delay(20);
  Serial.print("AT+CMGS=\"01093458458\"");
  Serial.print('\n');

  Serial.print("Temperature=");
  Serial.print(LM35_Temperature);
  Serial.print("^C");

  float DHT_Humidity = dht.readHumidity();
  float DHT_Temperature = dht.readTemperature();

  Serial.print("DHT_Temperature=");
  Serial.print(DHT_Temperature);
  Serial.print("^C");

  Serial.print("DHT_Humidity=");
  Serial.print(DHT_Humidity);
  Serial.print("^C");


  Serial.print((char)26);


  //LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T1=");
    lcd.print(LM35_Temperature);
  
    lcd.print(" T2=");
    lcd.print(DHT_Temperature);
  
    lcd.setCursor(0, 1);
    lcd.print("Humidity=");
    lcd.print(DHT_Humidity);

  //delay (1000);


  //Read_Msg
  while (Serial.available()) {
    Message = Serial.readString();

    firstCommaIndex = Message.indexOf(',');
    secondCommaIndex = Message.indexOf(',', firstCommaIndex + 1);
    thirdCommaIndex = Message.indexOf(',', secondCommaIndex + 1);
    forthCommaIndex = Message.indexOf(',', thirdCommaIndex + 1);

    firstValue = Message.substring(0, firstCommaIndex);
    secondValue = Message.substring(firstCommaIndex + 1, secondCommaIndex);
    thirdValue = Message.substring(secondCommaIndex + 1, thirdCommaIndex);
    forthValue = Message.substring(thirdCommaIndex + 1, forthCommaIndex);
    fifthValue = Message.substring(forthCommaIndex + 1);

    firstValue.trim();
    secondValue.trim();
    thirdValue.trim();
    forthValue.trim();
    fifthValue.trim();
    
    if (firstValue == "010") {

      if (secondValue == "OFF") {
        motorOn = false;
      } else {

        
        if (secondValue == "ON") {
          motorOn = true;
        }
        //      if(secondValue == "OFF"){
        //         motorOn = false;
        //        }

        if (thirdValue == "C") {
          motorClockwise = true;
        }
        if (thirdValue == "ANTIC") {
          motorClockwise = false;
        }

        if (forthValue == "L") {
          step_delay = 150;
        }
        if (forthValue == "H") {
          step_delay = 50;
        }
        cycleNumber = fifthValue.toInt();
      }
    }
  }

  if (motorOn == true) {

    for (int j = 0; j < cycleNumber; j++) {
//      lcd.clear();
//      lcd.print(cycleNumber);
//      lcd.setCursor(0, 1);
//      lcd.print(j);
      if (motorClockwise == true) {
        for (int i = 7; i >= 0; i--) {
          PORTB = Twophase[i];
          delay (step_delay);
        }
      }
      else {
        for (int i = 0; i < 8; i++) {
          PORTB = Twophase[i];
          delay (step_delay);
        }
      }
    }
    cycleNumber = 0;
  }


}
