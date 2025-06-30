#include <REGX52.H>
#include "Delay.h"

sbit RCK=P3^5;		//RCLK
sbit SCK=P3^6;  	//SRCLK
sbit SER=P3^4;		//SER

#define MATRIX_LED_PORT   P0

/**
  * @brief 74H595д��һ���ֽ�
  * @param Ҫд����ֽ�
  * @retval ��
  */
void _74H595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
}

/**
  * @brief ��������ʼ��
  * @param ��
  * @retval ��
  */
void MatrixLED_Init()
{
		SCK=0;
		RCK=0;
}

/**
  * @brief LED��������ʾһ������
  * @param Column Ҫѡ����У���ΧΪ0��7��0�������
  * @param Date ѡ������ʾ�����ݣ���λ���ϣ�1Ϊ����0Ϊ��
  * @retval ��
  */
void MatrixLED_ShowColumn(unsigned char Column,Date)
{
	_74H595_WriteByte(Date);
	MATRIX_LED_PORT=~(0x80>>Column);
	Delay(1);
	MATRIX_LED_PORT=0xff;
}
