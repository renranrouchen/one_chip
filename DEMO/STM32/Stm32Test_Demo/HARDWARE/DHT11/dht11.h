#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DHT11������ʪ�ȴ�������������	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO��������
#define DHT11_IO_IN()  {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=8<<20;}
#define DHT11_IO_OUT() {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=3<<20;}
////IO��������											   
#define	DHT11_DQ_OUT PCout(13) //���ݶ˿�	PA0 
#define	DHT11_DQ_IN  PCin(13)  //���ݶ˿�	PA0 


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif


/*demo

unsigned char Temp,RhValue;
int main(void)
{
    delay_init();	    		//��ʱ������ʼ��
    NVIC_Configuration();
	  delay_ms(500);

    LCD1602_Init();
	  Lcd1602_Display_Two_bit(0,0,1);
	  DHT11_Init();
    while(1)
    {
			if(DHT11_Read_Data(&Temp,&RhValue) == 0)
			{
				Lcd1602_Display_Three_bit(0,0,Temp);//������ʪ�ȣ�ֻȡ��������
				Lcd1602_Display_Three_bit(1,0,RhValue);
			}
			delay_ms(200);
    }
}

*/












