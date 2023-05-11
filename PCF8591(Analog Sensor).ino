// 첫번째가 조도
// 두번째 온도
// 세번째가 다이렉트
//네번째가 가변저항
#include "Wire.h"
#define PCF8591 (0x90 >> 1)
#include <LiquidCrystal_I2C.h>  // LiquidCrystal_I2C 헤더파일 호출
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD의 address 주소 및 크기 입력
byte adcvalue0, adcvalue1, adcvalue2, adcvalue3;
int led =13;
void setup()
{
 Wire.begin();
 Serial.begin(9600);
 pinMode(led,OUTPUT);
 lcd.init();  // LCD 초기화
 lcd.backlight();  // LCD 백라이트 함수
}

void loop()
{
 Wire.beginTransmission(PCF8591);
 Wire.write(0x04);
 Wire.endTransmission();
 Wire.requestFrom(PCF8591, 5);

 adcvalue0=Wire.read();
 adcvalue0=Wire.read();
 adcvalue1=Wire.read();
 adcvalue2=Wire.read();
 adcvalue3=Wire.read();

 Serial.print(adcvalue0);
 Serial.print(" ,");
 Serial.print(adcvalue1);
 Serial.print(" ,");
 Serial.print(adcvalue2);
 Serial.print(" ,");
 Serial.print(adcvalue3);
 Serial.println();

 if (adcvalue0 <220){
    digitalWrite(led, LOW);
 }
 else if(adcvalue0 == 255){
    digitalWrite(led,LOW);
 }
 else{
    digitalWrite(led, HIGH);
 }
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("direct:");
 lcd.print(adcvalue2);
 lcd.setCursor(0,1);
 lcd.print("registor:");
 lcd.print(adcvalue3);



 delay(1000);
}
