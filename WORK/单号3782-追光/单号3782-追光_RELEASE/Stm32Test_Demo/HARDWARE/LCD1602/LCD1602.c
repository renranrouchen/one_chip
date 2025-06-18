#include "LCD1602.h"
#include "delay.h"
#include "sys.h"

u8 Dao_xu(u8 data)
{
    u8 i = 0 ,temp = 0;;
	  
	  for(i = 0; i < 8; i++)
	 {
	   temp += (((data >> i) & 0x01) << (7 - i));
	 }
	 return temp;
}

/*-----------------------------------------------
  ���ƣ�LCD1602
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ���
  ���ݣ�ͨ����׼����̬��ʾ�ַ�
  ���Ŷ������£�1-VSS 2-VDD 3-V0 4-RS 5-R/W 6-E 7-14 DB0-DB7 15-BLA 16-
              ��æ����
------------------------------------------------*/

/*------------------------------------------------
              д�������
------------------------------------------------*/
void LCD_PORT(unsigned char com)
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
 void LCD_Write_Com(unsigned char com) 
{

	delay_us(2500);
	RS =0;
	EN=0;	
	delay_us(5);
  EN=1;
  //delay_us(10);	
  LCD_PORT(com);

	delay_us(10);	
  EN=0;                   
	delay_us(400);	
	delay_ms(4);	
}

/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(unsigned char Data) 
{

  delay_us(2500);
  RS=1;
  delay_us(30);	
  EN=1;
  //RW=0;
  LCD_PORT(Data);
  delay_us(10);	
  EN=0;                  
	delay_us(400);	
	delay_ms(4);	
  	
}

void LCD1602_GPIO_Config(void)
{
	
	GPIO_InitTypeDef LCD1602_GPIOStruct;
	//����ȱ��PA13/14/15 & PB3/4Ĭ������ΪJTAG���ܣ���Ҫ��JTAG�ص�
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);	
	 
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8| GPIO_Pin_9 ;     //����Ϊ��©��� 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;//
	GPIO_Init(GPIOB,&LCD1602_GPIOStruct);
	
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15 ;     //����Ϊ��©��� 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;//GPIO_Speed_10MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA,&LCD1602_GPIOStruct);
	
	

	
	
}




void LCD1602_Init(void)
{
	  LCD1602_GPIO_Config();   //����GPIO��
    LCD_Write_Com(0X38);  //16*2��ʾ��5*7����8λ���ݽӿ�
    LCD_Write_Com(0x0C);  //��ʾ���������ر�
    LCD_Write_Com(0x06);  //���ֲ�������ַ�Զ�+1
    LCD_Write_Com(0x01);  //����
	 // LCD1602_WriteCmd(0x0f);  //��ʾ���������ر�
	
}

/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
 {     
 if (y == 0) 
 	{     
	 LCD_Write_Com(0x80 + x);     
 	}
 else 
 	{     
 	LCD_Write_Com(0xC0 + x);     
 	}        
 while (*s) 
 	{     
 LCD_Write_Data( *s);     
 s ++;     
 	}
 }
/*------------------------------------------------
              д���ַ�����
------------------------------------------------*/
 void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
 {     
 if (y == 0) 
 	{     
 	LCD_Write_Com(0x80 + x);     
 	}    
 else 
 	{     
 	LCD_Write_Com(0xC0 + x);     
 	}        
 LCD_Write_Data( Data);  
 }
 
 
 void LCD1602_write_long(unsigned char x,unsigned char y,u32 data,unsigned char num) 
{
    unsigned char temp[12],i = 12;
    while(i--)
    {
         temp[i] = ' ';
    }
    temp[num] = '\0';
    while(num--)
    {
      if(data || data%10)
         temp[num] = data % 10 + 0x30;
      data = data/10;
    }
   LCD_Write_String(x,y,temp);   
}
void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com(0x80+add);
	else
		LCD_Write_Com(0x80+0x40+add);
	LCD_Write_Data(0x30+date/10%10);
	LCD_Write_Data(0x30+date%10);	
}
void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com(0x80+add);
	else
		LCD_Write_Com(0x80+0x40+add);
	LCD_Write_Data(0x30+date/100%10);
	LCD_Write_Data(0x30+date/10%10);
	LCD_Write_Data(0x30+date%10);	
}
void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p)
{
	if(hang==0)   
		LCD_Write_Com(0x80+add);
	else
		LCD_Write_Com(0x80+0x40+add);
		while(1)
		{
			if(*p == '\0')  break;
			LCD_Write_Data(*p);
			p++;
		}	
}

/*****************���ƹ�꺯��********************/
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date)
{		
	if(hang==0)   
		LCD_Write_Com(0x80+add);
	else
		LCD_Write_Com(0x80+0x40+add);
	if(date == 1)
		LCD_Write_Com(0x0f);     //��ʾ��겢����˸	
	else 
		LCD_Write_Com(0x0c);   //�رչ��
}

 /*------------------------------------------------
                ��������
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 delay_ms(5);
 }

/*------------------------------------------------*/
 
// D0  D1 D2 D3 D4 D5 D6 D7 E   RW RS
// A15 B3 B4 B5 B6 B7 B8 B9 A12    A11

   
