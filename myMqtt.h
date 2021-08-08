/********************************************************************************
 *      Copyright:  (C) 2020 ysn
 *                  All rights reserved.
 *
 *       Filename:  mosquitto_sub.h
 *    Description:  This head file is mosquitto_sub.
 *
 *        Version:  1.0.0(28/07/20)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "28/07/20 05:27:49"
 *
 ********************************************************************************/

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <libgen.h>
#include <unistd.h>
#include <errno.h>
#include <cjson/cJSON.h>
#include <mosquitto.h>

//openhab init argc
#define OH_HOST "192.168.31.61"  //域名
#define OH_PORT  1883  //MQTT BORKER PORT
#define OH_CLIENT_ID "raspberry"  //DEVICENAME

#define OH_USER "openhabian"
#define OH_PASSWD "1"

#define OH_SUB_TOPIC "cmdled"
#define OH_PUB_TOPIC "getled"

#define KEEP_ALIVE 60
#define MSG_MAX_SIZE  512
#define BUF_SIZE   128

/*
 * if define MAIN:     will use this file's main func to test.
 * if not define MAIN: will use the mian file's mian func to test.
 * */

//int cv_status = 0;

typedef struct mosquitto_s
{
    char *host;
    int  port;
    char *sub_topic;
    char *pub_topic;
    char *client_id;
    char *user;
    char *password;
    int  keepalive;
    char *recv_message;

} mosquitto_t;  /* ---  end of struct mosquitto_s  ---*/
 char buf[1024];
//extern int init_mosquitto_argc (mosquitto_t *mosquitto);
extern int mosquitto_sub_init (struct mosquitto *mosqut, mosquitto_t *mosquitto);

int init_mosquitto_argc(mosquitto_t *mosquitto);
int mosquitto_sub_start (struct mosquitto *mosqut, mosquitto_t *mosquitto);
void mySubscribe_message_callback(struct mosquitto *mosqut,void *obj, const struct mosquitto_message *msg);
void mySubscribe_connect_callback(struct mosquitto *mosqut, void *obj, int rc);
void mySubscribe_disconnect_callback(struct mosquitto *mosq, void *obj, int rc);
void mySubscribe_callback(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos);
static void mosquitto_sub_clean (struct mosquitto *mosqut, void (disconnect_callback)(struct mosquitto *mosqut, void *, int));

void myPublish_connect_callback(struct mosquitto *mosq, void *obj, int rc);
void myPublish_disconnect_callback(struct mosquitto *mosq, void *obj, int rc);
void myPublish_callback(struct mosquitto *mosq, void *obj, int mid);
int mosquitto_pub_start (struct mosquitto *mosqut, mosquitto_t *mosquitto);
void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
//int init_mosquitto_pub_argc(mosquitto_t *mosquitto);
static void mosquitto_pub_clean (struct mosquitto *mosqut, void (disconnect_callback)(struct mosquitto *mosqut, void *, int));
int example_publish(struct mosquitto *mosq,mosquitto_t *mosquitto);
