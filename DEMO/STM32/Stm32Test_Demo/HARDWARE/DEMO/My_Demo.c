#include "My_Demo.h"
#include "My_Config.h"

#if CONFIG_LCD1602 == ENABLED


/*-----------------------------------------------
  名称：LCD1602
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：通过标准程序静态显示字符
  引脚定义如下：1-VSS 2-VDD 3-V0 4-RS 5-R/W 6-E 7-14 DB0-DB7 15-BLA 16-
              判忙函数
------------------------------------------------*/

/*------------------------------------------------
              写入命令函数
------------------------------------------------*/
void LCD_PORT_Demo(unsigned char com)
{
	if (com&0x01)
			D0=1;
	else
			D0=0;

	if (com&0x02)
			D1=1;
	else
			D1=0;

	if (com&0x04)
			D2=1;
	else
			D2=0;

	if (com&0x08)
			D3=1;
	else
			D3=0; 
	if (com&0x10)
			D4=1;
	else
			D4=0;

	if (com&0x20)
			D5=1;
	else
			D5=0;

	if (com&0x40)
			D6=1;
	else
			D6=0;

	if (com&0x80)
			D7=1;
	else
			D7=0; 	
}
 void LCD_Write_Com_Demo(unsigned char com) 
{

	delay_us(2500);
	RS =0;
	EN=0;	
	delay_us(5);
  EN=1;
  //delay_us(10);	
  LCD_PORT_Demo(com);

	delay_us(10);	
  EN=0;                   
	delay_us(400);	
	delay_ms(4);	
}

/*------------------------------------------------
              写入数据函数
------------------------------------------------*/
 void LCD_Write_Data_Demo(unsigned char Data) 
{

  delay_us(2500);
  RS=1;
  delay_us(30);	
  EN=1;
  //RW=0;
  LCD_PORT_Demo(Data);
  delay_us(10);	
  EN=0;                  
	delay_us(400);	
	delay_ms(4);	
  	
}

void LCD1602_GPIO_Config_Demo(void)
{
	
	GPIO_InitTypeDef LCD1602_GPIOStruct;
	//不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);	
	 
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8| GPIO_Pin_9 ;     //设置为开漏输出 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;//
	GPIO_Init(GPIOB,&LCD1602_GPIOStruct);
	
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15 ;     //设置为开漏输出 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;//GPIO_Speed_10MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA,&LCD1602_GPIOStruct);
	
	

	
	
}




void LCD1602_Init_Demo(void)
{
	  LCD1602_GPIO_Config_Demo();   //开启GPIO口
    LCD_Write_Com_Demo(0X38);  //16*2显示，5*7点阵，8位数据接口
    LCD_Write_Com_Demo(0x0C);  //显示器开，光标关闭
    LCD_Write_Com_Demo(0x06);  //文字不动，地址自动+1
    LCD_Write_Com_Demo(0x01);  //清屏

	
}


void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	LCD_Write_Data_Demo(0x30+date/10%10);
	LCD_Write_Data_Demo(0x30+date%10);	
}
void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	LCD_Write_Data_Demo(0x30+date/100%10);
	LCD_Write_Data_Demo(0x30+date/10%10);
	LCD_Write_Data_Demo(0x30+date%10);	
}
void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
		while(1)
		{
			if(*p == '\0')  break;
			LCD_Write_Data_Demo(*p);
			p++;
		}	
}

/*****************控制光标函数********************/
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date)
{		
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	if(date == 1)
		LCD_Write_Com_Demo(0x0f);     //显示光标并且闪烁	
	else 
		LCD_Write_Com_Demo(0x0c);   //关闭光标
}

 /*------------------------------------------------
                清屏函数
------------------------------------------------*/
 void LCD_Clear_Demo(void) 
 { 
 LCD_Write_Com_Demo(0x01); 
 delay_ms(5);
 }

/*------------------------------------------------*/
 
// D0  D1 D2 D3 D4 D5 D6 D7 E   RW RS
// A15 B3 B4 B5 B6 B7 B8 B9 A12    A11

#if CONFIG_DS1302 == ENABLED
/*********************************************************/
// 液晶输出数字
/*********************************************************/
void Ds13b02_DisPlay(unsigned char hang,unsigned char add,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add); 
	
	LCD_Write_Data_Demo(yue%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(yue%10+0x30);				// 个位
	LCD_Write_Data_Demo('-');
	LCD_Write_Data_Demo(ri%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(ri%10+0x30);				// 个位
	LCD_Write_Data_Demo(' ');	
	LCD_Write_Data_Demo(shi%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(shi%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(fen%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(fen%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(miao%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(miao%10+0x30);				// 个位

}

/*********************************************************/
// 液晶输出数字
/*********************************************************/
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add); 
	

	LCD_Write_Data_Demo(shi%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(shi%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(fen%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(fen%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(miao%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(miao%10+0x30);				// 个位

}
#endif
#if CONFIG_DS18b02 == ENABLED
void Lcd1602_Display_Ds18b02(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	LCD_Write_Data_Demo(0x30+date/100%10);
	LCD_Write_Data_Demo(0x30+date/10%10);
	LCD_Write_Data_Demo('.');
	LCD_Write_Data_Demo(0x30+date%10);	
}
#endif 
#endif
 
#if CONFIG_KEY == ENABLED
 
unsigned char Key_value_Demo(pKey_Process key_Process)	 //独立按键程序
{
	unsigned char Key_value;
#if KEY_COUNT == 1
	if(Demo_KEY1 == 0)
	{
		delay_ms(5);//去抖动 
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
		delay_ms(5);//去抖动 
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
	  delay_ms(5);//去抖动 
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
	  delay_ms(5);//去抖动 
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
	  delay_ms(5);//去抖动 
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
	  delay_ms(5);//去抖动 
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
	
	//if(a1=='A'){a1=0;Key_value=1;}
	//if(a1=='B'){a1=0;Key_value=2;}
	//if(a1=='C'){a1=0;Key_value=3;}	
	key_Process(Key_value);
	return Key_value;
}


void KEY_Init_Demo(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试

#if KEY_COUNT == 1

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 2
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 3
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 4
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 5
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 6
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif


	
} 
 
#endif
#if CONFIG_ADC == ENABLED

//内存中存储转换结果
vu16 ADC_ConvertedValue_Demo[Sample_Num_Demo][Channel_Num_Demo];
 
 
//DMA??:ADC1->CR --> ADC_ConvertedValue
void ADC_DMA_Config_Demo(void)
{
	 DMA_InitTypeDef DMA_InitStructure;
				   
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 DMA_DeInit(DMA1_Channel1);												//DMA的通道1寄存器设为缺省值
	 DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		//DMA外设ADC基地址
	 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue_Demo;		//DMA内存基地址
	 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//内存作为数据传输的目的地
	 DMA_InitStructure.DMA_BufferSize = Sample_Num_Demo*Channel_Num_Demo;				//DMA通道的DMA缓存大小
	 DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//外设地址不变
	 DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				//内存地址递增
	 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//DMA通道的DMA缓存大小
	 DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//DMA通道的DMA缓存大小
	 DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//工作在循环缓存模式
	 DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA通道x拥有高优先级
	 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;			//DMA通道x没有设置为内存到内存传输
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);			//
	 DMA_Cmd(DMA1_Channel1,ENABLE);
}
 
 
void ADC1_Config_Demo(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 ADC_InitTypeDef ADC_InitStructure;
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	   
	//PA0 通道0 PA1 通道1 PA2 通道2
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;		
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			//模拟输入
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 ADC_DMA_Config_Demo();
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6); 		//设置ADC分频因子6 72M/6=12M，ADC最大时间不能超过14M
	
	// ADC_DeInit(ADC1);
	 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//ADC1和ADC2工作在独立模式
	 ADC_InitStructure.ADC_ScanConvMode = ENABLE;							//多通道
	 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//连续转换
	 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//软件启动转换
	 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//转换结果右对齐
	 ADC_InitStructure.ADC_NbrOfChannel = Channel_Num_Demo;						//通道数
	 ADC_Init(ADC1, &ADC_InitStructure); 
 
	   
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	//
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
 
	   
	 ADC_DMACmd(ADC1, ENABLE);	   
	 ADC_Cmd(ADC1, ENABLE);
	 
	 ADC_ResetCalibration(ADC1);					
	 while(ADC_GetResetCalibrationStatus(ADC1));  	//
	 ADC_StartCalibration(ADC1);					//??AD??
	 while(ADC_GetCalibrationStatus(ADC1));			//
	 
	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//
}
 
 
uint16_t ReadADCAverageValue_Demo(uint16_t Channel)
{
	uint8_t i;
	uint32_t sum = 0;
	for(i=0; i<Sample_Num_Demo; i++)
	{
		sum+=ADC_ConvertedValue_Demo[i][Channel];		//
	}
	return (sum/Sample_Num_Demo);
}


#endif
 
#if CONFIG_OLED_4PIN == ENABLED

unsigned char OLED_GRAM_Demo[128][8]={0};

const unsigned char  zm8x16_index_Demo[]=
"0123456789: |-+<.^abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ_";//字串索引
const unsigned char  zm8x16_Table_Demo[][16]={
0x00,0x00,0x07,0xF0,0x08,0x08,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00,/*"0",0*/

0x00,0x00,0x00,0x00,0x08,0x04,0x08,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,/*"1",1*/

0x00,0x00,0x0E,0x0C,0x10,0x14,0x10,0x24,0x10,0x44,0x10,0x84,0x0F,0x0C,0x00,0x00,/*"2",2*/

0x00,0x00,0x0C,0x18,0x10,0x04,0x10,0x84,0x10,0x84,0x11,0x44,0x0E,0x38,0x00,0x00,/*"3",3*/

0x00,0x00,0x00,0x60,0x01,0xA0,0x02,0x24,0x0C,0x24,0x1F,0xFC,0x00,0x24,0x00,0x24,/*"4",4*/

0x00,0x00,0x1F,0x98,0x11,0x04,0x11,0x04,0x11,0x04,0x10,0x88,0x10,0x70,0x00,0x00,/*"5",5*/

0x00,0x00,0x07,0xF0,0x08,0x88,0x11,0x04,0x11,0x04,0x09,0x04,0x00,0xF8,0x00,0x00,/*"6",6*/

0x00,0x00,0x18,0x00,0x10,0x00,0x10,0x7C,0x11,0x80,0x16,0x00,0x18,0x00,0x00,0x00,/*"7",7*/

0x00,0x00,0x0E,0x38,0x11,0x44,0x10,0x84,0x10,0x84,0x11,0x44,0x0E,0x38,0x00,0x00,/*"8",8*/

0x00,0x00,0x0F,0x80,0x10,0x48,0x10,0x44,0x10,0x44,0x08,0x88,0x07,0xF0,0x00,0x00,/*"9",9*/

0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x03,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,/*":",10*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",11*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,/*"|",12*/

0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,/*"-",13*/

0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x07,0xF0,0x00,0x80,0x00,0x80,0x00,0x80,/*"+",14*/

0x00,0x00,0x00,0x80,0x01,0x40,0x02,0x20,0x04,0x10,0x08,0x08,0x10,0x04,0x00,0x00,/*"<",15*/

0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*".",16*/

0x00,0x00,0x00,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x00,0x00,0x00,0x00,/*"^",0*/


0x00,0x00,0x00,0x98,0x01,0x24,0x01,0x24,0x01,0x48,0x00,0xFC,0x00,0x04,0x00,0x00,/*"a",0*/

0x08,0x00,0x0F,0xFC,0x00,0x88,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x70,0x00,0x00,/*"b",1*/

0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x00,/*"c",2*/

0x00,0x00,0x00,0xF8,0x01,0x04,0x01,0x04,0x01,0x04,0x09,0x08,0x0F,0xFC,0x00,0x04,/*"d",3*/

0x00,0x00,0x00,0xF8,0x01,0x24,0x01,0x24,0x01,0x24,0x01,0x24,0x00,0xE8,0x00,0x00,/*"e",4*/

0x00,0x00,0x01,0x04,0x01,0x04,0x07,0xFC,0x09,0x04,0x09,0x04,0x04,0x00,0x00,0x00,/*"f",5*/

0x00,0x00,0x00,0xD6,0x01,0x29,0x01,0x29,0x01,0x29,0x01,0xC9,0x01,0x06,0x00,0x00,/*"g",6*/

0x08,0x04,0x0F,0xFC,0x00,0x84,0x01,0x00,0x01,0x00,0x01,0x04,0x00,0xFC,0x00,0x04,/*"h",7*/

0x00,0x00,0x01,0x04,0x19,0x04,0x19,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00,/*"i",8*/

0x00,0x00,0x00,0xD6,0x01,0x29,0x01,0x29,0x01,0x29,0x01,0xC9,0x01,0x06,0x00,0x00,/*"g",9*/

0x08,0x04,0x0F,0xFC,0x00,0x24,0x00,0x60,0x01,0x94,0x01,0x0C,0x01,0x04,0x00,0x00,/*"k",10*/

0x00,0x00,0x08,0x04,0x08,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00,/*"l",11*/


0x01,0x04,0x01,0xFC,0x01,0x04,0x01,0x00,0x01,0xFC,0x01,0x04,0x01,0x00,0x00,0xFC,/*"m",12*/

0x01,0x04,0x01,0xFC,0x00,0x84,0x01,0x00,0x01,0x00,0x01,0x04,0x00,0xFC,0x00,0x04,/*"n",13*/

0x00,0x00,0x00,0xF8,0x01,0x04,0x01,0x04,0x01,0x04,0x01,0x04,0x00,0xF8,0x00,0x00,/*"o",14*/

0x01,0x01,0x01,0xFF,0x00,0x89,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x70,0x00,0x00,/*"p",15*/

0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x00,0x89,0x01,0xFF,0x00,0x01,/*"q",16*/

0x01,0x04,0x01,0x04,0x01,0xFC,0x00,0x84,0x01,0x04,0x01,0x00,0x01,0x80,0x00,0x00,/*"r",17*/

0x00,0x00,0x00,0xCC,0x01,0x24,0x01,0x24,0x01,0x24,0x01,0x24,0x01,0x98,0x00,0x00,/*"s",18*/

0x00,0x00,0x01,0x00,0x01,0x00,0x07,0xF8,0x01,0x04,0x01,0x04,0x00,0x08,0x00,0x00,/*"t",19*/

0x01,0x00,0x01,0xF8,0x00,0x04,0x00,0x04,0x00,0x04,0x01,0x08,0x01,0xFC,0x00,0x04,/*"u",20*/

0x01,0x00,0x01,0xC0,0x01,0x30,0x00,0x0C,0x01,0x30,0x01,0xC0,0x01,0x00,0x00,0x00,/*"v",21*/

0x01,0x80,0x01,0x70,0x00,0x0C,0x01,0x30,0x01,0xE0,0x00,0x1C,0x01,0x60,0x01,0x80,/*"w",22*/

0x00,0x00,0x01,0x04,0x01,0x8C,0x01,0x70,0x00,0x74,0x01,0x8C,0x01,0x04,0x00,0x00,/*"x",23*/

0x01,0x00,0x01,0x81,0x01,0x61,0x00,0x1E,0x00,0x18,0x01,0x60,0x01,0x80,0x01,0x00,/*"y",24*/

0x00,0x00,0x01,0x84,0x01,0x0C,0x01,0x34,0x01,0x44,0x01,0x84,0x01,0x0C,0x00,0x00,/*"z",25*/

0x00,0x04,0x00,0x3C,0x03,0xC4,0x1C,0x40,0x07,0x40,0x00,0xE4,0x00,0x1C,0x00,0x04,/*"A",26*/

0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x04,0x11,0x04,0x0E,0x88,0x00,0x70,0x00,0x00,/*"B",27*/

0x03,0xE0,0x0C,0x18,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x08,0x1C,0x10,0x00,0x00,/*"C",28*/

0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00,/*"D",29*/

0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x04,0x17,0xC4,0x10,0x04,0x08,0x18,0x00,0x00,/*"E",30*/

0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x00,0x17,0xC0,0x10,0x00,0x08,0x00,0x00,0x00,/*"F",31*/

0x03,0xE0,0x0C,0x18,0x10,0x04,0x10,0x04,0x10,0x44,0x1C,0x78,0x00,0x40,0x00,0x00,/*"G",32*/

0x10,0x04,0x1F,0xFC,0x10,0x84,0x00,0x80,0x00,0x80,0x10,0x84,0x1F,0xFC,0x10,0x04,/*"H",33*/

0x00,0x00,0x10,0x04,0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x00,0x00,0x00,0x00,/*"I",34*/

0x03,0xE0,0x0C,0x18,0x10,0x04,0x10,0x04,0x10,0x44,0x1C,0x78,0x00,0x40,0x00,0x00,/*"G",35*/

0x10,0x04,0x1F,0xFC,0x11,0x04,0x03,0x80,0x14,0x64,0x18,0x1C,0x10,0x04,0x00,0x00,/*"K",36*/

0x10,0x04,0x1F,0xFC,0x10,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x0C,0x00,0x00,/*"L",37*/

0x10,0x04,0x1F,0xFC,0x1F,0x80,0x00,0x7C,0x1F,0x80,0x1F,0xFC,0x10,0x04,0x00,0x00,/*"M",38*/

0x10,0x04,0x1F,0xFC,0x0C,0x04,0x03,0x00,0x00,0xE0,0x10,0x18,0x1F,0xFC,0x10,0x00,/*"N",39*/

0x07,0xF0,0x08,0x08,0x10,0x04,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00,/*"O",40*/

0x10,0x04,0x1F,0xFC,0x10,0x84,0x10,0x80,0x10,0x80,0x10,0x80,0x0F,0x00,0x00,0x00,/*"P",41*/

0x07,0xF0,0x08,0x08,0x10,0x14,0x10,0x14,0x10,0x0C,0x08,0x0A,0x07,0xF2,0x00,0x00,/*"Q",42*/

0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x00,0x11,0xC0,0x11,0x30,0x0E,0x0C,0x00,0x04,/*"R",43*/

0x00,0x00,0x0E,0x1C,0x11,0x04,0x10,0x84,0x10,0x84,0x10,0x44,0x1C,0x38,0x00,0x00,/*"S",44*/

0x18,0x00,0x10,0x00,0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x00,0x18,0x00,0x00,0x00,/*"T",45*/

0x10,0x00,0x1F,0xF8,0x10,0x04,0x00,0x04,0x00,0x04,0x10,0x04,0x1F,0xF8,0x10,0x00,/*"U",46*/

0x10,0x00,0x1E,0x00,0x11,0xE0,0x00,0x1C,0x00,0x70,0x13,0x80,0x1C,0x00,0x10,0x00,/*"V",47*/

0x10,0x00,0x1F,0xC0,0x00,0x7C,0x1F,0x80,0x00,0x7C,0x1F,0xC0,0x10,0x00,0x00,0x00,/*"W",48*/

0x10,0x04,0x18,0x0C,0x16,0x34,0x01,0xC0,0x01,0xC0,0x16,0x34,0x18,0x0C,0x10,0x04,/*"X",49*/

0x10,0x00,0x1C,0x00,0x13,0x04,0x00,0xFC,0x13,0x04,0x1C,0x00,0x10,0x00,0x00,0x00,/*"Y",50*/

0x08,0x04,0x10,0x1C,0x10,0x64,0x10,0x84,0x13,0x04,0x1C,0x04,0x10,0x18,0x00,0x00,/*"Z",51*/

0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,/*"_",0*/

};
const unsigned char  zm16x16_index_Demo[]="欢";//字串索引
const unsigned char  zm16x16_Table_Demo[][32]={

0x20,0x08,0x24,0x10,0x22,0x60,0x21,0x80,0x26,0x41,0x39,0x32,0x02,0x04,0x0C,0x18,
0xF0,0x60,0x13,0x80,0x10,0x60,0x10,0x18,0x14,0x04,0x18,0x02,0x00,0x01,0x00,0x00,/*"?",0*/

			
};

//****************************************************************************
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Read/Write Sequence
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void I2C_3_Demo(unsigned char mcmd)
{
unsigned char length = 8;			// Send Command

	while(length--)
	{
		if(mcmd & 0x80)
		{
			SDA3_1;
		}
		else
		{
			SDA3_0;
		}
//		uDelay(3);
		SCL3_1;
//		uDelay(3);
		SCL3_0;
//		uDelay(3);
		mcmd = mcmd << 1;
	}
}


void I2C_Ack3_Demo()
{
	SDA3_1;
//	uDelay(3);
	SCL3_1;
//	uDelay(3);
	SCL3_0;
//	uDelay(3);
}


void I2C_NAck3_Demo()
{
	SDA3_0;
//	uDelay(3);
	SCL3_1;
//	uDelay(3);
	SCL3_0;
//	uDelay(3);
}


void I2C_Start3_Demo()
{
	SDA3_0;
//	uDelay(3);
	SCL3_1;
//	uDelay(3);
	SCL3_0;
//	uDelay(3);
	I2C_3_Demo(0x78);
	I2C_Ack3_Demo();
}


void I2C_Stop3_Demo()
{
	SCL3_1;
//	uDelay(5);
	SDA3_0;
//	uDelay(5);
	SDA3_1;
//	uDelay(5);
}


void Write_Command3_Demo(unsigned char Data)
{
	I2C_Start3_Demo();
	I2C_3_Demo(0x00);
	I2C_Ack3_Demo();
	I2C_3_Demo(Data);
	I2C_Ack3_Demo();
	I2C_Stop3_Demo();
}


void Write_Data3_Demo(unsigned char Data)
{
	I2C_Start3_Demo();
	I2C_3_Demo(0x40);
	I2C_Ack3_Demo();
	I2C_3_Demo(Data);
	I2C_Ack3_Demo();
	I2C_Stop3_Demo();
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear_Demo(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM_Demo[n][i]=0X00;  
	OLED_Refresh_Gram_Demo();//更新显示
}

void	OLED_Init3_Demo(void)
{
	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);
 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
 
	delay_ms(300);
	
	
//		RES3=0;
//		//uDelay(2);
//		RES3=1;
//		//internal setting


		Write_Command3_Demo(0xae);	//--turn off oled panel

		Write_Command3_Demo(0x00);	//--set low column address
		Write_Command3_Demo(0x10);	//--set high column address

		Write_Command3_Demo(0x40);	//--set start line address

		Write_Command3_Demo(0xb0);	//--set page address

		Write_Command3_Demo(0x81);	//--set contrast control register
		Write_Command3_Demo(0xff);

		Write_Command3_Demo(0xa1);	//--set segment re-map 127 to 0   a0:0 to seg127
		Write_Command3_Demo(0xa6);	//--set normal display


		//切换显示角度 上下颠倒显示
		//Write_Command3(0xc0);	//--set com(N-1)to com0  c0:com0 to com(N-1)
		
		//切换显示角度
		Write_Command3_Demo(0xc0);	//--set com(N-1)to com0  c0:com0 to com(N-1)

		Write_Command3_Demo(0xa8);	//--set multiples ratio(1to64)
		Write_Command3_Demo(0x3f);	//--1/64 duty

		Write_Command3_Demo(0xd3);	//--set display offset
		Write_Command3_Demo(0x00);	//--not offset

		Write_Command3_Demo(0xd5);	//--set display clock divide ratio/oscillator frequency
		Write_Command3_Demo(0x80);	//--set divide ratio

		Write_Command3_Demo(0xd9);	//--set pre-charge period
		Write_Command3_Demo(0xf1);

		Write_Command3_Demo(0xda);	//--set com pins hardware configuration
		Write_Command3_Demo(0x12);

		Write_Command3_Demo(0xdb);	//--set vcomh
		Write_Command3_Demo(0x40);

		Write_Command3_Demo(0x8d);	//--set chare pump enable/disable
		Write_Command3_Demo(0x14);	//--set(0x10) disable
		//Write_Command3(0x10);	//--set(0x10) disable
		Write_Command3_Demo(0xaf);	//--turn on oled panel
		//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=void 	LCD_Init(void)
		
		OLED_Clear_Demo();
		

}

//更新显存到LCD		 
void OLED_Refresh_Gram_Demo(void)
{
	u8 j,n;
	
	for(j=0;j<8;j++)
	{
		Write_Command3_Demo(0x22);//--set page1
		Write_Command3_Demo(j);//--set start page
		Write_Command3_Demo(0x07);//--set end page

		
		for(n=0;n<128;n++)Write_Data3_Demo(OLED_GRAM_Demo[n][j]); 
		
	}
	
}

/* 返回一个8*16字符索引位置 */					
unsigned char enN_Demo(unsigned char *s){
	unsigned char i;
	for(i=0;zm8x16_index_Demo[i]!=0;i++)if(zm8x16_index_Demo[i]==s[0])break;
	return i;	
}
/* 返回一个16*16字符索引位置 */
unsigned char cnN_Demo(unsigned char *s){
	unsigned char i;
	for(i=0;zm16x16_index_Demo[i]!=0;i+=2)
		if(zm16x16_index_Demo[i]==*s&&zm16x16_index_Demo[i+1]==*(s+1))break ;
	return i/2;
}


//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void OLED_DrawPoint_Demo(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM_Demo[x][pos]|=temp;
	else OLED_GRAM_Demo[x][pos]&=~temp;	    
}


void OLED_ShowStr_ENCH_Demo(u8 x, u8 y,unsigned char *s)
{
	 u8 temp,t,t1,value;
   u8 y0=y;
	 unsigned char i;
	 for(i=0;s[i]!=0;i++){
	 	if(s[i]<0x80){ 	//英文
			value=enN_Demo(&s[i]);
			
			for(t=0;t<16;t++)
			{  
				  temp = zm8x16_Table_Demo[value][t];    //调用1616字体

					for(t1=0;t1<8;t1++)
					{
							if(temp&0x80)OLED_DrawPoint_Demo(x,y,1);
							else OLED_DrawPoint_Demo(x,y,!1);
							temp<<=1;
							y++;
							if((y-y0)==16)
							{
									y=y0;
									x++;
									break;
							}
					}    
			} 	
			//x=x+8;	
		}else{			//中文
			value=cnN_Demo(&s[i]);
			for(t=0;t<32;t++)
			{  
				  temp = zm16x16_Table_Demo[value][t];    //调用1616字体

					for(t1=0;t1<8;t1++)
					{
							if(temp&0x80)OLED_DrawPoint_Demo(x,y,1);
							else OLED_DrawPoint_Demo(x,y,!1);
							temp<<=1;
							y++;
							if((y-y0)==16)
							{
									y=y0;
									x++;
									break;
							}
					}    
			}
			//中文两个字节，需要加1
			i+=1;			
		}//中文
		
	}
	OLED_Refresh_Gram_Demo();	
}

void OLED_ShowNum_Demo(u8 x, u8 y,unsigned int num)
{
	u8 t,temp,t1;
	u8 y0=y;	
	for(t=0;t<16;t++)
	{  
		temp = zm8x16_Table_Demo[num][t];    //调用1616字体

		for(t1=0;t1<8;t1++)
		{
				if(temp&0x80)OLED_DrawPoint_Demo(x,y,1);
				else OLED_DrawPoint_Demo(x,y,!1);
				temp<<=1;
				y++;
				if((y-y0)==16)
				{
						y=y0;
						x++;
						break;
				}
		}    
	} 	
		
}
void OLED_ShowNum_Weight_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/1000%10);
	OLED_ShowStr_ENCH_Demo(row+8,col,(u8*)".");
	OLED_ShowNum_Demo(row+16,col,s/100%10);
	OLED_ShowNum_Demo(row+24,col,s/10%10);
	OLED_ShowNum_Demo(row+32,col,s%10);
	OLED_Refresh_Gram_Demo();	
}
void OLED_ShowNum_One_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/1%10);
	OLED_Refresh_Gram_Demo();	
}
void OLED_ShowNum_Two_Demo(unsigned char row,unsigned char col,unsigned int s)
{

	OLED_ShowNum_Demo(row,col,s/10%10);
	OLED_ShowNum_Demo(row+8,col,s%10);
	OLED_Refresh_Gram_Demo();	
}
void OLED_ShowNum_Three_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/100%10);
	OLED_ShowNum_Demo(row+8,col,s/10%10);
	OLED_ShowNum_Demo(row+16,col,s%10);
	OLED_Refresh_Gram_Demo();	
}
void OLED_ShowNum_four_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/1000%10);
	OLED_ShowNum_Demo(row+8,col,s/100%10);
	OLED_ShowNum_Demo(row+16,col,s/10%10);
	OLED_ShowNum_Demo(row+24,col,s%10);
	OLED_Refresh_Gram_Demo();	
}
void OLED_ShowNum_Temp_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/100%10);
	OLED_ShowNum_Demo(row+8,col,s/10%10);
	OLED_ShowNum_Demo(row+16,col,16);
	OLED_ShowNum_Demo(row+24,col,s%10);
	OLED_Refresh_Gram_Demo();	
}
#if CONFIG_DS1302 == ENABLED
void OLED_ShowNum_Ds13b02_DisPlay(unsigned char row,unsigned char col,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao)
{

	
	OLED_ShowNum_Demo(row,col,yue/10%10);		// 十位
	OLED_ShowNum_Demo(row+8,col,yue%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+16,col,(u8*)"-");
	OLED_ShowNum_Demo(row+24,col,ri%100/10);		// 十位
	OLED_ShowNum_Demo(row+32,col,ri%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+40,col,(u8*)" ");	
	OLED_ShowNum_Demo(row+48,col,shi%100/10);		// 十位
	OLED_ShowNum_Demo(row+56,col,shi%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+64,col,(u8*)":");
	OLED_ShowNum_Demo(row+72,col,fen%100/10);		// 十位
	OLED_ShowNum_Demo(row+80,col,fen%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+88,col,(u8*)":");
	OLED_ShowNum_Demo(row+96,col,miao%100/10);		// 十位
	OLED_ShowNum_Demo(row+104,col,miao%10);				// 个位
	OLED_Refresh_Gram_Demo();

}

