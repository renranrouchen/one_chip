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

/****�޸ĵĵ�*****
***���ñ��1602��com��data��ֻ��Ҫ��Lcd1602_write_com��Lcd1602_write_data�滻�ɶ�Ӧ
***Ҫ������1602��ֻ��Ҫ�޸���Ӧ������
***/
#define Lcd1602_Demo_write_com Lcd1602_write_com
#define Lcd1602_Demo_write_data Lcd1602_write_data

sbit Lcd1602_rs=P2^5;	 //1602����/����ѡ������ H:����      	L:����
sbit Lcd1602_rw=P2^6;	 //1602��д����	         H:���ݼĴ���  	L:ָ��Ĵ���
sbit Lcd1602_e =P2^7;	 //1602ʹ������          �½��ش���


void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p);
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date);
void Lcd1602_Display_Init();

/******LCD1602 Demo******
void main()
{
	Lcd1602_Display_Init();
	Lcd1602_Display_String("hello world");
	while(1);
}

*/
#endif


#if CONFIG_KEY == ENABLED

sbit Demo_KEY1 = P1^3;
sbit Demo_KEY2 = P1^2;
sbit Demo_KEY3 = P1^1;
sbit Demo_KEY4 = P1^0;
sbit Demo_KEY5 =  P3^6;
sbit Demo_KEY6 =  P3^7;
#define KEY_COUNT 3 //������Ҫ�������������6��
typedef void (*pKey_Process)(unsigned char );
void Key_value_Demo(pKey_Process key_Process);	

/******Key Demo******
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //���ü�
	{
		Menu_Count ++;

		if(Menu_Count >= 2)
		{
			//�����ؽ���
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
	Key_value_Demo(Key_Process_Demo);
	while(1)
	{
	
	}
}
***/
#endif

#if CONFIG_ADC0832 == ENABLED

sbit ADCS = P2^4;	//adc0832 ʱ�����Ŷ���
sbit ADCLK =P2^3;
sbit ADDI = P2^2;	//adc0832  �������Ŷ���
sbit ADDO = P2^2;	//adc0832  Ƭѡ���Ŷ���

unsigned char ADC0832_Demo(bit mode,bit channel); 

/******ADC0832 Demo******
long value;

unsigned char cs;
unsigned int sum;
unsigned char Ad_dat=0;
void main()
{
	while(1)
	{
		//����demo
		value = ADC0832_Demo(1,0);//ͨ��0 	
		//value = ADC0832_Demo(1,1);//ͨ��1 	
		//value = value * 486 / 256; //486��Ӧ��Ϊ��Χ
		value = (256-value) * 486 / 256;//��ֵ����
		
		//ˮλdemo
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
				Ad_dat=(float)((Ad_dat-2)/2.4); //��Χ100 
			else
				Ad_dat=0;	
				
			sum=0;
			
		}
	}
}

*/
#endif

#if CONFIG_DS1302 == ENABLED

sbit clk = P2^1;	  //ds1302ʱ���߶���
sbit io =  P2^2;	  //������
sbit rst = P2^0;	  //��λ��
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
unsigned char Time_arry[7];

void main()
{
	while(1)
	{
		Ds1302_Read_Time(arry);
		Ds13b02_DisPlay(0,6,arry[2],arry[1],arry[0]);	//ʹ��1602
		DelayMs_utrl(100);
		
		//����ʱ����
		//Ds1302_Save(0x84,arry[2]);
		//Ds1302_Save(0x82,arry[1]);
		//Ds1302_Save(0x80,arry[0]);	
	}
}

*/
#endif


#if CONFIG_DS18b02 == ENABLED
sbit dq   = P3^7;	//18b20 IO�ڵĶ���
unsigned int Ds18b20_Read_temp();
/******Ds18b20 Demo******
void main()
{
	Lcd1602_Display_Init();
	while(1)
	{
		Lcd1602_Display_Three_bit(0,0,Ds18b20_Read_temp());
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
//��int���͵�����  dat1 = byte_read(0x2000);dat2 = byte_read(0x2001);dat1*100+dat2;
//дint���͵����� 	dat1=yanwu/100; dat2=yanwu%100;  SectorErase(0x2000); byte_write(0x2000,dat1); byte_write(0x2001,dat2);

/******EEPROM Demo******
uchar dat1;
void main()
{
	SectorErase(0x2000);
	byte_write(0x2000,dat1);
	DelayMs_utrl(100);
	dat1 = byte_read(0x2000);
	
	while(1)
	{

	}
}

*/
#endif

#if CONFIG_24C02 == ENABLED

//ģ��I2C ���ߵ����Ŷ���
sbit SCL = P2^1;
sbit SDA = P2^0;
void DELAY_24C02_Demo(unsigned int t);          //��ʱ����
void IICStart_24C02_Demo(void);         //I2C��ʼ����
void IICStop_24C02_Demo(void);          //I2C��������
void Ack_24C02_Demo(void);              //I2CӦ����
void NOAck_24C02_Demo(void);            //I2CӦ��Ǻ���
bit Check_Ack_24C02_Demo(void);         //I2CӦ���⺯��
void SEND0_24C02_Demo(void);            //I2C����0����
void SEND1_24C02_Demo(void);            //I2C����1���� 
void Write_byte_24C02_Demo(unsigned char dat);  //I2C�����ֽں���
unsigned char Read_byte_24C02_Demo(void);//I2C��ȡ�ֽں���
unsigned char rdeeprom_24C02_Demo(unsigned char addr);    //��AT2402����
void wrteeprom_24C02_Demo(unsigned char addr,unsigned char dat);  //дAT2402����

/****** Demo******
void main()
{
	wrteeprom_24C02_Demo(3,1);
	DelayMs_utrl(10);//����д��ʱ���10ms���ҵ���ʱ
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
#define Time_count 20 //20Ϊ1s
typedef void (*Timer2_Process)();
void Timer2_init_Demo(Timer2_Process T_Process);


/****** Demo******
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
#define CRC 0XFF
#define REV_NUM 2 //������0��ʼ��
typedef void (*UART0_RX_Process_T)(unsigned char *RxDate);
void UART0_Init_Demo(UART0_RX_Process_T RX_Process);
void UART0_Send_Byte_Demo(unsigned char a);

/****** Demo******
void UART0_Recv_Process(unsigned char *RxDate)//���յ����ݵĴ���
{
	Lcd1602_Display_Three_bit(0,0,RxDate[1]));
}
void main()
{
	UART0_Init_Demo(UART0_Recv_Process);
	DelayMs_utrl(500);
	UART0_Send_Byte_Demo(0xFF);
	UART0_Send_Byte_Demo(1);	
	while(1)
	{
		
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
#endif

#if CONFIG_HX711 == ENABLED
extern unsigned long Weight_Maopi;
//IO����
sbit HX711_DOUT=P1^2; 
sbit HX711_SCK=P1^3; 

long Get_Weight();
void Get_Maopi();
#endif

#if CONFIG_HRSR04 == ENABLED
void HRSR04_Timer_init();
unsigned int GetDistance(void);
#endif

#if CONFIG_MP3_TF == ENABLED
void uart_init();
void Delay_ms(unsigned int n);
void Uart_SendCMD(unsigned char CMD ,unsigned char feedback , unsigned int dat);
#endif

#if CONFIG_SHT11 == ENABLED

sbit DATA = P2^7;		//λ����
sbit SCK  = P2^6;

enum {TEMP,HUMI};

typedef union 				//���干��ͬ����
{ 	
	unsigned int i;
	float f;
} value;

void s_connectionreset(void);
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);
void calc_sth10(float *p_humidity ,float *p_temperature);
#endif

#if CONFIG_DHT11 == ENABLED

sbit DTH_PIN=P3^7;// ��ʪ��ģ���źŽ�
char DHT11_RH(unsigned char* arry);
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
#endif

#if CONFIG_ESP8266 == ENABLED
extern unsigned char a;
void Uart_Init();
void ESP8266_Set(unsigned char *puf);
void Esp8266_Delay_Ms(int cnt);
void Esp8266_init();
void UartSendString(unsigned char *string);
#endif

#if CONFIG_ISD4004 == ENABLED
#define ISDPOWERUP      0X25           //ISD4004�ϵ�
#define ISDSTOP         0X10           //ISD4004�µ�
#define OPERSTOP        0X30           //ISD4004ֹͣ��ǰ����
#define PLAYSET         0XE0//0XE7           //ISD4004��ָ����ַ��ʼ����
#define PLAYCUR         0XF0           //ISD4004�ӵ�ǰ��ַ��ʼ����
#define RECSET          0XA0//0XA5           //ISD4004��ָ����ַ��ʼ¼��
#define RECCUR          0XB0           //ISD4004�ӵ�ǰ��ַ��ʼ¼��

#define ADDR1STR        0x0000//0X020           //��һ�׵���ʼ��ַ 
#define ADDR2STR        0x012d//0X240           //�ڶ��׵���ʼ��ַ 
#define ADDR3STR        0x0259//0X180           //�����׵���ʼ��ַ 
#define ADDR4STR        0x0385//0X720           //�����׵���ʼ��ַ 
sbit   SS=P1^5;            //LOW IS ACTIVELY
sbit   MOSI=P1^4;
sbit   MISO=P1^3;
sbit   SCLK=P1^6;

extern void stop();
extern void rec(unsigned int addr);
extern void play(unsigned int addr);
extern bit flag_xh;
#endif

#if CONFIG_EX0_EX1 == ENABLED
typedef void (*EX0_1_Process)();
void EX0_INIT(EX0_1_Process T_Process);
void EX1_INIT(EX0_1_Process T_Process);
#endif

#if CONFIG_LCD12864 == ENABLED

#define Disp_On  0x3f//����ʾ
#define Disp_Off 0x3e//����ʾ
#define Col_Add  0x40//��ַ��׼
#define Page_Add 0xb8
#define Start_Line 0xc0
#define REGULATE 0      //У׼
#define SPACE 1    //ˢ���¶�ʱ������s��
//�������Ŷ���
sbit cs1=P2^4; 		//CS1=1
sbit cs2=P2^3; 		//CS2=1
sbit Enable=P2^2; 	//ʹ�ܶ�
sbit Di=P2^0;  		//��������ѡ���
sbit RW=P2^1;  		//��дѡ���
void Lcd_Init();
void hz_disp16(unsigned char pag,unsigned char col, unsigned char code *hzk);
void hz_disp8(unsigned char pag,unsigned char col, unsigned char code *hzk);
#endif

#if CONFIG_IRSEND == ENABLED
//����ܽŽӿ�
sbit HL=P3^4;
void IR_init();
void SendIRdata(char p_irdata);

#endif

#if CONFIG_DS18B20_MULT== ENABLED
#define MAXNUM 5 //���������8�� DS18B02
sbit DQ=P3^5;    //����������
void DS18B20_Processing(unsigned char *Temp_Value);
void search_rom(void);//����ROM
#endif
#endif

