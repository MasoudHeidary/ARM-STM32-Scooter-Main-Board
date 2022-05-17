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

/* Includes ------------------------------------------------------------------*/
// Lock States
#define APP_LockStateLock 0
#define APP_LockStateFree 1
#define APP_LockStateFind 2

// Front Led
#define APP_FrontLedOff 0
#define APP_FrontLedOn	1
#define APP_FrontLedToggle 2

/* Includes ------------------------------------------------------------------*/
struct {
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

/* Includes ------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* INC_APP_H_ */
