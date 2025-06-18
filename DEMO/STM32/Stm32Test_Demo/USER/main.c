#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "My_Demo.h"
#include <string.h>

int main(void)
{
		delay_init();	    		//��ʱ������ʼ��
		NVIC_Configuration();	
		//����ȱ��PA13/14/15 & PB3/4Ĭ������ΪJTAG���ܣ���Ҫ��JTAG�ص�
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	
		delay_ms(500);

		while(1)
		{			
			delay_ms(100);
		}
}

