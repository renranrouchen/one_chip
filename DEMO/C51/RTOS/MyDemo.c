
#include "MyConfig.h"
#include "MyDemo.h"
#include <intrins.h>


#if CONFIG_UTRL == ENABLED

void DelayMs_utrl(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}

#endif
/*********************LCD1602*********************/
#if CONFIG_LCD1602 == ENABLED

void Lcd1602_Demo_write_com(unsigned char com);
void Lcd1602_Demo_write_data(unsigned char dat);


/********************************************************************
* 名称 : delay_uint()
* 功能 : 小延时。
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Lcd1602_delay_uint(unsigned int q)
{
	while(q--);
}

/********************************************************************
* 名称 : write_com(uchar com)
* 功能 : 1602命令函数
* 输入 : 输入的命令值
* 输出 : 无
***********************************************************************/
void Lcd1602_write_com(unsigned char com)
{
	Lcd1602_e=0;
	Lcd1602_rs=0;
	Lcd1602_rw=0;
	P0=com;
	Lcd1602_delay_uint(3);
	Lcd1602_e=1;
	Lcd1602_delay_uint(25);
	Lcd1602_e=0;
}

/********************************************************************
* 名称 : write_data(uchar dat)
* 功能 : 1602写数据函数
* 输入 : 需要写入1602的数据
* 输出 : 无
***********************************************************************/
void Lcd1602_write_data(unsigned char dat)
{
	Lcd1602_e=0;
	Lcd1602_rs=1;
	Lcd1602_rw=0;
	P0=dat;
	Lcd1602_delay_uint(3);
	Lcd1602_e=1;
	Lcd1602_delay_uint(25);
	Lcd1602_e=0;	
}

void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	Lcd1602_Demo_write_data(0x30+date/10%10);
	Lcd1602_Demo_write_data(0x30+date%10);	
}

void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	Lcd1602_Demo_write_data(0x30+date/100%10);
	Lcd1602_Demo_write_data(0x30+date/10%10);
	Lcd1602_Demo_write_data(0x30+date%10);	
}

void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
		while(1)
		{
			if(*p == '\0')  break;
			Lcd1602_Demo_write_data(*p);
			p++;
		}	
}


/*****************控制光标函数********************/
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date)
{		
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	if(date == 1)
		Lcd1602_Demo_write_com(0x0f);     //显示光标并且闪烁	
	else 
		Lcd1602_Demo_write_com(0x0c);   //关闭光标
}

void Lcd1602_Display_Init()
{
	Lcd1602_Demo_write_com(0x38);
	Lcd1602_Demo_write_com(0x38);
	Lcd1602_Demo_write_com(0x0c);
	Lcd1602_Demo_write_com(0x06);
}
#if CONFIG_DS1302 == ENABLED
/*********************************************************/
// 液晶输出数字
/*********************************************************/
void Ds13b02_DisPlay(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add); 
	Lcd1602_Demo_write_data(shi%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(shi%10+0x30);				// 个位
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(fen%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(fen%10+0x30);				// 个位
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(miao%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(miao%10+0x30);				// 个位

}
#endif

#endif

/********************独立按键程序*****************/
#if CONFIG_KEY == ENABLED


void Key_value_Demo(pKey_Process key_Process)	 //独立按键程序
{
	unsigned char Key_value;
#if KEY_COUNT == 1
	if((Demo_KEY1 == 0))
	{
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}				
	}	
#endif	
#if KEY_COUNT == 2
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0))
	{
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
				
	}	
	
#endif	
#if KEY_COUNT == 3
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) )
	{
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		
	}	
#endif	
#if KEY_COUNT == 4
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) || (Demo_KEY4 == 0) )
	{
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		if(Demo_KEY4 == 0)
		{
			Key_value = 4;
			while(!Demo_KEY4);
		}
	
	}	
#endif	
#if KEY_COUNT == 5
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) || (Demo_KEY4 == 0) || (Demo_KEY5 == 0))
	{
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		if(Demo_KEY4 == 0)
		{
			Key_value = 4;
			while(!Demo_KEY4);
		}
		if(Demo_KEY5 == 0)
		{
			Key_value = 5;
			while(!Demo_KEY5);
		}
	
	}	
#endif	
#if KEY_COUNT == 6
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) || (Demo_KEY4 == 0) || (Demo_KEY5 == 0) || (Demo_KEY6 == 0))
	{
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		if(Demo_KEY4 == 0)
		{
			Key_value = 4;
			while(!Demo_KEY4);
		}
		if(Demo_KEY5 == 0)
		{
			Key_value = 5;
			while(!Demo_KEY5);
		}
		if(Demo_KEY6 == 0)
		{
			Key_value = 6;
			while(!Demo_KEY6);
		}		
	}
#endif	
	else
		Key_value = 21;
	
	key_Process(Key_value);

}



#endif


/*********************ADC0832********************/
#if CONFIG_ADC0832 == ENABLED

  

unsigned char ADC0832_Demo(bit mode,bit channel)    //AD转换，返回结果
{
	unsigned char i,dat,ndat;
	
	ADCS = 0;//拉低CS端
	_nop_();
	_nop_();
	
	ADDI = 1;	//第1个下降沿为高电平
	ADCLK = 1;//拉高CLK端
	_nop_();
	_nop_();
	ADCLK = 0;//拉低CLK端,形成下降沿1
	_nop_();
	_nop_();
	
	ADDI = mode;	//低电平为差分模式，高电平为单通道模式。	
	ADCLK = 1;//拉高CLK端
	_nop_();
	_nop_();
	ADCLK = 0;//拉低CLK端,形成下降沿2
	_nop_();
	_nop_();
	
	ADDI = channel;	//低电平为CH0，高电平为CH1	
	ADCLK = 1;//拉高CLK端
	_nop_();
	_nop_();
	ADCLK = 0;//拉低CLK端,形成下降沿3
	
	ADDI = 1;//控制命令结束(经试验必需)
	dat = 0;
	//下面开始读取转换后的数据，从最高位开始依次输出（D7~D0）
	for(i = 0;i < 8;i++)
	{
		dat <<= 1;
		ADCLK=1;//拉高时钟端
		_nop_();
		_nop_();
		ADCLK=0;//拉低时钟端形成一次时钟脉冲
		_nop_();
		_nop_();
		dat |= ADDO;
	}
	ndat = 0; 	   //记录D0
	if(ADDO == 1)
	ndat |= 0x80;
	//下面开始继续读取反序的数据（从D1到D7） 
	for(i = 0;i < 7;i++)
	{
		ndat >>= 1;
		ADCLK = 1;//拉高时钟端
		_nop_();
		_nop_();
		ADCLK=0;//拉低时钟端形成一次时钟脉冲
		_nop_();
		_nop_();
		if(ADDO==1)
		ndat |= 0x80;
	}	  
	ADCS=1;//拉高CS端,结束转换
	ADCLK=0;//拉低CLK端
	ADDI=1;//拉高数据端,回到初始状态
	if(dat==ndat)
	return(dat);
	else
	return 0;   
}

#endif

/*********************DS1302********************/
#if CONFIG_DS1302 == ENABLED

/******************
	ds1302 内部RAM   RAM0  1100 000R/W   1读 0写
					 RAM1  1100 001R/W  
					       ....... 
					 RAM30 1111 110R/W   
********************/

unsigned char code Ds1302_write_add[]={0x80,0x82,0x84,0x86,0x88,0x8c,0x8a};   //写地址
unsigned char code Ds1302_read_add[] ={0x81,0x83,0x85,0x87,0x89,0x8d,0x8b};   //读地址
unsigned char code Ds1302_init_ds[]  ={0x58,0x29,0x07,0x05,0x10,0x14,0x1}; 

void DelayMs_Ds1302(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}

/*************写一个数据到对应的地址里***************/
void Ds1302_Write_Demo(unsigned char add,unsigned char dat)
{
	unsigned char i;
	rst = 1;			 //把复位线拿高
	for(i=0;i<8;i++)
	{				     //低位在前

		io = add & 0x01;    	
		add >>= 1;		 //把地址右移一位
		clk = 1;		 //时钟线拿高	 
		clk = 0;		 //时钟线拿低开始写数据
	}									 
	for(i=0;i<8;i++)
	{

		io = dat & 0x01;
		dat >>= 1;		 //把数据右移一位	
		clk = 1;		 //时钟线拿高
		clk = 0;		 //时钟线拿低开始写数据
	}
	rst = 0;			 //复位线合低
}


/*************从对应的地址读一个数据出来***************/
unsigned char Ds1302_Read_Demo(unsigned char add)
{
	unsigned char value,i;
	rst = 1;			 //把复位线拿高
	for(i=0;i<8;i++)
	{				     //低位在前
		clk = 0;		 //时钟线拿低开始写数据
		io = add & 0x01;    	
		add >>= 1;		 //把地址右移一位
		clk = 1;		 //时钟线拿高
	}		
	for(i=0;i<8;i++)
	{
		clk = 1;		 //时钟线拿高
		clk = 0;		 //时钟线拿低开始读数据
		value >>= 1;
		if(io == 1)
			value |= 0x80;
	}
	rst = 0;			 //复位线合低
	clk = 0;
	io = 0;
	return value;		 //返回读出来的数据
}

unsigned char BCD_Decimal(unsigned char bcd)//BCD码转十进制函数，输入BCD，返回十进制
{
	 unsigned char Decimal;
	 Decimal=bcd>>4;
	 return(Decimal=Decimal*10+(bcd&=0x0F));
}

/*************把要的时间 年月日 都读出来***************/
//arry[7]
void Ds1302_Read_Time(unsigned char *arry)
{
	*arry      = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[0]));	//读秒
	*(arry+1)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[1]));	//读分
	*(arry+2)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[2]));	//读时
	*(arry+3)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[3]));	//读日
	*(arry+4)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[4]));	//读月
	*(arry+5)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[5]));	//读年
	*(arry+6)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[6]));	//读星期
}