void OLED_ShowNum_Ds13b02_Min(unsigned char row,unsigned char col,unsigned char shi,unsigned char fen,unsigned char miao)
{

	

	OLED_ShowNum_Demo(row,col,shi%100/10);		// 十位
	OLED_ShowNum_Demo(row+8,col,shi%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+16,col,(u8*)":");
	OLED_ShowNum_Demo(row+24,col,fen%100/10);		// 十位
	OLED_ShowNum_Demo(row+32,col,fen%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+40,col,(u8*)":");
	OLED_ShowNum_Demo(row+48,col,miao%100/10);		// 十位
	OLED_ShowNum_Demo(row+56,col,miao%10);				// 个位
	OLED_Refresh_Gram_Demo();

}
#endif


#if CONFIG_CARSPEED == ENABLED

void OLED_ShowNum_fiive_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/10000%10);
	OLED_ShowNum_Demo(row+8,col,s/1000%10);	
	OLED_ShowNum_Demo(row+16,col,s/100%10);
	OLED_ShowNum_Demo(row+24,col,s/10%10);
	OLED_ShowNum_Demo(row+32,col,s%10);
	OLED_Refresh_Gram_Demo();	
}
#endif

#if CONFIG_BMP180 == ENABLED
void OLED_ShowNum_BMP180_Demo(unsigned char row,unsigned char col,unsigned int s)
{

	OLED_ShowNum_Demo(row,col,s/100000%10);	
	OLED_ShowNum_Demo(row+8,col,s/10000%10);
	OLED_ShowNum_Demo(row+16,col,s/1000%10);
	OLED_ShowStr_ENCH_Demo(row+24,col,(u8*)".");
	OLED_ShowNum_Demo(row+32,col,s/100%10);	
	OLED_ShowNum_Demo(row+40,col,s/10%10);	
	OLED_Refresh_Gram_Demo();	
}
#endif
#endif
#if CONFIG_TIMER2 == ENABLED
static pTime2Process_Demo Tim2_Handle_Process;
void TIM2_Int_Init_demo(u16 Period,u16 Prescaler,pTime2Process_Demo TimeProcess)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 			//时钟使能

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);   						//使能或者失能指定的TIM中断
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn;//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
	Tim2_Handle_Process = TimeProcess;
	TIM_Cmd(TIM2, ENABLE);  										//使能TIMx外设							 
}
	   
/**
 * @Description: 通用定时器TIM3中断函数
 */
void TIM2_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		if(Tim2_Handle_Process != 0)
			Tim2_Handle_Process();
		
	}
}

#endif
#if CONFIG_TIMER3 == ENABLED


static pTimeProcess_Demo Tim3_Handle_Process_Demo;
void TIM3_Int_Init_Demo(u16 Period,u16 Prescaler,pTimeProcess_Demo TimeProcess)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 			//时钟使能

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   						//使能或者失能指定的TIM中断
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn;//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
	Tim3_Handle_Process_Demo = TimeProcess;
	TIM_Cmd(TIM3, ENABLE);  										//使能TIMx外设							 
}
	   
/**
 * @Description: 通用定时器TIM3中断函数
 */
void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		if(Tim3_Handle_Process_Demo != 0)
			Tim3_Handle_Process_Demo();
		 
	}
}

#endif

#if CONFIG_TIMER3_PWN == ENABLED
void TIM3_PWM_Init_Demo(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //超过对比的部分为低电平0，持续为低电平
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
 
	TIM_Cmd(TIM3, ENABLE); 

}

/**DEMO
//0为最亮，899为最暗
TIM3_PWM_Init_Demo(899, 0);//0~900,bu fen ping

TIM_SetCompare2(TIM3, 100);
**/

#endif
#if CONFIG_TIMER4 == ENABLED
static pTime4Process_Demo Tim4_Handle_Process_Demo;
void TIM4_Int_Init_Demo(u16 arr,u16 psc,pTime4Process_Demo TimeProcess)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 


	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	Tim4_Handle_Process_Demo = TimeProcess;
	TIM_Cmd(TIM4, ENABLE);  
}

void TIM4_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		if(Tim4_Handle_Process_Demo != 0)
			Tim4_Handle_Process_Demo();
		 
	}
  
	
}

#endif
#if CONFIG_DS18b02 == ENABLED




void SDA_Set_Output_DS18B20(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_DS18B20;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_DS18B20, &GPIO_InitStructure);					 					
}

void SDA_Set_Input_DS18B20(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_DS18B20;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_DS18B20, &GPIO_InitStructure);					 
}
//复位DS18B20
void DS18B20_Rst_Demo(void)	   
{                 
	DS18B20_IO_OUT(); //SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; //拉低DQ
    delay_us(750);    //拉低750us
    DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
u8 DS18B20_Check_Demo(void) 	   
{   
	u8 retry=0;
	DS18B20_IO_IN();//SET PA0 INPUT	 
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
u8 DS18B20_Read_Bit_Demo(void) 			 // read one bit
{
    u8 data;
	DS18B20_IO_OUT();//SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; 
	delay_us(2);
    DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();//SET PA0 INPUT
	delay_us(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;	 
    delay_us(50);           
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
u8 DS18B20_Read_Byte_Demo(void)    // read one byte
{        
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit_Demo();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte_Demo(u8 dat)     
 {             
    u8 j;
    u8 testb;
	DS18B20_IO_OUT();//SET PA0 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;// Write 1
            delay_us(2);                            
            DS18B20_DQ_OUT=1;
            delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;// Write 0
            delay_us(60);             
            DS18B20_DQ_OUT=1;
            delay_us(2);                          
        }
    }
}
//开始温度转换
void DS18B20_Start_Demo(void)// ds1820 start convert
{   						               
    DS18B20_Rst_Demo();	   
	DS18B20_Check_Demo();	 
    DS18B20_Write_Byte_Demo(0xcc);// skip rom
    DS18B20_Write_Byte_Demo(0x44);// convert
} 
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
u8 DS18B20_Init_Demo(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(SDA_RCC_DS18B20, ENABLE);	 //使能PORTA口时钟 
	
 	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_DS18B20;				//PORTA0 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(SDA_GPIO_DS18B20, &GPIO_InitStructure);

 	GPIO_SetBits(SDA_GPIO_DS18B20,SDA_GPIO_PIN_DS18B20);    //输出1

	DS18B20_Rst_Demo();

	return DS18B20_Check_Demo();
}  
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
short DS18B20_Get_Temp_Demo(void)
{
    u8 temp;
    u8 TL,TH;
	  short tem;
    DS18B20_Start_Demo ();                    // ds1820 start convert
    DS18B20_Rst_Demo();
    DS18B20_Check_Demo();	 
    DS18B20_Write_Byte_Demo(0xcc);// skip rom
    DS18B20_Write_Byte_Demo(0xbe);// convert	    
    TL=DS18B20_Read_Byte_Demo(); // LSB   
    TH=DS18B20_Read_Byte_Demo(); // MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//温度为负  
    }else temp=1;//温度为正	  	  
    tem=TH; //获得高八位
    tem<<=8;    
    tem+=TL;//获得底八位
    tem=(float)tem*0.625;//转换     
	if(temp)return tem/10; //返回温度值
	else return -tem/10;    
} 
 

#endif

#if CONFIG_MOTO_STEP == ENABLED



//按键对应IO初始化函数
void MotoStep_Init_Demo(pTimeProcess_Demo  TimeProce)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//定时器3初始化
	TIM3_Int_Init_Demo (10, 7200,TimeProce);//10ms faster
}

/***********************正转****************************/
void Moto_Zheng_Demo(unsigned char dat)
{
	switch(dat)
	{

		
		case 0: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 1: MOTO_PIN0=1;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 4: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 5: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=1; break;
		case 6: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		case 7: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;		
		
	}
}

/***********************正转****************************/
void Moto_Fan_Demo(unsigned char dat)
{
	switch(dat)
	{

		case 7: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 6: MOTO_PIN0=1;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 5: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 4: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=1; break;
		case 1: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		case 0: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;	
	}
}
void MotoStopFun_Demo(void)
{
	MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0;
}

#endif

#if CONFIG_MOTO_STEP_MUL == ENABLED



//按键对应IO初始化函数
void MotoStep_Init_Demo(pTimeProcess_Demo  TimeProce)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	//定时器3初始化
	TIM3_Int_Init_Demo (10, 7200,TimeProce);//10ms faster
}

/***********************正转****************************/
void Moto_Zheng_Demo(unsigned char dat)
{
	switch(dat)
	{

		
		case 0: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 1: MOTO_PIN0=1;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 4: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 5: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=1; break;
		case 6: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		case 7: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;		
		
	}
}

/***********************正转****************************/
void Moto_Fan_Demo(unsigned char dat)
{
	switch(dat)
	{

		case 7: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 6: MOTO_PIN0=1;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 5: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 4: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=1; break;
		case 1: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		case 0: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;	
	}
}
void MotoStopFun_Demo(void)
{
	MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0;
}
/***********************正转****************************/
void Moto_Zheng_Demo1(unsigned char dat)
{
	switch(dat)
	{

		
		case 0: MOTO_PIN01=1;MOTO_PIN11=0;MOTO_PIN21=0;MOTO_PIN31=0; break;
		case 1: MOTO_PIN01=1;MOTO_PIN11=1;MOTO_PIN21=0;MOTO_PIN31=0; break;
		case 2: MOTO_PIN01=0;MOTO_PIN11=1;MOTO_PIN21=0;MOTO_PIN31=0; break;
		case 3: MOTO_PIN01=0;MOTO_PIN11=1;MOTO_PIN21=1;MOTO_PIN31=0; break;
		case 4: MOTO_PIN01=0;MOTO_PIN11=0;MOTO_PIN21=1;MOTO_PIN31=0; break;
		case 5: MOTO_PIN01=0;MOTO_PIN11=0;MOTO_PIN21=1;MOTO_PIN31=1; break;
		case 6: MOTO_PIN01=0;MOTO_PIN11=0;MOTO_PIN21=0;MOTO_PIN31=1; break;
		case 7: MOTO_PIN01=1;MOTO_PIN11=0;MOTO_PIN21=0;MOTO_PIN31=1; break;		
		
	}
}

/***********************正转****************************/
void Moto_Fan_Demo1(unsigned char dat)
{
	switch(dat)
	{

		case 7: MOTO_PIN01=1;MOTO_PIN11=0;MOTO_PIN21=0;MOTO_PIN31=0; break;
		case 6: MOTO_PIN01=1;MOTO_PIN11=1;MOTO_PIN21=0;MOTO_PIN31=0; break;
		case 5: MOTO_PIN01=0;MOTO_PIN11=1;MOTO_PIN21=0;MOTO_PIN31=0; break;
		case 4: MOTO_PIN01=0;MOTO_PIN11=1;MOTO_PIN21=1;MOTO_PIN31=0; break;
		case 3: MOTO_PIN01=0;MOTO_PIN11=0;MOTO_PIN21=1;MOTO_PIN31=0; break;
		case 2: MOTO_PIN01=0;MOTO_PIN11=0;MOTO_PIN21=1;MOTO_PIN31=1; break;
		case 1: MOTO_PIN01=0;MOTO_PIN11=0;MOTO_PIN21=0;MOTO_PIN31=1; break;
		case 0: MOTO_PIN01=1;MOTO_PIN11=0;MOTO_PIN21=0;MOTO_PIN31=1; break;	
	}
}
void MotoStopFun_Demo1(void)
{
	MOTO_PIN01=0;MOTO_PIN11=0;MOTO_PIN21=0;MOTO_PIN31=0;
}

#endif


#if CONFIG_USART1 == ENABLED

#include <stdio.h>
u8 a1;

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}

void usart1_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}


void usart1_SendByte_Demo(unsigned char a)
{

	USART_SendData(USART1,a); //开始发送
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	USART_ClearFlag(USART1,USART_FLAG_TXE);
}


void usart1_SendString_Demo(unsigned char *Index)
{

	while(*Index)//检测字符串结束符
	{
		usart1_SendByte_Demo(*Index++);//发送当前字符
	}

}



void USART1_Send_Data_Demo(unsigned char *Data,unsigned short Length)
{

	unsigned short i;


	for(i=0;i<Length;i++)
	{
		/* Place your implementation of fputc here */
		/* e.g. write a character to the USART */
		USART_SendData(USART1, *Data++);
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{}
	}

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		a1 =USART_ReceiveData(USART1);	//读取接收到的数据

	} 

}

#endif

#if CONFIG_USART2 == ENABLED
u8 a2;

void usart2_init_Demo(u32 bound)
{
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//  
	
	//重新定义管脚
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	//USART2_TX    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // 引脚不能更改
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 
   
  //USART2_RX	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化   

  //Usart NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3 原3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3     原2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2
}
 /*发送一个字节数据*/
 void USART2SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART2,SendData);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
} 

/*
根据长度向串口2 发送数据
*/
void usart2_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2, data[i]); //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		//i++;
	}
	//i++;
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void usart2_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART2, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
/*
串口2中断函数
*/
void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{	
		a2 = USART_ReceiveData(USART2);	

	}  
}
#endif


#if CONFIG_USART3 == ENABLED
u8 a3;
void usart3_init_Demo(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;   
	NVIC_InitTypeDef    NVIC_InitStructure;  
		

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    

		
	//USART3?Tx---GPIO----Pb.10----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//USART3?Rx---GPIO----Pb.11----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                      
		
	USART_InitStructure.USART_BaudRate=bound;             
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                      
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART_Init(USART3,&USART_InitStructure);	        //

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //

	USART_Cmd(USART3,ENABLE);                           //

}

void USART3_IRQHandler(void) //??1??????
{
	
	if(USART_GetFlagStatus(USART3,USART_IT_RXNE) != RESET)  //
	{			
		a3=USART_ReceiveData(USART3);
		

	
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);        //
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==RESET);	  //
	}
}
 /*发送一个字节数据*/
 void USART3SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
} 

/*
根据长度向串口2 发送数据
*/
void usart3_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART3, data[i]); //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		//i++;
	}
	//i++;
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}

#endif

#if CONFIG_SR04 == ENABLED

volatile unsigned char Time2_Over_Flag_Demo = 0;
void Tim2_Init_Demo(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;

	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
	TIM_DeInit(TIM2);//复位TIM2定时器
	TIM_TimeBaseStructure.TIM_Period = 49999;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
	 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4; 
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	//NVIC_Init(&NVIC_InitStructure); 	
}

void SR04_Init_Demo(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;// 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成 输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	Tim2_Init_Demo();
}
void TIM2_IRQHandler(void)
{

	Time2_Over_Flag_Demo = 1;
	
	 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
}
void SR04_Processing_Demo(unsigned short *Length_Value)
{
	
	unsigned short i;
			
			Trig = 1;  //拉高TRIG超过10US。
			i = 0xFFF;
			while(--i);
			i = 0xFFF;
			while(--i);	
			Trig = 0;	
			TIM2->CNT=0;//计数器清0
			while(1)//等待ECHO脚高电平
			{
				 if(Echo == 1)
				  {
							TIM_Cmd(TIM2, ENABLE);// TIM2 enable counter [允许tim2计数]
							break;
				  }
				 if	(Time2_Over_Flag_Demo)
				 {
						Time2_Over_Flag_Demo = 0;
				  	break;
				 }					
			}
			
			while(1)
			{
				
				  if(Echo == 0)
				  {
						TIM_Cmd(TIM2, DISABLE);
						break;
				  }
				 if	(Time2_Over_Flag_Demo)
				 {
						Time2_Over_Flag_Demo = 0;
				  	break;
				 }								
			} 
			
			//	Length_Value(cm) = (TIM5->CNT(us)*340m/s)/2 = (TIM5->CNT/1000000*340*100)/2=	TIM5->CNT/(1000000*2/340)=TIM5->CNT*58.82
			*Length_Value =TIM2->CNT/58.0;//ECHO脚低电平后读取计数器的值，从而算出往返时间
       //printf("legth %ld,value %d\r\n",*Length_Value,TIM2->CNT);
			//大于4米
			if(*Length_Value >= 400) *Length_Value = 400;
}

#endif

#if CONFIG_FLASH == ENABLED
#include "stm32f10x_flash.h"

//读取指定地址的半字(16位数据)
//faddr:读地址(此地址必须为2的倍数!!)
//返回值:对应数据.
u16 STMFLASH_ReadHalfWord_Demo(u32 faddr)
{
	return *(vu16*)faddr; 
}
#if STM32_FLASH_WREN	//如果使能了写   
//不检查的写入
//WriteAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数   
void STMFLASH_Write_NoCheck_Demo(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//地址增加2.
	}  
}

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数
void STMFLASH_Read_Demo(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord_Demo(ReadAddr);//读取2个字节.
		ReadAddr+=2;//偏移2个字节.	
	}
}
//从指定地址开始写入指定长度的数据
//WriteAddr:起始地址(此地址必须为2的倍数!!)
//pBuffer:数据指针
//NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //字节
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF_Demo[STM_SECTOR_SIZE/2];//最多是2K字节
void STMFLASH_Write_Demo(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//非法地址
	FLASH_Unlock();						//解锁
	offaddr=WriteAddr-STM32_FLASH_BASE;		//实际偏移地址.
	secpos=offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//扇区剩余空间大小   
	if(NumToWrite<=secremain)secremain=NumToWrite;//不大于该扇区范围
	while(1) 
	{	
		STMFLASH_Read_Demo(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF_Demo,STM_SECTOR_SIZE/2);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(STMFLASH_BUF_Demo[secoff+i]!=0XFFFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//擦除这个扇区
			for(i=0;i<secremain;i++)//复制
			{
				STMFLASH_BUF_Demo[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck_Demo(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF_Demo,STM_SECTOR_SIZE/2);//写入整个扇区  
		}else STMFLASH_Write_NoCheck_Demo(WriteAddr,pBuffer,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;				//扇区地址增1
			secoff=0;				//偏移位置为0 	 
		   	pBuffer+=secremain;  	//指针偏移
			WriteAddr+=secremain;	//写地址偏移	   
		   	NumToWrite-=secremain;	//字节(16位)数递减
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//下一个扇区还是写不完
			else secremain=NumToWrite;//下一个扇区可以写完了
		}	 
	};	
	FLASH_Lock();//上锁
}
#endif



//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:起始地址
//WriteData:要写入的数据
void Test_Write_Demo(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write_Demo(WriteAddr,&WriteData,1);//写入一个字 
}

#endif

#if CONFIG_DS1302 == ENABLED

const unsigned char  Ds1302_write_add_Demo[]={0x80,0x82,0x84,0x86,0x88,0x8c,0x8a};   //写地址
const unsigned char  Ds1302_read_add_Demo[] ={0x81,0x83,0x85,0x87,0x89,0x8d,0x8b};   //读地址

void SDA_Set_Output_DS1302(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_DS1302;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_DS1302, &GPIO_InitStructure);					 					
}

void SDA_Set_Input_DS1302(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_DS1302;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_DS1302, &GPIO_InitStructure);					 
}

//DS1302初始化
void DS1302_Init_Demo(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
		
 	RCC_APB2PeriphClockCmd(SDA_RCC_DS1302|SCK_RCC_DS1302|RST_RCC_DS1302, ENABLE);	 //使能PORTA口时钟 
	
 	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_DS1302;				//PORTA0 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(SDA_GPIO_DS1302, &GPIO_InitStructure);	
	
 	GPIO_InitStructure.GPIO_Pin = SCK_GPIO_PIN_DS1302;				//PORTA0 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(SCK_GPIO_DS1302, &GPIO_InitStructure);	

 	GPIO_InitStructure.GPIO_Pin = RST_GPIO_PIN_DS1302;				//PORTA0 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(RST_GPIO_DS1302, &GPIO_InitStructure);	
	
	GPIO_SetBits(SDA_GPIO_DS1302, SDA_GPIO_PIN_DS1302);   //PB1拉高
	GPIO_SetBits(SCK_GPIO_DS1302, SCK_GPIO_PIN_DS1302);   //PB1拉高
	GPIO_SetBits(RST_GPIO_DS1302, RST_GPIO_PIN_DS1302);   //PB1拉高

}

//向DS1302写入一个字节数据
void DS1302_Write_Byte_Demo(u8 addr, u8 data)
{
  u8 i;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr & 0xFE;  //最低位置零，写数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	for (i = 0; i < 8; i ++) //写数据
	{
	  if(data & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	  data = data>>1;
	}
	DS1302_RST = 0;      //停止DS1302总线
}

//从DS1302读出一个字节数据
u8 DS1302_Read_Byte_Demo(u8 addr)
{
  u8 i,temp;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr | 0x01;  //最低位置高，读数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	DS1302_IO_IN();
	for (i = 0; i < 8; i ++) //读数据
	{
	  temp = temp >> 1;
		if(DS1302_DATA_IN)
			temp |= 0x80;
		else
			temp &= 0x7F;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	}
	DS1302_RST = 0;      //停止DS1302总线
	return temp;
}


unsigned char BCD_Decimal_Demo(unsigned char bcd)//BCD码转十进制函数，输入BCD，返回十进制
{
	 unsigned char Decimal;
	 Decimal=bcd>>4;
	 return(Decimal=Decimal*10+(bcd&=0x0F));
}
/*************把要的时间 年月日 都读出来***************/
//arry[7]
void Ds1302_Read_Time_Demo(unsigned char *arry)
{
	*arry      = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[0]));	//读秒
	*(arry+1)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[1]));	//读分
	*(arry+2)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[2]));	//读时
	*(arry+3)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[3]));	//读日
	*(arry+4)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[4]));	//读月
	*(arry+5)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[5]));	//读年
	*(arry+6)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[6]));	//读星期
}

void Ds1302_Save_Demo(unsigned char  po, unsigned char  dat)
{
	unsigned char  temp;
	temp=(dat)/10*16+(dat)%10;//十进制转换成DS1302要求的DCB码
	DS1302_Write_Byte_Demo(0x8e,0x00);//允许写，禁止写保护 
	DS1302_Write_Byte_Demo(po,temp);//向DS1302内写分寄存器82H写入调整后的分数据BCD码
	DS1302_Write_Byte_Demo(0x8e,0x80);//打开写保护	
}

#endif

#if CONFIG_DHT11 == ENABLED

 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//DHT11数字温湿度传感器驱动代码	   
//修改日期:2012/9/12
//版本：V1.0
//版权所有，盗版必究。
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
      
//复位DHT11
void DHT11_Rst_Demo(void)	   
{                 
	  DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//拉低DQ
    delay_ms(20);    	//拉低至少18ms
    DHT11_DQ_OUT=1; 	//DQ=1 
	  delay_us(30);     	//主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check_Demo(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit_Demo(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte_Demo(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit_Demo();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data_Demo(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst_Demo();
	if(DHT11_Check_Demo()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte_Demo();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT11_Init_Demo(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC13 输出高
			    
	DHT11_Rst_Demo();  //复位DHT11
	return DHT11_Check_Demo();//等待DHT11的回应
} 


#endif

#if CONFIG_HX711 == ENABLED
unsigned long Weight_Maopi_Demo;

void GPIO_Weigh_Init_Demo(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint32_t Read_Weigh_Demo(void)
{
	uint8_t i;
	uint32_t value = 0;
	

	GPIO_SetBits(GPIOB, GPIO_Pin_7); //????DT??????
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); //????SCK??????
	

	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
	delay_us(1);

	for(i=0; i<24; i++) //24???????????????????
	{

		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		delay_us(1);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)
		{
			value = value << 1;
			value |= 0x00;
		}
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 1)
		{
			value = value << 1;
			value |= 0x01;
		}
		delay_us(1);
	}
	
	//? 25? 27 ???????????? A/D ??????????
	GPIO_SetBits(GPIOB, GPIO_Pin_6); 
	value = value^0x800000; 
	delay_us(1); 
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); 
	delay_us(1);  
	return value; 	
}

//****************************************************
//获取毛皮重量
//****************************************************
unsigned long Get_Maopi_Demo(void)
{
	unsigned long Weight_Maopi_temp = 0;
mm:	Weight_Maopi_temp = Read_Weigh_Demo();
	delay_ms(200);
	Weight_Maopi_Demo = Read_Weigh_Demo();
	if(Weight_Maopi_Demo/GapValue!=Weight_Maopi_temp/GapValue)
		goto mm;
	return Weight_Maopi_Demo;

} 

unsigned long Get_Weight_Demo(void)
{
	long Weight_Shiwu;
	Weight_Shiwu = Read_Weigh_Demo();
	
	Weight_Shiwu = Weight_Shiwu-Weight_Maopi_Demo ;		//
	
	Weight_Shiwu = (unsigned int)((float)Weight_Shiwu/GapValue); 	//			
  	
  return Weight_Shiwu;
}

#endif

#if CONFIG_LED == ENABLED
void LED_Init_Demo(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //LED端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
}
#endif

#if CONFIG_MP3 == ENABLED
static unsigned char Send_buf_Demo[10] = {0} ;
u8 a1;
void MP3_uart_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		a1 =USART_ReceiveData(USART1);	//读取接收到的数据

	} 

}

void MP3_USART1_Send_Data_Demo(unsigned char *Data,unsigned short Length)
{

	unsigned short i;


	for(i=0;i<Length;i++)
	{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, *Data++);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{}
	}

}
void MP3_Init_Demo(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	MP3_uart_init_Demo(9600);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟
	//MP3 BUSY jiao 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化		
}

/*****************************************************************************************************
 - 功能描述：串口发送一帧数据

*****************************************************************************************************/


void SendCmd_Demo(unsigned char len)
{

		MP3_USART1_Send_Data_Demo(Send_buf_Demo,len);

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

void DoSum_Demo( unsigned char *Str, unsigned char len)
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


void Uart_SendCMD_Demo(unsigned char CMD ,unsigned char feedback , unsigned int dat)
{
		
		while(BUSY == 0){}
    Send_buf_Demo[0] = 0x7e;    //保留字节
    Send_buf_Demo[1] = 0xff;    //保留字节
    Send_buf_Demo[2] = 0x06;    //长度
    Send_buf_Demo[3] = CMD;     //控制指令
    Send_buf_Demo[4] = feedback;//是否需要反馈
    Send_buf_Demo[5] = (unsigned char)(dat >> 8);//datah
    Send_buf_Demo[6] = (unsigned char)(dat);     //datal
		Send_buf_Demo[9] = 0xef;
    DoSum_Demo(&Send_buf_Demo[1],6);        //校验
    SendCmd_Demo(10);       //发送此帧数据
		
}


#endif

#if CONFIG_GPS == ENABLED
#include <string.h>
#include "stdio.h"

#define GPS_RXD_END          0
unsigned char GPS_RXD_Index = 0;
unsigned char GPS_States = 0;
char GPS_RXD[100];
char string_n[15];
char string_e[15];


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif

void GPS_uart_init_Demo(u32 bound){
  //GPIO端口设置
	int i=0;
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	for(i=0;i<6;i++)
	{
			string_e[i]='0';
		
	}
	string_e[3]='.';

	for(i=0;i<5;i++)
	{
			string_n[i]='0';		
	}
	string_n[2]='.';		
}

/* 根据空格分隔字符串 */ 
int partition(char *src, char *par, int pos) 
{ 
  int i,j; 

  i = pos; 

  //取到第一个非空格字符 
  if(src[i] == ',') 
  { 
    ++i; 
  } 
 
  if(src[i] != '\0') 
  { 
    j = 0; 
    while((src[i] != '\0') && (src[i] != ',')) 
    { 
      par[j] = src[i]; 
      ++i; 
      ++j; 
    }
    if(j==0)
	{
	  par[0]='0'; 
    par[1]='\0';
	  return i; 	  
	}
    par[j]='\0'; 
 
    return i; 
  } 
  else 
  { 
    return -1; 
  } 
}
//GPS数据解析

//$GPRMC,055607.00,A,3959.44811,N,11625.31055,E,2.312,,300317,,,A*78
//$GPRMC,055609.00,A,3959.44931,N,11625.31260,E,0.802,,300317,,,A*79

//20180424定位数据
//$GPRMC,123824.000,A,3300.8520,N,11237.0341,E,0.00,0.00,240418,,,A*6460

//$GPGGA,124123.000,3300.8535,N,11237.0404,E,6,05,2.0,96.8,M,0.0,M,,*51
//$GPGGA,124521.000,3300.8496,N,11237.0337,E,1,06,2.1,109.9,M,0.0,M,,*6B
//$GPGGA,124932.000,3300.8753,N,11237.0498,E,6,05,9.4,77.6,M,0.0,M,,*5053

//$GPGGA,,,,,,0,00,99.99,,,,,,*48 99.99*30

int PraseGPGGA(void)
{
    // 拷贝一份用于分割
    char buf[100] = {0};
    strncpy(buf, GPS_RXD, sizeof(buf) - 1);

    // 字段指针数组
    char *fields[15] = {0};
    int fieldCount = 0;

    // 分割字段
    char *token = strtok(buf, ",*");
    while (token && fieldCount < 15) {
        fields[fieldCount++] = token;
        token = strtok(NULL, ",*");
    }

    // 检查字段数量
    if (fieldCount < 15) {
        return -1;
    }

    // 字段索引

	string_n[0]=fields[2][0];
	string_n[1]=fields[2][1];
	string_n[2]='.';
	string_n[3]=fields[2][2];
	string_n[4]=fields[2][3];

	string_e[0]=fields[4][0];
	string_e[1]=fields[4][1];
	string_e[2]=fields[4][2];
	string_e[3]='.';
	string_e[4]=fields[4][3];
	string_e[5]=fields[4][4];
    // 如有需要，可保存 HDOP、VDOP

    //rtinfo(gDebugType, "%s, PDOP:%2.1f, HDOP:%2.1f, VDOP:%2.1f.", __FUNCTION__, fPDOP, fHDOP, fVDOP);

    return 0;
}
void GPS_Processing(void)
{
	int i;
	int position,k;
	char partition_string[20];
	if(GPS_States & (1 << GPS_RXD_END))
	{
		GPS_States &= ~(1 << GPS_RXD_END);
			
   // strcpy(GPS_Value,"$GPGGA,124932.000,3300.8753,N,11237.0498,E,6,05,9.4,77.6,M,0.0,M,,*5053");
		position=0;
		k=0;
		if(GPS_RXD[0]=='$'&&GPS_RXD[1]=='G'&&GPS_RXD[2]=='P'&&GPS_RXD[3]=='G'&&GPS_RXD[4]=='G'&&GPS_RXD[5]=='A')
		{
			//用逗号分隔，k对应的为哪个位置的逗号
		  while((position = partition(GPS_RXD,partition_string,position)) != -1) 
		  { 
				++k;
				if(k==3)
				{
					memset(string_n, 0, sizeof(string_n));
					if(partition_string[1]!='\0')
					{
						string_n[0]=partition_string[0];
						string_n[1]=partition_string[1];
						string_n[2]='.';
						string_n[3]=partition_string[2];
						string_n[4]=partition_string[3];
						//string_n[5]=',';
						//string_n[6]=partition_string[5];
						string_n[5]='\0';

					}else
						//strcpy(string_n,partition_string);
						for(i=0;i<5;i++)
						{
							if(string_n[i]==0)
								string_n[i]='0';
							
						}
						string_n[2]='.';					

				}
				if(k==5)
				{
					memset(string_e, 0, sizeof(string_e));
					if(partition_string[1]!='\0')
					{
						string_e[0]=partition_string[0];
						string_e[1]=partition_string[1];
						string_e[2]=partition_string[2];
						string_e[3]='.';
						string_e[4]=partition_string[3];
						string_e[5]=partition_string[4];
						//string_e[6]=',';
						//string_e[7]=partition_string[6];
						string_e[6]='\0';

					}else					
						//strcpy(string_e,partition_string);
						for(i=0;i<6;i++)
						{
							if(string_e[i]==0)
								string_e[i]='0';
							
						}
						string_e[3]='.';

				}	

		  }
		}

	
	
	
	}
	
}
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 a;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		a =USART_ReceiveData(USART1);	//读取接收到的数据
		if(a == '$')
		{
			GPS_RXD_Index = 0;
			GPS_RXD[GPS_RXD_Index] = a;	
			GPS_RXD_Index++;
		}
		else if((a == '\r')&&(GPS_RXD[4]=='G')) //收到一帧完整数据   只接受$GPGGA这一帧数据
		{
		

			
			GPS_States |= (1 <<GPS_RXD_END); //标记GPS接收完成
			
			GPS_RXD[GPS_RXD_Index] = a;	
			GPS_RXD_Index++;
			GPS_RXD_Index = GPS_RXD_Index % 100;			
			GPS_Processing();	
			//PraseGPGGA();
			//将处理完的数据清除
			memset(GPS_RXD, 0, sizeof(GPS_RXD));

		}
		else
		{
			if(GPS_RXD[0]=='$')
			{
				GPS_RXD[GPS_RXD_Index] = a;	
				GPS_RXD_Index++;
				GPS_RXD_Index = GPS_RXD_Index % 100;
			}
		}	

	} 

}
void GPS_Init_Demo(void)
{
	GPS_uart_init_Demo(9600);
}

