#include <core_build_options.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <swRTC.h>
#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

//Buzz
const int BuzzPin = 3;

//button
const int button1 = 15;
const int button2 = 16;
const int button3 = 17;
//led
const int led1 =13;
const int led2 =12;
const int led3 =11;
const int led4 =10;
bool led1_status = false;
bool led2_status = false;
bool led3_status = false;
bool led4_status = false;
//Potentionmeter
const int Potentionmeter = 14;

//Temperature Sensor
const int ONE_WIRE_BUS = 19;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//RealTimeClock
swRTC cur_RTC;

void setup() {
  // put your setup code here, to run once:

  Timer1.initialize();
  MFS.initialize(&Timer1);    // initialize multi-function shield library
  MFS.write("Hi--");

  Serial.begin(9600);
  pinMode(BuzzPin, OUTPUT);
  digitalWrite(BuzzPin, HIGH);

  sensors.begin();

  cur_RTC.stopRTC();
  cur_RTC.setTime(00, 00, 00);  //시, 분, 초
  cur_RTC.startRTC();

  pinMode(Potentionmeter, INPUT);
  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  sensors.requestTemperatures();
  float current_Temp = sensors.getTempCByIndex(0);
  int cur_Hour = cur_RTC.getHours();
  int cur_Min = cur_RTC.getMinutes();
  int cur_Sec = cur_RTC.getSeconds();

  float cur_Time = cur_Min + (cur_Sec * 0.01);
  float potValue = pot_map(analogRead(Potentionmeter), 0, 1023, 0, 99);
  if(potValue > 45)
  {
    digitalWrite(BuzzPin, LOW);
  }
  else
  {
    digitalWrite(BuzzPin, HIGH);
  }

  static int button_status = 0;

  if(digitalRead(button1) == 0)
  {
    button_status = 1;
    if (led1_status == false)
    {
      digitalWrite(led1,LOW);
      led1_status = true;
    }
    else
    {
      digitalWrite(led1,HIGH);
      led1_status = false;
    }
    
  }
  else if(digitalRead(button2) == 0)
  {
    button_status = 2; 
    if (led2_status == false)
    {
      digitalWrite(led2,LOW);
      led2_status = true;
    }
    else
    {
      digitalWrite(led2,HIGH);
      led2_status = false;
    }
    
  }
  else if(digitalRead(button3) == 0)
  {
    button_status = 3;
    cur_RTC.setTime(00, 00, 00);//초기화
    if (led3_status == false)
    {
      digitalWrite(led3,LOW);
      led3_status = true;
    }
    else
    {
      digitalWrite(led3,HIGH);
      led3_status = false;
    }
  }

  if ((led1_status ==false)&&(led2_status ==false)&&(led3_status ==false))
  {
    digitalWrite(led4,LOW);
  }
  else
  {
    digitalWrite(led4,HIGH);
  }
  
  if(button_status == 1)
  {
    MFS.write(potValue, 2);  
  }
  else if(button_status == 2)
  {
    MFS.write(cur_Time, 2);
  }
  else if(button_status == 3)
  {
     MFS.write(cur_Time, 2);
  }
}

float pot_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