void Ds1302_Save(unsigned char  po, unsigned char  dat)
{
	unsigned char  temp;
	temp=(dat)/10*16+(dat)%10;//十进制转换成DS1302要求的DCB码
	Ds1302_Write_Demo(0x8e,0x00);//允许写，禁止写保护 
	Ds1302_Write_Demo(po,temp);//向DS1302内写分寄存器82H写入调整后的分数据BCD码
	Ds1302_Write_Demo(0x8e,0x80);//打开写保护	
}

/*************把要写的时间 年月日 都写入ds1302里***************/
void Ds1302_Write_Time(unsigned char *arry)
{
	Ds1302_Write_Demo(0x8e,0x00);			//打开写保护

	Ds1302_Write_Demo(Ds1302_write_add[0],0x80);	

	Ds1302_Write_Demo(Ds1302_write_add[0],arry[0]);	//写秒
	Ds1302_Write_Demo(Ds1302_write_add[1],arry[1]);		//写分
	Ds1302_Write_Demo(Ds1302_write_add[2],arry[2]);		//写时
	Ds1302_Write_Demo(Ds1302_write_add[3],arry[3]);		//写日
	Ds1302_Write_Demo(Ds1302_write_add[4],arry[4]);		//写月
	Ds1302_Write_Demo(Ds1302_write_add[5],arry[5]);	//写星期
	Ds1302_Write_Demo(Ds1302_write_add[6],arry[6]);	//写年
	Ds1302_Write_Demo(0x8e,0x80);			//关闭写保护
}

/*************把数据保存到ds1302 RAM中**0-31*************/
void Ds1302_Write_ram(unsigned char add,unsigned char dat)
{
	add <<= 1;     //地址是从第二位开始的
	add &= 0xfe;   //把最低位清零  是写的命令
	add |= 0xc0;   //地址最高两位为 1  
	Ds1302_Write_Demo(0x8e,0x00);
	Ds1302_Write_Demo(add,dat);	
	Ds1302_Write_Demo(0x8e,0x80);
}


/*************把数据从ds1302 RAM读出来**0-31*************/
unsigned char Ds1302_Read_ds1302ram(unsigned char add)
{
	add <<= 1;     //地址是从第二位开始的
	add |= 0x01;   //把最高位置1  是读命令
	add |= 0xc0;   //地址最高两位为 1  
	return(Ds1302_Read_Demo(add));	
}

/**********************设置ds1302时间函数**********************/
void Ds1302_Set_time(unsigned char num,unsigned char *shi,unsigned char dat)	 //调时
{
  	if(num == 1)
    {
    	*shi+=0x01;
		if((*shi & 0x0f) >= 0x0a)
			*shi = (*shi & 0xf0) + 0x10;
		if(*shi >= dat)
			*shi = 0;
    }
    else
    {
		if(*shi == 0x00)
			*shi = dat;
		if((*shi & 0x0f) == 0x00)
			*shi = (*shi | 0x0a) - 0x10;
		*shi -=0x01 ; 
    }  
}

/*************初始化ds1302时间***************/
void Ds1302_Init()
{
	unsigned char i;
	rst = 0;	//第一次读写数据时要把IO品拿低
	clk = 0;
	io = 0;
	i = Ds1302_Read_ds1302ram(30);   
	if(i != 3)
	{	
		i = 3;
		Ds1302_Write_ram(30,i);			 //4050   4100		 3080

		Ds1302_Write_Demo(0x8e,0x00);	            //打开写保护
		for(i=0;i<7;i++)
			Ds1302_Write_Demo(Ds1302_write_add[i],Ds1302_init_ds[i]);	//把最高位值0 允许ds1302工作
		Ds1302_Write_Demo(0x8e,0x80);	//关写保护
	}

	//read_time();		  //读时间
	//if(miao >= 0x60)
	{
		Ds1302_Write_Demo(0x8e,0x00);	            //打开写保护
		Ds1302_Write_Demo(Ds1302_write_add[0],0x01);	//把最高位值0 允许ds1302工作
		Ds1302_Write_Demo(0x8e,0x80);	//关写保护
		
	}

}

/*demo
uchar arry[7];
Ds1302_Read_Time(arry);
*/
#endif

/*********************DS18b02********************/
#if CONFIG_DS18b02 == ENABLED
/***********************18b20初始化函数*****************************/

/********************************************************************
* 名称 : delay_uint()
* 功能 : 小延时。
* 输入 : 无
* 输出 : 无
***********************************************************************/


void delay_18B20(unsigned int q)
{
	while(q--);
}

void Ds18b02_Init()
{
	bit q;
	dq = 1;				//把总线拿高
	delay_18B20(1);	    //15us
	dq = 0;				//给复位脉冲
	delay_18B20(80);		//750us
	dq = 1;				//把总线拿高 等待
	delay_18B20(10);		//110us
	q = dq;				//读取18b20初始化信号
	delay_18B20(20);		//200us
	dq = 1;				//把总线拿高 释放总线
}

/*************写18b20内的数据***************/
void DS18b20_Write(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{					 //写数据是低位开始
		dq = 0;			 //把总线拿低写时间隙开始 
		dq = dat & 0x01; //向18b20总线写数据了
		delay_18B20(5);	 // 60us
		dq = 1;			 //释放总线
		dat >>= 1;
	}	
}

/*************读取18b20内的数据***************/
unsigned char Ds18b20_Read()
{
	unsigned char i,value;
	for(i=0;i<8;i++)
	{
		dq = 0;			 //把总线拿低读时间隙开始 
		value >>= 1;	 //读数据是低位开始
		dq = 1;			 //释放总线
		if(dq == 1)		 //开始读写数据 
			value |= 0x80;
		delay_18B20(5);	 //60us	读一个时间隙最少要保持60us的时间
	}
	return value;		 //返回数据
}

/*************读取温度的值 读出来的是小数***************/
unsigned int Ds18b20_Read_temp()
{
	unsigned int value;
	unsigned char low;			   //在读取温度的时候如果中断的太频繁了，就应该把中断给关了，否则会影响到18b20的时序
	Ds18b02_Init();		   //初始化18b20
	DS18b20_Write(0xcc);	   //跳过64位ROM
	DS18b20_Write(0x44);	   //启动一次温度转换命令

	Ds18b02_Init();		   //初始化18b20
	
	DS18b20_Write(0xcc);	   //跳过64位ROM
	DS18b20_Write(0xbe);	   //发出读取暂存器命令
	
	low = Ds18b20_Read();	   //读温度低字节
	value = Ds18b20_Read();  //读温度高字节
	value <<= 8;		   //把温度的高位左移8位
	value |= low;		   //把读出的温度低位放到value的低八位中
	value *= 0.0625;	       //转换到温度值 
	return value;		   //返回读出的温度 
}

#endif


/*********************EEPROM********************/
#if CONFIG_EEPROM == ENABLED

/********STC89C51扇区分布*******
第一扇区：1000H--11FF
第二扇区：1200H--13FF
第三扇区：1400H--15FF
第四扇区：1600H--17FF
第五扇区：1800H--19FF
第六扇区：1A00H--1BFF
第七扇区：1C00H--1DFF
第八扇区：1E00H--1FFF
*****************/

/********STC89C52扇区分布*******
第一扇区：2000H--21FF
第二扇区：2200H--23FF
第三扇区：2400H--25FF
第四扇区：2600H--27FF
第五扇区：2800H--29FF
第六扇区：2A00H--2BFF
第七扇区：2C00H--2DFF
第八扇区：2E00H--2FFF
*****************/


#define RdCommand 0x01 //定义ISP的操作命令
#define PrgCommand 0x02
#define EraseCommand 0x03 
#define Error 1
#define Ok 0
#define WaitTime 0x01 //定义CPU的等待时间
sfr ISP_DATA=0xe2;  //寄存器申明
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;


	

/* ================ 打开 ISP,IAP 功能 ================= */
void ISP_IAP_enable_Demo(void)
{
	 EA = 0;       /* 关中断   */
	 ISP_CONTR = ISP_CONTR & 0x18;       /* 0001,1000 */
	 ISP_CONTR = ISP_CONTR | WaitTime; /* 写入硬件延时 */
	 ISP_CONTR = ISP_CONTR | 0x80;       /* ISPEN=1  */
}
/* =============== 关闭 ISP,IAP 功能 ================== */
void ISP_IAP_disable_Demo(void)
{
	 ISP_CONTR = ISP_CONTR & 0x7f; /* ISPEN = 0 */
	 ISP_TRIG = 0x00;
	 EA   =   1;   /* 开中断 */
}
/* ================ 公用的触发代码 ==================== */
void ISPgoon_Demo(void)
{
	 ISP_IAP_enable_Demo();   /* 打开 ISP,IAP 功能 */
	 ISP_TRIG = 0x46;  /* 触发ISP_IAP命令字节1 */
	 ISP_TRIG = 0xb9;  /* 触发ISP_IAP命令字节2 */
	 _nop_();
}
/* ==================== 字节读 ======================== */
unsigned char byte_read_Demo(unsigned int byte_addr)
{
	EA = 0;
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);/* 地址赋值 */
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	 ISP_CMD   = ISP_CMD & 0xf8;   /* 清除低3位  */
	 ISP_CMD   = ISP_CMD | RdCommand; /* 写入读命令 */
	 ISPgoon_Demo();       /* 触发执行  */
	 ISP_IAP_disable_Demo();    /* 关闭ISP,IAP功能 */
	 EA  = 1;
	 return (ISP_DATA);    /* 返回读到的数据 */
}
/* ================== 扇区擦除 ======================== */
void SectorErase_Demo(unsigned int sector_addr)
{
	 unsigned int iSectorAddr;
	 iSectorAddr = (sector_addr & 0xfe00); /* 取扇区地址 */
	 ISP_ADDRH = (unsigned char)(iSectorAddr >> 8);
	 ISP_ADDRL = 0x00;
	 ISP_CMD = ISP_CMD & 0xf8;   /* 清空低3位  */
	 ISP_CMD = ISP_CMD | EraseCommand; /* 擦除命令3  */
	 ISPgoon_Demo();       /* 触发执行  */
	 ISP_IAP_disable_Demo();    /* 关闭ISP,IAP功能 */
}
/* ==================== 字节写 ======================== */
void byte_write_Demo(unsigned int byte_addr, unsigned char original_data)
{
	 EA  = 0;
//	 SectorErase(byte_addr);
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);  /* 取地址  */
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	 ISP_CMD  = ISP_CMD & 0xf8;    /* 清低3位 */
	 ISP_CMD  = ISP_CMD | PrgCommand;  /* 写命令2 */
	 ISP_DATA = original_data;   /* 写入数据准备 */
	 ISPgoon_Demo();       /* 触发执行  */
	 ISP_IAP_disable_Demo();     /* 关闭IAP功能 */
	 EA =1;
}
#endif


