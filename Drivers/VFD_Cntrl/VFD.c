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



//MI 0 is the run command - bit 0
//MI 1 is the direction command - which we dont control - bit 1
//MI 2 is speed 1 - bit 2
//MI 3 is speed 2 - bit 3
//2 and 3 together is speed 3 -  bit 4
//MI 4 is speed 4 - bit 5

void TurnOnVFD(MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p,uint8_t vfdSpeed){
	if (vfdSpeed == SPINDLE_SPEED_6000){
		p->values.M3 = 0;
		p->values.M2 = 0;
		p->values.M1 = 1;
		p->values.run = 1;
		mcp->outputGPIO[0] = p->raw;
		mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	}
	else if (vfdSpeed == SPINDLE_SPEED_8000){
		//data[0] = 0x50;	//
		p->values.M3 = 0;
		p->values.M2 = 1;
		p->values.M1 = 0;
		p->values.run = 1;
		mcp->outputGPIO[0] = p->raw;
		mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	}
	else if (vfdSpeed == SPINDLE_SPEED_10000){
		//data[0] = 0x70;	//
		p->values.M3 = 0;
		p->values.M2 = 1;
		p->values.M1 = 1;
		p->values.run = 1;
		mcp->outputGPIO[0] = p->raw;
		mcp23017_write(mcp, OLATA,mcp->outputGPIO);
	}
	else if (vfdSpeed == SPINDLE_SPEED_12000){
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
}


void TurnOffVFD(MCP23017_HandleTypeDef *mcp,MCP23017_PortA *p){
	//data[0] = 0x00;
	//data[0] = 0x90;	//
	p->values.M3 = 0;
	p->values.M2 = 0;
	p->values.M1 = 0;
	p->values.run = 0;
	mcp->outputGPIO[0] = p->raw;
	mcp23017_write(mcp, OLATA,mcp->outputGPIO);
}