#endif

#if CONFIG_HEART_RATE == ENABLED
#include <stm32f10x_exti.h>
unsigned int xlTab[5];//心率数组
unsigned char count=0;	//心率滤波计数
unsigned int xinLater=0;//	心率延时处理
unsigned int xinLv =0;    //心率值
//外部中断初始化函数
void EXTIX_Init_Demo(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA15
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15	


    //GPIOA.0	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		

 
}

void EXTIX_TIM3_Int_Init_Demo(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
void heart_rate_init_demo(void)
{
	EXTIX_TIM3_Int_Init_Demo(49,7199);
	EXTIX_Init_Demo();
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		

			xinLater++;   
			if(xinLater>400)	//滤波滤掉手指未放情况
			{
				xinLv = 0; 	//滤波滤掉手指未放情况
				xinLater=0;
			}
		}
}

void EXTI0_IRQHandler(void)
{

		//OLED_ShowNum_Three_Demo(0,32,xinLater);
  if(xinLater>60)   //滤波防止抖动300ms
  {
    if(xinLater>400)		//滤波滤掉手指未放情况
    {
      xinLater =0;		//此时心率为0
    }
    else
    {
      xlTab[count++]=xinLater;//记录前后两次事件间隔 
      xinLater=0;
      if(count>=4)		//记录超过4次进行滤波处理
      {
        xinLv =60000/((xlTab[0]+xlTab[1]+xlTab[2]+xlTab[3])/4*5);//60000单位ms 表示60s /4求平均  *5每次定时5ms
 				if(xinLv<80)
					xinLv=0;
				else
					xinLv = xinLv-80;	
				count=0;		//清除本次记录
      }   
      xinLater =0;	//延时清零
    }
  }
	
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

#endif
#if CONFIG_GSM == ENABLED

u8 a3;
void GSM_USART3_ConfigDemo(u32 band)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;   
	NVIC_InitTypeDef    NVIC_InitStructure;  
		

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    

		
	//USART3?Tx---GPIO----PB.10----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//USART3?Rx---GPIO----PB11----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                      
		
	USART_InitStructure.USART_BaudRate=band;             
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                      
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART_Init(USART3,&USART_InitStructure);	        //

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //

	USART_Cmd(USART3,ENABLE);                           //

}

void gsm_init_demo(void)
{
	GSM_USART3_ConfigDemo(9600);
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void gsm_usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
 /*发送一个字节数据*/
 void gsm_usart3_send_byte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
}

void USART3_IRQHandler(void) //??1??????
{
	
	if(USART_GetFlagStatus(USART3,USART_IT_RXNE) != RESET)  //
	{			
		a3=USART_ReceiveData(USART3);
		

	
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);        //
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==RESET);	  //
	}
}
void SendNum(unsigned char num)
{
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('3');
	gsm_usart3_send_byte_Demo(0x30+num);	
}
void SendNum_char(unsigned char num)
{
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('3');
	gsm_usart3_send_byte_Demo(num);	
}
void SendTwoNum(unsigned char num)
{
		if(num>=100)
		   num = 99;
		SendNum(num/10);
		SendNum(num%10);	
}
#endif


#if CONFIG_BMP180 == ENABLED

//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

#include <math.h>
_bmp180 bmp180;

//BMP180初始化
//对使用的IIC端口进行初始化
void BMP_Init(void)
{
	IIC_Init();
}

//写一个数据到BMP180
void BMP_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite)
{
	IIC_Start();
	
	IIC_Send_Byte(0xEE);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(WriteAddr);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(DataToWrite);
	IIC_Wait_Ack();
	IIC_Stop();
}

//从BMP180读一个字节数据
uint8_t BMP_ReadOneByte(uint8_t ReadAddr)
{
	uint8_t data = 0;
	
	IIC_Start();
	
	IIC_Send_Byte(0xEE);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(ReadAddr);
	IIC_Wait_Ack();
	
	IIC_Start();
	
	IIC_Send_Byte(0xEF);
	IIC_Wait_Ack();
	
	data = IIC_Read_Byte(1);
	IIC_Stop();
	
	return data;
}

//从BMP180读一个16位的数据
short BMP_ReadTwoByte(uint8_t ReadAddr)
{
	short data;
	uint8_t msb,lsb;
	
	IIC_Start();
	
	IIC_Send_Byte(0xEE);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(ReadAddr);
	IIC_Wait_Ack();
	
	IIC_Start();
	
	IIC_Send_Byte(0xEF);
	IIC_Wait_Ack();
	
	msb = IIC_Read_Byte(1);
	lsb = IIC_Read_Byte(0);
	
	IIC_Stop();
	
	data = msb*256 + lsb;
	
	return data;
}

//从BMP180的获取计算参数
void BMP_ReadCalibrationData(void)
{
	bmp180.AC1 = BMP_ReadTwoByte(0xAA);
	bmp180.AC2 = BMP_ReadTwoByte(0xAC);
	bmp180.AC3 = BMP_ReadTwoByte(0xAE);
	bmp180.AC4 = BMP_ReadTwoByte(0xB0);
	bmp180.AC5 = BMP_ReadTwoByte(0xB2);
	bmp180.AC6 = BMP_ReadTwoByte(0xB4);
	bmp180.B1  = BMP_ReadTwoByte(0xB6);
	bmp180.B2  = BMP_ReadTwoByte(0xB8);
	bmp180.MB  = BMP_ReadTwoByte(0xBA);
	bmp180.MC  = BMP_ReadTwoByte(0xBC);
	bmp180.MD  = BMP_ReadTwoByte(0xBE);
}

//从BMP180读取未修正的温度
long BMP_Read_UT(void)
{
	long temp = 0;
	BMP_WriteOneByte(0xF4,0x2E);
	
	delay_ms(5);
	temp = (long)BMP_ReadTwoByte(0xF6);
	return temp;
}

//从BMP180读取未修正的大气压
long BMP_Read_UP(void)
{
	long pressure = 0;
	
	BMP_WriteOneByte(0xF4,0x34);
	delay_ms(5);
	
	pressure = (long)BMP_ReadTwoByte(0xF6);
	//pressure = pressure + BMP_ReadOneByte(0xf8);
	pressure &= 0x0000FFFF;
	
	return pressure;
}

//用获取的参数对温度和大气压进行修正，并计算海拔
void BMP_UncompemstatedToTrue(void)
{
	bmp180.UT = BMP_Read_UT();//第一次读取错误
	bmp180.UT = BMP_Read_UT();//进行第二次读取修正参数
	bmp180.UP = BMP_Read_UP();
	
	bmp180.X1 = ((bmp180.UT - bmp180.AC6) * bmp180.AC5) >> 15;
	bmp180.X2 = (((long)bmp180.MC) << 11) / (bmp180.X1 + bmp180.MD);
	bmp180.B5 = bmp180.X1 + bmp180.X2;
	bmp180.Temp  = (bmp180.B5 + 8) >> 4;
	
	bmp180.B6 = bmp180.B5 - 4000;
	bmp180.X1 = ((long)bmp180.B2 * (bmp180.B6 * bmp180.B6 >> 12)) >> 11;
	bmp180.X2 = ((long)bmp180.AC2) * bmp180.B6 >> 11;
	bmp180.X3 = bmp180.X1 + bmp180.X2;
	
	bmp180.B3 = ((((long)bmp180.AC1) * 4 + bmp180.X3) + 2) /4;
	bmp180.X1 = ((long)bmp180.AC3) * bmp180.B6 >> 13;
	bmp180.X2 = (((long)bmp180.B1) *(bmp180.B6*bmp180.B6 >> 12)) >>16;
	bmp180.X3 = ((bmp180.X1 + bmp180.X2) + 2) >> 2;
	bmp180.B4 = ((long)bmp180.AC4) * (unsigned long)(bmp180.X3 + 32768) >> 15;
	bmp180.B7 = ((unsigned long)bmp180.UP - bmp180.B3) * 50000;
	
	if(bmp180.B7 < 0x80000000)
	{
		bmp180.p = (bmp180.B7 * 2) / bmp180.B4;		
	}
	else
	{
		bmp180.p = (bmp180.B7 / bmp180.B4) * 2;
	}
	
	bmp180.X1 = (bmp180.p >> 8) * (bmp180.p >>8);
	bmp180.X1 = (((long)bmp180.X1) * 3038) >> 16;
	bmp180.X2 = (-7357 * bmp180.p) >> 16;
	
	bmp180.p = bmp180.p + ((bmp180.X1 + bmp180.X2 + 3791) >> 4);
	
	bmp180.altitude = 44330 * (1-pow(((bmp180.p) / 101325.0),(1.0/5.255)));  //值为m 100820Pa返回 42M
}

#endif

#if CONFIG_ESP8266 == ENABLED
u8 a1;
void esp8266_uart1_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}


void esp8266_UART1_Send_Byte_Demo(unsigned char a)
{

	USART_SendData(USART1,a); //开始发送
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	USART_ClearFlag(USART1,USART_FLAG_TXE);
}


void esp8266_UART1_Send_String_Demo(unsigned char *Index)
{

	while(*Index)//检测字符串结束符
	{
		esp8266_UART1_Send_Byte_Demo(*Index++);//发送当前字符
	}

}



void esp8266_USART1_Send_Data_Demo(unsigned char *Data,unsigned short Length)
{

	unsigned short i;


	for(i=0;i<Length;i++)
	{
		/* Place your implementation of fputc here */
		/* e.g. write a character to the USART */
		USART_SendData(USART1, *Data++);
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{}
	}

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 revTemp=0;
	static u8 StartFlag=0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		revTemp = USART_ReceiveData(USART1);
		if(StartFlag==0)
		{			
			if(revTemp=='@')
			{
				StartFlag=1;
			}
		}else
		{
			a1 = revTemp;
			StartFlag=0;
		}
		//a1 =USART_ReceiveData(USART1);	//读取接收到的数据

	} 

}
/******************************************************************** 
名称：WIFI模块设置函数  作用: 启动模块，以便可以实现无线接入和控制  
********************************************************************/ 
void ESP8266_Set(unsigned char *puf) 
	{                        	// 数组指针*puf指向字符串数组
    while(*puf!='\0') 
		{  		//遇到空格跳出循环
        esp8266_UART1_Send_Byte_Demo(*puf);  		//向WIFI模块发送控制指令。
        puf++;
    }
    delay_ms(5);
    esp8266_UART1_Send_Byte_Demo('\r'); 			//回车
    delay_ms(5);
    esp8266_UART1_Send_Byte_Demo('\n');   			//换行
}
void Esp8266_init(void)
{
		esp8266_uart1_init_Demo(9600);
		delay_ms(100);
	  ESP8266_Set((u8*)"AT+CWMODE=2"); 							//设置路由器模式1 station,模式2 AP,模式3 station+AP混合模式   设置前wifi的波特率设置成9600
    delay_ms(300);
    //ESP8266_Set((u8*)"AT+RST"); 									//重新启动wifi模块
    delay_ms(300);
//    ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  设置模块SSID:WIFI, PWD:密码 及安全类型加密模式（WPA2-PSK）
    ESP8266_Set((u8*)"AT+CWSAP=\"wifi_yuxia\",\"12345678\",11,4");
    delay_ms(300);
//    ESP8266_Set("AT+CIPMUX=1");								//开启多连接模式，允许多个各客户端接入
    ESP8266_Set((u8*)"AT+CIPMUX=1");								//开启单连接模式
    delay_ms(300);
    ESP8266_Set((u8*)"AT+CIPSERVER=1,5000");  					//启动TCP/IP 实现基于网络//控制 	ESP8266_Set("AT+CIPSERVER=1,5000");
    delay_ms(500);
    ESP8266_Set((u8*)"AT+CIPSTO=0"); 
    delay_ms(500);	
}

#endif

#if CONFIG_MPU6050 == ENABLED

void I2C_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	
	
	RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin=I2C_SCL|I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}

void I2C_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

//产生起始信号
void I2C_Start(void)
{
    I2C_SDA_OUT();
	
	I2C_SDA_H;
	I2C_SCL_H;
	delay_us(5);
	I2C_SDA_L;
	delay_us(6);
	I2C_SCL_L;
}

//产生停止信号
void I2C_Stop(void)
{
   I2C_SDA_OUT();

   I2C_SCL_L;
   I2C_SDA_L;
   I2C_SCL_H;
   delay_us(6);
   I2C_SDA_H;
   delay_us(6);
}

//主机产生应答信号ACK
void I2C_Ack(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_L;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}

//主机不产生应答信号NACK
void I2C_NAck(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_H;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}
//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
u8 I2C_Wait_Ack(void)
{
	u8 tempTime=0;

	I2C_SDA_IN();

	I2C_SDA_H;
	delay_us(1);
	I2C_SCL_H;
	delay_us(1);

	while(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C_Stop();
			return 1;
		}	 
	}

	I2C_SCL_L;
	return 0;
}
//I2C 发送一个字节
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_us(2); //发送数据
		I2C_SCL_L;
		delay_us(2);
	}
}

//I2C 读取一个字节

u8 I2C_Read_Byte(u8 ack)
{
   u8 i=0,receive=0;

   I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C_SCL_L;
		delay_us(2);
		I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
		   receive++;
		delay_us(1);	
   }

   	if(ack==0)
	   	I2C_NAck();
	else
		I2C_Ack();

	return receive;
}


void PMU6050_WriteReg(u8 reg_add,u8 reg_dat)
{
	I2C_Start();
	I2C_Send_Byte(MPU6050_SLAVE_ADDRESS);
	I2C_Wait_Ack();
	I2C_Send_Byte(reg_add);
	I2C_Wait_Ack();
	I2C_Send_Byte(reg_dat);
	I2C_Wait_Ack();
	I2C_Stop();
}

void PMU6050_ReadData(u8 reg_add,unsigned char*Read,u8 num)
{
	unsigned char i;
	
	I2C_Start();
	I2C_Send_Byte(MPU6050_SLAVE_ADDRESS);
	I2C_Wait_Ack();
	I2C_Send_Byte(reg_add);
	I2C_Wait_Ack();
	
	I2C_Start();
	I2C_Send_Byte(MPU6050_SLAVE_ADDRESS+1);
	I2C_Wait_Ack();
	
	for(i=0;i<(num-1);i++){
		*Read=I2C_Read_Byte(1);
		Read++;
	}
	*Read=I2C_Read_Byte(0);
	I2C_Stop();
}

void MPU6050_Init(void)
{
	
	
	I2C_Init1();

//	MPU6050_PWR_MGMT_1_INIT();
	PMU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	     //解除休眠状态
	PMU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //陀螺仪采样率
	PMU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	
	PMU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);	  //配置加速度传感器工作在16G模式
	PMU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	
	
	delay_ms(100);
//	MPU6050_PWR_MGMT_1_INIT();
	PMU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	     //解除休眠状态
	PMU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //陀螺仪采样率
	PMU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	
	PMU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);	  //配置加速度传感器工作在16G模式
	PMU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	
	
}

void MPU6050ReadID(void)
{
	unsigned char Re = 0;
    PMU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //读器件地址
     //printf("%d\r\n",Re);
}
void MPU6050ReadAcc(short *accData)
{
    u8 buf[6];
    PMU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = ((buf[0] << 8) | buf[1])/172;
    accData[1] = ((buf[2] << 8) | buf[3])/172;
    accData[2] = ((buf[4] << 8) | buf[5])/172;
}
void MPU6050ReadGyro(short *gyroData)
{
    u8 buf[6];
    PMU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

void MPU6050ReadTemp(short *tempData)
{
	u8 buf[2];
    PMU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
    *tempData = (buf[0] << 8) | buf[1];
}

void MPU6050_ReturnTemp(short*Temperature)
{
	short temp3;
	u8 buf[2];
	
	PMU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
  temp3= (buf[0] << 8) | buf[1];
	*Temperature=(((double) (temp3 + 13200)) / 280)-13;
}


#endif

#if CONFIG_GSM_TXRX == ENABLED


u8 a3;
u8 send_flag;
u8 sim_status=0;

volatile unsigned char UART3_RXD[UART3_RXD_SIZE];
volatile unsigned char UART3_RXD_Time = 0;
volatile unsigned int UART3_RXD_Index = 0;
volatile unsigned char UART3_Status_Registe = 0;
volatile unsigned char GPRS_Time_Counter = 100;
volatile unsigned char SMS_States_Register = 0;
volatile unsigned char SMS_CMD_Register = 0;
volatile unsigned int SIM800_CMD_Register = 0;
volatile unsigned char GPRS_States_Registe = 0;
volatile unsigned char SMS_Retry = SMS_RETYR_CONST;
volatile unsigned char SMS_States_Register;
volatile unsigned int SMS_Time_Cnt = 0;
void gsm_TIM2_Int_Init_demo(u16 Period,u16 Prescaler)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 			//时钟使能

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);   						//使能或者失能指定的TIM中断
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn;//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
	TIM_Cmd(TIM2, ENABLE);  										//使能TIMx外设							 
}

void TIM2_IRQHandler(void) 
{

   static unsigned char Time0_100ms_Counter = 0;	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 

        if (UART3_RXD_Time)//20ms
        {
            if (--UART3_RXD_Time == 0) //串口接收超时
            {
                UART3_Status_Registe |= 1 << UART3_RXD_END;

            }
        }
        if (++Time0_100ms_Counter >= 5)//用于注册的间隔时间
        {
            Time0_100ms_Counter = 0;


            if (GPRS_Time_Counter)
            {
                GPRS_Time_Counter--;
            }

        }				
	}
}
void UART3_RXD_CLR(void)
{
    unsigned int i;

    for (i = 0; i < UART3_RXD_SIZE; i++)
    {
        UART3_RXD[i] = 0;
    }
    UART3_Status_Registe &= ~(1 << UART3_RXD_END); //串口收到的数据已经处理完
    UART3_RXD_Index = 0;

}


void GSMTXRX__USART3_ConfigDemo(u32 band)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;   
	NVIC_InitTypeDef    NVIC_InitStructure;  
		

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    

		
	//USART3?Tx---GPIO----PB.10----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//USART3?Rx---GPIO----PB11----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                      
		
	USART_InitStructure.USART_BaudRate=band;             
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                      
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART_Init(USART3,&USART_InitStructure);	        //

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //

	USART_Cmd(USART3,ENABLE);                           //

}

/*串口3 发送数据到上位机 data 以\0结尾*/
void gsmtxrx_usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	//printf("%s",data);
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //向串口2发送数据
		
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
 /*发送一个字节数据*/
 void gsmtxrx_usart3_send_byte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
	      //printf("%s",&SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
}



void USART3_IRQHandler(void) //??1??????
{
	
	if(USART_GetFlagStatus(USART3,USART_IT_RXNE) != RESET)  //
	{			
		a3=USART_ReceiveData(USART3);
		

		UART3_RXD_Time = UART3_RXD_TIME;  //重置串口接收超时

		UART3_RXD[UART3_RXD_Index] = a3;

		UART3_RXD_Index++;

		UART3_RXD_Index = UART3_RXD_Index % UART3_RXD_SIZE;	
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);        //
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==RESET);	  //
	}
}
void SMS_Init(void)
{
	  //文本模式
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);

    //直接配置为短信过来直接显示出来
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //配置短信显示模式
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //配置短信显示模式
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //配置短信显示模式
    delay_ms(200);

}
void GPRS_CREG(void)
{
    
    if ((~GPRS_States_Registe) & (1 << GPRS_AT_CREG)) //没有注册成功 继续注册
    {
        if (GPRS_Time_Counter == 0)
        {

            SIM800_CMD_Register = 0;

            gsmtxrx_usart3_SendString_Demo((u8*)" AT&F\r\n"); //恢复出厂默认设置
            gsmtxrx_usart3_SendString_Demo((u8*)" ATE0\r\n"); //取消回显示
            gsmtxrx_usart3_SendString_Demo((u8*)" AT+CREG?\r\n");  //模块注册
    
            SMS_Init();


            GPRS_Time_Counter = 100; //25s超时
        }
        else
        {

            if (SIM800_CMD_Register & (1 << CMD_CREG)) //收到模块返回数据
            {
                GPRS_States_Registe |= (1 << GPRS_AT_CREG); //收到模块回复CREG信息
                SIM800_CMD_Register &= ~(1 << CMD_CREG); //清空标志
            }

        }
    }
    else
    {


    }
}
char hand(char *str)
{
    char *strx = 0;
    strx = strstr((const char *)(UART3_RXD), (const char *)str);
    return ((strx != NULL) ? 1 : 0);
}
void SIM800_CMD_Coding(void)
{

//AT+CMGF=1
//AT+CNMI=2,2,0,1 收到短信内容直接显示出来
//+CMT: "+8613403779870","","17/11/26,14:09:46+32"
//close

    if (hand("+CMT:")) //收到新短信
    {

        SMS_States_Register |= (1 << SMS_RXD_CMTI);


    }

    if (hand("+CMGR:")) //读到短信内容
    {

    }

    if (hand("+CMGS:"))  //短信发送完成
    {
        SMS_CMD_Register |= (1 << SMS_CMGS);
			  //gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n"); 

    }
    if (hand("SMS Ready")) 
    {
				

    }
    if (hand("READY"))
    {
        SIM800_CMD_Register |= (1 << CMD_READY);
    }
    if (hand(">"))
    {
        SMS_CMD_Register |= (1 << SMS_WaitData);
        SIM800_CMD_Register |= (1 << CMD_WaitData);
    }

    if (hand("SEND OK"))
    {
        SIM800_CMD_Register |= (1 << CMD_SendOK);
    }


     //可正常收到数据，AT+CREG?
    if (hand("+CREG: 0,1"))
    {
        sim_status=1;
        SIM800_CMD_Register |= (1 << CMD_CREG);
        GPRS_States_Registe |= (1 << GPRS_AT_CREG);
    }
    if (hand("+CREG: 0,5"))
    {
        sim_status=1;
        SIM800_CMD_Register |= (1 << CMD_CREG);
        GPRS_States_Registe |= (1 << GPRS_AT_CREG);
    }
    //无法接收到短信，AT+CREG?
    if (hand("+CREG: 0,2"))
    {

       // SIM800_CMD_Register |= (1 << CMD_CREG);
       // GPRS_States_Registe |= (1 << GPRS_AT_CREG);
    }

    if (hand("+CGATT: 1"))
    {
        SIM800_CMD_Register |= (1 << CMD_CGATT1);
    }
    if (hand("+CGATT: 0"))
    {
        SIM800_CMD_Register |= (1 << CMD_CGATT0);
    }
    if (hand("ERROR"))
    {
        SMS_CMD_Register |= (1 << SMS_ERROR); //接收错误
        SIM800_CMD_Register |= (1 << CMD_ERROR);
    }
    if (hand("CONNECT OK"))
    {
        SIM800_CMD_Register |= (1 << CMD_CONNECT_OK);
    }
    if (hand("OPEN")) //读取短信数据
    {

    }
    if (hand("CLOSE")) //读取短信数据
    {
       // SIM800_CMD_Register |= (1 << CMD_CLOSE);

    }
    if (hand("DATA")) //读取短信数据，接收到数据后要发送，需要延时1秒左右才发送
    {
			send_flag = 1;
      //Lcd1602_Display_String(1,5,(u8*)"DATA ");
    }		
    if (hand("SET"))  //收到新短信
    {


    }

    if (hand("RING") | hand("CRING")) //有来电
    {

        SIM800_CMD_Register |= (1 << CMD_RING);
    }

    if (hand("OK"))
    {

        SMS_CMD_Register |= (1 << SMS_RXD_OK);
        SIM800_CMD_Register |= (1 << CMD_OK);
    }
    else;


    if (hand("SHUT OK"))
    {
        SIM800_CMD_Register |= (1 << CMD_SHUT_OK);
    }
    else;

    if (hand("NO CARRIER"))
    {
        SIM800_CMD_Register |= (1 << CMD_NO_CARRIER);
    }

    UART3_RXD_CLR();
}


void UART3_Processing(void)
{

    if (UART3_Status_Registe & (1 << UART3_RXD_END)) //收到串口数据
    {

        SIM800_CMD_Coding();//

        UART3_RXD_CLR();
        UART3_Status_Registe &= ~(1 << UART3_RXD_END);
    }


    if (SIM800_CMD_Register & (1 << CMD_RING))
    {

        //UART0_Send_String("ATH\r\n"); //直接挂断

        //SMS_Retry = 5;
        SMS_States_Register |= (1 << SMS_TXD_ENA); //发送短信
        SIM800_CMD_Register &= ~(1 << CMD_RING);
    }

}

void SMS_Send(u8* num,u8* data)
{
    static volatile unsigned char SMS_Step = 0;

    if (SMS_Retry == 0)
    {
        //超过发送重试次数,不再发送
        SMS_States_Register &= ~(1 << SMS_TXD_ENA);
        return;
    }

    if (SMS_Time_Cnt) //超时时间
    {
        SMS_Time_Cnt--;
    }

    switch (SMS_Step)
    {

    case 0:
        SMS_CMD_Register = 0; //清空接收状态

        gsmtxrx_usart3_SendString_Demo((u8*)" AT+CMGF=1\r\n"); //设置短信模式
        SMS_Step++;
        SMS_Time_Cnt = 20; //1秒
        if (SMS_Retry) SMS_Retry--; //重试次数-1
        break;

    case 1:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //超时无应答,或者指令错误
            SMS_Step = 0;
        }

        if (SMS_CMD_Register & (1 << SMS_RXD_OK))
        {

            SMS_CMD_Register = 0; //清空接收状态

            gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGS=\""); //设置接收短信号码
            gsmtxrx_usart3_SendString_Demo(num);  //
            gsmtxrx_usart3_SendString_Demo((u8*)"\"\r\n");
            SMS_Step++;
            SMS_Time_Cnt = 60; //3秒
        }

        break;

    case 2:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //超时无应答,或者指令错误
            SMS_Step = 0;
            gsmtxrx_usart3_send_byte_Demo(0x1A);  //内容结束

        }

        if (SMS_CMD_Register & (1 << SMS_WaitData)) //等待<
        {

            SMS_CMD_Register = 0; //清空接收状态

            gsmtxrx_usart3_SendString_Demo(data); //发送短信内容

            gsmtxrx_usart3_send_byte_Demo(0x1A);  //内容结束
            SMS_Step++;
            SMS_Time_Cnt = 180; //9.3秒
        }
        break;

    case 3:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //超时无应答,或者指令错误
            SMS_Step = 0;
            gsmtxrx_usart3_send_byte_Demo(0x1A);  //内容结束
            if (SMS_Retry) SMS_Retry--; //重试次数-1

        }

        if (SMS_CMD_Register & (1 << SMS_CMGS) || (SMS_CMD_Register & (1 << SMS_RXD_OK)))
        {
            //短信发送成功
            SMS_States_Register &= ~(1 << SMS_TXD_ENA);


            SMS_CMD_Register = 0;
            SMS_Time_Cnt = 120; //6秒
            SMS_Step = 0;
        }
        break;

    default:
        SMS_Step = 0;
        break;

    }

}


