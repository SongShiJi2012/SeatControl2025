/************************************************************************************************
File created time : 2025-05-15 15:14:09
Tool Name :         DSM_If_Generate.py + DSM_If_Generate.xlsx
Filename:           Rte_VfbInterface.c
Author:             Ai
Description:        Generate VFB interface
/************************************************************************************************/
/************************************************************************************************
                                   C O P Y R I G H T  
-------------------------------------------------------------------------------  
Copyright (c) 2013-2025 by Shenzhen Southern Dare Automotive Electronics Co.,Ltd.. All rights reserved.  
/************************************************************************************************/

#include "Rte_VfbInterface.h"

/*********************************Variable Definition *******************************************/
#if 0
主驾高度调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrHeightSwitchCmd = 0;

#if 0
主驾纵向调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrLengthSwitchCmd = 0;

#if 0
主驾靠背调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrBackSwitchCmd = 0;

#if 0
主驾腿托调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrFrontSwitchCmd = 0;

#if 0
主驾高度输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrHeightMotorCmd = 0;

#if 0
主驾纵向输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrLengthMotorCmd = 0;

#if 0
主驾靠背输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrBackMotorCmd = 0;

#if 0
主驾腿托输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrFrontMotorCmd = 0;

#if 0
主驾高度调节动作原因
#endif
INT8U DrHeightMotorReason = 0;

#if 0
主驾纵向调节动作原因
#endif
INT8U DrLengthMotorReason = 0;

#if 0
主驾靠背调节动作原因
#endif
INT8U DrBackMotorReason = 0;

#if 0
主驾腿托调节动作原因
#endif
INT8U DrFrontMotorReason = 0;

#if 0
主驾高度自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U DrHeightAutoRunFlag = 0;

#if 0
主驾纵向自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U DrLengthAutoRunFlag = 0;

#if 0
主驾靠背自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U DrBackAutoRunFlag = 0;

#if 0
主驾腿托自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U DrFrontAutoRunFlag = 0;

#if 0
主驾当前电机控制类型:
0:无动作;
1:HUM;
2:舒适;
3:记忆调用;
4:手动调节;
5:学习调节
#endif
INT8U DrMoveType = 0;

#if 0
主驾高度霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U DrHeightHallErr = 0;

#if 0
主驾纵向霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U DrLengthHallErr = 0;

#if 0
主驾靠背霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U DrBackHallErr = 0;

#if 0
主驾腿托霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U DrFrontHallErr = 0;

#if 0
主驾任一霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U DrAnyoneHallErr = 0;

#if 0
主驾高度霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U DrHeightDTCHallErr = 0;

#if 0
主驾纵向霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U DrLengthDTCHallErr = 0;

#if 0
主驾靠背霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U DrBackDTCHallErr = 0;

#if 0
主驾腿托霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U DrFrontDTCHallErr = 0;

#if 0
主驾任一霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U DrAnyoneDTCHallErr = 0;

#if 0
主驾高度堵转故障标志:
0:无故障
1:故障
#endif
INT8U DrHeightStallErr = 0;

#if 0
主驾纵向堵转故障标志:
0:无故障
1:故障
#endif
INT8U DrLengthStallErr = 0;

#if 0
主驾靠背堵转故障标志:
0:无故障
1:故障
#endif
INT8U DrBackStallErr = 0;

#if 0
主驾腿托堵转故障标志:
0:无故障
1:故障
#endif
INT8U DrFrontStallErr = 0;

#if 0
主驾任一堵转故障标志:
0:无故障
1:故障
#endif
INT8U DrAnyoneStallErr = 0;

#if 0
主驾高度继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U DrHeightRelayAdheErr = 0;

#if 0
主驾纵向继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U DrLengthRelayAdheErr = 0;

#if 0
主驾靠背继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U DrBackRelayAdheErr = 0;

#if 0
主驾腿托继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U DrFrontRelayAdheErr = 0;

#if 0
主驾任一继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U DrAnyoneRelayAdheErr = 0;

#if 0
主驾高度开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U DrHeightSwitchAdheErr = 0;

#if 0
主驾纵向开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U DrLengthSwitchAdheErr = 0;

#if 0
主驾靠背开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U DrBackSwitchAdheErr = 0;

#if 0
主驾腿托开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U DrFrontSwitchAdheErr = 0;

#if 0
主驾高度向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrHeightSwitchAdheErr_ForWard = 0;

#if 0
主驾高度向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrHeightSwitchAdheErr_Back = 0;

#if 0
主驾纵向向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrLengthSwitchAdheErr_ForWard = 0;

#if 0
主驾纵向向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrLengthSwitchAdheErr_Back = 0;

#if 0
主驾靠背向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrBackSwitchAdheErr_ForWard = 0;

#if 0
主驾靠背向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrBackSwitchAdheErr_Back = 0;

#if 0
主驾腿托向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrFrontSwitchAdheErr_ForWard = 0;

#if 0
主驾腿托向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrFrontSwitchAdheErr_Back = 0;

#if 0
主驾任一开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U DrAnyoneSwitchAdheErr = 0;

#if 0
主驾高度软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U DrHeightSoftStopErr = 0;

#if 0
主驾纵向软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U DrLengthSoftStopErr = 0;

#if 0
主驾靠背软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U DrBackSoftStopErr = 0;

#if 0
主驾腿托软止点故障:
0:无故障
1:上/前
2:下/后
#endif
INT8U DrFrontSoftStopErr = 0;

#if 0
主驾任一软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U DrAnyoneSoftStopErr = 0;

#if 0
主驾高度电机运行超时标志:
0:无故障
1:超时
#endif
INT8U DrHeightMotorTimeOutErr = 0;

#if 0
主驾纵向电机运行超时标志:
0:无故障
1:超时
#endif
INT8U DrLengthMotorTimeOutErr = 0;

#if 0
主驾靠背电机运行超时标志:
0:无故障
1:超时
#endif
INT8U DrBackMotorTimeOutErr = 0;

#if 0
主驾腿托电机运行超时标志:
0:无故障
1:超时
#endif
INT8U DrFrontMotorTimeOutErr = 0;

#if 0
副驾高度调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaHeightSwitchCmd = 0;

#if 0
副驾纵向调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaLengthSwitchCmd = 0;

#if 0
副驾靠背调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaBackSwitchCmd = 0;

#if 0
副驾腿托调节开关输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaFrontSwitchCmd = 0;

#if 0
副驾高度输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaHeightMotorCmd = 0;

#if 0
副驾纵向输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaLengthMotorCmd = 0;

#if 0
副驾靠背输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaBackMotorCmd = 0;

#if 0
副驾腿托输出给电机驱动的命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaFrontMotorCmd = 0;

#if 0
副驾高度调节动作原因
#endif
INT8U PaHeightMotorReason = 0;

#if 0
副驾纵向调节动作原因
#endif
INT8U PaLengthMotorReason = 0;

#if 0
副驾靠背调节动作原因
#endif
INT8U PaBackMotorReason = 0;

#if 0
副驾腿托调节动作原因
#endif
INT8U PaFrontMotorReason = 0;

#if 0
副驾高度自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U PaHeightAutoRunFlag = 0;

#if 0
副驾纵向自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U PaLengthAutoRunFlag = 0;

#if 0
副驾靠背自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U PaBackAutoRunFlag = 0;

#if 0
副驾腿托自动运动成功标志位:
0:Invalid
1:Running
2:Success
3:Fail
#endif
INT8U PaFrontAutoRunFlag = 0;

#if 0
副驾电机当前动作类型:
0:无动作;
1:HUM;
2:舒适;
3:记忆调用;
4:手动调节;
5:学习调节
#endif
INT8U PaMoveType = 0;

#if 0
副驾高度霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U PaHeightHallErr = 0;

#if 0
副驾纵向霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U PaLengthHallErr = 0;

#if 0
副驾靠背霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U PaBackHallErr = 0;

#if 0
副驾腿托霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U PaFrontHallErr = 0;

#if 0
副驾任一霍尔故障标志-当前(无调节动作时清除):
0:无故障
1:故障
#endif
INT8U PaAnyoneHallErr = 0;

#if 0
副驾高度霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U PaHeightDTCHallErr = 0;

#if 0
副驾纵向霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U PaLengthDTCHallErr = 0;

#if 0
副驾靠背霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U PaBackDTCHallErr = 0;

#if 0
副驾腿托霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U PaFrontDTCHallErr = 0;

#if 0
副驾任一霍尔故障标志-DTC(检测到霍尔变化时清除):
0:无故障
1:故障
#endif
INT8U PaAnyoneDTCHallErr = 0;

#if 0
副驾高度堵转故障标志:
0:无故障
1:故障
#endif
INT8U PaHeightStallErr = 0;

#if 0
副驾纵向堵转故障标志:
0:无故障
1:故障
#endif
INT8U PaLengthStallErr = 0;

#if 0
副驾靠背堵转故障标志:
0:无故障
1:故障
#endif
INT8U PaBackStallErr = 0;

#if 0
副驾腿托堵转故障标志:
0:无故障
1:故障
#endif
INT8U PaFrontStallErr = 0;

#if 0
副驾任一堵转故障标志:
0:无故障
1:故障
#endif
INT8U PaAnyoneStallErr = 0;

#if 0
副驾高度继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U PaHeightRelayAdheErr = 0;

#if 0
副驾纵向继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U PaLengthRelayAdheErr = 0;

#if 0
副驾靠背继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U PaBackRelayAdheErr = 0;

#if 0
副驾腿托继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U PaFrontRelayAdheErr = 0;

#if 0
副驾任一继电器粘连故障标志:
0:无故障
1:上前粘连故障
2:下后粘连故障
#endif
INT8U PaAnyoneRelayAdheErr = 0;

#if 0
副驾高度开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U PaHeightSwitchAdheErr = 0;

#if 0
副驾纵向开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U PaLengthSwitchAdheErr = 0;

#if 0
副驾靠背开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U PaBackSwitchAdheErr = 0;

#if 0
副驾腿托开关粘连故障标志:后期修改粘连逻辑删除
0:无故障
1:故障
#endif
INT8U PaFrontSwitchAdheErr = 0;

#if 0
副驾高度向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaHeightSwitchAdheErr_ForWard = 0;

#if 0
副驾高度向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaHeightSwitchAdheErr_Back = 0;

#if 0
副驾纵向向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaLengthSwitchAdheErr_ForWard = 0;

#if 0
副驾纵向向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaLengthSwitchAdheErr_Back = 0;

#if 0
副驾靠背向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaBackSwitchAdheErr_ForWard = 0;

#if 0
副驾靠背向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaBackSwitchAdheErr_Back = 0;

#if 0
副驾腿托向前开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaFrontSwitchAdheErr_ForWard = 0;

#if 0
副驾腿托向后开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaFrontSwitchAdheErr_Back = 0;

#if 0
副驾任一开关粘连故障标志:
0:无故障
1:故障
#endif
INT8U PaAnyoneSwitchAdheErr = 0;

#if 0
副驾高度软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U PaHeightSoftStopErr = 0;

