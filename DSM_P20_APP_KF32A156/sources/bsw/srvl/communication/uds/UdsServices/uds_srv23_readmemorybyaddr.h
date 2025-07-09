/*!
************************************************************************************************************************
* @file uds_srv23_readmemorybyaddr.h
* @brief 23读取内存服务
* @par 模块输入参数
       
* @par 模块输出参数
       
* @details 
* @author Lews Hammond(刘发星)
* @date 2020-5-20
************************************************************************************************************************
*/

#ifndef UDS_SRV23_READ_MEMORY_BY_ADDR_H
#define UDS_SRV23_READ_MEMORY_BY_ADDR_H


#if (SID23_READ_MEMORY_BY_ADDR == DESC_ENABLE)

/*! @brief 23服务数据地址格式定义 */
#define D_UDS_READ_MEMORY_ADDR_FORMAT                   4u
/*! @brief 23服务数据长度格式定义 */
#define D_UDS_READ_MEMORY_LEN_FORMAT                    2u
/*! @brief 23服务支持最大读取字节长度 */
#define D_UDS_READ_MEMORY_LENGTH_LIMIT                  512u
/*! @brief 23服务支持的内存地址范围个数 */
#define D_UDS_READ_MEMORY_START_ADDR                    6u



void UdsApp_23ReadMemoryByAddr(void);



#endif


#endif

