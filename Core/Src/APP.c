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

	if (huart->Instance == USART3) {
			APP_corpiRX();
			HAL_UART_Receive_DMA(APP_CorpiUART, APP.RXBuffer, APP_RXBufferLen);
		}
}


void APP_init(void) {
	// Corpi
	HAL_UART_Receive_DMA(APP_CorpiUART, APP.RXBuffer, APP_RXBufferLen);
	lcd_init();
	lcd_clear();
	lcd_gotoxy(0, 0);
	lcd_puts("Loading...");

	// initialize states
	APP.Lock = APP_LockStateLock;
	APP.FrontLed = APP_FrontLedOff;
	APP_corpiTX();

	// initialize MQTT
	APP.ping_reg_timer = HAL_GetTick();
	APP.publish_timer = HAL_GetTick();
	APP.step = 0;

	// GPS
	M_GPS_init(huart2);
	M_GPS_bufInit(huart2);
}


void APP_corpiRX(void) {
	if(APP.RXBuffer[0] == APP_RXHeader) {
		APP.Throttle = APP.RXBuffer[1];
		APP.Brake = APP.RXBuffer[2] ? APP_BrakeTaken : APP_BrakeFree;
	}
}


void APP_corpiTX(void) {
	APP.TXBuffer[0] = APP_TXHeader;
	APP.TXBuffer[1] =
			(APP.Lock & 0x03) |
			((APP.FrontLed & 0x03) << 2);

	HAL_UART_Transmit(APP_CorpiUART, APP.TXBuffer, APP_TXBufferLen, 1000);
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

	// publish Location
	if((APP.step > 2) && (HAL_GetTick() - APP.publish_timer > 15000)) {
	  sprintf(msg, "%lf,%lf", M_GPS_getLatitude(), M_GPS_getLongitude());
	  if(!M_MQTT_publish("scooter/112", msg, packet_id++, 0))
		  APP.step = 0;

	  APP.publish_timer = HAL_GetTick();
	}

	// update LCD
	char str[16] = "";
	sprintf(str, "Lock:%2d,Led:%2d  ", APP.Lock, APP.FrontLed);
	lcd_gotoxy(0, 0);
	lcd_puts(str);

	memset(str, 0, 16);
	if (APP.Brake == APP_BrakeFree)
		sprintf(str, "Throttle: %3d", (int)APP.Throttle);
	else
		sprintf(str, "BRAKE!         ");
	lcd_gotoxy(0, 1);
	lcd_puts(str);
}
