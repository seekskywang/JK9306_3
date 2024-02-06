#include "Test/test.h"
#include "LCD/lpc177x_8x_lcd.h"
#include "lpc177x_8x_uart.h"
#include "lpc177x_8x_gpio.h"
#include "Globalvalue/GlobalValue.h"
#include "use_disp.h"
#include "EX_SDRAM/EX_SDRAM.H"
//#include "stdint.h"
#include "key/key.h"
#include "uart.h"
//#include "timer.h"
#include "lpc177x_8x_eeprom.h"
//#include "math.h"
#include "LCD/AsciiLib.h"

#include "use_disp.h"
#include "set_manu.h"
#include "string.h"
#include "stdio.h"
//#include "open.h"
#include "modbus_slave.h"
#include  "usbhost_lpc17xx.h"
#include "ff.h"
#include "bsp_bmp.h"

typedef struct Data{
  uint32_t Voltage[3];       //��ѹ
  uint32_t Current[3];       //����
  uint32_t Freq;     				//Ƶ��
	int16_t Pa[3];       		  //�й�����
	int16_t Pq[3];       		  //�޹�����
  int16_t Pf[3];       			//��������
	int32_t PaSum;						//���й�����
	int32_t QSum;								//���޹�����
	int32_t PfAvg;       			//ƽ����������
	uint32_t Power[3];       	//���ڹ���
	uint32_t Wp[2];							//�й����
	uint32_t Wq[2];							//�޹����
  uint32_t SFreq[3];     				//Ƶ��
	uint32_t W[3];     				//Ƶ��
	int8_t polarity[3];       	//������������ֵ
}Dispdata;

u32 bmpnum=123456;
u8 bmpname[30];
uint8_t usb_oenflag;
Dispdata Disp;
extern void uartSendChars(LPC_UART_TypeDef *UARTx,const void *str, uint16_t strlen);
extern	void 	Disp_Box(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t bevel_edge,uint32_t color);
void flashSetFlags(u8 blank);
void flashMainFlags(u8 blank);
//u8 adx[26]={0},ad_ram[4];
uint16_t val_hz;
u8 hz_t;
extern uint8_t key,key_flg,key_sum;
//union UUUU tem;
u8 TSetInput =1;			 //
u8 MainFDSP= 1;//
//u8 KPVCursorP =Nub2cur;				//
//u8 KPACursorP =Nub2cur;				//
//u8 KPOVPCursorP  =Nub2cur;			//
//u8 KPOCPCursorP  =Nub2cur;			//
u8 KInputF;			//
char *DIS;			//
char *TDKS;			//
char DInputNum[10];	//

char DisPFInputNum[6];	//
char DisVAInputNum[6];	//
char DisFInputNum[6];	//
char DisPFInputNum[6];	//
char DisVARInputNum[6];	//
char DisVHzInputNum[6];	//
char DisIHzInputNum[6];	//

char TTULnputNum[10];//临时现存 用于如果输入值大于范围显示位之前的值   
char TTILnputNum[10];//
char TTADDnputNum[10];//

char TTPFInputNum[6];	//
char TTVAInputNum[6];	//
char TTFInputNum[6];	//
char TTPFInputNum[6];	//
char TTVARInputNum[6];	//
char TTVHzInputNum[6];	//
char TTIHzInputNum[6];	//


u8 EN_CurDIS =0;
u8 KPULCursorP  =Nub3cur;
u8 KPILCursorP  =Nub2cur;
u8 KPADDCursorP =Nub3cur;
u8 datapage;
extern u8 setflag;

FATFS fs;         /* Work area (file system object) for logical drive */
FIL fsrc;         /* file objects */   
FRESULT res;
UINT br;

struct RDispPara Para_main[]={
	{8, 40 ,3, 0,1,0, "MODE :", "ģʽ:" },
	 { 8, 70,6, 0,4,0,"RNG_V:" , "V��Χ:" },
	  {8, 100 ,6, 0,7,0, "RNG_I:" , "I��Χ:" },
		{ 10, 150 ,0, 0,20000,0, "VA:" , "VA:" },
		{10, 180 ,0, 0,20000,0,"PF:" , "PF:" },
    { 10, 210 ,0, 0,20000,0, "VAR:"  , "VAR:" },
		{ 10, 240 ,0, 0,20000,0, "FREQ:" , "Ƶ��:" },
		{170, 240 ,0,  0,20000,0,"VHz:"  , "VHz:" },
		{ 330, 240 ,0, 0,20000,0, "IHz:"  , "IHz:" },
};

struct bitDefine
{
    unsigned bit0: 1;
    unsigned bit1: 1;
    unsigned bit2: 1;
    unsigned bit3: 1;
    unsigned bit4: 1;
    unsigned bit5: 1;
    unsigned bit6: 1;
    unsigned bit7: 1;
} flagA, flagB,flagC,flagD,flagE,flagF,flagG , flagH,flagI,flagJ;

typedef struct
{
  uint16_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_data_direction */

  uint16_t SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */

  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
 
  uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint16_t SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
}SPI_InitTypeDef;
//typedef struct
//{
//  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
//                                       This parameter can be any value of @ref GPIO_pins_define */

//  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
//                                       This parameter can be a value of @ref GPIOMode_TypeDef */

//  GPIOSpeed_TypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.
//                                       This parameter can be a value of @ref GPIOSpeed_TypeDef */

//  GPIOOType_TypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.
//                                       This parameter can be a value of @ref GPIOOType_TypeDef */

//  GPIOPuPd_TypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.
//                                       This parameter can be a value of @ref GPIOPuPd_TypeDef */
//}GPIO_InitTypeDef;
//void SPI_FLASH_Init(void)
//{
//  SPI_InitTypeDef  SPI_InitStructure;
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  /* ?? FLASH_SPI ?GPIO ?? */
//  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO, 
//       SPI_FLASH_SPI_MISO_GPIO,SPI_FLASH_SPI_SCK_GPIO ???? */
//  RCC_AHB1PeriphClockCmd (FLASH_SPI_SCK_GPIO_CLK | FLASH_SPI_MISO_GPIO_CLK|FLASH_SPI_MOSI_GPIO_CLK|FLASH_CS_GPIO_CLK, ENABLE);

//  /*!< SPI_FLASH_SPI ???? */
//  FLASH_SPI_CLK_INIT(FLASH_SPI_CLK, ENABLE);
// 
//  //??????
//  GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT,FLASH_SPI_SCK_PINSOURCE,FLASH_SPI_SCK_AF); 
//	GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT,FLASH_SPI_MISO_PINSOURCE,FLASH_SPI_MISO_AF); 
//	GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT,FLASH_SPI_MOSI_PINSOURCE,FLASH_SPI_MOSI_AF); 
//  
//  /*!< ?? SPI_FLASH_SPI ??: SCK */
//  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
//  
//  GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
//  
//	/*!< ?? SPI_FLASH_SPI ??: MISO */
//  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
//  GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
//  
//	/*!< ?? SPI_FLASH_SPI ??: MOSI */
//  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
//  GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);  

//	/*!< ?? SPI_FLASH_SPI ??: CS */
//  GPIO_InitStructure.GPIO_Pin = FLASH_CS_PIN;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStructure);

//  /* ???? FLASH: CS?????*/
//  SPI_FLASH_CS_HIGH();

//  /* FLASH_SPI ???? */
//  // FLASH?? ??SPI??0???3,????CPOL CPHA
//  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
//  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//  SPI_InitStructure.SPI_CRCPolynomial = 7;
//  SPI_Init(FLASH_SPI, &SPI_InitStructure);

//  /* ?? FLASH_SPI  */
//  SPI_Cmd(FLASH_SPI, ENABLE);
//}
void dly10(u8 t)
{
u8 y;
	for(y=0;y<t;t++)
	{y=y;}
}



//==========================================================
//�������ƣ�Power_Process
//�������ܣ��ϵ紦��
//��ڲ�������
//���ڲ�������
//�������ڣ�2015.10.26
//�޸����ڣ�2015.10.26 08:53
//��ע˵������������SET����У׼����ģʽ
//==========================================================
void Power_Process(void)
{
//	InitGlobalValue();//��ʼ��ȫ�ֱ���
//	init_timer(0, 20);//��ʱ����ʼ��
//	enable_timer(0);
	Uart_Send_Flag=0;
	EEPROM_Init();
//	EEPROM_Write(0, 0, buff, MODE_8_BIT, 4000);
//	EEPROM_Read(0, 0, buff, MODE_8_BIT, 4095);
//	Set_Compbcd_float();
	ReadSavedata();//��ȡ��������
	if(flag_SetAutoZero == 0)
	{
		setflag = 1;
	}
//GPIO_5463_Configuration();
//	Disp_PowerOn_Menu();//��ʾ��������
//lcd_image((uint8_t *)gImage_open);
//	Electric_currentAmp(0);

//	if(AddressVal==0xff)
//	AddressVal=1;
//if(CurrentLimit>2051000)CurrentLimit=2000000;
//if(POWLimit>99999)POWLimit=99999;
}

extern void UARTPuts(LPC_UART_TypeDef *UARTx, const void *str);

//extern void Page_Polygon_Box(void);
//extern  void Disp_Box(uint16_t x1,uint16_t y1,uint16_t x2, uint16_t y2, uint8_t bevel_edge, uint32_t color);
//uint8_t  r421_rang;

/*
const char V_Auto[][7]=
{  "V-Auto",	"I-Auto"};
const char V_300v[][7]=
{  "300 AC",	"2500mA"};*/
const char Rms[][4]=
	{  "Rms",	"ON"};

const char RNG_V[][7]=
{  "U-Auto",	"75V",	"150V",	"300V",	"600V"};
const char RNG_I[][7]=
{  "A-Auto",	"1mA",	"3mA",	"10mA",	"40mA",	"150mA",	"500mA","2A"};

//const char PVA[][4]=
//	{  "P:",	"VA:"};
const char PFHZ[][6]=
	{  "PF:",	"Freq:"};
const char PIA[][3]=
	{  "V","mA","Hz","W","va","s"};

union fc
{
    float f;
	uint32_t sum;
    uint8_t c[4];
};
union fc V_val,A_val,P_val,HZ_val,PF_val,VA_val,E_val,VAR_val,VHz_val,IHz_val,WH_val,T_val;	

//unsigned char Bmp030[]=
//{
/*------------------------------------------------------------------------------
;  ??? / ?? : P
;  ?�?(??): 36�40
------------------------------------------------------------------------------*/
//0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x42,0x3E,0x02,0x02,0x02,0x02,0x07,0x00,0x00,

