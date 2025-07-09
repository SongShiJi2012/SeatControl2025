#ifndef          _PROG_H
#define          _PROG_H
#include  "Common.h"
#include "BootFlash.h"
#include "Srvl_E2Cfg_Generation.h"


/* prog request return status */
#define PROG_REQ_OK             (0x0u)
#define PROG_REQ_BUSY           (0x1u)
#define PROG_REQ_PARERR         (0x2u)
#define PROG_REQ_STEPERR        (0x3u)


#define PROG_HAND_OK            (0x0u)
#define PROG_HAND_ERR           (0x1u)

#define PROG_STATE_IDLE         (0x0u)
#define PROG_STATE_WRITE_REQ    (0x1u)
#define PROG_STATE_WRITE_START  (0x2u)
#define PROG_STATE_WRITE_WAIT   (0x3u)
#define PROG_STATE_WRITE_OK     (0x4u)
#define PROG_STATE_ERASE_START  (0x5u)
#define PROG_STATE_ERASE_WAIT   (0x6u)
#define PROG_STATE_ERASE_OK     (0x7u)
#define PROG_STATE_CKS_START    (0x8u)
#define PROG_STATE_CKS_WAIT     (0x9u)
#define PROG_STATE_CKS_OK       (0xau)
#define PROG_STATE_VERIFY_START (0xbu)
#define PROG_STATE_VERIFY_WAIT  (0xcu)
#define PROG_STATE_VERIFY_OK    (0xdu)


extern const INT8U BootloaderSoftwareVersionNumber[D_CustomerBootVersion_Len_15];
extern const INT8U DareBootSoftwareVersionNumber[D_DareBootVersion_Len_8];
extern BOOL    IsOperateFlash; // 当前是否在写Flash标识
extern INT32U  ReqDownloadFlashBlock; // // 请求下载的Block数, 一个Bit代表一个Block
extern INT32U  ReqDownloadFlashBlockCnt; // 统计实际下载的Block数, 一个Bit代表一个Block
extern const INT8U E2promInitBootBufDefine[E2PROM_INIT_BOOT_LEN];
extern const INT8U E2promAppCodeValidFlgDefine[D_E2promAppCodeValidFlg_Len];
extern const INT8U E2promAppCodeInvalidFlgDefine[D_E2promAppCodeValidFlg_Len];

void  Checksum_Crc32_CRCValue(const INT8U *pData, INT32U DataLen);
INT32U      Checksum_Crc32(const INT8U *pData, INT32U DataLen);
INT32U      Checksum_Crc32_FarAddr(INT32U DataAddr, INT32U DataLen);

void        Prog_Init(void);
INT32U      GetGlobalAddr(INT32U  LogicAddr);
BOOL        CheckAppCodeSectorStartAddr(INT32U  LogicAddr);
INT32U      GetAppCodeSectorMaxLen(INT32U  LogicStartAddr);
INT32U  GetAppCodeBlockIndex(INT32U  LogicStartAddr);
INT8U       Prog_WriteFlashDrvToRam(void);
INT8U       Prog_WriteAppCodeToRom(INT16U rDataNum);
BOOL        CheeckFlashDrvIsValid(void);
BOOL        CheeckAppFileIsValid(void);
BOOL        CheckAppCoeValidFlg(void);
BOOL        CheckE2promAppCoeValidFlg(void);

#endif

