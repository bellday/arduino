
#include <LiquidCrystal_I2C.h>  // LiquidCrystal_I2C 헤더파일 호출
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD의 address 주소 및 크기 입력

void setup()
{
    Serial.begin(115200); //통신을 위하여 사용
    lcd.init();  // LCD 초기화
    lcd.backlight();  // LCD 백라이트 함수
}

void loop()
{
    String hour,h,m;
    int hours, min;
    int first;
    int MinuteAngle = 0;
    float hourAngle = 0;
    float answer;
    if (Serial.available() != 0)
    {
        hour = Serial.readString();
        int leng = hour.length();
        Serial.println(hour);
        first = hour.indexOf(":");
        h= hour.substring(0,first);
        m= hour.substring(first+1,leng);
        //Serial.println(leng + (String) " " + first + (String) " " + h +(String) " " + m);
        
        hours = h.toInt();
        min= m.toInt();
        MinuteAngle = min * 6;
        hourAngle = (hours*60 + min) * 0.5;
        if (hourAngle >= 360){
            hourAngle = hourAngle - 360;
        }
        //Serial.println((String) "Min" + MinuteAngle);
        //Serial.println(hourAngle);

        if (hourAngle > MinuteAngle){
            if ((hourAngle - MinuteAngle)>180)
            {
                answer =  360 - (hourAngle - MinuteAngle);
                Serial.println((String) "Angle : " + abs(answer));
                lcd.setCursor(0,0);
                lcd.print("Time:");
                lcd.print(hour);
                lcd.setCursor(0,1);
                lcd.print("Angle:");
                lcd.print(abs(answer));
            }
            else
            {
                answer = hourAngle - MinuteAngle;
                Serial.println((String) "Angle : " + abs(answer));
                lcd.setCursor(0,0);
                lcd.print("Time:");
                lcd.print(hour);
                lcd.setCursor(0,1);
                lcd.print("Angle:");
                lcd.print(abs(answer));
            }
        }
        else
        {
            if ((MinuteAngle - hourAngle)>180)
            {
                answer =  360 - (MinuteAngle - hourAngle);
                Serial.println((String) "Angle : " + abs(answer));
                lcd.setCursor(0,0);
                lcd.print("Time:");
                lcd.print(hour);
                lcd.setCursor(0,1);
                lcd.print("Angle:");
                lcd.print(abs(answer));
            }
            else
            {
                answer =  MinuteAngle - hourAngle;
                Serial.println((String) "Angle : " + abs(answer));
                lcd.setCursor(0,0);
                lcd.print("Time:");
                lcd.print(hour);
                lcd.setCursor(0,1);
                lcd.print("Angle:");
                lcd.print(abs(answer));
            }
        }
    }
    
}
