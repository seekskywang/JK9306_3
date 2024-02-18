//==========================================================
//�ļ����ƣ�GlobalValue.h
//�ļ�������ȫ�ֱ���ͷ�ļ�
//�ļ��汾��Ver1.0
//�������ڣ�2015.10.26 
//�޸����ڣ�2015.10.28 15:38
//�ļ����ߣ��ƺ���
//��ע˵������
//ע�������
//==========================================================
#ifndef __GlobalValue_h__
#define __GlobalValue_h__
#include "stdint.h"
//#include "TypeDefine.h"
#define FIT_INUM    12
//==========================================================
//����汾��10
#define SOFTWARE_VERSION		(0x10)

//==========================================================
//Ĭ�ϳ������(0)
#define DEFAULT_MACHINE_ID 		(0)

//Ĭ�ϳ�������(0)
#define DEFAULT_PASSWORD 		(0)

//Ĭ�Ͽ�������(0)
#define SET_BOOT_DEFAULT		(0)

//==========================================================
//��������
#define _DEBUG_CONFIG_FALSE		(0)
#define _DEBUG_CONFIG_TRUE		(1)

//==========================================================
//�������
//#define DEBUG_SUPPORT			(_DEBUG_CONFIG_TRUE)
#define DEBUG_SUPPORT			(_DEBUG_CONFIG_FALSE)

//==========================================================
//ISP�������ã����������
#if DEBUG_SUPPORT
	#define HW_ISP_SUPPORT		(_DEBUG_CONFIG_FALSE)
#else
	#define HW_ISP_SUPPORT		(_DEBUG_CONFIG_TRUE)
#endif

//==========================================================
//Uart��������
#define HW_UART_SUPPORT			(_DEBUG_CONFIG_TRUE)

//==========================================================
//��������������
#define HW_BEEP_SUPPORT			(_DEBUG_CONFIG_TRUE)

//==========================================================
//ADֵ�˲����ã����������ȶ���
#define AD_FILTER_SUPPORT		(_DEBUG_CONFIG_TRUE)

//==========================================================
#define SETUP_MENU_MAX  	(2)//������ò˵�

#define DEBUG_MENU_MAX  	(6)//���У׼�˵�

#define PARAMETER_MENU_MAX	(3)//�������˵�

#define SYSTEM_MENU_MAX		(4)//���ϵͳ�˵�

#define CONFIG_MENU_MAX		(3)//���������(0-2)

#define PW_LENGTH 			(4)//�������λ��

#define RANGE_MAX 			(4-1)//�������

#define AD_BUF_LENGTH		(8)//A/Dֵ����������

#define MAX_R_RANGE			(5)//�����������

#define BUTTOM_X_VALUE		(84)//��ʾ������ʾ��ʾ�ĵ�һ��Xλ��

#define BUTTOM_MID_VALUE	(80)//��ʾ������ʾ��ʾ���м���λ��

#define BUTTOM_Y_VALUE		(271-30)//��ʾ������ʾ��ʾ�ĵ�һ��Yλ��

#define KEY_NUM				(4)	//����������

#define NUM_LENTH 			(6)//��ʾ����
#define NUM_FREQ 			(33+4)//��ʾ����			

//==========================================================
#define OHM 				(0xF4)	//CGROM���Ц��ַ�������Ϊ0xF4

//==========================================================
//��ʾ������X����
#define MSG_ADDR_X 			(1)
#define AUTO_ADDR_X 		(12)
#define RANGE_ADDR_X 		(17)

#define RES_ADDR_X 			(1)
#define VOL_ADDR_X 			(12)

#define DISP_UNIT_XPOS	380-8
#define DISP_UNIT_YPOS	92
//==========================================================
//���ⳤ��
#define TITLE_LEN_MAX		(8)

//量程
//#define VRANGE		300		//��ѹ����300V
#define CRANGE		10		//��������10mA

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

//����ʾ���
#define HLINEXS					1
#define HLINEXE					478
#define HLINEY					50
#define MARGINVER		  	45
#define MARGINHOR				160
#define CH1X						65
#define CH1Y						28
#define CHMARGIN				160

//通讯帧定义
#define VFRAME				3				//��ѹ
#define CFRAME				3+2*3		//����
#define PAFRAME				3+2*6		//�й�����
#define PFFRAME				3+2*9 	//��������
#define PASUMFRAME		3+2*12 	//���й�����
#define QSUMFRAME			3+2*13 	//���޹�����
#define PAVFRAME			3+2*14 	//����ƽ����������
#define FFRAME				3+2*15	//Ƶ��
#define WP1RAME				3+2*16	//�����й����
#define WQ1RAME				3+2*18	//�����޹����
#define WP2RAME				3+2*20	//�����й����
#define WQ2RAME				3+2*22	//�����޹����
#define QFRAME				3+2*24	//�޹�����
#define PFRAME				3+2*27	//���ڹ���
//#define FSFRAME				3+2*36	//Ƶ��
#define WFRAME				3+2*30	//�����ڹ���

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
//��С����͵�λ����
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
//�����б�����
typedef struct
{
    uint8_t Param;//����
    uint8_t Comp;//�ȽϿ���
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
//ϵͳ����
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
	uint8_t File;			//������ʾ---�ļ�
	uint8_t Tool;			//������ʾ---����
	uint8_t Parameter;		//������ʾ---����
	uint8_t Rang;			//������ʾ---����
	uint8_t Speed;			//������ʾ---�ٶ�
	uint8_t Trigger;		//������ʾ---����
} Disp_Set_Typedef;
extern Disp_Set_Typedef Disp_Set_Resist;

