/*
 * machineSettings.c
 *
 *  Created on: Apr 11, 2023
 *      Author: harsha
 */

#include "machineSettings.h"
#include "math.h"

void InitializeMachineSettings(machineSettingsTypeDef *ms){
    ms->spindleSpeed = 8000;
    ms->inputYarnCountNe = 20;
    int outputYarnCountNe = ms->inputYarnCountNe / 2;
    ms->outputYarnDia = CalculateYarnDia(outputYarnCountNe);
    ms->tpi = 14;
    ms->packageHeight = 280;
    ms->diaBuildFactor = 0.12 ;
    ms->windingOffsetCoils = 2;
    ms->windingClosenessFactor = 108;
}

float CalculateYarnDia(int yarnCount){
	return -0.10284 + 1.592/sqrt((double)yarnCount);  //from the link : https://textilelearner.net/yarn-count-diameter-and-composition/
}

float ConvertYarnUnits(int input,int conversion){
	float output = 0;
	if (conversion == NE_TO_NM){
		output = input * 0.591;
	}else if (conversion == NM_TO_NE){
		output = input/0.591;
	}
	return output;
}

void CalculateMachineParameters(machineSettingsTypeDef *ms,machineParamsTypeDef *mp){
	mp->RD.delivery_MtrMin = (float)(ms->spindleSpeed)/(ms->tpi) * 0.0254;
	//we calculate and keep the output yarn dia as per formul abut use the yarn dia from the app in
	//the calculations
	mp->RD.outputYarnCountNe = ms->inputYarnCountNe/2;
	mp->RD.outputYarnDia_formula = CalculateYarnDia(mp->RD.outputYarnCountNe);

	float windingClosenessFactor_float = ms->windingClosenessFactor/100.0;
	float temp1 = ((mp->RD.delivery_MtrMin*1000)/(3.14 * AVERAGE_BOBBIN_DIA ));
	float temp2 = ms->outputYarnDia* windingClosenessFactor_float;
	mp->RD.windingVelocity_mmSec = (temp1 * temp2 )/60; //in mm/sec
	mp->RD.bindingVelocity_mmSec = mp->RD.windingVelocity_mmSec * BINDWINDRATIO;

	mp->RD.ht_difference_perStroke = (ms->windingOffsetCoils * ms->outputYarnDia * windingClosenessFactor_float)/ms->diaBuildFactor;
	mp->RD.strokesPerDoff = (ms->packageHeight - CHASEHEIGHT)/mp->RD.ht_difference_perStroke;

	mp->RD.windingStroke = CHASEHEIGHT;
	mp->RD.bindingStroke = CHASEHEIGHT - mp->RD.ht_difference_perStroke;
	mp->RD.windingTime = CHASEHEIGHT/mp->RD.windingVelocity_mmSec;
	mp->RD.bindingTime = mp->RD.bindingStroke/mp->RD.bindingVelocity_mmSec;

	mp->RD.totalStrokeTime_min = (mp->RD.windingTime + mp->RD.bindingTime)/60;
	mp->RD.doffTimeMin =  mp->RD.strokesPerDoff/mp->RD.totalStrokeTime_min;

	mp->RD.totalYarnLengthInMtrsPerBobbin = mp->RD.delivery_MtrMin * mp->RD.doffTimeMin;
	mp->RD.outputYarnCountNm = ConvertYarnUnits(mp->RD.outputYarnCountNe,NE_TO_NM);
	mp->RD.yarnWeightinGramsPerBobbin = mp->RD.totalYarnLengthInMtrsPerBobbin/mp->RD.outputYarnCountNm;

	//Now get the values for the motors, and also the values that keep updating as the machine runs
	if(ms->spindleSpeed == 6000){
		mp->rampTimes_sec = 30;
	}else if(ms->spindleSpeed == 8000){
		mp->rampTimes_sec = 40;
	}else if (ms->spindleSpeed == 10000){
		mp->rampTimes_sec = 50;
	}else if (ms->spindleSpeed == 12000){
		mp->rampTimes_sec = 60;
	}else{}

	mp->changeLayerTimes_ms = DEFAULT_CHANGE_LAYER_TIME;

	float req_CalRoller_RPM = (mp->RD.delivery_MtrMin*1000)/CALENDER_ROLLER_CIRC;
	mp->calenderMotorRPM = req_CalRoller_RPM * CALENDER_ROLLER_GEARBOX;
	mp->liftMotorRPMWinding = (mp->RD.windingVelocity_mmSec/LIFT_SCREW_PITCH_MM) * LIFT_MOTOR_TO_LIFT_SCREW_RATIO;
	mp->liftMotorRPMBinding = (mp->RD.bindingVelocity_mmSec/LIFT_SCREW_PITCH_MM) * LIFT_MOTOR_TO_LIFT_SCREW_RATIO;

	//setup for layer 0
    mp->currentStrokeNo = 0;
    mp->currentStrokeMode = WINDING;
    mp->currentStrokeTargetAbsPos = CHASEHEIGHT;
    mp->left_liftStrokeHeight = CHASEHEIGHT;
    mp->right_liftStrokeHeight = CHASEHEIGHT;
    mp->currentStrokeTime = mp->RD.windingTime;
    mp->currentStrokeVelocity = mp->RD.windingVelocity_mmSec;

    mp->currentLiftDirection = LIFT_UP;
	mp->currentRunTimeMin = 0;

}

