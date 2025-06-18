
#ifndef __USART2_H
#define	__USART2_H
#include "stm32f10x.h"
#define USART2_REC_LEN 100
extern u8 IRQURA2;//����2 ����������ϱ�־ 
extern u8 USART2_RX_BUF[USART2_REC_LEN];//����2�������ݷ���ȥ
void usart2_init(u32 band);//����2 ��ʼ������
void usart2_SendStringByLen(unsigned char * data,u8 len);//
void usart2_SendString(unsigned char * data);
u16 usart2_receive(u32 time);
void USART2SendByte(unsigned char SendData);
#endif

/*demo

#include "usart2.h"

int main(void)
{
    delay_init();	    		//��ʱ������ʼ��
    NVIC_Configuration();
	  delay_ms(500);
//    uart_init(9600);
    LCD1602_Init();
		usart2_init(9600);
    while(1)
    {
			usart2_SendString("hello");
			delay_ms(1000);
    }
}
*/

