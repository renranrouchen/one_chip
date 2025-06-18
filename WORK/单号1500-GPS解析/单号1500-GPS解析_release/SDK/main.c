#include "MyDemo.h"

extern uchar xdata gps_flag;      //GPS处理标志
extern char xdata rev_buf[80];        //接收缓存
extern uchar xdata rev_stop ;     //接收停止标志

GPS_INFO xdata  GPS; 



												



void main()
{

	UART0_Init_Demo();
	Init12864();
	showStr(0,0,"卫星值:         ");
	showStr(2,0,"                ");
	showStr(4,0,"纬度:           ");
	showStr(6,0,"经度:           ");
	while(1)
	{
		
		if(rev_stop)   //如果接收完一行
		{

				if (GPS_GGA_Parse(rev_buf, &GPS))  //解析GPGGA
				{

					gps_flag = 0;
					rev_stop  = 0;
					showThreeNum(0,8*7,GPS.direction);
					//showThreeNum(2,8*7,GPS.speed);
					if(GPS.speed==15)
					{
						showStr(2,0,"固定解");
					}else
					{
						showStr(2,0,"未收敛");
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