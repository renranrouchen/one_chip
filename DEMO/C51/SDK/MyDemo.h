#ifndef _MYDEMO_H_
#define _MYDEMO_H_
#include <reg52.h>
#include "MyConfig.h"

#define TRUE 1
#define FALSE 0

#if CONFIG_UTRL == ENABLED
#define uchar unsigned char		 
#define uint unsigned int
void DelayMs_utrl(unsigned int time);
#endif

#if CONFIG_LCD1602 == ENABLED

/****ÐÞ¸ÄµÄµã*****
***Ì×ÓÃ±ðµÄ1602µÄcom¼°data£¬Ö»ÐèÒª°ÑLcd1602_write_com¼°Lcd1602_write_dataÌæ»»³É¶ÔÓ¦
***ÒªÓÃÕâÌ×1602£¬Ö»ÐèÒªÐÞ¸ÄÏàÓ¦µÄÒý½Å
***/
#define Lcd1602_Demo_write_com Lcd1602_write_com
#define Lcd1602_Demo_write_data Lcd1602_write_data

sbit Lcd1602_rs=P2^5;	 //1602Êý¾Ý/ÃüÁîÑ¡ÔñÒý½Å H:Êý¾Ý      	L:ÃüÁî
sbit Lcd1602_rw=P2^6;	 //1602¶ÁÐ´Òý½Å	         H:Êý¾Ý¼Ä´æÆ÷  	L:Ö¸Áî¼Ä´æÆ÷
sbit Lcd1602_e =P2^7;	 //1602Ê¹ÄÜÒý½Å          ÏÂ½µÑØ´¥·¢


void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p);
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date);
void Lcd1602_Display_Init();
#if CONFIG_DS1302 == ENABLED
void Ds13b02_DisPlay_fen(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao);
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao);
#endif

#if CONFIG_DS18b02 == ENABLED
void Lcd1602_Display_Ds18b02(unsigned char hang,unsigned char add,unsigned int date);
#endif
/******LCD1602 Demo******
Lcd1602_Display_guanbiao(0,0,0);
Lcd1602_Display_String(0,0,"                ");
Lcd1602_Display_String(1,0,"                ");
void main()
{
	Lcd1602_Display_Init();
	Lcd1602_Display_String(0,0,"hello world");
	while(1);
}

*/
#endif


#if CONFIG_KEY == ENABLED

sbit Demo_KEY1 = P1^0;
sbit Demo_KEY2 = P1^1;
sbit Demo_KEY3 = P1^2;
sbit Demo_KEY4 = P1^3;
sbit Demo_KEY5 =  P3^6;
sbit Demo_KEY6 =  P3^7;
#define KEY_COUNT 3 //¶¨ÒåÐèÒª¼¸¸ö°´¼ü£¬×î¶à6¸ö
typedef void (*pKey_Process)(unsigned char );
void Key_value_Demo(pKey_Process key_Process);	
typedef void (*pFuc_Process)(unsigned char hang,unsigned char add,unsigned int date);
/******Key Demo******
if(Menu_Count==0)
Lcd1602_Display_guanbiao(0,0,0);
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //ÉèÖÃ¼ü
	{
		Menu_Count ++;

		if(Menu_Count >= 2)
		{
			//´¦Àí·µ»Ø½çÃæ
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}

	if(Key_value == 2)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}
	
	if(Key_value == 3)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}		
		
}

void main()
{
	
	while(1)
	{
		Key_value_Demo(Key_Process_Demo);
	}
}


	if(Key_value == 1)	 //ÉèÖÃ¼ü
	{
		Menu_Count ++;
		revbuff=0;
		if(Menu_Count >= 4)
		{
			Lcd1602_Display_String(0,0,"                ");
			Lcd1602_Display_String(1,0,"                ");		
			//´¦Àí·µ»Ø½çÃæ
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				Lcd1602_Display_String(0,0,"xxx Set         ");
				Lcd1602_Display_String(1,0,"                ");
				Lcd1602_Display_Three_bit(1,6,Ad_dat1_l);
				break;
			case 2:
				Lcd1602_Display_String(0,0,"xxx Set         ");
				Lcd1602_Display_String(1,0,"                ");
				Lcd1602_Display_Three_bit(1,6,Ad_dat2_l);				
				break;
			case 3:
				Lcd1602_Display_String(0,0,"xxx Set         ");
				Lcd1602_Display_String(1,0,"                ");
				Lcd1602_Display_Three_bit(1,6,Ad_dat3_l);
				break;			
			
		}
	}

	if(Key_value == 2)	 //
	{
		revbuff=0;		
		switch(Menu_Count)
		{
			case 1:
				Ad_dat1_l++;
				Lcd1602_Display_Three_bit(1,6,Ad_dat1_l);
				break;
			case 2:
				Ad_dat2_l++;
				Lcd1602_Display_Three_bit(1,6,Ad_dat2_l);				
				break;
			case 3:
				Ad_dat3_l++;
				Lcd1602_Display_Three_bit(1,6,Ad_dat3_l);
				break;
		}
	}
	
	if(Key_value == 3)	 //
	{
		revbuff=0;		
		switch(Menu_Count)
		{
			case 1:
				if(Ad_dat1_l>0)
				Ad_dat1_l--;
				Lcd1602_Display_Three_bit(1,6,Ad_dat1_l);
				break;
			case 2:
				if(Ad_dat2_l>0)
				Ad_dat2_l--;
				Lcd1602_Display_Three_bit(1,6,Ad_dat2_l);				
				break;
			case 3:
				if(Ad_dat3_l>0)
				Ad_dat3_l--;
				Lcd1602_Display_Three_bit(1,6,Ad_dat3_l);
				break;
		}
	}	
	
	
	
	
	
	
	============¡·¡·¡·¡·
#include "MyDemo.h"
#include <stdio.h>
#include <string.h>
unsigned char Menu_Count =0;
unsigned char ucDisplayFlag=1;
#define SETNUM 4
code unsigned char  SetDisplay[SETNUM][16]={
	"xx1 SET",
	"xx2 SET",
	"xx3 SET",
	"xx4 SET",
};
unsigned char SetDValue[SETNUM]={
  50,
	60,
	70,
};
pFuc_Process FucProcess[SETNUM]={
	Lcd1602_Display_Three_bit,
	Lcd1602_Display_Three_bit,
	Lcd1602_Display_Three_bit,
	Lcd1602_Display_Three_bit,
};
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //ÉèÖÃ¼ü
	{
		Menu_Count ++;

		if(Menu_Count >= SETNUM+1)
		{
			ucDisplayFlag=1;
			//´¦Àí·µ»Ø½çÃæ
			Menu_Count = 0;
			return;
		}
		if(Menu_Count>0)
		{

			Lcd1602_Display_String(0,0,"                ");
			Lcd1602_Display_String(1,0,"                ");						
			Lcd1602_Display_String(0,0,SetDisplay[Menu_Count-1]);
			FucProcess[Menu_Count-1](1,6,SetDValue[Menu_Count-1]);			
		}

	}

	if(Key_value == 2)	 //
	{
		if(Menu_Count>0)
		{
			SetDValue[Menu_Count-1]++;
			FucProcess[Menu_Count-1](1,6,SetDValue[Menu_Count-1]);			
		}
	}
	
	if(Key_value == 3)	 //
	{
		if(Menu_Count>0)
		{
			SetDValue[Menu_Count-1]--;
			FucProcess[Menu_Count-1](1,6,SetDValue[Menu_Count-1]);		
		}
	}		
		
}

void main()
{

	Lcd1602_Display_Init();
	while(1)
	{
		Key_value_Demo(Key_Process_Demo);
		if(Menu_Count==0)
		{
			if(ucDisplayFlag)
			{
				ucDisplayFlag=0;
				Lcd1602_Display_String(0,0,"                ");
				Lcd1602_Display_String(1,0,"                ");				
				//ÏÔÊ¾
			}

	
		}
		DelayMs_utrl(100);
	}
}
***/
#endif

#if CONFIG_ADC0832 == ENABLED

sbit ADCS = P2^0;	//adc0832 Ê±ÖÓÒý½Å¶¨Òå
sbit ADCLK =P2^1;
sbit ADDI = P2^2;	//adc0832  Êý¾ÝÒý½Å¶¨Òå
sbit ADDO = P2^2;	//adc0832  Æ¬Ñ¡Òý½Å¶¨Òå

unsigned char ADC0832_Demo(bit mode,bit channel); 

