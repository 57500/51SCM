#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"


unsigned char Sec,Min,Hour;

void  main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	Timer0Init();
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);

	}
}

void Timer0_Routine()  interrupt 1
{
	static unsigned int T0Count;
	TH0=0xfc;
	TL0=0x18;
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		Sec++;
		if(Sec>=60)
		{
			Sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hour++;
				if(Hour>=24)
				{
					Hour=0;
				}
			}
		}
	}
}