/*********************24C02********************/
#if CONFIG_24C02 == ENABLED

/*********************************
      BASE  DRIVE
**********************************/
void DELAY_24C02_Demo(unsigned int t)
{
	while(t!=0)
	t--;
}

/******************************
      IIC  DRIVE
******************************/
void IICStart_24C02_Demo(void)
{
     SCL=0;  
 	 DELAY_24C02_Demo(1);
     SDA=1; SCL=1; DELAY_24C02_Demo(1);
     SDA=0; DELAY_24C02_Demo(1);
     SCL=0; 
}

void IICStop_24C02_Demo(void)
{
	 SDA=0;SCL=1; DELAY_24C02_Demo(1);
     SDA=1; DELAY_24C02_Demo(1);
     SCL=0; 	
}
void SEND0_24C02_Demo(void)
{
	SDA=0;
	SCL=1;
	DELAY_24C02_Demo(1);
	SCL=0;
}

void SEND1_24C02_Demo(void)
{
	SDA=1;
	DELAY_24C02_Demo(1);
	SCL=1;
	DELAY_24C02_Demo(1);
	SCL=0;
}

bit Check_Ack_24C02_Demo(void)
{
   unsigned char errtime=250;
   DELAY_24C02_Demo(1);
   SCL=1; 
   DELAY_24C02_Demo(1);
   CY=SDA;
   while(CY)
   {
    errtime--; 
    CY=SDA;
    if (!errtime)
     {
     IICStop_24C02_Demo();
    
     return 1;
     }
}
 DELAY_24C02_Demo(1);
 SCL=0; 
 return 0;
}


void Write_byte_24C02_Demo(unsigned char dat) 
{
    unsigned char i;
	for(i=0;i<8;i++)
	{	
		if((dat<<i)&0x80)
		SEND1_24C02_Demo();
		else
		SEND0_24C02_Demo();
	}
}


unsigned char Read_byte_24C02_Demo(void)
{
	unsigned char i,temp=0;     
	for(i=0;i<8;i++)
	{
        SDA=1;
	    SCL=1;
	    DELAY_24C02_Demo(1);  
		if(SDA==1)
		{
			temp=temp<<1;
			temp=temp|0x01;
		}
		else
			temp=temp<<1;
		 SCL=0;	
	  }
	  return temp;
}

/************************************
      EEPROM  DRIVE
	  Addr:from 0x00-->
*************************************/
unsigned char rdeeprom_24C02_Demo(unsigned char addr)
{ 
        unsigned char temp=0;
		bit flag=0;
		IICStart_24C02_Demo();
		Write_byte_24C02_Demo(0xa0);
        Check_Ack_24C02_Demo();
		Write_byte_24C02_Demo(addr);
		Check_Ack_24C02_Demo();
		IICStart_24C02_Demo();
		Write_byte_24C02_Demo(0xa1);
		Check_Ack_24C02_Demo();
		temp=Read_byte_24C02_Demo();
		SEND1_24C02_Demo();
		IICStop_24C02_Demo();
 	    return temp;   
}  
    
   
void wrteeprom_24C02_Demo(unsigned char addr,unsigned char dat)
{
    IICStart_24C02_Demo();
		Write_byte_24C02_Demo(0xa0);
		Check_Ack_24C02_Demo();
		Write_byte_24C02_Demo(addr);
		Check_Ack_24C02_Demo();
		Write_byte_24C02_Demo(dat);
		Check_Ack_24C02_Demo();
		IICStop_24C02_Demo();
} 
#endif

/*********************Timer2********************/
#if CONFIG_Timer2 == ENABLED
static Timer2_Process  Interrp_Process;

unsigned char TimeCtr;

void Timer2_init_Demo(Timer2_Process T_Process)
{
	RCAP2H = (0XFFFF - 50000)/256;
	RCAP2L = (0XFFFF - 50000)%256;
	T2CON =0;
	//T2MOD = 0;
	IE |=0xA0;
	TR2 = 1;
	Interrp_Process = T_Process;
}

void timer2() interrupt 5
{
	TF2 = 0;
	TimeCtr++;
	if(TimeCtr >= Time_count)//1秒
	{
		TimeCtr =0;
		Interrp_Process();
		//Buzzer_P = ~Buzzer_P;
	}
		
}

#endif

/*********************Timer0定时********************/
#if CONFIG_Timer0 == ENABLED

//	TMOD=0x21;             //定时器T1工作于计数模式1，定时器T0工作于计时模式1；
//	TH1=(65536-46083)/256;    //定时器T0的高8位设置初值，每50ms产生一次中断
//	TL1=(65536-46083)%256;    //定时器T0的低8位设置初值，每50ms产生一次中断
//	TH0=(65536-20000)/256;    //定时器T0的高8位设置初值，每50ms产生一次中断
//	TL0=(65536-20000)%256;    //定时器T0的低8位设置初值，每50ms产生一次中断
static Timer0_Process  Timer_Process;
unsigned char RHCounter;
//定时器0初始化
void Timer0_Init_demo(Timer0_Process T_Process) 
{
    ET0 = 1;        //允许定时器0中断
    TMOD = 0x01;       //定时器工作方式选择
    TL0 = 0xFF;
    TH0 = 0x4B;     //定时器赋予初值
    TR0 = 1;        //启动定时器
	  EA = 1;
		Timer_Process = T_Process;
}

//定时器0中断
void Timer0_ISR (void) interrupt 1 using 0 {
    TL0 = 0xFF;
    TH0 = 0x4B;     //定时器赋予初值
    RHCounter++;

    if (RHCounter >= 40) //2秒
		{
				Timer_Process();
        RHCounter = 0;
    }
}
#endif


/********************UART0 *********************/
#if CONFIG_UART0 == ENABLED
bit UART0_TXD_BUSY = 0;
static UART0_RX_Process_T  UART0_RX_Process;
void UART0_Send_Byte_Demo(unsigned char a)
{

	SBUF = a;
  UART0_TXD_BUSY = 1;	
	while(UART0_TXD_BUSY);	//等待发送成功

}




/*----------------------------
UART1 发送字符串
-----------------------------*/
void UART0_Send_String_Demo(char *s)
{
	while(*s)//检测字符串结束符
	{
		UART0_Send_Byte_Demo(*s++);//发送当前字符
	}
}


void UART0_Init_Demo(UART0_RX_Process_T RX_Process)
{
	
	TMOD|= 0X20;		//T1  方式2  ，8位   自动重装   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600
	TR1=1; 		    // 定时器1启动  


	SM0=0;	    // 设置串口的工作模式
	SM1=1; 	    //方式1


	REN=1; 		 // 允许串口接收数据 	 

  TI=1;
	ES=1; 	     // 串口中断应许 
	EA=1;		 // 开启中断 
	UART0_RX_Process = RX_Process;
	
}
unsigned char UART0_RXD[3];
unsigned char UART0_RXD_Index =0;
void UART0_ISR(void) interrupt 4
{
	unsigned char a;
	
	if(RI)
	{
		RI = 0;
		
		a = SBUF;
		//接收多数据
		UART0_RXD[UART0_RXD_Index] = a;
		UART0_RXD_Index++;
		if(UART0_RXD[0] != CRC)//校验帧
		{
			UART0_RXD_Index =0;
		}
		if(UART0_RXD_Index>REV_NUM)//要接收的数量
		{
			UART0_RX_Process(UART0_RXD);
			UART0_RXD[1] = 0;
			UART0_RXD_Index =0;	
		}			
				
	}
	else if(TI)
	{
		TI = 0;
		UART0_TXD_BUSY = 0;
	}
	else
	{
		RI = 0;
		TI = 0;
	}
	
}
#endif



/********************KEY_MAP *********************/
#if CONFIG_KEY_MAP == ENABLED

//按键扫描函数 :    
//功能；只扫描一个按键，按键为号小优先  
//返回键值：
//         7    8    9    10	   //10:清除单价并且清除重量	
//         4    5    6    11	   //11:清除单价最后一位
//         1    2    3    12	   //12:去皮
//         14   0    15   13	   //14:无功能（用于扩展）15：小数点  13：确定