/******ADC0832 Demo******
Ad_dat2 = (256-Ad_dat2) * 100 / 256;//¶ÔÖµ·´Ïà		
unsigned char Ad_dat1_l=30;
unsigned char Ad_dat2_l=40;
unsigned char Ad_dat1=0;
unsigned char Ad_dat2=0;
void main()
{
	Lcd1602_Display_Init();
	
	Lcd1602_Display_String(0,0,"A:              ");
	Lcd1602_Display_String(1,0,"B:              ");
	while(1)
	{
		Ad_dat1 = ADC0832_Demo(1,0);//Í¨µÀ0 	
		Ad_dat2 = ADC0832_Demo(1,1);//Í¨µÀ1 
		Ad_dat1 = Ad_dat1 * 100 / 256; //486¶ÔÓ¦µÄÎª·¶Î§
		Ad_dat2 = Ad_dat2 * 100 / 256;//¶ÔÖµ·´Ïà		
		Lcd1602_Display_Three_bit(0,2,Ad_dat1);
		Lcd1602_Display_Three_bit(1,2,Ad_dat2);
		DelayMs_utrl(100);
	}
}



//ÓêµÎÖµÊÇ·´µÄ
long value;

unsigned char cs;
unsigned int sum;
unsigned char Ad_dat=0;
void main()
{
	while(1)
	{
		//ÑÌÎídemo
		value = ADC0832_Demo(1,0);//Í¨µÀ0 	
		//value = ADC0832_Demo(1,1);//Í¨µÀ1 	
		//value = value * 486 / 256; //486¶ÔÓ¦µÄÎª·¶Î§
		value = (256-value) * 486 / 256;//¶ÔÖµ·´Ïà
		
		//Ë®Î»demo
		if(cs<10)		 		//
		{
			cs++;
			sum+=ADC0832_Demo(1,0);		
			DelayMs_utrl(10);	
		}
		else					//
		{
			cs=0;				//
			Ad_dat=(uchar)(sum/10);	
			if(Ad_dat>2)
				Ad_dat=(float)((Ad_dat-2)/2.4); //·¶Î§100 
			else
				Ad_dat=0;	
				
			sum=0;
			
		}
	}
}

*/
#endif

#if CONFIG_DS1302 == ENABLED

sbit clk = P2^4;	  //ds1302Ê±ÖÓÏß¶¨Òå
sbit io =  P2^5;	  //Êý¾ÝÏß
sbit rst = P2^3;	  //¸´Î»Ïß

#define WRITE_NIAN 0X8C
#define WRITE_YUE  0X88
#define WRITE_RI   0X86
#define WRITE_SHI  0X84
#define WRITE_FEN  0X82
#define WRITE_MIAO 0X80
void DelayMs_Ds1302(unsigned int time);
void Ds1302_Write_Demo(unsigned char add,unsigned char dat);
unsigned char Ds1302_Read_Demo(unsigned char add);
unsigned char BCD_Decimal(unsigned char bcd);
void Ds1302_Read_Time(unsigned char *arry);
void Ds1302_Write_Time(unsigned char *arry);
void Ds1302_Save(unsigned char  po, unsigned char  dat);
void Ds1302_Write_ram(unsigned char add,unsigned char dat);
unsigned char Ds1302_Read_ds1302ram(unsigned char add);
void Ds1302_Set_time(unsigned char num,unsigned char *shi,unsigned char dat);
void Ds1302_Init();

/******DS1302 Demo******

unsigned char Time_arry_o[3]={0,30,10};
unsigned char Time_arry_c[3]={0,31,10};

unsigned char Time_arry[7];

void main()
{
	while(1)
	{
		Ds1302_Read_Time(Time_arry);
		Ds13b02_DisPlay_Min(0,6,Time_arry[2],Time_arry[1],Time_arry[0]);	//Ê¹ÄÜ1602
		DelayMs_utrl(100);
		
		//ÄêÔÂÈÕ
		Ds1302_Save(WRITE_NIAN,Time_arry[5]);
		Ds1302_Save(WRITE_YUE,Time_arry[4]);
		Ds1302_Save(WRITE_RI,Time_arry[3]);	
		
		//ÉèÖÃÊ±ÔÂÃë
		//Ds1302_Save(WRITE_SHI,arry[2]);
		//Ds1302_Save(WRITE_FEN,arry[1]);
		//Ds1302_Save(WRITE_MIAO,arry[0]);	
	}
}
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //ÉèÖÃ¼ü
	{
		Menu_Count ++;

		if(Menu_Count >= 4)
		{
			//´¦Àí·µ»Ø½çÃæ
			Lcd1602_Display_guanbiao(0,9,0);
			Lcd1602_Display_String(0,0,"T:     OVER:    ");
			Lcd1602_Display_String(1,0,"                ");
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				Lcd1602_Display_String(0,0,"Ts:             ");
			  Lcd1602_Display_String(1,0,"                ");
			  Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);
			  Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 2:
				Lcd1602_Display_guanbiao(0,7,1);
				break;
			case 3:
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			case 4:
				Lcd1602_Display_String(0,0,"To:             ");
			  Lcd1602_Display_String(1,0,"                ");
			  Ds13b02_DisPlay(0,3,Time_arry_o[2],Time_arry_o[1],Time_arry_o[0]);
			  Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 5:
				Lcd1602_Display_guanbiao(0,7,1);
				break;
			case 6:
				Lcd1602_Display_guanbiao(0,10,1);
				break;		
			case 7:
				Lcd1602_Display_String(0,0,"Tc:             ");
			  Lcd1602_Display_String(1,0,"                ");
			  Ds13b02_DisPlay(0,3,Time_arry_c[2],Time_arry_c[1],Time_arry_c[0]);
			  Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 8:
				Lcd1602_Display_guanbiao(0,7,1);
				break;
			case 9:
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			
		}
	}

	if(Key_value == 2)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				if(Time_arry[2]<24)
					Time_arry[2]++;
				Ds1302_Save(0x84,Time_arry[2]);
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);									
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 2:
				if(Time_arry[1]<60)
					Time_arry[1]++;
				Ds1302_Save(0x82,Time_arry[1]);	
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);									
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 3:
				if(Time_arry[0]<60)
					Time_arry[0]++;
				Ds1302_Save(0x80,Time_arry[0]);	
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);								
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			case 4:
				if(Time_arry_o[2]<24)
					Time_arry_o[2]++;
				Ds13b02_DisPlay(0,3,Time_arry_o[2],Time_arry_o[1],Time_arry_o[0]);									
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 5:
				if(Time_arry_o[1]<60)
					Time_arry_o[1]++;	
				Ds13b02_DisPlay(0,3,Time_arry_o[2],Time_arry_o[1],Time_arry_o[0]);									
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 6:
				if(Time_arry_o[0]<60)
					Time_arry_o[0]++;
				Ds13b02_DisPlay(0,3,Time_arry_o[2],Time_arry_o[1],Time_arry_o[0]);									
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			case 7:
				if(Time_arry_c[2]<24)
					Time_arry_c[2]++;
				Ds13b02_DisPlay(0,3,Time_arry_c[2],Time_arry_c[1],Time_arry_c[0]);									
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 8:
				if(Time_arry_c[1]<60)
					Time_arry_c[1]++;
				Ds13b02_DisPlay(0,3,Time_arry_c[2],Time_arry_c[1],Time_arry_c[0]);									
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 9:
				if(Time_arry_c[0]<60)
					Time_arry_c[0]++;
				Ds13b02_DisPlay(0,3,Time_arry_c[2],Time_arry_c[1],Time_arry_c[0]);								
				Lcd1602_Display_guanbiao(0,10,1);
				break;

		}
	}
	
	if(Key_value == 3)	 //
	{
		switch(Menu_Count)
		{
			case 0:

				break;
			case 1:
				if(Time_arry[2]>0)
					Time_arry[2]--;
				Ds1302_Save(0x84,Time_arry[2]);
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
								
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 2:
				if(Time_arry[1]>0)
					Time_arry[1]--;
				Ds1302_Save(0x82,Time_arry[1]);	
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
								
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 3:
				if(Time_arry[0]>0)
					Time_arry[0]--;
				Ds1302_Save(0x80,Time_arry[0]);
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
								
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			case 4:
				if(Time_arry_o[2]>0)
					Time_arry_o[2]--;
				Ds13b02_DisPlay(0,3,Time_arry_o[2],Time_arry_o[1],Time_arry_o[0]);									
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 5:
				if(Time_arry_o[1]>0)
					Time_arry_o[1]--;	
				Ds13b02_DisPlay(0,3,Time_arry_o[2],Time_arry_o[1],Time_arry_o[0]);									
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 6:
				if(Time_arry_o[0]>0)
					Time_arry_o[0]--;
				Ds13b02_DisPlay(0,3,Time_arry_o[2],Time_arry_o[1],Time_arry_o[0]);									
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			case 7:
				if(Time_arry_c[2]>0)
					Time_arry_c[2]--;
				Ds13b02_DisPlay(0,3,Time_arry_c[2],Time_arry_c[1],Time_arry_c[0]);									
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 8:
				if(Time_arry_c[1]>0)
					Time_arry_c[1]--;
				Ds13b02_DisPlay(0,3,Time_arry_c[2],Time_arry_c[1],Time_arry_c[0]);									
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 9:
				if(Time_arry_c[0]>0)
					Time_arry_c[0]--;
				Ds13b02_DisPlay(0,3,Time_arry_c[2],Time_arry_c[1],Time_arry_c[0]);								
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			
		}
	}		
		
}

*/
#endif


