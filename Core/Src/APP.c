/*
 * APP.c
 *
 *  Created on: May 17, 2022
 *      Author: Masoud Heidary
 *      gitHub: https://github.com/MasoudHeidary/
 *     License: MIT
 */

#include "APP.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart->Instance == USART1){
		M_SIM800_RXCallBack();
	}

	if (huart->Instance == USART2) {
			M_GPS_bufCplt();
			M_GPS_bufInit(huart2);
	}
}


void APP_init(void) {
	// initialize states
	APP.Lock = APP_LockStateLock;
	APP.FrontLed = APP_FrontLedOff;

	// initialize MQTT
	APP.ping_reg_timer = HAL_GetTick();
	APP.publish_timer = HAL_GetTick();
	APP.step = 0;

	// GPS
	M_GPS_init(huart2);
	M_GPS_bufInit(huart2);
}

void APP_while(void) {
	int packet_id = 1000;
	char msg[50] = "";

	if(APP.step == 0) {
	  if (M_SIM800_init())
		  APP.step++;
	}

	if(APP.step == 1) {
	  if(M_SIM800_connect("mcinet", "", "", "mqtt.eclipseprojects.io", 1883))
		  APP.step++;
	  else
		  APP.step = 0;
	}

	if(APP.step == 2) {
	  if(M_MQTT_connect("", "", "123456", 60, 0)) {
		  APP.step++;
		  APP.publish_timer = HAL_GetTick();
		  APP.ping_reg_timer = HAL_GetTick();
	  }
	  else
		  APP.step = 0;
	}

	if(APP.step == 3) {
	  if(M_MQTT_subscribe("scooter/112", 0))
		  APP.step++;
	  else
		  APP.step = 0;
	}
	// end machine state

	// ping req (keep alive) process
	if((APP.step > 2) && (HAL_GetTick() - APP.ping_reg_timer > 30000)) {
	  if (!M_MQTT_pingReq())
		  APP.step = 0;
	  APP.ping_reg_timer = HAL_GetTick();
	}

	// publish process
	if((APP.step > 2) && (HAL_GetTick() - APP.publish_timer > 15000)) {
	  sprintf(msg, "%Lf:%Lf", M_GPS_getLatitude(), M_GPS_getLongitude());
	  if(!M_MQTT_publish("scooter/112", msg, packet_id++, 0))
		  APP.step = 0;

	  APP.publish_timer = HAL_GetTick();
	}
}
