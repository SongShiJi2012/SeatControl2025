
//*****************************************************************************
//                  Shanghai ChipON Micro-Electronic Co.,Ltd                  
//*****************************************************************************
//  @File Name        : __driver_Flash_API.h
//  @Author           : ChipON AE/FAE Group                                   
//  @Date             : 2024-05-17
//  @Chip Version     : A02                                                   
//  @HW Version       : KF32A156-MINI-EVB_V1.2
//  @Example Version  : V2.2.0.240517_release
//  @Description      : 
//****************************************************************************
//  Copyright (C) by Shanghai ChipON Micro-Electronic Co.,Ltd                 
//  All rights reserved.                                                      
//                                                                            
//  This software is copyright protected and proprietary to                    
//  Shanghai ChipON Micro-Electronic Co.,Ltd.                                 
//*****************************************************************************/
	.text
//###############################################################################
	.EQU  FLASH_WORK_CLR, 					0x50AF0007
	.EQU  FLASH_WORK_CMD,					0x50AF0001
	
	.EQU  Function_Parameter_Validate,   	0x5A5A6688
	.EQU  CMD_SUCCESS, 				  		0x00
	.EQU  CMD_ERROR,					  	0xAA
	.EQU  PARAM_ERROR,					  	0x0C
	.EQU  TimeOutCountValue, 				50000
//###############################################################################
.macro __FLASH_Function__ name
	.section .text$\name
	.align	1
	.export	\name
	.type	\name, @function
	.func \name
\name:
.endm

.macro __RAM_Function__ name
	.section .indata$\name
	.align	1
	.export	\name
	.type	\name, @function
	.func \name
\name:
.endm

.macro __End_Function__ name
		.size	\name, .-\name
		.endfunc
.endm
//###############################################################################
	.SET __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN ,        0
	.SET __FLASH_Driver_Use_LOCK_UNLOCK_Function,		 0
	
//###############################################################################	
.if 0	
	.SET __FLASH_API_LIKE_A150,	1	
.else
.if 1
	.SET __FLASH_API_LIKE_A156,	1	
.else
	.SET __FLASH_API_LIKE_A158,	1
.endif
.endif	
// .if __FLASH_API_LIKE_A158
.if 0
	.EQU  __FLASH_MAX_SIZE__,	(2048*1024-1)
.else
	.EQU  __FLASH_MAX_SIZE__,	(512*1024-1)
.endif
	.EQU  __FLASH_MIN_SIZE__,	(4096) //interrupt vector table


//###############################################################################

.ifdef 	__FLASH_API_LIKE_A150 
	.SET 		FLASH_KEY1,  0x87654321
	.SET 		FLASH_KEY2,  0x05040302
	.SET 		FLASH_KEY3,  0x789ABCDE
	.SET 		FLASH_KEY4,  0x16151413
.else 
.ifdef __FLASH_API_LIKE_A156 
	.SET 		FLASH_KEY1,  0x27654330;
	.SET 		FLASH_KEY2,  0x81040304
	.SET 		FLASH_KEY3,  0x7896dcde
	.SET 		FLASH_KEY4,  0x92151407
.else
.ifdef __FLASH_API_LIKE_A158 
	.SET 		FLASH_KEY1,  0x27654330;
	.SET 		FLASH_KEY2,  0x81040304
	.SET 		FLASH_KEY3,  0x7896dcde
	.SET 		FLASH_KEY4,  0x92151407
.else
	.error  "Err config"
.endif
.endif
.endif
//###############################################################################
	.SET  FLASH_ISPCON0		, 0x40200100
	.SET  FLASH_ISPCON1		, 0x40200104
	.SET  FLASH_ISPCMD		, 0x40200108
	.SET  FLASH_ISPTRG		, 0x4020010C
	.SET  FLASH_ISPADDR		, 0x4020011C
	.SET  FLASH_STATE		, 0x40200120
	.SET  FLASH_NVMUNLOCK	, 0x40200128
	.SET  FLASH_PROUNLOCK	, 0x4020012C
