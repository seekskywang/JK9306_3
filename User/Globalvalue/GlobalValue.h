//==========================================================
//ÎÄ¼şÃû³Æ£ºGlobalValue.h
//ÎÄ¼şÃèÊö£ºÈ«¾Ö±äÁ¿Í·ÎÄ¼ş
//ÎÄ¼ş°æ±¾£ºVer1.0
//´´½¨ÈÕÆÚ£º2015.10.26 
//ĞŞ¸ÄÈÕÆÚ£º2015.10.28 15:38
//ÎÄ¼ş×÷Õß£º»ÆºêÁé
//±¸×¢ËµÃ÷£ºÎŞ
//×¢ÒâÊÂÏî£ºÎŞ
//==========================================================
#ifndef __GlobalValue_h__
#define __GlobalValue_h__
#include "stdint.h"
//#include "TypeDefine.h"
#define FIT_INUM    12
//==========================================================
//Èí¼ş°æ±¾£º10
#define SOFTWARE_VERSION		(0x10)

//==========================================================
//Ä¬ÈÏ³ö³§±àºÅ(0)
#define DEFAULT_MACHINE_ID 		(0)

//Ä¬ÈÏ³ö³§ÃÜÂë(0)
#define DEFAULT_PASSWORD 		(0)

//Ä¬ÈÏ¿ª»ú´ÎÊı(0)
#define SET_BOOT_DEFAULT		(0)

//==========================================================
//µ÷ÊÔÅäÖÃ
#define _DEBUG_CONFIG_FALSE		(0)
#define _DEBUG_CONFIG_TRUE		(1)

//==========================================================
//·ÂÕæµ÷ÊÔ
//#define DEBUG_SUPPORT			(_DEBUG_CONFIG_TRUE)
#define DEBUG_SUPPORT			(_DEBUG_CONFIG_FALSE)

//==========================================================
//ISP¿ª¹ØÅäÖÃ£¬·ÂÕæµ÷ÊÔÓÃ
#if DEBUG_SUPPORT
	#define HW_ISP_SUPPORT		(_DEBUG_CONFIG_FALSE)
#else
	#define HW_ISP_SUPPORT		(_DEBUG_CONFIG_TRUE)
#endif

//==========================================================
//Uart¿ª¹ØÅäÖÃ
#define HW_UART_SUPPORT			(_DEBUG_CONFIG_TRUE)

//==========================================================
//·äÃùÆ÷¿ª¹ØÅäÖÃ
#define HW_BEEP_SUPPORT			(_DEBUG_CONFIG_TRUE)

//==========================================================
//ADÖµÂË²¨ÅäÖÃ£¬Ôö¼ÓÊı¾İÎÈ¶¨¶È
#define AD_FILTER_SUPPORT		(_DEBUG_CONFIG_TRUE)

//==========================================================
#define SETUP_MENU_MAX  	(2)//×î´óÉèÖÃ²Ëµ¥

#define DEBUG_MENU_MAX  	(6)//×î´óĞ£×¼²Ëµ¥

#define PARAMETER_MENU_MAX	(3)//×î´ó²ÎÊı²Ëµ¥

#define SYSTEM_MENU_MAX		(4)//×î´óÏµÍ³²Ëµ¥

#define CONFIG_MENU_MAX		(3)//×î´óÅäÖÃÏî(0-2)

#define PW_LENGTH 			(4)//×î´óÃÜÂëÎ»Êı

#define RANGE_MAX 			(4-1)//×î´óÁ¿³Ì

#define AD_BUF_LENGTH		(8)//A/DÖµ»º³åÇø³¤¶È

#define MAX_R_RANGE			(5)//µç×è×î´óÁ¿³Ì

#define BUTTOM_X_VALUE		(84)//ÏÔÊ¾ÏÂÃæÌáÊ¾ÏÔÊ¾µÄµÚÒ»¸öXÎ»ÖÃ

#define BUTTOM_MID_VALUE	(80)//ÏÔÊ¾ÏÂÃæÌáÊ¾ÏÔÊ¾µÄÖĞ¼ä¼ä¸ôÎ»ÖÃ

#define BUTTOM_Y_VALUE		(271-30)//ÏÔÊ¾ÏÂÃæÌáÊ¾ÏÔÊ¾µÄµÚÒ»¸öYÎ»ÖÃ