#if CONFIG_DS18b02 == ENABLED
sbit dq   = P3^7;	//18b20 IO¿ÚµÄ¶¨Òå
unsigned int Ds18b20_Read_temp();
/******Ds18b20 Demo******
uint temp_l=30;

uint temp;
void main()
{
	
	while(1)
	{
	  //¶Á³öÀ´µÄÊÇÈýÎ»Êý£¬µÚÈýÎ»ÊÇÐ¡Êý
		temp=Ds18b20_Read_temp();
		Lcd1602_Display_Three_bit(0,0,temp);
		DelayMs_utrl(100);
	}
}

*/

#endif

#if CONFIG_EEPROM == ENABLED
void SectorErase_Demo(unsigned int sector_addr);
void byte_write_Demo(unsigned int byte_addr, unsigned char original_data);
unsigned char byte_read_Demo(unsigned int byte_addr);

//demo
//¶ÁintÀàÐÍµÄÊý¾Ý  dat1 = byte_read(0x2000);dat2 = byte_read(0x2001);dat1*100+dat2;
//Ð´intÀàÐÍµÄÊý¾Ý 	dat1=yanwu/100; dat2=yanwu%100;  SectorErase(0x2000); byte_write(0x2000,dat1); byte_write(0x2001,dat2);

/******EEPROM Demo******
uchar dat1;
void main()
{
	SectorErase_Demo(0x2000);
	byte_write_Demo(0x2000,dat1);
	DelayMs_utrl(100);
	dat1 = byte_read_Demo(0x2000);
	
	while(1)
	{

	}
}

*/
#endif

#if CONFIG_24C02 == ENABLED

//Ä£ÄâI2C ×ÜÏßµÄÒý½Å¶¨Òå
sbit SCL = P2^0;
sbit SDA = P2^1;
void DELAY_24C02_Demo(unsigned int t);          //ÑÓÊ±º¯Êý
void IICStart_24C02_Demo(void);         //I2C¿ªÊ¼º¯Êý
void IICStop_24C02_Demo(void);          //I2C½áÊøº¯Êý
void Ack_24C02_Demo(void);              //I2CÓ¦´ðº¯Êý
void NOAck_24C02_Demo(void);            //I2CÓ¦´ð·Çº¯Êý
bit Check_Ack_24C02_Demo(void);         //I2CÓ¦´ð¼ì²âº¯Êý
void SEND0_24C02_Demo(void);            //I2C·¢ËÍ0º¯Êý
void SEND1_24C02_Demo(void);            //I2C·¢ËÍ1º¯Êý 
void Write_byte_24C02_Demo(unsigned char dat);  //I2C·¢ËÍ×Ö½Úº¯Êý
unsigned char Read_byte_24C02_Demo(void);//I2C¶ÁÈ¡×Ö½Úº¯Êý
unsigned char rdeeprom_24C02_Demo(unsigned char addr);    //¶ÁAT2402º¯Êý
void wrteeprom_24C02_Demo(unsigned char addr,unsigned char dat);  //Ð´AT2402º¯Êý

/****** Demo******
void main()
{
	wrteeprom_24C02_Demo(3,1);
	DelayMs_utrl(10);//Á¬ÐøÐ´ÈëÊ±¶à¸ö10ms×óÓÒµÄÑÓÊ±
	wrteeprom_24C02_Demo(4,1);
	DelayMs_utrl(100);
	Lcd1602_Display_Three_bit(0,0,rdeeprom_24C02_Demo(3));
	Lcd1602_Display_Three_bit(1,0,rdeeprom_24C02_Demo(4));
	while(1)
	{
	
	}
}

*/

#endif

#if CONFIG_Timer2 == ENABLED
#define Time_count 20 //20Îª1s
typedef void (*Timer2_Process)();
void Timer2_init_Demo(Timer2_Process T_Process);

/****** Demo******
//¸ú´®¿Ú»á³åÍ»£¿Ê¹ÓÃ´®¿Úºó£¬¶¨Ê±Æ÷2¾ÍÎÞ·¨Ê¹ÓÃ

void Timer2_Process2()
{

}
void main()
{
	Timer2_init_Demo(Timer2_Process2);
	while(1)
	{
	
	}
}

*/
#endif

#if CONFIG_Timer0 == ENABLED
typedef void (*Timer0_Process)();
void Timer0_Init_demo(Timer0_Process T_Process);

/****** Demo******
void Timer0_Process2()
{

}
void main()
{
	Timer0_Init_demo(Timer0_Process2);
	while(1)
	{
	
	}
}

*/
#endif

#if CONFIG_UART0 == ENABLED
extern unsigned char a;
typedef void (*UART0_RX_Process_T)(unsigned char *RxDate);
void UART0_Init_Demo();
void UART0_Send_Byte_Demo(unsigned char a);
void UART0_Send_String_Demo(char *s);

/****** Demo******
void UART0_Recv_Process(unsigned char *RxDate)//½ÓÊÕµ½Êý¾ÝµÄ´¦Àí
{
	Lcd1602_Display_Three_bit(0,0,RxDate[1]));
}
void main()
{
	UART0_Init_Demo();
	DelayMs_utrl(500);
	UART0_Send_Byte_Demo(0xFF);
	UART0_Send_Byte_Demo(1);	
	while(1)
	{
		
	}
}
#include <stdio.h>
void main()
{
	int i=2;
	UART0_Init_Demo();
	while(1)
	{
		//UART0_Send_Byte_Demo('A');
		printf("H,%3d,E",i);
		DelayMs_utrl(1000);
	}
}

*/
#endif

#if CONFIG_KEY_MAP == ENABLED

sbit ROW1=P3^0;
sbit ROW2=P3^1;
sbit ROW3=P3^2;
sbit ROW4=P3^3;
sbit COL1=P3^4;
sbit COL2=P3^5;
sbit COL3=P3^6;
sbit COL4=P3^7;
unsigned char Getkeyboard(void);

/*DEMO

// A(10) B(11) C(12) D(13) *(14) #(15)
uchar key_value;
void main()
{

	Lcd1602_Display_Init();
	while(1)
	{
    key_value=Getkeyboard();
		if(key_value!=99)
			Lcd1602_Display_Two_bit(0,0,key_value);
		DelayMs_utrl(100);
	}
}

*/
#endif

#if CONFIG_HX711 == ENABLED
extern unsigned long Weight_Maopi;
//IOÉèÖÃ
sbit HX711_DOUT=P1^2; 
sbit HX711_SCK=P1^3; 

long Get_Weight();
void Get_Maopi();

/****** Demo******
long KgValue;
void main()
{
	Get_Maopi();
	while(1)
	{
		KgValue = Get_Weight();
	}
}
*****/
#endif

#if CONFIG_HRSR04 == ENABLED
sbit Trig_P    = P2^2;		// ³¬Éù²¨Ä£¿éµÄTrig¹Ü½Å
sbit Echo_P    = P2^3;		// ³¬Éù²¨Ä£¿éµÄEcho¹Ü½Å
void HRSR04_Timer_init();
unsigned int GetDistance(void);
/****** Demo******
//Òª¾«È·Ð¡Êýµã£¬°Ñ½ÓÊÕÊýÖµ¸Ä³Éfloat
volatile uint Distanc;
void main()
{
	HRSR04_Timer_init();
	while(1)
	{
			Distanc = GetDistance();
	}
}
***/
#endif

