#include"myDevices.h"

#define SHOCK_LED 26
int shockInit(struct myDevices * p){
	pinMode(p->pinNumber,INPUT);
	digitalWrite(p->pinNumber,LOW);
	pinMode(SHOCK_LED,OUTPUT);
	digitalWrite(SHOCK_LED,HIGH);
}

void shockControl(struct myDevices *p){
	if(p->flag == 1){
		digitalWrite(SHOCK_LED,LOW);
	}
	if(p->flag == 0){
		digitalWrite(SHOCK_LED,HIGH);
	}
}

int ifShock(struct myDevices * p){
	if(digitalRead(p->pinNumber) == 1){
		printf("车辆晃动，请减速慢行\n");
		p->flag = 1;
		strcpy(p->status,"ON");
	}
	else{
		printf("车辆行驶平稳\n");
		p->flag = 0;
		strcpy(p->status,"OFF");
	}
	p->devicesControl(p);
	printf("ifShockifShock\n");
	return 0;
}

struct myDevices shock = {
	.devicesName = "shock",
	.pinNumber = 2,
	.flag = 0,
	.devicesInit = shockInit,
	.getData = ifShock,
	.devicesControl = shockControl
	/*.open = swOpen,
	.close = swClose*/
};

struct myDevices *addShockSensorToDeviceLink(struct myDevices *phead){
  if(phead == NULL)
    return &shock;
  else{
    shock.next = phead;
    phead = &shock;
  }
  return phead;
}