int led =5;
int turn_off =0;
String teststr;
int interruptpin = 2;
int interruptpin2 = 3;
unsigned long cnt = 0;
int button=0;
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
  
    if (teststr=="one")
    {
      button=1;
    }
    else if(teststr=="two")
    {
      button=2;
    }
    else if(teststr=="three")
    {
      button=3;
    }
    else if(teststr=="zero")
    {
      button=0;
    }
  }
  if (turn_off ==1)
  {
    off();
    //초기화해주기
    button=0;
    teststr="";
  }
  else
  {
    if (button%4==1)
    {
      button=1;
      
      second();
      
    }
    else if(button%4==2)
    {
      button=2;
      teststr = "";
      halfsecond();
      
    }   
    else if(button%4==3)
    {
      button=3;
      teststr = "";
      full();
      
    }
    else if (button%4==0)
    {
      button=0;
      teststr = "";
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
  delay(1000);
}

void interrupt() //누르는 순간
{
    if(millis()-cnt > 300)
    {
      button++;
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