#if CONFIG_MP3_TF == ENABLED
sbit voice_busy = P2^0;
void uart_init();
void Delay_ms(unsigned int n);
void Uart_SendCMD(unsigned char CMD ,unsigned char feedback , unsigned int dat);

/* demo****
#define VOICE_INIT 4
void main()
{
	//´®¿Ú³õÊ¼»¯
	uart_init();
	EA = 1;
		//ÓïÒôÌáÊ¾
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x03,0,VOICE_INIT);//³õÊ¼»¯
	Delay_ms(500);
	while(1)
	{
		...
		Uart_SendCMD(0x03,0,(dat/100));//°ÙÎ»
		Delay_ms(100);
		Uart_SendCMD(0x03,0,12);//°Ù
		Delay_ms(100);		
	}
}

*/
#endif

#if CONFIG_SHT11 == ENABLED

sbit DATA = P2^7;		//Î»¶¨Òå
sbit SCK  = P2^6;

enum {TEMP,HUMI};

typedef union 				//¶¨Òå¹²ÓÃÍ¬ÀàÐÍ
{ 	
	unsigned int i;
	float f;
} value;

void s_connectionreset(void);
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);
void calc_sth10(float *p_humidity ,float *p_temperature);

/*demo
void main()
{
	unsigned int temp,humi;		//¶¨ÒåÎÂ¶ÈºÍÊª¶È±äÁ¿
	value humi_val,temp_val;		//¶¨ÒåÁ½¸ö¹²Í¬Ìå£¬Ò»¸öÓÃÓÚÊª¶È£¬Ò»¸öÓÃÓÚÎÂ¶È
	unsigned char error;		    //ÓÃÓÚ¼ìÑéÊÇ·ñ³öÏÖ´íÎó
	unsigned char checksum;			//CRC			 
	uchar wendu[6];				 	//ÓÃÓÚ¼ÇÂ¼ÎÂ¶È
	uchar shidu[6];				 	//ÓÃÓÚ¼ÇÂ¼Êª¶È	
	value humi_val,temp_val;		//¶¨ÒåÁ½¸ö¹²Í¬Ìå£¬Ò»¸öÓÃÓÚÊª¶È£¬Ò»¸öÓÃÓÚÎÂ¶È
	while(1)
	{
		error=0;					   //³õÊ¼»¯error=0£¬¼´Ã»ÓÐ´íÎó
		error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP); //ÎÂ¶È²âÁ¿
		error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI); //Êª¶È²âÁ¿
    if(error!=0) 
			s_connectionreset();                 ////Èç¹û·¢Éú´íÎó£¬ÏµÍ³¸´Î»		
		else
		{
				humi_val.f=(float)humi_val.i;                   //×ª»»Îª¸¡µãÊý
     		temp_val.f=(float)temp_val.i;                   //×ª»»Îª¸¡µãÊý
     		calc_sth10(&humi_val.f,&temp_val.f);            //ÐÞÕýÏà¶ÔÊª¶È¼°ÎÂ¶È
//   		dew_point=calc_dewpoint(humi_val.f,temp_val.f); //¼ÆËãe dew_point
   			temp=temp_val.f*10;
     		humi=humi_val.f*10;		
		}
	}

}


*/
#endif

#if CONFIG_DHT11 == ENABLED

sbit DTH_PIN=P3^7;// ÎÂÊª¶ÈÄ£¿éÐÅºÅ½Å
char DHT11_RH(unsigned char* arry);
/*Demo	
//RH_Value[2]ÎªÎÂ¶È
//RH_Value[0]ÎªÊª¶È

unsigned char rh_l=60,temp_l=30;
unsigned char RH_Value[4];
while(1)
{
	if(DHT11_RH(RH_Value) == TRUE)
	{
		Lcd1602_Display_Three_bit(0,0,RH_Value[0]);//¶Á³öÎÂÊª¶È£¬Ö»È¡ÕûÊý²¿·Ö
		Lcd1602_Display_Three_bit(1,0,RH_Value[2]);
	}
}
*/
#endif



#if CONFIG_LCD12864_LIB == ENABLED

sbit lcd_RS =    P2^5; 
sbit Lcd_Rw	=	 P2^6;
sbit Lcd_En	=	 P2^7;

void LCDInit();
void Lcd_String(const unsigned char  *str);
void Lcd_Display2data(unsigned char line,unsigned char list,unsigned char Date);
void Lcd_Display3data(unsigned char line,unsigned char list,unsigned int Date);
void  Lcd_ShowSring(unsigned char line,unsigned char list,unsigned char *p);

/*demo

  LCDInit();	//lcd12864³õÊ¼»¯
	Lcd_ShowSring(1,0,"ÅïÄÚÎÂÊª¶È¹âÕÕ");
  Lcd_ShowSring(2,0,"ÎÂ¶È:");
	Lcd_ShowSring(3,0,"Êª¶È:");
	Lcd_ShowSring(4,0,"¹â¶È:");
	while(1);

*/
#endif

#if CONFIG_ESP8266 == ENABLED
extern unsigned char a;
void Uart_Init();
void ESP8266_Set(unsigned char *puf);
void Esp8266_Delay_Ms(int cnt);
void Esp8266_init();
void UartSendString(unsigned char *string);

/**demo

unsigned char buff[30];
void EPS8266_Send(void)
{
	static unsigned char Cnt1 = 1;
  if(++Cnt1 == 5)
	{
		//IPÎª192.168.4.1 £¬¶Ë¿ÚºÅÎª 5000
		//ESP8266_Set ÒÑ¾­ÓÐ¼Ó/r/nÁËAT+CIPSEND=0,26ºóÒª¼Ó»Ø³µ£¬26Îª·¢ËÍµÄ³¤¶È£¬ÊýÁ¿Ò»¶¨Òª×¼
		ESP8266_Set((u8*)"AT+CIPSEND=0,26");	   ////·¢ËÍ×Ö·û³¤¶È   
	}else if(Cnt1 >= 10)
	{
		Cnt1 = 0;
		Cnt1 = 0;
		buff[0]= 'H';
		buff[1]= ':';
		buff[2]= 1/100%10+0x30;
		buff[3]= 1/10%10+0x30;
		buff[4]= 1%10+0x30;
		buff[5]= ',';
		buff[6]= 456/100%10+0x30;
		buff[7]= 456/10%10+0x30;
		buff[8]= ',';
		buff[9]= 456%10+0x30;
		buff[10]= ',';
		buff[11]= 789/100%10+0x30;
		buff[12]= 789/10%10+0x30;
		buff[13]= 789%10+0x30;
		buff[14]= ',';
   	buff[15]= 1+0x30;
		buff[16]= ',';
   	buff[17]= 1+0x30;
		buff[18]= ',';	
   	buff[19]= 1+0x30;
		buff[20]= ',';	
   	buff[21]= 1+0x30;
		buff[22]= ',';	
   	buff[23]= 1+0x30;
		buff[24]= ',';			
		buff[25]= 'E';
		UartSendString(buff);		
	}	
}
void main()
{
	Esp8266_init();
	while(1)
	{
			//½ÓÊÕµ½µÄÊý¾ÝÎª +IPD,0,1:A
			if(a1=='A')
			{
				
				Lcd1602_Display_String(1,0,(u8*)"A");
				a1=0;
			}
			//½ÓÊÕµ½µÄÊý¾ÝÎª +IPD,0,1:B
			if(a1=='B')
			{
				
				Lcd1602_Display_String(1,0,(u8*)"B");
				a1=0;
			}
			//½ÓÊÕµ½µÄÊý¾ÝÎª +IPD,0,1:C
			if(a1=='C')
			{
				
				Lcd1602_Display_String(1,0,(u8*)"C");
				a1=0;
			}			
      EPS	
		EPS8266_Send();
		DelayMs_utrl(100);
	}
}


**/
#endif

#if CONFIG_ISD4004 == ENABLED
#define ISDPOWERUP      0X25           //ISD4004ÉÏµç
#define ISDSTOP         0X10           //ISD4004ÏÂµç
#define OPERSTOP        0X30           //ISD4004Í£Ö¹µ±Ç°²Ù×÷
#define PLAYSET         0XE0//0XE7           //ISD4004´ÓÖ¸¶¨µØÖ·¿ªÊ¼·ÅÒô
#define PLAYCUR         0XF0           //ISD4004´Óµ±Ç°µØÖ·¿ªÊ¼·ÅÒô
#define RECSET          0XA0//0XA5           //ISD4004´ÓÖ¸¶¨µØÖ·¿ªÊ¼Â¼Òô
#define RECCUR          0XB0           //ISD4004´Óµ±Ç°µØÖ·¿ªÊ¼Â¼Òô

