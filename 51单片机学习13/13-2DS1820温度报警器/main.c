#include <REGX52.H>
#include "DS18B20.h"
#include "Delay.h"
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "I2C.h"
#include "Timer0.h"

float T;
char TLow,THigh;
unsigned char KeyNum,TShow;

void  main()
{
	THigh=AT24C02_ReadByte(0);
	TLow=AT24C02_ReadByte(1);
	if(THigh>125||TLow<-55||THigh<=TLow)
	{
		THigh=20;
		TLow=15;
	}
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);
	while(1)
	{
		KeyNum=Key();
		/*温度读取及显示*/
		DS18B20_ConvertT();
		T=DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			TShow=-T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			TShow=T;
		}
		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
		
		
		
		
		/*阈值判断及显示*/
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				THigh++;
				if(THigh>125){THigh=125;}
			}				
			if(KeyNum==2)
			{
				THigh--;
				if(THigh<=TLow){THigh++;}
			}		
			if(KeyNum==3)
			{
				TLow++;
				if(TLow>=THigh){TLow--;}
			}		
			if(KeyNum==4)
			{
				TLow--;
				if(TLow<-55){TLow=-55;}
			}
			LCD_ShowSignedNum(2,4,THigh,3);
			LCD_ShowSignedNum(2,12,TLow,3);
			AT24C02_WriteByte(0,THigh);
			Delay(5);
			AT24C02_WriteByte(1,TLow);
			Delay(5);
		}
		if(T>THigh)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if(T<TLow)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD_ShowString(1,13,"    ");
		}
		
	}
}

void Timer0_Routine()  interrupt 1
{
	static unsigned int T0Count;
	TH0=0xfc;
	TL0=0x18;
	T0Count++;
	if(T0Count>=20)
	{
		T0Count=0;
		Key_Loop();
	}
}