//};
void	USE_SETSW( void )			
{
	TSetInput = SET;  //使能输入
	EN_CurDIS = SET; //使能光标单独显示 同同时用于按下按键光标自动移位

	//保存光标赋值
	if(MainFDSP== MainsetMu)  //如果是设置界面
	{
		if(BlankP==ModePnt||BlankP==URangPnt||BlankP==IRangPnt)
		CursorP =Nub5cur;
			else
		CursorP =Nub2cur;
	}
	else if(MainFDSP== SYSsetMu)  //如果是设置界面
	{
			switch(BlankP)
			{
//				case AddressPnt:
//					CursorP = KPADDCursorP;
//				    KInputF = CursorP-2;
//					break;
				case PLimitPnt:
					CursorP = KPULCursorP;
					break;
				case ILimitPnt:
					CursorP = KPILCursorP;
					break;
				default:
					CursorP = Nub5cur;    //???
					break;
			}
	}
}
/*
static void SlectMainPara( uint8_t i ,uint8_t blank)
{
	char str[10]={0};
	int len = 0;

	Colour.Fword=White;//
  Colour.black=Black;
	switch(i)
	{
		case ModePnt:
			WriteString_16(Para_main[i].row+63, Para_main[i].col, (char *)Rms[Para_main[i].val],  0);
		  len = strlen(Rms[Para_main[i].val]);    //
		  strncpy(str,Rms[Para_main[i].val],len);
			break;
		case URangPnt:
			WriteString_16(Para_main[i].row+63, Para_main[i].col, (char *)RNG_V[Para_main[i].val],  0);
		  len = strlen(RNG_V[Para_main[i].val]);    //
		  strncpy(str,RNG_V[Para_main[i].val],len);
			break;
		case IRangPnt:
			WriteString_16(Para_main[i].row+63, Para_main[i].col, (char *)RNG_I[Para_main[i].val],  0);
		  len = strlen(RNG_I[Para_main[i].val]);    //
		  strncpy(str,RNG_I[Para_main[i].val],len);
			break;

		case PFPnt:
			Para_main[i].val = PF_val.sum;
			DisPFInputNum[0] =  Para_main[i].val /10000;  
				DisPFInputNum[1] =  '.';
				DisPFInputNum[2] =  Para_main[i].val %10000 /1000; 
				DisPFInputNum[3] =  Para_main[i].val %1000 /100; 
				DisPFInputNum[4] =  Para_main[i].val %100  /10; 
				DisPFInputNum[5] =  Para_main[i].val %10 ; 
			PutNum(Para_main[i].row+48, Para_main[i].col, DisPFInputNum[0], Colour.Fword, Colour.black );
		  PutChar( Para_main[i].row+60, Para_main[i].col , DisPFInputNum[1], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+72, Para_main[i].col,  DisPFInputNum[2], Colour.Fword, Colour.black ); 
			PutNum(Para_main[i].row+84, Para_main[i].col,  DisPFInputNum[3], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+96, Para_main[i].col,  DisPFInputNum[4], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+108, Para_main[i].col,  DisPFInputNum[5], Colour.Fword, Colour.black );
			//PutChar( Para_main[i].row+173, Para_main[i].col , 'V', Colour.Fword, Colour.black );
			len = 6;
			break;
		case FPnt:
			Para_main[i].val = HZ_val.sum;
			DisFInputNum[0] =  Para_main[i].val /10000;
					DisFInputNum[1] =  Para_main[i].val %10000 /1000; 
					DisFInputNum[2] =  '.'; 
					DisFInputNum[3] =  Para_main[i].val %1000 /100; 
					DisFInputNum[4] =  Para_main[i].val %100 /10; 
					DisFInputNum[5] =  Para_main[i].val %10; 
			PutNum(Para_main[i].row+48, Para_main[i].col, DisFInputNum[0], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+60, Para_main[i].col,  DisFInputNum[1], Colour.Fword, Colour.black ); 
			PutChar(Para_main[i].row+72, Para_main[i].col , DisFInputNum[2], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+84, Para_main[i].col,  DisFInputNum[3], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+96, Para_main[i].col,  DisFInputNum[4], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+108, Para_main[i].col,  DisFInputNum[5], Colour.Fword, Colour.black );
			len = 6;
			break;
		case VAPnt:
			Para_main[i].val = VA_val.sum;
			DisVAInputNum[0] =  Para_main[i].val /10000;  
				DisVAInputNum[1] =  '.'; 
				DisVAInputNum[2] =  Para_main[i].val %10000 /1000; 
				DisVAInputNum[3] =  Para_main[i].val %1000 /100; 
				DisVAInputNum[4] =  Para_main[i].val %100 /10; 
				DisVAInputNum[5] =  Para_main[i].val %10; 
			PutNum(Para_main[i].row+48, Para_main[i].col, DisVAInputNum[0], Colour.Fword, Colour.black );
				PutChar( Para_main[i].row+60, Para_main[i].col , DisVAInputNum[1], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+72, Para_main[i].col,  DisVAInputNum[2], Colour.Fword, Colour.black ); 
			PutNum(Para_main[i].row+84, Para_main[i].col,  DisVAInputNum[3], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+96, Para_main[i].col,  DisVAInputNum[4], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+108, Para_main[i].col,  DisVAInputNum[5], Colour.Fword, Colour.black );
			len = 6;
			break;
		case VARPnt:
			Para_main[i].val = VAR_val.sum;
			DisVARInputNum[0] =  Para_main[i].val /10000;  
				DisVARInputNum[1] =  '.'; 
				DisVARInputNum[2] =  Para_main[i].val %10000 /1000; 
				DisVARInputNum[3] =  Para_main[i].val %1000 /100; 
				DisVARInputNum[4] =  Para_main[i].val %100 /10; 
				DisVARInputNum[5] =  Para_main[i].val %10; 
			PutNum(Para_main[i].row+48, Para_main[i].col, DisVARInputNum[0], Colour.Fword, Colour.black );
				PutChar( Para_main[i].row+60, Para_main[i].col , DisVARInputNum[1], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+72, Para_main[i].col,  DisVARInputNum[2], Colour.Fword, Colour.black ); 
			PutNum(Para_main[i].row+84, Para_main[i].col,  DisVARInputNum[3], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+96, Para_main[i].col,  DisVARInputNum[4], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+108, Para_main[i].col,  DisVARInputNum[5], Colour.Fword, Colour.black );
			len = 6;
			break;
		case IHzPnt:
			Para_main[i].val = IHz_val.sum;
			DisIHzInputNum[0] =  Para_main[i].val /10000;  
					DisIHzInputNum[1] =  Para_main[i].val %10000 /1000; 
					DisIHzInputNum[2] =  '.'; 
					DisIHzInputNum[3] =  Para_main[i].val %1000 /100; 
					DisIHzInputNum[4] =  Para_main[i].val %100 /10; 
					DisIHzInputNum[5] =  Para_main[i].val %10; 
			PutNum(Para_main[i].row+48, Para_main[i].col, DisIHzInputNum[0], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+60, Para_main[i].col,  DisIHzInputNum[1], Colour.Fword, Colour.black ); 
        PutChar( Para_main[i].row+72, Para_main[i].col , DisIHzInputNum[2], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+84, Para_main[i].col,  DisIHzInputNum[3], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+96, Para_main[i].col,  DisIHzInputNum[4], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+108, Para_main[i].col,  DisIHzInputNum[5], Colour.Fword, Colour.black );
			len = 6;
			break;
		case VHzPnt:
			Para_main[i].val = VHz_val.sum;
			DisVHzInputNum[0] =  Para_main[i].val /10000 ;  
					DisVHzInputNum[1] =  Para_main[i].val %10000 /1000; 
					DisVHzInputNum[2] =  '.'; 
					DisVHzInputNum[3] =  Para_main[i].val %1000 /100; 
					DisVHzInputNum[4] =  Para_main[i].val %100 /10; 
					DisVHzInputNum[5] =  Para_main[i].val %10; 
			PutNum(Para_main[i].row+48, Para_main[i].col, DisVHzInputNum[0], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+60, Para_main[i].col,  DisVHzInputNum[1], Colour.Fword, Colour.black ); 
			//PutNum(Para_main[i].row+72, Para_main[i].col,  DisVHzInputNum[2], Colour.Fword, Colour.black ); 
        PutChar( Para_main[i].row+72, Para_main[i].col , DisVHzInputNum[2], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+84, Para_main[i].col,  DisVHzInputNum[3], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+96, Para_main[i].col,  DisVHzInputNum[4], Colour.Fword, Colour.black );
			PutNum(Para_main[i].row+108, Para_main[i].col,  DisVHzInputNum[5], Colour.Fword, Colour.black );
			len = 6;
			break;
		default: i=0;
			break;	
}
	if(len>0&&i==blank)   
	{
		Colour.Fword=Red;
		Colour.black=Blue;

			if(blank==PFPnt)
			{
				PutNum(Para_main[i].row+48, Para_main[i].col, DisPFInputNum[0], Colour.Fword, Colour.black );
				PutChar( Para_main[i].row+60, Para_main[i].col , DisPFInputNum[1], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+72, Para_main[i].col,  DisPFInputNum[2], Colour.Fword, Colour.black ); 
				PutNum(Para_main[i].row+84, Para_main[i].col,  DisPFInputNum[3], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+96, Para_main[i].col,  DisPFInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+108, Para_main[i].col,  DisPFInputNum[5], Colour.Fword, Colour.black );
			}
			if(blank==FPnt)
			{
				PutNum(Para_main[i].row+48, Para_main[i].col, DisFInputNum[0], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+60, Para_main[i].col,  DisFInputNum[1], Colour.Fword, Colour.black ); 
				PutChar( Para_main[blank].row+72, Para_main[blank].col , DisFInputNum[2], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+84, Para_main[i].col,  DisFInputNum[3], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+96, Para_main[i].col,  DisFInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+108, Para_main[i].col,  DisFInputNum[5], Colour.Fword, Colour.black );
			}
			else if(blank==VAPnt)
			{
				PutNum(Para_main[i].row+48, Para_main[i].col, DisVAInputNum[0], Colour.Fword, Colour.black );
				PutChar( Para_main[i].row+60, Para_main[i].col , DisVAInputNum[1], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+72, Para_main[i].col,  DisVAInputNum[2], Colour.Fword, Colour.black ); 
				PutNum(Para_main[i].row+84, Para_main[i].col,  DisVAInputNum[3], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+96, Para_main[i].col,  DisVAInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+108, Para_main[i].col,  DisVAInputNum[5], Colour.Fword, Colour.black );
			}
			else if(blank== VARPnt)
			{
				PutNum(Para_main[i].row+48, Para_main[i].col, DisVARInputNum[0], Colour.Fword, Colour.black );
				PutChar( Para_main[i].row+60, Para_main[i].col , DisVARInputNum[1], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+72, Para_main[i].col,  DisVARInputNum[2], Colour.Fword, Colour.black ); 
				PutNum(Para_main[i].row+84, Para_main[i].col,  DisVARInputNum[3], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+96, Para_main[i].col,  DisVARInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+108, Para_main[i].col,  DisVARInputNum[5], Colour.Fword, Colour.black );
			}
			else if(blank== IHzPnt)
			{
				PutNum(Para_main[i].row+48, Para_main[i].col, DisIHzInputNum[0], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+60, Para_main[i].col,  DisIHzInputNum[1], Colour.Fword, Colour.black ); 
        PutChar( Para_main[i].row+72, Para_main[i].col , DisIHzInputNum[2], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+84, Para_main[i].col,  DisIHzInputNum[3], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+96, Para_main[i].col,  DisIHzInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+108, Para_main[i].col,  DisIHzInputNum[5], Colour.Fword, Colour.black );
			}
			else if(blank==VHzPnt)
			{
				PutNum(Para_main[i].row+48, Para_main[i].col,DisVHzInputNum[0],Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+60, Para_main[i].col, DisVHzInputNum[1],Colour.Fword, Colour.black ); 
        PutChar( Para_main[i].row+72, Para_main[i].col,DisVHzInputNum[2],Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+84, Para_main[i].col,DisVHzInputNum[3],Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+96, Para_main[i].col,DisVHzInputNum[4],Colour.Fword, Colour.black );
				PutNum(Para_main[i].row+108, Para_main[i].col,DisVHzInputNum[5],Colour.Fword, Colour.black );
			}
			else if(blank==ModePnt)
				WriteString_16(Para_main[i].row+63,Para_main[i].col,(char *)Rms[Para_main[i].val],0);

			else if(blank==URangPnt)
				WriteString_16(Para_main[i].row+63,Para_main[i].col,(char *)RNG_V[Para_main[i].val],0);

			else if(blank==IRangPnt)
				WriteString_16(Para_main[i].row+63,Para_main[i].col,(char *)RNG_I[Para_main[i].val],0);
		}
}
*/
void DisBlank_main(unsigned char bank,uint8_t mode)
{
	  if(BlankP==ModePnt||BlankP==URangPnt||BlankP==IRangPnt)
    LCD_DrawRect(Para_main[bank].row+63,Para_main[bank].col,Para_main[bank].row+63+Para_main[bank].len*10,Para_main[bank].col+16,Colour.black );
			else
		LCD_DrawRect(Para_main[bank].row+48,Para_main[bank].col,Para_main[bank].row+48+Para_main[bank].len*10,Para_main[bank].col+16,Colour.black );
		Colour.Fword=Red;
		Colour.black=Blue;
			if(bank==PFPnt)
			{
				Para_main[bank].val = PF_val.sum;
				DisPFInputNum[0] =  Para_main[bank].val /10000;  
				DisPFInputNum[1] =  '.'; 
				DisPFInputNum[2] =  Para_main[bank].val %10000 /1000; 
				DisPFInputNum[3] =  Para_main[bank].val %1000 /100; 
				DisPFInputNum[4] =  Para_main[bank].val %100 /10; 
				DisPFInputNum[5] =  Para_main[bank].val %10; 
				PutNum(Para_main[bank].row+48, Para_main[bank].col, DisPFInputNum[0], Colour.Fword, Colour.black);
				PutChar(Para_main[bank].row+60, Para_main[bank].col , DisPFInputNum[1], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+72, Para_main[bank].col,  DisPFInputNum[2], Colour.Fword, Colour.black); 

				PutNum(Para_main[bank].row+84, Para_main[bank].col,  DisPFInputNum[3], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+96, Para_main[bank].col,  DisPFInputNum[4], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+108, Para_main[bank].col,  DisPFInputNum[5], Colour.Fword, Colour.black);
				if(TSetInput==SET)
				PutNum(Para_main[bank].row+48+12*(KInputF),Para_main[bank].col,DisPFInputNum[KInputF],Colour.black,Colour.Fword);
			}
			else if(bank==FPnt)
			{
				Para_main[bank].val = HZ_val.sum;
				DisFInputNum[0] =  Para_main[bank].val /10000;  
					DisFInputNum[1] =  Para_main[bank].val %10000 /1000; 
					DisFInputNum[2] =  '.';
					DisFInputNum[3] =  Para_main[bank].val %1000 /100; 
					DisFInputNum[4] =  Para_main[bank].val %100 /10; 
					DisFInputNum[5] =  Para_main[bank].val %10 ; 
				PutNum(Para_main[bank].row+48, Para_main[bank].col, DisFInputNum[0], Colour.Fword, Colour.black );
				PutNum(Para_main[bank].row+60, Para_main[bank].col,  DisFInputNum[1], Colour.Fword, Colour.black ); 
				PutChar(Para_main[bank].row+72,Para_main[bank].col , DisFInputNum[2], Colour.Fword, Colour.black );
				PutNum(Para_main[bank].row+84, Para_main[bank].col,  DisFInputNum[3], Colour.Fword, Colour.black );
				PutNum(Para_main[bank].row+96, Para_main[bank].col,  DisFInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_main[bank].row+108,Para_main[bank].col,  DisFInputNum[5], Colour.Fword, Colour.black );
		  	if(TSetInput ==SET)
				{
					PutNum(Para_main[bank].row+48+12*(KInputF),Para_main[bank].col,DisFInputNum[KInputF],Colour.black,Colour.Fword); 
				}
			}
			else if(bank==VAPnt)
			{
				Para_main[bank].val = VA_val.sum;
				DisVAInputNum[0] =  Para_main[bank].val /10000;  
				DisVAInputNum[1] =  '.'; 
				DisVAInputNum[2] =  Para_main[bank].val %10000 /1000; 
				DisVAInputNum[3] =  Para_main[bank].val %1000 /100; 
				DisVAInputNum[4] =  Para_main[bank].val %100 /10; 
				DisVAInputNum[5] =  Para_main[bank].val %10; 
				PutNum(Para_main[bank].row+48, Para_main[bank].col, DisVAInputNum[0], Colour.Fword, Colour.black);
				PutChar(Para_main[bank].row+60,Para_main[bank].col, DisVAInputNum[1], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+72, Para_main[bank].col,  DisVAInputNum[2], Colour.Fword, Colour.black); 
				PutNum(Para_main[bank].row+84, Para_main[bank].col,  DisVAInputNum[3], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+96, Para_main[bank].col,  DisVAInputNum[4], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+108,Para_main[bank].col,  DisVAInputNum[5], Colour.Fword, Colour.black);
			if(TSetInput ==SET)
					PutNum(Para_main[bank].row+48+12*(KInputF),Para_main[bank].col,DisVAInputNum[KInputF],Colour.black,Colour.Fword); 
			}
			else if(bank== VARPnt)
			{
				Para_main[bank].val = VAR_val.sum;
				DisVARInputNum[0] =  Para_main[bank].val /10000;  
				DisVARInputNum[1] =  '.'; 
				DisVARInputNum[2] =  Para_main[bank].val %10000 /1000; 
				DisVARInputNum[3] =  Para_main[bank].val %1000 /100; 
				DisVARInputNum[4] =  Para_main[bank].val %100 /10; 
				DisVARInputNum[5] =  Para_main[bank].val %10; 
				PutNum(Para_main[bank].row+48, Para_main[bank].col, DisVARInputNum[0], Colour.Fword, Colour.black);
				PutChar(Para_main[bank].row+60, Para_main[bank].col, DisVARInputNum[1], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+72, Para_main[bank].col,  DisVARInputNum[2], Colour.Fword, Colour.black); 
				PutNum(Para_main[bank].row+84, Para_main[bank].col,  DisVARInputNum[3], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+96, Para_main[bank].col,  DisVARInputNum[4], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+108, Para_main[bank].col,  DisVARInputNum[5], Colour.Fword, Colour.black);
			  if(TSetInput ==SET)
					PutNum(Para_main[bank].row+48+12*(KInputF),Para_main[bank].col,DisVARInputNum[KInputF],Colour.black,Colour.Fword); 
			}
			else if(bank== IHzPnt)
			{
				Para_main[bank].val = IHz_val.sum;
				DisIHzInputNum[0] =  Para_main[bank].val /10000;  
					DisIHzInputNum[1] =  Para_main[bank].val %10000 /1000; 
					DisIHzInputNum[2] =  '.'; 
					DisIHzInputNum[3] =  Para_main[bank].val %1000 /100; 
					DisIHzInputNum[4] =  Para_main[bank].val %100 /10; 
					DisIHzInputNum[5] =  Para_main[bank].val %10; 
				PutNum(Para_main[bank].row+48, Para_main[bank].col, DisIHzInputNum[0], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+60, Para_main[bank].col,  DisIHzInputNum[1], Colour.Fword, Colour.black); 
        PutChar(Para_main[bank].row+72, Para_main[bank].col, DisIHzInputNum[2], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+84, Para_main[bank].col,  DisIHzInputNum[3], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+96, Para_main[bank].col,  DisIHzInputNum[4], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+108, Para_main[bank].col,  DisIHzInputNum[5], Colour.Fword, Colour.black);
				 if(TSetInput ==SET)
					PutNum(Para_main[bank].row+48+12*(KInputF),Para_main[bank].col,DisIHzInputNum[KInputF],Colour.black,Colour.Fword);
			}
			else if(bank==VHzPnt)
			{
				Para_main[bank].val = VHz_val.sum;
				DisVHzInputNum[0] =  Para_main[bank].val /10000;  
					DisVHzInputNum[1] =  Para_main[bank].val %10000 /1000; 
					DisVHzInputNum[2] =  '.'; 
					DisVHzInputNum[3] =  Para_main[bank].val %1000 /100; 
					DisVHzInputNum[4] =  Para_main[bank].val %100 /10; 
					DisVHzInputNum[5] =  Para_main[bank].val %10; 
				PutNum(Para_main[bank].row+48, Para_main[bank].col, DisVHzInputNum[0], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+60, Para_main[bank].col,  DisVHzInputNum[1], Colour.Fword, Colour.black); 
        PutChar(Para_main[bank].row+72, Para_main[bank].col , DisVHzInputNum[2], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+84, Para_main[bank].col,  DisVHzInputNum[3], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+96, Para_main[bank].col,  DisVHzInputNum[4], Colour.Fword, Colour.black);
				PutNum(Para_main[bank].row+108, Para_main[bank].col,  DisVHzInputNum[5], Colour.Fword, Colour.black);
				if(TSetInput ==SET)
					PutNum(Para_main[bank].row+48+12*(KInputF),Para_main[bank].col,DisVHzInputNum[KInputF],Colour.black,Colour.Fword);
			}
			else if(bank==ModePnt){
				Colour.Fword=Blue;
				Colour.black=Red;
				WriteString_16(Para_main[bank].row+63,Para_main[bank].col,(char *)Rms[Para_main[bank].val],0);
				
			}else if(bank==URangPnt){
				Colour.Fword=Blue;
				Colour.black=Red;
				WriteString_16(Para_main[bank].row+63,Para_main[bank].col,(char *)RNG_V[Para_main[bank].val],0);
			
			}else if(bank==IRangPnt){
				Colour.Fword=Blue;
				Colour.black=Red;
				WriteString_16(Para_main[bank].row+63,Para_main[bank].col,(char *)RNG_I[Para_main[bank].val],0);
			}
   Colour.Fword=White;
	 Colour.black=LCD_COLOR_TEST_BACK;//Black;
}
#define LCD_COLOR_TURQUOISE		 0x3f4828	//����ɫ     //0x9b9907 (��ɫ)0x5f6738