#define ADDR1STR        0x0000//0X020           //µÚÒ»Ê×µÄÆðÊ¼µØÖ· 
#define ADDR2STR        0x012d//0X240           //µÚ¶þÊ×µÄÆðÊ¼µØÖ· 
#define ADDR3STR        0x0259//0X180           //µÚÈýÊ×µÄÆðÊ¼µØÖ· 
#define ADDR4STR        0x0385//0X720           //µÚËÄÊ×µÄÆðÊ¼µØÖ· 
sbit   SS=P1^5;            //LOW IS ACTIVELY
sbit   MOSI=P1^4;
sbit   MISO=P1^3;
sbit   SCLK=P1^6;

extern void stop();
extern void rec(unsigned int addr);
extern void play(unsigned int addr);
extern bit flag_xh;

/*demo
play(ADDR4STR);

*/
#endif


#if CONFIG_FUZZIFY == ENABLED
void fuzzy_engine(unsigned char input);
/*demo
		if(Temperature <= Temp_L)//Ð¡ÓÚÉè¶¨ÖµÊ±£¬²ÉÓÃÄ£ºý¼ÆËã
		{
						
		 //Ä£ºý¼ÆËã
			fuzzy_engine((Temp_L - Temperature)*10);
		 
		 if(fuzzy_out)  //¸ù¾ÝÄ£ºý¼ÆËã½á¹û£¬´¦ÀíÊä³ö×´Ì¬
		 {
				LED_3_BUF = led_3=0;		//ÏÔÊ¾¶ÔÓ¦µÄÖ¸Ê¾µÆ
		 }
		 else
		 {
			 LED_3_BUF = led_3=0;		//ÏÔÊ¾¶ÔÓ¦µÄÖ¸Ê¾µÆ 
		 }		
			
		} 
 
 */
#endif
#if CONFIG_EX0_EX1 == ENABLED
typedef void (*EX0_1_Process)();
void EX0_INIT(EX0_1_Process T_Process);
void EX1_INIT(EX0_1_Process T_Process);
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

#if CONFIG_LCD12864 == ENABLED

#define Disp_On  0x3f//¿ªÏÔÊ¾
#define Disp_Off 0x3e//¹ØÏÔÊ¾
#define Col_Add  0x40//µØÖ·»ù×¼
#define Page_Add 0xb8
#define Start_Line 0xc0
#define REGULATE 0      //Ð£×¼
#define SPACE 1    //Ë¢ÐÂÎÂ¶ÈÊ±¼ä¼ä¸ô£¨s£©
//¸÷ÖÖÒý½Å¶¨Òå
sbit cs1=P2^4; 		//CS1=1
sbit cs2=P2^3; 		//CS2=1
sbit Enable=P2^2; 	//Ê¹ÄÜ¶Ë
sbit Di=P2^0;  		//Êý¾ÝÃüÁîÑ¡Ôñ¶Ë
sbit RW=P2^1;  		//¶ÁÐ´Ñ¡Ôñ¶Ë
void Lcd_Init();
void hz_disp16(unsigned char pag,unsigned char col, unsigned char code *hzk);
void hz_disp8(unsigned char pag,unsigned char col, unsigned char code *hzk);
#endif

#if CONFIG_IRSEND == ENABLED
//ºìÍâ¹Ü½Å½Ó¿Ú
sbit HL=P3^4;
void SendIRdata(char p_irdata);
void IR_SEND_INIT();
/**demo

void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //ÉèÖÃ¼ü
	{
		SendIRdata(0x45);
	}

	if(Key_value == 2)	 //
	{
    SendIRdata(0x46);
	}
	
	if(Key_value == 3)	 //
	{
		SendIRdata(0x47);
	}		
		
}


	
void main()
{
	IR_SEND_INIT();
	while(1)
	{
		Key_value_Demo(Key_Process_Demo);
		DelayMs_utrl(100);
	}
}
**/
#endif

#if CONFIG_IR_REVICE == ENABLED
extern unsigned char ir_num;	
void IR_Init(void);
//½ÓÍâ²¿ÖÐ¶Ï0 P32 ,Ê¹ÓÃ¶¨Ê±Æ÷0
/*demo

void main()
{

	IR_Init();
	Lcd1602_Display_Init();
	Lcd1602_Display_String(0,0,"hello world");
	while(1)
	{
 
		if(ir_num>0)
		{
			Lcd1602_Display_Two_bit(1,0,ir_num);
			ir_num=0;
		}
			
			
		
	}
}
*/
#endif
#if CONFIG_DS18B20_MULT== ENABLED
#define MAXNUM 5 //¶¨Òå×î¶àÓÐ8¸ö DS18B02
sbit DQ=P3^5;    //¶¨ÒåÊý¾ÝÏß
void DS18B20_Processing(unsigned char *Temp_Value);
void search_rom(void);//ËÑË÷ROM

/****** Demo******
unsigned char Temp_Value[5];
void main()
{
	search_rom();
	while(1)
	{
		DS18B20_Processing(Temp_Value);
	}
}
*****/
#endif

#if CONFIG_LCD12864_PLUS== ENABLED

#define lcdDat P0  /* LCD12864 Êý¾ÝÏß */
sbit cs2= P1^4;    /* ÓÒÆÁÆ¬Ñ¡£¬¸ßµçÆ½ÓÐÐ§ */
sbit cs1= P1^3;    /* ×óÆÁÆ¬Ñ¡£¬¸ßµçÆ½ÓÐÐ§ */
sbit en = P1^2;    /* ¶Á,Ð´Ê¹ÄÜ,¸ßµçÆ½ÓÐÐ§£¬ÏÂÑØËø¶¨Êý¾Ý */
sbit rw = P1^1;    /* 1¶Á\0Ð´ */
sbit rs = P1^0;    /* 1Êý¾Ý\0Ö¸Áî */
#define addX0 0xB8       /* xµØÖ·£¨0Ò³£© */
#define addY0 0x40       /* yµØÖ·£¨0ÁÐ£© */
#define addZ0 0xC0       /* ZµØÖ·£¨0ÐÐ¿ªÊ¼ÏÔÊ¾£© */

#define CONFIG_CH    ENABLED

void Init12864();
void showStr(unsigned char row,unsigned char col,unsigned char *s);
void showXY(unsigned char row,unsigned char col,unsigned char x,unsigned char y,unsigned char *tab);
void showThreeNum(unsigned char row,unsigned char col,unsigned int s);
void showDS18B02Num(unsigned char row,unsigned char col,unsigned int s);
void Ds13b02_DisPlay_12864(unsigned char row,unsigned char col,unsigned char shi,unsigned char fen,unsigned char miao);
/****** Demo******
showStr(0,0,"                ");
showStr(2,0,"                ");
showStr(4,0,"                ");
showStr(6,0,"                ");
void main()
{
	Init12864();
	showStr(0,0," »¶Ó­Ê¹ÓÃÃÜÂëËø ");
	showStr(2,0,"12  ÇëÊäÈëÃÜÂë   ");
	showThreeNum(4,64,123);
	while(1)
	{

	}
}

*/
#endif

#if CONFIG_KEY_MAP_2== ENABLED
sbit col3=P0^0;sbit col2=P0^1;sbit col1=P0^2;sbit col0=P0^3;
sbit row0=P2^0;sbit row1=P2^1;sbit row2=P1^0;sbit row3=P1^1;
typedef void (*pKey_Map_Process)(unsigned char );
unsigned char key_get();
void Key_Map(pKey_Map_Process key_Map_Process);


/****** Demo******
void Key_Process_Demo(unsigned char Key_value)
{
	showThreeNum(6,0,Key_value);
}
void main()
{
	Init12864();
	showStr(0,0," »¶Ó­Ê¹ÓÃÃÜÂëËø ");
	showStr(2,0,"12  ÇëÊäÈëÃÜÂë   ");
	showThreeNum(4,64,126);
	while(1)
	{
			//showThreeNum(6,0,key_get());
		Key_Map(Key_Process_Demo);
		DelayMs_utrl(100);
	}
}

*/
#endif

#if CONFIG_MAX6675== ENABLED

