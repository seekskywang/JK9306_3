#ifndef __use_disp_H_
#define __use_disp_H_
#include  "stdint.h"
#include  "Globalvalue/globalvalue.h"
#define FIRSTLINE	26
#define	SPACE1		22
#define LIST1		0
#define LIST2		250
#define SELECT_1END 192
#define SELECT_2END (410+32)

#define   KEY_XLEFTP     391		//������ߵ�Xλ��
#define   KEY_XRIGHT     473		//�����ұߵ�Xλ��
#define   KEY_HIGH		 41			 //�����Ŀ��
#define   KEY_LENGHT     96			//�����ĳ���
#define   KEY_TOTALWID   45			 
#define   KEY_RED		 130			 //�����Ļ�ɫ
#define   KEY_GREEN		 130
#define   KEY_BLUE		 130
#define   KEY_CHANG      3
#define   COLORFLAG      7
#define   KEY_WORD       103
#define   POLYGON_RED	 160		 //����ν����ɫ KEY_TOTALWID 120
#define   POLYGON_CHANG	 2			//����ν����С
#define   POLYGON_WORD1	 140  	//����ε�һ���ֵ���ʾ��ɫ
#define   POLYGON_WORD2	 160
#define   KEY_LINE_COL   126   
#define   POLYGON_LINE	 158		//��ʾ����������Ľ����ɫ200
#define   POLYGON_SEC    72
#define   POLYGON_EN	 112		//��ʾӢ���ַ�
#define   KEY_WORD2      90 

#define   LINE_DISTAN    31
#define   KEY_DIS_MODE1  58			//������ʾ�����������ɫ
#define   BOX_0_SITE  2

#define   SYSSET_BOX_LEN  128		//ϵͳ���÷��򳤶�

#define  SCREENWIDE   480
#define  SCREENHIGH   272
#define  INSTRUCT_TO_DEBUG	Delay(0x3f);
#define  SHORT_DELAY  Delay(0x1f);
#define  INSTR_FIVE   0x03
#define  SITE         5
#define  CORRE_SITE   5
#define  INSTR_FOUR   0x00
#define  LONGDELAY	  Delay(0x2ff);


Sort_TypeDef Time_Set_Cov(Sort_TypeDef *Time);
Sort_TypeDef Freq_Set_Cov(Sort_TypeDef *Freq);

Sort_TypeDef Input_Set_Cov(Sort_TypeDef *Input_Ref);

void Send_Main_Ord(void);
//����ʱ������ʾ�������ʾ
void Disp_Range_ComDispValue(Button_Page_Typedef *Button_Page);
void Disp_RangeDispvalue(uint8_t data);
void Disp_Range_DispMainUnit(uint8_t num,uint8_t unit);//������ʾ��Cp�ĵ�λ
void Disp_Range_DispSecondUnit(uint8_t num,uint8_t unit);//������ʾ��Rp�ĵ�λ
void Disp_RangeTestvalue(void);//������ʾ�е�Cp��Rp��ֵ

void Disp_Button_ItemScanSet(uint32_t value);
void Disp_Button_ItemScan_no(void);

Sort_TypeDef Input_Set_CovPre(Sort_TypeDef *Input_Ref);
void Disp_Test_Unit_v(uint32_t x,uint32_t y);
void Disp_Test_Unit_mA(uint32_t x,uint32_t y);
void Send_UartStart(void);
void Savetoeeprom(void);
void ReadSavedata(void);

void Communiction_Protocol(Button_Page_Typedef* Button_Page );
void lcd_image(uint8_t *pt);

void Disp_Start_Corr(void);//��ʾ��ʼУ��
void Start_Correction(void);//��ʼУ��
void Init_C(void);//���ݳ�ʼ��У��
void Correction_C(Button_Page_Typedef* Button_Page)	;	//����У��
void Save_C(void);	//�������ֵ

void Init_R(void);//��ʼ������
void Correction_R(Button_Page_Typedef* Button_Page);		//����У��
void Save_R(void);	//�������ֵ
void Exit_correction(void);	//�˳�У��
void Clear_Instr(void);  //���У��

void Disp_Test(void);
void	Disp_Setup(void);
void Disp_Test_Set(Button_Page_Typedef* Button_Page);	//�������ý���
void Disp_Shift(void);      //����ʾ����
void Disp_Shift_Set(Button_Page_Typedef* Button_Page);//����ʾ����
void Disp_ShiftSet(void);   //������
void Disp_ShiftSet_Set(Button_Page_Typedef* Button_Page);//�������е�����
void Disp_System(void);	    //��ʾϵͳ���ý���
void Disp_SysSet_Set(Button_Page_Typedef* Button_Page);	//ϵͳ���õ�����

void Disp_Key_Box(Button_Page_Typedef* Button_Page);			//����������ʾ
void Disp_Num_Keyboard_Box(void);   //Button_Page_Typedef* Button_Page���ְ�������
void Disp_UpOrLow_Limit_Word(void); //Button_Page_Typedef* Button_Page��ֵ��������ʾ�����޵���

void Num_Keyboard(void);	//Button_Page_Typedef* Button_Page���ְ�������
void Manage_File(void);		//�ļ��������
void Draw_LIN5(uint8_t x,uint8_t y,uint16_t len,uint32_t color);
void Draw_LIN3_Y(uint8_t x,uint8_t y,uint16_t len,uint32_t color);
extern const char All_TopName_E[][20];	
extern const char All_TopName[][20];
extern const char DataTab[][20];
extern const char DataTabE[][20];
extern const char CHNAME[][5];
extern const char SubDataTab[2][3][20];
#endif
