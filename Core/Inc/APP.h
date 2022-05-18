/*
 * APP.h
 *
 *  Created on: May 17, 2022
 *      Author: Masoud Heidary
 *      gitHub: https://github.com/MasoudHeidary/
 *     License: MIT
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "M_MQTT.h"
#include "M-GPS.h"
#include "LCD_16x2.h"

/* Includes ------------------------------------------------------------------*/
// Lock States
#define APP_LockStateLock 0
#define APP_LockStateFree 1
#define APP_LockStateFind 2

// Front Led
#define APP_FrontLedOff 0
#define APP_FrontLedOn	1
#define APP_FrontLedToggle 2

// Brake
#define APP_BrakeFree 0
#define APP_BrakeTaken 1

// TX
// ﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏
// | TX Header(8bit) | 00 00 FrontLED(2) Lock(2) |
// ﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋
#define APP_CorpiUART &huart3
#define APP_TXBufferLen 2
#define APP_TXHeader '@'

// RX
// ﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏
// | RX Header(8bit) | Throttle(8bit) | 00 00 00 Brake(1bit) |
// ﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋
#define APP_RXBufferLen 3
#define APP_RXHeader '@'

/* Includes ------------------------------------------------------------------*/
struct {
	// Corpi (steering wheel)
	uint8_t TXBuffer[APP_TXBufferLen];
	uint8_t RXBuffer[APP_RXBufferLen];
	uint8_t Throttle;
	bool Brake;

	// State
	uint8_t Lock;
	uint8_t FrontLed;

	// MQTT Communication
	uint32_t ping_reg_timer;
	uint32_t publish_timer;
	int step;
} APP;

/* Includes ------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
void APP_init(void);
void APP_corpiRX(void);
void APP_corpiTX(void);
void APP_while(void);

/* Includes ------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* INC_APP_H_ */