#define KEY_NUM				(4)	//°´¼üÁéÃô¶È

#define NUM_LENTH 			(6)//ÏÔÊ¾³¤¶È
#define NUM_FREQ 			(33+4)//ÏÔÊ¾³¤¶È			

//==========================================================
#define OHM 				(0xF4)	//CGROMÖĞÓĞ¦¸×Ö·û£¬±àÂëÎª0xF4

//==========================================================
//ÏÔÊ¾·ÖÇøµÄX×ø±ê
#define MSG_ADDR_X 			(1)
#define AUTO_ADDR_X 		(12)
#define RANGE_ADDR_X 		(17)

#define RES_ADDR_X 			(1)
#define VOL_ADDR_X 			(12)

#define DISP_UNIT_XPOS	380-8
#define DISP_UNIT_YPOS	92
//==========================================================
//±êÌâ³¤¶È
#define TITLE_LEN_MAX		(8)

//é‡ç¨‹
//#define VRANGE		300		//µçÑ¹Á¿³Ì300V
#define CRANGE		10		//µçÁ÷Á¿³Ì10mA

#define MAINDATA1X				10		
#define MAINDATA1Y				56		
#define MAINUNIT1X				10+6*16+5		
#define MAINUNIT1Y				54
#define MAINDATAXOFFSET		160
#define MAINDATAYOFFSET		45

#define SUBNAMEX						4	
#define SUBNAMEY						50	
#define SUBNAMEOFFSET				20	

#define SUBDATA1X					4+80-60		
#define SUBDATA1Y					50	
#define SUBUNIT1X					4+80+20*6-60	
#define SUBUNIT1Y					50
#define SUBDATAXOFFSET		150
#define SUBDATAYOFFSET		20

#define SETPARAX					20
#define SETPARAY		  		30
#define SETPARAXOFFSET		160
#define SETPARAYOFFSET		28

//Ö÷ÏÔÊ¾±í¸ñ
#define HLINEXS					1
#define HLINEXE					478
#define HLINEY					50
#define MARGINVER		  	45
#define MARGINHOR				160
#define CH1X						65
#define CH1Y						28
#define CHMARGIN				160

//é€šè®¯å¸§å®šä¹‰
#define VFRAME				3				//µçÑ¹
#define CFRAME				3+2*3		//µçÁ÷
#define PAFRAME				3+2*6		//ÓĞ¹¦¹¦ÂÊ
#define PFFRAME				3+2*9 	//¹¦ÂÊÒòÊı
#define PASUMFRAME		3+2*12 	//×ÜÓĞ¹¦¹¦ÂÊ
#define QSUMFRAME			3+2*13 	//×ÜÎŞ¹¦¹¦ÂÊ
#define PAVFRAME			3+2*14 	//ÈıÏàÆ½¾ù¹¦ÂÊÒòÊı
#define FFRAME				3+2*15	//ÆµÂÊ
#define WP1RAME				3+2*16	//ÕıÏòÓĞ¹¦µç¶È
#define WQ1RAME				3+2*18	//ÕıÏòÎŞ¹¦µç¶È
#define WP2RAME				3+2*20	//ÕıÏòÓĞ¹¦µç¶È
#define WQ2RAME				3+2*22	//ÕıÏòÎŞ¹¦µç¶È
#define QFRAME				3+2*24	//ÎŞ¹¦¹¦ÂÊ
#define PFRAME				3+2*27	//ÊÓÔÚ¹¦ÂÊ
//#define FSFRAME				3+2*36	//ÆµÂÊ
#define WFRAME				3+2*30	//×ÜÊÓÔÚ¹¦ÂÊ

typedef struct
{
	float first_value;
	float comp_highvalue[5];
	float comp_lowvalue[5];
}Comp_Testvalue_Typedef;
extern Comp_Testvalue_Typedef  Comp_Testvalue;