void RecHandle(void)
{
	u8 i;
	for(i=0;i<3;i++)//��ѹ
	{
		Disp.Voltage[i] = ((ComBuf.rec.buf[VFRAME+i*2]<<8) + 
		ComBuf.rec.buf[VFRAME+1+i*2])*4;
	}
	for(i=0;i<3;i++)//����
	{
		Disp.Current[i] = ((ComBuf.rec.buf[CFRAME+i*2]<<8) + 
		ComBuf.rec.buf[CFRAME+1+i*2])*2;
	}
	for(i=0;i<3;i++)//�й�����
	{
		Disp.Pa[i] = ((ComBuf.rec.buf[PAFRAME+i*2]<<8) + 
		ComBuf.rec.buf[PAFRAME+1+i*2]);
		if(Disp.Pa[i] < 0)
		{
			Disp.Pa[i] = -Disp.Pa[i];
		}
		Disp.Pa[i] *= 8;
	}
	for(i=0;i<3;i++)//���ڹ���
	{
		Disp.Power[i] = ((ComBuf.rec.buf[PFRAME+i*2]<<8) +
		ComBuf.rec.buf[PFRAME+1+i*2])*8;
	}
	
	
	
	for(i=0;i<3;i++)//��������
	{
		Disp.Pf[i] = (ComBuf.rec.buf[PFFRAME+i*2]<<8) +
		ComBuf.rec.buf[PFFRAME+1+i*2];
		if(Disp.Pf[i] < 0)
		{
			Disp.Pf[i] = -Disp.Pf[i];
			Disp.polarity[i]=1;//
		}else{
			Disp.polarity[i]=0;
		}
	}
	
	//���й�����
	Disp.PaSum = ((ComBuf.rec.buf[PASUMFRAME]<<8) +
		ComBuf.rec.buf[PASUMFRAME+1])*8;
	
	//���޹�����
	Disp.QSum = ((ComBuf.rec.buf[QSUMFRAME]<<8) +
		ComBuf.rec.buf[QSUMFRAME+1])*8;
	
	//����ƽ����������
	Disp.PfAvg = ((ComBuf.rec.buf[PAVFRAME]<<8) +
		ComBuf.rec.buf[QSUMFRAME+1]);
	
	//Ƶ��
	Disp.Freq = ((ComBuf.rec.buf[FFRAME]<<8) +
		ComBuf.rec.buf[FFRAME+1]);
	
	//�����й����
	Disp.Wp[0] = (int32_t)((double)((ComBuf.rec.buf[WP1RAME]<<24) + 
		(ComBuf.rec.buf[WP1RAME+1]<<16)+
		(ComBuf.rec.buf[WP1RAME+2]<<8)+
		ComBuf.rec.buf[WP1RAME+3]));
	
	//�����޹����
	Disp.Wq[0] = (int32_t)((double)((ComBuf.rec.buf[WQ1RAME]<<24) + 
		(ComBuf.rec.buf[WQ1RAME+1]<<16)+
		(ComBuf.rec.buf[WQ1RAME+2]<<8)+
		ComBuf.rec.buf[WQ1RAME+3]));
	
	//�����й����
	Disp.Wp[1] = (int32_t)((double)((ComBuf.rec.buf[WP2RAME]<<24) + 
		(ComBuf.rec.buf[WP2RAME+1]<<16)+
		(ComBuf.rec.buf[WP2RAME+2]<<8)+
		ComBuf.rec.buf[WP2RAME+3]));
	
	//�����޹����
	Disp.Wq[1] = (int32_t)((double)((ComBuf.rec.buf[WQ2RAME]<<24) + 
		(ComBuf.rec.buf[WQ2RAME+1]<<16)+
		(ComBuf.rec.buf[WQ2RAME+2]<<8)+
		ComBuf.rec.buf[WQ2RAME+3]));
	
	for(i=0;i<3;i++)//�޹�����
	{
		Disp.Pq[i] = ((ComBuf.rec.buf[QFRAME+i*2]<<8) + 
		ComBuf.rec.buf[QFRAME+1+i*2]);
		
		if(Disp.Pq[i] < 0)
		{
			Disp.Pq[i] = -Disp.Pq[i];
		}
		Disp.Pq[i] *= 8;
	}
	
//	for(i=0;i<3;i++)//Ƶ��
//	{
////		Disp.Voltage[i] = (uint32_t)((double)((ComBuf.rec.buf[3+i*2]<<8) + 
////			ComBuf.rec.buf[4+i*2]) * 3);
//		Disp.SFreq[i] = (ComBuf.rec.buf[FSFRAME+i*2]<<8) +
//		ComBuf.rec.buf[FSFRAME+1+i*2];
//	}
//	for(i=0;i<3;i++)//�й����
//	{
//		Disp.W[i] = (int32_t)((double)((ComBuf.rec.buf[WFRAME+i*4]<<24) + 
//		(ComBuf.rec.buf[WFRAME+1+i*4]<<16)+
//		(ComBuf.rec.buf[WFRAME+2+i*4]<<8)+
//		ComBuf.rec.buf[WFRAME+3+i*4])*300*20/3600);
//	}
//	Disp.Current = (ComBuf.rec.buf[5]<<8) + ComBuf.rec.buf[6];//10A
//	Disp.Pa = ((ComBuf.rec.buf[7]<<8) + ComBuf.rec.buf[8])*25;//10A
//	Disp.Power =((ComBuf.rec.buf[31]<<8) + ComBuf.rec.buf[32])*25;//10A
//	Disp.Current = ((ComBuf.rec.buf[5]<<8) + ComBuf.rec.buf[6])*2;//20A
//	Disp.Pa = ((ComBuf.rec.buf[7]<<8) + ComBuf.rec.buf[8])*50;//20A
//	Disp.Power =((ComBuf.rec.buf[31]<<8) + ComBuf.rec.buf[32])*50;//20A
//	Disp.Pf = ((ComBuf.rec.buf[11])<<8) + (ComBuf.rec.buf[12]);
//	Disp.Freq = (ComBuf.rec.buf[13]<<8) + ComBuf.rec.buf[14];
	
	
//	Disp.Pf=0x03e8;
	
}
void MaxAlarm(void)
{
	if(Flag_Alarm_OFF == 0)
	{
		if(Disp.Current[0] > CurrentLimit ||
			Disp.Current[1] > CurrentLimit	||
			Disp.Pa[0] > POWLimit ||
			Disp.Pa[1] > POWLimit)
		{
			BUZZER();
			D1_H
//			GPIO_SetValue(0, (1<<12));
		}else{
			GPIO_SetDir(0, (1<<12), GPIO_DIRECTION_OUTPUT);	
//			BUZZER();
//			GPIO_SetValue(0, (1<<12));
			GPIO_ClearValue(0, (1<<12));//beep off
			D1_L
		}
	}else{
		GPIO_SetDir(0, (1<<12), GPIO_DIRECTION_OUTPUT);	
		GPIO_ClearValue(0, (1<<12));//beep off
		D1_L
	}
}
void Disp_R(uint8_t para)
{
	char  buf[8]={"0"};
	char  over[7]={"       "};
	static char t,alrmi,alrmp;
	uint8_t i=0,potv,potvp,poti,potw,potva;
	uint32_t valp,pfx;
//	Colour.Fword=White;
//  Colour.black=LCD_COLOR_TEST_BACK;//0x202020;//Black;//LCD_COLOR_TURQUOISE;//

////	Disp_Box(1,25,478,268,3,Yellow);
//	Draw_LIN5(1,74-49,475+3,Yellow);
//	Draw_LIN5(1,74,475+3,Green);
//	Draw_LIN5(1,123,475+3,PCOLOR);
//	Draw_LIN5(1,172,475+3,LCD_COLOR_MAGENTA);
//	Draw_LIN5(1,221,475+3,FCOLOR);
//	Draw_LIN3_Y(241,25,242,Yellow);
////	Draw_LIN5(3,123,150-MENUOFFSETX,Yellow);
////	LCD_DrawLine(120,55,478,55,Yellow);
//	if(flag_SetLang==0)			WriteString_16(0,4,All_TopName[0],0);

//		else		  WriteString_16(0,4,All_TopName_E[0],0);

	Colour.Fword=White;
//	Colour.black=Black;
//	for(i=ModePnt;i<=IRangPnt;i++)
//	{
//		if(flag_SetLang==0)			WriteString_16(Para_main[i].row, Para_main[i].col, (char *)Para_main[i].Ch,1);

//		else		  WriteString_16(Para_main[i].row, Para_main[i].col, (char *)Para_main[i].En,0);
//	}
//U rms
	Colour.Fword=Yellow;
  Colour.black=LCD_COLOR_BLACK;
//Colour.black=Black;//
//	LCD_ShowFontCN_40_55(159-MENUOFFSETX,33,24,34,(uint8_t*)nAsciiDot20X40E+102*53);//U
//		WriteString_16(185-MENUOFFSETX, 52, Rms[0], 0);
//		LCD_ShowFontCN_40_55(215-MENUOFFSETX,33,24,34,(uint8_t*)nAsciiDot20X40E+102*26);//:
//		LCD_ShowFontCN_40_55(453,33,24,34,(uint8_t*)nAsciiDot20X40E+102*54);//V

//if(ComBuf.rec.end)	ComBuf.rec.end=0;

	if(datapage == 0)
	{
	//��ѹ
		Hex_Format(Disp.Voltage[0],2,5,0);
		WriteString_Big(MAINDATA1X,MAINDATA1Y,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X,MAINUNIT1Y,24,34,
		(uint8_t*)nAsciiDot20X40E+102*54);//V
		
		Hex_Format(Disp.Voltage[1],2,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET,MAINDATA1Y,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET,MAINUNIT1Y,24,34,
		(uint8_t*)nAsciiDot20X40E+102*54);//V
		
		Hex_Format(Disp.Voltage[2],2,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET*2,MAINDATA1Y,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET*2,MAINUNIT1Y,24,34,
		(uint8_t*)nAsciiDot20X40E+102*54);//V
		
	//����
		Colour.Fword=Green;
		Hex_Format(Disp.Current[0],3,5,0);
		WriteString_Big(MAINDATA1X,MAINDATA1Y+MAINDATAYOFFSET,DispBuf);
		
		LCD_ShowFontCN_STR_40_55(MAINUNIT1X,
		MAINUNIT1Y+MAINDATAYOFFSET,24,34,(uint8_t*)"A",2);//A
		
		Hex_Format(Disp.Current[1],3,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET,
		MAINDATA1Y+MAINDATAYOFFSET,DispBuf);
		
		LCD_ShowFontCN_STR_40_55(MAINUNIT1X+MAINDATAXOFFSET,
		MAINUNIT1Y+MAINDATAYOFFSET,24,34,(uint8_t*)"A",2);//A
		
		Hex_Format(Disp.Current[2],3,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET*2,
		MAINDATA1Y+MAINDATAYOFFSET,DispBuf);
		
		LCD_ShowFontCN_STR_40_55(MAINUNIT1X+MAINDATAXOFFSET*2,
		MAINUNIT1Y+MAINDATAYOFFSET,24,34,(uint8_t*)"A",2);//A
		
	//�й�����
		Colour.Fword=PCOLOR;
		Hex_Format(Disp.Pa[0],1,5,0);
		WriteString_Big(MAINDATA1X,MAINDATA1Y+MAINDATAYOFFSET*2,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X+24,MAINUNIT1Y+MAINDATAYOFFSET*2,24,34,
		(uint8_t*)nAsciiDot20X40E+102*55);//W
		
		Hex_Format(Disp.Pa[1],1,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET,
		MAINDATA1Y+MAINDATAYOFFSET*2,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET+24,
		MAINUNIT1Y+MAINDATAYOFFSET*2,24,34,
		(uint8_t*)nAsciiDot20X40E+102*55);//W
		
		Hex_Format(Disp.Pa[2],1,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET*2,
		MAINDATA1Y+MAINDATAYOFFSET*2,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET*2+24,
		MAINUNIT1Y+MAINDATAYOFFSET*2,24,34,
		(uint8_t*)nAsciiDot20X40E+102*55);//W
		
	//��������
		Colour.Fword=LCD_COLOR_MAGENTA;
		Hex_Format(Disp.Pf[0],4,5,0);
		WriteString_Big(MAINDATA1X,MAINDATA1Y+MAINDATAYOFFSET*3,DispBuf);
			
		Hex_Format(Disp.Pf[1],4,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET,
		MAINDATA1Y+MAINDATAYOFFSET*3,DispBuf);
		
		Hex_Format(Disp.Pf[2],4,5,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET*2,
		MAINDATA1Y+MAINDATAYOFFSET*3,DispBuf);
		
	//Ƶ��
		Colour.Fword=FCOLOR;
		Hex_Format(Disp.Freq,2,4,0);
		WriteString_Big(MAINDATA1X,MAINDATA1Y+MAINDATAYOFFSET*4,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X,MAINUNIT1Y+MAINDATAYOFFSET*4,
		24,34,(uint8_t*)nAsciiDot20X40E+102*40);//H
		LCD_ShowFontCN_40_55(MAINUNIT1X+24,MAINUNIT1Y+MAINDATAYOFFSET*4,
		24,34,(uint8_t*)nAsciiDot20X40E+102*90);//z

		Hex_Format(Disp.Freq,2,4,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET,
		MAINDATA1Y+MAINDATAYOFFSET*4,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET,
		MAINUNIT1Y+MAINDATAYOFFSET*4,
		24,34,(uint8_t*)nAsciiDot20X40E+102*40);//H
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET+24,
		MAINUNIT1Y+MAINDATAYOFFSET*4,
		24,34,(uint8_t*)nAsciiDot20X40E+102*90);//z
		
		Hex_Format(Disp.Freq,2,4,0);
		WriteString_Big(MAINDATA1X+MAINDATAXOFFSET*2,
		MAINDATA1Y+MAINDATAYOFFSET*4,DispBuf);
		
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET*2,
		MAINUNIT1Y+MAINDATAYOFFSET*4,
		24,34,(uint8_t*)nAsciiDot20X40E+102*40);//H
		LCD_ShowFontCN_40_55(MAINUNIT1X+MAINDATAXOFFSET*2+24,
		MAINUNIT1Y+MAINDATAYOFFSET*4,
		24,34,(uint8_t*)nAsciiDot20X40E+102*90);//z
		
		MaxAlarm();
	}else if(datapage == 1){
		//�й����
		Colour.Fword=White;
		Hex_Format(Disp.W[0],3,7,0);
		WriteString_16(SUBDATA1X,SUBDATA1Y,
		DispBuf,0);
		WriteString_16(SUBUNIT1X,SUBUNIT1Y,
		"kWh",0);
		Hex_Format(Disp.W[1],3,7,0);
		WriteString_16(SUBDATA1X+SUBDATAXOFFSET,SUBDATA1Y,
		DispBuf,0);
		WriteString_16(SUBUNIT1X+SUBDATAXOFFSET,SUBUNIT1Y,
		"kWh",0);
		//���ڹ���
		Hex_Format(Disp.Power[0],1,5,0);
		WriteString_16(SUBDATA1X,SUBDATA1Y+SUBDATAYOFFSET,
		DispBuf,0);	
		WriteString_16(SUBUNIT1X,SUBUNIT1Y+SUBDATAYOFFSET,
		"VA",0);
		Hex_Format(Disp.Power[1],1,5,0);
		WriteString_16(SUBDATA1X+SUBDATAXOFFSET,
		SUBDATA1Y+SUBDATAYOFFSET,
		DispBuf,0);
		WriteString_16(SUBUNIT1X+SUBDATAXOFFSET,
		SUBUNIT1Y+SUBDATAYOFFSET,
		"VA",0);
		//�޹�����
		Hex_Format(Disp.Pq[0],1,5,0);
		WriteString_16(SUBDATA1X,SUBDATA1Y+SUBDATAYOFFSET*2,
		DispBuf,0);	
		WriteString_16(SUBUNIT1X,SUBUNIT1Y+SUBDATAYOFFSET*2,
		"Var",0);
		Hex_Format(Disp.Pq[1],1,5,0);
		WriteString_16(SUBDATA1X+SUBDATAXOFFSET,
		SUBDATA1Y+SUBDATAYOFFSET*2,
		DispBuf,0);
		WriteString_16(SUBUNIT1X+SUBDATAXOFFSET,
		SUBUNIT1Y+SUBDATAYOFFSET*2,
		"Var",0);
	}
