/***********************************************************************************************
 * @file name: main.c
 * @description: ����������ļ�������ϵͳ��ʼ������ѭ������
 * @author: ssj 20250509
 * @version: V1.0
 * @copyright: Copyright ? 2025 XXX��˾����������Ȩ��
 * @history:
 *           - 2025-05-09 ssj ���洴��
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
        //ι��
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