#if 0
副驾纵向软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U PaLengthSoftStopErr = 0;

#if 0
副驾靠背软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U PaBackSoftStopErr = 0;

#if 0
副驾腿托软止点故障:
0:无故障
1:上/前
2:下/后
#endif
INT8U PaFrontSoftStopErr = 0;

#if 0
副驾任一软止点故障标志:
0:无故障
1:上/前
2:下/后
#endif
INT8U PaAnyoneSoftStopErr = 0;

#if 0
副驾高度电机运行超时标志:
0:无故障
1:超时
#endif
INT8U PaHeightMotorTimeOutErr = 0;

#if 0
副驾纵向电机运行超时标志:
0:无故障
1:超时
#endif
INT8U PaLengthMotorTimeOutErr = 0;

#if 0
副驾靠背电机运行超时标志:
0:无故障
1:超时
#endif
INT8U PaBackMotorTimeOutErr = 0;

#if 0
副驾腿托电机运行超时标志:
0:无故障
1:超时
#endif
INT8U PaFrontMotorTimeOutErr = 0;

#if 0
主驾迎宾纵向请求位置
#endif
INT16U DrWelLengthReqPosi = 0;

#if 0
主驾迎宾靠背请求位置
#endif
INT16U DrWelBackReqPosi = 0;

#if 0
副驾迎宾纵向请求位置
#endif
INT16U PaWelLengthReqPosi = 0;

#if 0
副驾迎宾靠背请求位置
#endif
INT16U PaWelBackReqPosi = 0;

#if 0
记忆调用高度霍尔
#endif
INT16U DrMemHeightReqPosi = 0;

#if 0
记忆调用纵向霍尔
#endif
INT16U DrMemLengthReqPosi = 0;

#if 0
记忆调用靠背霍尔
#endif
INT16U DrMemBackReqPosi = 0;

#if 0
记忆调用腿托霍尔
#endif
INT16U DrMemFrontReqPosi = 0;

#if 0
记忆调用高度霍尔
#endif
INT16U PaMemHeightReqPosi = 0;

#if 0
记忆调用纵向霍尔
#endif
INT16U PaMemLengthReqPosi = 0;

#if 0
记忆调用靠背霍尔
#endif
INT16U PaMemBackReqPosi = 0;

#if 0
记忆调用腿托霍尔
#endif
INT16U PaMemFrontReqPosi = 0;

#if 0
主驾小憩调用位置-高度
#endif
INT16U DrResHeightReqPosi = 0;

#if 0
主驾小憩调用位置-纵向
#endif
INT16U DrResLengthReqPosi = 0;

#if 0
主驾小憩调用位置-靠背
#endif
INT16U DrResBackReqPosi = 0;

#if 0
主驾小憩调用位置-腿托
#endif
INT16U DrResFrontReqPosi = 0;

#if 0
主驾小憩回位位置-高度
#endif
INT16U DrResHeightReCallPosi = 0;

#if 0
主驾小憩回位位置-纵向
#endif
INT16U DrResLengthReCallPosi = 0;

#if 0
主驾小憩回位位置-靠背
#endif
INT16U DrResBackReCallPosi = 0;

#if 0
主驾小憩回位位置-腿托
#endif
INT16U DrResFrontReCallPosi = 0;

#if 0
/*主驾加热档位*/
enHeatLvlSts_EN_HEAT_LVL_OFF = 0,    /* Default value */
enHeatLvlSts_EN_HEAT_LVL_1,
enHeatLvlSts_EN_HEAT_LVL_2,
enHeatLvlSts_EN_HEAT_LVL_3
#endif
INT8U DrHeat = 0;

#if 0
/*副驾/二排加热档位*/
enHeatLvlSts_EN_HEAT_LVL_OFF = 0,    /* Default value */
enHeatLvlSts_EN_HEAT_LVL_1,
enHeatLvlSts_EN_HEAT_LVL_2,
enHeatLvlSts_EN_HEAT_LVL_3
#endif
INT8U PaHeat = 0;

#if 0
/*方向盘/三排加热档位*/
enHeatLvlSts_EN_HEAT_LVL_OFF = 0,    /* Default value */
enHeatLvlSts_EN_HEAT_LVL_1,
enHeatLvlSts_EN_HEAT_LVL_2,
enHeatLvlSts_EN_HEAT_LVL_3
#endif
INT8U ThirdHeat = 0;

#if 0
/*主驾加热硬线*/
FALSE = 0,    /* Default value */
TRUE
#endif
INT8U DrHeatIo = 0;

#if 0
/*副驾/二排加热硬线*/
FALSE = 0,    /* Default value */
TRUE
#endif
INT8U PaHeatIo = 0;

#if 0
/*方向盘/三排加热硬线*/
FALSE = 0,    /* Default value */
TRUE
#endif
INT8U ThirdHeatIo = 0;

#if 0
/*主驾加热输出故障状态*/
enNoneHeatCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U DrHeatCmdFaultSts = 0;

#if 0
/*副驾/二排加热输出故障状态*/
enNoneHeatCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U PaHeatCmdFaultSts = 0;

#if 0
/*方向盘/三排加热输出故障状态*/
enNoneHeatCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U ThirdHeatCmdFaultSts = 0;

#if 0
/*主驾加热NTC故障状态*/
enNoneHeatNTCFault = 0,    /* Default value */
enNTCShortToGND,
enNTCOpenLoad,
enNTCOverRange
#endif
INT8U DrHeatNTCFaultSts = 0;

#if 0
/*副驾/二排加热NTC故障状态*/
enNoneHeatNTCFault = 0,    /* Default value */
enNTCShortToGND,
enNTCOpenLoad,
enNTCOverRange
#endif
INT8U PaHeatNTCFaultSts = 0;

#if 0
/*方向盘/三排加热NTC故障状态*/
enNoneHeatNTCFault = 0,    /* Default value */
enNTCShortToGND,
enNTCOpenLoad,
enNTCOverRange
#endif
INT8U ThirdHeatNTCFaultSts = 0;

#if 0
主驾加热禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U DrHeatStopReason = 0;

#if 0
副驾/二排加热禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U PaHeatStopReason = 0;

#if 0
方向盘/三排加热禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U ThirdHeatStopReason = 0;

#if 0
主驾加热类型
0:无
1:HMI
2:TBox
#endif
INT8U DrHeatType = 0;

#if 0
副驾/二排加热类型
0:无
1:HMI
2:Tbox
#endif
INT8U PaHeatType = 0;

#if 0
方向盘/三排加热类型
0:无
1:HMI
2:Tbox
#endif
INT8U ThirdHeatType = 0;

#if 0
发动机运行状态
0:无
1:运行
#endif
INT8U EngineRunFlag = 0;

#if 0
远程控制状态
0:无
1:可控
#endif
INT8U RemoteModeFlag = 0;

#if 0
主驾加热运行状态-P20
0:无
1:运行
#endif
INT8U DrHeatRunState = 0;

#if 0
副驾/二排加热运行状态-P20
0:无
1:运行
#endif
INT8U PaHeatRunState = 0;

#if 0
方向盘/三排加热运行状态-P20
0:无
1:运行
#endif
INT8U ThirdHeatRunState = 0;

#if 0
/*主驾通风档位*/
enVentLvlSts_EN_Vent_LVL_OFF = 0,    /* Default value */
enVentLvlSts_EN_Vent_LVL_1,
enVentLvlSts_EN_Vent_LVL_2,
enVentLvlSts_EN_Vent_LVL_3
#endif
INT8U DrVent = 0;

#if 0
/*副驾/二排通风档位*/
enVentLvlSts_EN_Vent_LVL_OFF = 0,    /* Default value */
enVentLvlSts_EN_Vent_LVL_1,
enVentLvlSts_EN_Vent_LVL_2,
enVentLvlSts_EN_Vent_LVL_3
#endif
INT8U PaVent = 0;

#if 0
/*方向盘/三排通风档位*/
enVentLvlSts_EN_Vent_LVL_OFF = 0,    /* Default value */
enVentLvlSts_EN_Vent_LVL_1,
enVentLvlSts_EN_Vent_LVL_2,
enVentLvlSts_EN_Vent_LVL_3
#endif
INT8U ThirdVent = 0;

#if 0
/*主驾通风输出故障状态*/
enNoneVentCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U DrVentCmdFaultSts = 0;

#if 0
/*副驾/二排通风输出故障状态*/
enNoneVentCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U PaVentCmdFaultSts = 0;

#if 0
/*方向盘/三排通风输出故障状态*/
enNoneVentCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U ThirdVentCmdFaultSts = 0;

#if 0
主驾通风禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U DrVentStopReason = 0;

#if 0
副驾/二排通风禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U PaVentStopReason = 0;

#if 0
方向盘/三排通风禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U ThirdVentStopReason = 0;

#if 0
主驾通风类型
0:无
1:HMI
2:TBox
#endif
INT8U DrVentType = 0;

#if 0
副驾/二排通风类型
0:无
1:HMI
2:Tbox
#endif
INT8U PaVentType = 0;

#if 0
方向盘/三排通风类型
0:无
1:HMI
2:Tbox
#endif
INT8U ThirdVentType = 0;

#if 0
主驾通风运行状态-P20
0:无
1:运行
#endif
INT8U DrVentRunState = 0;

#if 0
副驾/二排通风运行状态-P20
0:无
1:运行
#endif
INT8U PaVentRunState = 0;

#if 0
方向盘/三排通风运行状态-P20
0:无
1:运行
#endif
INT8U ThirdVentRunState = 0;

#if 0
学习标志
0:无学习
1:请求学习
#endif
INT8U DrLearnEnable = 0;

#if 0
学习状态

#endif
INT8U DrLearnSts = 0;

#if 0
学习退出原因
#endif
INT8U LearnExitCause = 0;

#if 0
/*主驾加热输出故障状态*/
enNoneHeatCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U DrHeatCmdFaultSts4DTC = 0;

#if 0
/*副驾/二排加热输出故障状态*/
enNoneHeatCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U PaHeatCmdFaultSts4DTC = 0;

#if 0
/*方向盘/三排加热输出故障状态*/
enNoneHeatCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U ThirdHeatCmdFaultSts4DTC = 0;

#if 0
/*主驾通风输出故障状态*/
enNoneVentCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U DrVentCmdFaultSts4DTC = 0;

#if 0
/*副驾/二排通风输出故障状态*/
enNoneVentCmdFault = 0,    /* Default value */
enShortToGND,
enOpenLoad
#endif
INT8U PaVentCmdFaultSts4DTC = 0;

#if 0
副驾学习状态

#endif
INT8U PaLearnSts = 0;

#if 0
副驾学习退出原因
#endif
INT8U PaLearnExitCause = 0;

#if 0
整车运行状态
0:无
1:运行
#endif
INT8U VehicleRunFlag = 0;

#if 0
P档标志位
0:非P;
1:P档
#endif
INT8U GearP = 0;

#if 0
网络busoff标志位
0:正常;
1:busoff故障
#endif
INT8U BusoffFlag = 0;

