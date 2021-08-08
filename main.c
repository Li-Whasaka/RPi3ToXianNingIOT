#include "myMqtt.h"
#include "myDevices.h"

struct myDevices* pheadDevices;
struct myDevices *dht11Handler = NULL;
struct myDevices *shockHandler = NULL;
struct myDevices *switchHandler = NULL;
struct myDevices *fansHandler = NULL;
struct myDevices *BEEP = NULL;
struct myDevices *LED1 = NULL;
struct myDevices *LED2 = NULL;
struct myDevices *LED3 = NULL;


struct mosquitto *OH_mosq =NULL;
mosquitto_t OH_mosquitto;

static int running = 1;

void piSetup(){
  while(wiringPiSetup()==-1){
      printf("Setup wiringPi failed!");
      sleep(2);
  }
}

struct myDevices* findDevicesByName(const char *name,struct myDevices* phead){
    struct myDevices *tmp=phead;
    if(phead == NULL){
        printf("no devices ###phead\n");
        return NULL;
    }
    while(tmp){
        if(strcmp(tmp->devicesName,name)==0)//deviceName
            return tmp;
        tmp=tmp->next;
    }
    return NULL;
}

void myPublish_disconnect_callback(struct mosquitto *mosq, void *obj, int rc){
    printf("Call the function: myPublish_disconnect_callback\n");
    running = 0;
}



void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message){
	if(message->payloadlen){
        char * str = (char *)(message->payload);
        printf("\ntopic:%s\n message_callback_payload:\n%s\n", message->topic, str);
         //这里用来控制设备
        LED1->readData(str,LED1);
        LED2->readData(str,LED2);
		LED3->readData(str,LED3);
		BEEP->readData(str,BEEP);
		fansHandler->readData(str,fansHandler);
		memset(str,0,strlen(str));
    }else{
        printf("\nmy_message_callback: %s (null)\n", message->topic);
    }
    //fflush(stdout);
}

int example_publish(struct mosquitto *mosq,mosquitto_t *mosquitto){
    int             res = 0;
    char           *topic = NULL;
    int             topic_len = 0;
	char           *payload = NULL;
	static int now = 0;

    //这里添加你要上报信息的设备
    dht11Handler->getData(dht11Handler);
    while(!dht11Handler->flag){
        dht11Handler->getData(dht11Handler);
    }
    shockHandler->getData(shockHandler);

    cJSON *root=cJSON_CreateObject();
	cJSON *rt=cJSON_CreateObject();
    cJSON *properties=cJSON_CreateObject();
    cJSON_AddItemToObject(root,"properties",properties);
	cJSON_AddItemToObject(rt,"properties",properties);
	cJSON_AddItemToObject(properties,"RPHumidity",cJSON_CreateNumber(dht11Handler->humidity));
	cJSON_AddItemToObject(properties,"RPTemperature",cJSON_CreateNumber(dht11Handler->temperature));
	cJSON_AddItemToObject(properties,"shockLED",cJSON_CreateString(shockHandler->status));
	if(now == 0){
		cJSON_AddItemToObject(properties,"raspled1",cJSON_CreateString(LED1->status));
		cJSON_AddItemToObject(properties,"raspled2",cJSON_CreateString(LED2->status));
		cJSON_AddItemToObject(properties,"raspled3",cJSON_CreateString(LED3->status));
		cJSON_AddItemToObject(properties,"raspfans",cJSON_CreateString(fansHandler->status));
		now = 1;
		payload = cJSON_Print(root);
		mosquitto_publish(mosq,NULL,mosquitto->pub_topic,strlen(payload),payload,0,0);
	}

    payload = cJSON_Print(rt);
    mosquitto_publish(mosq,NULL,"getRP",strlen(payload),payload,0,0);
    if(running == 0){
         while(1);
    }
    printf("pub payload : \n%s\n",payload);
    return 0;
}



int example_subscribe(struct mosquitto *mosq,mosquitto_t *mosquitto){
	int             res = 0;
    char           *topic = NULL;
    int             topic_len = 0;
    res = mosquitto_subscribe(mosq,NULL,mosquitto->sub_topic,0);
	if(res != MOSQ_ERR_SUCCESS){
		printf("Sub the topic error\n");
		return -1;
	}
	else
		printf("subscribe topic:%s success.\n", mosquitto->sub_topic);
	return 0;
}

