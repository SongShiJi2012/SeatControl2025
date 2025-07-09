/**************************************************************
* Author:           JeanYuan
* Copyright (c) 2013-2019 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved. 
*  generated :Thu Nov 28 14:49:52 2024

**************************************************************/
#include  "DSM.h"

#define kTxSendCyclic         (vuint8)0x01    /* Cyclic send                   */
/**************************************************************/
/* set event function                               */ 
/**************************************************************/
extern void IlSetEvent(IlTransmitHandle txHandle); 


extern _c_IVI4_buf MEMORY_FAR  IVI4;
extern _c_IVI8_DSM_buf MEMORY_FAR  IVI8_DSM;
extern _c_VCU1_buf MEMORY_FAR  VCU1;
extern _c_GWB1_buf MEMORY_FAR  GWB1;
extern _c_BDC3_buf MEMORY_FAR  BDC3;
extern _c_ABS1_buf MEMORY_FAR  ABS1;
extern _c_BDC6_PEPS1_buf MEMORY_FAR  BDC6_PEPS1;
extern _c_BDC5_buf MEMORY_FAR  BDC5;
extern _c_GWB2_buf MEMORY_FAR  GWB2;
extern _c_TCU1_buf MEMORY_FAR  TCU1;
/**************************************************************/
/* Databuffer for send objects                                            */ 
/**************************************************************/
_c_DSM_0x502_buf MEMORY_FAR  DSM_0x502;
_c_DSM_0x501_buf MEMORY_FAR  DSM_0x501;
_c_DSM_2_buf MEMORY_FAR  DSM_2;
_c_DSM_buf MEMORY_FAR  DSM;
/**************************************************************/
/* Databuffer for receive objects                                            */ 
/**************************************************************/
_c_IVI4_buf MEMORY_FAR  IVI4;
_c_IVI8_DSM_buf MEMORY_FAR  IVI8_DSM;
_c_VCU1_buf MEMORY_FAR  VCU1;
_c_GWB1_buf MEMORY_FAR  GWB1;
_c_BDC3_buf MEMORY_FAR  BDC3;
_c_ABS1_buf MEMORY_FAR  ABS1;
_c_BDC6_PEPS1_buf MEMORY_FAR  BDC6_PEPS1;
_c_BDC5_buf MEMORY_FAR  BDC5;
_c_GWB2_buf MEMORY_FAR  GWB2;
_c_TCU1_buf MEMORY_FAR  TCU1;
/**************************************************************/
/* Send structures                                             */ 
/**************************************************************/
V_MEMROM0 V_MEMROM1 tCanTxId V_MEMROM2 CanTxId[kCanNumberOfTxObjects] = {

	 0x502		/* id: 	 0x502:DSM_0x502*/
	,0x501		/* id: 	 0x501:DSM_0x501*/
	,0x500		/* id: 	 0x500:DSM_2*/
	,0x3B2		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 canuint8 V_MEMROM2 CanTxDLC[kCanNumberOfTxObjects] = {
	 0x08		/* id: 	 0x502:DSM_0x502*/
	,0x08		/* id: 	 0x501:DSM_0x501*/
	,0x08		/* id: 	 0x500:DSM_2*/
	,0x08		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects] = {
	 (TxDataPtr)DSM_0x502._c		/* id: 	 0x502:DSM_0x502*/
	,(TxDataPtr)DSM_0x501._c		/* id: 	 0x501:DSM_0x501*/
	,(TxDataPtr)DSM_2._c		/* id: 	 0x500:DSM_2*/
	,(TxDataPtr)DSM._c		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxType[kIlNumberOfTxObjects]={
	 kTxSendCyclic		/* id: 	 0x502:DSM_0x502*/
	,kTxSendCyclic		/* id: 	 0x501:DSM_0x501*/
	,kTxSendCyclic		/* id: 	 0x500:DSM_2*/
	,kTxSendCyclic		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxCyclicCycles[kIlNumberOfTxObjects]={
	 100		/* id: 	 0x502:DSM_0x502*/
	,100		/* id: 	 0x501:DSM_0x501*/
	,100		/* id: 	 0x500:DSM_2*/
	,200		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxEventCycles[kIlNumberOfTxObjects]={
	 100		/* id: 	 0x502:DSM_0x502*/
	,100		/* id: 	 0x501:DSM_0x501*/
	,100		/* id: 	 0x500:DSM_2*/
	,200		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 tIlTxUpdateCounter V_MEMROM2 IlTxUpdateCycles[kIlNumberOfTxObjects]={
	 1		/* id: 	 0x502:DSM_0x502*/
	,1		/* id: 	 0x501:DSM_0x501*/
	,1		/* id: 	 0x500:DSM_2*/
	,1		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxStartCycles[kIlNumberOfTxObjects]={
	 30		/* id: 	 0x502:DSM_0x502*/
	,30		/* id: 	 0x501:DSM_0x501*/
	,30		/* id: 	 0x500:DSM_2*/
	,30		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxCyclesFastTime[kIlNumberOfTxObjects]={
	 0		/* id: 	 0x502:DSM_0x502*/
	,0		/* id: 	 0x501:DSM_0x501*/
	,0		/* id: 	 0x500:DSM_2*/
	,20		/* id: 	 0x3B2:DSM*/
};

V_MEMROM0 V_MEMROM1 tIlTxCounter V_MEMROM2 IlTxCyclesNRepeatTime[kIlNumberOfTxObjects]={
	 0		/* id: 	 0x502:DSM_0x502*/
	,0		/* id: 	 0x501:DSM_0x501*/
	,0		/* id: 	 0x500:DSM_2*/
	,5		/* id: 	 0x3B2:DSM*/
};

/**************************************************************/
/* Receive structures                                             */
/**************************************************************/
V_MEMROM0 V_MEMROM1 tCanRxId V_MEMROM2 CanRxId[kCanNumberOfRxObjects] = {

	 0x367		/* id: 	 0x367:IVI4*/
	,0x351		/* id: 	 0x351:IVI8_DSM*/
	,0x2AE		/* id: 	 0x2AE:VCU1*/
	,0x2A7		/* id: 	 0x2A7:GWB1*/
	,0x28E		/* id: 	 0x28E:BDC3*/
	,0x284		/* id: 	 0x284:ABS1*/
	,0x283		/* id: 	 0x283:BDC6_PEPS1*/
	,0x281		/* id: 	 0x281:BDC5*/
	,0x26E		/* id: 	 0x26E:GWB2*/
	,0x238		/* id: 	 0x238:TCU1*/
};

V_MEMROM0 V_MEMROM1 CanReceiveHandle V_MEMROM2 CanRxMsgIndirection[kCanNumberOfRxObjects] = {
	 0x00		/* id: 	 0x0367:IVI4*/
	,0x01		/* id: 	 0x0351:IVI8_DSM*/
	,0x02		/* id: 	 0x02AE:VCU1*/
	,0x03		/* id: 	 0x02A7:GWB1*/
	,0x04		/* id: 	 0x028E:BDC3*/
	,0x05		/* id: 	 0x0284:ABS1*/
	,0x06		/* id: 	 0x0283:BDC6_PEPS1*/
	,0x07		/* id: 	 0x0281:BDC5*/
	,0x08		/* id: 	 0x026E:GWB2*/
	,0x09		/* id: 	 0x0238:TCU1*/
};

V_MEMROM0 V_MEMROM1 canuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects] = {
	 0x08		/* id: 	 0x367:IVI4*/
	,0x08		/* id: 	 0x351:IVI8_DSM*/
	,0x08		/* id: 	 0x2AE:VCU1*/
	,0x08		/* id: 	 0x2A7:GWB1*/
	,0x08		/* id: 	 0x28E:BDC3*/
	,0x08		/* id: 	 0x284:ABS1*/
	,0x08		/* id: 	 0x283:BDC6_PEPS1*/
	,0x08		/* id: 	 0x281:BDC5*/
	,0x08		/* id: 	 0x26E:GWB2*/
	,0x08		/* id: 	 0x238:TCU1*/
};

V_MEMROM0 V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects] = {
	 (RxDataPtr)IVI4._c		/* id: 	 0x367:IVI4*/
	,(RxDataPtr)IVI8_DSM._c		/* id: 	 0x351:IVI8_DSM*/
	,(RxDataPtr)VCU1._c		/* id: 	 0x2AE:VCU1*/
	,(RxDataPtr)GWB1._c		/* id: 	 0x2A7:GWB1*/
	,(RxDataPtr)BDC3._c		/* id: 	 0x28E:BDC3*/
	,(RxDataPtr)ABS1._c		/* id: 	 0x284:ABS1*/
	,(RxDataPtr)BDC6_PEPS1._c		/* id: 	 0x283:BDC6_PEPS1*/
	,(RxDataPtr)BDC5._c		/* id: 	 0x281:BDC5*/
	,(RxDataPtr)GWB2._c		/* id: 	 0x26E:GWB2*/
	,(RxDataPtr)TCU1._c		/* id: 	 0x238:TCU1*/
};

V_MEMROM0 V_MEMROM1 tIlRxTimeoutCounter V_MEMROM2 IlRxTimeoutTbl[kIlNumberOfRxTimeoutCounters] = {
	 100		/* id:   0x367:IVI4*/
	 ,100		/* id:   0x351:IVI8_DSM*/
	 ,100		/* id:   0x2AE:VCU1*/
	 ,200		/* id:   0x2A7:GWB1*/
	 ,1000		/* id:   0x28E:BDC3*/
	 ,200		/* id:   0x284:ABS1*/
	 ,1000		/* id:   0x283:BDC6_PEPS1*/
	 ,500		/* id:   0x281:BDC5*/
	 ,200		/* id:   0x26E:GWB2*/
	 ,100		/* id:   0x238:TCU1*/
};

V_MEMROM0 V_MEMROM1 canuint8 V_MEMROM2 IlRxCheckSumFlag[kIlNumberOfRxTimeoutCounters] = {
	 0		/* id:   0x367:IVI4*/
	,0		/* id:   0x351:IVI8_DSM*/
	,0		/* id:   0x2AE:VCU1*/
	,0		/* id:   0x2A7:GWB1*/
	,0		/* id:   0x28E:BDC3*/
	,0		/* id:   0x284:ABS1*/
	,0		/* id:   0x283:BDC6_PEPS1*/
	,0		/* id:   0x281:BDC5*/
	,0		/* id:   0x26E:GWB2*/
	,0		/* id:   0x238:TCU1*/
};

V_MEMROM0 V_MEMROM1 tIlRxTimeoutCounter V_MEMROM2 IlRxCyclesFastTime[kIlNumberOfRxTimeoutCounters]={
	 0		/* id: 	 0x367:IVI4*/
	,0		/* id: 	 0x351:IVI8_DSM*/
	,0		/* id: 	 0x2AE:VCU1*/
	,0		/* id: 	 0x2A7:GWB1*/
	,0		/* id: 	 0x28E:BDC3*/
	,0		/* id: 	 0x284:ABS1*/
	,0		/* id: 	 0x283:BDC6_PEPS1*/
	,0		/* id: 	 0x281:BDC5*/
	,0		/* id: 	 0x26E:GWB2*/
	,0		/* id: 	 0x238:TCU1*/
};

V_MEMROM0 V_MEMROM1 tIlRxTimeoutCounter V_MEMROM2 IlRxCyclesNRepeatTime[kIlNumberOfRxTimeoutCounters]={
	 0		/* id: 	 0x367:IVI4*/
	,0		/* id: 	 0x351:IVI8_DSM*/
	,0		/* id: 	 0x2AE:VCU1*/
	,0		/* id: 	 0x2A7:GWB1*/
	,0		/* id: 	 0x28E:BDC3*/
	,0		/* id: 	 0x284:ABS1*/
	,0		/* id: 	 0x283:BDC6_PEPS1*/
	,0		/* id: 	 0x281:BDC5*/
	,0		/* id: 	 0x26E:GWB2*/
	,0		/* id: 	 0x238:TCU1*/
};

/**************************************************************/
/* Signals of send messages                                    */ 
/**************************************************************/
void ILPutTxDSM_0x502_DSM_DriverHeatStopReason(canuint8 sigData)
{
    b_DSM_0x502_DSM_DriverHeatStopReason_b(sigData);

}
void ILPutTxDSM_0x502_DSM_DriverHeatRunType(canuint8 sigData)
{
    b_DSM_0x502_DSM_DriverHeatRunType_b(sigData);

}
void ILPutTxDSM_0x502_DSM_RemoteStatus(canuint8 sigData)
{
    b_DSM_0x502_DSM_RemoteStatus_b(sigData);

}
void ILPutTxDSM_0x502_DSM_PassengerHeatStopReason(canuint8 sigData)
{
    b_DSM_0x502_DSM_PassengerHeatStopReason_b(sigData);

}
void ILPutTxDSM_0x502_DSM_PassengerHeatRunType(canuint8 sigData)
{
    b_DSM_0x502_DSM_PassengerHeatRunType_b(sigData);

}
void ILPutTxDSM_0x502_DSM_EngineRunStatus(canuint8 sigData)
{
    b_DSM_0x502_DSM_EngineRunStatus_b(sigData);

}
void ILPutTxDSM_0x502_DSM_DriverVentilateStopReason(canuint8 sigData)
{
    b_DSM_0x502_DSM_DriverVentilateStopReason_b(sigData);

}
void ILPutTxDSM_0x502_DSM_DriverVentRunType(canuint8 sigData)
{
    b_DSM_0x502_DSM_DriverVentRunType_b(sigData);

}
void ILPutTxDSM_0x502_VehicleRunStatus(canuint8 sigData)
{
    b_DSM_0x502_VehicleRunStatus_b(sigData);

}
void ILPutTxDSM_0x502_DSM_PassengerVentilateStopReason(canuint8 sigData)
{
    b_DSM_0x502_DSM_PassengerVentilateStopReason_b(sigData);

}
void ILPutTxDSM_0x502_DSM_PassengerVentRunType(canuint8 sigData)
{
    b_DSM_0x502_DSM_PassengerVentRunType_b(sigData);

}
void ILPutTxDSM_0x502_DSM_WheelHeatStopReason(canuint8 sigData)
{
    b_DSM_0x502_DSM_WheelHeatStopReason_b(sigData);

}
void ILPutTxDSM_0x502_DSM_SteerWheelHeatRunType(canuint8 sigData)
{
    b_DSM_0x502_DSM_SteerWheelHeatRunType_b(sigData);

}
void ILPutTxDSM_0x502_DSM_ECUVot(canuint8 sigData)
{
    b_DSM_0x502_DSM_ECUVot_b(sigData);

}
void ILPutTxDSM_0x502_DSM_CarPowerMode(canuint8 sigData)
{
    b_DSM_0x502_DSM_CarPowerMode_b(sigData);

}
void ILPutTxDSM_0x502_DSM_PassengerMoveType(canuint8 sigData)
{
    b_DSM_0x502_DSM_PassengerMoveType_b(sigData);

}
void ILPutTxDSM_0x502_DSM_DrHeightLockSts(canuint8 sigData)
{
    b_DSM_0x502_DSM_DrHeightLockSts_b(sigData);

}
void ILPutTxDSM_0x502_DSM_DrLengthLockSts(canuint8 sigData)
{
    b_DSM_0x502_DSM_DrLengthLockSts_b(sigData);

}
void ILPutTxDSM_0x502_DSM_DrBackLockSts(canuint8 sigData)
{
    b_DSM_0x502_DSM_DrBackLockSts_b(sigData);

}
void ILPutTxDSM_0x502_DSM_DrFrontLockSts(canuint8 sigData)
{
    b_DSM_0x502_DSM_DrFrontLockSts_b(sigData);

}
void ILPutTxDSM_0x502_DSM_PaLengthLockSts(canuint8 sigData)
{
    b_DSM_0x502_DSM_PaLengthLockSts_b(sigData);

}
void ILPutTxDSM_0x502_DSM_PaBackLockSts(canuint8 sigData)
{
    b_DSM_0x502_DSM_PaBackLockSts_b(sigData);

}

void ILPutTxDSM_0x501_DSM_DriverHeightMoveReason(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverHeightMoveReason_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverHeightCMD(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverHeightCMD_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverHeightUPSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverHeightUPSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverLengthMoveReason(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverLengthMoveReason_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverLengthCMD(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverLengthCMD_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverHeightDNSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverHeightDNSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverBackMoveReason(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverBackMoveReason_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverBackCMD(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverBackCMD_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverLengthUPSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverLengthUPSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverFrontMoveReason(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverFrontMoveReason_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverFrontCMD(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverFrontCMD_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverLengthDNSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverLengthDNSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerLengthMoveReason(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerLengthMoveReason_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerLengthCMD(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerLengthCMD_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverBackUPSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverBackUPSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerBackMoveReason(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerBackMoveReason_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerBackCMD(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerBackCMD_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverBackDNSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverBackDNSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverFrontUPSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverFrontUPSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverFrontDNSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverFrontDNSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerLengthUPSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerLengthUPSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerLengthDNSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerLengthDNSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerBackUPSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerBackUPSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerBackDNSW(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerBackDNSW_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerLengthLearnSts(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerLengthLearnSts_b(sigData);

}
void ILPutTxDSM_0x501_DSM_PassengerBackLearnSts(canuint8 sigData)
{
    b_DSM_0x501_DSM_PassengerBackLearnSts_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverHeightLearnSt(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverHeightLearnSt_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverLengthLearnSts(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverLengthLearnSts_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverBackLearnSts(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverBackLearnSts_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverFrontLearnSts(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverFrontLearnSts_b(sigData);

}
void ILPutTxDSM_0x501_DSM_DriverMoveType(canuint8 sigData)
{
    b_DSM_0x501_DSM_DriverMoveType_b(sigData);

}

void ILPutTxDSM_2_DSM_DrNtcValue(canuint16 sigData)
{
    b_DSM_2_DSM_DrNtcValue_b(sigData);

}
void ILPutTxDSM_2_DSM_PaNtcValue(canuint16 sigData)
{
    b_DSM_2_DSM_PaNtcValue_b(sigData);

}
void ILPutTxDSM_2_DSM_SteerNtcValue(canuint16 sigData)
{
    b_DSM_2_DSM_SteerNtcValue_b(sigData);

}

void ILPutTxDSM_DSM_FLSeatPosMsg(canuint8 sigData)
{
    b_DSM_DSM_FLSeatPosMsg_b(sigData);

}
void ILPutTxDSM_DSM_FRSeatPosMsg(canuint8 sigData)
{
    b_DSM_DSM_FRSeatPosMsg_b(sigData);

}
void ILPutTxDSM_DSM1_FLSeatMem1Sts(canuint8 sigData)
{
    b_DSM_DSM1_FLSeatMem1Sts_b(sigData);

}
void ILPutTxDSM_DSM_FLSeatMemStsAndMsg(canuint8 sigData)
{
    b_DSM_DSM_FLSeatMemStsAndMsg_b(sigData);

}
void ILPutTxDSM_DSM3_FLSeatMem3Sts(canuint8 sigData)
{
    b_DSM_DSM3_FLSeatMem3Sts_b(sigData);

}
void ILPutTxDSM_DSM2_FLSeatMem2Sts(canuint8 sigData)
{
    b_DSM_DSM2_FLSeatMem2Sts_b(sigData);

}
void ILPutTxDSM_DSM_St_FLSeatmeet(canuint8 sigData)
{
    b_DSM_DSM_St_FLSeatmeet_b(sigData);

}
void ILPutTxDSM_DSM1_FRSeatMem1Sts(canuint8 sigData)
{
    b_DSM_DSM1_FRSeatMem1Sts_b(sigData);

}
void ILPutTxDSM_DSM_FRSeatMemStsAndMsg(canuint8 sigData)
{
    b_DSM_DSM_FRSeatMemStsAndMsg_b(sigData);

}
void ILPutTxDSM_DSM_St_FRSeatmeet(canuint8 sigData)
{
    b_DSM_DSM_St_FRSeatmeet_b(sigData);

}
void ILPutTxDSM_DSM2_FRSeatMem3Sts(canuint8 sigData)
{
    b_DSM_DSM2_FRSeatMem3Sts_b(sigData);

}
void ILPutTxDSM_DSM2_FRSeatMem2Sts(canuint8 sigData)
{
    b_DSM_DSM2_FRSeatMem2Sts_b(sigData);

}
void ILPutTxDSM_DSM_St_PasSeatHeatGear(canuint8 sigData)
{
    b_DSM_DSM_St_PasSeatHeatGear_b(sigData);

}
void ILPutTxDSM_DSM_St_PasSeatHeatSW(canuint8 sigData)
{
    b_DSM_DSM_St_PasSeatHeatSW_b(sigData);

}
void ILPutTxDSM_DSM_St_DriSeatHeatGear(canuint8 sigData)
{
    b_DSM_DSM_St_DriSeatHeatGear_b(sigData);

}
void ILPutTxDSM_DSM_St_DriSeatHeatSW(canuint8 sigData)
{
    b_DSM_DSM_St_DriSeatHeatSW_b(sigData);

}
void ILPutTxDSM_DSM_St_DriSeatVentilationGear(canuint8 sigData)
{
    b_DSM_DSM_St_DriSeatVentilationGear_b(sigData);

}
void ILPutTxDSM_DSM_St_DriSeatVentilationSW(canuint8 sigData)
{
    b_DSM_DSM_St_DriSeatVentilationSW_b(sigData);

}
void ILPutTxDSM_DSM_MassageMode_FB(canuint8 sigData)
{
    b_DSM_DSM_MassageMode_FB_b(sigData);

}
void ILPutTxDSM_DSM_St_PasSeatVentilationGear(canuint8 sigData)
{
    b_DSM_DSM_St_PasSeatVentilationGear_b(sigData);

}
void ILPutTxDSM_DSM_St_PasSeatVentilationSW(canuint8 sigData)
{
    b_DSM_DSM_St_PasSeatVentilationSW_b(sigData);

}
void ILPutTxDSM_IntelligentPowerDown_FB(canuint8 sigData)
{
    b_DSM_IntelligentPowerDown_FB_b(sigData);

}
void ILPutTxDSM_DSM_NapMode_FB(canuint8 sigData)
{
    b_DSM_DSM_NapMode_FB_b(sigData);

}
void ILPutTxDSM_DSM_MassageLevel_FB(canuint8 sigData)
{
    b_DSM_DSM_MassageLevel_FB_b(sigData);

}
void ILPutTxDSM_DSM_SwsHeatSts(canuint8 sigData)
{
    b_DSM_DSM_SwsHeatSts_b(sigData);

}


/**************************************************************/
/* Signals of receive messages                                    */ 
/**************************************************************/
