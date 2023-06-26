/*
 * BT_Machine.c
 *
 *  Created on: 25-Apr-2023
 *      Author: harsha
 */

#include "BT_Machine.h"


uint8_t BT_MC_generateSettingsMsg(machineSettingsTypeDef *m){
	  char TLV_Buffer[12];
	  uint8_t tlvSize = 0;
	  uint8_t eof_size  = 0;
	  uint8_t initLength = 0;

	  initLength = Init_TXBuf_Frame(SETTINGS_FROM_MC,SUBSTATE_NA,12);

	  generateTLV_I(TLV_Buffer,INPUT_YARN_NE,m->inputYarnCountNe);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_INT,initLength+tlvSize);
	  tlvSize += TLV_INT;

	  generateTLV_F(TLV_Buffer,OUTPUT_YARN_DIA,m->outputYarnDia);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_FLOAT,initLength+tlvSize);
	  tlvSize += TLV_FLOAT;

	  generateTLV_I(TLV_Buffer,SPINDLE_SPEED,m->spindleSpeed);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_INT,initLength+tlvSize);
	  tlvSize += TLV_INT;

	  generateTLV_I(TLV_Buffer,TPI_RD,m->tpi);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_INT,initLength+tlvSize);
	  tlvSize += TLV_INT;

	  generateTLV_I(TLV_Buffer,PACKAGE_HEIGHT,m->packageHeight);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_INT,initLength+tlvSize);
	  tlvSize += TLV_INT;

	  generateTLV_F(TLV_Buffer,DIA_BUILD_FACTOR,m->diaBuildFactor);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_FLOAT,initLength+tlvSize);
	  tlvSize += TLV_FLOAT;

	  generateTLV_I(TLV_Buffer,WINDING_CLOSENESS_FACTOR,m->windingClosenessFactor);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_INT,initLength+tlvSize);
	  tlvSize += TLV_INT;

	  generateTLV_I(TLV_Buffer,WINDING_OFFSET_COILS,m->windingOffsetCoils);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_INT,initLength+tlvSize);
	  tlvSize += TLV_INT;

	  eof_size = addEOF(initLength+tlvSize);
	  correctLengthInFrame(initLength,tlvSize,eof_size);

	  return initLength + tlvSize + eof_size;
}

//FLYER
uint8_t BT_MC_parse_Settings(machineSettingsTypeDef *mspBT){
	//Buffer Rec index 10 onwards is TLVs till 10 + TlvsLength
	TLVStruct_TypeDef T;
	uint8_t TLV_start = 10;
	uint8_t tlvSize = 0;
	uint8_t count = 0;
	uint8_t allSettingsRecieved = 0;

    for (int i=0;i<BT.attributeCnt;i++){
    	tlvSize = parseTLV(&T,TLV_start);
    	TLV_start += tlvSize;
    	switch (T.type){
    		case INPUT_YARN_NE:
    			mspBT->inputYarnCountNe = T.value_int;
    			count += 1;
    			break;
    		case OUTPUT_YARN_DIA:
    			mspBT->outputYarnDia = T.value_f;
    			count += 1;
    			break;
    		case SPINDLE_SPEED:
    			mspBT->spindleSpeed = T.value_int;
    			count += 1;
    			break;
    		case TPI_RD:
    			mspBT->tpi = T.value_int;
    			count += 1;
    			break;
    		case PACKAGE_HEIGHT:
    			mspBT->packageHeight = T.value_int;
    			count += 1;
    			break;
    		case DIA_BUILD_FACTOR:
    			mspBT->diaBuildFactor = T.value_f;
    			count += 1;
    			break;
    		case WINDING_CLOSENESS_FACTOR:
    			mspBT->windingClosenessFactor = T.value_int;
    			count += 1;
    			break;
    		case WINDING_OFFSET_COILS:
    			mspBT->windingOffsetCoils = T.value_int;
    			count += 1;
    			break;
    		}
    }

    if (count == 8){
    	allSettingsRecieved = 1;
    }

    return allSettingsRecieved;
}

//FLYER
uint8_t BT_MC_Save_Settings(void){
	uint8_t fail;
	fail = WriteMachineSettingsIntoEeprom(&msp_BT);
	if (fail == 0){
		msp.inputYarnCountNe = msp_BT.inputYarnCountNe;
		msp.outputYarnDia = msp_BT.outputYarnDia;
		msp.spindleSpeed = msp_BT.spindleSpeed;
		msp.tpi = msp_BT.tpi;
		msp.packageHeight = msp_BT.packageHeight;
		msp.windingClosenessFactor = msp_BT.windingClosenessFactor;
		msp.windingOffsetCoils = msp_BT.windingOffsetCoils;
		msp.diaBuildFactor = msp_BT.diaBuildFactor;
		//send success msg to APP
	}
	return !fail;
}


uint8_t GetMotorID_from_BTMotor_ID(uint8_t BT_motorID){
	if (BT_motorID == BT_CALENDAR_ROLLER){
		return CALENDER_ROLLER;
	}
	else if (BT_motorID == BT_LIFT_LEFT){
		return RD_LEFT_LIFT;
	}
	else if (BT_motorID == BT_LIFT_RIGHT){
		return RD_RIGHT_LIFT;
	}
	return 0;
}

uint8_t Get_BTMotorID_from_Motor_ID(uint8_t motorID){
	if (motorID == CALENDER_ROLLER){
		return BT_CALENDAR_ROLLER;
	}
	else if (motorID == RD_LEFT_LIFT){
		return BT_LIFT_LEFT;
	}
	else if (motorID == RD_RIGHT_LIFT){
		return BT_LIFT_RIGHT;
	}
	return 0;
}

uint8_t GetMotorId_from_CarousalID(uint8_t carousalID){
	if (carousalID == BT_CALENDAR_ROLLER){
		return CALENDER_ROLLER;
	}
	else if (carousalID == BT_LIFT_LEFT){
		return RD_LEFT_LIFT;
	}else if (carousalID == BT_LIFT_RIGHT){
		return RD_RIGHT_LIFT;
	}
	return 99;
}

uint8_t BT_generate_GbCalibMsg(GB_diag *gbd){
	  char TLV_Buffer[12];
	  uint8_t tlvSize = 0;
	  uint8_t eof_size  = 0;
	  uint8_t initLength = 0;

	  initLength = Init_TXBuf_Frame(GBCALIB_DATA_FROM_MB,SUBSTATE_NA,2);

	  generateTLV_F(TLV_Buffer,GB_CALIB_LEFT_ABSPOS,gbd->leftLift_DutyCycle);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_FLOAT,initLength+tlvSize);
	  tlvSize += TLV_FLOAT;

	  generateTLV_F(TLV_Buffer,GB_CALIB_RIGHT_ABSPOS,gbd->rightLift_DutyCycle);
	  add_TLVBuf_To_TxBuf(TLV_Buffer,TLV_FLOAT,initLength+tlvSize);
	  tlvSize += TLV_FLOAT;

	  eof_size = addEOF(initLength+tlvSize);
	  correctLengthInFrame(initLength,tlvSize,eof_size);
	  return initLength+tlvSize+eof_size;

}
