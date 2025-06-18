#include "main.h"
/************************************************************************************/
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
/***********************************************************************************/
unsigned char idata nAsrStatus=0;	
unsigned char G0_flag=DISABLE;		//���б�־��ENABLE:���С�DISABLE:��ֹ���� 
void MCU_init(); 					//��Ƭ����ʼ��
void ProcessInt0(); 				//ʶ������
void delay(unsigned long uldata);	//��ʱ����
void User_handle(unsigned char dat);//�û�ִ�в�������
void delay200ms();					//��ʱ200ms
void Led_test(void);				//��Ƭ������ָʾ

/***********************************************************
* ��    �ƣ�void main(void)
* ��    �ܣ��������������
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void main(void)
{
	unsigned char idata nAsrRes;
	unsigned char i=0;
	Led_test();					//LED�Ʋ���
	MCU_init();					//��Ƭ����ʼ��
	LD_Reset();					//LD3320��λ
	UartIni(); 					//���ڳ�ʼ��
	nAsrStatus=LD_ASR_NONE;		//��ʼ״̬��û������ASR

	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if(RunASR()==0)					//����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: 				//һ��ASRʶ�����̽�����ȥȡASRʶ����
			{				
				nAsrRes = LD_GetResult();		//��ȡ���
				User_handle(nAsrRes);			//�û�ִ�к���
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		}			
	}
}
/***********************************************************
* ��    �ƣ�LED�Ʋ���
* ��    �ܣ���Ƭ���Ƿ���ָʾ
* ��ڲ������� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void Led_test(void)
{
	LED=~ LED;
	delay200ms();
	LED=~ LED;
	delay200ms();
	LED=~ LED;
	delay200ms();
	LED=~ LED;
	delay200ms();
	LED=~ LED;
	delay200ms();
	LED=~ LED;
}
/***********************************************************
* ��    �ƣ� void MCU_init()
* ��    �ܣ� ��Ƭ����ʼ��
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void MCU_init()
{
	P0=0xff;
	P1=0xff;
	P2=0xff;
	P3=0xff;
	P4=0xff;

	P1M0=0xff;	//P1�˿�����Ϊ����������ܣ������IO�������������������̵���ģ�鹤��
	P1M1=0x00;

	LD_MODE=0;	//����MD�ܽ�Ϊ�ͣ�����ģʽ��д
	IE0=1;
	EX0=1;
	EA=1;
}
void delay200us(void)
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=97;a>0;a--);
}
void delay(unsigned long uldata)
{
	unsigned int j=0;
	unsigned int g=0;
	while(uldata--)
	delay200us();
}
void delay200ms(void)
{
    unsigned char a,b,c;
    for(c=4;c>0;c--)
        for(b=116;b>0;b--)
            for(a=214;a>0;a--);
    _nop_();
}
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				
}
/***********************************************************
* ��    �ƣ��û�ִ�к��� 
* ��    �ܣ�ʶ��ɹ���ִ�ж������ڴ˽����޸� 
* ��ڲ������� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void User_handle(uint8 dat)
{
	if(dat>0)
		dat=(dat-1)+'A';
	else
		dat='#';
	UARTSendByte(dat);//����ʶ���루ʮ�����ƣ�	
	if(0==dat)
	{
	 	G0_flag=ENABLE;
		LED=0;
	}
	else if(ENABLE==G0_flag)
	{	
	 	G0_flag=DISABLE;
		LED=1;

	}	
	else 	
	{
	}
}
