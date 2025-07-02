#include <REGX52.H>


sbit LED=P2^0;

void Delay(unsigned int t)
{
	while(t--);
}


void  main()
{
	unsigned char Time,t;
	while(1)
	{
		for(Time=0;Time<100;Time++)
		{
			for(t=0;t<20;t++)
			{
				LED=0;
				Delay(Time);
				LED=1;
				Delay(100-Time);
			}
		}
		for(Time=100;Time>0;Time--)
		{
			for(t=0;t<20;t++)
			{
				LED=0;
				Delay(Time);
				LED=1;
				Delay(100-Time);
			}
		}
	}
}