void SetupMachineParametersForFirstLayer(machineParamsTypeDef *mp){
    mp->currentStrokeNo = 0;
    mp->currentStrokeMode = WINDING;
    mp->currentStrokeTargetAbsPos = CHASEHEIGHT;
    mp->left_liftStrokeHeight = CHASEHEIGHT;
    mp->right_liftStrokeHeight = CHASEHEIGHT;
    mp->currentStrokeTime = mp->RD.windingTime;
    mp->currentStrokeVelocity = mp->RD.windingVelocity_mmSec;

    mp->currentLiftDirection = LIFT_UP;
	mp->currentRunTimeMin = 0;
}

void UpdateMachineParameters(machineSettingsTypeDef *ms,machineParamsTypeDef *mp){
	if (mp->currentStrokeMode == WINDING){
		mp->currentStrokeMode = BINDING;
		mp->currentLiftDirection = LIFT_DOWN;
	    mp->currentStrokeTargetAbsPos = mp->currentStrokeTargetAbsPos - mp->RD.bindingStroke;
	    mp->currentStrokeTime = mp->RD.bindingTime;
	    mp->currentStrokeVelocity = mp->RD.bindingVelocity_mmSec;
	}else if (mp->currentStrokeMode == BINDING){
		mp->currentStrokeMode = WINDING;
		mp->currentLiftDirection = LIFT_UP;
	    mp->currentStrokeTargetAbsPos = mp->currentStrokeTargetAbsPos + mp->RD.windingStroke;
	    mp->currentStrokeTime = mp->RD.windingTime;
	    mp->currentStrokeVelocity = mp->RD.windingVelocity_mmSec;
	    mp->currentStrokeNo++;
	}
}


uint8_t getMotorCANAddress(uint8_t motor){
	if (motor == CALENDER_ROLLER){
		return 2;
	}
	return 0;
}

uint8_t getLiftMotorCANAddress(uint8_t motor){
	if (motor == RD_LEFT_LIFT){
		return RD_LEFTLIFT_ADDRESS;
	}else if (motor == RD_RIGHT_LIFT){
		return RD_RIGHTLIFT_ADDRESS;
	}else{
		return 0;
	}
}

uint8_t GetMotorID_from_CANAddress(uint8_t canAddress){
	if (canAddress == RD_CALENDER_ADDRESS){
		return CALENDER_ROLLER;
	}else if (canAddress == RD_LEFTLIFT_ADDRESS){
		return RD_LEFT_LIFT;
	}else if (canAddress == RD_RIGHTLIFT_ADDRESS){
		return RD_RIGHT_LIFT;
	}
	return 6; // return
}