int init_openhabmos_argc(mosquitto_t *mosquitto){

    mosquitto->host = OH_HOST;
    mosquitto->port = OH_PORT;
    mosquitto->sub_topic = OH_SUB_TOPIC;
    mosquitto->pub_topic = OH_PUB_TOPIC;
    mosquitto->client_id = OH_CLIENT_ID;
    mosquitto->user = OH_USER;
    mosquitto->password = OH_PASSWD;
    mosquitto->keepalive = KEEP_ALIVE;
    mosquitto->recv_message = NULL;
    return 0;
}



int main(){
    int ret;
    int rv = -1;
	int OH_rv = -1;
    int loop_cnt = 0;

    struct mosquitto *mosq = NULL;
    mosquitto_t  mosquitto;

	memset(&OH_mosquitto, 0, sizeof(OH_mosquitto));

    piSetup();

    pheadDevices = addDht11ToDeviceLink(pheadDevices);
	pheadDevices = addShockSensorToDeviceLink(pheadDevices);
    //pheadDevices = addSwitchToDeviceLink(pheadDevices);
	pheadDevices = addLED1ToDeviceLink(pheadDevices);
	pheadDevices = addLED2ToDeviceLink(pheadDevices);
	pheadDevices = addLED3ToDeviceLink(pheadDevices);
	pheadDevices = addBeepToDeviceLink(pheadDevices);
	pheadDevices = addFANSToDeviceLink(pheadDevices);

	shockHandler = findDevicesByName("shock",pheadDevices);
	dht11Handler = findDevicesByName("dht11",pheadDevices);
	fansHandler = findDevicesByName("fans",pheadDevices);
	LED1 = findDevicesByName("led1",pheadDevices);
	LED2 = findDevicesByName("led2",pheadDevices);
	LED3 = findDevicesByName("led3",pheadDevices);
	BEEP = findDevicesByName("Beep",pheadDevices);

	shockHandler->devicesInit(shockHandler);
	fansHandler->devicesInit(fansHandler);
	LED1->devicesInit(LED1);
	LED2->devicesInit(LED2);
	LED3->devicesInit(LED3);
	BEEP->devicesInit(BEEP);

	//switchHandler = findDevicesByName("sw",pheadDevices);
	//switchHandler->devicesInit(switchHandler);

    // 初始化mosquitto
    rv = mosquitto_lib_init();
    if (rv){
        printf("Init mosquitto lib error:%s\n", strerror(errno));
        return rv;
    }


	OH_rv = init_openhabmos_argc(&OH_mosquitto);

    if (OH_rv){
        printf("Init mosquitto_sub & pub arguments error:%s\n", strerror(errno));
        return -1;
    }


	OH_rv = mosquitto_sub_start(OH_mosq, &OH_mosquitto);

    if (OH_rv){
        printf("mosquitto_sub_start failed.\n");
        mosquitto_lib_cleanup();
        return -1;
    }
    else{
        printf("mosquitto_sub_start success.\n ");
    }

	//openhab
    OH_mosq = mosquitto_new(OH_mosquitto.client_id, true, (void *)&OH_mosquitto);
    mosquitto_connect_callback_set(OH_mosq, myPublish_connect_callback);
    mosquitto_disconnect_callback_set(OH_mosq, myPublish_disconnect_callback);
    mosquitto_username_pw_set(OH_mosq,OH_mosquitto.user, OH_mosquitto.password);
    mosquitto_message_callback_set(OH_mosq, my_message_callback);
    mosquitto_publish_callback_set(OH_mosq, myPublish_callback);
	mosquitto_connect(OH_mosq, OH_HOST, OH_PORT, KEEP_ALIVE);


	int OH_loop = mosquitto_loop_start(OH_mosq);


	if(OH_loop != MOSQ_ERR_SUCCESS){
        printf("Mosquitto_pub OH_loop error\n");
        return -1;
    }
	example_subscribe(OH_mosq,&OH_mosquitto);
	//example_publish(OH_mosq,&OH_mosquitto);

	//sleep(3);
    while(1){
		//example_subscribe(mosq,&mosquitto);
		example_publish(OH_mosq,&OH_mosquitto);
		sleep(2);
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    printf("End!\n");

    return 0;
}