sbit  SO  = P1^5;  				//P3.6¿ÚÓëSOÏàÁ¬
sbit  MAX6675_SCK = P1^6; 				//P3.4¿ÚÓëSCKÏàÁ¬
sbit  CS1 = P1^7;  				//P3.5¿ÚÓëCSÏàÁ¬

sbit  CS2  = P1^7;   				//P3.5¿ÚÓëCSÏàÁ¬
sbit  CS3  = P1^7;   				//P3.5¿ÚÓëCSÏàÁ¬
sbit  CS4  = P1^7;  				//P3.5¿ÚÓëCSÏàÁ¬
void MAX6675_Processing(unsigned char CH,unsigned short *MAX6675_Temp);

/**demo**
idata  unsigned short MAX6675_Temp[4] = {0,0,0,0};
void main()
{
	while(1)
	{
		MAX6675_Processing(0,MAX6675_Temp);
	}
		
}
			
**/
#endif

#if CONFIG_GSM== ENABLED

//#define RsBuf_N			250
void Uart_init();
void SendASC(unsigned char d);
void SendString(unsigned char *str)	;
void Gsm_init();
void GSM_delay_ms(unsigned int z);
unsigned char strsearch(unsigned char *ptr2,unsigned char *ptr1_at);
void SendTwoNum(unsigned char num);
void SendNum(unsigned char num);
void SendNum_char(unsigned char num);
/***demo

uchar stauts=0;
unsigned char  dianhuahaoma[12]="18459195135";
void Send_SMS_CH(unsigned char *sta,unsigned char option)
{
	
		unsigned char _Data[1];
		static unsigned char Step = 0;
		uchar send_number;
			
			if(*sta!=0)
			{
				switch(Step)
				{
					case 0:
								SendString("AT\r\n"); Step++;
								break;
					
					case 1: SendString("ATE0\r\n");  Step++;  break;

					
					case 2:SendString("AT+CMGF=1\r\n");Step++;break;
			 
					case 3:SendString("AT+CSCS=\"UCS2\"\r\n");Step++;break;
			 

					case 4: SendString("AT+CSMP=17,0,2,25\r\n");Step++;  break;
			 
					case 5: SendString("AT+CMGS=\"");Step++; 
									for(send_number=0;send_number<11;send_number++)//ÔÚÃ¿Î»ºÅÂëÇ°¼Ó003
									{
										SendNum_char(dianhuahaoma[send_number]);
									} 								
									SendString("\"\r\n");

					break;

					case 6: 
									switch(option)
									{
										case 0:
											SendString("52305403836F65F695F48BF753CA65F65403836F"); 
										break;
									}
									
									SendString("0020");			//·¢ËÍ¿Õ¸ñ
									_Data[0] = 0x1A;
									SendASC(*_Data);
									Step = 0;
									*sta=0;
									break;
					default: Step = 0;
					break;
				}
				DelayMs_utrl(100);
		 }


}
void Send_SMS_EN(unsigned char *sta,unsigned char option)
{
	
		unsigned char _Data[1];
		static unsigned char Step = 0;

			
			if(*sta!=0)
			{
				switch(Step)
				{
					case 0:
								SendString("AT\r\n"); Step++;
								break;
					
					case 1: SendString("ATE0\r\n");  Step++;  break;

					
					case 2:SendString("AT+CMGF=1\r\n");Step++;break;
			 
					case 3:SendString((uchar*)"AT+CSCS=\"GSM\"\r\n");Step++;break;
			 
					case 4:SendString((uchar*)"AT+CSMP=17,167,1,0\r\n");Step++;break;			 
					case 5: SendString("AT+CMGS=\"");Step++; 
									SendString(dianhuahaoma);  								
									SendString("\"\r\n");
					break;

					case 6: 
									switch(option)
									{
										case 0:
											SendString("HELLO"); 
										break;
									}
									
									_Data[0] = 0x1A;
									SendASC(*_Data);
									Step = 0;
									*sta=0;
									break;
					default: Step = 0;
					break;
				}
				DelayMs_utrl(100);
		 }


}
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //ÉèÖÃ¼ü
	{
		Menu_Count ++;
		if(dianhuahaoma[0]<'9')
		dianhuahaoma[0]++;
    Lcd1602_Display_String(0,0,dianhuahaoma);
		if(Menu_Count >= 2)
		{
			//´¦Àí·µ»Ø½çÃæ
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}

	if(Key_value == 2)	 //
	{
				if(dianhuahaoma[0]>'0')
		dianhuahaoma[0]--;
    Lcd1602_Display_String(0,0,dianhuahaoma);
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}
	
	if(Key_value == 3)	 //
	{stauts=1;
		//SendString("AT\r\n");
		switch(Menu_Count)
		{
			case 0:
				
				break;
			case 1:
				break;
			case 2:
				break;
		}
	}		
		
}
void main()
{
	Gsm_init();
	Lcd1602_Display_Init();
	Lcd1602_Display_String(0,0,dianhuahaoma);
	while(1)
	{
		Key_value_Demo(Key_Process_Demo);
		if(stauts==0)
		{
			//ÅÐ¶Ï·¢ËÍµÄÌõ¼þ,³É¹¦stauts=1;
			//stauts=1;
			
		}
		//·¢ËÍÍê³ÉºóstautsÏû³ý
		Send_SMS_EN(&stauts,0);
		DelayMs_utrl(100);
	}
}

unsigned char  dianhuahaoma[12]={1,3,7,5,5,1,0,0,5,0,4};
void TransmitText(unsigned char Status)
{
	uchar send_number;
	SendString("AT+CMGF=1\r\n"); //ÉèÖÃÎÄ±¾Ä£Ê½
  GSM_delay_ms(1000);	
	SendString("AT+CSCS=\"UCS2\"\r\n");//ÉèÖÃ¶ÌÐÅ¸ñÊ½£¬·¢ËÍºº×ÖÄ£Ê½
	GSM_delay_ms(1000);
	SendString("AT+CSMP=17,0,2,25\r\n");//ÉèÖÃ¶ÌÐÅÎÄ±¾Ä£Ê½²ÎÊý£¨¾ßÌåÄÚÈÝ²Î¿¼¿ª·¢×ÊÁÏÄÚµÄÄ£¿é×ÊÁÏ£©
	GSM_delay_ms(1000);
	
	SendString("AT+CMGS=");	//ÐÅÏ¢·¢ËÍÖ¸Áî AT+CMGS=//
	SendASC('"');
	for(send_number=0;send_number<11;send_number++)//ÔÚÃ¿Î»ºÅÂëÇ°¼Ó003
	{
		SendNum(dianhuahaoma[send_number]);
	}   
	SendASC('"');
	SendASC('\r');			//·¢ËÍ»Ø³µÖ¸Áî//
	SendASC('\n');			//·¢ËÍ»»ÐÐÖ¸Áî//
	//¸ÃÑÓÊ±»áÓ°ÏìÏÂÒ»¸ö·¢ËÍµÄµÚÒ»¸ö×Ö½ÚµÄÊý¾Ý	
//	GSM_delay_ms(1000);			
			
	
  //È·±£Êý¾ÝÍêÕû£¬²»È»»á·¢ËÍÊ§°Ü	

	SendString("002C8BF753CA65F6590474060021");//,Çë¼°Ê±´¦Àí£¡
	SendString("0020");			//·¢ËÍ¿Õ¸ñ
	GSM_delay_ms(1000);	
	SendASC(0x1a);  //È·¶¨·¢ËÍ¶ÌÐÅ
	
	SendASC('\r');
	SendASC('\n');					
	GSM_delay_ms(1000);
}
//Ó¢ÎÄ 
unsigned char  PhoneNO[]= "13755100504";//½ÓÊÕ·½ºÅÂë
void GSM_SENT()
{
		SendString((uchar*)" AT+CMGF=1\r\n");	
		
		GSM_delay_ms(1000);
		
		SendString((uchar*)"AT+CSCS=\"GSM\"\r\n");	
		
		GSM_delay_ms(1000);
		
		SendString((uchar*)"AT+CMGS=");	//ÐÅÏ¢·¢ËÍÖ¸Áî AT+CMGS=//
		SendASC('"');
		SendString(PhoneNO);   
		SendASC('"');
		SendASC('\r');			//·¢ËÍ»Ø³µÖ¸Áî//
		SendASC('\n');			//·¢ËÍ»Ø³µÖ¸Áî//
		
		GSM_delay_ms(1000);
		
    SendString("system fall down");
		GSM_delay_ms(1000);
		
		SendASC(0x1a);		
}

void main()
{
	Gsm_init();
	while(1)
	{
		TransmitText(2);
		DelayMs_utrl(100);
	}
}

***/
#endif

