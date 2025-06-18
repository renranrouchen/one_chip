#include "MyDemo.h"

extern uchar xdata gps_flag;      //GPS�����־
extern char xdata rev_buf[80];        //���ջ���
extern uchar xdata rev_stop ;     //����ֹͣ��־

GPS_INFO xdata  GPS; 



												



void main()
{

	UART0_Init_Demo();
	Init12864();
	showStr(0,0,"����ֵ:         ");
	showStr(2,0,"                ");
	showStr(4,0,"γ��:           ");
	showStr(6,0,"����:           ");
	while(1)
	{
		
		if(rev_stop)   //���������һ��
		{

				if (GPS_GGA_Parse(rev_buf, &GPS))  //����GPGGA
				{

					gps_flag = 0;
					rev_stop  = 0;
					showThreeNum(0,8*7,GPS.direction);
					//showThreeNum(2,8*7,GPS.speed);
					if(GPS.speed==15)
					{
						showStr(2,0,"�̶���");
					}else
					{
						showStr(2,0,"δ����");
					}
					showStr(4,8*5,GPS.la_arry);
					showStr(6,8*5,GPS.lo_arry);
					//showwei(4,8*5,GPS.longitude);
					//showJIN(6,8*5,GPS.latitude);
				}
				rev_stop  = 0;

		}

		DelayMs_utrl(100);
	}
}