unsigned char Getkeyboard(void)
{
    unsigned char number = 0;
    unsigned char i;
	
	//行输入低电平
    ROW1=ROW2=ROW3=ROW4=0;
	//如果列输出不全为高，则说明有键按下
	if ((COL1!=1)||(COL2!=1)||(COL3!=1)||(COL4!=1))
	{
	   //输入0111
	   ROW1=0;
	   ROW2=ROW3=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 1;	   // 7
	   else if (COL2==0) return 2;	//	 8
	   else if (COL3==0) return 3;	 //	9
	   else if (COL4==0) return 10;	 //	 10
	   //输入1011
	   ROW2=0;
	   ROW1=ROW3=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 4;	  //4
	   else if (COL2==0) return 5; //  5
	   else if (COL3==0) return 6;	// 6
	   else if (COL4==0) return 11;	 //	11
	   //输入1101
	   ROW3=0;
	   ROW1=ROW2=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 7;  //1
	   else if (COL2==0) return 8;	  // 2
	   else if (COL3==0) return 9;	  //   3
	   else if (COL4==0) return 12;	  //   12
	   //输入0111
	   ROW4=0;
	   ROW1=ROW2=ROW3=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 14;
	   else if (COL2==0) return 0;
	   else if (COL3==0) return 15;
	   else if (COL4==0) return 13;
	   //没有检测到列低电平
	   return 99;
	}
	return 99;
}

#endif

/********************HX711 *********************/
#if CONFIG_HX711 == ENABLED

unsigned long Weight_Maopi;

void Delay__hx711_us(void)
{
	_nop_();
	_nop_();
}

//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
unsigned int GapValue=245;
void Delay_ms_HX711(unsigned int n)
{
	unsigned int  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}

unsigned long HX711_Read(void)	//增益128
{
	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT=1; 
	Delay__hx711_us();
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
	} 
 	HX711_SCK=1; 
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	Delay__hx711_us();
	HX711_SCK=0;  
	return(count);
}
//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi()
{
	unsigned long Weight_Maopi_0 = 0;
mm:	Weight_Maopi_0 = HX711_Read();
	Delay_ms_HX711(500);
	Weight_Maopi = HX711_Read();
	if(Weight_Maopi/GapValue!=Weight_Maopi_0/GapValue)
	goto mm;

} 

//****************************************************
//称重
//****************************************************
long Get_Weight()
{
	long Weight_Shiwu;
	Weight_Shiwu = HX711_Read();
	Weight_Shiwu = Weight_Shiwu - Weight_Maopi;		//获取净重
	
	Weight_Shiwu = (unsigned int)((float)Weight_Shiwu/GapValue); 	//计算实物的实际重量																
  return Weight_Shiwu;
}
#endif

/********************HRSR04 *********************/
#if CONFIG_HRSR04 == ENABLED
sbit Trig_P    = P2^2;		// 超声波模块的Trig管脚
sbit Echo_P    = P2^3;		// 超声波模块的Echo管脚
/*********************************************************/
// 毫秒级的延时函数，time是要延时的毫秒数
/*********************************************************/
void HRSR04_DelayMs(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}
void HRSR04_Timer_init()
{
		TMOD = 0x01;											// 选择定时器0，并且确定是工作方式1（为了超声波模块测量距离计时用的）
}

unsigned int GetDistance(void)
{
	unsigned int ss;					// 用于记录测得的距离
	//uart那边开启了TR0不知道为什么
	TR0=0;
	TH0=0;
	TL0=0;

	Trig_P=1;					// 给超声波模块一个开始脉冲
	HRSR04_DelayMs(1);
	Trig_P=0;

	while(!Echo_P);		// 等待超声波模块的返回脉冲
	TR0=1;						// 启动定时器，开始计时
	while(Echo_P);		// 等待超声波模块的返回脉冲结束
	TR0=0;						// 停止定时器，停止计时

	ss=((TH0*256+TL0)*0.034)/2;		// 距离cm=（时间us * 速度cm/us）/2

	return ss;
}

/* 
HRSR04_Timer_init();  
while(1)
{
	...
	Distanc = GetDistance();
}
*/
#endif

/********************MP3_TF_16P *********************/
#if CONFIG_MP3_TF == ENABLED
sbit voice_busy = P2^0;
unsigned char a;

//9600bps
void uart_init()
{
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
	TI = 1;
	
	//TH0=0x4c;
	//TL0=0x00;	  //装载定时器1数据
	//TR0=1;		  //开始定时
	//ET0=1;		  //是能定时器1

}

void UartSendByte(unsigned char byte)
{
	SBUF = byte;
	while(!TI);
		TI = 0;
}


void UartSendString(unsigned char *string)
{
	while(*string)
	{
		UartSendByte(*string++);
	}
}


void ser() interrupt 4
{
	RI = 0;
	a = SBUF;
}

static unsigned char Send_buf[10] = {0} ;
static unsigned char Recv_buf[10] = {0} ;

static unsigned char SendDataLen = 0 ;
static unsigned char ResendDataLen = 0 ;


/*****************************************************************************************************
 - 功能描述：
 - 隶属模块：
 - 参数说明：
 - 返回说明：
 - 注：
*****************************************************************************************************/

/*****************************************************************************************************
 - 功能描述：串口发送一帧数据

*****************************************************************************************************/


void SendCmd(unsigned char len)
{
    unsigned char i = 0 ;

    //UartSendByte(0x7E); //??
    //UartSendByte(0xff); //??	
		//UartSendByte(0x7e);
    for(i=0; i<len; i++)//??
    {
		UartSendByte(Send_buf[i]) ;
    }
    //UartSendByte(0xEF) ;//??
}

/*****************************************************************************************************
 - 功能描述：求和校验
 - 隶属模块：
 - 参数说明：
 - 返回说明：
 - 注：				和校验的思路如下
							发送的指令，去掉起始和结束。将中间的6个字节进行累加，最后取反码
							接收端就将接收到的一帧数据，去掉起始和结束。将中间的数据累加，再加上接收到的校验
							字节。刚好为0，这样就代表接收到的数据完全正确
*****************************************************************************************************/

void DoSum( unsigned char *Str, unsigned char len)
{
    unsigned int xorsum = 0;
    unsigned char i;

    for(i=0; i<len; i++)
    {
        xorsum  = xorsum + Str[i];
    }
	xorsum     = 0 -xorsum;
	*(Str+i)   = (unsigned char)(xorsum >>8);
	*(Str+i+1) = (unsigned char)(xorsum & 0x00ff);
}


/*****************************************************************************************************
 - 功能描述：串口向外发送命令【包括控制和查询】
 - 隶属模块：外部
 - 参数说明：CMD：表示控制指令，请查询指令表，还包括查询的相关指令
							feedback：是否需要应答[0：不需要应答，1：需要应答]
							data：传送的参数
 - 返回说明：
 - 注：
*****************************************************************************************************/


void Uart_SendCMD(unsigned char CMD ,unsigned char feedback , unsigned int dat)
{
		TR0 = 0;
		while(voice_busy == 0);
    Send_buf[0] = 0x7e;    //保留字节
    Send_buf[1] = 0xff;    //保留字节
    Send_buf[2] = 0x06;    //长度
    Send_buf[3] = CMD;     //控制指令
    Send_buf[4] = feedback;//是否需要反馈
    Send_buf[5] = (unsigned char)(dat >> 8);//datah
    Send_buf[6] = (unsigned char)(dat);     //datal
		Send_buf[9] = 0xef;
    DoSum(&Send_buf[1],6);        //校验
    SendCmd(10);       //发送此帧数据
		TR0 =1;
}
//****************************************************
//MS延时函数(12M晶振下测试)
//****************************************************
void Delay_ms(unsigned int n) {
    unsigned int  i,j;
    for(i=0; i<n; i++)
        for(j=0; j<123; j++);
}
/* demo
	//串口初始化
	uart_init();
	EA = 1;
		//语音提示
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x03,0,VOICE_INIT);//欢迎使用语音电子称
	Delay_ms(500);
	while(1)
	{
		...
		Uart_SendCMD(0x03,0,(dat/100));//百位
		Delay_ms(100);
		Uart_SendCMD(0x03,0,12);//百
		Delay_ms(100);		
	}
*/
#endif

/********************SHT11 *********************/
#if CONFIG_SHT11 == ENABLED
#define noACK 0				//继续传输数据，用于判断是否结束通讯
#define ACK   1             //结束数据传输；
							//地址  命令  读/写
