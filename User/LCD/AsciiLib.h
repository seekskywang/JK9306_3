
#ifndef __AsciiLib_H
#define __AsciiLib_H  

/* Includes ------------------------------------------------------------------*/
#include <string.h>
extern const unsigned char _C[][40];
extern const unsigned char _p[][40];
extern const unsigned char TAB_num[][32];
extern const unsigned char MainData_num[][16];
extern const unsigned char Out_Assic[][40];
extern const unsigned char nAsciiDotBig[];
extern unsigned char nAsciiDot20X40E[];
/* Private define ------------------------------------------------------------*/
#define  ASCII_8X16_MS_Gothic
//#define  ASCII_8X16_System

/* Private function prototypes -----------------------------------------------*/
void GetASCIICode(unsigned char* pBuffer,unsigned char ASCII);
void GetASCIICode_12(unsigned char* pBuffer,unsigned char ASCII);
#endif 


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
