/***********************************************************************************************
 * @file name: main.c
 * @description: 主程序入口文件，负责系统初始化及主循环管理
 * @author: ssj 20250509
 * @version: V1.0
 * @copyright: Copyright ? 2025 XXX公司，保留所有权利
 * @history:
 *           - 2025-05-09 ssj 初版创建
 ***********************************************************************************************/

#include "kf32a156.h"
#include "system_init.h"
#include "UserTask.h"
#include "Cdd_Hall.h"
#include "Event.h"
#include "CpuPeripheralInit.h"
#include "ecual_wdog.h"

volatile int exit_code = 0;
//                            _ooOoo_
//                           o8888888o
//                           88" . "88
//                           (| -_- |)
//                           O\  =  /O
//                        ____/`---'\____
//                      .'  \\|     |//  `.
//                     /  \\|||  :  |||//  \
//                    /  _||||| -:- |||||-  \
//                    |   | \\\  -  /// |   |
//                    | \_|  ''\---/''  |   |
//                    \  .-\__  `-`  ___/-. /
//                  ___`. .'  /--.--\  `. . __
//               ."" '<  `.___\_<|>_/___.'  >'"".
//              | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//              \  \ `-.   \_ __\ /__ _/   .-` /  /
//         ======`-.____`-.___\_____/___.-`____.-'======
//                            `=---='
//        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//                      Buddha Bless, No Bug !
int main(void)
{
    CPU_System_Init();

    InitEvent();
    AllTask_Init();
    for(;;)
    {
        //喂狗
        ecual_FeedDog();
        AppAppCycEvent();
    }

  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

