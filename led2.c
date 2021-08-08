#include"myDevices.h"
#include <cjson/cJSON.h>


int led2Init(struct myDevices * p){
	pinMode(p->pinNumber,OUTPUT);
	digitalWrite(p->pinNumber,HIGH);
	strcpy(p->status,"OFF");
}


void led2Control(struct myDevices *p){
	if(p->flag == 0){
		digitalWrite(p->pinNumber,HIGH);
		printf("led2 close\n");
	}
	if(p->flag == 1){
		printf("led2 open\n");
		digitalWrite(p->pinNumber,LOW);
	}
}

int readled2Message(char *str,struct myDevices * p){

	char *sr0=strstr(str,"\"raspled2\":ON");
	char *sr1=strstr(str,"\"raspled2\":OFF");
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

struct myDevices led2= {
	.devicesName = "led2",
	.pinNumber = 5,
	.flag = 0,
	.devicesControl = led2Control,
	.readData = readled2Message,
	.devicesInit = led2Init
	/*.open = swOpen,
	.close = swClose*/
};


struct myDevices *addLED2ToDeviceLink(struct myDevices *phead){
  if(phead==NULL)
    return &led2;
  else{
    led2.next=phead;
    phead=&led2;
  }
  return phead;
}

