#ifndef           E2PROM_H
#define           E2PROM_H
#include  "Common.h"
#include "Srvl_E2Cfg_Generation.h"
#include "EmulatedEE.h"

#define EEPROMBUFFMAXNUM						(448u) /*���ζ�дeeprom�������󳤶�*/
#define EEPROMOPERATEERRORMAXTIME        		(3u) // �����ʧ�ܺ� ��д����
#define	EEPROM_ADDRESS							(0x0u) 	 	/*��EEPROM��ʼ��ַ*/
#define	EEPROM_SIZE								(EN_EERPROM_SECTOR_NUM_MAX * EEPROMBUFFMAXNUM)/*��EEPROM����*/
typedef enum
{
	EEPROM_IDLE = 0,
	EEPROM_READ_START,	
	EEPROM_READ_SUCCESS,
	EEPROM_READ_ERROR,
	EEPROM_ERASE_START,
	EEPROM_WRITE_START,
	EEPROM_WRITE_SUCCESS,
	EEPROM_VERIFY_SUCCESS,
	EEPROM_WRITE_ERROR,
	EEPROM_WRITE_WAIT_FOR_10MS,
	EEPROM_ERROR,
} EEPROMOperateState;

typedef  enum
{
	E2PROM_OPOK = 0,
	E2PROM_READNG,
	E2PROM_WRITENG,
}E2PROMOperateResult;

typedef        enum
{
	EEOpNULL,
	EEOpWR,
	EEOpRD
}eE2promOpType;

typedef struct
{
	E2PROMOperateResult                     OperateResult;
	EEPROMOperateState                      OperateState;         // EEPROM����״̬
	INT8U                                   E2promOpErrorTime;
	INT8U                                   WriteCheckSum;
	INT16U                                  WritedDataNum;       // д�����ݸ���
	INT32U                                  E2pDataAddress;      // ָ��EEPROM��ַ
	INT16U                                  DataNum;             // ���ݸ���
	INT8U                                   *pData;              // RAM��ַ(��������ַ)
    INT16U                                  OpIndex;             /* E2PROM ��Ŀ��� */
    eE2promOpType		                    OpType;              /* �������� */
} EEPROMInfoStructType;

extern EEPROMInfoStructType E2PROMOpInfo;

#define		IsE2promIDLE()     				(EEPROM_IDLE == E2PROMOpInfo.OperateState)
#define		IsE2promBusy()     				(EEPROM_IDLE != E2PROMOpInfo.OperateState)
#define		IsE2promWriteBusy()				(IsE2promBusy() && (EEOpWR == E2PROMOpInfo.OpType))
#define		IsE2promReadBusy()				(IsE2promBusy() && (EEOpRD == E2PROMOpInfo.OpType))
#define		IsE2promOptResultEnd(Index)    	((E2promOpOK == Srvl_GetE2DataBlockOptResult(Srvl_GetE2DefineDataBlockID(Index))) || (E2promOpFail == Srvl_GetE2DataBlockOptResult(Srvl_GetE2DefineDataBlockID(Index))))
#define		IsE2promOptResultOK(Index)      (E2promOpOK == Srvl_GetE2DataBlockOptResult(Srvl_GetE2DefineDataBlockID(Index)))
#define		IsAppE2promOptReqIDLE(Index)    (EN_EEPROM_STA_IDLE == Srvl_GetE2DataBlockEepOptReq(Srvl_GetE2DefineDataBlockID(Index)))

extern void Srvl_E2OptTask(void);
extern void Srvl_E2OptInit(void);
extern void Srvl_E2Read(INT32U lu32Dest, INT32U lu32Size, INT8U *lpu8ReadBuf);
extern INT8U Srvl_E2Write(INT32U lu32Dest, INT32U lu32Size, const INT8U * lpu8DataBuf);
extern void Srvl_RestoreDataFromBackUpID(INT16U DataBlockId);
extern void Srvl_WriteDataToBackUpID(INT16U DataBlockId);

extern void Srvl_E2SetOpt(INT8U DataBlockId, EEPROMOperateState eOpStep);

extern INT8U Srvl_GetMemIndexDataU8(enSrvMemIndex MemIndex);
extern void Srvl_SetMemIndexDataU8(enSrvMemIndex MemIndex, INT8U u8SourceData);
extern INT16U Srvl_GetMemIndexDataU16(enSrvMemIndex MemIndex);
extern void Srvl_SetMemIndexDataU16(enSrvMemIndex MemIndex, INT16U u16SourceData);
extern BOOL Srvl_WriteMemIndexData(enSrvMemIndex MemIndex, INT8U* ptru8data, INT8U len);
extern void Srvl_ReadMemIndexData(enSrvMemIndex MemIndex, INT8U* ptru8data, INT8U len);
extern void Srvl_PreSaveMemDataFunc(void);

#endif

