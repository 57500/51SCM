#include "I2C.h"
#include <REGX52.H>


#define AT24C02_ADDRESS  0xa0

/**
  * @brief AT24C02д��һ���ֽ�
  * @param WordAddress Ҫд���ֽڵĵ�ַ��Date Ҫд����ֽ�
  * @retval ��
  */
void AT24C02_WriteByte(unsigned char WordAddress,Date)
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Date);
	I2C_ReceiveAck();
	I2C_Stop();
}

/**
  * @brief AT24C02 ��ȡһ���ֽ�
  * @param WordAddressҪ��ȡ�ֽڵĵ�ַ
  * @retval Date ����������
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Date;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	Date=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();	
	return Date;
}