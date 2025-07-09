/*!
************************************************************************************************************************
* @file uds_srv23_readmemorybyaddr.h
* @brief 23��ȡ�ڴ����
* @par ģ���������
       
* @par ģ���������
       
* @details 
* @author Lews Hammond(������)
* @date 2020-5-20
************************************************************************************************************************
*/

#ifndef UDS_SRV23_READ_MEMORY_BY_ADDR_H
#define UDS_SRV23_READ_MEMORY_BY_ADDR_H


#if (SID23_READ_MEMORY_BY_ADDR == DESC_ENABLE)

/*! @brief 23�������ݵ�ַ��ʽ���� */
#define D_UDS_READ_MEMORY_ADDR_FORMAT                   4u
/*! @brief 23�������ݳ��ȸ�ʽ���� */
#define D_UDS_READ_MEMORY_LEN_FORMAT                    2u
/*! @brief 23����֧������ȡ�ֽڳ��� */
#define D_UDS_READ_MEMORY_LENGTH_LIMIT                  512u
/*! @brief 23����֧�ֵ��ڴ��ַ��Χ���� */
#define D_UDS_READ_MEMORY_START_ADDR                    6u



void UdsApp_23ReadMemoryByAddr(void);



#endif


#endif

