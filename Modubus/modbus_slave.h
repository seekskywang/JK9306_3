/*
*********************************************************************************************************
*
*	ģ������ : MODEBUS ͨ��ģ�� (��վ��
*	�ļ����� : modbus_slave.h
*	��    �� : V1.4
*	˵    �� : ͷ�ļ�
*
*
*********************************************************************************************************
*/

#ifndef __MODBUY_SLAVE_H
#define __MODBUY_SLAVE_H
#include "stdint.h"
#define SADDR485	1
#define SBAUD485	9600

/* 01H ��ǿ�Ƶ���Ȧ */
/* 05H дǿ�Ƶ���Ȧ */
#define REG_D01		0x0101
#define REG_D02		0x0102
#define REG_D03		0x0103
#define REG_D04		0x0104
#define REG_DXX 	REG_D04

/* 02H ��ȡ����״̬ */
#define REG_T01		0x0201
#define REG_T02		0x0202
#define REG_T03		0x0203
#define REG_TXX		REG_T03

/* 03H �����ּĴ��� */
/* 06H д���ּĴ��� */
/* 10H д�������Ĵ��� */
#define SLAVE_REG_P00		0x0000       //R_VOLU
#define SLAVE_REG_P01		0x0001      //Load_Voltage
#define SLAVE_REG_P02		0x0002      //Load_Current
#define SLAVE_REG_P03		0x0003		//Change_Voltage
#define SLAVE_REG_P04		0x0004		//Change_Current
#define SLAVE_REG_P05		0x0005		//Load_OCP
#define SLAVE_REG_P06		0x0006		//Change_OCP
#define SLAVE_REG_P07		0x0007		//Short_Time
#define SLAVE_REG_P08		0x0008		//Leak_Current
#define SLAVE_REG_P09		0x0009		//R1_Volu
#define SLAVE_REG_P10		0x000A		//R2_Volu
#define SLAVE_REG_P11		0x000B		//Temper
#define SLAVE_REG_P12		0x000C		//DHQ_Voltage
#define SLAVE_REG_P13		0x000D		//MODE
#define SLAVE_REG_P14		0x000E		//Load_Mode
#define SLAVE_REG_P15		0x000F		//Load_SET_Voltage
#define SLAVE_REG_P16		0x0010		//Load_SET_Current
#define SLAVE_REG_P17		0x0011		//Change_SET_Voltage
#define SLAVE_REG_P18		0x0012		//Change_SET_Current

/* 04H ��ȡ����Ĵ���(ģ���ź�) */
#define REG_A01		0x0401
#define REG_AXX		REG_A01


/* RTU Ӧ����� */
#define RSP_OK				0		/* �ɹ� */
#define RSP_ERR_CMD			0x01	/* ��֧�ֵĹ����� */
#define RSP_ERR_REG_ADDR	0x02	/* �Ĵ�����ַ���� */
#define RSP_ERR_VALUE		0x03	/* ����ֵ����� */
#define RSP_ERR_WRITE		0x04	/* д��ʧ�� */

#define S_RX_BUF_SIZE		30
#define S_TX_BUF_SIZE		128

struct MODS_T
{
	uint8_t RxBuf[S_RX_BUF_SIZE];
	uint8_t TxBuf[S_TX_BUF_SIZE];
	uint8_t RxCount;
	uint8_t RxStatus;
	uint8_t RxNewFlag;
	uint8_t RspCode;
	
	uint8_t TxCount;
};

struct VAR_Ta
{
	/* 03H 06H ��д���ּĴ��� */
	uint16_t P00;
	uint16_t P01;
	uint16_t P02;
	uint16_t P03;
	uint16_t P04;
	uint16_t P05;
	uint16_t P06;
	uint16_t P07;
	uint16_t P08;
	uint16_t P09;
	uint16_t P10;
	uint16_t P11;
	uint16_t P12;
	uint16_t P13;
	uint16_t P14;
	uint16_t P15;
	uint16_t P16;
	uint16_t P17;
	uint16_t P18;
	/* 04H ��ȡģ�����Ĵ��� */
	uint16_t A01;

	/* 01H 05H ��д����ǿ����Ȧ */
	uint16_t D01;
	uint16_t D02;
	uint16_t D03;
	uint16_t D04;

};
struct PRINT_MODS_T
{
	uint8_t Rxlen;
	char RxBuf[S_RX_BUF_SIZE];
	uint8_t Txlen;
	char TxBuf[S_TX_BUF_SIZE];
};
void MODS_Poll(void);
void MODS_ReciveNew(uint8_t _byte);



extern struct MODS_T g_tModS;
extern struct VAR_Ta g_tVar;
extern unsigned int  Tick_10ms;
extern uint16_t CRC16_Modbus(uint8_t *_pBuf, uint16_t _usLen);
#endif



