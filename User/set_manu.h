#ifndef __Set_manu_H
#define __Set_manu_H 

#define  StrNUM         16
//#define  BaudRatePnt		0
//#define  CheckPnt				1
//#define  AddressPnt			2
//#define  FilterPnt			3
//#define  IOModePnt			4
#define  AutoZeroPnt    0
#define  LanguagePnt		1
//#define  Wh							7
//#define  PowerPnt				8
//#define  USBModePnt			9
//#define  HotKeyPnt			10
#define  BeeperPnt			2
#define  PLimitPnt			3
#define  ILimitPnt			4
#define  BeepPnt			5
#define  ParaNUM       6
#define Clearcur			0
//#define MAX_LPW  1
//#define MAX_LCUR  100
#define MAX_ADD  	254    
#define NULLsetMu			100 

//--------------EMWIN 使用变量----------------//
#define MainsetMu			0 //电压设置页面

#define SYSsetMu			4 //系统设置页面
#define WavesetMu			5 //波形显示页面
#define UsbsetMu			6 //USB存储页面
#define NullsetMu			200 //电压设置页面

#define Allcur				0xff	 	//数字全部填充
#define Nub1cur				2 			//数字的最高位单独填充
#define Nub2cur				3 			//数字的次高位单独填充
#define Nub3cur				4 			//依次往右
#define Nub4cur				5 			//依次往右
#define Nub5cur				6 			//依次往右

#define   Flag_GE                   (flagC.bit0)//��λ��˸��־
#define   Flag_SHI                  (flagC.bit1)//ʮλ��˸��־
#define   Flag_BAI                  (flagC.bit2)//��λ��˸��־
#define   Flag_QIAN                 (flagC.bit3)//ǧλ��˸��־
#define   Flag_WANG                 (flagC.bit4)//万位

#define MAX_PW  		60000//Para_Set[ULimitPnt].val 		
#define MAX_CUR  		20000//Para_Set[ILimitPnt].val

#define MENUOFFSETX  		10
struct RDispPara	
{
  int row;                    //???
  int col;                   //???
	int len;
	char flag;
	unsigned int max;
	unsigned int val;
  char En[StrNUM];    //??
  char Ch[StrNUM];    //??
};

#define   BaudRate_SetVal			(Para_Set[BaudRatePnt].val)			//������	
#define   Check_SetMod  			(Para_Set[CheckPnt].val)				//У�鷽ʽ	  
#define   AddressVal          (Para_Set[AddressPnt].val)			//���ڵ�ַ	  
#define   flag_SetFilter 			(Para_Set[FilterPnt].val)			//��ʾ���軹�ǵ�ѹ	  
#define   flag_SetIOMode  		(Para_Set[IOModePnt].val)				//����������	  
#define   flag_SetAutoZero  	(Para_Set[AutoZeroPnt].val)     		//�Լ쿪��	
#define   flag_SetLang  			(Para_Set[LanguagePnt].val)		//������������Ϊ0,Ӣ��Ϊ1		
#define   flag_SetPower 			(Para_Set[PowerPnt].val)
//��Դ����	  
#define  	flag_SetWh			(Para_Set[Wh].val)
#define   flag_SetUSBMode			(Para_Set[USBModePnt].val)			//usbģʽ	  
#define  	flag_SetHotKey			(Para_Set[HotKeyPnt].val)				//��ݼ�����	
#define 	Flag_Beep_OFF 			(Para_Set[BeeperPnt].val)				//����������	
#define 	Flag_Alarm_OFF 			(Para_Set[BeepPnt].val)   //��������
#define  	POWLimit        (Para_Set[PLimitPnt].val)	//�޹���ֵ			  
#define  	CurrentLimit        (Para_Set[ILimitPnt].val)	//����ֵ
#define  	TMode	        (Para_main[0].val)	//ģʽ
#define  	VRANGE	        (Para_main[1].val)	//V��Χ
#define  	IRANGE 	        (Para_main[2].val)	//I��Χ

extern unsigned char BlankP;       // ?????????????
extern struct RDispPara Para_Set[ParaNUM];
extern struct RDispPara Para_main[9];
extern unsigned char CursorP  ;
void Disp_Sys_set(void);
void Disp_Main_set(void);
extern char DisULInputNum[10];	//
extern char DisILInputNum[10];	//
extern char DisADDInputNum[3];	//
extern unsigned char TSetInput;	
void DisBlank(unsigned char blank,unsigned char mode);
#endif 