typedef struct 
{
	uint8_t Display;	//		�Ƚ���ʾ--����--��ʾ
	uint8_t Ring;		//		�Ƚ���ʾ--����--Ѷ��
	uint8_t Count;		//		�Ƚ���ʾ--����--����
	uint8_t Mode;		//		�Ƚ���ʾ--����--ģʽ
}Compare_Tool_Typedef;

typedef struct 
{
	uint8_t File;								//�Ƚ���ʾ---�ļ�
	Compare_Tool_Typedef Compare_Tool ;//�Ƚ���ʾ---����
	uint8_t Comp;								//�Ƚ���ʾ---�Ƚ�
	uint8_t Compar_Mode;						//�Ƚ���ʾ---�Ƚ�ģʽ
	Sort_TypeDef Toplimt;							//�Ƚ���ʾ---����
	Sort_TypeDef Lowlimt;							//�Ƚ���ʾ---����
}Disp_CompareMenu_Typedef;
extern Disp_CompareMenu_Typedef Disp_CompareMenu,Set_CompareMenu;

typedef struct 
{
	uint8_t File;		       //����ʾ---�ļ�
	uint8_t Tool;			   //����ʾ---����
	uint8_t Shift;			   //����ʾ---��
	uint8_t Shfit_Bell;		   //����ʾ---��Ѷ��
}Disp_Set_Shift_Typedef;

extern Disp_Set_Shift_Typedef Disp_Set_Shift;

typedef struct 
{
	uint8_t Shift_Mode;		//������--����--��ģʽ
	uint8_t Shift_Ring;		//������--����--��Ѷ��
}ShiftSet_Tool;

typedef struct				//�������е�״̬1.2.3
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
	uint8_t File;						//������--�ļ�
	ShiftSet_Tool Tool;					//������--����
	ShiftSet_Num_Typedef Shift;			//������--��
	ShiftSet_Num_Typedef State;			//������--״̬
	Limit_Set_Typedef UpLimit;			//������--����
	Limit_Set_Typedef LowLimit;			//������--����
	ShiftSet_Num_Typedef Nominal_Value; //������--���ֵ
	ShiftSet_Num_Typedef Per;			//������--�ٷ���
}Disp_Set_ShiftSet_Typedef;
*/
//extern Disp_Set_ShiftSet_Typedef Disp_Set_ShiftSet;
/*
typedef struct
{
	uint32_t Baud;     					//ϵͳ�����еĲ�����

}Disp_Set_SysSet_T;

extern Disp_Set_SysSet_T Disp_Set_SysSet;
*/
typedef struct 
{
	uint8_t  RBuff[16];	  		//��ʾ���Ե�Rֵ
	uint8_t  chn;
	uint8_t  EXTG;
	uint8_t  read421ok;
}Disp_Test_Date_T;

extern Disp_Test_Date_T Test_Dat;

//==========================================================
//ȫ�ֱ���
extern  unsigned long SystemStatus;//ϵͳ״̬
extern unsigned long SystemMessage;//ϵͳ��Ϣ
extern char DispBuf[12];
extern unsigned long Count_buff[12];
extern uint8_t Uart_Send_Flag;
extern uint32_t Usb_Open_flag;
//==========================================================
//ϵͳ״̬
enum SysStatusEnum
{	
	SYS_STATUS_ERROR,			//�쳣
	SYS_STATUS_RESET,			//��λ
	SYS_STATUS_POWER,			//����
	SYS_STATUS_DATASTORE,	//���ݱ���
	SYS_STATUS_FILE,			//�ļ�����
	SYS_STATUS_SETUPTEST,//��������
	SYS_STATUS_TEST,			//����
	SYS_STATUS_RANGE,		//������ʾ
	SYS_STATUS_RANGECOUNT,	//��������ʾ
	SYS_STATUS_ITEM,			//�б�ɨ����ʾ
	SYS_STATUS_USERDEBUG,//�û�У�� 
	SYS_STATUS_FACRDEBUG, //����У��
	SYS_STATUS_SYSSET,     //ϵͳ����
  SYS_STATUS_LIMITSET, //��������
  SYS_STATUS_ITEMSET,//�б�ɨ������
	SYS_STATUS_TOOL,//����
	SYS_STATUS_RESIST,   //���������ʾ����
	SYS_STATUS_COMPARE,  //������ԱȽϽ���
	SYS_STATUS_SHIFT,    //������Ե�����
	SYS_STATUS_SHIFTSET, //������Ե����ý���
	SYS_STATUS_SYSTEMSET,//�������ϵͳ���ý���
	SYS_STATUS_MAIN,//����
};
//==========================================================
//��ѡ״̬
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
//ϵͳ��Ϣ
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
//�����б�
//void InitGlobalValue(void);//ȫ�ֱ�����ʼ��
void LoadDefaultSet(void);//����Ĭ������ֵ
void LoadDefaultParameter(void);//����Ĭ�ϲ���ֵ
void LoadDefaultSystem(void);//����Ĭ��ϵͳֵ
void LoadDefaultConfig(void);//����Ĭ������ֵ
void LoadDefaultCalibrate(void);//����Ĭ��У׼ֵ
void ReadSaveData(void);//��ȡ�������
//void WriteSaveData(void);//д�뱣�����

#define SetSystemStatus(status) (SystemStatus=status)
#define GetSystemStatus() (SystemStatus)
#define GetSystemMessage() (SystemMessage)
#define SetSystemMessage(msg) (SystemMessage=msg)

void Check_Calibrate_Limit(void);//У׼ֵ���
void Hex_Format(uint32_t dat , uint8_t Dot , uint8_t len , uint8_t dispzero);

#endif