typedef struct
{
	uint8_t Main_Funbuff[8];
	uint8_t Main_Secondbuff[8];
	uint8_t Main_Vmbuff[8];
//	uint8_t Main_Imbuff[8];
}Test_DispBCD_Typedef;
typedef struct
{
	uint8_t Main_flag;
	uint8_t Second_falg;
}Main_Second_TypeDed;
/*
typedef struct
{
	uint8_t buff[5];
	uint32_t Num;
	uint32_t Dot;
	uint32_t Unit;
}Range_Set_Typedef;
typedef struct
{
	Range_Set_Typedef all[4];
}All_Compvalue_Typedef;
extern All_Compvalue_Typedef Comp_Change;
*/
//==========================================================
//´øĞ¡ÊıµãºÍµ¥Î»µÄÊı
typedef struct 
{
	uint8_t Wei;
	uint32_t Num;
	uint8_t Dot;
	uint8_t Unit;
	uint8_t Dotp;
}Sort_TypeDef;
typedef struct
{
	uint8_t buff[10];
	uint8_t Vmvaluebuff[10];
	uint8_t Imvaluebuff[10];
}Test_Dispvalue;
extern Test_Dispvalue Test_value;
/*
typedef struct
{
    Sort_TypeDef Low;
    Sort_TypeDef Hi;
}Comp_V_Typedef;*/
//¼«ÏŞÁĞ±íÉèÖÃ
typedef struct
{
    uint8_t Param;//²ÎÊı
    uint8_t Comp;//±È½Ï¿ª¹Ø
	Sort_TypeDef Low[5];
    Sort_TypeDef Hi[5];
}Limit_Tab;
/*
typedef struct
{
	uint32_t Year;
	uint32_t Mon;
	uint32_t data;
}Data_Value_Typedef;
typedef struct
{
	uint32_t Hour;
	uint32_t Min;
	uint32_t Sec;
}Timer_Value_Typedef;*/
//ÏµÍ³ÉèÖÃ
typedef struct
{
    uint32_t Main_Func;
    uint32_t Menu_Disp;
    uint32_t Baue_Rate;
}Sys_Setup_Typedef;

typedef struct
{
	uint8_t adr;
	uint8_t mode;
	uint8_t check;
	uint8_t filter;
	uint8_t iomode;//	uint8_t page;
	uint8_t clear;
	uint8_t lang;
	uint8_t signal;
	uint8_t beep;
	uint8_t alrm;
	uint8_t boud;	//	Sort_TypeDef Trig_time;//  Sort_TypeDef Temp_time;
	uint8_t vrange;
	uint8_t irange;
	uint8_t usbmode;
	uint8_t hotkey;
	uint8_t whswitch;
}Main_Func_TypeDef;
typedef union UUUU
{
	float	adx;//
	uint32_t ax;
//	int32_t sx;
	uint8_t	bx[4];
}fcc;
typedef struct
{
//	Sys_Setup_Typedef	Sys_Setup;
	union UUUU	div[10];
	union UUUU	zer[10];
	Main_Func_TypeDef	Main;
	Limit_Tab	Limit;
}Savee;
extern Savee SaveData;

typedef struct
{
	Main_Func_TypeDef	Save_Main;
	Limit_Tab	Limit;
	union UUUU	div[10];
	union UUUU	zer[10];
}Saveeprom;
extern Saveeprom	Saveeeprom;

typedef struct
{
	uint8_t page;
	uint8_t index;
	uint8_t row;
	uint32_t key;
	uint8_t force;
	uint8_t sumkey;
	uint8_t test;
	uint8_t third;
}Button_Page_Typedef;
extern Button_Page_Typedef Button_Page;

typedef struct
{
	uint16_t xpos;
	uint16_t ypos;
	uint16_t lenth;
}Disp_Coordinates_Typedef;
typedef struct
{
	uint8_t Ordel;
	uint8_t name;
} Send_Ord_Typedef;

typedef struct
{
	Send_Ord_Typedef first;
	Send_Ord_Typedef second;
	Send_Ord_Typedef third;
}Send_Mainord_Typedef;

extern Send_Mainord_Typedef Send_Mainord;
typedef struct
{
	uint8_t File;			//²âÁ¿ÏÔÊ¾---ÎÄ¼ş
	uint8_t Tool;			//²âÁ¿ÏÔÊ¾---¹¤¾ß
	uint8_t Parameter;		//²âÁ¿ÏÔÊ¾---²ÎÊı
	uint8_t Rang;			//²âÁ¿ÏÔÊ¾---Á¿³Ì
	uint8_t Speed;			//²âÁ¿ÏÔÊ¾---ËÙ¶È
	uint8_t Trigger;		//²âÁ¿ÏÔÊ¾---´¥·¢
} Disp_Set_Typedef;
extern Disp_Set_Typedef Disp_Set_Resist;