#if 0
主驾迎宾当前运行状态:
0x00: enNull 默认初始化状态
0x01: enBWMoveSuccess 后移成功
0x02: enFWMoveSuccess 前移成功
0x03: enBWMoveFail 后移失败
0x04: enFWMoveFail 前移失败
0x05: enFWBreakBW 后移过程中执行前移
0x06: enBWBreakFW 前移过程中执行后移
0x07: enBWOngoing 后移过程中
0x08: enFWOngoing 前移过程中
0x09: enExit 退出迎宾功能
#endif
INT8U DrWelcomeRunSts = 0;

#if 0
副驾迎宾当前运行状态:
0x00: enNull 默认初始化状态
0x01: enBWMoveSuccess 后移成功
0x02: enFWMoveSuccess 前移成功
0x03: enBWMoveFail 后移失败
0x04: enFWMoveFail 前移失败
0x05: enFWBreakBW 后移过程中执行前移
0x06: enBWBreakFW 前移过程中执行后移
0x07: enBWOngoing 后移过程中
0x08: enFWOngoing 前移过程中
0x09: enExit 退出迎宾功能
#endif
INT8U PaWelcomeRunSts = 0;

#if 0
主驾迎宾功能座椅停止原因
0x00: enNull 默认初始化状态
0x01: enIVIPrmClose 功能配置关闭
0x02: enHallFault 霍尔故障
0x03: enLockFault堵转故障
0x04: enBusoff Busoff故障
0x05: enOtherMove 高优先级动作中断
0x06: enNotGearP 非P档
0x07: enNotLearn 未学习
0x08: enBackResetFaild 靠背恢复失败
0x09: enLengthMoveFaild 纵向移动反馈失败
0x0A: enBWMoveSuccess 后移成功
0x0B: enFWMoveSuccess 前移成功
#endif
INT8U DrWelcomeStopReason = 0;

#if 0
副驾迎宾功能座椅停止原因
0x00: enNull 默认初始化状态
0x01: enIVIPrmClose 功能配置关闭
0x02: enHallFault 霍尔故障
0x03: enLockFault堵转故障
0x04: enBusoff Busoff故障
0x05: enOtherMove 高优先级动作中断
0x06: enNotGearP 非P档
0x07: enNotLearn 未学习
0x08: enBackResetFaild 靠背恢复失败
0x09: enLengthMoveFaild 纵向移动反馈失败
0x0A: enBWMoveSuccess 后移成功
0x0B: enFWMoveSuccess 前移成功
#endif
INT8U PaWelcomeStopReason = 0;

#if 0
主驾迎宾纵向请求命令
0x00: enNULL 默认初始化状态
0x01: enBackwardSts 后移状态
0x02: enForwardSts 前移状态
#endif
INT8U DrWelLengthReqCMD = 0;

#if 0
副驾迎宾纵向请求命令
0x00: enNULL 默认初始化状态
0x01: enBackwardSts 后移状态
0x02: enForwardSts 前移状态
#endif
INT8U PaWelLengthReqCMD = 0;

#if 0
主驾所有电机学习标志:
0:No
1:Yes
#endif
INT8U DrLearnResult = 0;

#if 0
副驾所有电机学习标志:
0:No
1:Yes
#endif
INT8U PaLearnResult = 0;

#if 0
是否在P/N档:
0:No
1:Yes
#endif
INT8U GearPN = 0;

#if 0
副驾学习标志
0:无学习
1:请求学习
#endif
INT8U PaLearnEnable = 0;

#if 0
小憩模式
0x0:Inactive
0x1:关闭小憩模式
0x2:打开小憩模式
0x3:ERROR
#endif
INT8U NapMode = 0;

#if 0
记忆设置停止原因
0:无
1:未学习
2:座椅运动
3:霍尔故障
4:继电器粘连
5:堵转故障
6:非ON档
7:档位非P/N
8:车速故障
9:位置错误
10:记忆功能失能
11:小憩模式打开
12:电机运动
13:e2p故障
14:电压故障
#endif
INT8U MemSetStopReason = 0;

#if 0
记忆调用状态
0:无调用
1:有调用
#endif
INT8U SeatMemoryValidReq = 0;

#if 0
记忆调用停止原因
0:无
1:未学习
2:座椅运动
3:霍尔故障
4:继电器粘连
5:堵转故障
6:非ON档
7:档位非P/N
8:车速故障
9:位置错误
10:记忆功能失能
11:小憩模式打开
12:电机运动
13:e2p故障
14:电压故障
#endif
INT8U MemCallStopReason = 0;

#if 0
提示前置条件停止原因
0:无
1:未学习
2:座椅运动
3:霍尔故障
4:继电器粘连
5:堵转故障
6:非ON档
7:档位非P/N
8:车速故障
9:位置错误
10:记忆功能失能
11:小憩模式打开
12:电机运动
13:e2p故障
14:电压故障
#endif
INT8U PreMemRemindStop = 0;

#if 0
车速小于5km/h标志
0:大于5
1:小于5
#endif
INT8U SpeedLessThan5_Flag = 0;

#if 0
内测CAN发送主驾加热禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U CANDrHeatStopReason = 0;

#if 0
内测CAN发送副驾/二排加热禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U CANPaHeatStopReason = 0;

#if 0
内测CAN发送方向盘/三排加热禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U CANThirdHeatStopReason = 0;

#if 0
内测CAN发送主驾通风禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U CANDrVentStopReason = 0;

#if 0
内测CAN发送副驾/二排通风禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U CANPaVentStopReason = 0;

#if 0
内测CAN发送方向盘/三排通风禁能类型
0:无禁能
1:电压模式禁能
2:存在故障
3:互斥命令有效
4:恢复出厂
5:输出超时
6:掉线禁能
#endif
INT8U CANThirdVentStopReason = 0;

#if 0
主驾加热配置
0:不存在
1:存在
#endif
INT8U DrHeatEnable = 0;

#if 0
副驾/二排加热配置
0:不存在
1:存在
#endif
INT8U SecondHeatEnable = 0;

#if 0
方向盘/三排加热配置
0:不存在
1:存在
#endif
INT8U ThirdHeatEnable = 0;

#if 0
主驾通风配置
0:不存在
1:存在
#endif
INT8U DrVentEnable = 0;

#if 0
副驾/二排通风配置
0:不存在
1:存在
#endif
INT8U SecondVentEnable = 0;

#if 0
方向盘/三排通风配置
0:不存在
1:存在
#endif
INT8U ThirdVentEnable = 0;

#if 0
副驾记忆设置停止原因
0:无
1:未学习
2:座椅运动
3:霍尔故障
4:继电器粘连
5:堵转故障
6:非ON档
7:档位非P/N
8:车速故障
9:位置错误
10:记忆功能失能
11:小憩模式打开
12:电机运动
13:e2p故障
14:电压故障
#endif
INT8U PaMemSetStopReason = 0;

#if 0
副驾记忆调用状态
0:无调用
1:有调用
#endif
INT8U PaSeatMemoryValidReq = 0;

#if 0
副驾记忆调用停止原因
0:无
1:未学习
2:座椅运动
3:霍尔故障
4:继电器粘连
5:堵转故障
6:非ON档
7:档位非P/N
8:车速故障
9:位置错误
10:记忆功能失能
11:小憩模式打开
12:电机运动
13:e2p故障
14:电压故障
#endif
INT8U PaMemCallStopReason = 0;

#if 0
副驾提示前置条件停止原因
0:无
1:未学习
2:座椅运动
3:霍尔故障
4:继电器粘连
5:堵转故障
6:非ON档
7:档位非P/N
8:车速故障
9:位置错误
10:记忆功能失能
11:小憩模式打开
12:电机运动
13:e2p故障
14:电压故障
#endif
INT8U PaPreMemRemindStop = 0;

#if 0
满足通风加热通用前置条件标志位
0:不满足
1:满足
#endif
INT8U HVCommPC = 0;

#if 0
迎宾智能下电状态
0:未激活;
1:激活
#endif
INT8U tPwrDnSts = 0;

#if 0
小憩的按摩档位请求 - 按摩模块使用
#endif
INT8U Res_MassageLevel_Req = 0;

#if 0
小憩的按摩模式请求 - 按摩模块使用
#endif
INT8U Res_MassageMode_Req = 0;

#if 0
电压模式
0 : StopVolt
1 : LowVolt
2 : NormalVolt
3 : HighVolt
4 : OverVolt
#endif
INT8U VoltMode = 0;

#if 0
整车电源档位
0:OFF
1:ACC
2:ON
3:CRANK
#endif
INT8U PowerMode = 0;

#if 0
电机调节电压是否满足:
0:不满足
1:满足
#endif
INT8U VoltSatisfy = 0;

#if 0
方向盘加热最大时间,单位:s
#endif
INT8U SwHeatMaxTime = 0;

#if 0
主驾高度学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrHeightLearnCmd = 0;

#if 0
主驾纵向学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrLengthLearnCmd = 0;

#if 0
主驾靠背学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrBackLearnCmd = 0;

#if 0
主驾腿托学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U DrFrontLearnCmd = 0;

#if 0
副驾高度学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaHeightLearnCmd = 0;

#if 0
副驾纵向学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaLengthLearnCmd = 0;

#if 0
副驾靠背学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaBackLearnCmd = 0;

#if 0
副驾腿托学习输入的请求命令
0:无命令;
1:上前;
2:下后;
#endif
INT8U PaFrontLearnCmd = 0;

#if 0
主驾高度复位输入的请求坐标

#endif
INT16U DrHeightResetReqPosi = 0;

#if 0
主驾纵向复位输入的请求坐标

#endif
INT16U DrLengthResetReqPosi = 0;

#if 0
主驾靠背复位输入的请求坐标

#endif
INT16U DrBackResetReqPosi = 0;

#if 0
主驾腿托复位输入的请求坐标

#endif
INT16U DrFrontResetReqPosi = 0;

#if 0
副驾高度复位输入的请求坐标

#endif
INT16U PaHeightResetReqPosi = 0;

#if 0
副驾纵向复位输入的请求坐标

#endif
INT16U PaLengthResetReqPosi = 0;

#if 0
副驾靠背复位输入的请求坐标

#endif
INT16U PaBackResetReqPosi = 0;

#if 0
副驾腿托复位输入的请求坐标

#endif
INT16U PaFrontResetReqPosi = 0;


