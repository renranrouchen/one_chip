/**
 *  @file           timer.h
 *  @brief          STM32F10x ��ʱ�жϳ���
 *  @version 1.0
 *  @author         ���佨
 *  @date           2016��11��25��
 */

#include "timer.h"

static unsigned long RunTime=0;
/**
 * @Description: ͨ�ö�ʱ��TIM3��ʱ�жϳ�ʼ��
 * @param  Period    - �Զ���װֵ
 * @param  Prescaler - ʱ��Ԥ��Ƶ��
 * @note1 :�ж�ʱ��(s)=(Period*Prescaler)/ʱ��(72M)
 * @note1 :����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M,���ʱ����ͼ
 */
static pTimeProcess Tim3_Handle_Process;
void TIM3_Int_Init(u16 Period,u16 Prescaler,pTimeProcess TimeProcess)
{
    TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 			//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   						//ʹ�ܻ���ʧ��ָ����TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn;//TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  								//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
  
	Tim3_Handle_Process = TimeProcess;
	TIM_Cmd(TIM3, ENABLE);  										//ʹ��TIMx����							 
}
	   
/**
 * @Description: ͨ�ö�ʱ��TIM3�жϺ���
 */
void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 			//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);				//���TIMx���жϴ�����λ:TIM �ж�Դ 
	  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		if(Tim3_Handle_Process != 0)
			Tim3_Handle_Process();
		RunTime++; 
	}
}

unsigned long millis(void)
{
  return RunTime;
}


void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
 
	TIM_Cmd(TIM3, ENABLE); 

}
/**DEMO

TIM3_PWM_Init(899, 0);//0~900

TIM_SetCompare2(TIM3, 100);
**/