typedef struct 
{
	uint8_t Display;	//		±È½ÏÏÔÊ¾--¹¤¾ß--ÏÔÊ¾
	uint8_t Ring;		//		±È½ÏÏÔÊ¾--¹¤¾ß--Ñ¶Ïì
	uint8_t Count;		//		±È½ÏÏÔÊ¾--¹¤¾ß--¼ÆÊı
	uint8_t Mode;		//		±È½ÏÏÔÊ¾--¹¤¾ß--Ä£Ê½
}Compare_Tool_Typedef;

typedef struct 
{
	uint8_t File;								//±È½ÏÏÔÊ¾---ÎÄ¼ş
	Compare_Tool_Typedef Compare_Tool ;//±È½ÏÏÔÊ¾---¹¤¾ß
	uint8_t Comp;								//±È½ÏÏÔÊ¾---±È½Ï
	uint8_t Compar_Mode;						//±È½ÏÏÔÊ¾---±È½ÏÄ£Ê½
	Sort_TypeDef Toplimt;							//±È½ÏÏÔÊ¾---ÉÏÏŞ
	Sort_TypeDef Lowlimt;							//±È½ÏÏÔÊ¾---ÏÂÏŞ
}Disp_CompareMenu_Typedef;
extern Disp_CompareMenu_Typedef Disp_CompareMenu,Set_CompareMenu;

typedef struct 
{
	uint8_t File;		       //µµÏÔÊ¾---ÎÄ¼ş
	uint8_t Tool;			   //µµÏÔÊ¾---¹¤¾ß
	uint8_t Shift;			   //µµÏÔÊ¾---µµ
	uint8_t Shfit_Bell;		   //µµÏÔÊ¾---µµÑ¶Ïì
}Disp_Set_Shift_Typedef;

extern Disp_Set_Shift_Typedef Disp_Set_Shift;

typedef struct 
{
	uint8_t Shift_Mode;		//µµÉèÖÃ--¹¤¾ß--µµÄ£Ê½
	uint8_t Shift_Ring;		//µµÉèÖÃ--¹¤¾ß--µµÑ¶Ïì
}ShiftSet_Tool;

typedef struct				//µµÉèÖÃÖĞµÄ×´Ì¬1.2.3
{
	uint8_t First;
	uint8_t Second;
	uint8_t Third;
}ShiftSet_Num_Typedef ;

typedef  struct 
{
	Sort_TypeDef First;
	Sort_TypeDef Second;
	Sort_TypeDef Third;
}Limit_Set_Typedef;
/*
typedef struct 
{
	uint8_t File;						//µµÉèÖÃ--ÎÄ¼ş
	ShiftSet_Tool Tool;					//µµÉèÖÃ--¹¤¾ß
	ShiftSet_Num_Typedef Shift;			//µµÉèÖÃ--µµ
	ShiftSet_Num_Typedef State;			//µµÉèÖÃ--×´Ì¬
	Limit_Set_Typedef UpLimit;			//µµÉèÖÃ--ÉÏÏŞ
	Limit_Set_Typedef LowLimit;			//µµÉèÖÃ--ÏÂÏŞ
	ShiftSet_Num_Typedef Nominal_Value; //µµÉèÖÃ--±ê³ÆÖµ
	ShiftSet_Num_Typedef Per;			//µµÉèÖÃ--°Ù·ÖÊı
}Disp_Set_ShiftSet_Typedef;
*/
//extern Disp_Set_ShiftSet_Typedef Disp_Set_ShiftSet;
/*
typedef struct
{
	uint32_t Baud;     					//ÏµÍ³ÉèÖÃÖĞµÄ²¨ÌØÂÊ

}Disp_Set_SysSet_T;

extern Disp_Set_SysSet_T Disp_Set_SysSet;
*/
typedef struct 
{
	uint8_t  RBuff[16];	  		//ÏÔÊ¾²âÊÔµÄRÖµ
	uint8_t  chn;
	uint8_t  EXTG;
	uint8_t  read421ok;
}Disp_Test_Date_T;

extern Disp_Test_Date_T Test_Dat;

