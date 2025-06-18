#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "My_Demo.h"
#include <string.h>
volatile u16 PH0_Value_l = 20;
volatile u16 PH1_Value_l = 30;
volatile u16 PH2_Value_l = 40;

volatile u16 AD_Left = 0;
volatile u16 AD_Right = 0;
volatile u16 AD_Up = 0;
volatile u16 AD_Down = 0;
volatile u16 PH4_Value = 0;
#define MOTO_STEP 200
u32 MotoPoint=100;
unsigned char Motostatus=MotoStop_Demo;

u32 MotoPoint1=100;
unsigned char Motostatus1=MotoStop_Demo;
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //设置键
	{
		Menu_Count ++;

		if(Menu_Count >= 3)
		{
			OLED_ShowStr_ENCH_Demo(0,0 ,(unsigned char *)"左:000 右:000   ");
			OLED_ShowStr_ENCH_Demo(0,16,(unsigned char *)"上:000 下:000   ");
			OLED_ShowStr_ENCH_Demo(0,32,(unsigned char *)"雨滴:000        ");
			OLED_ShowStr_ENCH_Demo(0,48,(unsigned char *)"                ");			
			//处理返回界面
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				OLED_ShowStr_ENCH_Demo(0,0 ,(unsigned char *)"               ");	
				OLED_ShowStr_ENCH_Demo(0,16,(unsigned char *)"               ");	
				OLED_ShowStr_ENCH_Demo(0,32,(unsigned char *)"               ");	
				OLED_ShowStr_ENCH_Demo(0,48,(unsigned char *)"               ");				
				OLED_ShowStr_ENCH_Demo(0,0 ,(unsigned char *)"光照设置:");
				OLED_ShowNum_Three_Demo(8*5,16,PH0_Value_l);

		  break;
			case 2:
				OLED_ShowStr_ENCH_Demo(0,0 ,(unsigned char *)"               ");	
				OLED_ShowStr_ENCH_Demo(0,16,(unsigned char *)"               ");	
				OLED_ShowStr_ENCH_Demo(0,32,(unsigned char *)"               ");	
				OLED_ShowStr_ENCH_Demo(0,48,(unsigned char *)"               ");				
				OLED_ShowStr_ENCH_Demo(0,0 ,(unsigned char *)"雨滴设置:");
				OLED_ShowNum_Three_Demo(8*5,16,PH1_Value_l);
		  break;	
		}
	}

	if(Key_value == 2)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				if(PH0_Value_l<99)
				PH0_Value_l++;
				OLED_ShowNum_Three_Demo(8*5,16,PH0_Value_l);

		  break;
			case 2:
				if(PH1_Value_l<99)
				PH1_Value_l++;
				OLED_ShowNum_Three_Demo(8*5,16,PH1_Value_l);
		  break;	
		}
	}
	
	if(Key_value == 3)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				if(PH0_Value_l>0)
				PH0_Value_l--;
				OLED_ShowNum_Three_Demo(8*5,16,PH0_Value_l);

		  break;
			case 2:
				if(PH1_Value_l>0)
				PH1_Value_l--;
				OLED_ShowNum_Three_Demo(8*5,16,PH1_Value_l);
		  break;
		}
	}		
		
}
void Tim3_Handle_Process_m()
{
	static u8 i=0,j=0;
	

	switch(Motostatus)
	{
		case MotoStop_Demo:
			MotoStopFun_Demo();
			break;
		case MotoZheng_Demo:

			if(MotoPoint<MOTO_STEP)
			{
				i++;
				if(i>=8)
				{
					i=0;
					MotoPoint++;
				}
				
				Moto_Zheng_Demo(i);
				
			}else
				MotoStopFun_Demo();
					
			
			break;
		case MotoFan_Demo:
			if(MotoPoint>0)
			{
				i++;
				if(i>=8)
				{
					i=0;
					MotoPoint--;
				}
				Moto_Fan_Demo(i);
				
			}else
				MotoStopFun_Demo();
			break;

	}

	switch(Motostatus1)
	{
		case MotoStop_Demo:
			MotoStopFun_Demo1();
			break;
		case MotoZheng_Demo:

			if(MotoPoint1<MOTO_STEP)
			{
				j++;
				if(j>=8)
				{
					j=0;
					MotoPoint1++;
				}
				
				Moto_Zheng_Demo1(j);
				
			}else
				MotoStopFun_Demo1();
					
			
			break;
		case MotoFan_Demo:
			if(MotoPoint1>0)
			{
				j++;
				if(j>=8)
				{
					j=0;
					MotoPoint1--;
				}
				Moto_Fan_Demo1(j);
				
			}else
				MotoStopFun_Demo1();
			break;		
	}			
}
int main(void)
{
		delay_init();	    		//延时函数初始化
		NVIC_Configuration();	
		//不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	
		delay_ms(500);
	  //MOTO init
	  MotoStep_Init_Demo(Tim3_Handle_Process_m);	
		KEY_Init_Demo();
		ADC1_Config_Demo();
		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0 ,(unsigned char *)"左:000 右:000   ");
		OLED_ShowStr_ENCH_Demo(0,16,(unsigned char *)"上:000 下:000   ");
		OLED_ShowStr_ENCH_Demo(0,32,(unsigned char *)"雨滴:000        ");
		OLED_ShowStr_ENCH_Demo(0,48,(unsigned char *)"                ");
		while(1)
		{		
			Key_value_Demo(Key_Process_Demo);
			if(Menu_Count==0)
			{
				AD_Left = (4096-ReadADCAverageValue_Demo(0))*100/4096;			
				AD_Right = (4096-ReadADCAverageValue_Demo(1))*100/4096;			
				AD_Up = (4096-ReadADCAverageValue_Demo(2))*100/4096;	
				AD_Down = (4096-ReadADCAverageValue_Demo(3))*100/4096;			
				PH4_Value = (ReadADCAverageValue_Demo(4))*100/4096;				
				OLED_ShowNum_Three_Demo(8*3,0,AD_Left);	
				OLED_ShowNum_Three_Demo(8*10,0,AD_Right);
				OLED_ShowNum_Three_Demo(8*3,16,AD_Up);			
				OLED_ShowNum_Three_Demo(8*10,16,AD_Down);
				OLED_ShowNum_Three_Demo(8*5,32,PH4_Value);	
				if((PH4_Value>PH1_Value_l)||(AD_Left<PH0_Value_l&&AD_Right<PH0_Value_l&&AD_Up<PH0_Value_l&&AD_Down<PH0_Value_l))
				{
					Motostatus1=Motostatus=MotoStop_Demo;
					
				}else
				{
					if(((AD_Up<AD_Down)&&(AD_Down-AD_Up>10)))//上转 
					{
						Motostatus1=MotoZheng_Demo;
					}else if(((AD_Up>AD_Down)&&(AD_Up-AD_Down>10)))//下转
					{
						Motostatus1=MotoFan_Demo;
					}else
					{
						Motostatus1=Motostatus=MotoStop_Demo;
					}


					/////////////////////////////
					if(((AD_Left<AD_Right)&&(AD_Right-AD_Left>10)))//左转
					{
						Motostatus=MotoZheng_Demo;
					
					}else if(((AD_Left>AD_Right)&&(AD_Left-AD_Right>10)))//右转
					{
						Motostatus=MotoFan_Demo;
					}
					else
					{
						Motostatus=MotoStop_Demo;
					}					
				}
			
			}			
				
			delay_ms(100);
		}
}

