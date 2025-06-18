#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void UART1_Send_String(unsigned char *Index);
void USART1_Send_Data(unsigned char *Data,unsigned short Length);

/*DEMO

unsigned char buff[30];
unsigned long milli;
u8 keyVal;
void Bule_Send()
{
		buff[0]= 'H';
		buff[1]= ':';
	  buff[2]= PH0_Value/1000%10+0x30;
		buff[3]= PH0_Value/100%10+0x30;
		buff[4]= PH0_Value/10%10+0x30;
		buff[5]= PH0_Value%10+0x30;
		buff[6]= ',';
		buff[7]= PH1_Value/1000%10+0x30;
		buff[8]= PH1_Value/100%10+0x30;
		buff[9]= PH1_Value/10%10+0x30;
		buff[10]= PH1_Value%10+0x30;	
		buff[11]= ',';
		buff[12]= PH2_Value/1000%10+0x30;
		buff[13]= PH2_Value/100%10+0x30;
		buff[14]= PH2_Value/10%10+0x30;
		buff[15]= PH2_Value%10+0x30;
		buff[16]= ',';			
		buff[17]= 'E';	
		USART1_Send_Data(buff,sizeof(buff));		
}

int main(void)
{
    delay_init();	    		//��ʱ������ʼ��
    NVIC_Configuration();
	 // GPIO_TEST();
	  delay_ms(500);

	  uart_init(9600);
		OLED_Init3();


		OLED_ShowStr_ENCH(0,0,(unsigned char *)"01��ӭʹ������",1);

		OLED_Refresh_Gram();	
    while(1)
    {

			Bule_Send();
			printf("hello");

			delay_ms(100);
    }
}



*/
#endif


