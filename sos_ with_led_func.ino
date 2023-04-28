int led =5;
int turn_off =0;
String teststr;
int interruptpin = 2;
int interruptpin2 = 3;
unsigned long cnt = 0;
unsigned long now;
unsigned long sos_past=0;
unsigned long led_past=0;
int button=0;
bool ledStatus = false;
bool sos_status = false;
bool sos_signal = false;
int  c;
int num =400;
void setup(){
    pinMode(led,OUTPUT);
    pinMode(interruptpin, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(interruptpin), interrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(interruptpin2), interrupt2, RISING);

}

void loop(){
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
    else if (teststr=="sos")
    {   
        sos_status=!sos_status;
        
    }
    else
    {}
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
    if ((teststr=="one") or (button%4==1))
    {
      button=1;
      teststr="";
      second();
    }
    else if((teststr == "two")or (button%4==2))
    {
      button=2;
      teststr= "";
      halfsecond();
    }   
    else if((teststr == "three")or (button%4==3))
    {
      button=3;
      teststr = "";
      full();
    }
    else if ((teststr == "zero")or (button%4==0))
    {
      button=0;
      teststr = "";
      off();
    }
    if (sos_status==true)
    {
        if (0 <= c && c < 6)
        {
            hit(num);
            
            
        }
        else if (6 <= c && c < 12)
        {
            hit(num*2);
            
            
        }
        else if (12 <= c && c < 18)
        {
            hit(num);
            
        }
        
        else if (c==18)
        {
            c=0;
            Serial.println(c);
            sos_status=false;
        }
    }
  }
}


void second() //1초마다 깜빡
{
    now=millis();
    if (now - led_past >=1000){
        led_past = now;
        ledStatus = !ledStatus;
        digitalWrite(led, ledStatus ? HIGH : LOW);
    }
}
void halfsecond() //0.1초마다 깜빡
{
    now=millis();
    if (now - led_past >=300){
        led_past = now;
        ledStatus = !ledStatus;
        digitalWrite(led, ledStatus ? HIGH : LOW);
    }
}
void full() //켜져있는 상태
{
    digitalWrite(led, HIGH);
}
void off(){
  digitalWrite(led, LOW); 
}

void interrupt() //누르는 순간
{
    if(millis()-cnt > 150)
    {
      button++;
      Serial.println(button);
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

void hit(int num)
{
     now=millis();
        if(now-sos_past>num)
        {
            Serial.println(num);
            sos_past=now;
            sos_signal=!sos_signal;
            digitalWrite(LED_BUILTIN, sos_signal? HIGH:LOW);
            c++;
            Serial.println(c);
        }
}
