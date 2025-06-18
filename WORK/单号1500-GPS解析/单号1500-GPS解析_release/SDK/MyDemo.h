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

#if CONFIG_UART0 == ENABLED
typedef struct{
	int year;  
	int month; 
	int  day;
	int hour;
	int minute;
	int second;
}DATE_TIME;

typedef  struct{
	double  latitude;  //����
	double  longitude; //γ��
	int     latitude_Degree;	//��
	int		latitude_Cent;		//��
	int   	latitude_Second;    //��
	int     longitude_Degree;	//��
	int		longitude_Cent;		//��
	int   	longitude_Second;   //��
	float 	speed;      //�ٶ�
	float 	direction;  //����
	float 	height_ground;    //ˮƽ��߶�
	float 	height_sea;       //���θ߶�
	char la_arry[10];
	char lo_arry[10];
	uchar 	NS;
	uchar 	EW;
	DATE_TIME D;
}GPS_INFO;
typedef void (*UART0_RX_Process_T)(unsigned char *RxDate);
void UART0_Init_Demo();
void UART0_Send_Byte_Demo(unsigned char a);
int GPS_GGA_Parse(char *line,GPS_INFO *GPS);
void showJIN(unsigned char row,unsigned char col,unsigned int s);
void showwei(unsigned char row,unsigned char col,unsigned int s);
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
#include <stdio.h>
void main()
{
	int i=2;
	UART0_Init_Demo(UART0_Recv_Process);
	while(1)
	{
		//UART0_Send_Byte_Demo('A');
		printf("H,%3d,E",i);
		DelayMs_utrl(1000);
	}
}

*/
#endif

#if CONFIG_LCD12864_PLUS== ENABLED

#define lcdDat P0  /* LCD12864 ������ */
sbit cs2= P1^4;    /* ����Ƭѡ���ߵ�ƽ��Ч */
sbit cs1= P1^3;    /* ����Ƭѡ���ߵ�ƽ��Ч */
sbit en = P1^2;    /* ��,дʹ��,�ߵ�ƽ��Ч�������������� */
sbit rw = P1^1;    /* 1��\0д */
sbit rs = P1^0;    /* 1����\0ָ�� */
#define addX0 0xB8       /* x��ַ��0ҳ�� */
#define addY0 0x40       /* y��ַ��0�У� */
#define addZ0 0xC0       /* Z��ַ��0�п�ʼ��ʾ�� */

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
	showStr(0,0," ��ӭʹ�������� ");
	showStr(2,0,"12  ����������   ");
	showThreeNum(4,64,123);
	while(1)
	{

	}
}

*/
#endif

#endif