//if(para==1)
//{	V_val.c[3]=ComBuf.rec.buf[5];//[3];
//V_val.c[2]=ComBuf.rec.buf[6];//[4];
//V_val.c[1]=ComBuf.rec.buf[4];//[5];
//V_val.c[0]=ComBuf.rec.buf[3];//=0xb9;//[6];
//	
//	valp=V_val.f*100.1;
//	if(V_val.f < 6)
//		valp = 0;
////val*=200;
//	if(valp<100000)
//potv=2;
//else
//{valp/=10;potv=1;}
//	buf[0]='0'+valp/10000;
//buf[1]='0'+valp%10000/1000;
//buf[2]='0'+valp%1000/100;
//if(potv==2)
//{buf[3]='.';
//buf[4]='0'+valp%100/10;
//}
//else
//{buf[3]='0'+valp%100/10;
//buf[4]='.';
//}
//buf[5]='0'+valp%10;

//buf[6]=0;
//WriteString_Big(238,33,buf);
//}//////////////////////////////////////////////end v

 if(alrmi+alrmp)t++;
else
	t=1;
if(t>35)t=0;
//
if(t>20&&!Para_Set[13].val)GPIO_SetValue(0,1<<12);//beep on
else
	GPIO_ClearValue(0,1<<12);//beep off
//I rms
//Colour.Fword=Green;
//LCD_ShowFontCN_40_55(159-MENUOFFSETX,82,24,34,(uint8_t*)nAsciiDot20X40E+102*41);//I
//		WriteString_16(185-MENUOFFSETX,102,Rms[0], 0);
//		LCD_ShowFontCN_40_55(215-MENUOFFSETX,83,24,34,(uint8_t*)nAsciiDot20X40E+102*26);//:
//	 LCD_ShowFontCN_STR_40_55(452,85,24,34,"A",2);
//	Hex_Format(Disp.Current,3,5,0);
//	WriteString_Big(238-MENUOFFSETX,83,DispBuf);
//if(para==1)
//{A_val.c[3]=ComBuf.rec.buf[9];
//A_val.c[2]=ComBuf.rec.buf[10];
//A_val.c[1]=ComBuf.rec.buf[8];
//A_val.c[0]=ComBuf.rec.buf[7];
//valp=A_val.f*100000;
////val=1234567;
//if(V_val.f < 6)
//		valp = 0;
//if(CurrentLimit != 0 && valp>CurrentLimit*100)alrmi=1;

//else	alrmi=0;
//if(valp<100000)poti=2;
//else if(valp<1000000){valp/=10;poti=1;}
//else
//{valp/=100;poti=0;}

//buf[0]='0'+valp/10000;
//buf[1]='0'+valp%10000/1000;
//buf[2]='0'+valp%1000/100;
//if(poti==2)
//{
//buf[3]='.';
//buf[4]='0'+valp%100/10;
//}
//else if(poti==1)
//{
//buf[3]='0'+valp%100/10;
//buf[4]='.';
//}
//else
//{
//buf[3]='0'+valp%100/10;
//buf[4]='0'+valp%10;
//}
//if(poti==0)
//	buf[5]=' ';
//	else
//buf[5]='0'+valp%10;
//if(alrmi&&t>20)
//WriteString_Big(238,83,over);
//	else
//	WriteString_Big(238,83,buf);
//}/////////////////////////////////////////end i
Colour.Fword=PCOLOR;
//P :
//LCD_ShowFontCN_40_55(159-MENUOFFSETX,130,24,34,(uint8_t*)nAsciiDot20X40E+102*48);//P
//LCD_ShowFontCN_40_55(183-MENUOFFSETX,130,24,34,(uint8_t*)nAsciiDot20X40E+102*26);//:
//LCD_ShowFontCN_40_55(452,132,24,34,(uint8_t*)nAsciiDot20X40E+102*55);//W

//	Hex_Format(Disp.Power,2,6,0);
//	WriteString_Big(206-MENUOFFSETX,130,DispBuf);
//p_val
//if(para==1)
//{P_val.c[3]=ComBuf.rec.buf[17];//[11];
//P_val.c[2]=ComBuf.rec.buf[18];//[12];
//P_val.c[1]=ComBuf.rec.buf[16];//[13];
//P_val.c[0]=ComBuf.rec.buf[15];//[14];
//pfx=valp=P_val.f*1000;
////val=3456789;
//if(POWLimit != 0 && (valp>POWLimit*10))alrmp=1;
//else	alrmp=0;
////	if(valp<1000000){potw=3;}
////else if(valp<10000000){valp/=10;potw=2;}
////else if(valp<100000000){valp/=100;potw=1;}
////else	{valp/=1000;potw=0;}
//if(valp<1000000)
//{
//	buf[0]='0'+valp/100000;
//	buf[1]='0'+valp%100000/10000;
//	buf[2]='0'+valp%10000/1000;
//	buf[3]='.';
//	buf[4]='0'+valp%1000/100;
//	buf[5]='0'+valp%100/10;
//	buf[6]='0'+valp%10;
//}else{
//	buf[0]='0'+valp/1000000;
//	buf[1]='0'+valp%1000000/100000;
//	buf[2]='0'+valp%100000/10000;
//	buf[3]='0'+valp%10000/1000;
//	buf[4]='.';
//	buf[5]='0'+valp%1000/100;
//	buf[6]='0'+valp%100/10;
////	buf[6]='0'+valp%10;
//}
////if(potw==2)
////{buf[3]='.';
////buf[4]='0'+valp%100/10;}
////else if(potw==1)
////{buf[3]='0'+valp%100/10;
////buf[4]='.';}
////	else
////	{buf[3]='0'+valp%100/10;
////	buf[4]='0'+valp%10;}
////if(potw==0)
////buf[5]=' ';
////else
////	buf[5]='0'+valp%10;
//if(alrmp&&t>20)
//WriteString_Big(206,130,over);
//	else
//WriteString_Big(206,130,buf);
//}///////////////////////////////////////end p
Colour.Fword=LCD_COLOR_MAGENTA;
//pf
//LCD_ShowFontCN_40_55(159-MENUOFFSETX,180,24,34,(uint8_t*)nAsciiDot20X40E+102*48);//P
//LCD_ShowFontCN_40_55(181-MENUOFFSETX,180,24,34,(uint8_t*)nAsciiDot20X40E+102*70);//f
//LCD_ShowFontCN_40_55(215-MENUOFFSETX,180,24,34,(uint8_t*)nAsciiDot20X40E+102*26);//:

//	Hex_Format(Disp.Pf,4,5,0);
//	WriteString_Big(270-MENUOFFSETX,180,DispBuf);
//pf_val
//if(para==1)
//{PF_val.c[3]=ComBuf.rec.buf[13];
//PF_val.c[2]=ComBuf.rec.buf[14];
//PF_val.c[1]=ComBuf.rec.buf[12];
//PF_val.c[0]=ComBuf.rec.buf[11];
//valp=PF_val.f*1000;
//if(valp>1000)
//	valp=1000;
//if(V_val.f < 6)
//		valp = 0;
////val=POWLimit;
//buf[0]='0'+valp%10000/1000;
//buf[1]='.';
//buf[2]='0'+valp%1000/100;
//buf[3]='0'+valp%100/10;
//buf[4]='0'+valp%10;
//buf[5]=0;
//WriteString_Big(270,180,buf);
//}////////////////////////////////////////end pf
Colour.Fword=FCOLOR;//LCD_COLOR_CYAN;//
//Freq:
//LCD_ShowFontCN_40_55(159-MENUOFFSETX,228,24,34,(uint8_t*)nAsciiDot20X40E+102*38);//F
////LCD_ShowFontCN_40_55(181,228,24,34,(uint8_t*)nAsciiDot20X40E+102*82);//r
////LCD_ShowFontCN_40_55(203,228,24,34,(uint8_t*)nAsciiDot20X40E+102*69);//e
////LCD_ShowFontCN_40_55(225,228,24,34,(uint8_t*)nAsciiDot20X40E+102*81);//q
//LCD_ShowFontCN_40_55(215-MENUOFFSETX,228,24,34,(uint8_t*)nAsciiDot20X40E+102*26);//:

//	Hex_Format(Disp.Freq,2,4,0);
//	WriteString_Big(270-MENUOFFSETX,228,DispBuf);
//if(para==5)
//{HZ_val.c[3]=ComBuf.rec.buf[5];//[19];
//HZ_val.c[2]=ComBuf.rec.buf[6];//[20];
//HZ_val.c[1]=ComBuf.rec.buf[4];//[21];
//HZ_val.c[0]=ComBuf.rec.buf[3];//[22];
//valp=HZ_val.f*10;
//if(V_val.f < 6)
//	valp = 0;
//hz_t++;
//if(hz_t>10)hz_t=1;
//if(hz_t==1)val_hz=valp;
//else
//	val_hz+=valp;
//if(hz_t==10)
//{
////val_hz/=2;
//buf[0]='0'+val_hz%10000/1000;
//buf[1]='0'+val_hz%1000/100;
//buf[2]='.';
//buf[3]='0'+val_hz%100/10;
//buf[4]='0'+val_hz%10;
//buf[5]=0;
//WriteString_Big(270,228,buf);}
//}//////////////////////////////////////end hz
//LCD_ShowFontCN_40_55(430,232,24,34,(uint8_t*)nAsciiDot20X40E+102*40);//H
//LCD_ShowFontCN_40_55(452,232,24,34,(uint8_t*)nAsciiDot20X40E+102*90);//z
//Colour.Fword=White;

////Vpp
//if(para==1)
//{
//	
//	valp=V_val.f*141.4;
//	if(V_val.f < 6)
//	{
//		valp = 0;
//	}
//if(valp<100000)
//{potvp=2;}
//else if(valp<1000000)
//{valp/=10;potvp=1;}
//else
//	{valp/=100;potvp=0;}
//buf[0]='0'+valp/10000;
//buf[1]='0'+valp%10000/1000;
//buf[2]='0'+valp%1000/100;
//if(potvp==2)
//{buf[3]='.';
//buf[4]='0'+valp%100/10;
//}
//else if(potvp==1)
//	{
//buf[3]='0'+valp%100/10;
//buf[4]='.';
//}
//else
//{buf[3]='0'+valp%100/10;
//buf[4]='0'+valp%10;
//}
//if(potvp==0)
//	buf[5]=' ';
//else
//buf[5]='0'+valp%10;
//buf[6]=0;
//WriteString_16(45,140,buf,0);
//}
//WriteString_16(8,140,"Vp:",0);
//WriteString_16(130,140,"V",0);
////////////////////////////////////end vpp

////S:
//WriteString_16(8,170,"S:",0);
//if(para==1)
//{if(pfx)
//VA_val.f=P_val.f/PF_val.f;
//else
//	VA_val.f=0;
//valp=VA_val.f*100;

//if(valp<100000)
//{potva=2;}
//else if(valp<1000000)
//	{valp/=10;potva=1;}
//else
//{valp/=100;potva=0;}
//buf[0]='0'+valp/10000;
//buf[1]='0'+valp%10000/1000;
//buf[2]='0'+valp%1000/100;
//if(potva==2)
//{buf[3]='.';
//	buf[4]='0'+valp%100/10;
//}
//else if(potva==1)
//	{
//	buf[3]='0'+valp%100/10;
//	buf[4]='.';
//}
//else
//{
//buf[3]='0'+valp%100/10;
//buf[4]='0'+valp%10;}
//if(potva==0)
//buf[5]=' ';
//else
//buf[5]='0'+valp%10;
//buf[6]=0;
//WriteString_16(45, 170, buf, 0);
//}
//WriteString_16(130, 170, "VA", 0);
////////////////////////////////////////////end va
/*for(i=VAPnt;i<=IHzPnt;i++)
	{
		if(flag_SetLang==0)
		{
	//		WriteString_16(Para_main[i].row, Para_main[i].col, (uint8_t *)Para_main[i].Ch,  1);
		}
		else
		{
	//	  WriteString_16(Para_main[i].row, Para_main[i].col, (uint8_t *)Para_main[i].En,  0);		
		}
	}*/
//if(para==1)
//{
	Colour.Fword=White;
//VAR:
//WriteString_16(8,205,"T:",0);
//	
//	T_val.c[3]=ComBuf.rec.buf[25];//[3];
//	T_val.c[2]=ComBuf.rec.buf[26];//[4];
//	T_val.c[1]=ComBuf.rec.buf[23];//[5];
//	T_val.c[0]=ComBuf.rec.buf[24];//=0xb9;//[6];
//	
//		valp=(uint16_t)T_val.f;
//	if(V_val.f < 6)
//		valp = 0;
//val*=200;
//	if(valp<100000)
//	potv=2;
//	else
//	{valp/=10;potv=1;}
//		buf[0]='0'+valp/10000;
//	buf[1]='0'+valp%10000/1000;
//	buf[2]='0'+valp%1000/100;
//	if(potv==2)
//	{
////		buf[3]='.';
////		buf[4]='0'+valp%100/10;
//		buf[3]=0;
//		buf[4]=0;
//	}
//	else
//	{buf[3]='0'+valp%100/10;
////	buf[4]='.';

//		buf[4]=0;
//	}
////	buf[5]='0'+valp%10;
//	buf[5]=0;
//	buf[6]=0;
	
//buf[0]='0';//+VAR_val.sum/10000;
//buf[1]='0';//+VAR_val.sum%10000/1000;
//		buf[2]='0';//+alrmp+VAR_val.sum%1000/100;
//		buf[3]='.';
//buf[4]='0';//+VAR_val.sum%100/10;
//		buf[5]='0';//+alrmi+VAR_val.sum%10;
//		buf[6]=0;
//		strncpy(DisVARInputNum,buf,6);
//VAR:_val
//	sprintf(buf,"%d",valp);
//WriteString_16(45,205,buf,0);
//WriteString_16(118,205,PIA[5],0);//var
////}
////if(para==1)
////{
//	WH_val.c[3]=ComBuf.rec.buf[21];//[3];
//WH_val.c[2]=ComBuf.rec.buf[22];//[4];
//WH_val.c[1]=ComBuf.rec.buf[20];//[5];
//WH_val.c[0]=ComBuf.rec.buf[19];//=0xb9;//[6];
//	
//	valp=WH_val.f*100.1;
//	if(V_val.f < 6)
//		valp = 0;
////val*=200;
//	if(valp<100000)
//potv=2;
//else
//{valp/=10;potv=1;}
//	buf[0]='0'+valp/10000;
//buf[1]='0'+valp%10000/1000;
//buf[2]='0'+valp%1000/100;
//if(potv==2)
//{buf[3]='.';
//buf[4]='0'+valp%100/10;
//}
//else
//{buf[3]='0'+valp%100/10;
//buf[4]='.';
//}
//buf[5]='0'+valp%10;

//buf[6]=0;
//WriteString_Big(238,33,buf);

//WriteString_16(8,240,"W:",0);//pf:PFHZ[0]
//WriteString_16(110,240,"W.h",0);
//		//pf_val
//WriteString_16(45,240,buf,0);
//}
//strncpy(DisFInputNum,buf,6);

//strncpy(DisVHzInputNum,buf,6);

//strncpy(DisIHzInputNum,buf,6);

//WriteString_16(Para_main[0].row+63, Para_main[0].col, (char *)Rms[Para_main[0].val],0);//Rms
//WriteString_16(Para_main[1].row+63, Para_main[1].col, (char *)RNG_V[Para_main[1].val],0);//V-Auto
//WriteString_16(Para_main[2].row+63, Para_main[2].col, (char *)RNG_I[Para_main[2].val],0);//A-Auto
//for(i=0; i<=IHzPnt; i++) //
//		{
//		//	SlectMainPara(i,BlankP);
//		}
}

void Send_Uart3(u8 x)//(uint8_t *buff)
{
	u8 readbuf[8]={0x01,0x03,0x00,0x00,0x00,0x2C,0x00,0x00};//v
	readbuf[6] = (u8)(CRC16_Modbus(readbuf,6)>>8);
	readbuf[7] = (u8)(CRC16_Modbus(readbuf,6));
	uartSendChars(LPC_UART0,readbuf,8);
	
}

void SetWZero(void)
{
	u8 setbuf[21]={0x01,0x10,0x00,0x1E,0x00,0x06,0x0C,0x00,0x00,
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
							 ,0x00,0x00};
	setbuf[19] = (u8)(CRC16_Modbus(setbuf,19)>>8);
	setbuf[20] = (u8)(CRC16_Modbus(setbuf,19));
	uartSendChars(LPC_UART0,setbuf,21);
}

