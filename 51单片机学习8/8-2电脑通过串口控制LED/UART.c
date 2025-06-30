#include <REGX52.H>

/**
  * @brief ���ڳ�ʼ����4800bps@12.000MHz
  * @param ��
  * @retval ��
  */
void UART_Init()
{
	SCON=0x50;
	PCON |= 0x80;
	TMOD &= 0x0f;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xF3;		//�趨��ʱ��ֵ
	TH1 = 0xF3;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	EA=1;
	ES=1;
}


/**
  * @brief ���ڷ���һ���ֽ�����
  * @param Byte����Ҫ���͵�����
  * @retval ��
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/* �����жϺ���ģ��
void UATR_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
	
}
*/