void SMS_Processing(u8* num,u8* data)
{
    //未注册时，间隔时间查询注册
    GPRS_CREG();

		if ((GPRS_States_Registe) & (1 << GPRS_AT_CREG)) //注册上网络才允许发送短信
		{
				if (SMS_States_Register & (1 << SMS_TXD_ENA)) //有短信需要发送
				{
					  //发送数据
						SMS_Send(num,data);
				}
		}
    
    //处理接收到的数据
    UART3_Processing();

}
void gsm_txrx_init(void)
{
   GSMTXRX__USART3_ConfigDemo(9600);	
	 gsm_TIM2_Int_Init_demo(200, 7200);//20mw
}
#endif

#if CONFIG_ADXL345 == ENABLED


unsigned char BUF[8];                         //接收数据缓存区      	
unsigned char ge,shi,bai,qian,wan;           //显示变量
unsigned char err;
float temp_X,temp_Y,temp_Z;

void SCL_Set_Output_ADXL345(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN_ADXL345;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SCL_GPIO_ADXL345, &GPIO_InitStructure);					 					
}	

void SDA_Set_Output_ADXL345(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_ADXL345;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_ADXL345, &GPIO_InitStructure);					 					
}	

void SDA_Set_Input_ADXL345(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_ADXL345;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_ADXL345, &GPIO_InitStructure);					 
}



/**************************************
起始信号
**************************************/
void ADXL345_Start(void)
{
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    SET_SDA_ADXL345();//SDA = 1;                    //拉高数据线
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//Delay5us();                 //延时
    CLE_SDA_ADXL345();//SDA = 0;                    //产生下降沿
    delay_us(2);//Delay5us();                 //延时
    CLE_SCL_ADXL345();//SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop(void)
{
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    CLE_SDA_ADXL345();//SDA = 0;                    //拉低数据线
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//Delay5us();                 //延时
    SET_SDA_ADXL345();//SDA = 1;                    //产生上升沿
    delay_us(2);//Delay5us();                 //延时
    CLE_SCL_ADXL345();
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(unsigned char ack)
{   
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    if(ack==0)//SDA = ack;                  //写应答信号
    {
      CLE_SDA_ADXL345();
    }
    else
    {
      SET_SDA_ADXL345();
    }
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//Delay5us();                 //延时
    CLE_SCL_ADXL345();//SCL = 0;                    //拉低时钟线
    delay_us(5);//Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
unsigned char ADXL345_RecvACK(void)
{
    SDA_INT_ADXL345();
    SCL_OUT_ADXL345();
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//    Delay5us();                 //延时
    SET_SCL_ADXL345();
    if(SDA_VAL_ADXL345()== Bit_SET)   //CY = SDA;                   //读应答信号
    {
      err = 1;
    }
    else
    {
      err = 0;
    }
 
    CLE_SCL_ADXL345() ;//SCL = 0;                    //拉低时钟线
    delay_us(5);//    Delay5us();                 //延时
    SDA_OUT_ADXL345();
    return err;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(unsigned char dat)
{
    unsigned char i;
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    for (i=0; i<8; i++)         //8位计数器
    {
        delay_us(5);             //延时
        if(dat&0x80)  //SDA = CY;               //送数据口
        {SET_SDA_ADXL345();}
        else
        {CLE_SDA_ADXL345();}       
        delay_us(5);             //延时
        SET_SCL_ADXL345();//SCL = 1;                //拉高时钟线
        delay_us(5);             //延时
        CLE_SCL_ADXL345();//SCL = 0;                //拉低时钟线
        dat <<= 1;              //移出数据的最高位
    }
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
unsigned char ADXL345_RecvByte(void)
{
    unsigned char i;
    unsigned char Mid;
    unsigned char dat = 0;
    SDA_INT_ADXL345();
    SCL_OUT_ADXL345();

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        delay_us(5);            //延时
        SET_SCL_ADXL345();

			if(SDA_VAL_ADXL345()== Bit_SET)   //CY = SDA;                   //读应答信号
			{
				Mid = 1;
			}
			else
			{
				Mid = 0;
			}
		
//        Mid=SDA_VAL();
        if(Mid) dat++;
        delay_us(5);     
        CLE_SCL_ADXL345();//SCL = 0;                //拉低时钟线
    }
    return dat;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
unsigned char Single_Read_ADXL345(unsigned char REG_Address)
{  unsigned char REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);            //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //停止信号
    return REG_data; 
}
//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_Read_ADXL345(void)
{   unsigned char i;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(0x32);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //回应ACK
       }
   }
    ADXL345_Stop();                          //停止信号
    delay_ms(5);
}


//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345(void)
{
   Single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
   Single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}
//***********************************************************************
//显示x轴
void ReadData_x(void)
{   
  int  dis_data;                       //变量
  Multiple_Read_ADXL345();       	//连续读出数据，存储在BUF中
  dis_data=(BUF[1]<<8)+BUF[0];  //合成数据   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_X=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
  dis_data=(BUF[3]<<8)+BUF[2];  //合成数据   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_Y=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
  dis_data=(BUF[5]<<8)+BUF[4];    //合成数据   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_Z=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
}

#endif

#if CONFIG_CARSPEED == ENABLED
typedef struct
{
	FlagStatus Egde;//Egde = SET表示当前处于高电平;Egde = RESET表示当前处于低电平;
	u8 ucFinishFlag;//捕获结束标记
	u16 usCaptureRisingVal;//输入捕获值
	u16 usUpdateCnt;//计数溢出次数
	u32 ulFrequency;//输入波形的频率
	
}WaveCapture;
#define GENERAL_TIM4_Period    0xffff
#define GENERAL_TIM4_Prescaler  72
WaveCapture waveCapture = {RESET,0,0,0,0};
u32 ulFrequency_dat;
unsigned int dat[30];
unsigned char fil_Cnt = 0;
unsigned int Speed_dat = 0;
unsigned int filter(unsigned int arr[] , unsigned char num , unsigned char delt)
{
    unsigned int count, i, j, temp;
    //unsigned int value_buf[N];
    unsigned long  sum = 0;
    for( j = 0; j < num - 1; j++ )
    {
        for( i = 0; i < num - j - 1; i++ )
        {
            if( arr[i] > arr[i + 1] )
            {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
    for( count = delt; count < num - delt; count++ )
    {
			sum += arr[count];
    }
    return ( unsigned int )( sum / ( num - (delt*2) ) );
}







void	Tim4GpioInit(void);
void	Tim4ModeInit(void);
void	Tim4NvicInit(void);
	
void Tim4Init(void)//Timer4配置为输入捕获模式，产生1个通道输入捕获，可扩展
{
	Tim4GpioInit();
	Tim4ModeInit();
	Tim4NvicInit();
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update|TIM_IT_CC1);					//清除溢出中断标志
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);				//开启TIM2的中断
	TIM_Cmd(TIM4, ENABLE);
	
}

void	Tim4GpioInit(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;

  // Timer4输入捕获通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;  //CH1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_ResetBitS(GPIOB,GPIO_Pin_6);
}
void	Tim4ModeInit(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_DeInit(TIM4);										//重新将Timer设置为缺省值
	TIM_InternalClockConfig(TIM4);							//采用内部时钟给TIM4提供时钟源
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)(GENERAL_TIM4_Prescaler-1);//例如prescaler=72;			//预分频系数为72-1，这样计数器时钟为72MHz/72 = 1MHz。注意：预分频系数取值范围为1-65535
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//设置计数器模式为向上计数模式
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM4_Period-1;		//设置计数溢出大小，每计period个数就产生一个更新事件
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);			//将配置应用到TIM4中
	TIM_ARRPreloadConfig(TIM4, DISABLE);					//禁止ARR预装载缓冲器
	
	TIM_ICInitStruct.TIM_Channel =  TIM_Channel_1;
  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter = 0x00;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	
	TIM_ICInit(TIM4, & TIM_ICInitStruct);
	
}
void	Tim4NvicInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// 配置TIM中断	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;      	// 选择TIM4的中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	// 抢占式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		// 响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			// 中断使能
	NVIC_Init(&NVIC_InitStructure);							// 配置中断
}




unsigned int filter(unsigned int arr[] , unsigned char num , unsigned char delt);
u32 count;
void  TIM4_IRQHandler(void)
{
	//if(waveCapture.ucFinishFlag == 0)
	{	
		if ( TIM_GetITStatus( TIM4, TIM_IT_Update) != RESET ) 
		{	
			//----------------------------------------------------------
			//填充用户代码 Add User Code
			//if(	waveCapture.Egde == SET)
				waveCapture.usUpdateCnt ++;
			if(waveCapture.usUpdateCnt > 10)//10
			{
				fil_Cnt = 0;
				Speed_dat = 0;
				waveCapture.usCaptureRisingVal = 0;
				waveCapture.usUpdateCnt = 0;
				waveCapture.Egde = RESET;
				waveCapture.ulFrequency = 0;
				waveCapture.ucFinishFlag  = 0;
			}
			//---------------------------------------------------------
			//TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);  		 
		}	
		
		if ( TIM_GetITStatus( TIM4, TIM_IT_CC1) != RESET ) 
		{	
			//----------------------------------------------------------
			//填充用户代码 Add User Code
			count++;
			if(waveCapture.Egde == RESET)//第一次捕获到上升沿
			{
				waveCapture.usCaptureRisingVal = 0;
				waveCapture.usUpdateCnt = 0;
				waveCapture.Egde = SET;
				TIM_SetCounter(TIM4, 0);
			}
			else
			{
				
				waveCapture.usCaptureRisingVal = TIM_GetCapture1(TIM4);
				ulFrequency_dat = 1000000/(waveCapture.usUpdateCnt * 65536 +waveCapture.usCaptureRisingVal );
				//if(ulFrequency_dat < 300)
				{
					waveCapture.ulFrequency = ulFrequency_dat;
					waveCapture.ucFinishFlag  = 1;
				}
				waveCapture.usCaptureRisingVal = 0;
				waveCapture.usUpdateCnt = 0;
				waveCapture.Egde = RESET;
				waveCapture.ucFinishFlag  = 1;
			}
			//---------------------------------------------------------
			//TIM_ClearITPendingBit(TIM4 , TIM_IT_CC1);  		 
		}
		if(waveCapture.ucFinishFlag == 1)
		{
			
			waveCapture.ucFinishFlag  = 0;
			
			if(fil_Cnt<30)
			{
				dat[fil_Cnt] = waveCapture.ulFrequency;
				fil_Cnt++;
			}
			else
			{
				fil_Cnt = 0;
				Speed_dat = filter(dat,30,10);
			}
		}
	}
	//else
		TIM_ClearITPendingBit(TIM4 , TIM_IT_Update|TIM_IT_CC1);  
  	
}

#endif

#if CONFIG_RC522 == ENABLED
static void             RC522_SPI_Config             ( void );

#include <stdio.h>

void RC522_Init ( void )
{
	RC522_SPI_Config ();
	
	macRC522_Reset_Disable();
	
	macRC522_CS_Disable();

}


static void RC522_SPI_Config ( void )
{
  /* SPI_InitTypeDef  SPI_InitStructure */
  GPIO_InitTypeDef GPIO_InitStructure;  
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试	
	/*!< Configure SPI_RC522_SPI pins: CS */
	macRC522_GPIO_CS_CLK_FUN ( macRC522_GPIO_CS_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_CS_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_CS_Mode;
  GPIO_Init(macRC522_GPIO_CS_PORT, &GPIO_InitStructure);
	
  /*!< Configure SPI_RC522_SPI pins: SCK */
	macRC522_GPIO_SCK_CLK_FUN ( macRC522_GPIO_SCK_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_SCK_Mode;
  GPIO_Init(macRC522_GPIO_SCK_PORT, &GPIO_InitStructure);
	
  /*!< Configure SPI_RC522_SPI pins: MOSI */
	macRC522_GPIO_MOSI_CLK_FUN ( macRC522_GPIO_MOSI_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_MOSI_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_MOSI_Mode;
  GPIO_Init(macRC522_GPIO_MOSI_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_RC522_SPI pins: MISO */
	macRC522_GPIO_MISO_CLK_FUN ( macRC522_GPIO_MISO_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_MISO_Mode;
  GPIO_Init(macRC522_GPIO_MISO_PORT, &GPIO_InitStructure);	
	
	
  /*!< Configure SPI_RC522_SPI pins: RST */
	macRC522_GPIO_RST_CLK_FUN ( macRC522_GPIO_RST_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_RST_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_RST_Mode;
  GPIO_Init(macRC522_GPIO_RST_PORT, &GPIO_InitStructure);
	
}

/*
 * 函数名：SPI_RC522_SendByte
 * 描述  ：向RC522发送1 Byte 数据
 * 输入  ：byte，要发送的数据
 * 返回  : RC522返回的数据
 * 调用  ：内部调用
 */
void SPI_RC522_SendByte ( u8 byte )
{
    u8 counter;
	
	
    for(counter=0;counter<8;counter++)
    {     
			if ( byte & 0x80 )
					macRC522_MOSI_1 ();
			else 
					macRC522_MOSI_0 ();

//			Delay_us ( 3 );
			macRC522_DELAY();
		
			macRC522_SCK_0 ();

//			Delay_us ( 1 );
//			Delay_us ( 3 );
			macRC522_DELAY();
			 
			macRC522_SCK_1();

//			Delay_us ( 3 );
			macRC522_DELAY();
			 
			byte <<= 1; 
			
    } 
	
}


/*
 * 函数名：SPI_RC522_ReadByte
 * 描述  ：从RC522发送1 Byte 数据
 * 输入  ：无
 * 返回  : RC522返回的数据
 * 调用  ：内部调用
 */
u8 SPI_RC522_ReadByte ( void )
{
	u8 counter;
	u8 SPI_Data;


	for(counter=0;counter<8;counter++)
	{
			SPI_Data <<= 1;
	 
			macRC522_SCK_0 ();

//			Delay_us ( 3 );
		macRC522_DELAY();
		
			if ( macRC522_MISO_GET() == 1)
					SPI_Data |= 0x01;

//			Delay_us ( 2 );
//			Delay_us ( 3 );
			macRC522_DELAY();

			macRC522_SCK_1 ();
	
//			Delay_us ( 3 );
			macRC522_DELAY();
			
	}
	
	return SPI_Data;
	
}


/*
 * 函数名：ReadRawRC
 * 描述  ：读RC522寄存器
 * 输入  ：ucAddress，寄存器地址
 * 返回  : 寄存器的当前值
 * 调用  ：内部调用
 */
u8 ReadRawRC ( u8 ucAddress )
{
	u8 ucAddr, ucReturn;
	
	
	ucAddr = ( ( ucAddress << 1 ) & 0x7E ) | 0x80;
	
	macRC522_CS_Enable();
	
	SPI_RC522_SendByte ( ucAddr );
	
	ucReturn = SPI_RC522_ReadByte ();
	
	macRC522_CS_Disable();
	
	
	return ucReturn;
	
	
}


/*
 * 函数名：WriteRawRC
 * 描述  ：写RC522寄存器
 * 输入  ：ucAddress，寄存器地址
 *         ucValue，写入寄存器的值
 * 返回  : 无
 * 调用  ：内部调用
 */
void WriteRawRC ( u8 ucAddress, u8 ucValue )
{  
	u8 ucAddr;
	
	
	ucAddr = ( ucAddress << 1 ) & 0x7E;
	
	macRC522_CS_Enable();
	
	SPI_RC522_SendByte ( ucAddr );
	
	SPI_RC522_SendByte ( ucValue );
	
	macRC522_CS_Disable();	

	
}


/*
 * 函数名：SetBitMask
 * 描述  ：对RC522寄存器置位
 * 输入  ：ucReg，寄存器地址
 *         ucMask，置位值
 * 返回  : 无
 * 调用  ：内部调用
 */
void SetBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;
	
	
    ucTemp = ReadRawRC ( ucReg );
	
    WriteRawRC ( ucReg, ucTemp | ucMask );         // set bit mask
	
	
}


/*
 * 函数名：ClearBitMask
 * 描述  ：对RC522寄存器清位
 * 输入  ：ucReg，寄存器地址
 *         ucMask，清位值
 * 返回  : 无
 * 调用  ：内部调用
 */
void ClearBitMask ( u8 ucReg, u8 ucMask )  
{
    u8 ucTemp;
	
	
    ucTemp = ReadRawRC ( ucReg );
	
    WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) );  // clear bit mask
	
	
}


/*
 * 函数名：PcdAntennaOn
 * 描述  ：开启天线 
 * 输入  ：无
 * 返回  : 无
 * 调用  ：内部调用
 */
void PcdAntennaOn ( void )
{
    u8 uc;
	
	
    uc = ReadRawRC ( TxControlReg );
	
    if ( ! ( uc & 0x03 ) )
			SetBitMask(TxControlReg, 0x03);

		
}


/*
 * 函数名：PcdAntennaOff
 * 描述  ：开启天线 
 * 输入  ：无
 * 返回  : 无
 * 调用  ：内部调用
 */
void PcdAntennaOff ( void )
{
  ClearBitMask ( TxControlReg, 0x03 );
	
	
}


/*
 * 函数名：PcdRese
 * 描述  ：复位RC522 
 * 输入  ：无
 * 返回  : 无
 * 调用  ：外部调用
 */
void PcdReset ( void )
{
	macRC522_Reset_Disable();
	
	macRC522_DELAY();
	
	macRC522_Reset_Enable();
	
	macRC522_DELAY();
	
	macRC522_Reset_Disable();
	
	macRC522_DELAY();
	
	WriteRawRC ( CommandReg, 0x0f );
	
	while ( ReadRawRC ( CommandReg ) & 0x10 );
	
	macRC522_DELAY();
	
  WriteRawRC ( ModeReg, 0x3D );            //定义发送和接收常用模式 和Mifare卡通讯，CRC初始值0x6363
	
  WriteRawRC ( TReloadRegL, 30 );          //16位定时器低位    
	WriteRawRC ( TReloadRegH, 0 );			     //16位定时器高位
	
  WriteRawRC ( TModeReg, 0x8D );				   //定义内部定时器的设置
	
  WriteRawRC ( TPrescalerReg, 0x3E );			 //设置定时器分频系数
	
	WriteRawRC ( TxAutoReg, 0x40 );				   //调制发送信号为100%ASK	
	

}


/*
 * 函数名：M500PcdConfigISOType
 * 描述  ：设置RC522的工作方式
 * 输入  ：ucType，工作方式
 * 返回  : 无
 * 调用  ：外部调用
 */
void M500PcdConfigISOType ( u8 ucType )
{
	if ( ucType == 'A')                     //ISO14443_A
  {
		ClearBitMask ( Status2Reg, 0x08 );
		
    WriteRawRC ( ModeReg, 0x3D );//3F
		
		WriteRawRC ( RxSelReg, 0x86 );//84
		
		WriteRawRC( RFCfgReg, 0x7F );   //4F
		
		WriteRawRC( TReloadRegL, 30 );//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
		
		WriteRawRC ( TReloadRegH, 0 );
		
		WriteRawRC ( TModeReg, 0x8D );
		
		WriteRawRC ( TPrescalerReg, 0x3E );
		
		delay_us ( 2 );
		
		PcdAntennaOn ();//开天线
		
   }

	 
}


/*
 * 函数名：PcdComMF522
 * 描述  ：通过RC522和ISO14443卡通讯
 * 输入  ：ucCommand，RC522命令字
 *         pInData，通过RC522发送到卡片的数据
 *         ucInLenByte，发送数据的字节长度
 *         pOutData，接收到的卡片返回数据
 *         pOutLenBit，返回数据的位长度
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：内部调用
 */
char PcdComMF522 ( u8 ucCommand, u8 * pInData, u8 ucInLenByte, u8 * pOutData, u32 * pOutLenBit )		
{
    char cStatus = MI_ERR;
    u8 ucIrqEn   = 0x00;
    u8 ucWaitFor = 0x00;
    u8 ucLastBits;
    u8 ucN;
    u32 ul;
	
	
    switch ( ucCommand )
    {
       case PCD_AUTHENT:		//Mifare认证
          ucIrqEn   = 0x12;		//允许错误中断请求ErrIEn  允许空闲中断IdleIEn
          ucWaitFor = 0x10;		//认证寻卡等待时候 查询空闲中断标志位
          break;
			 
       case PCD_TRANSCEIVE:		//接收发送 发送接收
          ucIrqEn   = 0x77;		//允许TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
          ucWaitFor = 0x30;		//寻卡等待时候 查询接收中断标志位与 空闲中断标志位
          break;
			 
       default:
         break;
			 
    }
   
    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );		//IRqInv置位管脚IRQ与Status1Reg的IRq位的值相反 
    ClearBitMask ( ComIrqReg, 0x80 );			//Set1该位清零时，CommIRqReg的屏蔽位清零
    WriteRawRC ( CommandReg, PCD_IDLE );		//写空闲命令
    SetBitMask ( FIFOLevelReg, 0x80 );			//置位FlushBuffer清除内部FIFO的读和写指针以及ErrReg的BufferOvfl标志位被清除
    
    for ( ul = 0; ul < ucInLenByte; ul ++ )
		  WriteRawRC ( FIFODataReg, pInData [ ul ] );    		//写数据进FIFOdata
			
    WriteRawRC ( CommandReg, ucCommand );					//写命令
   
    
    if ( ucCommand == PCD_TRANSCEIVE )
			SetBitMask(BitFramingReg,0x80);  				//StartSend置位启动数据发送 该位与收发命令使用时才有效
    
    ul = 1000;//根据时钟频率调整，操作M1卡最大等待时间25ms
		
    do 														//认证 与寻卡等待时间	
    {
         ucN = ReadRawRC ( ComIrqReg );							//查询事件中断
         ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );		//退出条件i=0,定时器中断，与写空闲命令
		
    ClearBitMask ( BitFramingReg, 0x80 );					//清理允许StartSend位
		
    if ( ul != 0 )
    {
			if ( ! ( ReadRawRC ( ErrorReg ) & 0x1B ) )			//读错误标志寄存器BufferOfI CollErr ParityErr ProtocolErr
			{
				cStatus = MI_OK;
				
				if ( ucN & ucIrqEn & 0x01 )					//是否发生定时器中断
				  cStatus = MI_NOTAGERR;   
					
				if ( ucCommand == PCD_TRANSCEIVE )
				{
					ucN = ReadRawRC ( FIFOLevelReg );			//读FIFO中保存的字节数
					
					ucLastBits = ReadRawRC ( ControlReg ) & 0x07;	//最后接收到得字节的有效位数
					
					if ( ucLastBits )
						* pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;   	//N个字节数减去1（最后一个字节）+最后一位的位数 读取到的数据总位数
					else
						* pOutLenBit = ucN * 8;   					//最后接收到的字节整个字节有效
					
					if ( ucN == 0 )		
            ucN = 1;    
					
					if ( ucN > MAXRLEN )
						ucN = MAXRLEN;   
					
					for ( ul = 0; ul < ucN; ul ++ )
					  pOutData [ ul ] = ReadRawRC ( FIFODataReg );   
					
					}
					
      }
			
			else
				cStatus = MI_ERR;   
			
    }
   
   SetBitMask ( ControlReg, 0x80 );           // stop timer now
   WriteRawRC ( CommandReg, PCD_IDLE ); 
		 
		
   return cStatus;
		
		
}


/*
 * 函数名：PcdRequest
 * 描述  ：寻卡
 * 输入  ：ucReq_code，寻卡方式
 *                     = 0x52，寻感应区内所有符合14443A标准的卡
 *                     = 0x26，寻未进入休眠状态的卡
 *         pTagType，卡片类型代码
 *                   = 0x4400，Mifare_UltraLight
 *                   = 0x0400，Mifare_One(S50)
 *                   = 0x0200，Mifare_One(S70)
 *                   = 0x0800，Mifare_Pro(X))
 *                   = 0x4403，Mifare_DESFire
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
char PcdRequest ( u8 ucReq_code, u8 * pTagType )
{
   char cStatus;  
	 u8 ucComMF522Buf [ MAXRLEN ]; 
   u32 ulLen;
	

   ClearBitMask ( Status2Reg, 0x08 );	//清理指示MIFARECyptol单元接通以及所有卡的数据通信被加密的情况
   WriteRawRC ( BitFramingReg, 0x07 );	//	发送的最后一个字节的 七位
   SetBitMask ( TxControlReg, 0x03 );	//TX1,TX2管脚的输出信号传递经发送调制的13.56的能量载波信号

   ucComMF522Buf [ 0 ] = ucReq_code;		//存入 卡片命令字

   cStatus = PcdComMF522 ( PCD_TRANSCEIVE,	ucComMF522Buf, 1, ucComMF522Buf, & ulLen );	//寻卡  
  
   if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )	//寻卡成功返回卡类型 
   {    
       * pTagType = ucComMF522Buf [ 0 ];
       * ( pTagType + 1 ) = ucComMF522Buf [ 1 ];
   }
	 
   else
     cStatus = MI_ERR;

   
   return cStatus;
	 
	 
}


/*
 * 函数名：PcdAnticoll
 * 描述  ：防冲撞
 * 输入  ：pSnr，卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
char PcdAnticoll ( u8 * pSnr )
{
    char cStatus;
    u8 uc, ucSnr_check = 0;
    u8 ucComMF522Buf [ MAXRLEN ]; 
	  u32 ulLen;
    

    ClearBitMask ( Status2Reg, 0x08 );		//清MFCryptol On位 只有成功执行MFAuthent命令后，该位才能置位
    WriteRawRC ( BitFramingReg, 0x00);		//清理寄存器 停止收发
    ClearBitMask ( CollReg, 0x80 );			//清ValuesAfterColl所有接收的位在冲突后被清除
   
    ucComMF522Buf [ 0 ] = 0x93;	//卡片防冲突命令
    ucComMF522Buf [ 1 ] = 0x20;
   
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//与卡片通信
	
    if ( cStatus == MI_OK)		//通信成功
    {
			for ( uc = 0; uc < 4; uc ++ )
			{
         * ( pSnr + uc )  = ucComMF522Buf [ uc ];			//读出UID
         ucSnr_check ^= ucComMF522Buf [ uc ];
      }
			
      if ( ucSnr_check != ucComMF522Buf [ uc ] )
				cStatus = MI_ERR;    
				 
    }
    
    SetBitMask ( CollReg, 0x80 );
		
		
    return cStatus;
		
		
}


/*
 * 函数名：CalulateCRC
 * 描述  ：用RC522计算CRC16
 * 输入  ：pIndata，计算CRC16的数组
 *         ucLen，计算CRC16的数组字节长度
 *         pOutData，存放计算结果存放的首地址
 * 返回  : 无
 * 调用  ：内部调用
 */
void CalulateCRC ( u8 * pIndata, u8 ucLen, u8 * pOutData )
{
    u8 uc, ucN;
	
	
    ClearBitMask(DivIrqReg,0x04);
	
    WriteRawRC(CommandReg,PCD_IDLE);
	
    SetBitMask(FIFOLevelReg,0x80);
	
    for ( uc = 0; uc < ucLen; uc ++)
	    WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );   

    WriteRawRC ( CommandReg, PCD_CALCCRC );
	
    uc = 0xFF;
	
    do 
    {
        ucN = ReadRawRC ( DivIrqReg );
        uc --;
    } while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );
		
    pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );
    pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );
		
		
}


/*
 * 函数名：PcdSelect
 * 描述  ：选定卡片
 * 输入  ：pSnr，卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
char PcdSelect ( u8 * pSnr )
{
    char ucN;
    u8 uc;
	  u8 ucComMF522Buf [ MAXRLEN ]; 
    u32  ulLen;
    
    
    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;
	
    for ( uc = 0; uc < 4; uc ++ )
    {
    	ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
    	ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }
		
    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );
  
    ClearBitMask ( Status2Reg, 0x08 );

    ucN = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );
    
    if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
      ucN = MI_OK;  
    else
      ucN = MI_ERR;    

		
    return ucN;
		
		
}


/*
 * 函数名：PcdAuthState
 * 描述  ：验证卡片密码
 * 输入  ：ucAuth_mode，密码验证模式
 *                     = 0x60，验证A密钥
 *                     = 0x61，验证B密钥
 *         u8 ucAddr，块地址
 *         pKey，密码
 *         pSnr，卡片序列号，4字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
char PcdAuthState ( u8 ucAuth_mode, u8 ucAddr, u8 * pKey, u8 * pSnr )
{
    char cStatus;
	  u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;
    
	
    ucComMF522Buf [ 0 ] = ucAuth_mode;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    for ( uc = 0; uc < 6; uc ++ )
	    ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );   
	
    for ( uc = 0; uc < 6; uc ++ )
	    ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );   

    cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );
	
    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
      cStatus = MI_ERR;   
    
		
    return cStatus;
		
		
}


/*
 * 函数名：PcdWrite
 * 描述  ：写数据到M1卡一块
 * 输入  ：u8 ucAddr，块地址
 *         pData，写入的数据，16字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
char PcdWrite ( u8 ucAddr, u8 * pData )
{
    char cStatus;
	  u8 uc, ucComMF522Buf [ MAXRLEN ];
    u32 ulLen;
     
    
    ucComMF522Buf [ 0 ] = PICC_WRITE;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
 
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

    if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
      cStatus = MI_ERR;   
        
    if ( cStatus == MI_OK )
    {
			//memcpy(ucComMF522Buf, pData, 16);
      for ( uc = 0; uc < 16; uc ++ )
			  ucComMF522Buf [ uc ] = * ( pData + uc );  
			
      CalulateCRC ( ucComMF522Buf, 16, & ucComMF522Buf [ 16 ] );

      cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, & ulLen );
			
			if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
        cStatus = MI_ERR;   
			
    } 
		
		
    return cStatus;
		
		
}


/*
 * 函数名：PcdRead
 * 描述  ：读取M1卡一块数据
 * 输入  ：u8 ucAddr，块地址
 *         pData，读出的数据，16字节
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
char PcdRead ( u8 ucAddr, u8 * pData )
{
    char cStatus;
	  u8 uc, ucComMF522Buf [ MAXRLEN ]; 
    u32 ulLen;
    

    ucComMF522Buf [ 0 ] = PICC_READ;
    ucComMF522Buf [ 1 ] = ucAddr;
	
    CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
   
    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );
	
    if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
    {
			for ( uc = 0; uc < 16; uc ++ )
        * ( pData + uc ) = ucComMF522Buf [ uc ];   
    }
		
    else
      cStatus = MI_ERR;   
    
		
    return cStatus;
		
		
}


/*
 * 函数名：PcdHalt
 * 描述  ：命令卡片进入休眠状态
 * 输入  ：无
 * 返回  : 状态值
 *         = MI_OK，成功
 * 调用  ：外部调用
 */
