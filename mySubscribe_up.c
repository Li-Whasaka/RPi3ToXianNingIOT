#include "myMqtt.h"

// 定义运行标志决定是否需要结束
static int g_stop = 0;


static void mosquitto_sub_clean (struct mosquitto *mosqut, void (disconnect_callback)(struct mosquitto *mosqut, void *, int)){
    mosquitto_disconnect_callback_set(mosqut, disconnect_callback);
    mosquitto_destroy(mosqut);
    mosquitto_lib_cleanup();
}

int mosquitto_sub_start (struct mosquitto *mosqut, mosquitto_t *mosquitto){
    int rv = 1;
    mosqut = mosquitto_new(mosquitto->client_id, true, (void *)mosquitto);
    if (!mosqut){
        printf("mosquitto_sub new error:%s\n", strerror(errno));
        return rv;
    }
    else
        printf("mosquitto_sub new success.\n ");

    mosquitto_connect_callback_set(mosqut, mySubscribe_connect_callback);
    mosquitto_message_callback_set(mosqut, mySubscribe_message_callback);
    mosquitto_username_pw_set(mosqut, mosquitto->user, mosquitto->password);
    mosquitto_subscribe_callback_set(mosqut, mySubscribe_callback);


    while (!g_stop){
        rv = mosquitto_connect(mosqut, mosquitto->host, mosquitto->port, mosquitto->keepalive);
        if (rv){
            printf("mosquitto_sub Connect server error:%s\n", strerror(errno));
            mosquitto_destroy(mosqut);
            mosquitto_lib_cleanup();
            return 1;
        }
        else{
            printf("mosquitto_sub connect success.\n");
			//g_stop = 1;
            return 0;
        }
        mosquitto_loop_forever(mosqut, -1, 1);

        if( rv != MOSQ_ERR_SUCCESS) {
            printf("mosquitto_loop_forever: %s\n", strerror(errno));
            mosquitto_sub_clean(mosqut, mySubscribe_disconnect_callback);
            return 1;
        }
    }
    return 0;
}

void mySubscribe_connect_callback(struct mosquitto *mosqut, void *obj, int rc){
	printf("Call the function: mySubscribe_connect_callback\n");

	/*if (NULL == obj)
        return ;

    mosquitto_t    *mosquitto;
    int            mid;
    mosquitto = (mosquitto_t *)obj;

    if (!rc){

        if (mosquitto_subscribe(mosqut, &mid, mosquitto->sub_topic, 0) != MOSQ_ERR_SUCCESS)
        {
            printf("Set the topic error:%s\n", strerror(errno));
            return ;
        }
        else
            printf("subscribe topic:%s success.\n", mosquitto->sub_topic);

    }
    else
        printf("mySubscribe_connect_callback error\n");*/
}

void mySubscribe_disconnect_callback(struct mosquitto *mosq, void *obj, int rc){
    printf("Call the function: my_disconnect_callback\n");
    g_stop = 1;
}

void mySubscribe_callback(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos){
    printf("Call the function: on_subscribe\n");
    int i;
    printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for(i=1; i<qos_count; i++){
        printf(", %d", granted_qos[i]);
    }
    printf("\n");
}

void mySubscribe_message_callback(struct mosquitto *mosqut,void *obj, const struct mosquitto_message *msg){

    mosquitto_t *mosquitto;
    mosquitto = (mosquitto_t *)obj;
    memcpy(&mosquitto-> recv_message, (char *)&msg->payload, strlen((char *)msg->payload));
    printf("recv_message: %s\n", mosquitto->recv_message);

    if (0 == strcmp(msg->payload, "quit"))
        mosquitto_disconnect(mosqut);


}
