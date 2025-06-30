#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum,MODE,TimeSetSelect;

void TimeShow(void)
{
	DS1302_ReadTime();

	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
}

void TimeSet(void)
{
	if(KeyNum==2)
	{
		TimeSetSelect++;
		TimeSetSelect%=6;
	}
	if(KeyNum==3)
	{
		DS1302_Time[TimeSetSelect]++;
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||
			 DS1302_Time[1]==7||DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||
						DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}

	}
	if(KeyNum==4)
	{
		DS1302_Time[TimeSetSelect]--;
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||
			 DS1302_Time[1]==7||DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||
						DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}


	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
	LCD_ShowNum(2,10,TimeSetSelect,2);
}


void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0Init();
	DS1302_SetTime();

	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			if(MODE==0){MODE=1;}
			else if(MODE==1){MODE=0;DS1302_SetTime();}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}


	}
}

void Timer0_Routine()  interrupt 1
{
	static unsigned int T0Count;
	TH0=0xfc;
	TL0=0x18;
	T0Count++;
	if(T0Count>=5000)
	{
		T0Count=0;
	}
}