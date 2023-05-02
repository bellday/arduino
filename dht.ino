long levelTimeout = 500000; // 500ms
uint8_t bitmask = 0xFF;
uint8_t port = 0xFF;
int pin = 7;
void setup()
{
    Serial.begin(115200);
}

void loop()
{
    byte temperature = 0;
    byte humidity = 0;

    read(&temperature, &humidity);
    Serial.println((String)"Temperature : " + temperature +(String)" Celsius" );
    Serial.println((String)"Humidity: " +humidity + (String)"%" );

    delay(1000);
}

int read(byte *temperature, byte *humidity)
{
    int ret = 0;
    bitmask = digitalPinToBitMask(pin);
    port = digitalPinToPort(pin);
    int temp_sum=0;
    int humid_sum =0;
    int devide_num=128;
    int devide_num2=128;
    byte data[40] = {0};
    sample(data);

    // 받은 data 처리
    for (size_t i = 0; i < 40; i++)
    {
        //Serial.println((int) i +(String) " : " +data[i]);
        if((i>=0)&&(i<=7)){
            humid_sum=humid_sum+(data[i]*devide_num);
            devide_num=devide_num/2;
        }
        
        if((i>=16)&&(i<=23)){
            temp_sum=temp_sum+(data[i]*devide_num2);
            devide_num2=devide_num2/2;
        }
    }
    //Serial.println();

    *temperature = temp_sum;
    *humidity = humid_sum;
}
int sample(byte data[40])
{
    memset(data, 0, 40);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(20);
    //
    digitalWrite(pin, HIGH);
    pinMode(pin, INPUT);
    delayMicroseconds(25);

    long t = levelTime(LOW, 10, 6);
    if (t < 30)
    {
        // return -1;
    }
    t = levelTime(HIGH, 10, 6);
    if (t < 50)
    {
        // return -1;
    }

    for (size_t i = 0; i < 40; i++)
    {
        t = levelTime(LOW, 10, 6);
        if (t < 24)
        {
            // return -1;
        }
        t = levelTime(HIGH, 10, 6);
        if (t < 11)
        {
            // return -1;
        }
        data[i] = (t > 40 ? 1 : 0);
    }

    t = levelTime(LOW, 10, 6);
    if (t < 24)
    {
        return -1;
    }
    return 0;
}

long levelTime(byte level, int firstWait, int interval)
{
    unsigned long time_start = micros();
    long time = 0;


    uint8_t portState = level ? bitmask : 0;

    bool loop = true;
    for (int i = 0; loop; i++)
    {
        if (time < 0 || time > levelTimeout)
        {
            return -1;
        }

        if (i == 0)
        {
            if (firstWait > 0)
            {
                delayMicroseconds(firstWait);
            }
        }
        else if (interval > 0)
        {
            delayMicroseconds(interval);
        }
        time = micros() - time_start;

        // low상태에서 high 상태로 변할때 빠져 나가는 것
        loop = ((*portInputRegister(port) & bitmask) == portState);
    }

    return time;
}
