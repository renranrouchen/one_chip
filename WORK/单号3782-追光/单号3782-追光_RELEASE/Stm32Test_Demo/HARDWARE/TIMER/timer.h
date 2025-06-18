/**
 *  @file           timer.h
 *  @brief          STM32F10x ��ʱ�жϳ���
 *  @version 1.0
 *  @author         ���佨
 *  @date           2016��11��25��
 */


#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
/**
 * *FLAG_TIM3��ʱ��3�ж�״̬
 *  0-main��δ�ڴ�������
 *  1-��ʱ�жϷ�����main���Դ�������
 * -1-main�������ݳ�ʱ
 */
 
typedef void (*pTimeProcess)(); 
extern s8 FLAG_TIM3;
void TIM3_Int_Init(u16 Period,u16 Prescaler,pTimeProcess TimeProcess);
unsigned long millis(void); 

/*DEMO

unsigned long milli;

void Tim3_Handle_Process_m()
{
		milli++;
}
int main(void)
{
    delay_init();	    		//��ʱ������ʼ��
    NVIC_Configuration();
	  delay_ms(500);

		OLED_Init3();
	  //��ʱ��3��ʼ��
		TIM3_Int_Init(10000, 7200,Tim3_Handle_Process_m);//  1�� 72M/(7200)*(10000)
	  //������ʼ��

	 
		OLED_ShowStr_ENCH(0,0,(unsigned char *)"    ��ӭʹ��",1);

	  //ˢ��
		OLED_Refresh_Gram();	
		
		Motostatus= MotoZheng;
    while(1)
    {


      OLED_ShowNum(8*13,32,milli,3,16);		


			OLED_Refresh_Gram();

			
			//delay_ms(200);
    }
}


*/
#endif