void Use_MainProcess(void)
{
	static uint8_t key,ci,p;
	static uint16_t j;
	u8 maxP=Nub5cur;
	u8 minP=Nub1cur;
	u8 dotP=Nub3cur;
//	Button_Page_Typedef Button_Page;
  BlankP = 0;
//	Button_Page.index=0;
//	Button_Page.page=0;
	TSetInput = RESET; 
	MainFDSP = MainsetMu;
	datapage = 0;
  lcd_Clear(LCD_COLOR_TEST_BACK);
	
	//lcd_Clear(0x202020);
	//lcd_Clear(LCD_COLOR_TURQUOISE);
	//Disp_R();
	Delay_Key();
	Disp_Main_set();
	
//	strcpy((char *)bmpname,"0:123456.bmp");
 	while(GetSystemStatus()==SYS_STATUS_MAIN)
	{
//	  ci++;
////		ci%=10;
//		if(datapage == 0)
//		{
//			if(ci>3)			
//			{
//				ci=0;
//				Send_Uart3(1);
//				p=ci;
//			}
//		}else{
//			if(ci>10)			
//			{
//				ci=0;
//				Send_Uart3(1);
//				p=ci;
//			}
//		}
//		if(ci==1)			{Send_Uart3(1);p=ci;}
//		if(ci==3)			{Send_Uart3(2);p=2;}
//		if(ci==5)			{Send_Uart3(3);p=3;}
//		if(ci==7)		{Send_Uart3(4);p=4;}
//		if(ci==9)		{Send_Uart3(5);p=5;}
		if(ComBuf.rec.end==TRUE)
		{
			RecHandle();
			ComBuf.rec.end = 0;
		}
		Disp_R(p);
		key=HW_KeyScsn();
		flashMainFlags(BlankP);

					if(MainFDSP== MainsetMu)
					{
						switch(BlankP)
						{
						case PFPnt:
							dotP = Nub2cur;		 maxP=Nub5cur;  minP=Nub1cur;
							break;
						case FPnt:
							dotP = Nub3cur;		 maxP=Nub5cur;  minP=Nub1cur;
							break;
						case VAPnt:
							 dotP = Nub2cur;	 maxP=Nub5cur;  minP=Nub1cur;
							break;
						case VARPnt:
							dotP = Nub2cur;		 maxP=Nub5cur;  minP=Nub1cur;
							break;
						case IHzPnt:
							dotP = Nub3cur;		 maxP=Nub5cur;  minP=Nub1cur;
							break;
						case VHzPnt:
    					dotP = Nub3cur;		 maxP=Nub5cur;  minP=Nub1cur;
							break;
						default:
							break;
						}
					}

		if(key==0xff)		{key_sum=0;	key_flg=1;}
		else if(key_sum<7)				key_sum++;
		if(key_flg&&key_sum==6)
		{
			key_flg=0;
			if(Para_Set[BeeperPnt].val!=1)
			BUZZER();
		//Key_Pro(key);
			switch(key)
			{
				case KEY_Mid://��ͼ�汾��ͼ
				{
//					sprintf((char *)bmpname,"0:%0.6d.bmp",bmpnum);
//					Screen_shot(0,0,480,272,(const char *)bmpname);
//					bmpnum++;
				}break;
				case KEY_Trig:
				{
					setflag = 1;
				}break;
				case KEY_File://��ͼ�汾��ʼ��U��
				{
//					Host_Init();
//						//rc = Host_EnumDev();       /* Enumerate the device connected                                            */
//						do{
//							res=Host_EnumDev();
//							j++;
//			
//						}while(res!=0&&j<50);
//						if(res==0)
//							usb_oenflag=1;
//						else
//							usb_oenflag=0;
//						if(usb_oenflag)	
//						{
//							res=f_mount(0,&fs);
//							Host_DelayMS(20);
//							
//						}
				}break;
				case KEY_Disp:
//					if(BlankP++>IHzPnt)
//					 BlankP=0;
//					TSetInput = RESET;
//					MainFDSP = MainsetMu;
//					Disp_Main_set();
	          //Disp_R();
				break;
				case KEY_Setup:
					SetSystemStatus(SYS_STATUS_SYSSET);
					MainFDSP = SYSsetMu;
					lcd_Clear(LCD_COLOR_TEST_BACK);
					Use_SysSetProcess();
				break;
//				case KEY_UP:
//					if(TSetInput ==SET ) //è?¨?¤o??ˉè?“?…￥
//					{
//						Setvalue_Add();
//						DisBlank_main(BlankP,0);
//					}else{
//						BlankP --;
//						if(BlankP>IHzPnt)
//						 BlankP=2;
//						TSetInput = RESET;
//						MainFDSP = MainsetMu;
//						Disp_Main_set();
//					}
//					break;
//        case KEY_Down:
//					if(TSetInput ==SET ) //è?¨?¤o??ˉè?“?…￥
//					{
//						Setvalue_Reduction();//
//					    DisBlank_main(BlankP,0);
//					}else{
//						if(BlankP++>URangPnt)
//						 BlankP=0;
//						TSetInput = RESET;
//						MainFDSP = MainsetMu;
//						Disp_Main_set();
//					}
//					break;
        case KEY_Left:
					if(datapage == 1)
						datapage = 0;
					Disp_Main_set();
				break;
				case KEY_Right:
				if(datapage == 0)
					datapage = 1;
				Disp_Main_set();
				break;
//					if(TSetInput ==SET ) //è?¨?¤o??ˉè?“?…￥
//					{
//						CursorP--;
//						if(CursorP < minP||CursorP > maxP) //?…‰????§???¨
//						{
//							CursorP = maxP;
//							KInputF = maxP-1;//è?“?…￥??“?-??ˉ1?o”						
//						}
//            else if(CursorP < dotP)
//							KInputF = CursorP-2;

//						else 
//							KInputF = CursorP-1;//??“??2è?“?…￥??°??????é??
// 
//						DisBlank_main(BlankP,KEY_Left);				
//				}
//					break;
//				case KEY_Right:
//				if(TSetInput ==SET ) //è?¨?¤o??ˉè?“?…￥
//				{
//						CursorP++;
//						//è|???¤?–-?°???°??1??????--
//						//--
//					  if(CursorP < minP||CursorP > maxP) //?…‰????§???¨
//						{
//							CursorP = minP;		
//							KInputF = minP-2;//è?“?…￥??“?-??ˉ1?o”				
//						}
//						else if(CursorP < dotP)
//							KInputF = CursorP-2;

//						else 
//							KInputF = CursorP-1;//??“??2è?“?…￥??°??????é??
//						DisBlank_main(BlankP,KEY_Left);

//				}
//					break;
//				case KEY_Enter:
//					if(TSetInput ==0 ) //è?¨?¤o??ˉè?“?…￥
//					{
//						USE_SETSW();
//						if(CursorP < minP||CursorP > maxP) //?…‰????§???¨
//						{
//							CursorP = minP;		
//							KInputF = minP-2;//è?“?…￥??“?-??ˉ1?o”				
//						}
//						else if(CursorP < dotP)
//							KInputF = CursorP-2;

//						else 
//							KInputF = CursorP-1;//??“??2è?“?…￥??°??????é??
//						DisBlank_main(BlankP,KEY_Left);
//					}else{
//						TSetInput = 0;
//						Disp_Main_set();
//						Savetoeeprom();
//					}
//					break;
				default:
				break;
			}
				Delay_Key();
		}
	}
   // Savetoeeprom();
}

extern void DisBlank_set(unsigned char blank,uint8_t mode);

//ϵͳ����
void Use_SysSetProcess(void)
{
	//uint32_t  passwordnum=123769;
	uint32_t keynum=0;
	uint8_t key;	//,i=5
//	uint8_t Disp_flag=1;
	u8 maxP=Nub5cur;
	u8 minP=Nub1cur;
	u8 dotP=Nub3cur;
	BlankP = 0;

//	Button_Page.index=0;
//	Button_Page.page=0;
	TSetInput = RESET;
  lcd_Clear(LCD_COLOR_TEST_BACK);
	//Disp_Sys_Item();
	Disp_Sys_set();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_SYSSET)
	{
		key=HW_KeyScsn();
		flashSetFlags(BlankP);
		 if(MainFDSP== SYSsetMu)  //?|??????ˉè????????é?￠
					{
						switch(BlankP)
						{
//						case AddressPnt:
//							minP = Nub1cur;
//							maxP = Nub3cur;
//							dotP = Nub4cur;
//							break;
						case ILimitPnt:
							dotP = Nub3cur;
							maxP=Nub5cur;
							minP=Nub1cur;
							break;
						case PLimitPnt:
							dotP = Nub5cur;
						    maxP=Nub5cur;
							minP=Nub1cur;
							break;
						default:
							maxP=Nub5cur;
							break;
						}
					}
		if(key==0xff)
			keynum=0;

		else
			keynum++;
		if(keynum==9)
		{
			if(Para_Set[BeeperPnt].val!=1)
			BUZZER();
	//		Correc_successflag=0;
			switch(key)
			{
				case KEY_Mid:
				{
					sprintf((char *)bmpname,"0:%0.6d.bmp",bmpnum);
					Screen_shot(0,0,480,272,(const char *)bmpname);
					bmpnum++;
				}break;
				case KEY_Disp:
					Savetoeeprom();
					lcd_Clear(LCD_COLOR_TEST_BACK);
					SetSystemStatus(SYS_STATUS_MAIN);
					Use_MainProcess();
				    MainFDSP = MainsetMu;
					
			//  	Disp_R();
				break;
				case KEY_Setup:
//					 if(BlankP++>ILimitPnt)
//					 BlankP=0;
//					 TSetInput = RESET; 

//					 Disp_Sys_set();
					 break;
				case KEY_File:

				break;
				case KEY_Left:
					if(TSetInput ==SET ) //è?¨?¤o??ˉè?“?…￥
					{
						CursorP--;
						if(CursorP < minP||CursorP > maxP) //?…‰????§???¨
						{
							CursorP = maxP;
							if(BlankP==2)//set adr
								KInputF = maxP-2;//è?“?…￥??“?-??ˉ1?o”		
							else
								KInputF = maxP-1;
						}
						else if(CursorP < dotP)
							KInputF = CursorP-2;//2

						else
							KInputF = CursorP-1;//??“??2è?“?…￥??°??????é??
						DisBlank_set(BlankP,KEY_Left);				
					}else{
//						if(BlankP>7)
//						{
//							BlankP -= 8;
//						}
//						Disp_Sys_set();
					}
				break;
				case KEY_Right:
					if(TSetInput ==SET ) //è?¨?¤o??ˉè?“?…￥
					{
							CursorP++;						//è|???¤?–-?°???°??1??????--
						  if(CursorP < minP||CursorP > maxP) //?…‰????§???¨
							{
								CursorP = minP;		
								KInputF = minP-2;//è?“?…￥??“?-??ˉ1?o”				
							}
							else if(CursorP < dotP)
								KInputF = CursorP-2;

							else 
								KInputF = CursorP-1;//??“??2è?“?…￥??°??????é??
							DisBlank_set(BlankP,KEY_Right);
					}else{
//						if(BlankP<8)
//						{
//							BlankP += 8;
//						}
//						Disp_Sys_set();
					}
					break;
				case KEY_Down:
					if(TSetInput == SET)
					{
						Setvalue_Reduction();//
						DisBlank_set(BlankP,0);
//						if(BlankP == Wh)
//						{
//							if(Para_Set[Wh].val == 0)
//							{
//								Send_Uart3(6);
//							}else{
//								Send_Uart3(7);
//							}
//						}
					}else{
						
						if(BlankP++>ILimitPnt)
						 BlankP=0;
						 TSetInput = RESET; 
	
						 Disp_Sys_set();
					}
					
					
				break;
				case KEY_UP:
					if(TSetInput == SET)
					{
						Setvalue_Add();//
						DisBlank_set(BlankP,0);
//						if(BlankP == Wh)
//						{
//							if(Para_Set[Wh].val == 0)
//							{
//								Send_Uart3(6);
//							}else{
//								Send_Uart3(7);
//							}
//						}
					}else{
						
						if(BlankP>0)
							BlankP --;
						else
							BlankP = 5;
						 TSetInput = RESET; 

						 Disp_Sys_set();
					}
					
				break;
				case KEY_Enter:
					if(TSetInput == 0) //è?¨?¤o??ˉè?“?…￥
					{
						USE_SETSW();
						if(CursorP < minP||CursorP > maxP) //?…‰????§???¨
							{
								CursorP = minP;		
								KInputF = minP-2;//è?“?…￥??“?-??ˉ1?o”				
							}
							else if(CursorP < dotP)							KInputF = CursorP-2;

							else 							KInputF = CursorP-1;//??“??2è?“?…￥??°??????é??
					  DisBlank_set(BlankP,0);
					}else{
						TSetInput = 0;
						Disp_Sys_set();
						Savetoeeprom();
					}
				default:
				break;
			}
		}
	}
    //Savetoeeprom();
}

void flashSetFlags(u8 blank)
{
       u8 i;
	for(i=0;i<ParaNUM;i++) //
		{
			switch(blank)
			{
//				case AddressPnt:
//			  	DIS = DisADDInputNum;
//					TDKS =TTADDnputNum ;			//æ˜¾ç¤ºç¼“å†²
//					break;
				case PLimitPnt:
					DIS = DisULInputNum;
					TDKS =TTULnputNum;			//æ˜¾ç¤ºç¼“å†²
					break;
				case ILimitPnt:
					DIS = DisILInputNum;
					TDKS =TTILnputNum;			//æ˜¾ç¤ºç¼“å†²
					break;
				default:
					break;
			}
			if(i==blank)        // é€‰ä¸­é¡¹åˆ·æ–°
				Para_Set[i].flag = 1;
			else
				Para_Set[i].flag = 0;    //å…¶ä»–é¡¹å…³é—­
		}
}
void flashMainFlags(u8 blank)
{
	uint8_t i;
	for(i=0; i<=IHzPnt; i++) //
	{
		switch(blank)
		{
			case PFPnt:
				DIS = DisPFInputNum; 
				TDKS =TTPFInputNum ;			//æ˜¾ç¤ºç¼“å†²
				break;
			case VAPnt:
				DIS = DisVAInputNum; 
				TDKS =TTVAInputNum ;			//æ˜¾ç¤ºç¼“å†²
				break;
			case VARPnt:
				DIS = DisVARInputNum; 
				TDKS =TTVARInputNum ;			//æ˜¾ç¤ºç¼“å†²
				break;
			case IHzPnt:
				DIS = DisIHzInputNum; 
				TDKS =TTIHzInputNum ;			//æ˜¾ç¤ºç¼“å†²
				break;
			case VHzPnt:
				DIS = DisVHzInputNum; 
				TDKS =TTVHzInputNum ;			//æ˜¾ç¤ºç¼“å†²
				break;
			default:
				break;	
		}
		if(i==blank)        // é€‰ä¸­é¡¹åˆ·æ–°
			Para_main[i].flag = 1;
		else
			Para_main[i].flag = 0;     //å…¶ä»–é¡¹å…³é—­
	}
}

