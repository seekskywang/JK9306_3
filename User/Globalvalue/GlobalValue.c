//==========================================================
//�ļ����ƣ�GlobalValue.c
//�ļ�������ȫ�ֱ�������
//�ļ��汾��Ver1.0
//�������ڣ�2015.10.28
//�޸����ڣ�2015.10.28 15:38
//�ļ����ߣ��ƺ���
//��ע˵������
//ע�������
//==========================================================
#include "TypeDefine.h"	//��ֵ����
#include "Globalvalue/GlobalValue.h"

//==========================================================
//ȫ�ֱ���
Savee SaveData;
Saveeprom	Saveeeprom;
Test_Dispvalue Test_value;
uint32_t Usb_Open_flag;

Disp_Set_Typedef Disp_Set_Resist;			//����������ʾ
Disp_CompareMenu_Typedef Disp_CompareMenu,Set_CompareMenu;//�Ƚ���ʾ

Disp_Test_Date_T Test_Dat;

uint8_t Uart_Send_Flag;

 unsigned long SystemStatus;//ϵͳ״̬

char DispBuf[12];