#define STATUS_REG_W 0x06   //000   0011    0
#define STATUS_REG_R 0x07   //000   0011    1
#define MEASURE_TEMP 0x03   //000   0001    1
#define MEASURE_HUMI 0x05   //000   0010    1
#define RESET        0x1e   //000   1111    0
//写字节程序
char s_write_byte(unsigned char value)   
{ 
	unsigned char i,error=0; 
	for (i=0x80;i>0;i>>=1)             //高位为1，循环右移
	{ 
		if (i&value) DATA=1;          //和要发送的数相与，结果为发送的位
    	else DATA=0;                        
    	SCK=1;                          
    	_nop_();_nop_();_nop_();        //延时3us 
    	SCK=0;
	}
	DATA=1;                           //释放数据线
	SCK=1;                            
	error=DATA;                       //检查应答信号，确认通讯正常
	_nop_();_nop_();_nop_();
	SCK=0;        
	DATA=1;
	return error;                     //error=1 通讯错误
}
//读字节程序
char s_read_byte(unsigned char ack)
{ 
	unsigned char i,val=0;
	DATA=1;                           //释放数据线
	for(i=0x80;i>0;i>>=1)             //高位为1，循环右移
	{ 
		SCK=1;                         
    	if(DATA) val=(val|i);        //读一位数据线的值 
    	SCK=0;       
	}
	DATA=!ack;                        //如果是校验，读取完后结束通讯；
	SCK=1;                            
	_nop_();_nop_();_nop_();          //延时3us 
	SCK=0;   
	_nop_();_nop_();_nop_();       
	DATA=1;                           //释放数据线
	return val;
}
//启动传输
void s_transstart(void)
// generates a transmission start 
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
{ 
   	DATA=1; SCK=0;                   //准备
   	_nop_();
  	SCK=1;
   	_nop_();
   	DATA=0;
   	_nop_();
  	SCK=0; 
  	 _nop_();_nop_();_nop_();
   	SCK=1;
   	_nop_();
  	DATA=1;     
  	_nop_();
   	SCK=0;     
}
//连接复位
void s_connectionreset(void)
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
{ 
	unsigned char i; 
	DATA=1; SCK=0;                    //准备
	for(i=0;i<9;i++)                  //DATA保持高，SCK时钟触发9次，发送启动传输，通迅即复位
	{ 
		SCK=1;
    	SCK=0;
	}
	s_transstart();                   //启动传输
}
//软复位程序
char s_softreset(void)
// resets the sensor by a softreset 
{ 
	unsigned char error=0; 
	s_connectionreset();              //启动连接复位
	error+=s_write_byte(RESET);       //发送复位命令
	return error;                     //error=1 通讯错误
}          
//温湿度测量
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode)
// 进行温度或者湿度转换，由参数mode决定转换内容；
{ 
//	enum {TEMP,HUMI};		 //已经在头文件中定义
	unsigned error=0;
	unsigned int i;

	s_transstart();                   //启动传输
	switch(mode)                     //选择发送命令
    {	
		case TEMP : error+=s_write_byte(MEASURE_TEMP); break;		   //测量温度
    	case HUMI : error+=s_write_byte(MEASURE_HUMI); break;		   //测量湿度
    	default     : break; 
	}
	for (i=0;i<65535;i++) if(DATA==0) break; //等待测量结束
	if(DATA) error+=1;                // 如果长时间数据线没有拉低，说明测量错误 
	*(p_value) =s_read_byte(ACK);    //读第一个字节，高字节 (MSB)
	*(p_value+1)=s_read_byte(ACK);    //读第二个字节，低字节 (LSB)
	*p_checksum =s_read_byte(noACK); //read CRC校验码
	return error;					 // error=1 通讯错误
}
//温湿度值标度变换及温度补偿
void calc_sth10(float *p_humidity ,float *p_temperature)
{ 
	
	const float C1=-8.0;              // 12位湿度精度 修正公式
	const float C2=+0.0405;           // 12位湿度精度 修正公式
	const float C3=-0.0000028;        // 12位湿度精度 修正公式
	const float T1=+0.01;             // 14位温度精度 5V条件  修正公式
	const float T2=+0.00008;          // 14位温度精度 5V条件  修正公式
	
	float rh=*p_humidity;             // rh:      12位 湿度 
	float t=*p_temperature;           // t:       14位 温度
	float rh_lin;                     // rh_lin: 湿度 linear值
	float rh_true;                    // rh_true: 湿度 ture值
	float t_C;                        // t_C   : 温度 ℃
	
	t_C=t*0.01 - 40;                  //补偿温度
	rh_lin=C3*rh*rh + C2*rh + C1;     //相对湿度非线性补偿
	rh_true=1*(T1+T2*rh)+rh_lin;   //相对湿度对于温度依赖性补偿
	if(rh_true>100)rh_true=100;       //湿度最大修正
	if(rh_true<0.1)rh_true=0.1;       //湿度最小修正

	*p_temperature=t_C;               //返回温度结果
	*p_humidity=rh_true;              //返回湿度结果
}

/*demo
void main()
{
	unsigned int temp,humi;		//定义温度和湿度变量
	value humi_val,temp_val;		//定义两个共同体，一个用于湿度，一个用于温度
	unsigned char error;		    //用于检验是否出现错误
	unsigned char checksum;			//CRC			 
	uchar wendu[6];				 	//用于记录温度
	uchar shidu[6];				 	//用于记录湿度	
	value humi_val,temp_val;		//定义两个共同体，一个用于湿度，一个用于温度
	while(1)
	{
		error=0;					   //初始化error=0，即没有错误
		error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP); //温度测量
		error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI); //湿度测量
    if(error!=0) 
			s_connectionreset();                 ////如果发生错误，系统复位		
		else
		{
				humi_val.f=(float)humi_val.i;                   //转换为浮点数
     		temp_val.f=(float)temp_val.i;                   //转换为浮点数
     		calc_sth10(&humi_val.f,&temp_val.f);            //修正相对湿度及温度
//   		dew_point=calc_dewpoint(humi_val.f,temp_val.f); //计算e dew_point
   			temp=temp_val.f*10;
     		humi=humi_val.f*10;		
		}
	}

}


*/

#endif

/********************DHT11 *********************/
#if CONFIG_DHT11 == ENABLED

unsigned char U8FLAG,U8temp,U8comdata;

void Delay(unsigned int j)
{      
	unsigned char i;
	for(;j>0;j--)
	{ 	
		for(i=0;i<27;i++);
	}
}
void  Delay_10us(void)
{
	unsigned char i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
}
	
void  COM(void)			//
{

	unsigned char i;

	for(i=0;i<8;i++)	   
	{

		U8FLAG=2;	
		while((!DTH_PIN)&&U8FLAG++);
		Delay_10us();
		Delay_10us();
		Delay_10us();
		U8temp=0;
		if(DTH_PIN)U8temp=1;
		U8FLAG=2;
		while((DTH_PIN)&&U8FLAG++);
		//超时则跳出for循环		  
		if(U8FLAG==1)break;
		//判断数据位是0还是1	 

		// 如果高电平高过预定0高电平值则数据位为 1 

		U8comdata<<=1;
		U8comdata|=U8temp;        //0
	}//rof

}

	//--------------------------------
	//-----湿度读取子程序 ------------
	//--------------------------------
	//----以下变量均为全局变量--------
	//----温度高8位== U8T_data_H------
	//----温度低8位== U8T_data_L------
	//----湿度高8位== U8RH_data_H-----
	//----湿度低8位== U8RH_data_L-----
	//----校验 8位 == U8checkdata-----
	//----调用相关子程序如下----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

char DHT11_RH(unsigned char* arry)
{
	unsigned char U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
	//主机拉低18ms 
	DTH_PIN=0;
	Delay(180);
	DTH_PIN=1;
	//总线由上拉电阻拉高 主机延时20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//主机设为输入 判断从机响应信号 
	DTH_PIN=1;
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	if(!DTH_PIN)		 //T !	  
	{
		U8FLAG=2;
		//判断从机是否发出 80us 的低电平响应信号是否结束	 
		while((!DTH_PIN)&&U8FLAG++);
		U8FLAG=2;
		//判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		while((DTH_PIN)&&U8FLAG++);
		//数据接收状态		 
		COM();
		U8RH_data_H_temp=U8comdata;
		COM();
		U8RH_data_L_temp=U8comdata;
		COM();
		U8T_data_H_temp=U8comdata;
		COM();
		U8T_data_L_temp=U8comdata;
		COM();
		U8checkdata_temp=U8comdata;
		DTH_PIN=1;
		//数据校验 

		U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
		if(U8temp==U8checkdata_temp)
		{
			arry[0]=U8RH_data_H_temp;
			arry[1]=U8RH_data_L_temp;
			arry[2]=U8T_data_H_temp;
			arry[3]=U8T_data_L_temp;
			return TRUE;
		//U8checkdata=U8checkdata_temp;
		}else
			return FALSE;
	}//fi
	return FALSE;
}
/*Demo	
unsigned char RH_Value[4];
while(1)
{
	if(DHT11_RH(RH_Value) == TRUE)
	{
		Lcd1602_Display_Three_bit(0,0,RH_Value[0]);//读出温湿度，只取整数部分
		Lcd1602_Display_Three_bit(1,0,RH_Value[2]);
	}
}
*/
#endif


/********************LCD12864 *********************/
#if CONFIG_LCD12864_LIB == ENABLED

/********************************************
Description:  LCD12864 驱动 ,采用串行方式,
********************************************/ 


#define BIT(n)	(1<<(n))
#define SID_0   Lcd_Rw=0;
#define SID_1   Lcd_Rw=1; 
#define SCLK_0  Lcd_En=0;
#define SCLK_1  Lcd_En=1; 
//15脚 PSB 接低电平

//函数  delay(uchar z)
//功能能  延时

void Delay1(unsigned char z)
{
	unsigned char a,b;
	for(a=z;a>0;a--)
	 for(b=200;b>0;b--);	
} 

void SendByte(unsigned char bye)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if((bye<<i)&0x80){SID_1;}
		else {SID_0;}
		SCLK_1;

		SCLK_0;

	}
}

void Lcd_WriteCom(unsigned char CMD)
{
	SendByte(0xf8);
	SendByte(CMD&0xf0);
	SendByte((CMD<<4)&0xf0);
      Delay1(20);
	  Delay1(20);
	  Delay1(20);
}

void Lcd_WriteDate(unsigned char Data)
{	SendByte(0xf8+2);
	SendByte(Data&0xf0);
	SendByte((Data<<4)&0xf0);
}

void LCDInit()
{/*	RST=0;
	delay1MS(50);
	RST=1;          */
	lcd_RS=1;
    Lcd_WriteCom(0x34);//功能设置，一次送8位数据，基本指令集
    Lcd_WriteCom(0x30);//0000,1100  整体显示，游标off，游标位置off
    Lcd_WriteCom(0x01);//0000,0001 清DDRAM
    Lcd_WriteCom(0x06);//0000,0010 DDRAM地址归位
    Lcd_WriteCom(0x0c);//1000,0000 设定DDRAM 7位地址000，0000到地址计数器AC//     
}

/*****************************
发送字符串
*****************************/
//void show_str(uchar const *s)//改AVR去掉const
void  Lcd_String(const unsigned char  *str)
{
 while(*str !='\0')
   { 
   		Lcd_WriteDate(*str++);

   }
}

