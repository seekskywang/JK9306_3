
#ifndef __EX_SDRAM_h
#define __EX_SDRAM_h

#include "LPC177x_8x.h"
#include "lpc_types.h"
#include "system_LPC177x_8x.h" 

//#define SDRAM_CONFIG_32BIT	// ���2��16λSDRAM
#define SDRAM_CONFIG_16BIT 
#ifdef SDRAM_CONFIG_16BIT 
#define SDRAM_SIZE               0x2000000	// 256Mbit
/* LCD color */
#define White          0xFFFFFF
#define Black          0x000000
#define Red            0x0000FF
#define Green          0x00FF00
#define Blue           0xFF0000
#define Yellow         0x00FFFF
#define PCOLOR 		   0xCAFF70
#define FCOLOR 		   0x247FFF
/*
  * @brief  LCD color  
  */ 

#define LCD_COLOR_WHITE          0xFFFFFF	//��ɫ
#define LCD_COLOR_BLACK          0x000000	//��ɫ
#define LCD_COLOR_GREY           0xC0C0C0	//��ɫ
#define LCD_COLOR_BLUE           0x0000FF	//��ɫ
#define LCD_COLOR_BLUE2          0xA00000
#define LCD_COLOR_RED            0xFF0000
#define LCD_COLOR_MAGENTA        0xFF00FF	 //���ɫ
#define LCD_COLOR_GREEN          0x00FF00
#define LCD_COLOR_CYAN           0x00FFFF	//����ɫ
#define LCD_COLOR_YELLOW         0xFFFF00
#define SDRAM_SIZE               0x2000000	// 512Mbit
#define	LCD_COLOR_TEST_MID  	 		0x653434
#define	LCD_COLOR_TEST_BACK 	 		0X000000//0xb4007d//
#define	LCD_COLOR_TEST_BUTON     0X310038		//��ť��ɫ
#define	LCD_COLOR_TEST_LINE      0X694368		//������ɫ
#define	LCD_COLOR_TEST_BAR       0x352F3
#define	LCD_COLOR_SELECT       	LCD_COLOR_BLUE  //��ѡ�е���ɫ

#define LCD_COLOR_TURQUOISE		 0x3f4828	//����ɫ     //0x9b9907 (��ɫ)0x5f6738
#define LCD_COLOR_BABYGREY		 0xebe6e8	//ǳ��ɫ
#define LCD_COLOR_BABYBLACK		 0x1d1d1d	//ǳ��ɫ
#define LCD_COLOR_BABYBLUE		 0xe1e723
#define LCD_COLOR_ORANGE		 0x0000FF	//�ٻ�ɫ
#define LCD_COLOR_DARKGREY	     0x8d898a 	//���ɫ


#elif defined SDRAM_CONFIG_32BIT	 //
/* LCD color */
#define White          0xFFFFFF
#define Black          0x000000
#define Red            0x0000FF
#define Green          0x00FF00
#define Blue           0xFF0000
#define Yellow         0x00FFFF
#define PCOLOR 		   0xCAFF70
#define FCOLOR 		   0x247FFF
/*
  * @brief  LCD color  
  */ 

#define LCD_COLOR_WHITE          0xFFFFFF	//��ɫ
#define LCD_COLOR_BLACK          0x000000	//��ɫ
#define LCD_COLOR_GREY           0xC0C0C0	//��ɫ
#define LCD_COLOR_BLUE           0x0000FF	//��ɫ
#define LCD_COLOR_BLUE2          0xA00000
#define LCD_COLOR_RED            0xFF0000
#define LCD_COLOR_MAGENTA        0xFF00FF	 //���ɫ
#define LCD_COLOR_GREEN          0x00FF00
#define LCD_COLOR_CYAN           0x00FFFF	//����ɫ
#define LCD_COLOR_YELLOW         0xFFFF00
#define SDRAM_SIZE               0x4000000	// 512Mbit
#define	LCD_COLOR_TEST_MID  	 		0x653434
#define	LCD_COLOR_TEST_BACK 	 		0X000000//0xb4007d//
#define	LCD_COLOR_TEST_BUTON     0X310038		//��ť��ɫ
#define	LCD_COLOR_TEST_LINE      0X694368		//������ɫ
#define	LCD_COLOR_TEST_BAR       0x352F3
#define	LCD_COLOR_SELECT       	LCD_COLOR_BLUE  //��ѡ�е���ɫ

#define LCD_COLOR_TURQUOISE		 0x3f4828	//����ɫ     //0x9b9907 (��ɫ)0x5f6738
#define LCD_COLOR_BABYGREY		 0xebe6e8	//ǳ��ɫ
#define LCD_COLOR_BABYBLACK		 0x1d1d1d	//ǳ��ɫ
#define LCD_COLOR_BABYBLUE		 0xe1e723
#define LCD_COLOR_ORANGE		 0x0000FF	//�ٻ�ɫ
#define LCD_COLOR_DARKGREY	     0x8d898a 	//���ɫ

#else
	error Wrong SDRAM config, check ex_sdram.h
#endif

#define SDRAM_BASE               0xA0000000	   /* CS0 */

void SDRAM_Init (void);

#endif