void DSP_GetNum(void)
{
	if(MainFDSP== MainsetMu)
	{
		switch(BlankP)
		{
			case PFPnt:
				DIS = DisPFInputNum; 
				TDKS =TTPFInputNum;
				break;
			case VAPnt:
				DIS = DisVAInputNum; 
				TDKS =TTVAInputNum;
				break;
			case FPnt:
				DIS = DisFInputNum; 
				TDKS =TTFInputNum;
				break;
			case VARPnt:
				DIS = DisVARInputNum; 
				TDKS =TTVAInputNum;
				break;
			case VHzPnt:
				DIS = DisVHzInputNum; 
				TDKS =TTVHzInputNum;
				break;
			case IHzPnt:
				DIS = DisIHzInputNum; 
				TDKS =TTIHzInputNum;
				break;
			default:
				break;
		}
	}
	else if(MainFDSP== SYSsetMu)  //
	{
		switch(BlankP)
		{
//			case AddressPnt:
//				DIS = DisADDInputNum; 
//				TDKS =TTADDnputNum;
//				break;
			case PLimitPnt:
				DIS = DisULInputNum; 
				TDKS =TTULnputNum;
				break;
			case ILimitPnt:
				DIS = DisILInputNum;
				TDKS =TTILnputNum;
				break;
			default:
				break;
		}		
	}
}
/*
uint32_t DTempToNum( u8  a )
{
	static uint32_t temp;
	static uint32_t Stemp;
//	static char *DIS;//显示缓冲

	if(a==3)//例如 121.23
	{
		Stemp = DInputNum[ 0 ];
		temp = Stemp*10000;
		Stemp = DInputNum[ 1 ];
		temp  += Stemp*1000;

		Stemp = DInputNum[ 2 ];
		temp  +=Stemp*100;
		Stemp = DInputNum[ 4 ];
		temp  +=Stemp*10;
		Stemp = DInputNum[ 5 ];
		temp  +=Stemp;

		if(DIS[4]==' ')	DIS[4]='0';//显示同步  补0

		if(DIS[5]==' ')	DIS[5]='0';
	}
	if(a==2)//例如 12.123
	{			
		Stemp = DInputNum[ 0 ];
		temp = Stemp*10000;
		Stemp = DInputNum[ 1 ];
		temp  += Stemp*1000;

		Stemp = DInputNum[ 3 ];
		temp  +=Stemp*100;
		Stemp = DInputNum[ 4 ];
		temp  +=Stemp*10;
		Stemp = DInputNum[ 5 ];
		temp  +=Stemp;

			//设置电流需要判断数组 更换数组
		if(DIS[3]==' ')			DIS[3]='0' ; //显示同步
		if(DIS[4]==' ')			DIS[4]='0';
		if(DIS[5]==' ')			DIS[5]='0';
	}
	else if(a==1)//例如 1.223
	{				
		Stemp = DInputNum[ 0 ];
		temp = Stemp*1000;
		Stemp = DInputNum[ 2 ];
		temp  += Stemp*100;

		Stemp = DInputNum[ 3 ];
		temp  +=Stemp*10;
		Stemp = DInputNum[ 4 ];
		temp  +=Stemp;

		//设置电流需要判断数组 更换数组
		DIS[5]=DIS[4];//显示同步
		DIS[4]=DIS[3];
		DIS[3]=DIS[2];
		DIS[2]=DIS[1];
		DIS[1]=DIS[0];
		DIS[0]='0';
		if(DIS[3]==' ')			DIS[3]='0' ; //显示同步
		if(DIS[4]==' ')			DIS[4]='0';
		if(DIS[5]==' ')			DIS[5]='0';
	}
	else if(a==0)//例如 .223
	{					
		Stemp = DInputNum[ 1 ];
		temp = Stemp*100;
		Stemp = DInputNum[ 2 ];
		temp  += Stemp*10;						
		Stemp = DInputNum[ 3 ];
		temp  +=Stemp;	
		
		//设置电流需要判断数组 更换数组
		DIS[5]=DIS[3];//显示同步
		DIS[4]=DIS[2];
		DIS[3]=DIS[1];
		DIS[2]=DIS[0];
		DIS[0]=DIS[1]='0';

		if(DIS[3]==' ')			DIS[3]='0'; //显示同步
		if(DIS[4]==' ')			DIS[4]='0';
		if(DIS[5]==' ')			DIS[5]='0';

	}
	else if(a==250)//?? 223   ???????
	{					
		Stemp = DInputNum[ 0 ];
		temp = Stemp*100;
		Stemp = DInputNum[ 1 ];
		temp  += Stemp*10;						
		Stemp = DInputNum[ 2 ];
		temp  +=Stemp;
    DIS[5]=DIS[4]=DIS[3]=' ';
	}
	else if(a==251)//
	{					
		Stemp = DInputNum[ 0 ];
		temp  +=Stemp*10000;
		Stemp = DInputNum[ 2 ];
		temp = Stemp*1000;
		Stemp = DInputNum[ 3 ];
		temp  += Stemp*100;

		Stemp = DInputNum[ 4 ];
		temp  +=Stemp*10;
		Stemp = DInputNum[ 5 ];
		temp  +=Stemp;		
		if(DIS[0]==' ')			DIS[0]='0'; 
		if(DIS[4]==' ')			DIS[4]='0';
		if(DIS[5]==' ')			DIS[5]='0';
	}
	else//无小数点
	{
		if(KInputF ==1)
		{
			Stemp = DInputNum[ 0 ];
			temp = Stemp*1000;

			DIS[1]=DIS[0]='0';
			//DIS[0]; //为了显示同步
			DIS[2]='.';
			DIS[5]=DIS[4]=DIS[3]='0';
		}
		if(KInputF ==2)
		{
			Stemp = DInputNum[ 0 ];
			temp = Stemp*10000;
			Stemp = DInputNum[ 1 ];
			temp  += Stemp*1000;	

			DIS[2]='.';//显示同步
			DIS[5]=DIS[4]=DIS[3]='0';
		}
		if(KInputF >=3)//无效输入
			temp  =  MAX_PW + 10;//无效值
	}
	if( DIS[0]==' '&&DIS[1]==' '&&DIS[3]==' '&&DIS[4]==' '&&DIS[5]==' ')// 全为空输入无效
		temp = MAX_PW +10; //无效值

	return temp;
}*/
//����

/***************************************************************************************/
void ParaReduct(void)
{
	if(CursorP == Nub1cur)
	{
		Flag_WANG=1;Flag_QIAN =Flag_BAI =Flag_SHI =Flag_GE =0;
	}
	else if(CursorP == Nub2cur)
	{
		Flag_QIAN =1;Flag_BAI =Flag_SHI =Flag_GE =Flag_WANG=0;
	}
	else if(CursorP == Nub3cur)
	{
		Flag_BAI =1;Flag_QIAN =Flag_SHI =Flag_GE =Flag_WANG=0;
	}
	else if(CursorP == Nub4cur)
	{
		Flag_SHI =1;Flag_QIAN =Flag_BAI =Flag_GE =Flag_WANG=0;
	}
	else if(CursorP == Nub5cur)
	{
		Flag_GE =1;Flag_QIAN =Flag_BAI =Flag_SHI =Flag_WANG=0;
	}
	if(MainFDSP== MainsetMu)
    {
		if(Para_main[BlankP].flag == 1)
		{
			switch(BlankP)
			{
				case  PFPnt:
			//		PF_val.sum=DTempToNum( 251 );//??????????
					if(Flag_GE==1)						PF_val.sum--;
					else if(Flag_SHI==1)			PF_val.sum-=10;
					else if(Flag_BAI==1)			PF_val.sum-=100;
					else if(Flag_QIAN==1)			PF_val.sum-=1000;
					else if(Flag_WANG==1)			PF_val.sum-=10000;

				if(PF_val.sum>Para_main[BlankP].max)						PF_val.sum=0;//�����ֵ����5000���ε�����Ч
					break;
				case  VAPnt:
		//			VA_val.sum=DTempToNum( 251 );//??????????
					if(Flag_GE==1)						VA_val.sum--;
					else if(Flag_SHI==1)			VA_val.sum-=10;
					else if(Flag_BAI==1)			VA_val.sum-=100;
					else if(Flag_QIAN==1)			VA_val.sum-=1000;
					else if(Flag_WANG==1)			VA_val.sum-=10000;

				if(VA_val.sum>Para_main[BlankP].max)						VA_val.sum=0;//�����ֵ����5000���ε�����Ч
					break;	
				case  VARPnt:
		//			VAR_val.sum=DTempToNum( 251 );//??????????
					if(Flag_GE==1)						VAR_val.sum--;
					else if(Flag_SHI==1)			VAR_val.sum-=10;
					else if(Flag_BAI==1)			VAR_val.sum-=100;
					else if(Flag_QIAN==1)			VAR_val.sum-=1000;
					else if(Flag_WANG==1)			VAR_val.sum-=10000;

				if(VAR_val.sum>Para_main[BlankP].max)							VAR_val.sum=0;//�����ֵ����5000���ε�����Ч
					break;	
				case  FPnt:
		//			HZ_val.sum=DTempToNum( 2 );//??????????
					if(Flag_GE==1)						HZ_val.sum--;
					else if(Flag_SHI==1)			HZ_val.sum-=10;
					else if(Flag_BAI==1)			HZ_val.sum-=100;
					else if(Flag_QIAN==1)			HZ_val.sum-=1000;
					else if(Flag_WANG==1)			HZ_val.sum-=10000;

				if(HZ_val.sum>Para_main[BlankP].max)							HZ_val.sum=0;//�����ֵ����5000���ε�����Ч
					break;
				case  VHzPnt:
			//		VHz_val.sum=DTempToNum( 2 );//??????????
					if(Flag_GE==1)						VHz_val.sum--;
					else if(Flag_SHI==1)			VHz_val.sum-=10;
					else if(Flag_BAI==1)			VHz_val.sum-=100;
					else if(Flag_QIAN==1)			VHz_val.sum-=1000;
					else if(Flag_WANG==1)			VHz_val.sum-=10000;

				if(VHz_val.sum>Para_main[BlankP].max)							VHz_val.sum=0;//�����ֵ����5000���ε�����Ч
					break;
				case  IHzPnt:
		//			IHz_val.sum=DTempToNum( 2 );//??????????
					if(Flag_GE==1)						IHz_val.sum--;
					else if(Flag_SHI==1)			IHz_val.sum-=10;
					else if(Flag_BAI==1)			IHz_val.sum-=100;
					else if(Flag_QIAN==1)			IHz_val.sum-=1000;
					else if(Flag_WANG==1)			IHz_val.sum-=10000;

				if(IHz_val.sum>Para_main[BlankP].max)							IHz_val.sum=0;//�����ֵ����5000���ε�����Ч
					break;
				default:
					if(Flag_GE==1)
					{
						Para_main[BlankP].val--;
						if(Para_main[BlankP].val>Para_main[BlankP].max)
							Para_main[BlankP].val=Para_main[BlankP].max;
					}
					break;
			}
		}
   }
	else if(MainFDSP== SYSsetMu)  //???????,??????
   {
		if(Para_Set[BlankP].flag == 1)
		{
			switch(BlankP)
			{
//				case AddressPnt:
//				//	AddressVal=DTempToNum( 250 );//??????????;;	
//					if(Flag_BAI==1)
//					
//						AddressVal--;
//					//	if(AddressVal>MAX_ADD)							AddressVal=0;
//					
//					else if(Flag_QIAN==1)
//					
//						AddressVal-=10;
//					//	if(AddressVal>MAX_ADD)							AddressVal=0;
//					
//					else if(Flag_WANG==1)
//					
//						AddressVal-=100;
//						if(AddressVal>MAX_ADD)							AddressVal=0;
//					
//					break;
				case PLimitPnt:
			//		VoltageLimit=DTempToNum( 2 );//??????????
					if(Flag_GE==1)						POWLimit--;
					else if(Flag_SHI==1)			POWLimit-=10;
					else if(Flag_BAI==1)			POWLimit-=100;
					else if(Flag_QIAN==1)			POWLimit-=1000;
					else if(Flag_WANG==1)			POWLimit-=10000;

				if(POWLimit>MAX_PW)					POWLimit=0;//�����ֵ����5000���ε�����Ч
					break;
				case ILimitPnt:
				//	CurrentLimit=DTempToNum(251);//??????????
					if(Flag_GE==1)						CurrentLimit--;
					else if(Flag_SHI==1)			CurrentLimit-=10;
					else if(Flag_BAI==1)			CurrentLimit-=100;
					else if(Flag_QIAN==1)			CurrentLimit-=1000;
					else if(Flag_WANG==1)			CurrentLimit-=10000;

				if(CurrentLimit>MAX_CUR)		CurrentLimit=0;//�����ֵ����5000���ε�����Ч
					break;
				default:
					if(Flag_GE==1)
					{
						Para_Set[BlankP].val--;
						if(Para_Set[BlankP].val>Para_Set[BlankP].max)    //�������ֵ
							Para_Set[BlankP].val=Para_Set[BlankP].max;

						if(BlankP==LanguagePnt)	
             lcd_Clear(LCD_COLOR_TEST_BACK);//�����л�������								
					}
					break;
			}
		}
	}
}
/*
void DInput_GetNum1(void)
{
	uint32_t temp;
//	static uint32_t ttst;
	char str[10]={0};
   if(MainFDSP== MainsetMu)  //???????,??????
  {
  		if(Para_main[BlankP].flag == 1)
		{
			switch(BlankP)
			{
			   case PFPnt:
			   	    temp = PF_val.sum;
					sprintf(str,"%02d.%03d",temp/1000,temp%1000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisPFInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = '.';
					DInputNum[ 2 ]  = DIS[2]- 0x30;
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				case VAPnt:
					temp = VA_val.sum;
					sprintf(str,"%02d.%03d",temp/1000,temp%1000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisPFInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = '.';
					DInputNum[ 2 ]  = DIS[2]- 0x30;
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				case FPnt:
					temp = HZ_val.sum;
					sprintf(str,"%02d.%03d",temp/1000,temp%1000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisPFInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = DIS[1]- 0x30;
					DInputNum[ 2 ]  = '.';
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				case VARPnt:
					temp = VAR_val.sum;
					sprintf(str,"%02d.%03d",temp/1000,temp%1000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisPFInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = '.';
					DInputNum[ 2 ]  = DIS[2]- 0x30;
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				case VHzPnt:
					temp = VHz_val.sum;
					sprintf(str,"%02d.%03d",temp/1000,temp%1000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisPFInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = DIS[1]- 0x30;
					DInputNum[ 2 ]  = '.';
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				case IHzPnt:
					temp = VHz_val.sum;
					sprintf(str,"%02d.%03d",temp/1000,temp%1000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisPFInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = DIS[1]- 0x30;
					DInputNum[ 2 ]  = '.';
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				default:
					temp = Para_main[BlankP].val;
					break;
			}
		}
  }
   else if(MainFDSP== SYSsetMu)  //???????,??????
  {
	  if(Para_Set[BlankP].flag == 1)
		{
			switch(BlankP)
			{
				case AddressPnt:
					temp = AddressVal;
					sprintf(str,"%03d",temp);
					strncpy(DIS,str,3);
					strncpy(TDKS,DIS,3);
					strncpy(DInputNum,DIS,3);
					strncpy(DisADDInputNum,DInputNum,3);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = DIS[1]- 0x30;
					DInputNum[ 2 ]  = DIS[2]- 0x30;
					break;
				case PLimitPnt:
					temp = POWLimit;
					sprintf(str,"%02d.%03d",temp/1000,temp%1000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisULInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = DIS[1]- 0x30;
					DInputNum[ 2 ]  = '.';
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				case ILimitPnt:
					temp = CurrentLimit;
					sprintf(str,"%01d.%04d",temp/10000,temp%10000);
					strncpy(DIS,str,6);
					strncpy(TDKS,DIS,6);
					strncpy(DInputNum,DIS,6);
					strncpy(DisILInputNum,DInputNum,6);
					DInputNum[ 0 ]  = DIS[0] - 0x30;
					DInputNum[ 1 ]  = '.';
					DInputNum[ 2 ]  = DIS[2]- 0x30;
					DInputNum[ 3 ]  = DIS[3]- 0x30;
					DInputNum[ 4 ]  = DIS[4]- 0x30;
					DInputNum[ 5 ]  = DIS[5]- 0x30;
					break;
				default:
					temp = Para_Set[BlankP].val;
					break;
			}
			//Wrtite_SET_File(BlankP);
		}
	 }
}*/
void Setvalue_Reduction(void)//
{
	if( TSetInput != SET)  //????
	  return;
	//DSP_GetNum();
	ParaReduct();
	//DInput_GetNum();
}
void ParaAdd(void)
{
/********************????********************************************/
	if(CursorP == Nub1cur)
	{
		Flag_WANG=1;
		Flag_GE =Flag_SHI =Flag_BAI =Flag_QIAN =0;
	}
	else if(CursorP == Nub2cur)
	{
		Flag_WANG=Flag_GE =Flag_SHI =Flag_BAI =0;
		Flag_QIAN =1;
	}
	else if(CursorP == Nub3cur)
	{
		Flag_WANG=Flag_GE =Flag_SHI =Flag_QIAN =0;
		Flag_BAI =1;
	}
	else if(CursorP == Nub4cur)
	{
		Flag_WANG=Flag_GE =Flag_BAI =Flag_QIAN =0;
		Flag_SHI =1;
	}
	else if(CursorP == Nub5cur)
	{
		Flag_WANG=Flag_SHI =Flag_BAI =Flag_QIAN =0;
		Flag_GE =1;
	}
	if(MainFDSP== MainsetMu)
    {
		if(Para_main[BlankP].flag == 1)
		{
			switch(BlankP)
			{
				case  PFPnt:
				//	PF_val.sum=DTempToNum( 251 );
					if(Flag_GE==1)						PF_val.sum++;

					else if(Flag_SHI==1)			PF_val.sum+=10;

					else if(Flag_BAI==1)			PF_val.sum+=100;

					else if(Flag_QIAN==1)			PF_val.sum+=1000;

					else if(Flag_WANG==1)			PF_val.sum+=10000;

				if(PF_val.sum>Para_main[BlankP].max)		PF_val.sum=Para_main[BlankP].max;//�����ֵ����5000���ε�����Ч
					break;
				case  VAPnt:
				//	VA_val.sum=DTempToNum( 251 );
					if(Flag_GE==1)						VA_val.sum++;

					else if(Flag_SHI==1)			VA_val.sum+=10;

					else if(Flag_BAI==1)			VA_val.sum+=100;

					else if(Flag_QIAN==1)			VA_val.sum+=1000;

					else if(Flag_WANG==1)			VA_val.sum+=10000;

				if(VA_val.sum>Para_main[BlankP].max)							VA_val.sum=Para_main[BlankP].max;//�����ֵ����5000���ε�����Ч
					break;	
				case  VARPnt:
				//	VAR_val.sum=DTempToNum( 251 );//
					if(Flag_GE==1)						VAR_val.sum++;

					else if(Flag_SHI==1)			VAR_val.sum+=10;

					else if(Flag_BAI==1)			VAR_val.sum+=100;

					else if(Flag_QIAN==1)			VAR_val.sum+=1000;

					else if(Flag_WANG==1)			VAR_val.sum+=10000;

				if(VAR_val.sum>Para_main[BlankP].max)							VAR_val.sum=Para_main[BlankP].max;//�����ֵ����5000���ε�����Ч
					break;	
				case  FPnt:
				//	HZ_val.sum=DTempToNum( 2 );//
					if(Flag_GE==1)						HZ_val.sum++;

					else if(Flag_SHI==1)			HZ_val.sum+=10;

					else if(Flag_BAI==1)			HZ_val.sum+=100;

					else if(Flag_QIAN==1)			HZ_val.sum+=1000;

					else if(Flag_WANG==1)			HZ_val.sum+=10000;

				if(HZ_val.sum>Para_main[BlankP].max)							HZ_val.sum=Para_main[BlankP].max;//�����ֵ����5000���ε�����Ч
					break;
				case  VHzPnt:
				//	VHz_val.sum=DTempToNum( 2 );//
					if(Flag_GE==1)						VHz_val.sum++;

					else if(Flag_SHI==1)			VHz_val.sum+=10;

					else if(Flag_BAI==1)			VHz_val.sum+=100;

					else if(Flag_QIAN==1)			VHz_val.sum+=1000;

					else if(Flag_WANG==1)			VHz_val.sum+=10000;

				if(VHz_val.sum>Para_main[BlankP].max)							VHz_val.sum=Para_main[BlankP].max;//�����ֵ����5000���ε�����Ч
					break;
				case  IHzPnt:
			//		IHz_val.sum=DTempToNum( 2 );//
					if(Flag_GE==1)						IHz_val.sum++;

					else if(Flag_SHI==1)			IHz_val.sum+=10;

					else if(Flag_BAI==1)			IHz_val.sum+=100;

					else if(Flag_QIAN==1)			IHz_val.sum+=1000;

					else if(Flag_WANG==1)			IHz_val.sum+=10000;

				if(IHz_val.sum>Para_main[BlankP].max)							IHz_val.sum=Para_main[BlankP].max;//�����ֵ����5000���ε�����Ч
					break;
				default:
					if(Flag_GE==1)
					{
						Para_main[BlankP].val++;
						if(Para_main[BlankP].val>Para_main[BlankP].max)
							Para_main[BlankP].val=0;
					}
					break;
			}
		}
   }
	else if(MainFDSP== SYSsetMu)
   {
		if(Para_Set[BlankP].flag == 1)
		{
			switch(BlankP)
			{
//				case AddressPnt:
//				//	AddressVal=DTempToNum( 250 );//??????????;;	
//					if(Flag_BAI==1)						AddressVal++;

//					else if(Flag_QIAN==1)			AddressVal+=10;

//				else if(Flag_WANG==1)			AddressVal+=100;

//				if(AddressVal>MAX_ADD)			AddressVal=MAX_ADD;
//				AddressVal=1;
//					break;
				case PLimitPnt:
				//	VoltageLimit=DTempToNum( 2 );//??????????
					if(Flag_GE==1)						POWLimit++;

					else if(Flag_SHI==1)			POWLimit+=10;

					else if(Flag_BAI==1)			POWLimit+=100;

					else if(Flag_QIAN==1)			POWLimit+=1000;

					else if(Flag_WANG==1)			POWLimit+=10000;

				if(POWLimit>MAX_PW)					POWLimit=MAX_PW;//�����ֵ����5000���ε�����Ч
					break;
				case ILimitPnt:
				//	CurrentLimit=DTempToNum(251);//??????????
					if(Flag_GE==1)						CurrentLimit++;

					else if(Flag_SHI==1)			CurrentLimit+=10;

					else if(Flag_BAI==1)			CurrentLimit+=100;

					else if(Flag_QIAN==1)			CurrentLimit+=1000;

					else if(Flag_WANG==1)			CurrentLimit+=10000;

				if(CurrentLimit>MAX_CUR)		CurrentLimit=MAX_CUR;//�����ֵ����5000���ε�����Ч
					break;
				default:
					if(Flag_GE==1)
					{
						Para_Set[BlankP].val++;
						if(Para_Set[BlankP].val>Para_Set[BlankP].max)
							Para_Set[BlankP].val=0;

            if(BlankP==LanguagePnt)	
             lcd_Clear(LCD_COLOR_TEST_BACK);//�����л�������							
					}
					break;
			}
		}
	}
}
void Setvalue_Add(void)//
{
	if( TSetInput != SET)  //����û��
	  return;
	//DSP_GetNum();
	ParaAdd();
	//DInput_GetNum();
}