char PcdHalt( void )
{
	u8 ucComMF522Buf [ MAXRLEN ]; 
	u32  ulLen;
  

  ucComMF522Buf [ 0 ] = PICC_HALT;
  ucComMF522Buf [ 1 ] = 0;
	
  CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
 	PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );

  return MI_OK;
	
}


char IC_CMT ( u8 * PID ,u8 * KEY, u8 RW, u8 * Dat )
{
	u8 receivezt=0;
  
	
  receivezt=PcdRequest ( 0x52, PID );//寻卡
   if(receivezt!=MI_OK) return receivezt;
  receivezt=PcdAnticoll ( PID );//防冲撞
   if(receivezt!=MI_OK) return receivezt;
  receivezt=PcdSelect ( PID );//选定卡
   if(receivezt!=MI_OK) return receivezt;
  receivezt=PcdAuthState ( 0x60, 0x00, KEY, PID );//校验
	  if(receivezt!=MI_OK) return receivezt;

	if ( RW )//读写选择，1是读，0是写
    receivezt= PcdRead ( 0x00, Dat );
   
   else 
     receivezt=PcdWrite ( 0x00, Dat );
  if(receivezt!=MI_OK) return receivezt;
	 
  PcdHalt();
	return 0;
}



u8 GET_PID( u8 *PID)
{
		u8 receivezt=0;
		receivezt=PcdRequest ( 0x52, PID );//寻卡
		 if(receivezt!=MI_OK) return 0;
		receivezt=PcdAnticoll ( PID );//防冲撞
		 if(receivezt!=MI_OK) return 0;
		receivezt=PcdSelect ( PID );//选定卡
		 if(receivezt!=MI_OK) return 0;
	   return MI_OK;
}

u8 RC522_SCAN(u8* BUF)
{
	
	 u8 ucArray_ID [ 4 ] ;//存放IC卡号
	 if(GET_PID(ucArray_ID) == MI_OK)//获取RC522卡号
	 {
		sprintf((char*)BUF,"%02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );//吧IC卡号以字符串的形式拷贝到BUF中
		BUF[4]=0;
		return 1;
	 }
	
	return 0; 

}

#endif

#if CONFIG_AS608 == ENABLED
uint8_t Rxflag=0; 
uint8_t ucTemp;
int summaf,summas;
unsigned char   querenma=11;
unsigned char   sum[2];
unsigned int    PageID;
unsigned int    dz[4];
void usart2_init_Demo(u32 band)
{
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//  
	
	//重新定义管脚
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	//USART2_TX    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // 引脚不能更改
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 
   
  //USART2_RX	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化   

  //Usart NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3 原3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3     原2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = band;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2
}
 /*发送一个字节数据*/
 void USART2SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART2,SendData);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
} 

/*
根据长度向串口2 发送数据
*/
void usart2_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2, data[i]); //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		//i++;
	}
	//i++;
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void usart2_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART2, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
/*
串口2中断函数
*/
void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{	
			Rxflag=1;
			ucTemp = USART_ReceiveData(USART2);
	}		

}

void SFG_GetEcho(void)			      //握手
{
	  uint8_t  order[11]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x53,0x00};	
    usart2_SendStringByLen_Demo(order,11 );
		
		summaf=0x57;
		USART2SendByte_Demo(summaf);
		
		while(!Rxflag){}
		   Rxflag=0;
		  querenma=ucTemp;
		
		while(!Rxflag){}
		   Rxflag=0;		
		  sum[1]=ucTemp;
		
	  while(!Rxflag){}
		   Rxflag=0;		
		  sum[0]=ucTemp;
		
		summas=(sum[1]<<8)+sum[0];
}


void SFG_getimage(void)			      //录入指纹图像
{
	 u8 i;
	 uint8_t  order[11]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x01,0x00};
	 Rxflag=0;
	 usart2_SendStringByLen_Demo(order,11 );
	 
	 summaf=0x05;
	 USART2SendByte_Demo(summaf);
	 

	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag){}
		 Rxflag=0;

		
	 }

	 
	 while(!Rxflag){}
	   Rxflag=0;

		 querenma=ucTemp;
	 
	 while(!Rxflag){}
	    Rxflag=0;		
		  sum[1]=ucTemp;
	  while(!Rxflag){}
		   Rxflag=0;
		  sum[0]=ucTemp;
		summas=(sum[1]<<8)+sum[0];	 
}

void SFG_genchar(uint8_t bufferID) //生成特征并存于charbuffer1/2  调用后单片机波特率变化@@@
{
	u8 i;
	uint8_t  order[10]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02};	
	usart2_SendStringByLen_Demo( order,10 );
		
	USART2SendByte_Demo( bufferID);
	
	summaf=0x07+bufferID;
  sum[0]=summaf;
  sum[1]=summaf>>8;
	
	USART2SendByte_Demo(sum[1]);
	USART2SendByte_Demo(sum[0]);
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag){}
		 Rxflag=0;
		
	 }			
	while(!Rxflag){}
			 Rxflag=0;
		  querenma=ucTemp;
	 while(!Rxflag){}
		  Rxflag=0;
		  sum[1]=ucTemp;
		
	  while(!Rxflag){}
		  Rxflag=0;
		  sum[0]=ucTemp;
		
	summas=(sum[1]<<8)+sum[0];	 
}

void SFG_fastsearch(uint8_t bufferID)  //搜索指纹返回指纹ID号   sum、pagenum>255都会使程序卡@@@
{   
	uint8_t i,ID1,ID2;
	uint8_t order[10]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x08,0x1b};
	uint8_t order1[4]={0x00,0x00,0x00,180};
	usart2_SendStringByLen_Demo(order,10 );
	
	USART2SendByte_Demo(bufferID);
	
	usart2_SendStringByLen_Demo(order1,4 );
	
	 summaf=9+0x1b+bufferID+180;
   sum[0]=summaf;
   sum[1]=summaf>>8;
	 
	 USART2SendByte_Demo( sum[1]);
	 USART2SendByte_Demo( sum[0]);
	
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag){}
		 Rxflag=0;
	 }
	 
	 while(!Rxflag){}
	 Rxflag=0;
	 querenma=ucTemp;

	  while(!Rxflag){}
	    Rxflag=0;
	  ID1 = ucTemp;

		while(!Rxflag){}
	    Rxflag=0;
	  ID2 = ucTemp;

		while(!Rxflag){}
	    Rxflag=0;

	  while(!Rxflag){}
	    Rxflag=0;

		sum[1]=ucTemp;
	 
	  while(!Rxflag){}
		 Rxflag=0;
		sum[0]=ucTemp;

		summas=(sum[1]<<8)+sum[0];
		
		PageID=(ID1<<8)+ID2;
}

void SFG_enroll(void)				 //自动注册模板返回存储ID  =录图像+合并生成模板+储存模板
{
   uint8_t i,ID1,ID2;
   uint8_t  order[11]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x10,0x00};
   Rxflag=0;	 
	 usart2_SendStringByLen_Demo(order,11 );
	 
	 summaf=0x14;
	 USART2SendByte_Demo( summaf);
	 
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag){}
		 Rxflag=0;

	 }
	 
	 while(!Rxflag){}
	 Rxflag=0;

	 querenma=ucTemp;
		 
	
	 while(!Rxflag){}
	   Rxflag=0;

	  ID1 = ucTemp;
		
		while(!Rxflag){}
	    Rxflag=0;

	  ID2 = ucTemp;
	 
	  while(!Rxflag){}
		Rxflag=0;

		sum[1]=ucTemp;
	  while(!Rxflag){}
		Rxflag=0;

		sum[0]=ucTemp;
	 
	   PageID=(ID1<<8)+ID2;
}

void SFG_deletchar(uint16_t pageID,u16 N)   //删除指纹		     校验和在2字节的页码处应分高低字节相加
{
   uint8_t i,ID1,ID2;
	 uint8_t  order[10]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x07,0x0c};
   Rxflag=0;	 
	 usart2_SendStringByLen_Demo(order,10 );
	 
	 ID1=pageID;
	 ID2=pageID>>8;
	 
	 USART2SendByte_Demo( ID2);
	 USART2SendByte_Demo( ID1);
	 USART2SendByte_Demo(N>>8);
	 USART2SendByte_Demo(N);
	 
	 summaf=0x01+0x07+0x0C+ID1+ID2+N+(N>>8);
   sum[0]=summaf;
   sum[1]=summaf>>8;
	 
	 USART2SendByte_Demo(sum[1]);
	 USART2SendByte_Demo(sum[0]);
	 
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag){}
		 Rxflag=0;

//		 ucTemp=0;
	 }
	 while(!Rxflag){}	
   Rxflag=0;	
 
	   querenma=ucTemp;
	 
	 while(!Rxflag){}	
   Rxflag=0;

	 sum[1]=ucTemp;
	 
	 while(!Rxflag){}
	 Rxflag=0;
		 
	 sum[0]=ucTemp;
	 
	 summas=(sum[1]<<8)+sum[0];
}

void SFG_identify(void)				//自动验证指纹     录图像+生成特征+搜索
{
   uint8_t i,ID1,ID2;
	 uint8_t  order[11]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x11,0x00};
   Rxflag=0;	 
	 usart2_SendStringByLen_Demo( order,11 );
	 
	 summaf=0x15;
	 
	 USART2SendByte_Demo( summaf);
	 
	 for(i=0;i<9;i++)	
   {	
		while(!Rxflag)
			ucTemp = 0XFF;
		 Rxflag=0;
	 		
		 
	 }
	 
	 while(!Rxflag){}
    Rxflag=0;		 
	 querenma=ucTemp;
 

	 while(!Rxflag){}
    Rxflag=0;		 
 
	 ID2 = ucTemp;
	 while(!Rxflag){}
    Rxflag=0;		 		 
	 ID1 = ucTemp;	
		
		PageID=(ID2<<8)+ID1;
		
}

void as608_init()
{
	GPIO_InitTypeDef   GPIO_InitStructure;
   
	usart2_init_Demo(9600);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15	
	USART2SendByte_Demo(0xff);
}


#endif

#if CONFIG_GY906 == ENABLED


void GY906_I2C_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	
	
	RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin=I2C_SCL|I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}

void I2C_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

//产生起始信号
void I2C_Start(void)
{
    I2C_SDA_OUT();
	
	I2C_SDA_H;
	I2C_SCL_H;
	delay_us(5);
	I2C_SDA_L;
	delay_us(6);
	I2C_SCL_L;
}

//产生停止信号
void I2C_Stop(void)
{
   I2C_SDA_OUT();

   I2C_SCL_L;
   I2C_SDA_L;
   I2C_SCL_H;
   delay_us(6);
   I2C_SDA_H;
   delay_us(6);
}

//主机产生应答信号ACK
void I2C_Ack(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_L;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}

//主机不产生应答信号NACK
void I2C_NAck(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_H;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}
//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
u8 I2C_Wait_Ack(void)
{
	u8 tempTime=0;

	I2C_SDA_IN();

	I2C_SDA_H;
	delay_us(1);
	I2C_SCL_H;
	delay_us(1);

	while(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C_Stop();
			return 1;
		}	 
	}

	I2C_SCL_L;
	return 0;
}
//I2C 发送一个字节
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_us(2); //发送数据
		I2C_SCL_L;
		delay_us(2);
	}
}

//I2C 读取一个字节

u8 I2C_Read_Byte(u8 ack)
{
   u8 i=0,receive=0;

   I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C_SCL_L;
		delay_us(2);
		I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
		   receive++;
		delay_us(1);	
   }

   	if(ack==0)
	   	I2C_NAck();
	else
		I2C_Ack();

	return receive;
}

short gy906_Readtemp()
{

	unsigned char DataH,DataL,Pecreg;
	I2C_Start();
	I2C_Send_Byte(0x00);
	I2C_Wait_Ack();
	I2C_Send_Byte(0x07);
	I2C_Wait_Ack();
	
	I2C_Start();
	I2C_Send_Byte(0x01);
	I2C_Wait_Ack();
	
	
	DataL=I2C_Read_Byte(1);
	DataH=I2C_Read_Byte(1);
	Pecreg=I2C_Read_Byte(1);	
	I2C_Stop();
	Pecreg=Pecreg;//不报警告
	return (DataH*256+DataL);
}
#endif


#if CONFIG_RELAY == ENABLED

void relay_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	//做输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15		
	//做输出
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;				 //LED端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC	

}
#endif

#if CONFIG_KEYMAP == ENABLED

typedef struct 
 {
	GPIO_TypeDef* GPIOX;
	uint16_t GPIO_Pin;
 }KGPT[2][4]; //4*4
KGPT KPIN={ //只需要在下面填写横竖行的IO口和管脚   IO口和管脚都可以随意定义 无需在一个IO口 管脚也无需按顺序
						{{GPIOA,GPIO_Pin_0} ,{GPIOA,GPIO_Pin_1}, {GPIOA,GPIO_Pin_2},{GPIOA,GPIO_Pin_3}},//row 横行
						{{GPIOA,GPIO_Pin_4},{GPIOA,GPIO_Pin_5}, {GPIOA,GPIO_Pin_6},{GPIOA,GPIO_Pin_7}}  //col 竖行
					};
#define row 0
#define col 1					
#define RCC_APB2_GPIOX  RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA//IO时钟					
#define MAX_Time   36000000 // 松手检测最大延时   
//按键初始化函数 
					
					
void KEY_Init(void)
{
  u8 i;
	GPIO_InitTypeDef   GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2_GPIOX,ENABLE);//使能PORTC时钟
  for(i=0;i<4;i++)
	
	{
	 GPIO_InitStructure.GPIO_Pin = KPIN[row][i].GPIO_Pin;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(KPIN[row][i].GPIOX, &GPIO_InitStructure);//初始化row
	 GPIO_ResetBits(KPIN[row][i].GPIOX,KPIN[row][i].GPIO_Pin);
	}
 for(i=0;i<4;i++)
	{
		 GPIO_InitStructure.GPIO_Pin  = KPIN[col][i].GPIO_Pin;//PC5
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
		 GPIO_Init(KPIN[col][i].GPIOX, &GPIO_InitStructure);//初始化col
	}
} 

static u8 ReScan(GPIO_TypeDef* GPIOX,uint16_t colPin,u8 colIndex)
{
 u8 i;
 delay_ms(10);//消抖延时
 for(i = 0;i<4;i++)
 {
  GPIO_SetBits(KPIN[row][i].GPIOX,KPIN[row][i].GPIO_Pin);//每个行置1
  if((GPIO_ReadInputDataBit(GPIOX, colPin) == 1)) //如果列也变了 行的值就知道了 为 i
		{
			GPIO_ResetBits(KPIN[row][i].GPIOX,KPIN[row][i].GPIO_Pin); //行恢复 置0 
		  return colIndex+i*4+1;//返回的数据 为1-16 对应4x4键盘的16个键
		}
	GPIO_ResetBits(KPIN[row][i].GPIOX,KPIN[row][i].GPIO_Pin);     //行恢复 置0
 }
 return 0;
}


u8 KEY_Scan(void)
{	 
 u8 i,keyvalue;
	for(i = 0;i<4;i++)
	{
	 if(GPIO_ReadInputDataBit(KPIN[col][i].GPIOX,KPIN[col][i].GPIO_Pin) == 0)//检测列 列值为 i
	 {		   
			keyvalue = ReScan(KPIN[col][i].GPIOX,KPIN[col][i].GPIO_Pin,i);//检测行 取键值
		  while(GPIO_ReadInputDataBit(KPIN[col][i].GPIOX,KPIN[col][i].GPIO_Pin) == 0);
			return keyvalue;//返回键值
		}
	 delay_ms(1);
	}
return 0;
}

u8 KEY_tranform(u8 keyvalue)
{
	u8 value=0xff;
	switch(keyvalue)
	{
		case 0:
			value=0xff;
		break;
		case 1:
			value=1;
		break;
		case 2:
			value=2;
		break;
		case 3:
			value=3;
		break;
		case 4:
			value='A';
		break;
		case 5:
			value=4;
		break;
		case 6:
			value=5;
		break;
		case 7:
			value=6;
		break;
		case 8:
			value='B';
		break;
		case 9:
			value=7;
		break;		
		case 10:
			value=8;
		break;
		case 11:
			value=9;
		break;
		case 12:
			value='C';
		break;
		case 13:
			value='*';
		break;	
		case 14:
			value=0;
		break;
		case 15:
			value='#';
		break;
		case 16:
			value='D';
		break;			
	}
	return value;
}
				

#endif

#if CONFIG_MAX30102 == ENABLED
#include "myiic.h"
#include "max30102.h"
#include "algorithm.h"
#define MAX_BRIGHTNESS 255
uint8_t uch_dummy; 
uint32_t aun_ir_buffer[151]; //infrared LED sensor data
uint32_t aun_red_buffer[151];  //red LED sensor data
int32_t n_ir_buffer_length; //data length
int32_t n_spo2;  //SPO2 value
int8_t ch_spo2_valid;  //indicator to show if the SPO2 calculation is valid
int32_t n_heart_rate; //heart rate value
int8_t  ch_hr_valid;  //indicator to show if the heart rate calculation is valid
//int32_t COUNT = 0;
int32_t hrAvg_l=120;//心率
int32_t spo2Avg_l=70;//血氧浓度
int32_t hr_buf[50];
int32_t hrSum;
int32_t hrAvg;//心率
int32_t spo2_buf[50];
int32_t spo2Sum;
int32_t spo2Avg;//血氧浓度
int32_t spo2BuffFilled;
int32_t hrBuffFilled;
int32_t hrValidCnt = 0;
int32_t spo2ValidCnt = 0;
int32_t hrThrowOutSamp = 0;
int32_t spo2ThrowOutSamp = 0;
int32_t spo2Timeout = 0;
int32_t hrTimeout = 0;
uint32_t un_min, un_max, un_prev_data, un_brightness;  //variables to calculate the on-board LED brightness that reflects the heartbeats
int32_t i;
float f_temp;	

void max30102_init()
{
    bsp_InitI2C();//IIC初始化
    maxim_max30102_reset(); //resets the MAX30102
    maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy); //Reads/clears the interrupt status register
    maxim_max30102_init();  //initialize the MAX30102	
		
		un_brightness = 0;
    un_min = 0x3FFFF;
    un_max = 0;

    n_ir_buffer_length = 150; //buffer length of 150 stores 3 seconds of samples running at 50sps		

    //read the first 150 samples, and determine the signal range
    for(i = 0; i < n_ir_buffer_length; i++)
    {
        //while(KEY0 == 1); //wait until the interrupt pin asserts
        maxim_max30102_read_fifo((aun_red_buffer + i), (aun_ir_buffer + i)); //read from MAX30102 FIFO

        if(un_min > aun_red_buffer[i])
            un_min = aun_red_buffer[i]; //update signal min
        if(un_max < aun_red_buffer[i])
            un_max = aun_red_buffer[i]; //update signal max
    }
    un_prev_data = aun_red_buffer[i];
    //calculate heart rate and SpO2 after first 150 samples (first 3 seconds of samples)
    maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);	
}
void process_max30102()
{
		i = 0;
		un_min = 0x3FFFF;
		un_max = 0;


		//dumping the first 50 sets of samples in the memory and shift the last 100 sets of samples to the top
		for(i = 50; i < 150; i++)
		{
			aun_red_buffer[i - 50] = aun_red_buffer[i];
			aun_ir_buffer[i - 50] = aun_ir_buffer[i];

			//update the signal min and max
			if(un_min > aun_red_buffer[i])
					un_min = aun_red_buffer[i];
			if(un_max < aun_red_buffer[i])
					un_max = aun_red_buffer[i];
		}

		//take 50 sets of samples before calculating the heart rate.
		for(i = 100; i < 150; i++)
		{
			un_prev_data = aun_red_buffer[i - 1];
			//while(KEY0 == 1);
			maxim_max30102_read_fifo((aun_red_buffer + i), (aun_ir_buffer + i));

			//calculate the brightness of the LED
			if(aun_red_buffer[i] > un_prev_data)
			{
					f_temp = aun_red_buffer[i] - un_prev_data;
					f_temp /= (un_max - un_min);
					f_temp *= MAX_BRIGHTNESS;
					f_temp = un_brightness - f_temp;
					if(f_temp < 0)
							un_brightness = 0;
					else
							un_brightness = (int)f_temp;
			}
			else
			{
					f_temp = un_prev_data - aun_red_buffer[i];
					f_temp /= (un_max - un_min);
					f_temp *= MAX_BRIGHTNESS;
					un_brightness += (int)f_temp;
					if(un_brightness > MAX_BRIGHTNESS)
							un_brightness = MAX_BRIGHTNESS;
			}
		}
		maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);	
		if ((ch_hr_valid == 1) && (n_heart_rate < 150) && (n_heart_rate > 60))
		{
				hrTimeout = 0;

				// Throw out up to 1 out of every 5 valid samples if wacky
				if (hrValidCnt == 4)
				{
						hrThrowOutSamp = 1;
						hrValidCnt = 0;
						for (i = 12; i < 16; i++)
						{
								if (n_heart_rate < hr_buf[i] + 10)
								{
										hrThrowOutSamp = 0;
										hrValidCnt   = 4;
								}
						}
				}
				else
				{
						hrValidCnt = hrValidCnt + 1;
				}

				if (hrThrowOutSamp == 0)
				{

						// Shift New Sample into buffer
						for(i = 0; i < 15; i++)
						{
								hr_buf[i] = hr_buf[i + 1];
						}
						hr_buf[15] = n_heart_rate;

						// Update buffer fill value
						if (hrBuffFilled < 16)
						{
								hrBuffFilled = hrBuffFilled + 1;
						}

						// Take moving average
						hrSum = 0;
						if (hrBuffFilled < 2)
						{
								hrAvg = 0;
						}
						else if (hrBuffFilled < 4)
						{
								for(i = 14; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 1;
						}
						else if (hrBuffFilled < 8)
						{
								for(i = 12; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 2;
						}
						else if (hrBuffFilled < 16)
						{
								for(i = 8; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 3;
						}
						else
						{
								for(i = 0; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 4;
						}
				}
				hrThrowOutSamp = 0;
		}
		else
		{
				hrValidCnt = 0;
				if (hrTimeout == 4)
				{
						hrAvg = 0;
						hrBuffFilled = 0;
				}
				else
				{
						hrTimeout++;
				}
		}

		if ((ch_spo2_valid == 1) && (n_spo2 > 70))
		{
				spo2Timeout = 0;

				// Throw out up to 1 out of every 5 valid samples if wacky
				if (spo2ValidCnt == 4)
				{
						spo2ThrowOutSamp = 1;
						spo2ValidCnt = 0;
						for (i = 12; i < 16; i++)
						{
								if (n_spo2 > spo2_buf[i] - 10)
								{
										spo2ThrowOutSamp = 0;
										spo2ValidCnt   = 4;
								}
						}
				}
				else
				{
						spo2ValidCnt = spo2ValidCnt + 1;
				}

				if (spo2ThrowOutSamp == 0)
				{

						// Shift New Sample into buffer
						for(i = 0; i < 15; i++)
						{
								spo2_buf[i] = spo2_buf[i + 1];
						}
						spo2_buf[15] = n_spo2;

						// Update buffer fill value
						if (spo2BuffFilled < 16)
						{
								spo2BuffFilled = spo2BuffFilled + 1;
						}

						// Take moving average
						spo2Sum = 0;
						if (spo2BuffFilled < 2)
						{
								spo2Avg = 0;
						}
						else if (spo2BuffFilled < 4)
						{
								for(i = 14; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 1;
						}
						else if (spo2BuffFilled < 8)
						{
								for(i = 12; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 2;
						}
						else if (spo2BuffFilled < 16)
						{
								for(i = 8; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 3;
						}
						else
						{
								for(i = 0; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 4;
						}
				}
				spo2ThrowOutSamp = 0;
		}
		else
		{
				spo2ValidCnt = 0;
				if (spo2Timeout == 4)
				{
						spo2Avg = 0;
						spo2BuffFilled = 0;
				}
				else
				{
						spo2Timeout++;
				}
		}
								
}
#endif

#if CONFIG_DHT22 == ENABLED

 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//DHT11数字温湿度传感器驱动代码	   
//修改日期:2012/9/12
//版本：V1.0
//版权所有，盗版必究。
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
      
//复位DHT11
void DHT22_Rst_Demo(void)	   
{                 
	  DHT22_IO_OUT(); 	//SET OUTPUT
    DHT22_DQ_OUT=0; 	//拉低DQ
    delay_ms(20);    	//拉低至少18ms
    DHT22_DQ_OUT=1; 	//DQ=1 
	  delay_us(30);     	//主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT22_Check_Demo(void) 	   
{   
	u8 retry=0;
	DHT22_IO_IN();//SET INPUT	 
    while (DHT22_DQ_IN&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT22_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT22_Read_Bit_Demo(void) 			 
{
 	u8 retry=0;
	DHT22_IO_IN();//SET INPUT	 DHT22_IO_IN();//SET INPUT	 
	while(DHT22_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT22_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT22_DQ_IN)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT22_Read_Byte_Demo(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT22_Read_Bit_Demo();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT22_Read_Data_Demo(u8 *temp,u8 *humi)    
{
	//u32 humi_tem,temp_tem;
 	u8 buf[5];
	u8 i;
	DHT22_Rst_Demo();
	if(DHT22_Check_Demo()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT22_Read_Byte_Demo();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			
			*humi=(buf[0]*256+buf[1])/10;
			*temp=(buf[2]*256+buf[3])/10;

		}
	}
	else 
		return 1;
	return 0;	    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT22_Init_Demo(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOC,GPIO_Pin_14);						 //PC13 输出高
			    
	DHT22_Rst_Demo();  //复位DHT11
	return DHT22_Check_Demo();//等待DHT11的回应
} 

#endif

#if CONFIG_IR_REC == ENABLED
#include <stm32f10x_exti.h>
unsigned char ir_num;	
u32 hw_jsm;//
u8 hw_jsbz;//
unsigned char Im[4]={0x00,0x00,0x00,0x00};	 //IRCOM[0]~IRCOM[3]：地址码、地址反码、按键码、按键反码(都是十六进制)
void Hwjs_Init(void)//
{
	GPIO_InitTypeDef GPIO_InitStructure; //
	EXTI_InitTypeDef  EXTI_InitStructure;//
	NVIC_InitTypeDef NVIC_InitStructure;//
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);//
	
	//GPIO???
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//
	GPIO_Init(GPIOA,&GPIO_InitStructure); //
	
	EXTI_ClearITPendingBit(EXTI_Line8);//
	
	//
	EXTI_InitStructure.EXTI_Line=EXTI_Line8;//
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI9_5
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
	NVIC_Init(&NVIC_InitStructure);	//
	
}
void nvic_on_off(u8 status)
{
	NVIC_InitTypeDef NVIC_InitStructure;//
	if(status)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI9_5
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//
		NVIC_Init(&NVIC_InitStructure);	//
	}else
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI9_5
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;		//
		NVIC_Init(&NVIC_InitStructure);	//
	}
}

u8 HW_jssj(void)
{
	u8 t=0;//
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1)//
	{
		t++;
		delay_us(20);
		if(t>250)//
		{
			return t;
		}
	}
	return t;
}


void EXTI9_5_IRQHandler(void)
{
	
	//u8* temp;
	u8 Tim=0;//
	u8 ok=0;//
	u8 DATA=0;//
	u8 Num=0;//
//	nvic_on_off(0);
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1)//
		{
			Tim=HW_jssj();//
			if(Tim>=250)break;//
			if(Tim>=200&&Tim<250)//
			{
				ok=1;
			}
			else if(Tim>=60&&Tim<90)//
			{
				DATA=1;
			}else if(Tim>=10&&Tim<50)//
			{
				DATA=0;
			}
			
			if(ok==1)//
			{
				//
				hw_jsm<<=1;
				hw_jsm+=DATA;
				if(Num>=32)//
				{
					hw_jsbz=1;//
					//temp=(u8*)&hw_jsm;
					Im[2]=hw_jsm>>8;

//  					
					switch(Im[2])
					{
						case (0XA2): ir_num=1;break;
						case (0X62): ir_num=2;break;
						case (0XE2): ir_num=3;break;
						case (0xE1): ir_num=4;break;	 
						case (0x81): ir_num=5;break;		
						case (0x43): ir_num=6;break;
						case (0x07): ir_num=7;break;					
					}
					Im[2]=0;				
					break;
				}
			}
			Num++;//
		}
	}
//	nvic_on_off(1);
	EXTI_ClearITPendingBit(EXTI_Line8);//
}



#endif

#if CONFIG_LCD12864_LIB == ENABLED
void Delay_10ms(void)
{
	  delay_ms(10);
}

static void LCD_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4	| GPIO_Pin_5	;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);	 // turn off all led
}


void LCD_Init(void)
{
		// the initial delay time i make it all the same
		//初始化命令之间的延时所有定义为最长延时，20ms 手册上说是10 ms
		//这个延时可能会有点怪，我是为了后面还有作用，测试他的极限延时		
	  LCD_GPIO_Init();
		LCD_SendCom(0x34)	;
		Delay_10ms();
		LCD_SendCom(0x30)	;
		Delay_10ms();
		LCD_SendCom(0x0c)	;
		Delay_10ms();
		LCD_SendCom(0x01)	;
		Delay_10ms();
		LCD_SendCom(0x06)	;
		Delay_10ms();
	
}
//发送地址坐标
void LCD_Set_Position(u8 x, u8 y)
{
	u8 pos = 0;
	
	LCD_SendCom(0x30);						//这里是最重要的
														//，不同的功能切换的时候事先一定要声明是在哪个模式下的命令
	 switch(x)
    {
        case 1:
        x = 0x80;break;
        case 2:
        x = 0x90;break;
        case 3:
        x = 0x88;break;
        case 4:
        x = 0x98;break;
        default:break;
    } 
	
	pos = x + y;
	
	LCD_SendCom(pos);
}


void Delay_100us(void)
{
	delay_us(100);
}


//发送一个字节
void LCD_SendBity(u8 del)
{
	u8 i = 8 , data;
	data = del;
	
	LCD_CLK_H;								//每次发送的数据或者命令的话，都先拉高时钟线和数据线
	LCD_DATA_H;
	Delay_100us();
	
	while(i)
	{
		if(data & 0x80)
			LCD_DATA_H;
		else
			LCD_DATA_L;
		Delay_100us();
		
		LCD_CLK_L;							//时钟线拉高，延时一段时间再拉低，拉低意味着数据线上的数据要被12864锁存了
		Delay_100us();
		Delay_100us();
		LCD_CLK_H;
		Delay_100us();
		
		data = data << 1;
		i = i -1;
	}
}

//发送数据
void Send_Words(u8 ch)
{
	u8 data;														//发送数据，也是要分三个字节来发送，注意这次是fa开头，是发送，且发送的是数据的意思
	
	LCD_CS_H;
	
	data = ch;
	LCD_SendBity(0xfa);
	
	LCD_SendBity(data & 0xf0);
	LCD_SendBity( (data << 4) & 0xf0);

	LCD_CS_L;	
}

//发送命令
void LCD_SendCom(u8 com)										//发送命令，分三个字节发送，注意第一个字节哦，f8，是指发送动作，且是发送命令
{
	u8 data;
	
	LCD_CS_H;
	
	data = com;
	LCD_SendBity(0xf8);
	LCD_SendBity(data & 0xf0);
	
	LCD_SendBity( (data << 4) & 0xf0);

	LCD_CS_L;

}

void LCD_Clear(void)        //清除显示
{
    LCD_SendCom(0x01);
}

/***********************************************************************************
                  清除文本
************************************************************************************/
void LcmClearTXT( void )
{
	unsigned char i;
	LCD_SendCom(0x30);
	LCD_SendCom(0x80);
	for(i=0;i<64;i++)
	Send_Words(0x20);
	LCD_Set_Position(1, 0); 	    
}

/************************************************************************
*名    称：LCD_DispString()
*功    能：显示一个字符串，显示位置需提前设定
*入口参数：str[]:待显示的字符串
*出口参数：无
************************************************************************/
void LCD_DispString(char *str)
{
	uint16_t i;
	for(i=0;str[i]!='\0';i++)
	{
	    Send_Words(str[i]);
	}
}
/******************************************************************
*指定地址写字符串
* y_add   y地址
* x_add   x地址
* *str    字符串
*********************************************************************/

void LCD_Wstr(unsigned char y_add , unsigned char x_add , char *str)    
{
    LCD_Set_Position(y_add , x_add);
  	LCD_DispString(str);  
    
}
/*********************************************************************
*名    称：LCD_Dispnum()
*功    能：显示一个不超过8位的整数，显示位置需提前设置
*入口参数：num:待显示的整数，不超过8位
*出口参数：无
*********************************************************************/
void LCD_Dispnum(uint32_t num)
{
   char str[12];
   uint32_t q;
   uint16_t wei,i,j,k;
   if(num>=10000000)wei=8;
   else if(num>=1000000)wei=7;
   else if(num>=100000)wei=6;
   else if(num>=10000)wei=5;
   else if(num>=1000) wei=4;
   else if(num>=100)wei=3;
   else if(num>=10) wei=2;
   else wei=1;
   k=0;
   if(wei==1)str[k++]='0';
   for(i=wei;i>0;i--)
   {   q=1;
       j=1; //i=1时，q=1,得到个位
	   for(;j<i;j++)q *=10;
	   str[k++]=num/q +'0';
	   num %= q;
   }
   str[k] = '\0'; //添加字符串结束标志
   LCD_DispString(str);//显示字符串
}
/*********************************************************************
*名    称：LCD_Setpos_Dispnum()
*功    能：在指定位置显示一个不超过8位的整数
*入口参数：num:待显示的整数，不超过8位
*出口参数：无
*********************************************************************/
void LCD_Setpos_Dispnum(uint16_t row,uint16_t col,uint32_t num)
{
   LCD_Set_Position(row , col);	
   LCD_Dispnum(num);
}
void LCD_Setpos_two_Dispnum(uint16_t row,uint16_t col,char num)
{
		char str[3];
		str[0]=num/10+0x30;
		str[1]=num%10+0x30;
	 str[2] = '\0';
   LCD_Set_Position(row , col);	
   LCD_DispString(str);
}
void LCD_Setpos_shi_Dispnum(uint16_t row,uint16_t col,char year,char yue,char ri)
{
		char str[10];
		str[0]=year/10+0x30;
		str[1]=year%10+0x30;
		str[2]=':';
		str[3]=yue/10+0x30;
		str[4]=yue%10+0x30;
		str[5]=':';
		str[6]=ri/10+0x30;
		str[7]=ri%10+0x30;	
		str[8] = '\0';
   LCD_Set_Position(row , col);	
   LCD_DispString(str);
}
void LCD_string_Dis(uint16_t row,uint16_t col,unsigned char *strx)
{
		char str[50]={0};
		unsigned char i;
		for(i=0;strx[i]!=0;i++)
		{
			if(strx[i]<0x80)//英文
			{
				str[i]=strx[i];
			}else
			{
				str[i]=strx[i];
				i+=1;
				str[i]=strx[i];
			}
		}
		LCD_Set_Position(row , col);	
		LCD_DispString(str);
}
#endif

#if CONFIG_MAX6675 == ENABLED


void MAX6675_Delay(void)
{
	//delay_us(5);
	delay_ms(1);
}


void MAX6675_Processing(unsigned char CH,unsigned short *temp)
{
	
	unsigned char i;   
	unsigned int dat;
	unsigned int t;
	
	unsigned char Flag_connect;
	
	i   = 0;   
	dat = 0;   
	
	switch(CH)
	{
		case 0:	CS1 = 0;break;
		case 1: CS2 = 0;break;
		case 2: CS3 = 0;break;
		case 3: CS4 = 0;break;
	}

	MAX6675_Delay();
	SCK = 0;     
	MAX6675_Delay();
	
	for(i=0; i<16; i++)		//get D15-D0 from 6675  
	{      
		SCK = 1; 
		MAX6675_Delay();    
		dat = dat<<1;  
		
		if(  SO == 1 )   
			dat = dat|0x01;  
		
		SCK = 0;   
		MAX6675_Delay();		
	} 
	
	switch(CH){case 0:CS1  = 1; break;case 1: CS2 = 1;break;case 2: CS3 = 1;break;case 3: CS4 = 1;break;}
	
	MAX6675_Delay();  
	
	t = dat;
	

  Flag_connect = t&0x04;		 	//读出数据的D2位是热电偶掉线标志位，该位为1表示掉线，该位为0表示连接
  Flag_connect = Flag_connect>>2; 	//MAX6675是否在线

	t = t<<1;					   	//读出来的数据的D3~D14是温度值
	t = t>>4;
	
	temp[CH] = (t/4)-5;				//测得的温度单位是0.25，所以要乘以0.25（即除以4）才能得到以度为单位的温度值
	
	
}
void MAX6675_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//做输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15		
	//做输出
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6;				 //LED端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC		
}
#endif

#if CONFIG_TEA5767 == ENABLED


unsigned char radio_write_data[5]={0x2d,0x56,0x20,0x11,0x00}; //初始化写入TEA5767的数据(FM89.8Mhz)
unsigned char radio_read_data[5];                    
unsigned int Pll_Data;
unsigned long Frequency_Data;
void Get_Frequency(void);
void _I2C_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	
	
	RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin=I2C_SCL|I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}

void I2C_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

//产生起始信号
void I2C_Start(void)
{
    I2C_SDA_OUT();
	
	I2C_SDA_H;
	I2C_SCL_H;
	delay_us(5);
	I2C_SDA_L;
	delay_us(6);
	I2C_SCL_L;
}

//产生停止信号
void I2C_Stop(void)
{
   I2C_SDA_OUT();

   I2C_SCL_L;
   I2C_SDA_L;
   I2C_SCL_H;
   delay_us(6);
   I2C_SDA_H;
   delay_us(6);
}

//主机产生应答信号ACK
void I2C_Ack(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_L;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}

//主机不产生应答信号NACK
void I2C_NAck(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_H;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}
//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
u8 I2C_Wait_Ack(void)
{
	u8 tempTime=0;

	I2C_SDA_IN();

	I2C_SDA_H;
	delay_us(1);
	I2C_SCL_H;
	delay_us(1);

	while(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C_Stop();
			return 1;
		}	 
	}

	I2C_SCL_L;
	return 0;
}
//I2C 发送一个字节
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_us(2); //发送数据
		I2C_SCL_L;
		delay_us(2);
	}
}

