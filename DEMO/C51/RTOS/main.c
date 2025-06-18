#include "reg52.h"
#include "RTX51TNY.H"
#include "MyDemo.h"
sbit LED1 = P2^0;
sbit LED2 = P2^1;
void main0() _task_ 0
{
	Lcd1602_Display_Init();
	Lcd1602_Display_String(0,0,"hello world");	
	os_create_task(1);		//添加任务到列表	
	while(1)
	{
		LED1 = 0;
		os_wait(K_TMO,100,0);
		LED1 = 1;
		os_wait(K_TMO,100,0);
		os_switch_task();
	}
}

void main1() _task_ 1 
{
	
	while(1)
	{
		LED2 = 0;
		os_wait(K_TMO,100,0);
		LED2 = 1;
		os_wait(K_TMO,100,0);
		os_switch_task();		
	}
}