void Lcd_Display2data(unsigned char line,unsigned char list,unsigned char Date)
{
		unsigned char i;
		 unsigned char ta[]={0,0,'\0'};	  //用一个数组来装数
	   list=list &0x07;			       //限制在 0-7列
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }
	 for(i=2;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 
void Lcd_Display3data(unsigned char line,unsigned char list,unsigned int Date)
{
		unsigned char i;
		 unsigned char ta[]={0,0,0,0,'\0'};	  //用一个数组来装数
	   list=list &0x07;			       //限制在 0-7列
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }
	 for(i=3;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 


 

 ////////////////////////////////////////////////////////////////////
//函数	  Lcd_init(uchar com)
//功能    精确屏幕显示字符串
//参数    line  液晶屏的第几行  list  第几个位置开始写 （最多8个列）  *p要写的字符串
void  Lcd_ShowSring(unsigned char line,unsigned char list,unsigned char *p)
{
	 switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }

	    Lcd_String(p);

}

/*demo

  LCDInit();	//lcd12864初始化
	Lcd_ShowSring(1,0,"棚内温湿度光照");
  Lcd_ShowSring(2,0,"温度:");
	Lcd_ShowSring(3,0,"湿度:");
	Lcd_ShowSring(4,0,"光度:");
	while(1);

*/
#endif


/********************ESP8266*********************/
#if CONFIG_ESP8266 == ENABLED
unsigned char a;
void us_delay(unsigned char t) 
{  
	while(t--); 
}  

void Esp8266_Delay_Ms(int cnt)
{
	unsigned char i, j;

	while(cnt--)
	{

		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
//*********主函数*****************
//9600bps
void ESP8266_uart_init()
{
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
	TI = 1;
}
void UartSendByte(unsigned char byte)
{
	SBUF = byte;
	while(!TI);
		TI = 0;
}


void UartSendString(unsigned char *string)
{
	while(*string)
	{
		UartSendByte(*string++);
	}
}


void ser() interrupt 4
{
	if(RI)
	{
		RI = 0;
		a = SBUF;
	}
}


/******************************************************************** 
名称：WIFI模块设置函数  作用: 启动模块，以便可以实现无线接入和控制  
********************************************************************/ 
void ESP8266_Set(unsigned char *puf) 
	{                        	// 数组指针*puf指向字符串数组
    while(*puf!='\0') 
		{  		//遇到空格跳出循环
        UartSendByte(*puf);  		//向WIFI模块发送控制指令。
        Esp8266_Delay_Ms(5);
        puf++;
    }
    Esp8266_Delay_Ms(5);
    UartSendByte('\r'); 			//回车
    Esp8266_Delay_Ms(5);
    UartSendByte('\n');   			//换行
}
void Esp8266_init()
{
		ESP8266_uart_init();
		Esp8266_Delay_Ms(100);
	  ESP8266_Set("AT+CWMODE=2"); 							//设置路由器模式1 station,模式2 AP,模式3 station+AP混合模式   设置前wifi的波特率设置成9600
    Esp8266_Delay_Ms(300);
    ESP8266_Set("AT+RST"); 									//重新启动wifi模块
    Esp8266_Delay_Ms(300);
//    ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  设置模块SSID:WIFI, PWD:密码 及安全类型加密模式（WPA2-PSK）
    ESP8266_Set("AT+CWSAP=\"wifi_yuxia\",\"12345678\",11,4");
    Esp8266_Delay_Ms(300);
//    ESP8266_Set("AT+CIPMUX=1");								//开启多连接模式，允许多个各客户端接入
    ESP8266_Set("AT+CIPMUX=1");								//开启单连接模式
    Esp8266_Delay_Ms(300);
    ESP8266_Set("AT+CIPSERVER=1,5000");  					//启动TCP/IP 实现基于网络//控制 	ESP8266_Set("AT+CIPSERVER=1,5000");
    Esp8266_Delay_Ms(500);
    ESP8266_Set("AT+CIPSTO=0"); 
    Esp8266_Delay_Ms(500);	
}
/**demo

unsigned char buff[30];
void EPS8266_Send(void)
{
	static unsigned char Cnt1 = 1;
  if(++Cnt1 == 20)
	{
		ESP8266_Set("AT+CIPSEND=0,34\r\n");	   ////发送字符长度  
	}else if(Cnt1 >= 40)
	{
		Cnt1 = 0;
		buff[0]= 'h';
		buff[1]= 'e';
		buff[2]= 'a';
		buff[3]= 'd';
		buff[4]= ':';
		buff[5]= Ad_dat/100%10+0x30;
		buff[6]= Ad_dat/10%10+0x30;
		buff[7]= Ad_dat%10+0x30;
		buff[8]= ',';
		buff[9]= Ad_dat2/100%10+0x30;
		buff[10]= Ad_dat2/10%10+0x30;
		buff[11]= Ad_dat2%10+0x30;
		buff[12]= ',';
		buff[13]= MaFlag+0x30;
		buff[14]= '5';
		buff[15]= ',';	
		buff[16]= 'e';	
		buff[17]= 'n';	
		buff[18]= 'd';
		UartSendString(buff);		
	}	
}

	Esp8266_init();
	while(1)
	{
		EPS8266_Send();
	}

**/
#endif

/********************ISD4004*********************/
#if CONFIG_ISD4004 == ENABLED

void delayms(unsigned char ms)// 延时子程序 
{      
	unsigned char j;
	while(ms--)
	{
		for(j = 0; j < 120; j++);
	}
}
bit flag_xh = 0;
////////////////放音部分子程序，放音地址由ADDR决定////
void play(unsigned int addr)
{
	unsigned char y;
	flag_xh = 0;
	SS=0;
	MOSI=0;//发送开始
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x20>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送结束
	SS=1;//上电结束
	delayms(50);
	SS=0;
	MOSI=0;//发送地址
	SCLK=0;
	for(y=0;y<16;y++)
	{
	SCLK=0;
	if((addr>>y)&0x01)MOSI=1;
	else MOSI=0;
	_nop_();
	_nop_();
	_nop_();
	SCLK=1;
	_nop_();
	_nop_();
	_nop_();
	}//发送地址结束
	MOSI=0;//放音
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xe0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
	SS=0;
	MOSI=0;//放音
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xf0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
	//	flag_xh = 1;	 
}	
//////////////////////////lu音部分子程序，地址由ADDR决定/////////////////////////
void rec(unsigned int addr)                
{
 	unsigned int y;	
	SS=0;
	MOSI=0;//发送开始
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x20>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送结束
	SS=1;//上电结束
	delayms(50);
	SS=0;
	MOSI=0;//发送开始
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x20>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送结束
	SS=1;//上电结束
	delayms(50);
	delayms(50);
	SS=0;
	MOSI=0;//发送地址
	SCLK=0;
	for(y=0;y<16;y++)
	{
		SCLK=0;
		if((addr>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送地址结束
	MOSI=0;
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xa0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
	SS=0;
	MOSI=0;
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xb0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;	  }

////////////////////////////////////
////////////////////////////////
void stop()
{ 
  unsigned char y;
	SS=1;
	SS=0;
	MOSI=0;//放音
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x30>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
}

/*demo
play(ADDR4STR);

*/
#endif

/********************fuzzify*********************/
#if CONFIG_FUZZIFY == ENABLED
//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
// 定义差距输入常量
#define GAP_ZERO     0x00
#define GAP_VSMALL   0x01
#define GAP_SMALL    0x02
#define GAP_MEDIUM   0x03
#define GAP_BIG      0x04
// 定义控制输出常量
#define TURN_ZERO    0x80
#define TURN_VSMALL  0x81
#define TURN_SMALL   0x82
#define TURN_MEDIUM  0x83
#define TURN_BIG     0x84



//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
//unsigned char Temp_H,Temp_L;

//unsigned int sum;			  //10次AD值的综合变量
//unsigned char RH,RH_H=12,RH_L=8,state,ms,cs;  //当前水位，  水位上限，下限，  设置项变量，50ms变量   ，cs 为计次数变量    ，
//bit beep1,zt,s1;	  //报警标志位，   工作模式标志位，   闪烁标志位

//int Temperature;
 


//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
//-------------定义常量----------------------------------------------------------------
#define MU_MAX 0XFF            //模糊度的最大值为0XFF代表面1
#define RULE_TOT 10            //规则数个数
#define MF_TOT 5               //成员函数的个数
#define IO_NUM 0x07
#define LABEL_NUM 0x70
#define DEFAULT_VALUE 0x00
//----------------定义数据库-----------------------------------------------------------
unsigned char code output_memf[MF_TOT]={0, 15, 35, 60, 102};// OUTPUT TURNING NUMBER:
                                                            // ZERO, VSMALL, SMALL, MEDIUM, BIG
                                                            // 输入功能函数以点斜式方式存储. 第一维成员函数标号第二维是点斜式数据
unsigned char code input_memf[MF_TOT][4]={                  //距离功能函数
                                            { 0x00, 0x00, 0x00, 0x0d }, // VSLOW
                                            { 0x00, 0x0d, 0x14, 0x0d }, // SLOW
                                            { 0x1e, 0x0d, 0x32, 0x0d }, // MEDIUM
                                            { 0x3C, 0x0d, 0x50, 0x0d }, // FAST
                                            { 0x50, 0x09, 0x6e, 0x00 }  // VFAST
                                          };

//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
//-----------定义模糊系统规则-----------------------------------------------------------
unsigned char code rules[RULE_TOT]={ 
                                        // if...  then...
                                        GAP_ZERO,TURN_ZERO,
                                        GAP_VSMALL,TURN_VSMALL,
                                        GAP_SMALL,TURN_SMALL,
                                        GAP_MEDIUM,TURN_MEDIUM,
                                        GAP_BIG,TURN_BIG
                                   };


 //-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
 //-----------定义各变量-----------------------------------------------------------------
unsigned char outputs[MF_TOT],fuzzy_out;  //模糊输出mu值
//-----------子程序函数头申明-----------------------------------------------------------
void fuzzy_engine(unsigned char);
unsigned char compute_memval(unsigned char,unsigned char);
void defuzzify(void);

/***************************************************************************************************************/
unsigned char compute_memval(unsigned char input,unsigned char label)
 {
    int data temp;
    if (input < input_memf[label][0])
    {                                 // 如果输入不在曲线下u值为0
         return 0;
    }
    else
    {
        if (input < input_memf[label][2])
        {
             temp=input;              // 用点斜式计算mu
             temp-=input_memf[label][0];
             if (!input_memf[label][1])
             {
                temp=MU_MAX;
             }
             else
             {
                temp*=input_memf[label][1];
             }
             if (temp < 0x100)
             {                     // 如果结果不超过1
                return temp;       // 返回计算结果
             }
             else
             {
                return MU_MAX;     // 确保mu值在范围内
             }
        }
        else
        {                           // 输入落在第二条斜线上
            temp=input;               // 用点斜式方法计算 mu
            temp-=input_memf[label][2];
            temp*=input_memf[label][3];
            temp=MU_MAX-temp;
            if (temp < 0)
            {                      // 确保结果不小于0
                  return 0;
            }
            else
            {
                  return temp;        // mu为正 – 返回结果
            }
        }
    }
    return 0;
}
/*******************************************************************************
Function: defuzzify
Description: 计算模糊输出的重心并调用函数把它
             转换成可被系统使用的输出量
Parameters: 无.
Returns: 无.
Side Effects: outputs[][] 数组被清零.
*******************************************************************************/
void defuzzify(void)
{
    unsigned long numerator, denominator;
    unsigned char j;
    numerator=0;                         // 恢复总数值
    denominator=0;
    for (j=0; j<MF_TOT; j++)
    {                                // 计算总和值
        numerator+=(outputs[j]*output_memf[j]);
        denominator+=outputs[j];
        outputs[j]=0;                        // 清零输出作为参考使用
        if (denominator)
        {                                     // 确保分母是0的情况不发生
            fuzzy_out=numerator/denominator;  // 确定 COG
        }
        else
        {
            fuzzy_out=DEFAULT_VALUE;         // 没有规则被触发
        }
    }
}
/*******************************************************************************
Function: fuzzy_engine
Description: 实施规则基中的规则
Parameters: 无
Returns: 无.
Side Effects: 无
********************************************************************************/
unsigned char bdata clause_val;                        // 保存当前的分支进行快速访问
sbit clause_type = clause_val^7;                       // 表示分支是否是条件分支或者是结果分支
void fuzzy_engine(unsigned char input)
{
    bit then;                                       // 当正在分析结果时置位
    unsigned char if_val,                           // 保存当前规则中条件分支中的值
                  clause,                           // 规则基中当前的分支
                      mu,                           // 保存当前分支中的值
                 label=0;                           // 被条件使用的成员函数
                  then=0;                           // 设第一个分支是条件分支
           if_val=MU_MAX;                           // max out mu for the first rule
    for (clause=0; clause<RULE_TOT; clause++)
    {                                               // 遍历每条规则
        clause_val=rules[clause];                   // 读入当前的分支
        if (!clause_type)
        {                                           // 当前的分支是不是条件分支
            if (then)
            {                                       // 是否正在分析结果...
                then=0;
                if_val=MU_MAX;                      // 复位mu
            }
            mu=compute_memval(input, label);        // 得到条件分支的值
            if_val=mu;
            label++;
        }
        else
        {                                       // 当前分支是结果
            then=1;            // 置位标志位,如果当前规则的mu比参考的值要大,保存这个值作为新的模糊输出
            if (outputs[clause_val&0x07] < if_val)
            {
                outputs[clause_val&0x07]=if_val;
            }
        }
    }
    defuzzify(); // 用COG方法计算模糊输出和反模糊输出
 }

/*demo
		if(Temperature <= Temp_L)//小于设定值时，采用模糊计算
		{
						
		 //模糊计算
			fuzzy_engine((Temp_L - Temperature)*10);
		 
		 if(fuzzy_out)  //根据模糊计算结果，处理输出状态
		 {
				LED_3_BUF = led_3=0;		//显示对应的指示灯
		 }
		 else
		 {
			 LED_3_BUF = led_3=0;		//显示对应的指示灯 
		 }		
			
		} 
 
 */
#endif

/********************EX0_EX1*********************/
#if CONFIG_EX0_EX1 == ENABLED

static EX0_1_Process EX0_Process;
static EX0_1_Process EX1_Process;
void EX0_INIT(EX0_1_Process T_Process)
{
	EX0=1;     //开中断0
	IT0=1;     //中断0为边沿触发
	EA=1;     //开总中断
	EX0_Process = T_Process;
}

void EX1_INIT(EX0_1_Process T_Process)
{
	EX1=1;     //开中断0
	IT1=1;     //中断0为边沿触发
	EA=1;     //开总中断
	EX1_Process = T_Process;
}


//外部0中断子函数
void wb0() interrupt 0  //比赛时间开始/暂停
{
	EX0_Process();
}
//外部1中断子函数
void wb1() interrupt 2   //24s倒计时重新开始
{
	EX1_Process();
}
/*DEMO

sbit LED0 = P1^1;
sbit LED1 = P1^2;
void Ex0_Process()
{
	LED0 = ~LED0;
}
void Ex1_Process()
{
	LED1 = ~LED1;
}
void main()
{
	EX0_INIT(Ex0_Process);
	EX1_INIT(Ex1_Process);
	while(1)
	{

	}
}

*/
#endif

/********************LCD12864*********************/
#if CONFIG_LCD12864 == ENABLED



//延时函数
void delay(unsigned char t)
{
	unsigned char i,j;
	for(i=0;i<t;i++)
		for(j=0;j<10;j++);
}

//写命令函数
void write_com(unsigned char cmdcode)
{
	Di=0;
	RW=0;
	P0=cmdcode;		
	delay(2);
	Enable=1;
	delay(2);
	Enable=0;
}
//写数据函数
void write_data(unsigned char Dispdata)
{
	Di=1;
	RW=0;
	P0=Dispdata;
	delay(2);
	Enable=1;
	delay(2);
	Enable=0;
}

//清屏函数
void Lcd_Clr()
{
	unsigned char j,k;
	cs1=1;cs2=1;
 	write_com(Page_Add+0);
 	write_com(Col_Add+0);
 	for(k=0;k<8;k++)
 	{
		write_com(Page_Add+k);
  		for(j=0;j<64;j++)write_data(0x00);
	}
	cs1=0;cs2=0;
}

/****************************************
定位函数，定位一个字，
其中pag为行数0~3，
col为列数，col=16i，i=0~8
*hzk为要显示的内容；
****************************************/
void hz_disp16(unsigned char pag,unsigned char col, unsigned char code *hzk)
{
	unsigned char j=0,i=0;
	for(j=0;j<2;j++)
	{
		write_com(Page_Add+pag+j);
		write_com(Col_Add+col);
		for(i=0;i<16;i++) 
		write_data(hzk[16*j+i]);
	}
}

/****************************************
定位函数，定位一个字节，
其中pag为行数0~3，
col为列数，col=8i，i=0~16
*hzk为要显示的内容；
****************************************/
void hz_disp8(unsigned char pag,unsigned char col, unsigned char code *hzk)
{
	unsigned char j=0,i=0;
	for(j=0;j<2;j++)
	{
		write_com(Page_Add+pag+j);
		write_com(Col_Add+col);
		for(i=0;i<8;i++) 
		write_data(hzk[8*j+i]);
	}
			
}

//lcd初始化函数
void Lcd_Init()
{
	delay(100);
	cs1=1;
	cs2=1;
	delay(100);
	write_com(0x83);
	write_com(Disp_Off);
	write_com(Page_Add+0);
	write_com(Start_Line+0);
	write_com(Col_Add+0);
	write_com(Disp_On);

}

/*demo

//盆花自动浇水系统
char code pen[]={
0x20,0x20,0x10,0x08,0x94,0x72,0x10,0x90,0x13,0xF4,0x08,0x10,0x20,0x60,0x20,0x00,
0x40,0x40,0x7D,0x45,0x44,0x7C,0x44,0x44,0x45,0x7C,0x44,0x44,0x7E,0x44,0x40,0x00
};

char code jiao[]={
0x10,0x21,0x62,0x06,0x80,0x08,0x88,0x8B,0x5C,0x24,0x54,0x84,0x86,0xE4,0x00,0x00,
0x04,0x04,0xFE,0x01,0x80,0x82,0x42,0x3E,0x02,0x02,0x7E,0x82,0x82,0x82,0xE0,0x00
};


//显示‘0’，‘1’，‘2’，‘3’，‘4’，‘5’，‘6’，‘7’，‘8’，‘9’
char code base_num[][16]={
//'0'
{0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00},
//'1'
{0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},
//'2'
{0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00},
//'3'
{0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00},
//'4'
{0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00},
//'5'
{0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00},
//'6'
{0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00},
//'7'
{0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00},
//'8'
{0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00},
//'9'
{0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00},

{0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x37,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,0x00},

};
	unsigned int temp,humi;		//定义温度和湿度变量
	value humi_val,temp_val;		//定义两个共同体，一个用于湿度，一个用于温度
	unsigned char error;		    //用于检验是否出现错误
	unsigned char checksum;			//CRC			 
	unsigned char  wendu[6];				 	//用于记录温度
	unsigned char  shidu[6];				 	//用于记录湿度		
void System_Show()		//信息显示
{
	cs1=1;cs2=0;
	hz_disp16(0,0,pen);		//盆花自动

			 
	cs1=0;cs2=1;
	hz_disp16(0,0,jiao);	//浇水系统


}
void main()
{
	Lcd_Init();
	
	while(1)
	{
		error=0;					   //初始化error=0，即没有错误
		error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP); //温度测量
		error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI); //湿度测量
		if(error!=0)
			s_connectionreset();                 ////如果发生错误，系统复位
		else
		{ 		
		humi_val.f=(float)humi_val.i;                   //转换为浮点数
		temp_val.f=(float)temp_val.i;                   //转换为浮点数
		calc_sth10(&humi_val.f,&temp_val.f);            //修正相对湿度及温度
		//   		dew_point=calc_dewpoint(humi_val.f,temp_val.f); //计算e dew_point
		temp=temp_val.f*10;
		humi=humi_val.f*10;	

      		wendu[0]=(temp/1000)/1000;     		//温度百位 
      		wendu[1]=(temp%1000)/100;     	//温度十位	
   			  wendu[2]=(temp%100)/10;			//温度个位
      		wendu[3]=0x2E;						//小数点
   			  wendu[4]=temp%10;				//温度小数点后第一位		
			 
			    shidu[0]=(humi/1000)/1000;     		//湿度百位
      		shidu[1]=(humi%1000)/100;     	//湿度十位	
   			  shidu[2]=(humi%100)/10;			//湿度个位
      		shidu[3]=0x2E;						//小数点
   			  shidu[4]=humi%10;				//湿度小数点后第一位	 

					cs1=0;cs2=1;
					hz_disp8(2,0,base_num[wendu[0]]);	//显示温度
					hz_disp8(2,8,base_num[wendu[1]]);
					hz_disp8(2,16,base_num[wendu[2]]);
					hz_disp8(2,24,base_num[14]);
					hz_disp8(2,32,base_num[wendu[4]]);
					hz_disp8(2,40,base_num[12]);

					hz_disp8(4,0,base_num[shidu[0]]);	//显示湿度
					hz_disp8(4,8,base_num[shidu[1]]);
					hz_disp8(4,16,base_num[shidu[2]]);
					hz_disp8(4,24,base_num[14]);
					hz_disp8(4,32,base_num[shidu[4]]);
					hz_disp8(4 ,40,base_num[12]);

			
		System_Show();
		}
	}
}

*/
#endif

/********************IR_SEND*********************/
#if CONFIG_IRSEND == ENABLED


//红外发射管的亮灭控制
static bit OP;
//延时计数器
static unsigned int count;
//终止延时计数器
static unsigned int endcount;
//红外发送标志
static unsigned char flag;
//16位地址 第一字节
char iraddr1;
//16位地址 第二字节
char iraddr2;

void time0_init()
{
	//总中断开
	EA=1;
	//设置定时器0和1为16位模式
	TMOD=0x11;
	//定时器0中断允许
	ET0=1;
	//设定定时大小 38K 等加于 26us中断一次             
	TH0=0xff;
	TL0=0xe6;
	//开始计数
	TR0=1;	
}


//定时器0中断处理函数
void timeint(void) interrupt 1
{
	//设定定时器初值
	TH0=0xff;
	TL0=0xe6;
	
	//中断计数累加
	count++;
	if(flag==1)
	{
		OP=1;
	}
	else
	{
		OP=0;
	}
	HL=OP;
}


//发送数据函数
//发送的延时时间参数即(endcount)都是在12MHZ的值
void SendIRdata(char p_irdata)
{
	int i;
	char irdata=p_irdata;
	
	//发送9ms的起始码
	endcount=223;
	flag=1;
	count=0;
	while(count<endcount);

	//发送4.5ms的结果码
	endcount=117;
	flag=0;
	count=0;
	do{}while(count<endcount);

	//发送16位地址的前八位
	irdata=iraddr1;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}

	//发送16位地址的后八位
	irdata=iraddr2;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}


	//发送8位数据
	irdata=p_irdata;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}


	//发送8位数据反码
	irdata=~p_irdata;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}
	//结束信息
	endcount=13;
	flag=1;
	count=0;
	do{}while(count<endcount);
	flag=0;
}

void IR_init()
{
	//初始化
	count=0;
	flag=0;
	OP=0;
	HL=0;
  time0_init();	
	//写16位地址
	iraddr1=0;
	iraddr2=255;
}


#endif

#if CONFIG_DS18B20_MULT== ENABLED

bit first =1;
idata unsigned char ID[MAXNUM][8];
unsigned char num=0;
unsigned char temp_l,temp_h,temp_over,t; 
bit negetiveflag=0;
signed char tempalarm=0;
void delay_nus(unsigned int n)//?? ?? ??8+6(??)=14us
{
	while(n--);
}

void reset(void)  //ds18b20???????
{
	 unsigned char x=0;
	 DQ = 1;          	//DQ??
	 delay_nus(8);  	//????
	 DQ = 0;          	//????DQ??
	 delay_nus(80); 	//???? ?? 480us
	 DQ = 1;          	//????
	 delay_nus(10);
	 x=DQ;            	//????? ??x=0?????? x=1??????
	 delay_nus(5);
}

void write_bit(unsigned char dat)	//DS18B20 ??? ??
{
  	DQ = 0;
	_nop_();
    _nop_();
 	DQ = dat&0x01;
    delay_nus(5);
 	DQ = 1;
}

void write_byte(unsigned char dat)//?????
{
 	unsigned char i,j;
 	for (i=8; i>0; i--)
 	{
		j=dat&0x01;
  		write_bit(j);
		dat>>=1;
    }
}

unsigned char read_2bit(void)//??? ???
{
	unsigned char i;
	unsigned char dat = 0;
	for (i=2;i>0;i--)
	{
		DQ = 0; // ?????
		dat<<=1;
		DQ = 1; // ?????
		if(DQ)
		dat|=0x01;
		delay_nus(4);
	}
 	return(dat);
}

unsigned char read_byte(void)//????? ???
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ = 0; // ?????
		dat>>=1;
		DQ = 1; // ?????
		if(DQ)
		dat|=0x80;
		delay_nus(4);
	}
 	return(dat);  
}
void delay_nms(unsigned int n)
{
	unsigned int j=0;
	unsigned char i=0;
	for(j=0;j<n;j++)
	{
		for(i=0;i<120;i++)
		{
			_nop_();
		}
	}
}


