#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  


//////////////////////////////////////////////////////////////////////////////////////////////////////
//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 64 	 		//��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
//FLASH������ֵ
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif



/**DEMO

#include "stmflash.h"
#define FLASH_SAVE_ADDR  0X0800fe00	//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
u16 test_flash[2];

void read_flash()
{
	
	STMFLASH_Read(FLASH_SAVE_ADDR,test_flash,2);
	//if(data[0]==0xffff) return;  //���Ϊ�գ�ֱ�ӷ��ء�
	//ȡ����

	
}
int main(void)
{
    delay_init();	    		//��ʱ������ʼ��
    NVIC_Configuration();
	  delay_ms(500);
		read_flash();

    while(1)
    {
			test_flash[0]=1;
			test_flash[1]=2;
			STMFLASH_Write(FLASH_SAVE_ADDR,test_flash,2);  //���Ի�������
			//delay_ms(200);
    }
}


**/













