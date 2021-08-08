#include"myDevices.h"
#include <cjson/cJSON.h>


int swInit(struct myDevices * p){
	pinMode(p->pinNumber,OUTPUT);
	digitalWrite(p->pinNumber,HIGH);
	strcpy(p->status,"OFF");
}

int readMessage(char *str,struct myDevices * p){

	char *sr0=strstr(str,"\"testLED\":ON");
	char *sr1=strstr(str,"\"testLED\":OFF");
	if(sr0){
		p->flag = 1;
		strcpy(p->status,"OFF");
	}
	if(sr1){
		p->flag = 0;
		strcpy(p->status,"OFF");
	}

	return 0;
}

void swControl(struct myDevices *p){
	if(p->flag == 0){
		digitalWrite(p->pinNumber,HIGH);
		printf("switch close\n");
	}
	if(p->flag == 1){
		printf("switch open\n");
		digitalWrite(p->pinNumber,LOW);
	}
}

struct myDevices sw = {
	.devicesName = "sw",
	.pinNumber = 7,
	.flag = 0,
	.devicesControl = swControl,
	.readData = readMessage,
	.devicesInit = swInit
	/*.open = swOpen,
	.close = swClose*/
};


struct myDevices *addSwitchToDeviceLink(struct myDevices *phead){
  if(phead==NULL)
    return &sw;
  else{
    sw.next=phead;
    phead=&sw;
  }
  return phead;
}