void read_temp(unsigned char num_data)//???? ??? ???????????
{
	unsigned char f;	
	reset();
	write_byte(0xcc);//????ROM???
	write_byte(0x44);//????????
	if(first)
	{
		first =0;
		delay_nms(2000);
	}
	else
		delay_nms(100);		
	reset();
	write_byte(0x55);//????ROM???
	for(f=0;f<8;f++) //8??ROM?
	{
		write_byte(ID[num_data][f]);//???ROM
	}
	
	delay_nus(100);
	write_byte(0xbe);//??????
	delay_nus(100);
	temp_l=read_byte();
	temp_h=read_byte();
}

 
void temp_convert(void)//????
{
	negetiveflag=0;
	negetiveflag=temp_h&0x80;
	if(negetiveflag)
	{
		negetiveflag=1;
		temp_h=~temp_h;
  		if(temp_l==0)
		{
		 	temp_h++;  //??8???0?????,?????????1
		}
  		temp_l=~temp_l+1; 
	}
	temp_h<<=4;
	temp_l>>=4;
	temp_over=temp_h|temp_l;
	tempalarm=temp_over;
	if(negetiveflag==1)
	{
		 tempalarm=tempalarm*(-1);
	}
}
void display_total(void)	  //??????DS18B20?????
{
	//Lcd1602_Display_String(0,0,"total num :");
	//Lcd1602_Display_Two_bit(0,10,num);
}
/***********************????ROM*****************************/
void search_rom(void)//??ROM
{ 
	unsigned char k=0,l=0,chongtuwei=0,m=0,n=0;
	unsigned char s=0;
	unsigned char zhan[MAXNUM];
	unsigned char ss[64];
	do
	{
		reset();
		write_byte(0xf0);  //??ROM??	
		for(m=0;m<8;m++)
		{
			for(n=0;n<8;n++)
			{
				k=read_2bit();//?????
				k=k&0x03;   
				s>>=1;
				if(k==0x01)//01??????0 ?0 ???0?????
				{   		
					write_bit (0);
	    			ss[(m*8+n)]=0;
				}
				else if(k==0x02)//??????1 ?1 ???1?????
				{
					s=s|0x80;
					write_bit (1);
					ss[(m*8+n)]=1;
				}
				else if(k==0x00)//??????0  ???? ????? 
				{				//??????????0 ????????? ?????1
					chongtuwei=m*8+n+1;					
					if(chongtuwei>zhan[l])
					{						
						write_bit (0);
						ss[(m*8+n)]=0;												
						zhan[++l]=chongtuwei;						
					}
					else if(chongtuwei<zhan[l])
					{
						s=s|((ss[(m*8+n)]&0x01)<<7);
						write_bit (ss[(m*8+n)]);
					}
					else if(chongtuwei==zhan[l])
					{
						s=s|0x80;
						write_bit (1);
						ss[(m*8+n)]=1;
						l=l-1;
					}
				}
				else
				{
					goto loop;
				}
			}
			ID[num][m]=s;		
		}
		num++;
	}
	while(zhan[l]!=0&&(num<MAXNUM));		
loop:
	//search_cartoon();
	display_total();

}

void DS18B20_Processing(unsigned char *Temp_Value)
{
	static unsigned char i=0;

	ET0 = 0;					
	read_temp(i);   //??? i ?ds18b20 ???
	ET0 = 1;

	temp_convert(); //??????

	switch(i)
	{
		case 0:
			Temp_Value[0] = tempalarm;					
		break;

		case 1:
			Temp_Value[1] = tempalarm;

						
		break;			
		case 2:
			Temp_Value[2] = tempalarm;

		break;	

		case 3:
			Temp_Value[3] = tempalarm;

		break;	
		case 4:
			Temp_Value[4] = tempalarm;	

		break;							
	}
	i++;
	if(i >= num)
	i = 0;
}
#endif