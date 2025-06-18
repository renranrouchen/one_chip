#include "main.h"
/************************************************************************************/
//	nAsrStatus 用来在main主程序中表示程序运行的状态，不是LD3320芯片内部的状态寄存器
//	LD_ASR_NONE:		表示没有在作ASR识别
//	LD_ASR_RUNING：		表示LD3320正在作ASR识别中
//	LD_ASR_FOUNDOK:		表示一次识别流程结束后，有一个识别结果
//	LD_ASR_FOUNDZERO:	表示一次识别流程结束后，没有识别结果
//	LD_ASR_ERROR:		表示一次识别流程中LD3320芯片内部出现不正确的状态
/***********************************************************************************/
unsigned char idata nAsrStatus=0;	
unsigned char G0_flag=DISABLE;		//运行标志，ENABLE:运行。DISABLE:禁止运行 
void MCU_init(); 					//单片机初始化
void ProcessInt0(); 				//识别处理函数
void delay(unsigned long uldata);	//延时函数
void User_handle(unsigned char dat);//用户执行操作函数
void delay200ms();					//延时200ms
void Led_test(void);				//单片机工作指示

/***********************************************************
* 名    称：void main(void)
* 功    能：主函数程序入口
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void main(void)
{
	unsigned char idata nAsrRes;
	unsigned char i=0;
	Led_test();					//LED灯测试
	MCU_init();					//单片机初始化
	LD_Reset();					//LD3320复位
	UartIni(); 					//串口初始化
	nAsrStatus=LD_ASR_NONE;		//初始状态：没有在作ASR

	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if(RunASR()==0)					//启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: 				//一次ASR识别流程结束，去取ASR识别结果
			{				
				nAsrRes = LD_GetResult();		//获取结果
				User_handle(nAsrRes);			//用户执行函数
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
* 名    称：LED灯测试
* 功    能：单片机是否工作指示
* 入口参数：无 
* 出口参数：无
* 说    明： 					 
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
* 名    称： void MCU_init()
* 功    能： 单片机初始化
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void MCU_init()
{
	P0=0xff;
	P1=0xff;
	P2=0xff;
	P3=0xff;
	P4=0xff;

	P1M0=0xff;	//P1端口设置为推挽输出功能，即提高IO口驱动能力，从驱动继电器模块工作
	P1M1=0x00;

	LD_MODE=0;	//设置MD管脚为低，并行模式读写
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
* 名    称：用户执行函数 
* 功    能：识别成功后，执行动作可在此进行修改 
* 入口参数：无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void User_handle(uint8 dat)
{
	if(dat>0)
		dat=(dat-1)+'A';
	else
		dat='#';
	UARTSendByte(dat);//串口识别码（十六进制）	
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
