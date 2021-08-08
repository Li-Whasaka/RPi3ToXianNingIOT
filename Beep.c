#include"myDevices.h"


int BeepInit(struct myDevices * p){
	pinMode(p->pinNumber,OUTPUT);
	digitalWrite(p->pinNumber,HIGH);
	//strcpy(p->status,"OFF");
}



void BeepControl(struct myDevices *p){
	if(p->flag == 0){
		digitalWrite(p->pinNumber,HIGH);
		printf("alarmBeep close\n");
	}
	if(p->flag == 1){
		printf("alarmBeep open\n");
		digitalWrite(p->pinNumber,LOW);
	}
}

int readBeepMessage(char *str,struct myDevices * p){

	char *sr0=strstr(str,"\"alarmBeep\":ON");
	char *sr1=strstr(str,"\"alarmBeep\":OFF");
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

struct myDevices Beep= {
	.devicesName = "Beep",
	.pinNumber = 29,
	.flag = 0,
	.devicesControl = BeepControl,
	.readData = readBeepMessage,
	.devicesInit = BeepInit
	/*.open = swOpen,
	.close = swClose*/
};


struct myDevices *addBeepToDeviceLink(struct myDevices *phead){
  if(phead==NULL)
    return &Beep;
  else{
    Beep.next=phead;
    phead=&Beep;
  }
  return phead;
}

