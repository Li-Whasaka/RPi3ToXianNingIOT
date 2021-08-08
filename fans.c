#include"myDevices.h"
#include <cjson/cJSON.h>


int fansInit(struct myDevices * p){
	pinMode(p->pinNumber,OUTPUT);
	digitalWrite(p->pinNumber,HIGH);
	strcpy(p->status,"OFF");
}



void fansControl(struct myDevices *p){
	if(p->flag == 0){
		digitalWrite(p->pinNumber,HIGH);
		printf("raspfans close\n");
	}
	if(p->flag == 1){
		printf("raspfans open\n");
		digitalWrite(p->pinNumber,LOW);
	}
}

int readfansMessage(char *str,struct myDevices * p){

	char *sr0=strstr(str,"\"raspfans\":ON");
	char *sr1=strstr(str,"\"raspfans\":OFF");
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

struct myDevices fans= {
	.devicesName = "fans",
	.pinNumber = 28,
	.flag = 0,
	.devicesControl = fansControl,
	.readData = readfansMessage,
	.devicesInit = fansInit
	/*.open = swOpen,
	.close = swClose*/
};


struct myDevices *addFANSToDeviceLink(struct myDevices *phead){
  if(phead==NULL)
    return &fans;
  else{
    fans.next=phead;
    phead=&fans;
  }
  return phead;
}

