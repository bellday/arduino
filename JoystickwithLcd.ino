 /*
   텍스트LCD 사용을 위해 LiquidCrystal.h 헤더 파일을 include 한다.
*/
#include <LiquidCrystal_I2C.h>  // LiquidCrystal_I2C 헤더파일 호출
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD의 address 주소 및 크기 입력
/*
  각 핀 정의
*/
int joystick_x = 0;
int joystick_y = 1;
int loc_x ,loc_y ,loc_nx ,loc_ny=0;
void Clcd_display(long data, long data2) // 텍스트 LCD 디스플레이 함수
{
  

  Serial.println((String)" test_display : " +  data +(String) " "  +data2);
   // LCD 문자출력 시작(열,행)라인 설정
  if ((data >= 600)&&(loc_x == 0))
  {
    loc_nx = loc_x+1;
  }
  else if((data<=400)&&(loc_x == 1))
  {
    loc_nx = loc_x-1;
  }
  

  if ((data2 >= 600) && (loc_ny>=0) && (loc_ny<16))
  {
    loc_ny = loc_y+1;
  }
  else if((data2 <= 400) && (loc_ny>=0) && (loc_ny<16))

  {
    loc_ny = loc_y-1;
  }
  if (loc_ny == -1)
    { 
    loc_ny =loc_ny+1;
    }
  else if(loc_ny ==16)
  {
    loc_ny= loc_ny -1;
  }
  loc_y=loc_ny;
  loc_x=loc_nx;
  lcd.setCursor(loc_y, loc_x);
  
  Serial.println((String) " RST" + loc_y +loc_x);
  lcd.print(".");
}
void setup() // 초기화
{
  lcd.init();  // LCD 초기화
  lcd.backlight();  // LCD 백라이트 함수
	pinMode(7, INPUT_PULLUP);
    Serial.begin(115200);
}
/*
   조이스틱을 전, 후, 좌, 우 사용자가 이동하였을 경우 아두이노보드에서 이를 인지하여
   측정 된 X, Y축값을 텍스트LCD에 출력하도록 한다
*/
void loop() // 무한루프
{
  lcd.clear();
  int x = analogRead(joystick_x);      // 조이스틱 X축의 아날로그 신호를 x에 저장
  int y = analogRead(joystick_y);      // 조이스틱 Y축의 아날로그 신호를 y에 저장
  Clcd_display(x, y);
  
   delay(100);                                // 100ms만큼 지연
    int pinStatus =	digitalRead(7);
    Serial.println(pinStatus);
    if (pinStatus==0){
        lcd.setCursor(0,0);
        lcd.print("switch on");
        delay(1000);
    }
}
