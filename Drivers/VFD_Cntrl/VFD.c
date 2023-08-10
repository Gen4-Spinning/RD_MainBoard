/*
 * VFD.c
 *
 *  Created on: 22-May-2023
 *      Author: harsha
 */

#include "VFD.h"

//VFD settings - > to be set in the VFD itself
//set to 50Hz ac motor type
//set output frequency and run commands from the external inputs
//set display 3 first to rpm and after confirming speed set to power.
//set ramp up and ramp down times to be 12 sec each always


uint8_t VFD_getSpindleSpeedCode(uint16_t spindleSpeed){
	if (spindleSpeed < 7000){
		return SPINDLE_SPEED_6000;
	}else if (spindleSpeed < 8500){
		return SPINDLE_SPEED_8000;
	}else if (spindleSpeed < 10500){
		return SPINDLE_SPEED_10000;
	}else if (spindleSpeed < 12500){
		return SPINDLE_SPEED_12000;
	}else{
		return SPINDLE_SPEED_6000;
	}
	return SPINDLE_SPEED_6000;
}

void VFD_setSpindleSpeed(VFD *v,uint8_t spindlespeed_define){
	v->vfdSpeed = spindlespeed_define;
	if (v->vfdSpeed == SPINDLE_SPEED_6000){
		v->rampTime_sec = 30;
		v->maxRPM = 6000;
	}
	if (v->vfdSpeed == SPINDLE_SPEED_8000){
		v->rampTime_sec = 40;
		v->maxRPM = 8000;
	}
	if (v->vfdSpeed == SPINDLE_SPEED_10000){
		v->rampTime_sec = 50;
		v->maxRPM = 10000;
	}
	if (v->vfdSpeed == SPINDLE_SPEED_12000){
		v->rampTime_sec = 60;
		v->maxRPM = 12000;
	}
	v->rampRate = v->maxRPM/(v->rampTime_sec *10);
}

void VFD_calculateSpindleMotorSpeed(VFD *vfd,uint8_t rampUp){
	if (rampUp == 1){
		vfd->presentRPM = (uint16_t)vfd->presentRPM + vfd->rampRate;
		if (vfd->presentRPM > vfd->maxRPM){
			vfd->presentRPM = vfd->maxRPM;
		}
	}
	else if (rampUp==0){
		vfd->presentRPM = (uint16_t)vfd->presentRPM - vfd->rampRate;
		if (vfd->presentRPM < 0){
			vfd->presentRPM = 0;
		}
	}
}

//MI 0 is the run command - bit 0
//MI 1 is the direction command - which we dont control - bit 1
//MI 2 is speed 1 - bit 2
//MI 3 is speed 2 - bit 3
//2 and 3 together is speed 3 -  bit 4
//MI 4 is speed 4 - bit 5

void VFD_TurnOn(VFD *v,MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p){
	if (v->vfdSpeed == SPINDLE_SPEED_6000){
		p->values.M3 = 0;
		p->values.M2 = 0;
		p->values.M1 = 1;
		p->values.run = 1;
		mcp->outputGPIO[0] = p->raw;
		mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	}
	else if (v->vfdSpeed  == SPINDLE_SPEED_8000){
		//data[0] = 0x50;	//
		p->values.M3 = 0;
		p->values.M2 = 1;
		p->values.M1 = 0;
		p->values.run = 1;
		mcp->outputGPIO[0] = p->raw;
		mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	}
	else if (v->vfdSpeed  == SPINDLE_SPEED_10000){
		//data[0] = 0x70;	//
		p->values.M3 = 0;
		p->values.M2 = 1;
		p->values.M1 = 1;
		p->values.run = 1;
		mcp->outputGPIO[0] = p->raw;
		mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	}
	else if (v->vfdSpeed  == SPINDLE_SPEED_12000){
		//data[0] = 0x90;	//
		p->values.M3 = 1;
		p->values.M2 = 0;
		p->values.M1 = 0;
		p->values.run = 1;
		mcp->outputGPIO[0] = p->raw;
		mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	}
	else{

	}
	v->vfdOn = 1;
}


void VFD_TurnOff(VFD *v,MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p){
	//data[0] = 0x00;
	//data[0] = 0x90;	//
	p->values.M3 = 0;
	p->values.M2 = 0;
	p->values.M1 = 0;
	p->values.run = 0;
	mcp->outputGPIO[0] = p->raw;
	mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	v->vfdOn = 0;
}
