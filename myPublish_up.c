#include "myMqtt.h"
#include "myDevices.h"


static void mosquitto_pub_clean (struct mosquitto *mosqut, void (disconnect_callback)(struct mosquitto *mosqut, void *, int)){
    mosquitto_disconnect_callback_set(mosqut, disconnect_callback);
    mosquitto_destroy(mosqut);
    mosquitto_lib_cleanup();
}

void myPublish_connect_callback(struct mosquitto *mosq, void *obj, int rc){
    printf("Call the function: myPublish_connect_callback\n");
}


void myPublish_callback(struct mosquitto *mosq, void *obj, int mid){
    printf("Call the function: my_publish_callback\n");

}

