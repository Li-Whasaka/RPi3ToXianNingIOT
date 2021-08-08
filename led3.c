#include"myDevices.h"
#include <cjson/cJSON.h>


int led3Init(struct myDevices * p){
	pinMode(p->pinNumber,OUTPUT);
	digitalWrite(p->pinNumber,HIGH);
	strcpy(p->status,"OFF");
}



void led3Control(struct myDevices *p){
	if(p->flag == 0){
		digitalWrite(p->pinNumber,HIGH);
		printf("led3 close\n");
	}
	if(p->flag == 1){
		printf("led3 open\n");
		digitalWrite(p->pinNumber,LOW);
	}
}

int readled3Message(char *str,struct myDevices * p){

	char *sr0=strstr(str,"\"raspled3\":ON");
	char *sr1=strstr(str,"\"raspled3\":OFF");
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

struct myDevices led3= {
	.devicesName = "led3",
	.pinNumber = 6,
	.flag = 0,
	.devicesControl = led3Control,
	.readData = readled3Message,
	.devicesInit = led3Init
	/*.open = swOpen,
	.close = swClose*/
};


struct myDevices *addLED3ToDeviceLink(struct myDevices *phead){
  if(phead==NULL)
    return &led3;
  else{
    led3.next=phead;
    phead=&led3;
  }
  return phead;
}

