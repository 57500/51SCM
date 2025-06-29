#include <REGX52.H>
#include"LCD1602.h"
#include"Delay.h"

int Result=0;

void main()
{
	LCD_Init();
//	LCD_ShowChar(1,1,'A');
//	LCD_ShowString(1,1,"Hello,World");
//	LCD_ShowNum(2,1,123,3);
//	LCD_ShowSignedNum(1,13,-66,2);
//	LCD_ShowHexNum(2,5,0xa8,2);
//	LCD_ShowBinNum(2,8,0xaa,8);
	
//	Result=1+1;
//	LCD_ShowNum(1,1,Result,3);
	
	while(1)
	{
		Result++;
		Delay(1000);
		LCD_ShowNum(1,1,Result,3);
	}
}