/*********************************Get/Set Function *********************************************/
void Rte_SetVfb_DrHeightSwitchCmd(INT8U SetValue)
{
    DrHeightSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_DrHeightSwitchCmd(void)
{
    return DrHeightSwitchCmd;
}

void Rte_SetVfb_DrLengthSwitchCmd(INT8U SetValue)
{
    DrLengthSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_DrLengthSwitchCmd(void)
{
    return DrLengthSwitchCmd;
}

void Rte_SetVfb_DrBackSwitchCmd(INT8U SetValue)
{
    DrBackSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_DrBackSwitchCmd(void)
{
    return DrBackSwitchCmd;
}

void Rte_SetVfb_DrFrontSwitchCmd(INT8U SetValue)
{
    DrFrontSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_DrFrontSwitchCmd(void)
{
    return DrFrontSwitchCmd;
}

void Rte_SetVfb_DrHeightMotorCmd(INT8U SetValue)
{
    DrHeightMotorCmd = SetValue;
}
INT8U Rte_GetVfb_DrHeightMotorCmd(void)
{
    return DrHeightMotorCmd;
}

void Rte_SetVfb_DrLengthMotorCmd(INT8U SetValue)
{
    DrLengthMotorCmd = SetValue;
}
INT8U Rte_GetVfb_DrLengthMotorCmd(void)
{
    return DrLengthMotorCmd;
}

void Rte_SetVfb_DrBackMotorCmd(INT8U SetValue)
{
    DrBackMotorCmd = SetValue;
}
INT8U Rte_GetVfb_DrBackMotorCmd(void)
{
    return DrBackMotorCmd;
}

void Rte_SetVfb_DrFrontMotorCmd(INT8U SetValue)
{
    DrFrontMotorCmd = SetValue;
}
INT8U Rte_GetVfb_DrFrontMotorCmd(void)
{
    return DrFrontMotorCmd;
}

void Rte_SetVfb_DrHeightMotorReason(INT8U SetValue)
{
    DrHeightMotorReason = SetValue;
}
INT8U Rte_GetVfb_DrHeightMotorReason(void)
{
    return DrHeightMotorReason;
}

void Rte_SetVfb_DrLengthMotorReason(INT8U SetValue)
{
    DrLengthMotorReason = SetValue;
}
INT8U Rte_GetVfb_DrLengthMotorReason(void)
{
    return DrLengthMotorReason;
}

void Rte_SetVfb_DrBackMotorReason(INT8U SetValue)
{
    DrBackMotorReason = SetValue;
}
INT8U Rte_GetVfb_DrBackMotorReason(void)
{
    return DrBackMotorReason;
}

void Rte_SetVfb_DrFrontMotorReason(INT8U SetValue)
{
    DrFrontMotorReason = SetValue;
}
INT8U Rte_GetVfb_DrFrontMotorReason(void)
{
    return DrFrontMotorReason;
}

void Rte_SetVfb_DrHeightAutoRunFlag(INT8U SetValue)
{
    DrHeightAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_DrHeightAutoRunFlag(void)
{
    return DrHeightAutoRunFlag;
}

void Rte_SetVfb_DrLengthAutoRunFlag(INT8U SetValue)
{
    DrLengthAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_DrLengthAutoRunFlag(void)
{
    return DrLengthAutoRunFlag;
}

void Rte_SetVfb_DrBackAutoRunFlag(INT8U SetValue)
{
    DrBackAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_DrBackAutoRunFlag(void)
{
    return DrBackAutoRunFlag;
}

void Rte_SetVfb_DrFrontAutoRunFlag(INT8U SetValue)
{
    DrFrontAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_DrFrontAutoRunFlag(void)
{
    return DrFrontAutoRunFlag;
}

void Rte_SetVfb_DrMoveType(INT8U SetValue)
{
    DrMoveType = SetValue;
}
INT8U Rte_GetVfb_DrMoveType(void)
{
    return DrMoveType;
}

void Rte_SetVfb_DrHeightHallErr(INT8U SetValue)
{
    DrHeightHallErr = SetValue;
}
INT8U Rte_GetVfb_DrHeightHallErr(void)
{
    return DrHeightHallErr;
}

void Rte_SetVfb_DrLengthHallErr(INT8U SetValue)
{
    DrLengthHallErr = SetValue;
}
INT8U Rte_GetVfb_DrLengthHallErr(void)
{
    return DrLengthHallErr;
}

void Rte_SetVfb_DrBackHallErr(INT8U SetValue)
{
    DrBackHallErr = SetValue;
}
INT8U Rte_GetVfb_DrBackHallErr(void)
{
    return DrBackHallErr;
}

void Rte_SetVfb_DrFrontHallErr(INT8U SetValue)
{
    DrFrontHallErr = SetValue;
}
INT8U Rte_GetVfb_DrFrontHallErr(void)
{
    return DrFrontHallErr;
}

void Rte_SetVfb_DrAnyoneHallErr(INT8U SetValue)
{
    DrAnyoneHallErr = SetValue;
}
INT8U Rte_GetVfb_DrAnyoneHallErr(void)
{
    return DrAnyoneHallErr;
}

void Rte_SetVfb_DrHeightDTCHallErr(INT8U SetValue)
{
    DrHeightDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_DrHeightDTCHallErr(void)
{
    return DrHeightDTCHallErr;
}

void Rte_SetVfb_DrLengthDTCHallErr(INT8U SetValue)
{
    DrLengthDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_DrLengthDTCHallErr(void)
{
    return DrLengthDTCHallErr;
}

void Rte_SetVfb_DrBackDTCHallErr(INT8U SetValue)
{
    DrBackDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_DrBackDTCHallErr(void)
{
    return DrBackDTCHallErr;
}

void Rte_SetVfb_DrFrontDTCHallErr(INT8U SetValue)
{
    DrFrontDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_DrFrontDTCHallErr(void)
{
    return DrFrontDTCHallErr;
}

void Rte_SetVfb_DrAnyoneDTCHallErr(INT8U SetValue)
{
    DrAnyoneDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_DrAnyoneDTCHallErr(void)
{
    return DrAnyoneDTCHallErr;
}

void Rte_SetVfb_DrHeightStallErr(INT8U SetValue)
{
    DrHeightStallErr = SetValue;
}
INT8U Rte_GetVfb_DrHeightStallErr(void)
{
    return DrHeightStallErr;
}

void Rte_SetVfb_DrLengthStallErr(INT8U SetValue)
{
    DrLengthStallErr = SetValue;
}
INT8U Rte_GetVfb_DrLengthStallErr(void)
{
    return DrLengthStallErr;
}

void Rte_SetVfb_DrBackStallErr(INT8U SetValue)
{
    DrBackStallErr = SetValue;
}
INT8U Rte_GetVfb_DrBackStallErr(void)
{
    return DrBackStallErr;
}

void Rte_SetVfb_DrFrontStallErr(INT8U SetValue)
{
    DrFrontStallErr = SetValue;
}
INT8U Rte_GetVfb_DrFrontStallErr(void)
{
    return DrFrontStallErr;
}

void Rte_SetVfb_DrAnyoneStallErr(INT8U SetValue)
{
    DrAnyoneStallErr = SetValue;
}
INT8U Rte_GetVfb_DrAnyoneStallErr(void)
{
    return DrAnyoneStallErr;
}

void Rte_SetVfb_DrHeightRelayAdheErr(INT8U SetValue)
{
    DrHeightRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrHeightRelayAdheErr(void)
{
    return DrHeightRelayAdheErr;
}

void Rte_SetVfb_DrLengthRelayAdheErr(INT8U SetValue)
{
    DrLengthRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrLengthRelayAdheErr(void)
{
    return DrLengthRelayAdheErr;
}

void Rte_SetVfb_DrBackRelayAdheErr(INT8U SetValue)
{
    DrBackRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrBackRelayAdheErr(void)
{
    return DrBackRelayAdheErr;
}

void Rte_SetVfb_DrFrontRelayAdheErr(INT8U SetValue)
{
    DrFrontRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrFrontRelayAdheErr(void)
{
    return DrFrontRelayAdheErr;
}

void Rte_SetVfb_DrAnyoneRelayAdheErr(INT8U SetValue)
{
    DrAnyoneRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrAnyoneRelayAdheErr(void)
{
    return DrAnyoneRelayAdheErr;
}

void Rte_SetVfb_DrHeightSwitchAdheErr(INT8U SetValue)
{
    DrHeightSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrHeightSwitchAdheErr(void)
{
    return DrHeightSwitchAdheErr;
}

void Rte_SetVfb_DrLengthSwitchAdheErr(INT8U SetValue)
{
    DrLengthSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrLengthSwitchAdheErr(void)
{
    return DrLengthSwitchAdheErr;
}

void Rte_SetVfb_DrBackSwitchAdheErr(INT8U SetValue)
{
    DrBackSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrBackSwitchAdheErr(void)
{
    return DrBackSwitchAdheErr;
}

void Rte_SetVfb_DrFrontSwitchAdheErr(INT8U SetValue)
{
    DrFrontSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrFrontSwitchAdheErr(void)
{
    return DrFrontSwitchAdheErr;
}

void Rte_SetVfb_DrHeightSwitchAdheErr_ForWard(INT8U SetValue)
{
    DrHeightSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_DrHeightSwitchAdheErr_ForWard(void)
{
    return DrHeightSwitchAdheErr_ForWard;
}

void Rte_SetVfb_DrHeightSwitchAdheErr_Back(INT8U SetValue)
{
    DrHeightSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_DrHeightSwitchAdheErr_Back(void)
{
    return DrHeightSwitchAdheErr_Back;
}

void Rte_SetVfb_DrLengthSwitchAdheErr_ForWard(INT8U SetValue)
{
    DrLengthSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_DrLengthSwitchAdheErr_ForWard(void)
{
    return DrLengthSwitchAdheErr_ForWard;
}

void Rte_SetVfb_DrLengthSwitchAdheErr_Back(INT8U SetValue)
{
    DrLengthSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_DrLengthSwitchAdheErr_Back(void)
{
    return DrLengthSwitchAdheErr_Back;
}

void Rte_SetVfb_DrBackSwitchAdheErr_ForWard(INT8U SetValue)
{
    DrBackSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_DrBackSwitchAdheErr_ForWard(void)
{
    return DrBackSwitchAdheErr_ForWard;
}

void Rte_SetVfb_DrBackSwitchAdheErr_Back(INT8U SetValue)
{
    DrBackSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_DrBackSwitchAdheErr_Back(void)
{
    return DrBackSwitchAdheErr_Back;
}

void Rte_SetVfb_DrFrontSwitchAdheErr_ForWard(INT8U SetValue)
{
    DrFrontSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_DrFrontSwitchAdheErr_ForWard(void)
{
    return DrFrontSwitchAdheErr_ForWard;
}

void Rte_SetVfb_DrFrontSwitchAdheErr_Back(INT8U SetValue)
{
    DrFrontSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_DrFrontSwitchAdheErr_Back(void)
{
    return DrFrontSwitchAdheErr_Back;
}

void Rte_SetVfb_DrAnyoneSwitchAdheErr(INT8U SetValue)
{
    DrAnyoneSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_DrAnyoneSwitchAdheErr(void)
{
    return DrAnyoneSwitchAdheErr;
}

void Rte_SetVfb_DrHeightSoftStopErr(INT8U SetValue)
{
    DrHeightSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_DrHeightSoftStopErr(void)
{
    return DrHeightSoftStopErr;
}

void Rte_SetVfb_DrLengthSoftStopErr(INT8U SetValue)
{
    DrLengthSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_DrLengthSoftStopErr(void)
{
    return DrLengthSoftStopErr;
}

void Rte_SetVfb_DrBackSoftStopErr(INT8U SetValue)
{
    DrBackSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_DrBackSoftStopErr(void)
{
    return DrBackSoftStopErr;
}

void Rte_SetVfb_DrFrontSoftStopErr(INT8U SetValue)
{
    DrFrontSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_DrFrontSoftStopErr(void)
{
    return DrFrontSoftStopErr;
}

void Rte_SetVfb_DrAnyoneSoftStopErr(INT8U SetValue)
{
    DrAnyoneSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_DrAnyoneSoftStopErr(void)
{
    return DrAnyoneSoftStopErr;
}

void Rte_SetVfb_DrHeightMotorTimeOutErr(INT8U SetValue)
{
    DrHeightMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_DrHeightMotorTimeOutErr(void)
{
    return DrHeightMotorTimeOutErr;
}

void Rte_SetVfb_DrLengthMotorTimeOutErr(INT8U SetValue)
{
    DrLengthMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_DrLengthMotorTimeOutErr(void)
{
    return DrLengthMotorTimeOutErr;
}

void Rte_SetVfb_DrBackMotorTimeOutErr(INT8U SetValue)
{
    DrBackMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_DrBackMotorTimeOutErr(void)
{
    return DrBackMotorTimeOutErr;
}

void Rte_SetVfb_DrFrontMotorTimeOutErr(INT8U SetValue)
{
    DrFrontMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_DrFrontMotorTimeOutErr(void)
{
    return DrFrontMotorTimeOutErr;
}

void Rte_SetVfb_PaHeightSwitchCmd(INT8U SetValue)
{
    PaHeightSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_PaHeightSwitchCmd(void)
{
    return PaHeightSwitchCmd;
}

void Rte_SetVfb_PaLengthSwitchCmd(INT8U SetValue)
{
    PaLengthSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_PaLengthSwitchCmd(void)
{
    return PaLengthSwitchCmd;
}

void Rte_SetVfb_PaBackSwitchCmd(INT8U SetValue)
{
    PaBackSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_PaBackSwitchCmd(void)
{
    return PaBackSwitchCmd;
}

void Rte_SetVfb_PaFrontSwitchCmd(INT8U SetValue)
{
    PaFrontSwitchCmd = SetValue;
}
INT8U Rte_GetVfb_PaFrontSwitchCmd(void)
{
    return PaFrontSwitchCmd;
}

void Rte_SetVfb_PaHeightMotorCmd(INT8U SetValue)
{
    PaHeightMotorCmd = SetValue;
}
INT8U Rte_GetVfb_PaHeightMotorCmd(void)
{
    return PaHeightMotorCmd;
}

void Rte_SetVfb_PaLengthMotorCmd(INT8U SetValue)
{
    PaLengthMotorCmd = SetValue;
}
INT8U Rte_GetVfb_PaLengthMotorCmd(void)
{
    return PaLengthMotorCmd;
}

void Rte_SetVfb_PaBackMotorCmd(INT8U SetValue)
{
    PaBackMotorCmd = SetValue;
}
INT8U Rte_GetVfb_PaBackMotorCmd(void)
{
    return PaBackMotorCmd;
}

void Rte_SetVfb_PaFrontMotorCmd(INT8U SetValue)
{
    PaFrontMotorCmd = SetValue;
}
INT8U Rte_GetVfb_PaFrontMotorCmd(void)
{
    return PaFrontMotorCmd;
}

void Rte_SetVfb_PaHeightMotorReason(INT8U SetValue)
{
    PaHeightMotorReason = SetValue;
}
INT8U Rte_GetVfb_PaHeightMotorReason(void)
{
    return PaHeightMotorReason;
}

void Rte_SetVfb_PaLengthMotorReason(INT8U SetValue)
{
    PaLengthMotorReason = SetValue;
}
INT8U Rte_GetVfb_PaLengthMotorReason(void)
{
    return PaLengthMotorReason;
}

void Rte_SetVfb_PaBackMotorReason(INT8U SetValue)
{
    PaBackMotorReason = SetValue;
}
INT8U Rte_GetVfb_PaBackMotorReason(void)
{
    return PaBackMotorReason;
}

void Rte_SetVfb_PaFrontMotorReason(INT8U SetValue)
{
    PaFrontMotorReason = SetValue;
}
INT8U Rte_GetVfb_PaFrontMotorReason(void)
{
    return PaFrontMotorReason;
}

void Rte_SetVfb_PaHeightAutoRunFlag(INT8U SetValue)
{
    PaHeightAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_PaHeightAutoRunFlag(void)
{
    return PaHeightAutoRunFlag;
}

void Rte_SetVfb_PaLengthAutoRunFlag(INT8U SetValue)
{
    PaLengthAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_PaLengthAutoRunFlag(void)
{
    return PaLengthAutoRunFlag;
}

void Rte_SetVfb_PaBackAutoRunFlag(INT8U SetValue)
{
    PaBackAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_PaBackAutoRunFlag(void)
{
    return PaBackAutoRunFlag;
}

void Rte_SetVfb_PaFrontAutoRunFlag(INT8U SetValue)
{
    PaFrontAutoRunFlag = SetValue;
}
INT8U Rte_GetVfb_PaFrontAutoRunFlag(void)
{
    return PaFrontAutoRunFlag;
}

void Rte_SetVfb_PaMoveType(INT8U SetValue)
{
    PaMoveType = SetValue;
}
INT8U Rte_GetVfb_PaMoveType(void)
{
    return PaMoveType;
}

void Rte_SetVfb_PaHeightHallErr(INT8U SetValue)
{
    PaHeightHallErr = SetValue;
}
INT8U Rte_GetVfb_PaHeightHallErr(void)
{
    return PaHeightHallErr;
}

void Rte_SetVfb_PaLengthHallErr(INT8U SetValue)
{
    PaLengthHallErr = SetValue;
}
INT8U Rte_GetVfb_PaLengthHallErr(void)
{
    return PaLengthHallErr;
}

void Rte_SetVfb_PaBackHallErr(INT8U SetValue)
{
    PaBackHallErr = SetValue;
}
INT8U Rte_GetVfb_PaBackHallErr(void)
{
    return PaBackHallErr;
}

void Rte_SetVfb_PaFrontHallErr(INT8U SetValue)
{
    PaFrontHallErr = SetValue;
}
INT8U Rte_GetVfb_PaFrontHallErr(void)
{
    return PaFrontHallErr;
}

void Rte_SetVfb_PaAnyoneHallErr(INT8U SetValue)
{
    PaAnyoneHallErr = SetValue;
}
INT8U Rte_GetVfb_PaAnyoneHallErr(void)
{
    return PaAnyoneHallErr;
}

void Rte_SetVfb_PaHeightDTCHallErr(INT8U SetValue)
{
    PaHeightDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_PaHeightDTCHallErr(void)
{
    return PaHeightDTCHallErr;
}

void Rte_SetVfb_PaLengthDTCHallErr(INT8U SetValue)
{
    PaLengthDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_PaLengthDTCHallErr(void)
{
    return PaLengthDTCHallErr;
}

void Rte_SetVfb_PaBackDTCHallErr(INT8U SetValue)
{
    PaBackDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_PaBackDTCHallErr(void)
{
    return PaBackDTCHallErr;
}

void Rte_SetVfb_PaFrontDTCHallErr(INT8U SetValue)
{
    PaFrontDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_PaFrontDTCHallErr(void)
{
    return PaFrontDTCHallErr;
}

void Rte_SetVfb_PaAnyoneDTCHallErr(INT8U SetValue)
{
    PaAnyoneDTCHallErr = SetValue;
}
INT8U Rte_GetVfb_PaAnyoneDTCHallErr(void)
{
    return PaAnyoneDTCHallErr;
}

void Rte_SetVfb_PaHeightStallErr(INT8U SetValue)
{
    PaHeightStallErr = SetValue;
}
INT8U Rte_GetVfb_PaHeightStallErr(void)
{
    return PaHeightStallErr;
}

void Rte_SetVfb_PaLengthStallErr(INT8U SetValue)
{
    PaLengthStallErr = SetValue;
}
INT8U Rte_GetVfb_PaLengthStallErr(void)
{
    return PaLengthStallErr;
}

void Rte_SetVfb_PaBackStallErr(INT8U SetValue)
{
    PaBackStallErr = SetValue;
}
INT8U Rte_GetVfb_PaBackStallErr(void)
{
    return PaBackStallErr;
}

void Rte_SetVfb_PaFrontStallErr(INT8U SetValue)
{
    PaFrontStallErr = SetValue;
}
INT8U Rte_GetVfb_PaFrontStallErr(void)
{
    return PaFrontStallErr;
}

void Rte_SetVfb_PaAnyoneStallErr(INT8U SetValue)
{
    PaAnyoneStallErr = SetValue;
}
INT8U Rte_GetVfb_PaAnyoneStallErr(void)
{
    return PaAnyoneStallErr;
}

void Rte_SetVfb_PaHeightRelayAdheErr(INT8U SetValue)
{
    PaHeightRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaHeightRelayAdheErr(void)
{
    return PaHeightRelayAdheErr;
}

void Rte_SetVfb_PaLengthRelayAdheErr(INT8U SetValue)
{
    PaLengthRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaLengthRelayAdheErr(void)
{
    return PaLengthRelayAdheErr;
}

void Rte_SetVfb_PaBackRelayAdheErr(INT8U SetValue)
{
    PaBackRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaBackRelayAdheErr(void)
{
    return PaBackRelayAdheErr;
}

void Rte_SetVfb_PaFrontRelayAdheErr(INT8U SetValue)
{
    PaFrontRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaFrontRelayAdheErr(void)
{
    return PaFrontRelayAdheErr;
}

void Rte_SetVfb_PaAnyoneRelayAdheErr(INT8U SetValue)
{
    PaAnyoneRelayAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaAnyoneRelayAdheErr(void)
{
    return PaAnyoneRelayAdheErr;
}

void Rte_SetVfb_PaHeightSwitchAdheErr(INT8U SetValue)
{
    PaHeightSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaHeightSwitchAdheErr(void)
{
    return PaHeightSwitchAdheErr;
}

void Rte_SetVfb_PaLengthSwitchAdheErr(INT8U SetValue)
{
    PaLengthSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaLengthSwitchAdheErr(void)
{
    return PaLengthSwitchAdheErr;
}

void Rte_SetVfb_PaBackSwitchAdheErr(INT8U SetValue)
{
    PaBackSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaBackSwitchAdheErr(void)
{
    return PaBackSwitchAdheErr;
}

void Rte_SetVfb_PaFrontSwitchAdheErr(INT8U SetValue)
{
    PaFrontSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaFrontSwitchAdheErr(void)
{
    return PaFrontSwitchAdheErr;
}

void Rte_SetVfb_PaHeightSwitchAdheErr_ForWard(INT8U SetValue)
{
    PaHeightSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_PaHeightSwitchAdheErr_ForWard(void)
{
    return PaHeightSwitchAdheErr_ForWard;
}

void Rte_SetVfb_PaHeightSwitchAdheErr_Back(INT8U SetValue)
{
    PaHeightSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_PaHeightSwitchAdheErr_Back(void)
{
    return PaHeightSwitchAdheErr_Back;
}

void Rte_SetVfb_PaLengthSwitchAdheErr_ForWard(INT8U SetValue)
{
    PaLengthSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_PaLengthSwitchAdheErr_ForWard(void)
{
    return PaLengthSwitchAdheErr_ForWard;
}

void Rte_SetVfb_PaLengthSwitchAdheErr_Back(INT8U SetValue)
{
    PaLengthSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_PaLengthSwitchAdheErr_Back(void)
{
    return PaLengthSwitchAdheErr_Back;
}

void Rte_SetVfb_PaBackSwitchAdheErr_ForWard(INT8U SetValue)
{
    PaBackSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_PaBackSwitchAdheErr_ForWard(void)
{
    return PaBackSwitchAdheErr_ForWard;
}

void Rte_SetVfb_PaBackSwitchAdheErr_Back(INT8U SetValue)
{
    PaBackSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_PaBackSwitchAdheErr_Back(void)
{
    return PaBackSwitchAdheErr_Back;
}

void Rte_SetVfb_PaFrontSwitchAdheErr_ForWard(INT8U SetValue)
{
    PaFrontSwitchAdheErr_ForWard = SetValue;
}
INT8U Rte_GetVfb_PaFrontSwitchAdheErr_ForWard(void)
{
    return PaFrontSwitchAdheErr_ForWard;
}

void Rte_SetVfb_PaFrontSwitchAdheErr_Back(INT8U SetValue)
{
    PaFrontSwitchAdheErr_Back = SetValue;
}
INT8U Rte_GetVfb_PaFrontSwitchAdheErr_Back(void)
{
    return PaFrontSwitchAdheErr_Back;
}

void Rte_SetVfb_PaAnyoneSwitchAdheErr(INT8U SetValue)
{
    PaAnyoneSwitchAdheErr = SetValue;
}
INT8U Rte_GetVfb_PaAnyoneSwitchAdheErr(void)
{
    return PaAnyoneSwitchAdheErr;
}

void Rte_SetVfb_PaHeightSoftStopErr(INT8U SetValue)
{
    PaHeightSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_PaHeightSoftStopErr(void)
{
    return PaHeightSoftStopErr;
}

void Rte_SetVfb_PaLengthSoftStopErr(INT8U SetValue)
{
    PaLengthSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_PaLengthSoftStopErr(void)
{
    return PaLengthSoftStopErr;
}

void Rte_SetVfb_PaBackSoftStopErr(INT8U SetValue)
{
    PaBackSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_PaBackSoftStopErr(void)
{
    return PaBackSoftStopErr;
}

void Rte_SetVfb_PaFrontSoftStopErr(INT8U SetValue)
{
    PaFrontSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_PaFrontSoftStopErr(void)
{
    return PaFrontSoftStopErr;
}

void Rte_SetVfb_PaAnyoneSoftStopErr(INT8U SetValue)
{
    PaAnyoneSoftStopErr = SetValue;
}
INT8U Rte_GetVfb_PaAnyoneSoftStopErr(void)
{
    return PaAnyoneSoftStopErr;
}

void Rte_SetVfb_PaHeightMotorTimeOutErr(INT8U SetValue)
{
    PaHeightMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_PaHeightMotorTimeOutErr(void)
{
    return PaHeightMotorTimeOutErr;
}

void Rte_SetVfb_PaLengthMotorTimeOutErr(INT8U SetValue)
{
    PaLengthMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_PaLengthMotorTimeOutErr(void)
{
    return PaLengthMotorTimeOutErr;
}

void Rte_SetVfb_PaBackMotorTimeOutErr(INT8U SetValue)
{
    PaBackMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_PaBackMotorTimeOutErr(void)
{
    return PaBackMotorTimeOutErr;
}

void Rte_SetVfb_PaFrontMotorTimeOutErr(INT8U SetValue)
{
    PaFrontMotorTimeOutErr = SetValue;
}
INT8U Rte_GetVfb_PaFrontMotorTimeOutErr(void)
{
    return PaFrontMotorTimeOutErr;
}

void Rte_SetVfb_DrWelLengthReqPosi(INT16U SetValue)
{
    DrWelLengthReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrWelLengthReqPosi(void)
{
    return DrWelLengthReqPosi;
}

void Rte_SetVfb_DrWelBackReqPosi(INT16U SetValue)
{
    DrWelBackReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrWelBackReqPosi(void)
{
    return DrWelBackReqPosi;
}

void Rte_SetVfb_PaWelLengthReqPosi(INT16U SetValue)
{
    PaWelLengthReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaWelLengthReqPosi(void)
{
    return PaWelLengthReqPosi;
}

void Rte_SetVfb_PaWelBackReqPosi(INT16U SetValue)
{
    PaWelBackReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaWelBackReqPosi(void)
{
    return PaWelBackReqPosi;
}

void Rte_SetVfb_DrMemHeightReqPosi(INT16U SetValue)
{
    DrMemHeightReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrMemHeightReqPosi(void)
{
    return DrMemHeightReqPosi;
}

void Rte_SetVfb_DrMemLengthReqPosi(INT16U SetValue)
{
    DrMemLengthReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrMemLengthReqPosi(void)
{
    return DrMemLengthReqPosi;
}

void Rte_SetVfb_DrMemBackReqPosi(INT16U SetValue)
{
    DrMemBackReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrMemBackReqPosi(void)
{
    return DrMemBackReqPosi;
}

void Rte_SetVfb_DrMemFrontReqPosi(INT16U SetValue)
{
    DrMemFrontReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrMemFrontReqPosi(void)
{
    return DrMemFrontReqPosi;
}

void Rte_SetVfb_PaMemHeightReqPosi(INT16U SetValue)
{
    PaMemHeightReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaMemHeightReqPosi(void)
{
    return PaMemHeightReqPosi;
}

void Rte_SetVfb_PaMemLengthReqPosi(INT16U SetValue)
{
    PaMemLengthReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaMemLengthReqPosi(void)
{
    return PaMemLengthReqPosi;
}

void Rte_SetVfb_PaMemBackReqPosi(INT16U SetValue)
{
    PaMemBackReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaMemBackReqPosi(void)
{
    return PaMemBackReqPosi;
}

void Rte_SetVfb_PaMemFrontReqPosi(INT16U SetValue)
{
    PaMemFrontReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaMemFrontReqPosi(void)
{
    return PaMemFrontReqPosi;
}

void Rte_SetVfb_DrResHeightReqPosi(INT16U SetValue)
{
    DrResHeightReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrResHeightReqPosi(void)
{
    return DrResHeightReqPosi;
}

void Rte_SetVfb_DrResLengthReqPosi(INT16U SetValue)
{
    DrResLengthReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrResLengthReqPosi(void)
{
    return DrResLengthReqPosi;
}

void Rte_SetVfb_DrResBackReqPosi(INT16U SetValue)
{
    DrResBackReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrResBackReqPosi(void)
{
    return DrResBackReqPosi;
}

void Rte_SetVfb_DrResFrontReqPosi(INT16U SetValue)
{
    DrResFrontReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrResFrontReqPosi(void)
{
    return DrResFrontReqPosi;
}

void Rte_SetVfb_DrResHeightReCallPosi(INT16U SetValue)
{
    DrResHeightReCallPosi = SetValue;
}
INT16U Rte_GetVfb_DrResHeightReCallPosi(void)
{
    return DrResHeightReCallPosi;
}

void Rte_SetVfb_DrResLengthReCallPosi(INT16U SetValue)
{
    DrResLengthReCallPosi = SetValue;
}
INT16U Rte_GetVfb_DrResLengthReCallPosi(void)
{
    return DrResLengthReCallPosi;
}

void Rte_SetVfb_DrResBackReCallPosi(INT16U SetValue)
{
    DrResBackReCallPosi = SetValue;
}
INT16U Rte_GetVfb_DrResBackReCallPosi(void)
{
    return DrResBackReCallPosi;
}

void Rte_SetVfb_DrResFrontReCallPosi(INT16U SetValue)
{
    DrResFrontReCallPosi = SetValue;
}
INT16U Rte_GetVfb_DrResFrontReCallPosi(void)
{
    return DrResFrontReCallPosi;
}

void Rte_SetVfb_DrHeat(INT8U SetValue)
{
    DrHeat = SetValue;
}
INT8U Rte_GetVfb_DrHeat(void)
{
    return DrHeat;
}

void Rte_SetVfb_PaHeat(INT8U SetValue)
{
    PaHeat = SetValue;
}
INT8U Rte_GetVfb_PaHeat(void)
{
    return PaHeat;
}

void Rte_SetVfb_ThirdHeat(INT8U SetValue)
{
    ThirdHeat = SetValue;
}
INT8U Rte_GetVfb_ThirdHeat(void)
{
    return ThirdHeat;
}

void Rte_SetVfb_DrHeatIo(INT8U SetValue)
{
    DrHeatIo = SetValue;
}
INT8U Rte_GetVfb_DrHeatIo(void)
{
    return DrHeatIo;
}

void Rte_SetVfb_PaHeatIo(INT8U SetValue)
{
    PaHeatIo = SetValue;
}
INT8U Rte_GetVfb_PaHeatIo(void)
{
    return PaHeatIo;
}

void Rte_SetVfb_ThirdHeatIo(INT8U SetValue)
{
    ThirdHeatIo = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatIo(void)
{
    return ThirdHeatIo;
}

void Rte_SetVfb_DrHeatCmdFaultSts(INT8U SetValue)
{
    DrHeatCmdFaultSts = SetValue;
}
INT8U Rte_GetVfb_DrHeatCmdFaultSts(void)
{
    return DrHeatCmdFaultSts;
}

void Rte_SetVfb_PaHeatCmdFaultSts(INT8U SetValue)
{
    PaHeatCmdFaultSts = SetValue;
}
INT8U Rte_GetVfb_PaHeatCmdFaultSts(void)
{
    return PaHeatCmdFaultSts;
}

void Rte_SetVfb_ThirdHeatCmdFaultSts(INT8U SetValue)
{
    ThirdHeatCmdFaultSts = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatCmdFaultSts(void)
{
    return ThirdHeatCmdFaultSts;
}

void Rte_SetVfb_DrHeatNTCFaultSts(INT8U SetValue)
{
    DrHeatNTCFaultSts = SetValue;
}
INT8U Rte_GetVfb_DrHeatNTCFaultSts(void)
{
    return DrHeatNTCFaultSts;
}

void Rte_SetVfb_PaHeatNTCFaultSts(INT8U SetValue)
{
    PaHeatNTCFaultSts = SetValue;
}
INT8U Rte_GetVfb_PaHeatNTCFaultSts(void)
{
    return PaHeatNTCFaultSts;
}

void Rte_SetVfb_ThirdHeatNTCFaultSts(INT8U SetValue)
{
    ThirdHeatNTCFaultSts = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatNTCFaultSts(void)
{
    return ThirdHeatNTCFaultSts;
}

void Rte_SetVfb_DrHeatStopReason(INT8U SetValue)
{
    DrHeatStopReason = SetValue;
}
INT8U Rte_GetVfb_DrHeatStopReason(void)
{
    return DrHeatStopReason;
}

void Rte_SetVfb_PaHeatStopReason(INT8U SetValue)
{
    PaHeatStopReason = SetValue;
}
INT8U Rte_GetVfb_PaHeatStopReason(void)
{
    return PaHeatStopReason;
}

void Rte_SetVfb_ThirdHeatStopReason(INT8U SetValue)
{
    ThirdHeatStopReason = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatStopReason(void)
{
    return ThirdHeatStopReason;
}

void Rte_SetVfb_DrHeatType(INT8U SetValue)
{
    DrHeatType = SetValue;
}
INT8U Rte_GetVfb_DrHeatType(void)
{
    return DrHeatType;
}

void Rte_SetVfb_PaHeatType(INT8U SetValue)
{
    PaHeatType = SetValue;
}
INT8U Rte_GetVfb_PaHeatType(void)
{
    return PaHeatType;
}

void Rte_SetVfb_ThirdHeatType(INT8U SetValue)
{
    ThirdHeatType = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatType(void)
{
    return ThirdHeatType;
}

void Rte_SetVfb_EngineRunFlag(INT8U SetValue)
{
    EngineRunFlag = SetValue;
}
INT8U Rte_GetVfb_EngineRunFlag(void)
{
    return EngineRunFlag;
}

void Rte_SetVfb_RemoteModeFlag(INT8U SetValue)
{
    RemoteModeFlag = SetValue;
}
INT8U Rte_GetVfb_RemoteModeFlag(void)
{
    return RemoteModeFlag;
}

void Rte_SetVfb_DrHeatRunState(INT8U SetValue)
{
    DrHeatRunState = SetValue;
}
INT8U Rte_GetVfb_DrHeatRunState(void)
{
    return DrHeatRunState;
}

void Rte_SetVfb_PaHeatRunState(INT8U SetValue)
{
    PaHeatRunState = SetValue;
}
INT8U Rte_GetVfb_PaHeatRunState(void)
{
    return PaHeatRunState;
}

void Rte_SetVfb_ThirdHeatRunState(INT8U SetValue)
{
    ThirdHeatRunState = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatRunState(void)
{
    return ThirdHeatRunState;
}

void Rte_SetVfb_DrVent(INT8U SetValue)
{
    DrVent = SetValue;
}
INT8U Rte_GetVfb_DrVent(void)
{
    return DrVent;
}

void Rte_SetVfb_PaVent(INT8U SetValue)
{
    PaVent = SetValue;
}
INT8U Rte_GetVfb_PaVent(void)
{
    return PaVent;
}

void Rte_SetVfb_ThirdVent(INT8U SetValue)
{
    ThirdVent = SetValue;
}
INT8U Rte_GetVfb_ThirdVent(void)
{
    return ThirdVent;
}

void Rte_SetVfb_DrVentCmdFaultSts(INT8U SetValue)
{
    DrVentCmdFaultSts = SetValue;
}
INT8U Rte_GetVfb_DrVentCmdFaultSts(void)
{
    return DrVentCmdFaultSts;
}

void Rte_SetVfb_PaVentCmdFaultSts(INT8U SetValue)
{
    PaVentCmdFaultSts = SetValue;
}
INT8U Rte_GetVfb_PaVentCmdFaultSts(void)
{
    return PaVentCmdFaultSts;
}

void Rte_SetVfb_ThirdVentCmdFaultSts(INT8U SetValue)
{
    ThirdVentCmdFaultSts = SetValue;
}
INT8U Rte_GetVfb_ThirdVentCmdFaultSts(void)
{
    return ThirdVentCmdFaultSts;
}

void Rte_SetVfb_DrVentStopReason(INT8U SetValue)
{
    DrVentStopReason = SetValue;
}
INT8U Rte_GetVfb_DrVentStopReason(void)
{
    return DrVentStopReason;
}

void Rte_SetVfb_PaVentStopReason(INT8U SetValue)
{
    PaVentStopReason = SetValue;
}
INT8U Rte_GetVfb_PaVentStopReason(void)
{
    return PaVentStopReason;
}

void Rte_SetVfb_ThirdVentStopReason(INT8U SetValue)
{
    ThirdVentStopReason = SetValue;
}
INT8U Rte_GetVfb_ThirdVentStopReason(void)
{
    return ThirdVentStopReason;
}

void Rte_SetVfb_DrVentType(INT8U SetValue)
{
    DrVentType = SetValue;
}
INT8U Rte_GetVfb_DrVentType(void)
{
    return DrVentType;
}

void Rte_SetVfb_PaVentType(INT8U SetValue)
{
    PaVentType = SetValue;
}
INT8U Rte_GetVfb_PaVentType(void)
{
    return PaVentType;
}

void Rte_SetVfb_ThirdVentType(INT8U SetValue)
{
    ThirdVentType = SetValue;
}
INT8U Rte_GetVfb_ThirdVentType(void)
{
    return ThirdVentType;
}

void Rte_SetVfb_DrVentRunState(INT8U SetValue)
{
    DrVentRunState = SetValue;
}
INT8U Rte_GetVfb_DrVentRunState(void)
{
    return DrVentRunState;
}

void Rte_SetVfb_PaVentRunState(INT8U SetValue)
{
    PaVentRunState = SetValue;
}
INT8U Rte_GetVfb_PaVentRunState(void)
{
    return PaVentRunState;
}

void Rte_SetVfb_ThirdVentRunState(INT8U SetValue)
{
    ThirdVentRunState = SetValue;
}
INT8U Rte_GetVfb_ThirdVentRunState(void)
{
    return ThirdVentRunState;
}

void Rte_SetVfb_DrLearnEnable(INT8U SetValue)
{
    DrLearnEnable = SetValue;
}
INT8U Rte_GetVfb_DrLearnEnable(void)
{
    return DrLearnEnable;
}

void Rte_SetVfb_DrLearnSts(INT8U SetValue)
{
    DrLearnSts = SetValue;
}
INT8U Rte_GetVfb_DrLearnSts(void)
{
    return DrLearnSts;
}

void Rte_SetVfb_LearnExitCause(INT8U SetValue)
{
    LearnExitCause = SetValue;
}
INT8U Rte_GetVfb_LearnExitCause(void)
{
    return LearnExitCause;
}

void Rte_SetVfb_DrHeatCmdFaultSts4DTC(INT8U SetValue)
{
    DrHeatCmdFaultSts4DTC = SetValue;
}
INT8U Rte_GetVfb_DrHeatCmdFaultSts4DTC(void)
{
    return DrHeatCmdFaultSts4DTC;
}

void Rte_SetVfb_PaHeatCmdFaultSts4DTC(INT8U SetValue)
{
    PaHeatCmdFaultSts4DTC = SetValue;
}
INT8U Rte_GetVfb_PaHeatCmdFaultSts4DTC(void)
{
    return PaHeatCmdFaultSts4DTC;
}

void Rte_SetVfb_ThirdHeatCmdFaultSts4DTC(INT8U SetValue)
{
    ThirdHeatCmdFaultSts4DTC = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatCmdFaultSts4DTC(void)
{
    return ThirdHeatCmdFaultSts4DTC;
}

void Rte_SetVfb_DrVentCmdFaultSts4DTC(INT8U SetValue)
{
    DrVentCmdFaultSts4DTC = SetValue;
}
INT8U Rte_GetVfb_DrVentCmdFaultSts4DTC(void)
{
    return DrVentCmdFaultSts4DTC;
}

void Rte_SetVfb_PaVentCmdFaultSts4DTC(INT8U SetValue)
{
    PaVentCmdFaultSts4DTC = SetValue;
}
INT8U Rte_GetVfb_PaVentCmdFaultSts4DTC(void)
{
    return PaVentCmdFaultSts4DTC;
}

void Rte_SetVfb_PaLearnSts(INT8U SetValue)
{
    PaLearnSts = SetValue;
}
INT8U Rte_GetVfb_PaLearnSts(void)
{
    return PaLearnSts;
}

void Rte_SetVfb_PaLearnExitCause(INT8U SetValue)
{
    PaLearnExitCause = SetValue;
}
INT8U Rte_GetVfb_PaLearnExitCause(void)
{
    return PaLearnExitCause;
}

void Rte_SetVfb_VehicleRunFlag(INT8U SetValue)
{
    VehicleRunFlag = SetValue;
}
INT8U Rte_GetVfb_VehicleRunFlag(void)
{
    return VehicleRunFlag;
}

void Rte_SetVfb_GearP(INT8U SetValue)
{
    GearP = SetValue;
}
INT8U Rte_GetVfb_GearP(void)
{
    return GearP;
}

void Rte_SetVfb_BusoffFlag(INT8U SetValue)
{
    BusoffFlag = SetValue;
}
INT8U Rte_GetVfb_BusoffFlag(void)
{
    return BusoffFlag;
}

void Rte_SetVfb_DrWelcomeRunSts(INT8U SetValue)
{
    DrWelcomeRunSts = SetValue;
}
INT8U Rte_GetVfb_DrWelcomeRunSts(void)
{
    return DrWelcomeRunSts;
}

void Rte_SetVfb_PaWelcomeRunSts(INT8U SetValue)
{
    PaWelcomeRunSts = SetValue;
}
INT8U Rte_GetVfb_PaWelcomeRunSts(void)
{
    return PaWelcomeRunSts;
}

void Rte_SetVfb_DrWelcomeStopReason(INT8U SetValue)
{
    DrWelcomeStopReason = SetValue;
}
INT8U Rte_GetVfb_DrWelcomeStopReason(void)
{
    return DrWelcomeStopReason;
}

void Rte_SetVfb_PaWelcomeStopReason(INT8U SetValue)
{
    PaWelcomeStopReason = SetValue;
}
INT8U Rte_GetVfb_PaWelcomeStopReason(void)
{
    return PaWelcomeStopReason;
}

void Rte_SetVfb_DrWelLengthReqCMD(INT8U SetValue)
{
    DrWelLengthReqCMD = SetValue;
}
INT8U Rte_GetVfb_DrWelLengthReqCMD(void)
{
    return DrWelLengthReqCMD;
}

void Rte_SetVfb_PaWelLengthReqCMD(INT8U SetValue)
{
    PaWelLengthReqCMD = SetValue;
}
INT8U Rte_GetVfb_PaWelLengthReqCMD(void)
{
    return PaWelLengthReqCMD;
}

void Rte_SetVfb_DrLearnResult(INT8U SetValue)
{
    DrLearnResult = SetValue;
}
INT8U Rte_GetVfb_DrLearnResult(void)
{
    return DrLearnResult;
}

void Rte_SetVfb_PaLearnResult(INT8U SetValue)
{
    PaLearnResult = SetValue;
}
INT8U Rte_GetVfb_PaLearnResult(void)
{
    return PaLearnResult;
}

void Rte_SetVfb_GearPN(INT8U SetValue)
{
    GearPN = SetValue;
}
INT8U Rte_GetVfb_GearPN(void)
{
    return GearPN;
}

void Rte_SetVfb_PaLearnEnable(INT8U SetValue)
{
    PaLearnEnable = SetValue;
}
INT8U Rte_GetVfb_PaLearnEnable(void)
{
    return PaLearnEnable;
}

void Rte_SetVfb_NapMode(INT8U SetValue)
{
    NapMode = SetValue;
}
INT8U Rte_GetVfb_NapMode(void)
{
    return NapMode;
}

void Rte_SetVfb_MemSetStopReason(INT8U SetValue)
{
    MemSetStopReason = SetValue;
}
INT8U Rte_GetVfb_MemSetStopReason(void)
{
    return MemSetStopReason;
}

void Rte_SetVfb_SeatMemoryValidReq(INT8U SetValue)
{
    SeatMemoryValidReq = SetValue;
}
INT8U Rte_GetVfb_SeatMemoryValidReq(void)
{
    return SeatMemoryValidReq;
}

void Rte_SetVfb_MemCallStopReason(INT8U SetValue)
{
    MemCallStopReason = SetValue;
}
INT8U Rte_GetVfb_MemCallStopReason(void)
{
    return MemCallStopReason;
}

void Rte_SetVfb_PreMemRemindStop(INT8U SetValue)
{
    PreMemRemindStop = SetValue;
}
INT8U Rte_GetVfb_PreMemRemindStop(void)
{
    return PreMemRemindStop;
}

void Rte_SetVfb_SpeedLessThan5_Flag(INT8U SetValue)
{
    SpeedLessThan5_Flag = SetValue;
}
INT8U Rte_GetVfb_SpeedLessThan5_Flag(void)
{
    return SpeedLessThan5_Flag;
}

void Rte_SetVfb_CANDrHeatStopReason(INT8U SetValue)
{
    CANDrHeatStopReason = SetValue;
}
INT8U Rte_GetVfb_CANDrHeatStopReason(void)
{
    return CANDrHeatStopReason;
}

void Rte_SetVfb_CANPaHeatStopReason(INT8U SetValue)
{
    CANPaHeatStopReason = SetValue;
}
INT8U Rte_GetVfb_CANPaHeatStopReason(void)
{
    return CANPaHeatStopReason;
}

void Rte_SetVfb_CANThirdHeatStopReason(INT8U SetValue)
{
    CANThirdHeatStopReason = SetValue;
}
INT8U Rte_GetVfb_CANThirdHeatStopReason(void)
{
    return CANThirdHeatStopReason;
}

void Rte_SetVfb_CANDrVentStopReason(INT8U SetValue)
{
    CANDrVentStopReason = SetValue;
}
INT8U Rte_GetVfb_CANDrVentStopReason(void)
{
    return CANDrVentStopReason;
}

void Rte_SetVfb_CANPaVentStopReason(INT8U SetValue)
{
    CANPaVentStopReason = SetValue;
}
INT8U Rte_GetVfb_CANPaVentStopReason(void)
{
    return CANPaVentStopReason;
}

void Rte_SetVfb_CANThirdVentStopReason(INT8U SetValue)
{
    CANThirdVentStopReason = SetValue;
}
INT8U Rte_GetVfb_CANThirdVentStopReason(void)
{
    return CANThirdVentStopReason;
}

void Rte_SetVfb_DrHeatEnable(INT8U SetValue)
{
    DrHeatEnable = SetValue;
}
INT8U Rte_GetVfb_DrHeatEnable(void)
{
    return DrHeatEnable;
}

void Rte_SetVfb_SecondHeatEnable(INT8U SetValue)
{
    SecondHeatEnable = SetValue;
}
INT8U Rte_GetVfb_SecondHeatEnable(void)
{
    return SecondHeatEnable;
}

void Rte_SetVfb_ThirdHeatEnable(INT8U SetValue)
{
    ThirdHeatEnable = SetValue;
}
INT8U Rte_GetVfb_ThirdHeatEnable(void)
{
    return ThirdHeatEnable;
}

void Rte_SetVfb_DrVentEnable(INT8U SetValue)
{
    DrVentEnable = SetValue;
}
INT8U Rte_GetVfb_DrVentEnable(void)
{
    return DrVentEnable;
}

void Rte_SetVfb_SecondVentEnable(INT8U SetValue)
{
    SecondVentEnable = SetValue;
}
INT8U Rte_GetVfb_SecondVentEnable(void)
{
    return SecondVentEnable;
}

void Rte_SetVfb_ThirdVentEnable(INT8U SetValue)
{
    ThirdVentEnable = SetValue;
}
INT8U Rte_GetVfb_ThirdVentEnable(void)
{
    return ThirdVentEnable;
}

void Rte_SetVfb_PaMemSetStopReason(INT8U SetValue)
{
    PaMemSetStopReason = SetValue;
}
INT8U Rte_GetVfb_PaMemSetStopReason(void)
{
    return PaMemSetStopReason;
}

void Rte_SetVfb_PaSeatMemoryValidReq(INT8U SetValue)
{
    PaSeatMemoryValidReq = SetValue;
}
INT8U Rte_GetVfb_PaSeatMemoryValidReq(void)
{
    return PaSeatMemoryValidReq;
}

void Rte_SetVfb_PaMemCallStopReason(INT8U SetValue)
{
    PaMemCallStopReason = SetValue;
}
INT8U Rte_GetVfb_PaMemCallStopReason(void)
{
    return PaMemCallStopReason;
}

void Rte_SetVfb_PaPreMemRemindStop(INT8U SetValue)
{
    PaPreMemRemindStop = SetValue;
}
INT8U Rte_GetVfb_PaPreMemRemindStop(void)
{
    return PaPreMemRemindStop;
}

void Rte_SetVfb_HVCommPC(INT8U SetValue)
{
    HVCommPC = SetValue;
}
INT8U Rte_GetVfb_HVCommPC(void)
{
    return HVCommPC;
}

void Rte_SetVfb_tPwrDnSts(INT8U SetValue)
{
    tPwrDnSts = SetValue;
}
INT8U Rte_GetVfb_tPwrDnSts(void)
{
    return tPwrDnSts;
}

void Rte_SetVfb_Res_MassageLevel_Req(INT8U SetValue)
{
    Res_MassageLevel_Req = SetValue;
}
INT8U Rte_GetVfb_Res_MassageLevel_Req(void)
{
    return Res_MassageLevel_Req;
}

void Rte_SetVfb_Res_MassageMode_Req(INT8U SetValue)
{
    Res_MassageMode_Req = SetValue;
}
INT8U Rte_GetVfb_Res_MassageMode_Req(void)
{
    return Res_MassageMode_Req;
}

void Rte_SetVfb_VoltMode(INT8U SetValue)
{
    VoltMode = SetValue;
}
INT8U Rte_GetVfb_VoltMode(void)
{
    return VoltMode;
}

void Rte_SetVfb_PowerMode(INT8U SetValue)
{
    PowerMode = SetValue;
}
INT8U Rte_GetVfb_PowerMode(void)
{
    return PowerMode;
}

void Rte_SetVfb_VoltSatisfy(INT8U SetValue)
{
    VoltSatisfy = SetValue;
}
INT8U Rte_GetVfb_VoltSatisfy(void)
{
    return VoltSatisfy;
}

void Rte_SetVfb_SwHeatMaxTime(INT8U SetValue)
{
    SwHeatMaxTime = SetValue;
}
INT8U Rte_GetVfb_SwHeatMaxTime(void)
{
    return SwHeatMaxTime;
}

void Rte_SetVfb_DrHeightLearnCmd(INT8U SetValue)
{
    DrHeightLearnCmd = SetValue;
}
INT8U Rte_GetVfb_DrHeightLearnCmd(void)
{
    return DrHeightLearnCmd;
}

void Rte_SetVfb_DrLengthLearnCmd(INT8U SetValue)
{
    DrLengthLearnCmd = SetValue;
}
INT8U Rte_GetVfb_DrLengthLearnCmd(void)
{
    return DrLengthLearnCmd;
}

void Rte_SetVfb_DrBackLearnCmd(INT8U SetValue)
{
    DrBackLearnCmd = SetValue;
}
INT8U Rte_GetVfb_DrBackLearnCmd(void)
{
    return DrBackLearnCmd;
}

void Rte_SetVfb_DrFrontLearnCmd(INT8U SetValue)
{
    DrFrontLearnCmd = SetValue;
}
INT8U Rte_GetVfb_DrFrontLearnCmd(void)
{
    return DrFrontLearnCmd;
}

void Rte_SetVfb_PaHeightLearnCmd(INT8U SetValue)
{
    PaHeightLearnCmd = SetValue;
}
INT8U Rte_GetVfb_PaHeightLearnCmd(void)
{
    return PaHeightLearnCmd;
}

void Rte_SetVfb_PaLengthLearnCmd(INT8U SetValue)
{
    PaLengthLearnCmd = SetValue;
}
INT8U Rte_GetVfb_PaLengthLearnCmd(void)
{
    return PaLengthLearnCmd;
}

void Rte_SetVfb_PaBackLearnCmd(INT8U SetValue)
{
    PaBackLearnCmd = SetValue;
}
INT8U Rte_GetVfb_PaBackLearnCmd(void)
{
    return PaBackLearnCmd;
}

void Rte_SetVfb_PaFrontLearnCmd(INT8U SetValue)
{
    PaFrontLearnCmd = SetValue;
}
INT8U Rte_GetVfb_PaFrontLearnCmd(void)
{
    return PaFrontLearnCmd;
}

void Rte_SetVfb_DrHeightResetReqPosi(INT16U SetValue)
{
    DrHeightResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrHeightResetReqPosi(void)
{
    return DrHeightResetReqPosi;
}

void Rte_SetVfb_DrLengthResetReqPosi(INT16U SetValue)
{
    DrLengthResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrLengthResetReqPosi(void)
{
    return DrLengthResetReqPosi;
}

void Rte_SetVfb_DrBackResetReqPosi(INT16U SetValue)
{
    DrBackResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrBackResetReqPosi(void)
{
    return DrBackResetReqPosi;
}

void Rte_SetVfb_DrFrontResetReqPosi(INT16U SetValue)
{
    DrFrontResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_DrFrontResetReqPosi(void)
{
    return DrFrontResetReqPosi;
}

void Rte_SetVfb_PaHeightResetReqPosi(INT16U SetValue)
{
    PaHeightResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaHeightResetReqPosi(void)
{
    return PaHeightResetReqPosi;
}

void Rte_SetVfb_PaLengthResetReqPosi(INT16U SetValue)
{
    PaLengthResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaLengthResetReqPosi(void)
{
    return PaLengthResetReqPosi;
}

void Rte_SetVfb_PaBackResetReqPosi(INT16U SetValue)
{
    PaBackResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaBackResetReqPosi(void)
{
    return PaBackResetReqPosi;
}

void Rte_SetVfb_PaFrontResetReqPosi(INT16U SetValue)
{
    PaFrontResetReqPosi = SetValue;
}
INT16U Rte_GetVfb_PaFrontResetReqPosi(void)
{
    return PaFrontResetReqPosi;
}

/***************************end****************************/