//I2C 读取一个字节

u8 I2C_Read_Byte(u8 ack)
{
   u8 i=0,receive=0;

   I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C_SCL_L;
		delay_us(2);
		I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
		   receive++;
		delay_us(1);	
   }

   	if(ack==0)
	   	I2C_NAck();
	else
		I2C_Ack();

	return receive;
}

void ATIICxx_PWrite(unsigned char *McuAddress,unsigned char count)
{
I2C_Start();
I2C_Send_Byte( ATIIcxxDriverAddressW );
while(count--)
{
   I2C_Send_Byte( *(unsigned char*)McuAddress );
   McuAddress++;
}
I2C_Stop();
}

void ATIICxx_PRead(unsigned char *McuAddress,unsigned char count)
{
I2C_Start();
I2C_Send_Byte( ATIIcxxDriverAddressR );
while(count--)
{
   *McuAddress = I2C_Read_Byte(1);
   //I2C_Ack();
   McuAddress++;
}

I2C_NAck();
I2C_Stop();
}


/***********************************************************************************/
//读TEA5767状态,并转换成频率
void Radio_Read(void)
{
    unsigned char temp_l,temp_h;
    Pll_Data = 0;

    ATIICxx_PRead(&radio_read_data[0],5);
   
    temp_l = radio_read_data[1];
    temp_h = radio_read_data[0];
    temp_h &= 0x3f;
    Pll_Data = temp_h*256+temp_l;
    Get_Frequency();
}

/***********************************************************************************/
//由PLL计算频率
void Get_Frequency(void)
{
    unsigned char hlsi;
    unsigned int npll = 0;
   
    npll = Pll_Data;
    hlsi = radio_read_data[2]&0x10;
    if (hlsi)
        Frequency_Data = (unsigned long)((float)(npll)*(float)REFERENCE_FREQ*(float)0.25-225);    //频率单位:KHz
    else
        Frequency_Data = (unsigned long)((float)(npll)*(float)REFERENCE_FREQ*(float)0.25+225);    //频率单位:KHz
}

/***********************************************************************************/
//由频率计算PLL
void Get_Pll(void)
{
    unsigned char hlsi;

    hlsi = radio_read_data[2]&0x10;
    if (hlsi)
        Pll_Data = (unsigned int)((float)((Frequency_Data+225)*4)/(float)REFERENCE_FREQ);    //频率单位:k
    else
        Pll_Data = (unsigned int)((float)((Frequency_Data-225)*4)/(float)REFERENCE_FREQ);    //频率单位:k
}

/***********************************************************************************/
//手动设置频率,mode=1,+0.1MHz; mode="0:-0".1MHz ,不用考虑TEA5767用于搜台的相关位:SM,SUD
void Search(unsigned char mode)
{
    Radio_Read();
           
    if(mode)
    {
        Frequency_Data += 100;
        if(Frequency_Data > max_freq)
            Frequency_Data = min_freq;
    }
    else
    {
        Frequency_Data -= 100;
        if(Frequency_Data < min_freq)
            Frequency_Data = max_freq;
    }
             
    Get_Pll();
    radio_write_data[0] = Pll_Data/256;
    radio_write_data[1] = Pll_Data%256;
    radio_write_data[2] = 0x41;
    radio_write_data[3] = 0x11;
    radio_write_data[4] = 0x40;
    ATIICxx_PWrite(&radio_write_data[0],5);
}

/***********************************************************************************/
//自动搜台,mode=1,频率增加搜台; mode="0:频率减小搜台".
void Auto_Search(unsigned char mode)
{
    Radio_Read();
    Get_Pll();
    if(mode)
    {
        radio_write_data[2] = 0xb1;
        if(Pll_Data > max_pll)
        {
            Pll_Data = min_pll;
        }
    }
    else
    {
        radio_write_data[2] = 0x41;
        if(Pll_Data < min_pll)
        {
            Pll_Data = max_pll;
        }
    }
         
    radio_write_data[0] = Pll_Data/256+0x40;
    radio_write_data[1] = Pll_Data%256;   
    radio_write_data[3] = 0x11;
    radio_write_data[4] = 0x40;
    ATIICxx_PWrite(&radio_write_data[0],5);
    Radio_Read();
    while(!(radio_read_data[0]&0x80))     //RF电台就绪标志
    {
        Radio_Read();
    }   
}

#endif

#if CONFIG_CALENDAR_CHA == ENABLED

	
bit c_moon=0;                               //平年/润年  =0表示平年，=1表示润年
 uchar year_moon,month_moon,day_moon,week;
///月份数据表
 uchar day_code1[9]={0x0,0x1f,0x3b,0x5a,0x78,0x97,0xb5,0xd4,0xf3};
 uint day_code2[3]={0x111,0x130,0x14e};
//********阳历转换阴历表************************************
const uchar year_code[597]={
                    0x04,0xAe,0x53,    //1901 0
                    0x0A,0x57,0x48,    //1902 3
                    0x55,0x26,0xBd,    //1903 6
                    0x0d,0x26,0x50,    //1904 9
                    0x0d,0x95,0x44,    //1905 12
                    0x46,0xAA,0xB9,    //1906 15
                    0x05,0x6A,0x4d,    //1907 18
                    0x09,0xAd,0x42,    //1908 21
                    0x24,0xAe,0xB6,    //1909
                    0x04,0xAe,0x4A,    //1910
                    0x6A,0x4d,0xBe,    //1911
                    0x0A,0x4d,0x52,    //1912
                    0x0d,0x25,0x46,    //1913
                    0x5d,0x52,0xBA,    //1914
                    0x0B,0x54,0x4e,    //1915
                    0x0d,0x6A,0x43,    //1916
                    0x29,0x6d,0x37,    //1917
                    0x09,0x5B,0x4B,    //1918
                    0x74,0x9B,0xC1,    //1919
                    0x04,0x97,0x54,    //1920
                    0x0A,0x4B,0x48,    //1921
                    0x5B,0x25,0xBC,    //1922
                    0x06,0xA5,0x50,    //1923
                    0x06,0xd4,0x45,    //1924
                    0x4A,0xdA,0xB8,    //1925
                    0x02,0xB6,0x4d,    //1926
                    0x09,0x57,0x42,    //1927
                    0x24,0x97,0xB7,    //1928
                    0x04,0x97,0x4A,    //1929
                    0x66,0x4B,0x3e,    //1930
                    0x0d,0x4A,0x51,    //1931
                    0x0e,0xA5,0x46,    //1932
                    0x56,0xd4,0xBA,    //1933
                    0x05,0xAd,0x4e,    //1934
                    0x02,0xB6,0x44,    //1935
                    0x39,0x37,0x38,    //1936
                    0x09,0x2e,0x4B,    //1937
                    0x7C,0x96,0xBf,    //1938
                    0x0C,0x95,0x53,    //1939
                    0x0d,0x4A,0x48,    //1940
                    0x6d,0xA5,0x3B,    //1941
                    0x0B,0x55,0x4f,    //1942
                    0x05,0x6A,0x45,    //1943
                    0x4A,0xAd,0xB9,    //1944
                    0x02,0x5d,0x4d,    //1945
                    0x09,0x2d,0x42,    //1946
                    0x2C,0x95,0xB6,    //1947
                    0x0A,0x95,0x4A,    //1948
                    0x7B,0x4A,0xBd,    //1949
                    0x06,0xCA,0x51,    //1950
                    0x0B,0x55,0x46,    //1951
                    0x55,0x5A,0xBB,    //1952
                    0x04,0xdA,0x4e,    //1953
                    0x0A,0x5B,0x43,    //1954
                    0x35,0x2B,0xB8,    //1955
                    0x05,0x2B,0x4C,    //1956
                    0x8A,0x95,0x3f,    //1957
                    0x0e,0x95,0x52,    //1958
                    0x06,0xAA,0x48,    //1959
                    0x7A,0xd5,0x3C,    //1960
                    0x0A,0xB5,0x4f,    //1961
                    0x04,0xB6,0x45,    //1962
                    0x4A,0x57,0x39,    //1963
                    0x0A,0x57,0x4d,    //1964
                    0x05,0x26,0x42,    //1965
                    0x3e,0x93,0x35,    //1966
                    0x0d,0x95,0x49,    //1967
                    0x75,0xAA,0xBe,    //1968
                    0x05,0x6A,0x51,    //1969
                    0x09,0x6d,0x46,    //1970
                    0x54,0xAe,0xBB,    //1971
                    0x04,0xAd,0x4f,    //1972
                    0x0A,0x4d,0x43,    //1973
                    0x4d,0x26,0xB7,    //1974
                    0x0d,0x25,0x4B,    //1975
                    0x8d,0x52,0xBf,    //1976
                    0x0B,0x54,0x52,    //1977
                    0x0B,0x6A,0x47,    //1978
                    0x69,0x6d,0x3C,    //1979
                    0x09,0x5B,0x50,    //1980
                    0x04,0x9B,0x45,    //1981
                    0x4A,0x4B,0xB9,    //1982
                    0x0A,0x4B,0x4d,    //1983
                    0xAB,0x25,0xC2,    //1984
                    0x06,0xA5,0x54,    //1985
                    0x06,0xd4,0x49,    //1986
                    0x6A,0xdA,0x3d,    //1987
                    0x0A,0xB6,0x51,    //1988
                    0x09,0x37,0x46,    //1989
                    0x54,0x97,0xBB,    //1990
                    0x04,0x97,0x4f,    //1991
                    0x06,0x4B,0x44,    //1992
                    0x36,0xA5,0x37,    //1993
                    0x0e,0xA5,0x4A,    //1994
                    0x86,0xB2,0xBf,    //1995
                    0x05,0xAC,0x53,    //1996
                    0x0A,0xB6,0x47,    //1997
                    0x59,0x36,0xBC,    //1998
                    0x09,0x2e,0x50,    //1999 294
                    0x0C,0x96,0x45,    //2000 297
                    0x4d,0x4A,0xB8,    //2001
                    0x0d,0x4A,0x4C,    //2002
                    0x0d,0xA5,0x41,    //2003
                    0x25,0xAA,0xB6,    //2004
                    0x05,0x6A,0x49,    //2005
                    0x7A,0xAd,0xBd,    //2006
                    0x02,0x5d,0x52,    //2007
                    0x09,0x2d,0x47,    //2008
                    0x5C,0x95,0xBA,    //2009
                    0x0A,0x95,0x4e,    //2010
                    0x0B,0x4A,0x43,    //2011
                    0x4B,0x55,0x37,    //2012
                    0x0A,0xd5,0x4A,    //2013
                    0x95,0x5A,0xBf,    //2014
                    0x04,0xBA,0x53,    //2015
                    0x0A,0x5B,0x48,    //2016
                    0x65,0x2B,0xBC,    //2017
                    0x05,0x2B,0x50,    //2018
                    0x0A,0x93,0x45,    //2019
                    0x47,0x4A,0xB9,    //2020
                    0x06,0xAA,0x4C,    //2021
                    0x0A,0xd5,0x41,    //2022
                    0x24,0xdA,0xB6,    //2023
                    0x04,0xB6,0x4A,    //2024
                    0x69,0x57,0x3d,    //2025
                    0x0A,0x4e,0x51,    //2026
                    0x0d,0x26,0x46,    //2027
                    0x5e,0x93,0x3A,    //2028
                    0x0d,0x53,0x4d,    //2029
                    0x05,0xAA,0x43,    //2030
                    0x36,0xB5,0x37,    //2031
                    0x09,0x6d,0x4B,    //2032
                    0xB4,0xAe,0xBf,    //2033
                    0x04,0xAd,0x53,    //2034
                    0x0A,0x4d,0x48,    //2035
                    0x6d,0x25,0xBC,    //2036
                    0x0d,0x25,0x4f,    //2037
                    0x0d,0x52,0x44,    //2038
                    0x5d,0xAA,0x38,    //2039
                    0x0B,0x5A,0x4C,    //2040
                    0x05,0x6d,0x41,    //2041
                    0x24,0xAd,0xB6,    //2042
                    0x04,0x9B,0x4A,    //2043
                    0x7A,0x4B,0xBe,    //2044
                    0x0A,0x4B,0x51,    //2045
                    0x0A,0xA5,0x46,    //2046
                    0x5B,0x52,0xBA,    //2047
                    0x06,0xd2,0x4e,    //2048
                    0x0A,0xdA,0x42,    //2049
                    0x35,0x5B,0x37,    //2050
                    0x09,0x37,0x4B,    //2051
                    0x84,0x97,0xC1,    //2052
                    0x04,0x97,0x53,    //2053
                    0x06,0x4B,0x48,    //2054
                    0x66,0xA5,0x3C,    //2055
                    0x0e,0xA5,0x4f,    //2056
                    0x06,0xB2,0x44,    //2057
                    0x4A,0xB6,0x38,    //2058
                    0x0A,0xAe,0x4C,    //2059
                    0x09,0x2e,0x42,    //2060
                    0x3C,0x97,0x35,    //2061
                    0x0C,0x96,0x49,    //2062
                    0x7d,0x4A,0xBd,    //2063
                    0x0d,0x4A,0x51,    //2064
                    0x0d,0xA5,0x45,    //2065
                    0x55,0xAA,0xBA,    //2066
                    0x05,0x6A,0x4e,    //2067
                    0x0A,0x6d,0x43,    //2068
                    0x45,0x2e,0xB7,    //2069
                    0x05,0x2d,0x4B,    //2070
                    0x8A,0x95,0xBf,    //2071
                    0x0A,0x95,0x53,    //2072
                    0x0B,0x4A,0x47,    //2073
                    0x6B,0x55,0x3B,    //2074
                    0x0A,0xd5,0x4f,    //2075
                    0x05,0x5A,0x45,    //2076
                    0x4A,0x5d,0x38,    //2077
                    0x0A,0x5B,0x4C,    //2078
                    0x05,0x2B,0x42,    //2079
                    0x3A,0x93,0xB6,    //2080
                    0x06,0x93,0x49,    //2081
                    0x77,0x29,0xBd,    //2082
                    0x06,0xAA,0x51,    //2083
                    0x0A,0xd5,0x46,    //2084
                    0x54,0xdA,0xBA,    //2085
                    0x04,0xB6,0x4e,    //2086
                    0x0A,0x57,0x43,    //2087
                    0x45,0x27,0x38,    //2088
                    0x0d,0x26,0x4A,    //2089
                    0x8e,0x93,0x3e,    //2090
                    0x0d,0x52,0x52,    //2091
                    0x0d,0xAA,0x47,    //2092
                    0x66,0xB5,0x3B,    //2093
                    0x05,0x6d,0x4f,    //2094
                    0x04,0xAe,0x45,    //2095
                    0x4A,0x4e,0xB9,    //2096
                    0x0A,0x4d,0x4C,    //2097
                    0x0d,0x15,0x41,    //2098
                    0x2d,0x92,0xB5,    //2099
};

/*
函数功能:输入BCD阳历数据,输出BCD阴历数据(只允许1901-2099年)
调用函数示例:Conversion(c_sun,year_sun,month_sun,day_sun)
如:计算2004年10月16日Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun均为BCD数据,c_sun为世纪标志位,c_sun=0为21世
纪,c_sun=1为19世纪
调用函数后,原有数据不变,读c_moon,year_moon,month_moon,day_moon得出阴历BCD数据
*/
//子函数,用于读取数据表中农历月的大月或小月,如果该月为大返回1,为小返回0
bit get_moon_day(uchar month_p,uint table_addr)
{
    uchar temp;
    switch (month_p){
        case 1:{temp=year_code[table_addr]&0x08;
             if (temp==0)return(0);else return(1);}
        case 2:{temp=year_code[table_addr]&0x04;
             if (temp==0)return(0);else return(1);}
        case 3:{temp=year_code[table_addr]&0x02;
             if (temp==0)return(0);else return(1);}
        case 4:{temp=year_code[table_addr]&0x01;
             if (temp==0)return(0);else return(1);}
        case 5:{temp=year_code[table_addr+1]&0x80;
             if (temp==0) return(0);else return(1);}
        case 6:{temp=year_code[table_addr+1]&0x40;
             if (temp==0)return(0);else return(1);}
        case 7:{temp=year_code[table_addr+1]&0x20;
             if (temp==0)return(0);else return(1);}
        case 8:{temp=year_code[table_addr+1]&0x10;
             if (temp==0)return(0);else return(1);}
        case 9:{temp=year_code[table_addr+1]&0x08;
             if (temp==0)return(0);else return(1);}
        case 10:{temp=year_code[table_addr+1]&0x04;
             if (temp==0)return(0);else return(1);}
        case 11:{temp=year_code[table_addr+1]&0x02;
             if (temp==0)return(0);else return(1);}
        case 12:{temp=year_code[table_addr+1]&0x01;
             if (temp==0)return(0);else return(1);}
        case 13:{temp=year_code[table_addr+2]&0x80;
             if (temp==0)return(0);else return(1);}
    }
    return(0);
}

/*
函数功能:输入BCD阳历数据,输出BCD阴历数据(只允许1901-2099年)
调用函数示例:Conversion(c_sun,year_sun,month_sun,day_sun)
如:计算2004年10月16日Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun均为BCD数据,c_sun为世纪标志位,c_sun=0为21世
纪,c_sun=1为19世纪
调用函数后,原有数据不变,读c_moon,year_moon,month_moon,day_moon得出阴历BCD数据
*/

u32 _crol_(u32 data,u8 num)
{
	u8 i=0;
	u32 temp1=0;
	u32 temp2=0;
	u32 rtn_data;
	
	temp1=data;
	
	for(i=0;i<num;i++)
	{
		temp1=temp1<<1;
		temp2=temp2<<1;	
    if(temp1>0x0fffffff)
	  {
	  temp2+=1;
	  }
	
	  
	}
  rtn_data=temp1+temp2;
	return rtn_data;
 
}

