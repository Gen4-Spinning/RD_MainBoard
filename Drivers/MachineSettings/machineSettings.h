/*
 * machineSettings.h
 *
 *  Created on: Apr 11, 2023
 *      Author: harsha
 */

#ifndef MACHINESETTINGS_H_
#define MACHINESETTINGS_H_

#include "stdio.h"
#include "FDCAN.h"

//all Structs with arrays have to follow this Form
#define CALENDER_ROLLER 0
#define RD_LEFT_LIFT 1
#define RD_RIGHT_LIFT 2

#define CALENDER_ROLLER_CIRC 141.37
#define CALENDER_ROLLER_GEARBOX 6.91
#define LIFT_SCREW_PITCH_MM 4.0
#define LIFT_MOTOR_TO_LIFT_SCREW_RATIO 24

#define AVERAGE_BOBBIN_DIA 24
#define BINDWINDRATIO 2
#define CHASEHEIGHT 55

#define NE_TO_NM 1
#define NM_TO_NE 2

#define DEFAULT_CHANGE_LAYER_TIME 800

//LIMITS
#define MAX_MOTOR_RPM 1450

// lift direction in the motor sw
#define LIFT_UP 1
#define LIFT_DOWN 0

#define WINDING 1
#define BINDING 2

typedef struct machineSettings_Struct{
	int inputYarnCountNe;
	float outputYarnDia;
    int spindleSpeed;
    int tpi;
    int packageHeight;
    float diaBuildFactor;
    int windingOffsetCoils;
    int windingClosenessFactor;

}machineSettingsTypeDef;


typedef struct ringDoublerParameters{
	float delivery_MtrMin;
	uint8_t outputYarnCountNe;
	float outputYarnDia_formula;

	float windingVelocity_mmSec;
	float bindingVelocity_mmSec;

	float ht_difference_perStroke;
	int strokesPerDoff;

	float windingStroke;
	float bindingStroke;
	float windingTime;
	float bindingTime;

	float totalStrokeTime_min ;
	float doffTimeMin;

	float totalYarnLengthInMtrsPerBobbin;
	float outputYarnCountNm;
	float yarnWeightinGramsPerBobbin ;

}ringDoubler;

typedef struct machineParamaters_Struct{
    ringDoubler RD;

    uint16_t calenderMotorRPM;
    uint16_t liftMotorRPMWinding;
    uint16_t liftMotorRPMBinding;
    uint16_t rampTimes_sec;
    uint16_t changeLayerTimes_ms;

    int currentStrokeNo;
    int currentStrokeMode;
    float currentStrokeTargetAbsPos;
    float left_liftStrokeHeight;
    float right_liftStrokeHeight;
    float currentStrokeTime;
    float currentStrokeVelocity;

    float currentRunTimeMin;
    int currentLiftDirection;

}machineParamsTypeDef;


extern machineSettingsTypeDef msp;
extern machineSettingsTypeDef msp_BT;
extern machineParamsTypeDef mcParams;

// Eeprom MachineSettings
void ReadMachineSettingsFromEeprom(machineSettingsTypeDef *m);
uint8_t WriteMachineSettingsIntoEeprom(machineSettingsTypeDef *m);
uint8_t CheckMachineSettings(machineSettingsTypeDef* m);
void LoadDefaultMachineSettings(machineSettingsTypeDef* m);

//otherFns
void InitializeMachineSettings(machineSettingsTypeDef *ms);
float CalculateYarnDia(int yarnCount);
float ConvertYarnUnits(int input,int conversion);
void CalculateMachineParameters(machineSettingsTypeDef *ms,machineParamsTypeDef *mp);
void SetupMachineParametersForFirstLayer(machineParamsTypeDef *mp);
void UpdateMachineParameters(machineSettingsTypeDef *ms,machineParamsTypeDef *mp);

uint8_t getMotorCANAddress(uint8_t motor);
uint8_t getLiftMotorCANAddress(uint8_t motor);
uint8_t GetMotorID_from_CANAddress(uint8_t canAddress);


#endif /* MACHINESETTINGS_H_ */
