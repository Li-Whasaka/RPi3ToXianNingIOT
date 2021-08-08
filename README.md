# RPi3ToXianNingIOT
Example code of RPi3 connected to Xianning industrial Internet of things
# mosquitto
`Fisrt   modify   time       : 2021/05/26    16:13`</br>
`Second  modify   time       : 2021/05/28    21:49`</br>
`Third   modify   time       : 2021/06/15    19:40`</br>
`Fourth  modify   time       : 2021/08/08    10:44`</br> 
## Notice
### third modify time
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;We changed the way the platform username and password are made, and some changes have been made to the internal encryption function, and the other parts have not changed</br>
### The fourth  modify time
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I renamed repository "mosquitto" to "RPi3ToXianNingIOT",and Some code structures are optimized and new examples are added.</br>
## Introduction
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A sophomore wrote this. When I wrote it myself, I didn't have any reference materials. It was a bit buggy, but I was still able to establish contact with the cloud platform of the Internet of things to realize the sending, receiving and control of data. Hope to have a master to help improve and improve the code.</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;You can basically establish contact with all IOT cloud platforms through this program.just need you to modify some necessary information required.</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1、The necessary information mentioned above is contained in the header file named myMqtt.In it, I wrote a structure for storing those information.</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2、The device to be added also has a template structure in the header file named myDevices.You can refer to other equipment examples to imitate the equipment you need.</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3、For examples,the c files,"led1.c"\"led2.c"\"mySwtich.c"and so on.</br>
## program
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"myDevices.h"`.The function of adding device is provided. To add a new device, only copy the structure, select the required variables and functions, and then expose the function of adding device. This way of adding devices is similar to the simple factory mode of Java.</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;So just need four steps,you can `upload sensor information and control devices`:</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`Firstly`,According to other sensor templates, write the correct program of the device to be enabled.</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`Secondly`,Put the add device function declaration in "mydevices.h".</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`Thirdly`,In the appropriate function position of "myPublish_up.c " enables one's own device to collect information or control the device.</br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`Fourthly`,Inputing make to execute the makefile compilation project on the command line
  

