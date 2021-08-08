//
//mydht11.c
//
#pragma once

#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;

#define HIGH_TIME 32

struct myDevices{
	char devicesName[128];
	int pinNumber;
	int flag;
	char status[16];
	int humidity;
	int temperature;

	void (*devicesControl)(struct myDevices *p);
	int (*devicesInit)(struct myDevices * p);
	int (*readData)(char * str,struct myDevices * p);
	int (*getData)(struct myDevices * p);
	int (*open)(struct myDevices * p);
	int (*close)(struct myDevices * p);
	struct myDevices *next;
};

//int pinNumber = 1;  //use gpio1 to read data
uint32 databuf;

/*uint8 readData();
void get_temp_humidity();*/

//struct myDevices* findDevicesByName(const char *name,struct myDevices* phead);

struct myDevices* findDevicesByName(const char *name,struct myDevices* phead);

struct myDevices *addDht11ToDeviceLink(struct myDevices *phead);
struct myDevices *addSwitchToDeviceLink(struct myDevices *phead);
struct myDevices *addShockSensorToDeviceLink(struct myDevices *phead);
struct myDevices *addLED1ToDeviceLink(struct myDevices *phead);
struct myDevices *addLED2ToDeviceLink(struct myDevices *phead);
struct myDevices *addLED3ToDeviceLink(struct myDevices *phead);
struct myDevices *addBeepToDeviceLink(struct myDevices *phead);
struct myDevices *addFANSToDeviceLink(struct myDevices *phead);