u32 _cror_(u32 data,u8 num)
{
	u8 i=0;
	u32 temp1=0;
	u32 temp2=0;
	u32 rtn_data;
	
	temp1=data;
	
	for(i=0;i<num;i++)
	{
		temp2=temp2>>1;
		temp1=temp1>>1;
    if(temp1%2)
	  {
	  temp2+=0x8000000;
	  }
		
	  
	 
	}
  rtn_data=temp1+temp2;
	return rtn_data;

}
void Conversion(bit c,uchar year,uchar month,uchar day)
{                         //c=0 为21世纪,c=1 为19世纪 输入输出数据均为BCD数据
    uchar temp1,temp2,temp3,month_p;
    uint temp4,table_addr;
    bit flag2,flag_y;
    temp1=year/16;   //BCD->hex 先把数据转换为十六进制
    temp2=year%16;
   // year=temp1*10+temp2;
    year=temp1*16+temp2;
    temp1=month/16;
    temp2=month%16;
    //month=temp1*10+temp2;
    month=temp1*16+temp2;
    temp1=day/16;
    temp2=day%16;
    //day=temp1*10+temp2;
    day=temp1*16+temp2;
    //定位数据表地址
    if(c==0){                   
        table_addr=(year+0x64-1)*0x3;
    }
    else {
        table_addr=(year-1)*0x3;
    }
    //定位数据表地址完成
    //取当年春节所在的公历月份
    temp1=year_code[table_addr+2]&0x60; 
    temp1=_cror_(temp1,5);
    //取当年春节所在的公历月份完成
    //取当年春节所在的公历日
    temp2=year_code[table_addr+2]&0x1f; 
    //取当年春节所在的公历日完成
    // 计算当年春年离当年元旦的天数,春节只会在公历1月或2月
    if(temp1==0x1){  
        temp3=temp2-1;  
    }  
    else{
        temp3=temp2+0x1f-1;        
    }
    // 计算当年春年离当年元旦的天数完成
    //计算公历日离当年元旦的天数,为了减少运算,用了两个表
    //day_code1[9],day_code2[3]
    //如果公历月在九月或前,天数会少于0xff,用表day_code1[9],
    //在九月后,天数大于0xff,用表day_code2[3]
    //如输入公历日为8月10日,则公历日离元旦天数为day_code1[8-1]+10-1
    //如输入公历日为11月10日,则公历日离元旦天数为day_code2[11-10]+10-1
    if (month<10){ 
        temp4=day_code1[month-1]+day-1;
    }
    else{
        temp4=day_code2[month-10]+day-1;
    }
    if ((month>0x2)&&(year%0x4==0)){  //如果公历月大于2月并且该年的2月为闰月,天数加1
        temp4+=1;
    }
    //计算公历日离当年元旦的天数完成
    //判断公历日在春节前还是春节后
    if (temp4>=temp3){ //公历日在春节后或就是春节当日使用下面代码进行运算
        temp4-=temp3;
        month=0x1;
        month_p=0x1;  //month_p为月份指向,公历日在春节前或就是春节当日month_p指向首月
        flag2=get_moon_day(month_p,table_addr); //检查该农历月为大小还是小月,大月返回1,小月返回0
        flag_y=0;
        if(flag2==0)temp1=0x1d; //小月29天
        else temp1=0x1e; //大小30天
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);  //从数据表中取该年的闰月月份,如为0则该年无闰月
        while(temp4>=temp1){
            temp4-=temp1;
            month_p+=1;
            if(month==temp2){
            flag_y=~flag_y;
            if(flag_y==0)month+=1;
            }
            else month+=1;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)temp1=0x1d;
            else temp1=0x1e;
        }
        day=temp4+1;
    }
    else{  //公历日在春节前使用下面代码进行运算
        temp3-=temp4;
        if (year==0x0){year=0x63;c=1;}
        else year-=1;
        table_addr-=0x3;
        month=0xc;
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);
        if (temp2==0)
            month_p=0xc; 
        else
            month_p=0xd; //
        
         //month_p为月份指向,如果当年有闰月,一年有十三个月,月指向13,无闰月指向12
        
        flag_y=0;
        flag2=get_moon_day(month_p,table_addr);
        if(flag2==0)temp1=0x1d;
        else temp1=0x1e;
        while(temp3>temp1){
            temp3-=temp1;
            month_p-=1;
            if(flag_y==0)month-=1;
            if(month==temp2)flag_y=~flag_y;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)temp1=0x1d;
            else temp1=0x1e;
         }
        day=temp1-temp3+1;
    }
    c_moon=c;                 //HEX->BCD ,运算结束后,把数据转换为BCD数据
    temp1=year/10;
    temp1=_crol_(temp1,4);
    temp2=year%10;
    year_moon=temp1|temp2;
    temp1=month/10;
    temp1=_crol_(temp1,4);
    temp2=month%10;
    month_moon=temp1|temp2;
    temp1=day/10;
    temp1=_crol_(temp1,4);
    temp2=day%10;
    day_moon=temp1|temp2;

    year_moon  = year_moon/16*10  + year_moon%16;
    month_moon = month_moon/16*10 + month_moon%16;
    day_moon   = day_moon/16*10   + day_moon%16;
}
/*
函数功能:输入BCD阳历数据,输出BCD星期数据(只允许1901-2099年)
调用函数示例:Conver_week(c_sun,year_sun,month_sun,day_sun)
如:计算2004年10月16日Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun均为BCD数据,c_sun为世纪标志位,c_sun=0为21世
纪,c_sun=1为19世纪
调用函数后,原有数据不变,读week得出阴历BCD数据
*/
uchar table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表
/*
算法:日期+年份+所过闰年数+月较正数之和除7 的余数就是星期但如果是在
闰年又不到3 月份上述之和要减一天再除7
星期数为0
*/
void Conver_week(uchar year,uchar month,uchar day)
{//c=0 为21世纪,c=1 为19世纪 输入输出数据均为BCD数据
    uchar p1,p2;
    year+=0x64;  //如果为21世纪,年份数加100
    p1=year/0x4;  //所过闰年数只算1900年之后的
    p2=year+p1;
    p2=p2%0x7;  //为节省资源,先进行一次取余,避免数大于0xff,避免使用整型数据
    p2=p2+day+table_week[month-1];
    if (year%0x4==0&&month<3)p2-=1;
    week=p2%0x7;
}
/********************************************************
函数名称:uchar Getnonnian(uchar GreYear)
函数作用:计算阳历对应农历年份
参数说明:输入：阳历年份
         输出：阴历年份
********************************************************/
uchar Getnonnian(uchar GreYear)
{
    uchar a,b;
    a=GreYear%10;
    b=(8+GreYear)%12;
    return (b*16+a);
}


#endif

#if CONFIG_BH1750 == ENABLED


unsigned char    BUF[8];               //接收数据缓存区  
int   mcy;     //进位标志

/***开始信号***/
void BH1750_Start()
{
  SDA=1;                    //拉高数据线
  SCL=1;                   //拉高时钟线
  delay_us(5);                 //延时
  GPIO_ResetBits(bh1750_PORT, sda);                    //产生下降沿
  delay_us(5);                 //延时
  GPIO_ResetBits(bh1750_PORT, scl);                    //拉低时钟线
}

/*****停止信号******/
void BH1750_Stop()
{
    SDA=0;                   //拉低数据线
    SCL=1;                      //拉高时钟线
    delay_us(5);                 //延时
    GPIO_SetBits(bh1750_PORT, sda);                    //产生上升沿
    delay_us(5);                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(int ack)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Pin = sda;
  GPIO_Init(bh1750_PORT, &GPIO_InitStruct);  
	
	if(ack == 1)   //写应答信号
		SDA=1; 
	else if(ack == 0)
		SDA=0; 
	else
		return;			
  SCL=1;     //拉高时钟线
  delay_us(5);                 //延时
  SCL=0;      //拉低时钟线
  delay_us(5);                //延时
}

/**************************************
接收应答信号
**************************************/
int BH1750_RecvACK()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;  /*这里一定要设成输入上拉，否则不能读出数据*/
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Pin=sda;
  GPIO_Init(bh1750_PORT,&GPIO_InitStruct);
	
  SCL=1;            //拉高时钟线
  delay_us(5);                 //延时	
	if(GPIO_ReadInputDataBit(GPIOA,sda)==1)//读应答信号
    mcy = 1 ;  
  else
    mcy = 0 ;				
  SCL=0;                    //拉低时钟线
  delay_us(5);                 //延时
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_Init(bh1750_PORT,&GPIO_InitStruct);
	return mcy;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void BH1750_SendByte(uchar dat)
{
  uchar i;
  for (i=0; i<8; i++)         //8位计数器
  {
		if( 0X80 & dat )
      GPIO_SetBits(bh1750_PORT,sda);
    else
      GPIO_ResetBits(bh1750_PORT,sda);
		dat <<= 1;
    SCL=1;               //拉高时钟线
    delay_us(5);             //延时
    SCL=0;                //拉低时钟线
    delay_us(5);            //延时
  }
  BH1750_RecvACK();
}

uchar BH1750_RecvByte()
{
  uchar i;
  uchar dat = 0;
	uchar bit;
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;   /*这里一定要设成输入上拉，否则不能读出数据*/
  GPIO_InitStruct.GPIO_Pin = sda;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(bh1750_PORT,&GPIO_InitStruct );
	
  GPIO_SetBits(bh1750_PORT,sda);          //使能内部上拉,准备读取数据,
  for (i=0; i<8; i++)         //8位计数器
  {
    dat <<= 1;
    SCL=1;               //拉高时钟线
    delay_us(5);             //延时
			
		if( SET == GPIO_ReadInputDataBit(bh1750_PORT,sda))
      bit = 0X01;
    else
      bit = 0x00;  
		dat |= bit;             //读数据    
		SCL=0;                //拉低时钟线
    delay_us(5);            //延时
  }		
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(bh1750_PORT, &GPIO_InitStruct );
  return dat;
}

void Single_Write_BH1750(uchar REG_Address)
{
  BH1750_Start();                  //起始信号
  BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
  BH1750_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
//  BH1750_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
  BH1750_Stop();                   //发送停止信号
}

//初始化BH1750，根据需要请参考pdf进行修改****
void Init_BH1750()
{
  GPIO_InitTypeDef GPIO_InitStruct;
	 /*开启GPIOB的外设时钟*/ 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Pin = sda | scl ;
  GPIO_Init(bh1750_PORT,&GPIO_InitStruct); 
	
  Single_Write_BH1750(0x01);  
	delay_ms(180);            //延时180ms
}

//连续读出BH1750内部数据
void mread(void)
{   
	uchar i;	
  BH1750_Start();                          //起始信号
  BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	
	for (i=0; i<3; i++)                      //连续读取6个地址数据，存储中BUF
  {
    BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
    if (i == 3)
    {
      BH1750_SendACK(1);                //最后一个数据需要回NOACK
    }
    else
    {		
      BH1750_SendACK(0);                //回应ACK
    }
  }
  BH1750_Stop();                          //停止信号
  delay_ms(5);
}

float read_BH1750(void)
{
  int dis_data;                       //变量	
	float temp1;
	float temp2;
	Single_Write_BH1750(0x01);   // power on
  Single_Write_BH1750(0x10);   // H- resolution mode
  delay_ms(180);            //延时180ms
	mread();       //连续读出数据，存储在BUF中
  dis_data=BUF[0];
  dis_data=(dis_data<<8)+BUF[1]; //合成数据 
	temp1=dis_data/1.2;
	temp2=10*dis_data/1.2;	//取小数点
	temp2=(int)temp2%10;
//	OLED_ShowString(87,2,".",12); 
//	OLED_ShowNum(94,2,temp2,1,12);	
	return temp1;
}

#endif

#if CONFIG_HLW8032 == ENABLED
u8 a3;
#define USART3_REC_LEN  			200  
u8 USART3_RX_BUF[USART3_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
float ACVotage,ACCurrent,ActivePower,ApparentPower,PowerFactor,ElectricEnergy,E_Zero=0;
int ActivePower_temp;
u8 Pre_Data_Updata_Reg;
u16 UpdataCount;
u32 PFCount,PF_OneDegree;
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记	 
u32 Voltage_Parameter_Reg,Voltage_Reg,Current_Reg,Current_Parameter_Reg,Power_Parameter_Reg,Power_Reg;
u8 Data_Updata_Reg;
u16 PF_Reg;
u8 CmdAnalysis(u8* data,u16 len)
{
	u16 sum;
	u8 cheaksum,i;
	if(len<24)
	{
		return 1;
		
	}
	else 
   {
		 for(i=2;i<len-1;i++)
		 {
			sum+=data[i];
		 }
		 cheaksum=sum&0xFF;
		 if(cheaksum==data[len-1])
		 {
			 Voltage_Parameter_Reg=(u32)data[2]<<16|(u32)data[3]<<8|(u32)data[4];
			 Voltage_Reg=(u32)data[5]<<16|(u32)data[6]<<8|(u32)data[7];
			 Current_Parameter_Reg=(u32)data[8]<<16|(u32)data[9]<<8|(u32)data[10];
			 Current_Reg=(u32)data[11]<<16|(u32)data[12]<<8|(u32)data[13];
			 Power_Parameter_Reg=(u32)data[14]<<16|(u32)data[15]<<8|(u32)data[16];
			 Power_Reg=(u32)data[17]<<16|(u32)data[18]<<8|(u32)data[19];
			 Data_Updata_Reg=data[20];
			 PF_Reg=(u16)data[21]<<8|data[22];
		 } 
		 else
		 {
			 return 1;
		 }
		 return 0;
	 }
}
void USART3_ConfigDemo(u32 band)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;   
	NVIC_InitTypeDef    NVIC_InitStructure;  
		

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    

		
	//USART3?Tx---GPIO----Pb.10----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//USART3?Rx---GPIO----Pb.11----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                      
		
	USART_InitStructure.USART_BaudRate=band;             
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                      
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART_Init(USART3,&USART_InitStructure);	        //

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //
  USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);  //开启中断  
	USART_Cmd(USART3,ENABLE);                           //

}

void USART3_IRQHandler(void) //??1??????
{
  	u8 Res;
    u16 clear;	
   if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
    {
			 clear=USART3->SR;
			 clear=USART3->DR;
			if(CmdAnalysis(USART3_RX_BUF,USART3_RX_STA)==0)
			{
			

			}
				USART3_RX_STA=0;
  	}		
		else if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
				{
				Res =USART_ReceiveData(USART3);	//读取接收到的数据
				

							USART3_RX_BUF[USART3_RX_STA]=Res ;
							USART3_RX_STA++;
							if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
						
							 
				} 

}
 /*发送一个字节数据*/
 void USART3SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
} 

/*
根据长度向串口2 发送数据
*/
void usart3_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART3, data[i]); //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		//i++;
	}
	//i++;
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}

void Get_HLW8032(void)
{
	static u8 x=0;
	x++;
	if(x==12)x=0;
	//LED0=!LED0;	
	ACVotage=(Voltage_Parameter_Reg*1.88/Voltage_Reg);//电压有效值
	if(ACVotage<=15)
	 ACVotage=0;
	ACCurrent=(Current_Parameter_Reg*1.0/Current_Reg)/2;//电流有效值
	if(ACCurrent<0.1)//无电压时电压又飘移
	{
		ACCurrent=0;
		ApparentPower=0;
		ActivePower=0;
		PowerFactor=0;
	}
	if(ACVotage>2&&ACCurrent>0.1)//空载时电流有飘移
	{
	
	
		ApparentPower=ACVotage*ACCurrent;//视在功率
		ActivePower=Power_Parameter_Reg*1.88/Power_Reg;//有功功率
		PowerFactor=ActivePower/ApparentPower;//功率因数
	}
	/*printf ("电压有效值：%f\r\n",ACVotage);
	printf ("电流有效值：%f\r\n",ACCurrent);
	printf ("视在功率：%f\r\n",ApparentPower);
	printf ("有功功率：%f\r\n",ActivePower);
	printf ("功率因数：%f\r\n",PowerFactor);*/
	if(Pre_Data_Updata_Reg!=(Data_Updata_Reg&0x80))
	{
		UpdataCount++;
		Pre_Data_Updata_Reg=Data_Updata_Reg&0x80;
	}
	PFCount=UpdataCount*65536+PF_Reg;//脉冲信号个数
	PF_OneDegree=1000000000/Power_Parameter_Reg;
	PF_OneDegree=PF_OneDegree*3600/1.88;//1度电对应的脉冲个数；
	ElectricEnergy=(float)PFCount/(float)PF_OneDegree;//电能
	ActivePower_temp = ActivePower;
	/*printf ("电能：%f\r\n",ElectricEnergy);*/
}

#endif

#if CONFIG_RUDDER_PWN == ENABLED
void PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
    //时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    //GPIOB初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
    
	//定时器初始化
	TIM_TimeBaseStruct.TIM_Period=9999;//初值 //到达 10000次 时间 0.002ms*10000=20ms
	TIM_TimeBaseStruct.TIM_Prescaler=143;//预分频 72000000/144=500000HZ	 =0.002ms 
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);	     
   
	//PWM初始化
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);	
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);
    TIM_OC1Init(TIM4,&TIM_OCInitStructure);	
    TIM_OC2Init(TIM4,&TIM_OCInitStructure);
    
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);    
	//TIM3时钟使能
	TIM_Cmd(TIM3,ENABLE);	
	TIM_Cmd(TIM4,ENABLE);	
    TIM_SetCompare1(TIM3,250);//0.002ms*250=0.5ms
    TIM_SetCompare2(TIM3,250);
    TIM_SetCompare1(TIM4,250);
    TIM_SetCompare2(TIM4,250);   	
}
#endif

#if CONFIG_LCD12864_PLUS== ENABLED


#define addX0 0xB8       /* x地址（0页） */
#define addY0 0x40       /* y地址（0列） */
#define addZ0 0xC0       /* Z地址（0行开始显示） */


#define RCC_APB2_GPIOXX  RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA

#define RS                  PAout(11)                            
#define EN                  PAout(12) 
#define cs2                 PAout(7)                            
#define cs1                 PAout(8)
#define BIT_VALUE_GET(v, b) ((v) & (1<<(b)))
typedef struct _PinDef 
{
	GPIO_TypeDef* GPIOX;
	uint16_t GPIO_Pin;
}PinDef;

PinDef PinType[8]=
{
	{GPIOA,GPIO_Pin_15},
	{GPIOB,GPIO_Pin_3},
	{GPIOB,GPIO_Pin_4},
	{GPIOB,GPIO_Pin_5},
	{GPIOB,GPIO_Pin_6},
	{GPIOB,GPIO_Pin_7},
	{GPIOB,GPIO_Pin_8},
	{GPIOB,GPIO_Pin_9}
};
#if CONFIG_CH == ENABLED
unsigned char  zm8x16_index[]="0123456789: |-+.<";//字串索引
unsigned char  zm8x16_Table[][16]={
	0xF8,0xFC,0x04,0xC4,0x24,0xFC,0xF8,0x00,0x07,0x0F,0x09,0x08,0x08,0x0F,0x07,0x00, // -0-
	//0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,
	0x00,0x10,0x18,0xFC,0xFC,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x08,0x08,0x00, // -1-
	0x08,0x0C,0x84,0xC4,0x64,0x3C,0x18,0x00,0x0E,0x0F,0x09,0x08,0x08,0x0C,0x0C,0x00, // -2-
	0x08,0x0C,0x44,0x44,0x44,0xFC,0xB8,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00, // -3-
	0xC0,0xE0,0xB0,0x98,0xFC,0xFC,0x80,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00, // -4-
	0x7C,0x7C,0x44,0x44,0xC4,0xC4,0x84,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00, // -5-
	0xF0,0xF8,0x4C,0x44,0x44,0xC0,0x80,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00, // -6-
	0x0C,0x0C,0x04,0x84,0xC4,0x7C,0x3C,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00, // -7-
	0xB8,0xFC,0x44,0x44,0x44,0xFC,0xB8,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00, // -8-
	0x38,0x7C,0x44,0x44,0x44,0xFC,0xF8,0x00,0x00,0x08,0x08,0x08,0x0C,0x07,0x03,0x00, // -9-
	0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00,0x00, // -:-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // - -
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00, // -|-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, // ---
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0xFF,0x01,0x01,0x01, // -+-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,/*".",0*/	
  0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,/*"<",0*/
};
#else
unsigned char  zm8x16_index[]="0123456789: |-+.<abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//字串索引
unsigned char  zm8x16_Table[][16]={
	0xF8,0xFC,0x04,0xC4,0x24,0xFC,0xF8,0x00,0x07,0x0F,0x09,0x08,0x08,0x0F,0x07,0x00, // -0-
	//0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,
	0x00,0x10,0x18,0xFC,0xFC,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x08,0x08,0x00, // -1-
	0x08,0x0C,0x84,0xC4,0x64,0x3C,0x18,0x00,0x0E,0x0F,0x09,0x08,0x08,0x0C,0x0C,0x00, // -2-
	0x08,0x0C,0x44,0x44,0x44,0xFC,0xB8,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00, // -3-
	0xC0,0xE0,0xB0,0x98,0xFC,0xFC,0x80,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00, // -4-
	0x7C,0x7C,0x44,0x44,0xC4,0xC4,0x84,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00, // -5-
	0xF0,0xF8,0x4C,0x44,0x44,0xC0,0x80,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00, // -6-
	0x0C,0x0C,0x04,0x84,0xC4,0x7C,0x3C,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00, // -7-
	0xB8,0xFC,0x44,0x44,0x44,0xFC,0xB8,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00, // -8-
	0x38,0x7C,0x44,0x44,0x44,0xFC,0xF8,0x00,0x00,0x08,0x08,0x08,0x0C,0x07,0x03,0x00, // -9-
	0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00,0x00, // -:-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // - -
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00, // -|-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, // ---
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0xFF,0x01,0x01,0x01, // -+-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,/*".",0*/	
  0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,/*"<",0*/	
0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x19,0x24,0x24,0x12,0x3F,0x20,0x00,/*"a",0*/
0x10,0xF0,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,/*"b",1*/
0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,/*"c",2*/
0x00,0x00,0x80,0x80,0x80,0x90,0xF0,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,/*"d",3*/
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x24,0x24,0x24,0x24,0x17,0x00,/*"e",4*/
0x00,0x80,0x80,0xE0,0x90,0x90,0x20,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"f",5*/
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,/*"g",6*/
0x10,0xF0,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,/*"h",7*/
0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"i",8*/
0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,/*"j",0*/
0x10,0xF0,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x06,0x29,0x30,0x20,0x00,/*"k",10*/
0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"l",11*/
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,/*"m",12*/
0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,/*"n",13*/
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,/*"o",14*/
0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0x91,0x20,0x20,0x11,0x0E,0x00,/*"p",15*/
0x00,0x00,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0x91,0xFF,0x80,/*"q",16*/
0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,/*"r",17*/
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,/*"s",18*/
0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x10,0x00,/*"t",19*/
0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,/*"u",20*/
0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x03,0x0C,0x30,0x0C,0x03,0x00,0x00,/*"v",21*/
0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x01,0x0E,0x30,0x0C,0x07,0x38,0x06,0x01,/*"w",22*/
0x00,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x20,0x31,0x0E,0x2E,0x31,0x20,0x00,/*"x",23*/
0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x81,0x86,0x78,0x18,0x06,0x01,0x00,/*"y",24*/
0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,/*"z",25*/
0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,/*"A",26*/
0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,/*"B",27*/
0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,/*"C",28*/
0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,/*"D",29*/
0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,/*"E",30*/
0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,/*"F",31*/
0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,/*"G",32*/
0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,/*"H",33*/
0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,/*"I",34*/
0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,/*"J",0*/
0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,/*"K",36*/
0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,/*"L",37*/
0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x01,0x3E,0x01,0x3F,0x20,0x00,/*"M",38*/
0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,/*"N",39*/
0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,/*"O",40*/
0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,/*"P",41*/
0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x28,0x28,0x30,0x50,0x4F,0x00,/*"Q",42*/
0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,/*"R",43*/
0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,/*"S",44*/
0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,/*"T",45*/
0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,/*"U",46*/
0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,/*"V",47*/
0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,0x00,0x03,0x3E,0x01,0x3E,0x03,0x00,0x00,/*"W",48*/
0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,/*"X",49*/
0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,/*"Y",50*/
0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,/*"Z",51*/
};
#endif
unsigned char  zm16x16_index[]="  欢迎使用密码锁请输入密码";//字串索引
unsigned char  zm16x16_Table[][32]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",0*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",1*/

0x04,0x24,0x44,0x84,0x64,0x9C,0x40,0x30,0x0F,0xC8,0x08,0x08,0x28,0x18,0x00,0x00,
0x10,0x08,0x06,0x01,0x82,0x4C,0x20,0x18,0x06,0x01,0x06,0x18,0x20,0x40,0x80,0x00,/*"?",2*/

0x40,0x40,0x42,0xCC,0x00,0x00,0xFC,0x04,0x02,0x00,0xFC,0x04,0x04,0xFC,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x40,0x4F,0x44,0x42,0x40,0x7F,0x42,0x44,0x43,0x40,0x00,/*"?",3*/

0x80,0x60,0xF8,0x07,0x04,0xE4,0x24,0x24,0x24,0xFF,0x24,0x24,0x24,0xE4,0x04,0x00,
0x00,0x00,0xFF,0x00,0x80,0x81,0x45,0x29,0x11,0x2F,0x41,0x41,0x81,0x81,0x80,0x00,/*"?",4*/

0x00,0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,0x00,
0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x7F,0x02,0x02,0x42,0x82,0x7F,0x00,0x00,0x00,/*"?",5*/

0x10,0x8C,0x44,0x04,0xE4,0x04,0x95,0xA6,0x44,0x24,0x14,0x84,0x44,0x94,0x0C,0x00,
0x02,0x02,0x7A,0x41,0x41,0x43,0x42,0x7E,0x42,0x42,0x42,0x43,0xF8,0x00,0x00,0x00,/*"?",6*/

0x04,0x84,0xE4,0x5C,0x44,0xC4,0x00,0x02,0xF2,0x82,0x82,0x82,0xFE,0x80,0x80,0x00,
0x02,0x01,0x7F,0x10,0x10,0x3F,0x00,0x08,0x08,0x08,0x08,0x48,0x88,0x40,0x3F,0x00,/*"?",7*/

0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0xE2,0x2C,0x20,0xBF,0x20,0x28,0xE6,0x00,0x00,
0x01,0x01,0x01,0x7F,0x21,0x11,0x80,0x4F,0x20,0x10,0x0F,0x10,0x20,0x4F,0x80,0x00,/*"?",8*/

0x40,0x42,0xCC,0x00,0x00,0x44,0x54,0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
0x00,0x00,0x7F,0x20,0x10,0x00,0xFF,0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,/*"?",9*/

0x88,0x68,0x1F,0xC8,0x08,0x10,0xC8,0x54,0x52,0xD1,0x12,0x94,0x08,0xD0,0x10,0x00,
0x09,0x19,0x09,0xFF,0x05,0x00,0xFF,0x12,0x92,0xFF,0x00,0x5F,0x80,0x7F,0x00,0x00,/*"?",10*/

0x00,0x00,0x00,0x00,0x00,0x01,0xE2,0x1C,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x03,0x0C,0x30,0x40,0x80,0x80,0x00,/*"?",11*/

0x10,0x8C,0x44,0x04,0xE4,0x04,0x95,0xA6,0x44,0x24,0x14,0x84,0x44,0x94,0x0C,0x00,
0x02,0x02,0x7A,0x41,0x41,0x43,0x42,0x7E,0x42,0x42,0x42,0x43,0xF8,0x00,0x00,0x00,/*"?",12*/

0x04,0x84,0xE4,0x5C,0x44,0xC4,0x00,0x02,0xF2,0x82,0x82,0x82,0xFE,0x80,0x80,0x00,
0x02,0x01,0x7F,0x10,0x10,0x3F,0x00,0x08,0x08,0x08,0x08,0x48,0x88,0x40,0x3F,0x00,/*"?",13*/

			
};
void SetPinData(unsigned char com)
{
	u8 i;
  for(i=0;i<8;i++)	
	{
		if(BIT_VALUE_GET(com,i))
		{
			GPIO_SetBits(PinType[i].GPIOX,PinType[i].GPIO_Pin);
		}else
		{
			GPIO_ResetBits(PinType[i].GPIOX,PinType[i].GPIO_Pin);
		}
	}	
}

/** LCM忙检测 **/
void busy12864(){
	SetPinData(0xff);  //口线置1，防止干扰
	RS=0;// rw=1;	   //置“命令、读”模式
	//en=1; while(lcdDat&0x80); en=0;//忙等待
}
/** 写命令 参数：comDat为要发送的命令 **/
void WriteCom(unsigned char comDat){  
		busy12864();     		//忙，则等待
		RS=0;//rw=0;				//置“命令、写”模式
		delay_us(5);
		SetPinData(comDat);
    EN=1;
		delay_us(5);
		EN=0;//送出命令，并使之有效
}
/** 写数据 参数：dat为要发送的数据 **/
void WriteDat(unsigned char dat){  
    busy12864();  		 	//忙，则等待	
		delay_us(5);
		RS=1;//rw=0;			  	//置“数据、写”模式
    SetPinData(dat);
		delay_us(5);
    EN=1;
		delay_us(5);
		EN=0;//送出命令，并使之有效
}


void Init12864(void)
{
	u8 i;
	GPIO_InitTypeDef GPIO_InitStructure;
	//不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	 RCC_APB2PeriphClockCmd(RCC_APB2_GPIOXX | RCC_APB2Periph_AFIO,ENABLE);		 
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  for(i=0;i<8;i++)
	
	{
	 GPIO_InitStructure.GPIO_Pin = PinType[i].GPIO_Pin;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(PinType[i].GPIOX, &GPIO_InitStructure);//初始化row
	 GPIO_SetBits(PinType[i].GPIOX,PinType[i].GPIO_Pin);
	}

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_7|GPIO_Pin_8 ;     //设置为开漏输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	SetPinData(0xff);
	RS=0;// rw=1;	   //置“命令、读”模式
	//en=1; while(lcdDat&0x10); en=0;//等待复位完成
	WriteCom(0x3f);	  //开显示
	WriteCom(addZ0);	  //设置显示起始行	
	
}


/******** 任意尺寸点阵显示函数 ***********|
|参数：显示位置：row页数，col列号，		  |
|	   字符大小：x横向像素，y纵向页数	  |
|	   显示内容：tab字模表          ******/
void showXY(unsigned char row,unsigned char col,unsigned char x,unsigned char y,unsigned char *tab){
	unsigned char i,j;
	unsigned char right;
	if(col<64){right=0;} //置左右屏标志
	else {col-=64;right=1;}	
	for(i=0;i<y;i++){
		if(right)cs2=0,cs1=1;
		else  cs2=1,cs1=0;
		WriteCom(addX0+row+i); //行
		WriteCom(addY0+col);   //列
		for(j=0;j<x;j++){
			if(col+j<64)WriteDat(tab[i*x+j]); //未跨屏
			else if(right==0){		  //从左屏跨右屏
				 cs2=0,cs1=1;		  //选中右屏
				 WriteCom(addX0+row+i);	   //设置行
				 WriteCom(addY0+(col+j-64));
				 WriteDat(tab[i*x+j]);
			}						 //在右屏越界不显示
		}
	}
}

