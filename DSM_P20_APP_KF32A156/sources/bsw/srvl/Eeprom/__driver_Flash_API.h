/******************************************************************************
 *                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
 ******************************************************************************
 *  @File Name        : __driver_Flash_API.h
 *  @Author           : ChipON AE/FAE Group                                   
 *  @Date             : 2025-04-17
 *  @Chip Version     : A02                                                   
 *  @HW Version       : KF32A156-MINI-EVB_V1.2
 *  @Example Version  : V2.4.0.250417_release
 *  @Description      : 
 *****************************************************************************
 *  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
 *  All rights reserved.                                                      
 *                                                                            
 *  This software is copyright protected and proprietary to                    
 *  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
 ******************************************************************************/

#ifndef DRIVER_FLASH_OP_API_HEAD_H_
#define DRIVER_FLASH_OP_API_HEAD_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ user config 1

#define Function_Parameter_Validate   0x5A5A6688

#define CMD_SUCCESS 				  0x00
#define CMD_ERROR					  0xAA
#define PARAM_ERROR					  0x0C

#define TimeOutCountValue 5000000
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  __FLASH__ 		__attribute__((section(".text")))
#define  __RAM__ 		__attribute__((section(".indata")))

#define optimize_Os		__attribute__((optimize("-Os")))
#define optimize_O2		__attribute__((optimize("-O2")))
#define optimize_O0		__attribute__((optimize("-O0")))

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ user config

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned char  __FLASH_Read_Byte__(unsigned int address);
unsigned int  __FLASH_Read_WORD__(unsigned int address);
unsigned int  __FLASH_Read_One__(unsigned int address);
unsigned int  __FLASH_Read__(unsigned int address,unsigned int length,unsigned int buffers[]);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned int  __FLASH_UNLOCK_FUNCTION__(volatile unsigned int key,volatile unsigned int isopen);

unsigned int  __FLASH_Erase__(volatile unsigned key,volatile unsigned int WritrAddr,
								volatile unsigned int DataLength);
unsigned int  __FLASH_Program__(volatile unsigned int key,volatile unsigned int WritrAddr,
										volatile unsigned int DataLength,unsigned int WriteData[]);
unsigned int  __FLASH_Program_NBytes__(volatile unsigned int key,volatile unsigned int WritrAddr,
										volatile unsigned int DataLength,unsigned int WriteData[]);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ user config 1
#endif /* DRIVER_FLASH_OP_API_HEAD_H_ */
