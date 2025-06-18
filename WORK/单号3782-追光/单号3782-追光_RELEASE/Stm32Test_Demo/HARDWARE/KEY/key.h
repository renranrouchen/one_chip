#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
typedef void (*pKey_Process)(unsigned char );

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//��ȡ����1
#define KEY2   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����2 
#define KEY3   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����2 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define KEY2_PRES	3		//WK_UP  
#define KEY3_PRES	4		//WK_UP 
void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					
void Key_Process(pKey_Process Key_Process_p);

/*DEMO

u8 keyVal;

void Key_Process_s(unsigned char keyValue)
{
	if(keyValue == 1 )
	{
		keyVal++;

	}
	if(keyValue == 2 )
	{
		keyVal=keyVal+2;

	}
	if(keyValue == 3 )
	{
		keyVal=keyVal+3;

	}	
	if(keyValue == 4 )
	{
		keyVal=keyVal+4;

	}		
}
int main(void)
{
    delay_init();	    		//��ʱ������ʼ��
    NVIC_Configuration();
	 // GPIO_TEST();
	  delay_ms(500);

		OLED_Init3();

		KEY_Init();
		OLED_ShowStr_ENCH(0,0,(unsigned char *)"01��ӭʹ������",1);

		OLED_Refresh_Gram();	
    while(1)
    {
			Key_Process(Key_Process_s);

			OLED_ShowNum(16*3,32,keyVal,4,16);
			OLED_Refresh_Gram();	


			delay_ms(100);
    }
}



*/
#endif
