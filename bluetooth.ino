#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX) 형식으로 블루투스 모듈과 교차하여 연결
SoftwareSerial BTSerial(4, 5);
int led = 13;
char teststr = ' ', teststr2 = ' '; // 변수 초기화

void setup() {
  Serial.begin(9600); // 컴퓨터와의 시리얼 통신 초기화
  BTSerial.begin(9600); // 블루투스 모듈 초기화
  pinMode(led, OUTPUT);
}

void loop() {

  // 블루투스 모듈 → 아두이노 → 시리얼 모니터
  if (BTSerial.available()) {
    teststr = BTSerial.read();
    Serial.write(teststr); // 블루투스 모듈로부터 받은 데이터 시리얼 모니터에 출력

    if (teststr == 'o') {
      digitalWrite(led, HIGH);
    }
    else if (teststr == 'f') {
      digitalWrite(led, LOW);
    }
    
  }
  

  // 시리얼 모니터 → 아두이노 → 블루투스 모듈
  if (Serial.available()) {
    teststr2 = Serial.read();
    BTSerial.write(teststr2); // 시리얼 모니터로부터 받은 데이터 블루투스 모듈로 전송

  }
}