//==========================================================
//È«¾Ö±äÁ¿
extern  unsigned long SystemStatus;//ÏµÍ³×´Ì¬
extern unsigned long SystemMessage;//ÏµÍ³ĞÅÏ¢
extern char DispBuf[12];
extern unsigned long Count_buff[12];
extern uint8_t Uart_Send_Flag;
extern uint32_t Usb_Open_flag;
//==========================================================
//ÏµÍ³×´Ì¬
enum SysStatusEnum
{	
	SYS_STATUS_ERROR,			//Òì³£
	SYS_STATUS_RESET,			//¸´Î»
	SYS_STATUS_POWER,			//¿ª»ú
	SYS_STATUS_DATASTORE,	//Êı¾İ±£´æ
	SYS_STATUS_FILE,			//ÎÄ¼ş¹ÜÀí
	SYS_STATUS_SETUPTEST,//²âÁ¿ÉèÖÃ
	SYS_STATUS_TEST,			//²âÊÔ
	SYS_STATUS_RANGE,		//µµºÅÏÔÊ¾
	SYS_STATUS_RANGECOUNT,	//µµ¼ÆÊıÏÔÊ¾
	SYS_STATUS_ITEM,			//ÁĞ±íÉ¨ÃèÏÔÊ¾
	SYS_STATUS_USERDEBUG,//ÓÃ»§Ğ£Õı 
	SYS_STATUS_FACRDEBUG, //¹¤³§Ğ£Õı
	SYS_STATUS_SYSSET,     //ÏµÍ³ÉèÖÃ
  SYS_STATUS_LIMITSET, //¼«ÏŞÉèÖÃ
  SYS_STATUS_ITEMSET,//ÁĞ±íÉ¨ÃèÉèÖÃ
	SYS_STATUS_TOOL,//¹¤¾ß
	SYS_STATUS_RESIST,   //µç×è²âÊÔÏÔÊ¾½çÃæ
	SYS_STATUS_COMPARE,  //µç×è²âÊÔ±È½Ï½çÃæ
	SYS_STATUS_SHIFT,    //µç×è²âÊÔµµ½çÃæ
	SYS_STATUS_SHIFTSET, //µç×è²âÊÔµµÉèÖÃ½çÃæ
	SYS_STATUS_SYSTEMSET,//µç×è²âÊÔÏµÍ³ÉèÖÃ½çÃæ
	SYS_STATUS_MAIN,//½çÃæ
};
//==========================================================
//·ÖÑ¡×´Ì¬
/*enum SlectStatusEnum
{
	RH_FAIL,
	RL_FAIL,
	VH_FAIL,
	VL_FAIL,
	ALL_FAIL,
	ALL_PASS,
};*/
//==========================================================
//ÏµÍ³ÏûÏ¢
enum SysMessageEnum
{
	MSG_CLEAR , 
	MSG_IDLE , 
	MSG_TEST , 
	MSG_ABORT , 
	MSG_PASS ,
//	MSG_FAIL ,
	MSG_HIGH , 
	MSG_LOW , 
};

//==========================================================
//º¯ÊıÁĞ±í
//void InitGlobalValue(void);//È«¾Ö±äÁ¿³õÊ¼»¯
void LoadDefaultSet(void);//¼ÓÔØÄ¬ÈÏÉèÖÃÖµ
void LoadDefaultParameter(void);//¼ÓÔØÄ¬ÈÏ²ÎÊıÖµ
void LoadDefaultSystem(void);//¼ÓÔØÄ¬ÈÏÏµÍ³Öµ
void LoadDefaultConfig(void);//¼ÓÔØÄ¬ÈÏÅäÖÃÖµ
void LoadDefaultCalibrate(void);//¼ÓÔØÄ¬ÈÏĞ£×¼Öµ
void ReadSaveData(void);//¶ÁÈ¡±£´æ²ÎÊı
//void WriteSaveData(void);//Ğ´Èë±£´æ²ÎÊı

#define SetSystemStatus(status) (SystemStatus=status)
#define GetSystemStatus() (SystemStatus)
#define GetSystemMessage() (SystemMessage)
#define SetSystemMessage(msg) (SystemMessage=msg)

void Check_Calibrate_Limit(void);//Ğ£×¼Öµ¼ì²é
void Hex_Format(uint32_t dat , uint8_t Dot , uint8_t len , uint8_t dispzero);

#endif
