/*
 * VFD.h
 *
 *  Created on: 22-May-2023
 *      Author: harsha
 */

#ifndef VFD_CNTRL_VFD_H_
#define VFD_CNTRL_VFD_H_

#include "mcp23017.h"

#define SPINDLE_SPEED_12000 1 // has rampup time of 60 sec
#define SPINDLE_SPEED_10000 2 // 50 sec
#define SPINDLE_SPEED_8000 3 //40 sec
#define SPINDLE_SPEED_6000 4 // 30 sec


typedef struct VFD_struct{
	uint8_t vfdSpeed;
	uint16_t vfdOn;

	uint16_t maxRPM;
	uint8_t rampTime_sec;
	float rampRate;
	int16_t presentRPM;
}VFD;

extern VFD vfd;

uint8_t VFD_getSpindleSpeedCode(uint16_t spindleSpeed);
void VFD_setSpindleSpeed(VFD *v,uint8_t spindlespeed_define);
void VFD_TurnOn(VFD *v,MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p);
void VFD_TurnOff(VFD *v,MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p);

#endif /* VFD_CNTRL_VFD_H_ */
