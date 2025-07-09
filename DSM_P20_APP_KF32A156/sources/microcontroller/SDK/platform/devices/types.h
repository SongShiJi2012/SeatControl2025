////////////////////////////////////////////////////////////////////////////// 
/** 
* @file      types.h 
* 
* @brief     自定义数据类型
*
* @note      避免直接使用系统数据类型，通过操作系统本身数据存储类型转换为
             自定义数据类型使用
* 
* @author    ancle
* 
* @version   1.0.0 
* 
* @date      2019-03-30
* 
* 修改记录：
*
*    2019-03-30   ancle    New Create;
*/  
//////////////////////////////////////////////////////////////////////////////

#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

typedef unsigned char       bool_t;         /* C   style 布尔类型 */
typedef unsigned char       BOOL;           /* C++ style 布尔类型 */
#ifndef	TRUE
//#define TRUE           	(1)
#endif

#ifndef FALSE
//#define FALSE         	(0)
#endif

#if 1 /**< 鍩烘湰绫讳技瀹氫箟 */
#ifndef u8_t
    typedef unsigned char           u8_t;
#endif

#ifndef u16_t
    typedef unsigned short int      u16_t;
#endif

#ifndef u32_t
    typedef unsigned int            u32_t;
#endif

#ifndef u64_t
    typedef unsigned long long      u64_t;
#endif

#ifndef s8_t
    typedef signed char             s8_t;
#endif

#ifndef s16_t
    typedef signed short int        s16_t;
#endif

#ifndef s32_t
    typedef signed int		    s32_t;
#endif

#ifndef s64_t
    typedef signed long long        s64_t;
#endif

#ifndef u_unit_t
    typedef unsigned int            u_unit_t;       /**< 鏃犵鍙�MCU璁块棶鏁版嵁鍗曞厓 */
#endif

#ifndef s_unit_t
    typedef s32_t                   s_unit_t;       /**< 鏈夌鍙�MCU璁块棶鏁版嵁鍗曞厓 */
#endif
	
#ifndef bool_t
    typedef unsigned char           bool_t;
#endif

#endif

/* C Style pointer */
typedef int8_t*             int8_pt;        /* 8  bits signed pointer */
typedef int16_t*            int16_pt;       /* 16 bits signed pointer */
typedef int32_t*            int32_pt;       /* 32 bits signed pointer */

typedef uint8_t*            uint8_pt;       /* 8  bits unsigned pointer */
typedef uint16_t*           uint16_pt;      /* 16 bits unsigned pointer */
typedef uint32_t*           uint32_pt;      /* 32 bits unsigned pointer */

// signed data type: C++ Style
typedef signed   char       INT8;            /* 8  bits signed */
typedef signed   short      INT16;           /* 16 bits signed */
typedef signed   int        INT32;           /* 32 bits signed */
typedef signed   long long  INT64;           /* 64 bits signed */


// unsigned data type: C++ Style
typedef unsigned char       BYTE;           /* 8  bits unsigned */
typedef unsigned short      WORD;           /* 16 bits unsigned */
typedef unsigned int        DWORD;          /* 32 bits unsigned */
typedef unsigned long       LONG;           /* 32 bits unsigned */
typedef unsigned long long  LLONG;          /* 64 bits unsigned */

typedef unsigned char       UINT8;          /* 8  bits unsigned */
typedef unsigned short      UINT16;         /* 16 bits unsigned */
typedef unsigned int        UINT32;         /* 32 bits unsigned */
typedef unsigned long long  UINT64;         /* 64 bits unsigned */

typedef unsigned char   BOOL;
typedef	signed char		INT8S;
typedef	unsigned char	INT8U;
typedef	signed short	INT16S;
typedef	unsigned short	INT16U;
typedef	signed int		INT32S;
typedef	unsigned int	INT32U;

// floating data type: C/C++ Style
typedef          char       char_t;
typedef          char*      char_pt;
typedef          float      float32_t;
typedef          float*     float32_pt;
typedef          double     float64_t;
typedef          double*    float64_pt;
typedef long     double     float128_t;

/** 获取p_data的第n个数据 */
#ifndef GET_BYTE
#define GET_BYTE(p_data, n) \
	(((p_data) >> (8 * (n))) & 0xFF)
#endif

/** p1与p2合成两字节 */
#ifndef ADD16
#define ADD16(p1, p2) \
	(((uint16_t)(p1) << 8) | ((uint16_t)p2))
#endif

/** p1/p2/p3/p4合成四字节 */
#ifndef ADD32
#define ADD32(p1, p2, p3, p4) \
	(((uint32_t)(p1) << 24) | ((uint32_t)(p2) << 16) | \
	((uint32_t)(p3) << 8) | ((uint32_t)p4))
#endif

/** 取x/y的最小值 */
#ifndef MIN
#define MIN(x, y) \
	((x) < (y) ? (x) : (y))
#endif

/** 取x/y的最大值 */
#ifndef MAX
#define MAX(x, y) \
	((x) > (y) ? (x) : (y))
#endif

/** 取x/y的差值 */
#ifndef ABS_SUB
#define ABS_SUB(x, y) \
	(((x) >= (y)) ? (x - y) : (y - x))
#endif


#if !defined(SET_BIT)
/** data的第n位置1 */
#define SET_BIT(data, n) \
    (data |= (1U << (n)))
#endif

#if !defined(CLEAR_BIT)
/** data的第n位清0 */
#define CLEAR_BIT(data, n) \
    (data &= (~(1U << (n))))
#endif
#if !defined(GET_BIT)
/** Get Bit Value */
#define GET_BIT(data, n) \
    (data & (1U << (n)))
#endif

#define GET_HBYTE(U16Val)   (uint8_t)((U16Val & 0xff00) >> 8)
#define GET_LBYTE(U16Val)   (uint8_t)(U16Val & 0x00ff)


#endif /* _TYPES_H_ */