###############################################################################
	__RAM_Function__ __FLASH_UNLOCK_FUNCTION__
	SUB	sp,#32
	//++++++++++++++++++++++++++++++++++++++++++++++
	ST.w	[sp+#0],r0	
	LD   R4,#FLASH_KEY1
	ST.w	[sp+#1],R4
	
	ST.w	[sp+#2],r0
	LD   R4,#FLASH_KEY2
	ST.w	[sp+#3],R4
	
	ST.w	[sp+#4],r1
	LD   R4,#FLASH_KEY3
	ST.w	[sp+#5],R4
	
	ST.w	[sp+#6],r1
	LD   R4,#FLASH_KEY4
	ST.w	[sp+#7],R4
	//++++++++++++++++++++++++++++++++++++++++++++++
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key)
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_UNLOCK
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_UNLOCK
	//++++++++++++++++++++++++++++++++++++++++++++++if(isopen == 0xAA55)
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_UNLOCK
	MOV R2,#0xAA55
	CMP R0,R2
	JZ Cond_OPEN_IN_UNLOCK
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
	JMP Return_CMD_SUCCESS_IN_UNLOCK
Cond_OPEN_IN_UNLOCK:
	//++++++++++++++++++++++++++++++++++++++++++++++	key1 key2
	LD.w	r0,[SP + #1]
	LD.w	r1,[SP + #3]
	LD	r2,#FLASH_NVMUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_UNLOCK
	MOV R2,#0xAA55
	CMP R0,R2
	JNZ Return_CMD_SUCCESS_IN_UNLOCK
	//++++++++++++++++++++++++++++++++++++++++++++++	key3 key4
	LD.w	r0,[SP + #5]
	LD.w	r1,[SP + #7]
	LD	r2,#FLASH_PROUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_UNLOCK
	MOV R2,#0xAA55
	CMP R0,R2
	JNZ Return_CMD_SUCCESS_IN_UNLOCK
	//++++++++++++++++++++++++++++++++++++++++++++++	
Return_CMD_SUCCESS_IN_UNLOCK:
	MOV R0,#0
	JMP Return_PUSH_POP_IN_UNLOCK
Return_PARAM_ERROR_IN_UNLOCK:
	MOV R0,#PARAM_ERROR
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
//++++++++++++++++++++++++++++++++++++++++++++++
Return_PUSH_POP_IN_UNLOCK:	
	ST.w [SP+#0],R0
	ST.w [SP+#1],R0
	ST.w [SP+#2],R0
	ST.w [SP+#3],R0
	ST.w [SP+#4],R0
	ST.w [SP+#5],R0
	ST.w [SP+#6],R0
	ST.w [SP+#7],R0
//++++++++++++++++++++++++++++++++++++++++++++++
	ADD	sp,#32
	JMP	lr
	__End_Function__ __FLASH_UNLOCK_FUNCTION__
	
//#########################################################################################
	 __RAM_Function__ __FLASH_Read_Byte__
	LD.b	r0,[r0]
	JMP	lr
	__End_Function__ __FLASH_Read_Byte__
//#########################################################################################
	__RAM_Function__ __FLASH_Read_WORD__
	LD.w	r0,[r0]
	JMP	lr
	__End_Function__ 	__FLASH_Read_WORD__
//#########################################################################################
	__RAM_Function__  __FLASH_Read_One__
	LD.w	r0,[r0]
	JMP	lr
	__End_Function__ 	__FLASH_Read_One__
#########################################################################################
	__RAM_Function__  __FLASH_Erase__
	SUB	sp,#40
	//++++++++++++++++++++++++++++++++++++++++++++++
	ST.w	[sp+#0],r0	
	LD   R4,#FLASH_KEY1
	ST.w	[sp+#1],R4
	
	ST.w	[sp+#2],r0
	LD   R4,#FLASH_KEY2
	ST.w	[sp+#3],R4
	
	ST.w	[sp+#4],r1
	LD   R4,#FLASH_KEY3
	ST.w	[sp+#5],R4
	
	ST.w	[sp+#6],r1
	LD   R4,#FLASH_KEY4
	ST.w	[sp+#7],R4
	
	ST.w	[sp+#8],r2
	ST.w	[sp+#9],r2
	//++++++++++++++++++++++++++++++++++++++++++++++
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key)
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_ERASE
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++	key1 key2
	LD.w	r0,[SP + #1]
	LD.w	r1,[SP + #3]
	LD	r2,#FLASH_NVMUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++ address check
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_ERASE
	LD R4,#__FLASH_MAX_SIZE__
	CMP R0,R4
	JHI Return_PARAM_ERROR_IN_ERASE
	MOVL R4,#0x3FF
	ANL R1,R4
	JNZ Return_PARAM_ERROR_IN_ERASE
	LD R4,#__FLASH_MIN_SIZE__
	CMP R4,R0
	JHI Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++ len check
	LD.w	r0,[SP + #8]
	LD.w	r1,[SP + #9]
	CMP     R0,R1
	JNZ  Return_PARAM_ERROR_IN_ERASE
	LD 	    R4,#0
	CMP     R0,R4
	JZ   Return_PARAM_ERROR_IN_ERASE
	
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key){
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_ERASE
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++	key3 key4
	LD.w	r0,[SP + #5]
	LD.w	r1,[SP + #7]
	LD	r2,#FLASH_PROUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key){
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_ERASE
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++
.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
	DSI 
.endif
	//++++++++++++++++++++++++++++++++++++++++++++++ length 1K/2K aligned 
ERASE_NEXT_PAGE_IN_ERASE:
	LD.w	r0,[SP + #8]
	LD.w	r1,[SP + #9]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_ERASE
.ifdef __FLASH_API_LIKE_A158 
	MOVL R2,#0x07FF
.else
	MOVL R2,#0x03FF
.endif
	ANL R2,R0,R2
	JNZ Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++ address set
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_ERASE
	LD R4,#__FLASH_MAX_SIZE__
	CMP R0,R4
	JHI Return_PARAM_ERROR_IN_ERASE
	MOVL R4,#0x3FF
	ANL R4,R1,R4
	JNZ Return_PARAM_ERROR_IN_ERASE
	LD R4,#__FLASH_MIN_SIZE__
	CMP R4,R0
	JHI Return_PARAM_ERROR_IN_ERASE
	
	LD R2,#FLASH_ISPADDR
	ST.w [R2],R0
	LD.w R3,[R2]
	CMP R3,R1
	JNZ Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++ set cmd
	LD R2,#FLASH_ISPCMD
	MOVL R0,#0x7FB
	ST.w [R2],R0
	LD.w R3,[R2]
	CMP R3,R0
	JNZ Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++ run cmd
	LD R2,#FLASH_ISPTRG
	LD R0,#FLASH_WORK_CMD
	ST.w [R2],R0
	NOP
	NOP
	NOP
	//++++++++++++++++++++++++++++++++++++++++++++++ wait event
	LD R4,#TimeOutCountValue
ERASE_WAIT_BIT_2_TBIT:
	LD R3,#FLASH_STATE
	LD.w R1,[R3]
	JB R1,#2
	JMP ERASE_END_BIT_2_TBIT
	SUB R4,#1
	JZ ERASE_END_BIT_2_TBIT
	JMP ERASE_WAIT_BIT_2_TBIT
	//++++++++++++++++++++++++++++++++++++++++++++++ is timeout find
ERASE_END_BIT_2_TBIT:	
	CMP R4,#0
	JZ Return_PARAM_ERROR_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++ for next
	LD.w	r0,[SP + #4]
	MOV R1,#1
.ifdef __FLASH_API_LIKE_A158 
	LSL R1,#11  
.else
	LSL R1,#10  
.endif
	ADD R0,R1
	ST.w  [SP+#4],R0
	ST.w  [SP+#6],R0
	
	LD.w	r0,[SP + #8]
	SUB R0,R1
	ST.w  [SP + #8],R0
	ST.w  [SP + #9],R0
	
	JHI ERASE_NEXT_PAGE_IN_ERASE
	//++++++++++++++++++++++++++++++++++++++++++++++ ok
	MOV R0,#0
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
	//++++++++++++++++++++++++++++++++++++++++++++++ ng	
Return_CMD_SUCCESS_IN_ERASE:
	MOV R0,#0
	JMP Return_PUSH_POP_IN_ERASE
Return_PARAM_ERROR_IN_ERASE:
	MOV R0,#PARAM_ERROR
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
//++++++++++++++++++++++++++++++++++++++++++++++
Return_PUSH_POP_IN_ERASE:	
	//++++++++++++++++++++++++++++++++++++++++++++++
.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
	ENI 
.endif
	ST.w [SP+#0],R0
	ST.w [SP+#1],R0
	ST.w [SP+#2],R0
	ST.w [SP+#3],R0
	ST.w [SP+#4],R0
	ST.w [SP+#5],R0
	ST.w [SP+#6],R0
	ST.w [SP+#7],R0
//++++++++++++++++++++++++++++++++++++++++++++++
	ADD	sp,#40
	JMP	lr
	__End_Function__ __FLASH_Erase__
###########################################################################
	__RAM_Function__  __FLASH_Program__
	PUSH R5
	SUB	sp,#48
	//++++++++++++++++++++++++++++++++++++++++++++++
	ST.w	[sp+#0],r0	
	LD   R4,#FLASH_KEY1
	ST.w	[sp+#1],R4
	
	ST.w	[sp+#2],r0
	LD   R4,#FLASH_KEY2
	ST.w	[sp+#3],R4
	
	ST.w	[sp+#4],r1
	LD   R4,#FLASH_KEY3
	ST.w	[sp+#5],R4
	
	ST.w	[sp+#6],r1
	LD   R4,#FLASH_KEY4
	ST.w	[sp+#7],R4
	
	ST.w	[sp+#8],r2
	ST.w	[sp+#9],r2
	ST.w	[sp+#10],r3
	ST.w	[sp+#11],r3
	//++++++++++++++++++++++++++++++++++++++++++++++ clear syc
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
	//++++++++++++++++++++++++++++++++++++++++++++++ address check
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_FAST
	LD R4,#__FLASH_MAX_SIZE__
	CMP R0,R4
	JHI Return_PARAM_ERROR_IN_FAST
	MOVL R4,#0x1FF
	ANL R1,R4
	JNZ Return_PARAM_ERROR_IN_FAST
	LD R4,#__FLASH_MIN_SIZE__
	CMP R4,R0
	JHI Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++ len check
	LD.w	r0,[SP + #8]
	LD.w	r1,[SP + #9]
	CMP     R0,R1
	JNZ  Return_PARAM_ERROR_IN_FAST
	LD 	    R4,#0
	CMP     R0,R4
	JZ   Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key)
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_FAST
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++	key1 key2
	LD.w	r0,[SP + #1]
	LD.w	r1,[SP + #3]
	LD	r2,#FLASH_NVMUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key){
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_FAST
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++	key3 key4
	LD.w	r0,[SP + #5]
	LD.w	r1,[SP + #7]
	LD	r2,#FLASH_PROUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key){
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_FAST
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++ address  re same check
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++ length  512/1024 aligned
	LD.w	r0,[SP + #8]
	LD.w	r1,[SP + #9]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_FAST
.ifdef __FLASH_API_LIKE_A158 
	MOVL R2,#0x03FF
.else
	MOVL R2,#0x01FF
.endif
	ANL R0,R2
	JNZ Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++
.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
	DSI 
.endif
	//++++++++++++++++++++++++++++++++++++++++++++++ dwen bit 3 set
	LD R2,#FLASH_ISPCON0
	SET [R2],#3
	LD.b R3,[R2]
	MOV R2,#0x4B
	CMP R3,R2
	JNZ Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++ cmd page write
	LD R2,#FLASH_ISPCMD
	MOVL R0,#0x7e5
	MOVL R1,#0x7e5
	ST.w [R2],R0
	LD.w R3,[R2]
	CMP R3,R1
	JZ Fast_Process_Start
		//++ cmd failed
		LD R2,#FLASH_ISPCON0
		LD R0,#FLASH_WORK_CLR
		ST.w [R2],R0
		.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
		ENI 
		.endif
		JMP Return_PARAM_ERROR_IN_FAST
	//++++++++++++++++++++++++++++++++++++++++++++++
Fast_Process_Start:
	LD.w R0,[SP + #4]
	LD.w R1,[SP + #6]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_FAST

	LD.w R1,[SP + #8]
	LD.w R2,[SP + #9]
	CMP R2,R1
	JNZ Return_PARAM_ERROR_IN_FAST
	
	LD.w R2,[SP + #10]
	LD.w R3,[SP + #11]
	CMP R2,R3
	JNZ Return_PARAM_ERROR_IN_FAST
	
	JMP FAST_FIRST_HALF_PAGE
	//++++++++++++++++++++++++++++++++++++++++++++++
FAST_NEXT_HALF_PAGE:
	LD R3,#FLASH_ISPCMD
	MOVL R4,#0x7e5
	MOVL R5,#0x7e5
	ST.w [R3],R4
	LD.w R4,[R3]
	CMP R4,R5
	JNZ Return_PARAM_ERROR_IN_FAST	
	
FAST_FIRST_HALF_PAGE:
	LD R3,#FLASH_ISPTRG
	LD R4,#FLASH_WORK_CMD
	ST.w [R3],R4
	NOP
	NOP
	NOP
	//++++++++++++++++++++++++++++++++++++++++++++++
	MOV R4,#64
	//++++++++++++++++++++++++++++++++++++++++++++++
Fast_DATE_TRAN:
	LD.w R3,[R2++]
	ST.w [R0++],R3
	LD.w R3,[R2++]
	ST.w [R0++],R3
.ifdef __FLASH_API_LIKE_A158 
	LD.w R3,[R2++]
	ST.w [R0++],R3
	LD.w R3,[R2++]
	ST.w [R0++],R3
	SUB R1,#16
.else
	SUB R1,#8
.endif
	//---------------------------------------
	LD R3,#TimeOutCountValue
FAST_WAIT_BIT_3_TBUSY:
	LD R5,#FLASH_STATE
	JB [R5],#3
	JMP Fast_DATE_IF_TRAN
	SUB R3,#1
	JZ  FAST_END_BIT_3_TBUSY_TIMEOUT
	JMP FAST_WAIT_BIT_3_TBUSY
	
FAST_END_BIT_3_TBUSY_TIMEOUT:
	MOV R0,#0x55555555
	JMP Return_TimeOut
	//---------------------------------------
Fast_DATE_IF_TRAN:	
	
	MOV R3,R4
	CMP R3,#65
	JHI Return_PARAM_ERROR_IN_FAST
	SUB R4,#1
	JNZ Fast_DATE_TRAN
	//++++++++++++++++++++++++++++++++++++++++++++++
	
	LD R3,#TimeOutCountValue
FAST_WAIT_BIT_2_TBIT:
	LD R5,#FLASH_STATE
	JB [R5],#2
	JMP FAST_PAGE_HALF_FINISH
	SUB R3,#1
	JZ  FAST_TIMEOUT_BIT_2_TBIT
	JMP FAST_WAIT_BIT_2_TBIT
	//++++++++++++++++++++++++++++++++++++++++++++++
FAST_TIMEOUT_BIT_2_TBIT:
	MOV R0,#0xAAAAAAAA
	JMP Return_TimeOut

FAST_PAGE_HALF_FINISH:
	//++++++++++++++++++++++++++++++++++++++++++++++
.ifdef __FLASH_API_LIKE_A158 
	MOVL R3,#0x03FF
.else
	MOVL R3,#0x01FF
.endif
	ANL R3,R1
	JNZ Return_PARAM_ERROR_IN_FAST
	CMP R1,#0
	JNZ FAST_NEXT_HALF_PAGE
	//++++++++++++++++++++++++++++++++++++++++++++++
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
Return_CMD_SUCCESS_IN_FAST:
	MOV R0,#0
	JMP Return_PUSH_POP_IN_FAST
	
Return_PARAM_ERROR_IN_FAST:
	MOV R0,#PARAM_ERROR
	
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
	JMP Return_PUSH_POP_IN_FAST
	
Return_TimeOut:
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
//++++++++++++++++++++++++++++++++++++++++++++++
Return_PUSH_POP_IN_FAST:	
	.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
	ENI
	.endif
	ST.w [SP+#0],R0
	ST.w [SP+#1],R0
	ST.w [SP+#2],R0
	ST.w [SP+#3],R0
	ST.w [SP+#4],R0
	ST.w [SP+#5],R0
	ST.w [SP+#6],R0
	ST.w [SP+#7],R0
	ST.w [SP+#8],R0
	ST.w [SP+#9],R0
	ST.w [SP+#10],R0
	ST.w [SP+#11],R0
//++++++++++++++++++++++++++++++++++++++++++++++
	ADD	sp,#48
	POP R5
	JMP	lr
	__End_Function__	__FLASH_Program__
#########################################################################################	
	__RAM_Function__  __FLASH_Program_NBytes__
	PUSH R5
	SUB	sp,#48
	//++++++++++++++++++++++++++++++++++++++++++++++
	ST.w	[sp+#0],r0	
	LD   R4,#FLASH_KEY1
	ST.w	[sp+#1],R4
	
	ST.w	[sp+#2],r0
	LD   R4,#FLASH_KEY2
	ST.w	[sp+#3],R4
	
	ST.w	[sp+#4],r1
	LD   R4,#FLASH_KEY3
	ST.w	[sp+#5],R4
	
	ST.w	[sp+#6],r1
	LD   R4,#FLASH_KEY4
	ST.w	[sp+#7],R4
	
	ST.w	[sp+#8],r2
	ST.w	[sp+#9],r2
	ST.w	[sp+#10],r3
	ST.w	[sp+#11],r3
	//++++++++++++++++++++++++++++++++++++++++++++++ clear syc
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
	//++++++++++++++++++++++++++++++++++++++++++++++ address check
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_NBytes
	LD R4,#__FLASH_MAX_SIZE__
	CMP R0,R4
	JHI Return_PARAM_ERROR_IN_NBytes
	MOVL R4,#0x7
	ANL R1,R4
	JNZ Return_PARAM_ERROR_IN_NBytes
	LD R4,#__FLASH_MIN_SIZE__
	CMP R4,R0
	JHI Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++ len check
	LD.w	r0,[SP + #8]
	LD.w	r1,[SP + #9]
	CMP     R0,R1
	JNZ  Return_PARAM_ERROR_IN_NBytes
	LD 	    R4,#0
	CMP     R0,R4
	JZ   Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key)
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_NBytes
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++	key1 key2
	LD.w	r0,[SP + #1]
	LD.w	r1,[SP + #3]
	LD	r2,#FLASH_NVMUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key){
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_NBytes
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++	key3 key4
	LD.w	r0,[SP + #5]
	LD.w	r1,[SP + #7]
	LD	r2,#FLASH_PROUNLOCK
	ST.w	[R2],R0
	ST.w	[R2],R1
	//++++++++++++++++++++++++++++++++++++++++++++++if(Function_Parameter_Validate != key){
	LD.w	r0,[SP + #0]
	LD.w	r1,[SP + #2]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_NBytes
	LD 	R2,#Function_Parameter_Validate
	CMP R0,R2
	JNZ Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++ address  re same check
	LD.w	r0,[SP + #4]
	LD.w	r1,[SP + #6]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++ length  8aligned
	LD.w	r0,[SP + #8]
	LD.w	r1,[SP + #9]
	CMP R0,R1
	JNZ  Return_PARAM_ERROR_IN_NBytes
	MOV R2,#0x07
	ANL R0,R2
	JNZ Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++
.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
	DSI 
.endif
	//++++++++++++++++++++++++++++++++++++++++++++++ dwen bit 3 set
	LD R2,#FLASH_ISPCON0
	SET [R2],#3
	LD.b R3,[R2]
	MOV R2,#0x4B
	CMP R3,R2
	JNZ Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++ cmd word write
	LD R2,#FLASH_ISPCMD
	MOVL R0,#0x7f5
	MOVL R1,#0x7f5
	ST.w [R2],R0
	LD.w R3,[R2]
	CMP R3,R1
	JZ NBytes_Process_Start
		//++ cmd failed
		LD R2,#FLASH_ISPCON0
		LD R0,#FLASH_WORK_CLR
		ST.w [R2],R0
		.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
		ENI 
		.endif
		JMP Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++
NBytes_Process_Start:
	LD.w R0,[SP + #4]
	LD.w R1,[SP + #6]
	CMP R0,R1
	JNZ Return_PARAM_ERROR_IN_NBytes

	LD.w R1,[SP + #8]
	LD.w R2,[SP + #9]
	CMP R2,R1
	JNZ Return_PARAM_ERROR_IN_NBytes
	
	LD.w R2,[SP + #10]
	LD.w R3,[SP + #11]
	CMP R2,R3
	JNZ Return_PARAM_ERROR_IN_NBytes
	//++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++
NBytes_DATE_TRAN:
	LD.w R3,[R2++]
	ST.w [R0++],R3
	LD.w R3,[R2++]
	ST.w [R0++],R3
.ifdef __FLASH_API_LIKE_A158 
	LD.w R3,[R2++]
	ST.w [R0++],R3
	LD.w R3,[R2++]
	ST.w [R0++],R3
	SUB R1,#16
.else	
	SUB R1,#8
.endif	
	LD R3,#FLASH_ISPTRG
	LD R4,#FLASH_WORK_CMD
	ST.w [R3],R4
	NOP
	NOP
	NOP
	//---------------------------------------
	LD R3,#TimeOutCountValue
NBytes_WAIT_BIT_2_TBIT:
	LD R5,#FLASH_STATE
	JB [R5],#2
	JMP NBytes_DATE_IF_TRAN
	SUB R3,#1
	JZ  NBytes_END_BIT_2_TBIT_TIMEOUT
	JMP NBytes_WAIT_BIT_2_TBIT
	//---------------------------------------
NBytes_DATE_IF_TRAN:	
.ifdef __FLASH_API_LIKE_A158 
	MOVL R3,#0x0F
.else
	MOVL R3,#0x07
.endif
	ANL R3,R1
	JNZ Return_PARAM_ERROR_IN_NBytes
	CMP R1,#0
	JNZ NBytes_DATE_TRAN
	//++++++++++++++++++++++++++++++++++++++++++++++
NBytes_END_BIT_2_TBIT_TIMEOUT:
NBytes_FINSH_BIT_2_TBIT:
	//++++++++++++++++++++++++++++++++++++++++++++++
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
Return_CMD_SUCCESS_IN_NBytes:
	MOV R0,#0
	JMP Return_PUSH_POP_IN_NBytes
Return_PARAM_ERROR_IN_NBytes:
	MOV R0,#PARAM_ERROR
	
	LD	R2,#FLASH_WORK_CLR
	LD	R3,#FLASH_ISPCON0
	ST.w	[R3],R2
//++++++++++++++++++++++++++++++++++++++++++++++
Return_PUSH_POP_IN_NBytes:	
	.if __FLASH_ERASE_WRITE_ISR_CLOSE_AND_OPEN
	ENI
	.endif
	ST.w [SP+#0],R0
	ST.w [SP+#1],R0
	ST.w [SP+#2],R0
	ST.w [SP+#3],R0
	ST.w [SP+#4],R0
	ST.w [SP+#5],R0
	ST.w [SP+#6],R0
	ST.w [SP+#7],R0
	ST.w [SP+#8],R0
	ST.w [SP+#9],R0
	ST.w [SP+#10],R0
	ST.w [SP+#11],R0
//++++++++++++++++++++++++++++++++++++++++++++++
	ADD	sp,#48
	POP R5
	JMP LR
	__End_Function__ __FLASH_Program_NBytes__
	