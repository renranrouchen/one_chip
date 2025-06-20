//每次识别时都需要说“小杰”这个口令，才能够进行下一级的识别
#include "main.h"
#define FOSC 22118400L      //系统时钟
uint32_t baud=9600;         //串口波特率

/************************************************************************
函 数 名：串口初始化
功能描述：STC10L08XE 单片机串口初始化函数
返回函数：none
其他说明：none
**************************************************************************/
void UartIni(void)
{
    SCON=0x50;            			//8-bit variable UART
    TMOD=0x20;            			//Set Timer1 as 8-bit auto reload mode
    TH1=TL1=-(FOSC/12/32/baud); 	//Set auto-reload vaule
    TR1=1;                			//Timer1 start run
    ES=1;                 			//Enable UART interrupt
    EA=1;                 			//Open master interrupt switch
}
/***********************************************************
* 名    称： 
* 功    能： 
* 入口参数：无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void Uart_Isr() interrupt 4 using 1
{	
	if(RI)
	{	  
	}
}
/************************************************************************
功能描述：串口发送一字节数据
入口参数：DAT:带发送的数据
返 回 值：none
其他说明：none
**************************************************************************/
void UARTSendByte(uint8_t DAT)
{
	ES=0;
	TI=0;
	SBUF=DAT;
	while(TI==0);
	TI=0;
	ES=1;
}

