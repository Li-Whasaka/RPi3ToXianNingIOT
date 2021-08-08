#include"myDevices.h"
uint32 databuf;
int readSensorData(char * str,struct myDevices* p)
{
    uint8 crc;
    uint8 i;

    pinMode(p->pinNumber, OUTPUT); // set mode to output
    digitalWrite(p->pinNumber, 1); // output a high level

    pinMode(p->pinNumber,OUTPUT); // set mode to output
    digitalWrite(p->pinNumber, 1); // output a low level
    delayMicroseconds(4);
    digitalWrite(p->pinNumber, 0); // output a high level
    delay(25);
    digitalWrite(p->pinNumber, 1); // output a low level
    delayMicroseconds(60);

    pinMode(p->pinNumber, INPUT); // set mode to input
    pullUpDnControl(p->pinNumber,PUD_UP);

    if(digitalRead(p->pinNumber)==0) //SENSOR ANS
    {
        while(!digitalRead(p->pinNumber)); //wait to high
        delayMicroseconds(80);
        for(i=0;i<32;i++)
        {
          while(digitalRead(p->pinNumber)); //data clock start
          while(!digitalRead(p->pinNumber)); //data start

          delayMicroseconds(HIGH_TIME);
          databuf*=2;
          if(digitalRead(p->pinNumber)==1) //1
          {
            databuf++;
          }
        }

        for(i=0;i<8;i++)
        {
          while(digitalRead(p->pinNumber)); //data clock start
          while(!digitalRead(p->pinNumber)); //data start
          delayMicroseconds(HIGH_TIME);
          crc*=2;
          if(digitalRead(p->pinNumber)==1) //1
          {
            crc++;
          }
        }


        //printf("readSensorData2\n");
      return 1;
    }
    else
    {
      return 0;
    }
}


int get_temp_humidity(struct myDevices *p){
  pinMode(p->pinNumber,OUTPUT); // set mode to output
  digitalWrite(p->pinNumber, 1); // output a high level
  delay(100);
  int fd=p->readData(NULL,p);
  if(fd)
  {
    p->flag=1;
    char buf[128];
    printf("DHT11 Acquisition successful!\n");
    sprintf(buf,"%d.%d",(databuf>>24)&0xff,(databuf>>16)&0xff);
    p->humidity=atof(buf);
    memset(buf,'\0',128);
    sprintf(buf,"%d.%d",(databuf>>8)&0xff,databuf&0xff);
    p->temperature=atof(buf);
    memset(buf,'\0',128);
    databuf=0;
  }
  else{
    p->flag=0;
    printf("Error!\n");
    databuf=0;
  }
  return 0;
}

struct myDevices dht11={
  .devicesName="dht11",
  .pinNumber=1,
  .flag=1,
  .humidity=0,
  .temperature=0,
  .readData=readSensorData,
  .getData=get_temp_humidity
};

struct myDevices *addDht11ToDeviceLink(struct myDevices *phead){
  if(phead==NULL)
    return &dht11;
  else{
    dht11.next=phead;
    phead=&dht11;
  }
  return phead;
}