/* 返回一个8*16字符索引位置 */					
unsigned char enN(unsigned char *s){
	unsigned char i;
	for(i=0;zm8x16_index[i]!=0;i++)if(zm8x16_index[i]==s[0])break;
	return i;	
}
/* 返回一个16*16字符索引位置 */
unsigned char cnN(unsigned char *s){
	unsigned char i;
	for(i=0;zm16x16_index[i]!=0;i+=2)
		if(zm16x16_index[i]==*s&&zm16x16_index[i+1]==*(s+1))break ;
	return i/2;
}
/* 显示中英文字符串 */
void showStr(unsigned char row,unsigned char col,unsigned char *s){
	 unsigned char i;
	 for(i=0;s[i]!=0;i++){
	 	if(s[i]<0x80){ 	//英文
			showXY(row,col,8,2,zm8x16_Table[enN(&s[i])]);
			col+=8;
		}else{			
			showXY(row,col,16,2,zm16x16_Table[cnN(&s[i])]);	
			col+=16;i+=1;		
		}
		if(col>120){	 //换行处理
			col=0;
			row+=2;
		}
	 }
}
/* 显示数字 */
void showNum(unsigned char row,unsigned char col,unsigned char s){
	showXY(row,col,8,2,zm8x16_Table[s]);
}
void showThreeNum(unsigned char row,unsigned char col,unsigned int s)
{
	showNum(row,col,s/100%10);
	showNum(row,col+8,s/10%10);
	showNum(row,col+16,s%10);
}
void Ds13b02_DisPlay_12864(unsigned char row,unsigned char col,unsigned char shi,unsigned char fen,unsigned char miao)
{

	showNum(row,col,shi%100/10);		// 十位
	showNum(row,col+8,shi%10);				// 个位
	showStr(row,col+8*2,(u8*)":");
	showNum(row,col+8*3,fen%100/10);		// 十位
	showNum(row,col+8*4,fen%10);				// 个位
	showStr(row,col+8*5,(u8*)":");
	showNum(row,col+8*6,miao%100/10);		// 十位
	showNum(row,col+8*7,miao%10);				// 个位

}
#endif


#if CONFIG_GPS_EX== ENABLED

unsigned char  rev_start = 0;     //接收开始标志
unsigned char  rev_stop  = 0;     //接收停止标志
#include <string.h>
unsigned char  num = 0;           //
unsigned char  gps_flag = 0;      //GPS处理标志
char   rev_buf[80];        //接收缓存
void GPS_uart_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void GPS_Init_Demo(void)
{
	GPS_uart_init_Demo(9600);
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 ch;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		ch =USART_ReceiveData(USART1);	//读取接收到的数据
		if ((ch == '$') && (gps_flag == 0))  //如果收到字符'$'，便开始接收
		{
			rev_start = 1;
			rev_stop  = 0;
		}
	
		if (rev_start == 1)  //标志位为1，开始接收
		{
			rev_buf[num++] = ch;  //字符存到数组中
			if (ch == '\n')     //如果接收到换行
			{
				rev_buf[num] = '\0';
				rev_start = 0;
				rev_stop  = 1;
				gps_flag = 1;
				num = 0;
			}
		}	

	} 

}

static unsigned char GetComma(unsigned char num,char *str)
{
	unsigned char i,j = 0;
	int len=strlen(str);

	for(i = 0;i < len;i ++)
	{
		if(str[i] == ',')
			j++;
		if(j == num)
			return i + 1;	
	}

	return 0;	
}


static float Str_To_Float(char *buf)
{
	float rev = 0;
	float dat;
	int integer = 1;
	char *str = buf;
	int i;
	while(*str != '\0')
	{
		switch(*str)
		{
			case '0':
				dat = 0;
				break;
			case '1':
				dat = 1;
				break;
			case '2':
				dat = 2;
				break;		
			case '3':
				dat = 3;
				break;
			case '4':
				dat = 4;
				break;
			case '5':
				dat = 5;
				break;
			case '6':
				dat = 6;
				break;
			case '7':
				dat = 7;
				break;
			case '8':
				dat = 8;
				break;
			case '9':
				dat = 9;
				break;
			case '.':
				dat = '.';
				break;
		}
		if(dat == '.')
		{
			integer = 0;
			i = 1;
			str ++;
			continue;
		}
		if( integer == 1 )
		{
			rev = rev * 10 + dat;
		}
		else
		{
			rev = rev + dat / (10 * i);
			i = i * 10 ;
		}
		str ++;
	}
	return rev;

}
												

float Get_Float_Number(char *s)
{
	char  buf[10];
	unsigned char i;
	float rev;
	i=GetComma(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	rev=Str_To_Float(buf);
	return rev;	
}

 double Str_To_Double(char *buf)
{
	double rev = 0;
	double dat;
	int integer = 1;
	char *str = buf;
	int i;
	while(*str != '\0')
	{
		switch(*str)
		{
			case '0':
				dat = 0;
				break;
			case '1':
				dat = 1;
				break;
			case '2':
				dat = 2;
				break;		
			case '3':
				dat = 3;
				break;
			case '4':
				dat = 4;
				break;
			case '5':
				dat = 5;
				break;
			case '6':
				dat = 6;
				break;
			case '7':
				dat = 7;
				break;
			case '8':
				dat = 8;
				break;
			case '9':
				dat = 9;
				break;
			case '.':
				dat = '.';
				break;
		}
		if(dat == '.')
		{
			integer = 0;
			i = 1;
			str ++;
			continue;
		}
		if( integer == 1 )
		{
			rev = rev * 10 + dat;
		}
		else
		{
			rev = rev + dat / (10 * i);
			i = i * 10 ;
		}
		str ++;
	}
	return rev;
}
												

static double Get_Double_Number(char *s)
{
	char  buf[10];
	unsigned char i;
	double rev;
	i=GetComma(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	rev=Str_To_Double(buf);
	return rev;	
}





 void UTC2BTC(DATE_TIME *GPS)
{
	GPS->second ++;  
	if(GPS->second > 59)
	{
		GPS->second = 0;
		GPS->minute ++;
		if(GPS->minute > 59)
		{
			GPS->minute = 0;
			GPS->hour ++;
		}
	}	

    GPS->hour = GPS->hour + 8;
	if(GPS->hour > 23)
	{
		GPS->hour -= 24;
		GPS->day += 1;
		if(GPS->month == 2 ||
		   		GPS->month == 4 ||
		   		GPS->month == 6 ||
		   		GPS->month == 9 ||
		   		GPS->month == 11 )
		{
			if(GPS->day > 30)
			{
		   		GPS->day = 1;
				GPS->month++;
			}
		}
		else
		{
			if(GPS->day > 31)
			{	
		   		GPS->day = 1;
				GPS->month ++;
			}
		}
		if(GPS->year % 4 == 0 )
		{
	   		if(GPS->day > 29 && GPS->month == 2)
			{		
	   			GPS->day = 1;
				GPS->month ++;
			}
		}
		else
		{
	   		if(GPS->day > 28 &&GPS->month == 2)
			{
	   			GPS->day = 1;
				GPS->month ++;
			}
		}
		if(GPS->month > 12)
		{
			GPS->month -= 12;
			GPS->year ++;
		}		
	}
}

void Int_To_Str(int x,char *Str)
{
	int t;
	char *Ptr,Buf[5];
	int i = 0;
	Ptr = Str;
	if(x < 10)		// 当整数小于10时,转化为"0x"的格式
	{
		*Ptr ++ = '0';
		*Ptr ++ = x+0x30;
	}
	else
	{
		while(x > 0)
		{
			t = x % 10;
			x = x / 10;
			Buf[i++] = t+0x30;	// 通过计算把数字转化成ASCII码形式
		}
		i -- ;
		for(;i >= 0;i --) 		// 将得到的字符串倒序
		{
			*(Ptr++) = Buf[i];
		}
	}
	*Ptr = '\0';
}
//$GPGGA,043006.00,2244.5931794,N,11432.9395981,E,15,19,0.4,16.6771,M,-1.530,M,18.0,0000*5E
int GPS_GGA_Parse(char *line,GPS_INFO *GPS)
{
	unsigned char ch, status;
	char *buf = line;
	ch = buf[4];
	status = buf[GetComma(2, buf)];

	if (ch == 'G')  //$GPGGA
	{
		if (status != ',')
		{
			GPS->longitude  = Get_Double_Number(&buf[GetComma(2, buf)]);
			GPS->latitude  = Get_Double_Number(&buf[GetComma( 4, buf)]);
			GPS->speed=Get_Double_Number(&buf[GetComma(6, buf)]);      
			GPS->direction=Get_Double_Number(&buf[GetComma(7, buf)]); 
			return 1;
		}
	}
	
	return 0;
}
#endif

#if CONFIG_AS608_EX== ENABLED
#include <string.h>
u32 AS608Addr = 0XFFFFFFFF; //默认
vu16 USART3_RX_STA;
#define USART3_MAX_RECV_LEN		400					//最大接收缓存字节数
#define USART3_MAX_SEND_LEN		400					//最大发送缓存字节数
#define USART3_RX_EN 			1					//0,不接收;1,接收.
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}
//定时器7中断服务程序		    
void TIM2_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		USART3_RX_STA|=1<<15;	//标记接收完成
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIM7更新中断标志    
		TIM_Cmd(TIM2, DISABLE);  //关闭TIM7 
	}	    
}

void USART3_Init_Config(u32 bound)
{
	
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//  
	USART_DeInit(USART2);  
	//重新定义管脚
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	//USART2_TX    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // 引脚不能更改
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 
   
  //USART2_RX	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化   

  //Usart NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3 原3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3     原2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2	
	USART_ClearFlag(USART2, USART_FLAG_TC);					//清除发送完成标?
	
	TIM2_Int_Init(99,7199);		//10ms中断
	USART3_RX_STA=0;		//清零
	TIM_Cmd(TIM2,DISABLE);			//关闭定时器2
}


void USART2_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART2);		 
		if((USART3_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
		{ 
			if(USART3_RX_STA<USART3_MAX_RECV_LEN)	//还可以接收数据
			{
				TIM_SetCounter(TIM2,0);//计数器清空          				//计数器清空
				if(USART3_RX_STA==0) 				//使能定时器7的中断 
				{
					TIM_Cmd(TIM2,ENABLE);//使能定时器7
				}
				USART3_RX_BUF[USART3_RX_STA++]=res;	//记录接收到的值	 
			}else 
			{
				USART3_RX_STA|=1<<15;				//强制标记接收完成
			} 
		}
	}  				 											 
}
void As608_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART3_Init_Config(9600);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA6	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15		
}	
void keyWait(void)
{
	u8 keyFlag=1;	
	while(keyFlag)
	{
		if(AS608_KEY==0)
		{
			delay_ms(5);//去抖动
			if(AS608_KEY==0)
			{
				keyFlag=0;
				break;
			}
		}
		delay_ms(100);
	}
}
static void MYUSART_SendData(u8 data)
{
  while((USART2->SR & 0X40) == 0);
  USART2->DR = data;
}
//发送包头
static void SendHead(void)
{
  MYUSART_SendData(0xEF);
  MYUSART_SendData(0x01);
}
//发送地址
static void SendAddr(void)
{
  MYUSART_SendData(AS608Addr >> 24);
  MYUSART_SendData(AS608Addr >> 16);
  MYUSART_SendData(AS608Addr >> 8);
  MYUSART_SendData(AS608Addr);
}
//发送包标识,
static void SendFlag(u8 flag)
{
  MYUSART_SendData(flag);
}
//发送包长度
static void SendLength(int length)
{
  MYUSART_SendData(length >> 8);
  MYUSART_SendData(length);
}
//发送指令码
static void Sendcmd(u8 cmd)
{
  MYUSART_SendData(cmd);
}
//发送校验和
static void SendCheck(u16 check)
{
  MYUSART_SendData(check >> 8);
  MYUSART_SendData(check);
}
//判断中断接收的数组有没有应答包
//waittime为等待中断接收数据的时间（单位1ms）
//返回值：数据包首地址
static u8 *JudgeStr(u16 waittime)
{
  char *data;
  u8 str[8];
  str[0] = 0xef;
  str[1] = 0x01;
  str[2] = AS608Addr >> 24;
  str[3] = AS608Addr >> 16;
  str[4] = AS608Addr >> 8;
  str[5] = AS608Addr;
  str[6] = 0x07;
  str[7] = '\0';
  USART3_RX_STA = 0;
  while(--waittime)
  {
    delay_ms(1);
    if(USART3_RX_STA & 0X8000) //接收到一次数据
    {
      USART3_RX_STA = 0;
      data = strstr((const char*)USART3_RX_BUF, (const char*)str);
      if(data)
        return (u8*)data;
    }
  }
  return 0;
}
//录入图像 PS_GetImage
//功能:探测手指，探测到后录入指纹图像存于ImageBuffer。
//模块返回确认字
u8 PS_GetImage(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x03);
  Sendcmd(0x01);
  temp =  0x01 + 0x03 + 0x01;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//生成特征 PS_GenChar
//功能:将ImageBuffer中的原始图像生成指纹特征文件存于CharBuffer1或CharBuffer2
//参数:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//模块返回确认字
u8 PS_GenChar(u8 BufferID)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x04);
  Sendcmd(0x02);
  MYUSART_SendData(BufferID);
  temp = 0x01 + 0x04 + 0x02 + BufferID;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//精确比对两枚指纹特征 PS_Match
//功能:精确比对CharBuffer1 与CharBuffer2 中的特征文件
//模块返回确认字
u8 PS_Match(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x03);
  Sendcmd(0x03);
  temp = 0x01 + 0x03 + 0x03;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//搜索指纹 PS_Search
//功能:以CharBuffer1或CharBuffer2中的特征文件搜索整个或部分指纹库.若搜索到，则返回页码。
//参数:  BufferID @ref CharBuffer1	CharBuffer2
//说明:  模块返回确认字，页码（相配指纹模板）
u8 PS_Search(u8 BufferID, u16 StartPage, u16 PageNum, SearchResult *p)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x08);
  Sendcmd(0x04);
  MYUSART_SendData(BufferID);
  MYUSART_SendData(StartPage >> 8);
  MYUSART_SendData(StartPage);
  MYUSART_SendData(PageNum >> 8);
  MYUSART_SendData(PageNum);
  temp = 0x01 + 0x08 + 0x04 + BufferID
         + (StartPage >> 8) + (u8)StartPage
         + (PageNum >> 8) + (u8)PageNum;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[9];
    p->pageID   = (data[10] << 8) + data[11];
    p->mathscore = (data[12] << 8) + data[13];
  }
  else
    ensure = 0xff;
  return ensure;
}

u8 PS_Enroll(SearchResult *p)
{
	u8  *data;
	u16 temp;
	u8  ensure;
  SendHead();
  SendAddr();	
  SendFlag(0x01);//命令包标识	
  SendLength(0x03);	
  Sendcmd(0x10);
  temp = 0x01 + 0x03 + 0x10;
  SendCheck(temp);	
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[9];
    p->pageID 	= (data[10] << 8) + data[11];
  }
  else
    ensure = 0xff;
  return ensure;	
	
}
u8 PS_Identify(SearchResult *p)
{
	u8  *data;
	u16 temp;
	u8  ensure;
  SendHead();
  SendAddr();	
  SendFlag(0x01);//命令包标识	
  SendLength(0x03);	
  Sendcmd(0x11);
  temp = 0x01 + 0x03 + 0x11;
  SendCheck(temp);	
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[9];
    p->pageID 	= (data[10] << 8) + data[11];
  }
  else
    ensure = 0xff;
  return ensure;	
	
}
//合并特征（生成模板）PS_RegModel
//功能:将CharBuffer1与CharBuffer2中的特征文件合并生成 模板,结果存于CharBuffer1与CharBuffer2
//说明:  模块返回确认字
u8 PS_RegModel(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x03);
  Sendcmd(0x05);
  temp = 0x01 + 0x03 + 0x05;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//储存模板 PS_StoreChar
//功能:将 CharBuffer1 或 CharBuffer2 中的模板文件存到 PageID 号flash数据库位置。
//参数:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID（指纹库位置号）
//说明:  模块返回确认字
u8 PS_StoreChar(u8 BufferID, u16 PageID)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x06);
  Sendcmd(0x06);
  MYUSART_SendData(BufferID);
  MYUSART_SendData(PageID >> 8);
  MYUSART_SendData(PageID);
  temp = 0x01 + 0x06 + 0x06 + BufferID
         + (PageID >> 8) + (u8)PageID;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//删除模板 PS_DeletChar
//功能:  删除flash数据库中指定ID号开始的N个指纹模板
//参数:  PageID(指纹库模板号)，N删除的模板个数。
//说明:  模块返回确认字
u8 PS_DeletChar(u16 PageID, u16 N)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x07);
  Sendcmd(0x0C);
  MYUSART_SendData(PageID >> 8);
  MYUSART_SendData(PageID);
  MYUSART_SendData(N >> 8);
  MYUSART_SendData(N);
  temp = 0x01 + 0x07 + 0x0C
         + (PageID >> 8) + (u8)PageID
         + (N >> 8) + (u8)N;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//清空指纹库 PS_Empty
//功能:  删除flash数据库中所有指纹模板
//参数:  无
//说明:  模块返回确认字
u8 PS_Empty(void)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x03);
  Sendcmd(0x0D);
  temp = 0x01 + 0x03 + 0x0D;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//写系统寄存器 PS_WriteReg
//功能:  写模块寄存器
//参数:  寄存器序号RegNum:4\5\6
//说明:  模块返回确认字
u8 PS_WriteReg(u8 RegNum, u8 DATA)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x05);
  Sendcmd(0x0E);
  MYUSART_SendData(RegNum);
  MYUSART_SendData(DATA);
  temp = RegNum + DATA + 0x01 + 0x05 + 0x0E;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
//  if(ensure == 0)
//    printf("\r\n设置参数成功！");
//  else
//    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//读系统基本参数 PS_ReadSysPara
//功能:  读取模块的基本参数（波特率，包大小等)
//参数:  无
//说明:  模块返回确认字 + 基本参数（16bytes）
u8 PS_ReadSysPara(SysPara *p)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x03);
  Sendcmd(0x0F);
  temp = 0x01 + 0x03 + 0x0F;
  SendCheck(temp);
  data = JudgeStr(1000);
  if(data)
  {
    ensure = data[9];
    p->PS_max = (data[14] << 8) + data[15];
    p->PS_level = data[17];
    p->PS_addr = (data[18] << 24) + (data[19] << 16) + (data[20] << 8) + data[21];
    p->PS_size = data[23];
    p->PS_N = data[25];
  }
  else
    ensure = 0xff;
//  if(ensure == 0x00)
//  {
//    printf("\r\n模块最大指纹容量=%d", p->PS_max);
//    printf("\r\n对比等级=%d", p->PS_level);
//    printf("\r\n地址=%x", p->PS_addr);
//    printf("\r\n波特率=%d", p->PS_N * 9600);
//  }
//  else
//    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//设置模块地址 PS_SetAddr
//功能:  设置模块地址
//参数:  PS_addr
//说明:  模块返回确认字
u8 PS_SetAddr(u32 PS_addr)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x07);
  Sendcmd(0x15);
  MYUSART_SendData(PS_addr >> 24);
  MYUSART_SendData(PS_addr >> 16);
  MYUSART_SendData(PS_addr >> 8);
  MYUSART_SendData(PS_addr);
  temp = 0x01 + 0x07 + 0x15
         + (u8)(PS_addr >> 24) + (u8)(PS_addr >> 16)
         + (u8)(PS_addr >> 8) + (u8)PS_addr;
  SendCheck(temp);
  AS608Addr = PS_addr; //发送完指令，更换地址
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  AS608Addr = PS_addr;
//  if(ensure == 0x00)
//    printf("\r\n设置地址成功！");
//  else
//    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//功能： 模块内部为用户开辟了256bytes的FLASH空间用于存用户记事本,
//	该记事本逻辑上被分成 16 个页。
//参数:  NotePageNum(0~15),Byte32(要写入内容，32个字节)
//说明:  模块返回确认字
u8 PS_WriteNotepad(u8 NotePageNum, u8 *Byte32)
{
  u16 temp;
  u8  ensure, i;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(36);
  Sendcmd(0x18);
  MYUSART_SendData(NotePageNum);
  for(i = 0; i < 32; i++)
  {
    MYUSART_SendData(Byte32[i]);
    temp += Byte32[i];
  }
  temp = 0x01 + 36 + 0x18 + NotePageNum + temp;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
    ensure = data[9];
  else
    ensure = 0xff;
  return ensure;
}
//读记事PS_ReadNotepad
//功能：  读取FLASH用户区的128bytes数据
//参数:  NotePageNum(0~15)
//说明:  模块返回确认字+用户信息
u8 PS_ReadNotepad(u8 NotePageNum, u8 *Byte32)
{
  u16 temp;
  u8  ensure, i;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x04);
  Sendcmd(0x19);
  MYUSART_SendData(NotePageNum);
  temp = 0x01 + 0x04 + 0x19 + NotePageNum;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[9];
    for(i = 0; i < 32; i++)
    {
      Byte32[i] = data[10 + i];
    }
  }
  else
    ensure = 0xff;
  return ensure;
}
//高速搜索PS_HighSpeedSearch
//功能：以 CharBuffer1或CharBuffer2中的特征文件高速搜索整个或部分指纹库。
//		  若搜索到，则返回页码,该指令对于的确存在于指纹库中 ，且登录时质量
//		  很好的指纹，会很快给出搜索结果。
//参数:  BufferID， StartPage(起始页)，PageNum（页数）
//说明:  模块返回确认字+页码（相配指纹模板）
u8 PS_HighSpeedSearch(u8 BufferID, u16 StartPage, u16 PageNum, SearchResult *p)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x08);
  Sendcmd(0x1b);
  MYUSART_SendData(BufferID);
  MYUSART_SendData(StartPage >> 8);
  MYUSART_SendData(StartPage);
  MYUSART_SendData(PageNum >> 8);
  MYUSART_SendData(PageNum);
  temp = 0x01 + 0x08 + 0x1b + BufferID
         + (StartPage >> 8) + (u8)StartPage
         + (PageNum >> 8) + (u8)PageNum;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[9];
    p->pageID 	= (data[10] << 8) + data[11];
    p->mathscore = (data[12] << 8) + data[13];
  }
  else
    ensure = 0xff;
  return ensure;
}
//读有效模板个数 PS_ValidTempleteNum
//功能：读有效模板个数
//参数: 无
//说明: 模块返回确认字+有效模板个数ValidN
u8 PS_ValidTempleteNum(u16 *ValidN)
{
  u16 temp;
  u8  ensure;
  u8  *data;
  SendHead();
  SendAddr();
  SendFlag(0x01);//命令包标识
  SendLength(0x03);
  Sendcmd(0x1d);
  temp = 0x01 + 0x03 + 0x1d;
  SendCheck(temp);
  data = JudgeStr(2000);
  if(data)
  {
    ensure = data[9];
    *ValidN = (data[10] << 8) + data[11];
  }
  else
    ensure = 0xff;

//  if(ensure == 0x00)
//  {
//    printf("\r\n有效指纹个数=%d", (data[10] << 8) + data[11]);
//  }
//  else
//    printf("\r\n%s", EnsureMessage(ensure));
  return ensure;
}
//与AS608握手 PS_HandShake
//参数: PS_Addr地址指针
//说明: 模块返新地址（正确地址）
u8 PS_HandShake(u32 *PS_Addr)
{
  SendHead();
  SendAddr();
  MYUSART_SendData(0X01);
  MYUSART_SendData(0X00);
  MYUSART_SendData(0X00);
  delay_ms(200);
  if(USART3_RX_STA & 0X8000) //接收到数据
  {
    if(//判断是不是模块返回的应答包
      USART3_RX_BUF[0] == 0XEF
      && USART3_RX_BUF[1] == 0X01
      && USART3_RX_BUF[6] == 0X07
    )
    {
      *PS_Addr = (USART3_RX_BUF[2] << 24) + (USART3_RX_BUF[3] << 16)
                 + (USART3_RX_BUF[4] << 8) + (USART3_RX_BUF[5]);
      USART3_RX_STA = 0;
      return 0;
    }
    USART3_RX_STA = 0;
  }
  return 1;
}
#endif


#if CONFIG_TVOC== ENABLED
#include <string.h>
#include <stdio.h>
u8 a1;
u8 buffx[10];
int voc=0;
void usart1_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}


void usart1_SendByte_Demo(unsigned char a)
{

	USART_SendData(USART1,a); //开始发送
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	USART_ClearFlag(USART1,USART_FLAG_TXE);
}


void usart1_SendString_Demo(unsigned char *Index)
{

	while(*Index)//检测字符串结束符
	{
		usart1_SendByte_Demo(*Index++);//发送当前字符
	}

}



void USART1_Send_Data_Demo(unsigned char *Data,unsigned short Length)
{

	unsigned short i;


	for(i=0;i<Length;i++)
	{
		/* Place your implementation of fputc here */
		/* e.g. write a character to the USART */
		USART_SendData(USART1, *Data++);
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{}
	}

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	
	static u8 index=0;
	static u8 starFlag=0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		a1 =USART_ReceiveData(USART1);	//读取接收到的数据

		if(starFlag==0)
		{
			if(a1 == 0x5f)
			{
				starFlag=1;
				index=0;
				memset(buffx,0,sizeof(buffx));
				buffx[index++]=a1;
			}			
		}else
		{
				buffx[index++]=a1;
				if(index == 8)
				{
					voc = (buffx[1]<<8)+buffx[2];
					starFlag=0;
					index=0;
					memset(buffx,0,sizeof(buffx));
				}
		}
		
	} 

}
void TvocInit(void)
{
	usart1_init_Demo(9600);
}
#endif


#if CONFIG_PID== ENABLED

#include <string.h>
struct PID { 
unsigned int SetPoint; // 设定目标 Desired Value 
unsigned int Proportion; // 比例常数 Proportional Const 
unsigned int Integral; // 积分常数 Integral Const 
unsigned int Derivative; // 微分常数 Derivative Const 
unsigned int LastError; // Error[-1] 
unsigned int PrevError; // Error[-2] 
unsigned int SumError; // Sums of Errors 
}; 
struct PID spid; // PID Control Structure 
unsigned int rout; // PID Response (Output) 响应输出
unsigned int rin; // PID Feedback (Input)//反馈输入
unsigned char high_time,low_time,count=0;//占空比调节参数 
short iRTemp;
int set_temper=30,temper,temp; //温度变量定义
unsigned int s;
#define output PAout(5)
void PIDInit (struct PID *pp) 
{ 
	memset ( pp,0,sizeof(struct PID)); //用参数0初始化pp
} 



unsigned int PIDCalc( struct PID *pp, unsigned int NextPoint ) //PID计算
{ 
	unsigned int dError,Error; 
	Error = pp->SetPoint - NextPoint; // 偏差 
	pp->SumError += Error; // 积分 
	dError = pp->LastError - pp->PrevError; // 当前微分 
	pp->PrevError = pp->LastError; 
	pp->LastError = Error; 
	return (pp->Proportion * Error//比例
	+ pp->Integral * pp->SumError  //积分项
	+ pp->Derivative * dError); //   微分项 
}

void Tim2_Handle_Process_func()
{
	if(++count<=(high_time)) 	output=0;
	else if(count<=100) 
	{ 
		output=1; 
	} 
	else count=0; 
}
void pid_all_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		//做输出
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC	
	high_time=50; 
	low_time=50; 
	PIDInit ( &spid ); // Initialize Structure 
	spid.Proportion= 10; // Set PID Coefficients 
	spid.Integral = 8; 
	spid.Derivative =6; 
	spid.SetPoint =100; // Set PID Setpoint 	
}
void setcomparevalue(int temp,int set)
{
	iRTemp=temp;
	set_temper=set;
}	
/*********************************************************** 
温度比较处理子程序 
***********************************************************/ 
void compare_temper(void) 
{ 
	unsigned char i; 
	if(set_temper>temper) 	//设置温度大于当前温度
	{ 

		if(set_temper-temper>1) 	//温度相差1度以上
		{	 
			high_time=100; 
			low_time=0;
		} 
		else 	//设置温度不大于当前温度
		{ 
			for(i=0;i<10;i++) 
			{ 

				//get_temper();
			
				rin = s; // Read Input 
				rout = PIDCalc ( &spid,rin ); // Perform PID Interation 
			} 
			if (high_time<=100) 	high_time=(unsigned char)(rout/800); 
			else	high_time=100; 
			low_time= (100-high_time); 
		} 
	} 
	else if(set_temper<=temper) 	//设置温度不大于当前温度
	{ 

		if(temper-set_temper>0) //温度相差0度以上
		{ 
			high_time=0; 
			low_time=100; 
		} 
		else 
		{ 
			for(i=0;i<10;i++) 
			{ 

				//get_temper(); 

				rin = s; // Read Input 
				rout = PIDCalc ( &spid,rin ); // Perform PID Interation 
			} 
			if (high_time<100) high_time=(unsigned char)(rout/10000); 
			else 	high_time=0; 
			low_time= (100-high_time); 
		}
		
 
	}
	
}
#endif

#if CONFIG_MAX30102EX== ENABLED

#include "MAX30102.h"  //心率
#include "algorithm.h"
#include "blood.h"
#include "iic.h"
#include <stdio.h>
BloodData g_blooddata = {0};					//血液数据存储

void max30102_init()
{
	int i=0;
	IIC_GPIO_INIT();
	MAX30102_GPIO();
	Max30102_reset();
	MAX30102_Config();
	for(i = 0;i < 128;i++) 
	{
		while(MAX30102_INTPin_Read()==0)
		{
			//读取FIFO
			max30102_read_fifo();
		}
	}
}
void blood_Loop(void)
{
	unsigned char str[20]="";
	//血液信息获取
	blood_data_update();
	//血液信息转换
	blood_data_translate();
	//显示血液状态信息
	sprintf((char *)str,"SpO2:%2.1f%% ",g_blooddata.SpO2);
	if(str[5]=='n')
	{
		g_blooddata.heart=0;
		g_blooddata.SpO2=0;
		//OLED_ShowCH(0, 2, "---/min  --.-% ");
	}
	else
	{
		//OLED_ShowStr(0,2,str,16);
		g_blooddata.SpO2 = (g_blooddata.SpO2 > 99.99) ? 99.99:g_blooddata.SpO2;
	
	}

}
#endif