#if CONFIG_STEPMOTO== ENABLED
sbit dj1 = P2^0;   //µç»úIO¿Ú¶¨Òå
sbit dj2 = P2^1;   //µç»úIO¿Ú¶¨Òå
sbit dj3 = P2^2;   //µç»úIO¿Ú¶¨Òå
sbit dj4 = P2^3;   //µç»úIO¿Ú¶¨Òå
enum moto_statu
{
	STOP,
	OPEN,
	CLOSE,
};
#define TIME_COUNT 1 //
#define TIME_HAPPEND 10000 //10000Îª10ms
typedef void (*MotoTimer2_Process)();
void MotoStepSpeed(unsigned char status,unsigned int speed,unsigned int count);
void stop();
void zheng(unsigned char dat);
void fan(unsigned char dat);
void MotoTimer2_init_Demo(MotoTimer2_Process T_Process);
/**denmo

#define MOTO_COUNT 250
uchar motostatu=OPEN;
uint MotoPoint=0;

void Timer2_Process2()
{
	 static uchar i;
   switch(motostatu)
	 {
		 case STOP:
			 stop();
			 break;
		 case OPEN:
			if(MotoPoint<MOTO_COUNT)
			{
				i++;
				if(i>=4)
				{
					i=0;
					MotoPoint++;
				}
				
				zheng(i);
				
			}else
				stop();			 
		 
			 break;
		 case CLOSE:
			 
			if(MotoPoint>0)
			{
				i++;
				if(i>=4)
				{
					i=0;
					MotoPoint--;
				}
				
				fan(i);
				
			}else
				stop();		 
			 break;		 
	 }

}
void main()
{
  MotoTimer2_init_Demo(Timer2_Process2);
	while(1)
	{
		DelayMs_utrl(100);
	}
}
**/
#endif

#if CONFIG_7BIT_4_LED== ENABLED

#endif

#if CONFIG_BULETOOTH == ENABLED
void Bluetooth_uart_init(unsigned char *buff);
void Bluetooth_UartSendString(unsigned char *string);

/**demo 

//½ÓÊÕµ½µÄÊý¾Ý
unsigned char revbuff;
unsigned char buff[20];
void bluetooth_send()
{
	
	static unsigned int Cnt1 = 1;
	Cnt1++;
  if(Cnt1 >= 40)
	{
			Cnt1 = 0;
			buff[0]= 'H';
			buff[1]= ':';
			buff[2]= Length_Value/100%10+0x30;
			buff[3]= Length_Value/10%10+0x30;
			buff[4]= Length_Value%10+0x30;
			buff[5]= ',';
			buff[6]= adcx/1000%10+0x30;
			buff[7]= adcx/100%10+0x30;
			buff[8]= adcx/10%10+0x30;
			buff[9]= adcx%10+0x30;	
			buff[10]= ',';
			buff[11]= autoFlag+0x30;
			buff[12]= ',';			
			buff[13]= 'E';	
			Bluetooth_UartSendString(buff);		
	}
	

}
void main()
{
	Bluetooth_uart_init(&revbuff);
	while(1)
	{
		bluetooth_send();
		
	}
}
**/
#endif

#if CONFIG_PCF8591== ENABLED
#define  NOP()   _nop_()   /* ¶¨Òå¿ÕÖ¸Áî */
#define  _Nop()  _nop_()   /*¶¨Òå¿ÕÖ¸Áî*/

 
sbit     PCF8591_SCL=P1^1;       //I2C  Ê±ÖÓ 
sbit     PCF8591_SDA=P1^0;       //I2C  Êý¾Ý 

//Æð¶¯×ÜÏßº¯Êý
void PCF8591_Start();
//½áÊø×ÜÏßº¯Êý  
void PCF8591_Stop();
//Ó¦´ð×Óº¯Êý
void PCF8591_Ack(bit a);
//×Ö½ÚÊý¾Ý·¢ËÍº¯Êý
void PCF8591_SendByte(unsigned char  c);
//ÓÐ×ÓµØÖ··¢ËÍ¶à×Ö½ÚÊý¾Ýº¯Êý               
bit PCF8591_ISendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no) ;
//ÎÞ×ÓµØÖ··¢ËÍ¶à×Ö½ÚÊý¾Ýº¯Êý   
bit PCF8591_ISendStrExt(unsigned char sla,unsigned char *s,unsigned char no);
//ÎÞ×ÓµØÖ·¶Á×Ö½ÚÊý¾Ýº¯Êý               
unsigned char PCF8591_RcvByte();
/////////////////////////////////////////////////
bit PCF8591_DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
bit PCF8591_ISendByte(unsigned char sla,unsigned char c);
unsigned char PCF8591_IRcvByte(unsigned char sla);

/*demo

		for(i=0;i<8;i++)
		{
			switch(AD_CHANNEL)
			{
				case 0: PCF8591_ISendByte(PCF8591,0x41);
				AD_Up=PCF8591_IRcvByte(PCF8591)*2;  //ADC0 Ä£Êý×ª»»1
				break;  
				
				case 1: PCF8591_ISendByte(PCF8591,0x42);
				AD_Down=PCF8591_IRcvByte(PCF8591)*2;  //ADC1  Ä£Êý×ª»»2
				break;  
				case 2: PCF8591_ISendByte(PCF8591,0x43);
				AD_Left=PCF8591_IRcvByte(PCF8591)*2;  //ADC2 Ä£Êý×ª»»3
				break;  
				
				case 3: PCF8591_ISendByte(PCF8591,0x40);
				AD_Right=PCF8591_IRcvByte(PCF8591)*2;  //ADC3  Ä£Êý×ª»»4
				break; 
			}

			Send_Hex(Table,4);
			if(++AD_CHANNEL>3)
			{
					AD_CHANNEL=0;
					Table[0] = AD_Up;
					Table[1] = AD_Down;
					Table[2] = AD_Left;
					Table[3] = AD_Right;
				 Lcd1602_Display_Three_bit(0,3,AD_Up);
				 Lcd1602_Display_Three_bit(0,11,AD_Down);
				 Lcd1602_Display_Three_bit(1,3,AD_Left);
				 Lcd1602_Display_Three_bit(1,11,AD_Right);				
			 }
		}
*/
#endif

#if CONFIG_SPEAK_RING == ENABLED

sbit speaker=P3^2;     //ÎÞÔ´·äÃùÆ÷

void speak_ring_init();
void speak_play();

/*demo
void main()
{
	speak_ring_init();
	while(1)
	{
		speak_play();
	}
}

*/
#endif


#if CONFIG_RC522 == ENABLED

#define nop() _nop_()
/////////////////////////////////////////////////////////////////////
//MF522ÃüÁî×Ö
/////////////////////////////////////////////////////////////////////
#define PCD_IDLE              0x00               //È¡Ïûµ±Ç°ÃüÁî
#define PCD_AUTHENT           0x0E               //ÑéÖ¤ÃÜÔ¿
#define PCD_RECEIVE           0x08               //½ÓÊÕÊý¾Ý
#define PCD_TRANSMIT          0x04               //·¢ËÍÊý¾Ý
#define PCD_TRANSCEIVE        0x0C               //·¢ËÍ²¢½ÓÊÕÊý¾Ý
#define PCD_RESETPHASE        0x0F               //¸´Î»
#define PCD_CALCCRC           0x03               //CRC¼ÆËã

/////////////////////////////////////////////////////////////////////
//Mifare_One¿¨Æ¬ÃüÁî×Ö
/////////////////////////////////////////////////////////////////////
#define PICC_REQIDL           0x26               //Ñ°ÌìÏßÇøÄÚÎ´½øÈëÐÝÃß×´Ì¬
#define PICC_REQALL           0x52               //Ñ°ÌìÏßÇøÄÚÈ«²¿¿¨
#define PICC_ANTICOLL1        0x93               //·À³å×²
#define PICC_ANTICOLL2        0x95               //·À³å×²
#define PICC_AUTHENT1A        0x60               //ÑéÖ¤AÃÜÔ¿
#define PICC_AUTHENT1B        0x61               //ÑéÖ¤BÃÜÔ¿
#define PICC_READ             0x30               //¶Á¿é
#define PICC_WRITE            0xA0               //Ð´¿é
#define PICC_DECREMENT        0xC0               //¿Û¿î
#define PICC_INCREMENT        0xC1               //³äÖµ
#define PICC_RESTORE          0xC2               //µ÷¿éÊý¾Ýµ½»º³åÇø
#define PICC_TRANSFER         0xB0               //±£´æ»º³åÇøÖÐÊý¾Ý
#define PICC_HALT             0x50               //ÐÝÃß