void Disp_Main_set(void)
{
	u8 i;
	lcd_Clear(LCD_COLOR_TEST_BACK);
	GPIO_ClearValue(0,1<<12);//beep off
//	Colour.Fword=White;
//  Colour.black=LCD_COLOR_TEST_BACK;//0x202020;//Black;//LCD_COLOR_TURQUOISE;//

//	Disp_Box(1,25,478,268,3,Yellow);
	if(datapage == 0)
	{
		Colour.Fword=Red;
		Colour.black=Black;
		for(i=0;i<3;i++)
			WriteString_16(CH1X+i*CHMARGIN,CH1Y,CHNAME[i],0);
		Draw_LIN5(HLINEXS,HLINEY,HLINEXE,Yellow);
		Draw_LIN5(HLINEXS,HLINEY+MARGINVER,HLINEXE,Green);
		Draw_LIN5(HLINEXS,HLINEY+MARGINVER*2,HLINEXE,PCOLOR);
		Draw_LIN5(HLINEXS,HLINEY+MARGINVER*3,HLINEXE,LCD_COLOR_MAGENTA);
		Draw_LIN5(HLINEXS,HLINEY+MARGINVER*4,HLINEXE,FCOLOR);
		Draw_LIN3_Y(MARGINHOR,HLINEY,272-HLINEY,Yellow);
		Draw_LIN3_Y(MARGINHOR*2,HLINEY,272-HLINEY,Yellow);
	}else{
		Colour.Fword=Red;
		WriteString_16(SUBDATA1X+4*18,SUBDATA1Y-20,CHNAME[0],0);
		WriteString_16(SUBDATA1X+SUBDATAXOFFSET+4*18,SUBDATA1Y-20,CHNAME[1],0);
		Colour.Fword=White;
		for(i=0;i<3;i++)
		{
			WriteString_16(SUBNAMEX,SUBNAMEY+SUBNAMEOFFSET*i,
			SubDataTab[flag_SetLang][i],0);
		}
	}
//	Draw_LIN5(3,123,150-MENUOFFSETX,Yellow);
//	LCD_DrawLine(120,55,478,55,Yellow);
	Colour.Fword=Black;
  Colour.black=Yellow;
//	for(i=0;i<2;i++)
//	{
//		Colour.Fword=White;
		
		if(flag_SetLang==0)			
		{
			if(datapage == 0)
			{
				Colour.black=Yellow;
				LCD_DrawRect(0,4,52,4+16,Yellow);
			}else{
				Colour.black=LCD_COLOR_DARKGREY;
				LCD_DrawRect(0,4,52,4+16,LCD_COLOR_DARKGREY);
			}
			WriteString_16(0,4,DataTab[0],0);
			
			if(datapage == 1)
			{
				Colour.black=Yellow;
				LCD_DrawRect(0+18*3,4,18*3+52,4+16,Yellow);
			}else{
				Colour.black=LCD_COLOR_DARKGREY;
				LCD_DrawRect(0+18*3,4,18*3+52,4+16,LCD_COLOR_DARKGREY);
			}
			WriteString_16(0+18*3,4,DataTab[1],0);
		}else{  
			if(datapage == 0)
			{
				Colour.black=Yellow;
				LCD_DrawRect(0,4,52,4+16,Yellow);
			}else{
				Colour.black=LCD_COLOR_DARKGREY;
				LCD_DrawRect(0,4,52,4+16,LCD_COLOR_DARKGREY);
			}
			WriteString_16(8,4,DataTabE[0],0);
			
			if(datapage == 1)
			{
				Colour.black=Yellow;
				LCD_DrawRect(0+18*3,4,18*3+52,4+16,Yellow);
			}else{
				Colour.black=LCD_COLOR_DARKGREY;
				LCD_DrawRect(0+18*3,4,18*3+52,4+16,LCD_COLOR_DARKGREY);
			}
			WriteString_16(8+18*3,4,DataTabE[1],0);
		}
//	}
//	if(BlankP==ModePnt)
//	{
//		Colour.Fword=Red;
//		Colour.black=Blue;
//		WriteString_16(Para_main[0].row+63, Para_main[0].col, (char *)Rms[Para_main[0].val],0);//Rms
//		Colour.Fword=White;
//		Colour.black=LCD_COLOR_TEST_BACK;
//		WriteString_16(Para_main[1].row+63, Para_main[1].col, (char *)RNG_V[Para_main[1].val],0);//V-Auto
//		WriteString_16(Para_main[2].row+63, Para_main[2].col, (char *)RNG_I[Para_main[2].val],0);//A-Auto
//			
//	}else if(BlankP==URangPnt){
//		Colour.Fword=Red;
//		Colour.black=Blue;
//		WriteString_16(Para_main[1].row+63, Para_main[1].col, (char *)RNG_V[Para_main[1].val],0);//V-Auto
//		Colour.Fword=White;
//		Colour.black=LCD_COLOR_TEST_BACK;
//		WriteString_16(Para_main[0].row+63, Para_main[0].col, (char *)Rms[Para_main[0].val],0);//Rms		
//		WriteString_16(Para_main[2].row+63, Para_main[2].col, (char *)RNG_I[Para_main[2].val],0);//A-Auto
//	
//	}else if(BlankP==IRangPnt){
//		Colour.Fword=Red;
//		Colour.black=Blue;
//		WriteString_16(Para_main[2].row+63, Para_main[2].col, (char *)RNG_I[Para_main[2].val],0);//A-Auto
//		Colour.Fword=White;
//		Colour.black=LCD_COLOR_TEST_BACK;
//		WriteString_16(Para_main[0].row+63, Para_main[0].col, (char *)Rms[Para_main[0].val],0);//Rms
//		WriteString_16(Para_main[1].row+63, Para_main[1].col, (char *)RNG_V[Para_main[1].val],0);//V-Auto
//		
//	}
}
