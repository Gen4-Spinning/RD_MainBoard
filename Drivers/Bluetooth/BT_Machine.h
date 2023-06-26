/*
 * BT_Constants.h
 *
 *  Created on: Mar 9, 2023
 *      Author: harsha
 */

#ifndef BT_MC_H_
#define BT_MC_H_

#include "BT_Fns.h"
#include "GB_Diag.h"
#include "machineSettings.h"

//settings TLVs
#define INPUT_YARN_NE 0x90
#define OUTPUT_YARN_DIA 0x91
#define SPINDLE_SPEED 0x92
#define TPI_RD 0x93
#define PACKAGE_HEIGHT 0x94
#define DIA_BUILD_FACTOR 0x95
#define WINDING_CLOSENESS_FACTOR 0x96
#define WINDING_OFFSET_COILS 0x97


#define BT_CALENDAR_ROLLER 0x01
#define BT_LIFT_BOTH 0x07
#define BT_LIFT_LEFT 0x08
#define BT_LIFT_RIGHT 0x09

#define BT_DIAGNOSTIC_RUN 0x01
#define BT_DIAGNOSTIC_STOP 0x06

//TLVs for GB calib
#define GB_CALIB_LEFT_ABSPOS 0x01
#define GB_CALIB_RIGHT_ABSPOS 0x02

uint8_t BT_MC_generateSettingsMsg(machineSettingsTypeDef *m);
uint8_t BT_MC_parse_Settings(machineSettingsTypeDef *mspBT);
uint8_t BT_MC_Save_Settings(void);
uint8_t GetMotorID_from_BTMotor_ID(uint8_t BT_motorID);
uint8_t Get_BTMotorID_from_Motor_ID(uint8_t motorID);
uint8_t Get_BTMotorID_from_Motor_ID(uint8_t motorID);
uint8_t GetMotorId_from_CarousalID(uint8_t carousalID);
uint8_t BT_generate_GbCalibMsg(GB_diag *gbd);
#endif /* BT_MC_H_ */
