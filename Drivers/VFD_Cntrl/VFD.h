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
}VFD;



void TurnOnVFD(MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p,uint8_t vfdSpeed);
void TurnOffVFD(MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p);

#endif /* VFD_CNTRL_VFD_H_ */