/////////////////////////////////////////////////////////////////////
//MF522 FIFO³¤¶È¶¨Òå
/////////////////////////////////////////////////////////////////////
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte
#define MAXRLEN  18

/////////////////////////////////////////////////////////////////////
//MF522¼Ä´æÆ÷¶¨Òå
/////////////////////////////////////////////////////////////////////
// PAGE 0
#define     RFU00                 0x00    
#define     CommandReg            0x01    
#define     ComIEnReg             0x02    
#define     DivlEnReg             0x03    
#define     ComIrqReg             0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F
// PAGE 1     
#define     RFU10                 0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F
// PAGE 2    
#define     RFU20                 0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
// PAGE 3      
#define     RFU30                 0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		  		  0x3F

/////////////////////////////////////////////////////////////////////
//ºÍMF522Í¨Ñ¶Ê±·µ»ØµÄ´íÎó´úÂë
/////////////////////////////////////////////////////////////////////
#define 	MI_OK                 0
#define 	MI_NOTAGERR           (-1)
#define 	MI_ERR                (-2)

sbit  spi_cs=P1^3;
sbit  spi_ck=P1^4;
sbit  spi_mosi=P1^5;
sbit  spi_miso=P1^6;
sbit  spi_rst=P1^2;

#define SET_SPI_CS  spi_cs=1
#define CLR_SPI_CS  spi_cs=0

#define SET_SPI_CK  spi_ck=1
#define CLR_SPI_CK  spi_ck=0

#define SET_SPI_MOSI  spi_mosi=1
#define CLR_SPI_MOSI  spi_mosi=0

#define STU_SPI_MISO  spi_miso

#define SET_RC522RST  spi_rst=1
#define CLR_RC522RST  spi_rst=0

extern char PcdReset(void);
extern char PcdRequest(unsigned char req_code,unsigned char *pTagType);
extern void PcdAntennaOn(void);
extern void PcdAntennaOff(void);
extern char M500PcdConfigISOType(unsigned char type);
extern char PcdAnticoll(unsigned char *pSnr);
extern char PcdSelect(unsigned char *pSnr);
extern char PcdAuthState(unsigned char auth_mode,unsigned char addr,unsigned char *pKey,unsigned char *pSnr);
extern char PcdWrite(unsigned char addr,unsigned char *pData);
extern char PcdRead(unsigned char addr,unsigned char *pData);
extern char PcdHalt(void);
extern void init_rc522(void);
char read_id(unsigned char *pTagType);
/*demo

unsigned char xdata CardRevBuf[10] = { 0 };

void main()
{
	init_rc522();
	while(1)
	{
		if(read_id(CardRevBuf))//¶Á¿¨³É¹¦
		{

		}
		DelayMs_utrl(100);
	}
}

*/
#endif


#if CONFIG_MPU6050 == ENABLED

//****************************************
// ¶¨Òå51µ¥Æ¬»ú¶Ë¿Ú
//****************************************
sbit    SCL=P1^4;			//IICÊ±ÖÓÒý½Å¶¨Òå
sbit    SDA=P1^5;			//IICÊý¾ÝÒý½Å¶¨Òå
//****************************************
// ¶¨ÒåMPU6050ÄÚ²¿µØÖ·
//****************************************
#define	SMPLRT_DIV		0x19	//ÍÓÂÝÒÇ²ÉÑùÂÊ£¬µäÐÍÖµ£º0x07(125Hz)
#define	CONFIG			0x1A	//µÍÍ¨ÂË²¨ÆµÂÊ£¬µäÐÍÖµ£º0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//ÍÓÂÝÒÇ×Ô¼ì¼°²âÁ¿·¶Î§£¬µäÐÍÖµ£º0x18(²»×Ô¼ì£¬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//¼ÓËÙ¼Æ×Ô¼ì¡¢²âÁ¿·¶Î§¼°¸ßÍ¨ÂË²¨ÆµÂÊ£¬µäÐÍÖµ£º0x01(²»×Ô¼ì£¬2G£¬5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//µçÔ´¹ÜÀí£¬µäÐÍÖµ£º0x00(Õý³£ÆôÓÃ)
#define	WHO_AM_I		0x75	//IICµØÖ·¼Ä´æÆ÷(Ä¬ÈÏÊýÖµ0x68£¬Ö»¶Á)
#define	SlaveAddress	0xD0	//IICÐ´ÈëÊ±µÄµØÖ·×Ö½ÚÊý¾Ý£¬+1Îª¶ÁÈ¡



//**************************************************************************************************
void  Delay5us();
//********************************MPU6050²Ù×÷º¯Êý***************************************************
void  InitMPU6050();											//³õÊ¼»¯MPU6050
void  I2C_Start();
void  I2C_Stop();
void  I2C_SendACK(bit ack);
bit   I2C_RecvACK();
void  I2C_SendByte(unsigned char dat);
unsigned char I2C_RecvByte();
void  I2C_ReadPage();
void  I2C_WritePage();

unsigned char Single_ReadI2C(unsigned char REG_Address);						//¶ÁÈ¡I2CÊý¾Ý
void  Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data);	    //ÏòI2CÐ´ÈëÊý¾Ý
int GetData(unsigned char REG_Address);
float Angle_Calcu(void);
#include <math.h>

/*DEMO


unsigned int adx,ady,adz;
void main()
{
  InitMPU6050();
	while(1)
	{
		adx=GetData(ACCEL_XOUT_H);
		ady=GetData(ACCEL_YOUT_H);
		adz = GetData(ACCEL_ZOUT_H);
		adx = adx / 172;
		ady = ady / 172;
		adz = adz / 172;
		//Lcd1602_Display_Three_bit(1,4,adx);
		//Lcd1602_Display_Three_bit(1,8,ady);
		//Lcd1602_Display_Three_bit(1,4,adz);
	}
}

*/
#endif
#if CONFIG_OLED == ENABLED

#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý
#define OLED_MODE 0


sbit OLED_SCL=P1^6;//Ê±ÖÓ D0£¨SCLK£
sbit OLED_SDIN=P1^7;//D1£¨MOSI£© Êý¾Ý


#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1





//OLEDÄ£Ê½ÉèÖÃ
//0:4Ïß´®ÐÐÄ£Ê½
//1:²¢ÐÐ8080Ä£Ê½

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED¶Ë¿Ú¶¨Òå----------------  					   

void delay_ms(unsigned int ms);


//OLED¿ØÖÆÓÃº¯Êý
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack();

/*



	OLED_Init();	
	OLED_Clear();
	OLED_ShowString(0,0,(u8*)"Sm:000 Te:000   ",16);
	OLED_ShowString(0,2,(u8*)"St:Wu           ",16);
	OLED_ShowString(0,4,(u8*)"                ",16);
	OLED_ShowString(0,8,(u8*)"                ",16);
	OLED_ShowNum(8*3,0,123,3,16);
	OLED_ShowString(8*10,2,(u8*)"Fire",16);


*/
#endif

#if CONFIG_BMP180 == ENABLED

typedef struct __BMP180
{
	short AC1;
	short AC2;
	short AC3;
	unsigned short AC4;
	unsigned short AC5;
	unsigned short AC6;
	short B1;
	short B2;
	short MB;
	short MC;
	short MD;
	long PRE;
}_bmp180;
#define	BMP180_SlaveAddress   0xee	  //¶¨ÒåÆ÷¼þÔÚIIC×ÜÏßÖÐµÄ´ÓµØÖ·   
#define OSS 0

#define SCL(x) SCL##x
#define SDA(x) SDA##x

sbit    SDA(0)=P2^6; 
sbit	  SCL(0)=P2^7; 

sbit    SDA(1)=P2^0; 
sbit	  SCL(1)=P2^1; 

void Init_BMP180(uchar channal,_bmp180* tBmpValue);
long bmp180Convert(uchar channal,_bmp180 tBmpValue);
/*
		if(channal==0)
		{

		}else
		{
		
		}	
*/
#endif

#endif

