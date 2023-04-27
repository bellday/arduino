int led =5;
int turn_off =0;
String teststr;
int interruptpin = 2;
int interruptpin2 = 3;
unsigned long cnt = 0;
void setup(){
    pinMode(led,OUTPUT);
    pinMode(interruptpin, INPUT_PULLUP);
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(interruptpin), interrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(interruptpin2), interrupt2, RISING);

}

void loop(){
  //Serial.println("Enter data:");
  if (Serial.available() != 0) 
  {     //wait for data available
  

  
  teststr = Serial.readString();  //read until timeout

  teststr.trim(); //띄어쓰기 제거
  
  }
  if (turn_off ==1)
  { //turn_off 변수가 1일 경우 led 전원 off
    off();
    
  }
  else
  { //turn_off 변수가 1이 아닐경우 led전원을 제어 시작
    if (teststr=="one")
    {
      //Serial.println("1");
      second();
    }
    else if(teststr == "two")
    {
      //Serial.println("2");
      halfsecond();
    }   
    else if(teststr == "three")
    {
      //Serial.println("3");
      full();
    }
    else if (teststr == "zero")
    {
      off();
    }
  }
}


void second() //1초마다 깜빡
{
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
}
void halfsecond() //0.1초마다 깜빡
{
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
}
void full() //켜져있는 상태
{
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1);
}
void off(){
  digitalWrite(led, LOW);
  delay(1);
}

void interrupt() //누르는 순간
{
    if(millis()-cnt > 150) 
    {
        //Serial.println(cnt);

        
        
    }
    cnt = millis();
}
void interrupt2() //떼는 순간
{
    if(millis()-cnt > 2000)
    {
        if (turn_off==0)
        {
          turn_off=1; 
        }
        else
        {
          turn_off=0;
        }
    }
}
