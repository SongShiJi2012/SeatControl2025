#ifndef _SRVL_EEPROM_H_            
#define _SRVL_EEPROM_H_

/*************************************************************************************************
 * Include Files
 *************************************************************************************************/
#include "Srvl_Eeprom.h"
#include "pins_driver.h"
#include "Common.h"
#include "fee.h"

typedef enum
{
    EN_SRVL_EERPROM_SECTOR_0 = 512,
    EN_SRVL_EERPROM_SECTOR_1 = 510,
    EN_SRVL_EERPROM_SECTOR_2 = 508,
    EN_SRVL_EERPROM_SECTOR_3 = 506,
    EN_SRVL_EERPROM_SECTOR_4 = 504,
    EN_SRVL_EERPROM_SECTOR_5 = 502,
    EN_SRVL_EERPROM_SECTOR_MAX = 513,
}enSrvlEepromSectorType;

typedef struct
{
    INT32U StartAddr;
    INT32U SectorNum;
    INT32U FlashSector;
}Srvl_Eeprom_ConfType;

extern void Srvl_Eeprom_init(void);
extern FEE_StatusType Srvl_Eeprom_Write(INT32U WriteAddr, INT32U  DataLength, const INT32U  *Buffers);
extern FEE_StatusType Srvl_Eeprom_Read(INT32U  ReadAddr, INT32U  DataLength, INT32U  *Buffers);

#endif
