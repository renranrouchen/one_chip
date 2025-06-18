#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   


//IO�������� PB0 �л���ʱ��ע����CRL(0~7) ����CRH(8~15)
#define DS18B20_IO_IN()  {GPIOB->CRL&=0xFFFFFFF0;GPIOB->CRL|=0x00000008;}
#define DS18B20_IO_OUT() {GPIOB->CRL&=0xFFFFFFF0;GPIOB->CRL|=0x00000003;}
////IO��������											   
#define	DS18B20_DQ_OUT PBout(0) //���ݶ˿�	PA10
#define	DS18B20_DQ_IN  PBin(0)  //���ݶ˿�	PA10 
   	
u8 DS18B20_Init(void);			//��ʼ��DS18B20
short DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20    
#endif















