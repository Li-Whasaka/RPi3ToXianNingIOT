#include"myDevices.h"
#include <cjson/cJSON.h>


int led1Init(struct myDevices * p){
	pinMode(p->pinNumber,OUTPUT);
	digitalWrite(p->pinNumber,HIGH);
	strcpy(p->status,"OFF");
}


void led1Control(struct myDevices *p){
	if(p->flag == 0){
		digitalWrite(p->pinNumber,HIGH);
		printf("led1 close\n");
	}
	if(p->flag == 1){
		printf("led1 open\n");
		digitalWrite(p->pinNumber,LOW);
	}
}

int readled1Message(char *str,struct myDevices * p){
	if(!str)
		return -1;
	char *sr0=strstr(str,"\"raspled1\":ON");
	char *sr1=strstr(str,"\"raspled1\":OFF");
	if(sr0){
		p->flag = 1;
		strcpy(p->status,"ON");
	}
	if(sr1){
		p->flag = 0;
		strcpy(p->status,"OFF");
	}
	p->devicesControl(p);
	return 0;
}

struct myDevices led1 = {
	.devicesName = "led1",
	.pinNumber = 4,
	.flag = 0,
	.devicesControl = led1Control,
	.readData = readled1Message,
	.devicesInit = led1Init
	/*.open = swOpen,
	.close = swClose*/
};


struct myDevices *addLED1ToDeviceLink(struct myDevices *phead){
  if(phead==NULL)
    return &led1;
  else{
    led1.next=phead;
    phead=&led1;
  }
  return phead;
}
