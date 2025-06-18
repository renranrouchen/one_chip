
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
* ���� : delay_uint()
* ���� : С��ʱ��
* ���� : ��
* ��� : ��
***********************************************************************/
void Lcd1602_delay_uint(unsigned int q)
{
	while(q--);
}

/********************************************************************
* ���� : write_com(uchar com)
* ���� : 1602�����
* ���� : ���������ֵ
* ��� : ��
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
* ���� : write_data(uchar dat)
* ���� : 1602д���ݺ���
* ���� : ��Ҫд��1602������
* ��� : ��
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


/*****************���ƹ�꺯��********************/
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date)
{		
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	if(date == 1)
		Lcd1602_Demo_write_com(0x0f);     //��ʾ��겢����˸	
	else 
		Lcd1602_Demo_write_com(0x0c);   //�رչ��
}

void Lcd1602_Display_Init()
{
	Lcd1602_Demo_write_com(0x38);
	Lcd1602_Demo_write_com(0x38);
	Lcd1602_Demo_write_com(0x0c);
	Lcd1602_Demo_write_com(0x06);
}
#if CONFIG_DS1302 == ENABLED

void Ds13b02_DisPlay_fen(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add); 
	

	Lcd1602_Demo_write_data(shi%100/10+0x30);		// ʮλ
	Lcd1602_Demo_write_data(shi%10+0x30);				// ��λ
	Lcd1602_Demo_write_data('-');
	Lcd1602_Demo_write_data(fen%100/10+0x30);		// ʮλ
	Lcd1602_Demo_write_data(fen%10+0x30);				// ��λ
	Lcd1602_Demo_write_data('-');
	Lcd1602_Demo_write_data(miao%100/10+0x30);		// ʮλ
	Lcd1602_Demo_write_data(miao%10+0x30);				// ��λ

}
/*********************************************************/
// Һ���������
/*********************************************************/
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add); 
	

	Lcd1602_Demo_write_data(shi%100/10+0x30);		// ʮλ
	Lcd1602_Demo_write_data(shi%10+0x30);				// ��λ
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(fen%100/10+0x30);		// ʮλ
	Lcd1602_Demo_write_data(fen%10+0x30);				// ��λ
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(miao%100/10+0x30);		// ʮλ
	Lcd1602_Demo_write_data(miao%10+0x30);				// ��λ

}
#endif
#if CONFIG_DS18b02 == ENABLED
void Lcd1602_Display_Ds18b02(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	Lcd1602_Demo_write_data(0x30+date/100%10);
	Lcd1602_Demo_write_data(0x30+date/10%10);
	Lcd1602_Demo_write_data('.');
	Lcd1602_Demo_write_data(0x30+date%10);	
}
#endif
#endif

/********************������������*****************/
#if CONFIG_KEY == ENABLED


void Key_value_Demo(pKey_Process key_Process)	 //������������
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

  

unsigned char ADC0832_Demo(bit mode,bit channel)    //ADת�������ؽ��
{
	unsigned char i,dat,ndat;
	
	ADCS = 0;//����CS��
	_nop_();
	_nop_();
	
	ADDI = 1;	//��1���½���Ϊ�ߵ�ƽ
	ADCLK = 1;//����CLK��
	_nop_();
	_nop_();
	ADCLK = 0;//����CLK��,�γ��½���1
	_nop_();
	_nop_();
	
	ADDI = mode;	//�͵�ƽΪ���ģʽ���ߵ�ƽΪ��ͨ��ģʽ��	
	ADCLK = 1;//����CLK��
	_nop_();
	_nop_();
	ADCLK = 0;//����CLK��,�γ��½���2
	_nop_();
	_nop_();
	
	ADDI = channel;	//�͵�ƽΪCH0���ߵ�ƽΪCH1	
	ADCLK = 1;//����CLK��
	_nop_();
	_nop_();
	ADCLK = 0;//����CLK��,�γ��½���3
	
	ADDI = 1;//�����������(���������)
	dat = 0;
	//���濪ʼ��ȡת��������ݣ������λ��ʼ���������D7~D0��
	for(i = 0;i < 8;i++)
	{
		dat <<= 1;
		ADCLK=1;//����ʱ�Ӷ�
		_nop_();
		_nop_();
		ADCLK=0;//����ʱ�Ӷ��γ�һ��ʱ������
		_nop_();
		_nop_();
		dat |= ADDO;
	}
	ndat = 0; 	   //��¼D0
	if(ADDO == 1)
	ndat |= 0x80;
	//���濪ʼ������ȡ��������ݣ���D1��D7�� 
	for(i = 0;i < 7;i++)
	{
		ndat >>= 1;
		ADCLK = 1;//����ʱ�Ӷ�
		_nop_();
		_nop_();
		ADCLK=0;//����ʱ�Ӷ��γ�һ��ʱ������
		_nop_();
		_nop_();
		if(ADDO==1)
		ndat |= 0x80;
	}	  
	ADCS=1;//����CS��,����ת��
	ADCLK=0;//����CLK��
	ADDI=1;//�������ݶ�,�ص���ʼ״̬
	if(dat==ndat)
	return(dat);
	else
	return 0;   
}

#endif

/*********************DS1302********************/
#if CONFIG_DS1302 == ENABLED

/******************
	ds1302 �ڲ�RAM   RAM0  1100 000R/W   1�� 0д
					 RAM1  1100 001R/W  
					       ....... 
					 RAM30 1111 110R/W   
********************/

unsigned char code Ds1302_write_add[]={0x80,0x82,0x84,0x86,0x88,0x8c,0x8a};   //д��ַ
unsigned char code Ds1302_read_add[] ={0x81,0x83,0x85,0x87,0x89,0x8d,0x8b};   //����ַ
unsigned char code Ds1302_init_ds[]  ={0x58,0x29,0x07,0x05,0x10,0x14,0x1}; 

void DelayMs_Ds1302(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}

/*************дһ�����ݵ���Ӧ�ĵ�ַ��***************/
void Ds1302_Write_Demo(unsigned char add,unsigned char dat)
{
	unsigned char i;
	rst = 1;			 //�Ѹ�λ���ø�
	for(i=0;i<8;i++)
	{				     //��λ��ǰ

		io = add & 0x01;    	
		add >>= 1;		 //�ѵ�ַ����һλ
		clk = 1;		 //ʱ�����ø�	 
		clk = 0;		 //ʱ�����õͿ�ʼд����
	}									 
	for(i=0;i<8;i++)
	{

		io = dat & 0x01;
		dat >>= 1;		 //����������һλ	
		clk = 1;		 //ʱ�����ø�
		clk = 0;		 //ʱ�����õͿ�ʼд����
	}
	rst = 0;			 //��λ�ߺϵ�
}


/*************�Ӷ�Ӧ�ĵ�ַ��һ�����ݳ���***************/
unsigned char Ds1302_Read_Demo(unsigned char add)
{
	unsigned char value,i;
	rst = 1;			 //�Ѹ�λ���ø�
	for(i=0;i<8;i++)
	{				     //��λ��ǰ
		clk = 0;		 //ʱ�����õͿ�ʼд����
		io = add & 0x01;    	
		add >>= 1;		 //�ѵ�ַ����һλ
		clk = 1;		 //ʱ�����ø�
	}		
	for(i=0;i<8;i++)
	{
		clk = 1;		 //ʱ�����ø�
		clk = 0;		 //ʱ�����õͿ�ʼ������
		value >>= 1;
		if(io == 1)
			value |= 0x80;
	}
	rst = 0;			 //��λ�ߺϵ�
	clk = 0;
	io = 0;
	return value;		 //���ض�����������
}

unsigned char BCD_Decimal(unsigned char bcd)//BCD��תʮ���ƺ���������BCD������ʮ����
{
	 unsigned char Decimal;
	 Decimal=bcd>>4;
	 return(Decimal=Decimal*10+(bcd&=0x0F));
}

/*************��Ҫ��ʱ�� ������ ��������***************/
//arry[7]
void Ds1302_Read_Time(unsigned char *arry)
{
	*arry      = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[0]));	//����
	*(arry+1)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[1]));	//����
	*(arry+2)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[2]));	//��ʱ
	*(arry+3)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[3]));	//����
	*(arry+4)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[4]));	//����
	*(arry+5)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[5]));	//����
	*(arry+6)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[6]));	//������
}

void Ds1302_Save(unsigned char  po, unsigned char  dat)
{
	unsigned char  temp;
	temp=(dat)/10*16+(dat)%10;//ʮ����ת����DS1302Ҫ���DCB��
	Ds1302_Write_Demo(0x8e,0x00);//����д����ֹд���� 
	Ds1302_Write_Demo(po,temp);//��DS1302��д�ּĴ���82Hд�������ķ�����BCD��
	Ds1302_Write_Demo(0x8e,0x80);//��д����	
}

/*************��Ҫд��ʱ�� ������ ��д��ds1302��***************/
void Ds1302_Write_Time(unsigned char *arry)
{
	Ds1302_Write_Demo(0x8e,0x00);			//��д����

	Ds1302_Write_Demo(Ds1302_write_add[0],0x80);	

	Ds1302_Write_Demo(Ds1302_write_add[0],arry[0]);	//д��
	Ds1302_Write_Demo(Ds1302_write_add[1],arry[1]);		//д��
	Ds1302_Write_Demo(Ds1302_write_add[2],arry[2]);		//дʱ
	Ds1302_Write_Demo(Ds1302_write_add[3],arry[3]);		//д��
	Ds1302_Write_Demo(Ds1302_write_add[4],arry[4]);		//д��
	Ds1302_Write_Demo(Ds1302_write_add[5],arry[5]);	//д����
	Ds1302_Write_Demo(Ds1302_write_add[6],arry[6]);	//д��
	Ds1302_Write_Demo(0x8e,0x80);			//�ر�д����
}

/*************�����ݱ��浽ds1302 RAM��**0-31*************/
void Ds1302_Write_ram(unsigned char add,unsigned char dat)
{
	add <<= 1;     //��ַ�Ǵӵڶ�λ��ʼ��
	add &= 0xfe;   //�����λ����  ��д������
	add |= 0xc0;   //��ַ�����λΪ 1  
	Ds1302_Write_Demo(0x8e,0x00);
	Ds1302_Write_Demo(add,dat);	
	Ds1302_Write_Demo(0x8e,0x80);
}


/*************�����ݴ�ds1302 RAM������**0-31*************/
unsigned char Ds1302_Read_ds1302ram(unsigned char add)
{
	add <<= 1;     //��ַ�Ǵӵڶ�λ��ʼ��
	add |= 0x01;   //�����λ��1  �Ƕ�����
	add |= 0xc0;   //��ַ�����λΪ 1  
	return(Ds1302_Read_Demo(add));	
}

/**********************����ds1302ʱ�亯��**********************/
void Ds1302_Set_time(unsigned char num,unsigned char *shi,unsigned char dat)	 //��ʱ
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

/*************��ʼ��ds1302ʱ��***************/
void Ds1302_Init()
{
	unsigned char i;
	rst = 0;	//��һ�ζ�д����ʱҪ��IOƷ�õ�
	clk = 0;
	io = 0;
	i = Ds1302_Read_ds1302ram(30);   
	if(i != 3)
	{	
		i = 3;
		Ds1302_Write_ram(30,i);			 //4050   4100		 3080

		Ds1302_Write_Demo(0x8e,0x00);	            //��д����
		for(i=0;i<7;i++)
			Ds1302_Write_Demo(Ds1302_write_add[i],Ds1302_init_ds[i]);	//�����λֵ0 ����ds1302����
		Ds1302_Write_Demo(0x8e,0x80);	//��д����
	}

	//read_time();		  //��ʱ��
	//if(miao >= 0x60)
	{
		Ds1302_Write_Demo(0x8e,0x00);	            //��д����
		Ds1302_Write_Demo(Ds1302_write_add[0],0x01);	//�����λֵ0 ����ds1302����
		Ds1302_Write_Demo(0x8e,0x80);	//��д����
		
	}

}

/*demo
uchar arry[7];
Ds1302_Read_Time(arry);
*/
#endif

/*********************DS18b02********************/
#if CONFIG_DS18b02 == ENABLED
/***********************18b20��ʼ������*****************************/

/********************************************************************
* ���� : delay_uint()
* ���� : С��ʱ��
* ���� : ��
* ��� : ��
***********************************************************************/


void delay_18B20(unsigned int q)
{
	while(q--);
}

void Ds18b02_Init()
{
	bit q;
	dq = 1;				//�������ø�
	delay_18B20(1);	    //15us
	dq = 0;				//����λ����
	delay_18B20(80);		//750us
	dq = 1;				//�������ø� �ȴ�
	delay_18B20(10);		//110us
	q = dq;				//��ȡ18b20��ʼ���ź�
	delay_18B20(20);		//200us
	dq = 1;				//�������ø� �ͷ�����
}

/*************д18b20�ڵ�����***************/
void DS18b20_Write(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{					 //д�����ǵ�λ��ʼ
		dq = 0;			 //�������õ�дʱ��϶��ʼ 
		dq = dat & 0x01; //��18b20����д������
		delay_18B20(5);	 // 60us
		dq = 1;			 //�ͷ�����
		dat >>= 1;
	}	
}

/*************��ȡ18b20�ڵ�����***************/
unsigned char Ds18b20_Read()
{
	unsigned char i,value;
	for(i=0;i<8;i++)
	{
		dq = 0;			 //�������õͶ�ʱ��϶��ʼ 
		value >>= 1;	 //�������ǵ�λ��ʼ
		dq = 1;			 //�ͷ�����
		if(dq == 1)		 //��ʼ��д���� 
			value |= 0x80;
		delay_18B20(5);	 //60us	��һ��ʱ��϶����Ҫ����60us��ʱ��
	}
	return value;		 //��������
}

/*************��ȡ�¶ȵ�ֵ ֵΪ3λ��������λΪС��***************/
unsigned int Ds18b20_Read_temp()
{
	unsigned int value;
	unsigned char low;			   //�ڶ�ȡ�¶ȵ�ʱ������жϵ�̫Ƶ���ˣ���Ӧ�ð��жϸ����ˣ������Ӱ�쵽18b20��ʱ��
	float tt=0;
	Ds18b02_Init();		   //��ʼ��18b20
	DS18b20_Write(0xcc);	   //����64λROM
	DS18b20_Write(0x44);	   //����һ���¶�ת������

	Ds18b02_Init();		   //��ʼ��18b20
	
	DS18b20_Write(0xcc);	   //����64λROM
	DS18b20_Write(0xbe);	   //������ȡ�ݴ�������
	
	low = Ds18b20_Read();	   //���¶ȵ��ֽ�
	value = Ds18b20_Read();  //���¶ȸ��ֽ�
	value <<= 8;		   //���¶ȵĸ�λ����8λ
	value |= low;		   //�Ѷ������¶ȵ�λ�ŵ�value�ĵͰ�λ��
	tt =value * 0.0625;	       //ת�����¶�ֵ 
  value= tt*10+0.5;     //�Ŵ�10���������������	
	return value/10;		   //���ض������¶� 
}

#endif


/*********************EEPROM********************/
#if CONFIG_EEPROM == ENABLED

/********STC89C51�����ֲ�*******
��һ������1000H--11FF
�ڶ�������1200H--13FF
����������1400H--15FF
����������1600H--17FF
����������1800H--19FF
����������1A00H--1BFF
����������1C00H--1DFF
�ڰ�������1E00H--1FFF
*****************/

/********STC89C52�����ֲ�*******
��һ������2000H--21FF
�ڶ�������2200H--23FF
����������2400H--25FF
����������2600H--27FF
����������2800H--29FF
����������2A00H--2BFF
����������2C00H--2DFF
�ڰ�������2E00H--2FFF
*****************/


#define RdCommand 0x01 //����ISP�Ĳ�������
#define PrgCommand 0x02
#define EraseCommand 0x03 
#define Error 1
#define Ok 0
#define WaitTime 0x01 //����CPU�ĵȴ�ʱ��
sfr ISP_DATA=0xe2;  //�Ĵ�������
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;


	

/* ================ �� ISP,IAP ���� ================= */
void ISP_IAP_enable_Demo(void)
{
	 EA = 0;       /* ���ж�   */
	 ISP_CONTR = ISP_CONTR & 0x18;       /* 0001,1000 */
	 ISP_CONTR = ISP_CONTR | WaitTime; /* д��Ӳ����ʱ */
	 ISP_CONTR = ISP_CONTR | 0x80;       /* ISPEN=1  */
}
/* =============== �ر� ISP,IAP ���� ================== */
void ISP_IAP_disable_Demo(void)
{
	 ISP_CONTR = ISP_CONTR & 0x7f; /* ISPEN = 0 */
	 ISP_TRIG = 0x00;
	 EA   =   1;   /* ���ж� */
}
/* ================ ���õĴ������� ==================== */
void ISPgoon_Demo(void)
{
	 ISP_IAP_enable_Demo();   /* �� ISP,IAP ���� */
	 ISP_TRIG = 0x46;  /* ����ISP_IAP�����ֽ�1 */
	 ISP_TRIG = 0xb9;  /* ����ISP_IAP�����ֽ�2 */
	 _nop_();
}
/* ==================== �ֽڶ� ======================== */
unsigned char byte_read_Demo(unsigned int byte_addr)
{
	EA = 0;
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);/* ��ַ��ֵ */
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	 ISP_CMD   = ISP_CMD & 0xf8;   /* �����3λ  */
	 ISP_CMD   = ISP_CMD | RdCommand; /* д������� */
	 ISPgoon_Demo();       /* ����ִ��  */
	 ISP_IAP_disable_Demo();    /* �ر�ISP,IAP���� */
	 EA  = 1;
	 return (ISP_DATA);    /* ���ض��������� */
}
/* ================== �������� ======================== */
void SectorErase_Demo(unsigned int sector_addr)
{
	 unsigned int iSectorAddr;
	 iSectorAddr = (sector_addr & 0xfe00); /* ȡ������ַ */
	 ISP_ADDRH = (unsigned char)(iSectorAddr >> 8);
	 ISP_ADDRL = 0x00;
	 ISP_CMD = ISP_CMD & 0xf8;   /* ��յ�3λ  */
	 ISP_CMD = ISP_CMD | EraseCommand; /* ��������3  */
	 ISPgoon_Demo();       /* ����ִ��  */
	 ISP_IAP_disable_Demo();    /* �ر�ISP,IAP���� */
}
/* ==================== �ֽ�д ======================== */
void byte_write_Demo(unsigned int byte_addr, unsigned char original_data)
{
	 EA  = 0;
//	 SectorErase(byte_addr);
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);  /* ȡ��ַ  */
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	 ISP_CMD  = ISP_CMD & 0xf8;    /* ���3λ */
	 ISP_CMD  = ISP_CMD | PrgCommand;  /* д����2 */
	 ISP_DATA = original_data;   /* д������׼�� */
	 ISPgoon_Demo();       /* ����ִ��  */
	 ISP_IAP_disable_Demo();     /* �ر�IAP���� */
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
	
	Interrp_Process = T_Process;
	TR2 = 1;
}

void timer2() interrupt 5
{
	TF2 = 0;
	TimeCtr++;
	if(TimeCtr >= Time_count)//1��
	{
		TimeCtr =0;
		Interrp_Process();

	}
		
}

#endif

/*********************Timer0��ʱ********************/
#if CONFIG_Timer0 == ENABLED

//	TMOD=0x21;             //��ʱ��T1�����ڼ���ģʽ1����ʱ��T0�����ڼ�ʱģʽ1��
//	TH1=(65536-46083)/256;    //��ʱ��T0�ĸ�8λ���ó�ֵ��ÿ50ms����һ���ж�
//	TL1=(65536-46083)%256;    //��ʱ��T0�ĵ�8λ���ó�ֵ��ÿ50ms����һ���ж�
//	TH0=(65536-20000)/256;    //��ʱ��T0�ĸ�8λ���ó�ֵ��ÿ50ms����һ���ж�
//	TL0=(65536-20000)%256;    //��ʱ��T0�ĵ�8λ���ó�ֵ��ÿ50ms����һ���ж�
static Timer0_Process  Timer_Process;
unsigned char RHCounter;
//��ʱ��0��ʼ��
void Timer0_Init_demo(Timer0_Process T_Process) 
{
    ET0 = 1;        //����ʱ��0�ж�
    TMOD = 0x01;       //��ʱ��������ʽѡ��
    TL0 = 0xFF;
    TH0 = 0x4B;     //��ʱ�������ֵ
    TR0 = 1;        //������ʱ��
	  EA = 1;
		Timer_Process = T_Process;
}

//��ʱ��0�ж�
void Timer0_ISR (void) interrupt 1 using 0 {
    TL0 = 0xFF;
    TH0 = 0x4B;     //��ʱ�������ֵ
    RHCounter++;

    if (RHCounter >= 40) //2��
		{
				Timer_Process();
        RHCounter = 0;
    }
}
#endif


/********************UART0 *********************/
#if CONFIG_UART0 == ENABLED
bit UART0_TXD_BUSY = 0;
unsigned char a;
void UART0_Send_Byte_Demo(unsigned char a)
{

	SBUF = a;
  UART0_TXD_BUSY = 1;	
	while(UART0_TXD_BUSY);	//�ȴ����ͳɹ�

}

char putchar(char c)
{
	UART0_Send_Byte_Demo(c);
	return c;
}


/*----------------------------
UART1 �����ַ���
-----------------------------*/
void UART0_Send_String_Demo(char *s)
{
	while(*s)//����ַ���������
	{
		UART0_Send_Byte_Demo(*s++);//���͵�ǰ�ַ�
	}
}


void UART0_Init_Demo()
{
	
	TMOD|= 0X20;		//T1  ��ʽ2  ��8λ   �Զ���װ   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600
	TR1=1; 		    // ��ʱ��1����  


	SM0=0;	    // ���ô��ڵĹ���ģʽ
	SM1=1; 	    //��ʽ1


	REN=1; 		 // �����ڽ������� 	 

  TI=1;
	ES=1; 	     // �����ж�Ӧ�� 
	EA=1;		 // �����ж� 

	
}

void UART0_ISR(void) interrupt 4
{
	
	
	if(RI)
	{
		RI = 0;
		
		a = SBUF;
		
				
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

//����ɨ�躯�� :    
//���ܣ�ֻɨ��һ������������Ϊ��С����  
//���ؼ�ֵ��
//         7    8    9    10	   //10:������۲����������	
//         4    5    6    11	   //11:����������һλ
//         1    2    3    12	   //12:ȥƤ
//         14   0    15   13	   //14:�޹��ܣ�������չ��15��С����  13��ȷ��

unsigned char Getkeyboard(void)
{
    unsigned char number = 0;
    unsigned char i;
	
	//������͵�ƽ
    ROW1=ROW2=ROW3=ROW4=0;
	//����������ȫΪ�ߣ���˵���м�����
	if ((COL1!=1)||(COL2!=1)||(COL3!=1)||(COL4!=1))
	{
	   //����0111
	   ROW1=0;
	   ROW2=ROW3=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 1;	   // 7
	   else if (COL2==0) return 2;	//	 8
	   else if (COL3==0) return 3;	 //	9
	   else if (COL4==0) return 10;	 //	 10
	   //����1011
	   ROW2=0;
	   ROW1=ROW3=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 4;	  //4
	   else if (COL2==0) return 5; //  5
	   else if (COL3==0) return 6;	// 6
	   else if (COL4==0) return 11;	 //	11
	   //����1101
	   ROW3=0;
	   ROW1=ROW2=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 7;  //1
	   else if (COL2==0) return 8;	  // 2
	   else if (COL3==0) return 9;	  //   3
	   else if (COL4==0) return 12;	  //   12
	   //����0111
	   ROW4=0;
	   ROW1=ROW2=ROW3=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 14;
	   else if (COL2==0) return 0;
	   else if (COL3==0) return 15;
	   else if (COL4==0) return 13;
	   //û�м�⵽�е͵�ƽ
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

//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
unsigned int GapValue=245;
void Delay_ms_HX711(unsigned int n)
{
	unsigned int  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}

unsigned long HX711_Read(void)	//����128
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
    count=count^0x800000;//��25�������½�����ʱ��ת������
	Delay__hx711_us();
	HX711_SCK=0;  
	return(count);
}
//****************************************************
//��ȡëƤ����
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
//����
//****************************************************
long Get_Weight()
{
	long Weight_Shiwu;
	Weight_Shiwu = HX711_Read();
	Weight_Shiwu = Weight_Shiwu - Weight_Maopi;		//��ȡ����
	
	Weight_Shiwu = (unsigned int)((float)Weight_Shiwu/GapValue); 	//����ʵ���ʵ������																
  return Weight_Shiwu;
}
#endif

/********************HRSR04 *********************/
#if CONFIG_HRSR04 == ENABLED

/*********************************************************/
// ���뼶����ʱ������time��Ҫ��ʱ�ĺ�����
/*********************************************************/
void HRSR04_DelayMs(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}
void HRSR04_Timer_init()
{
		TMOD = 0x01;											// ѡ��ʱ��0������ȷ���ǹ�����ʽ1��Ϊ�˳�����ģ����������ʱ�õģ�
}

unsigned int GetDistance(void)
{
	unsigned int ss;					// ���ڼ�¼��õľ���
	//uart�Ǳ߿�����TR0��֪��Ϊʲô
	TR0=0;
	TH0=0;
	TL0=0;

	Trig_P=1;					// ��������ģ��һ����ʼ����
	HRSR04_DelayMs(1);
	Trig_P=0;

	while(!Echo_P);		// �ȴ�������ģ��ķ�������
	TR0=1;						// ������ʱ������ʼ��ʱ
	while(Echo_P);		// �ȴ�������ģ��ķ����������
	TR0=0;						// ֹͣ��ʱ����ֹͣ��ʱ

	ss=((TH0*256+TL0)*0.034)/2;		// ����cm=��ʱ��us * �ٶ�cm/us��/2

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
	//TL0=0x00;	  //װ�ض�ʱ��1����
	//TR0=1;		  //��ʼ��ʱ
	//ET0=1;		  //���ܶ�ʱ��1

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
 - ����������
 - ����ģ�飺
 - ����˵����
 - ����˵����
 - ע��
*****************************************************************************************************/

/*****************************************************************************************************
 - �������������ڷ���һ֡����

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
 - �������������У��
 - ����ģ�飺
 - ����˵����
 - ����˵����
 - ע��				��У���˼·����
							���͵�ָ�ȥ����ʼ�ͽ��������м��6���ֽڽ����ۼӣ����ȡ����
							���ն˾ͽ����յ���һ֡���ݣ�ȥ����ʼ�ͽ��������м�������ۼӣ��ټ��Ͻ��յ���У��
							�ֽڡ��պ�Ϊ0�������ʹ�����յ���������ȫ��ȷ
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
 - �����������������ⷢ������������ƺͲ�ѯ��
 - ����ģ�飺�ⲿ
 - ����˵����CMD����ʾ����ָ����ѯָ�����������ѯ�����ָ��
							feedback���Ƿ���ҪӦ��[0������ҪӦ��1����ҪӦ��]
							data�����͵Ĳ���
 - ����˵����
 - ע��
*****************************************************************************************************/


void Uart_SendCMD(unsigned char CMD ,unsigned char feedback , unsigned int dat)
{
		//TR0 = 0;
		while(voice_busy == 0);
    Send_buf[0] = 0x7e;    //�����ֽ�
    Send_buf[1] = 0xff;    //�����ֽ�
    Send_buf[2] = 0x06;    //����
    Send_buf[3] = CMD;     //����ָ��
    Send_buf[4] = feedback;//�Ƿ���Ҫ����
    Send_buf[5] = (unsigned char)(dat >> 8);//datah
    Send_buf[6] = (unsigned char)(dat);     //datal
		Send_buf[9] = 0xef;
    DoSum(&Send_buf[1],6);        //У��
    SendCmd(10);       //���ʹ�֡����
		//TR0 =1;
}
//****************************************************
//MS��ʱ����(12M�����²���)
//****************************************************
void Delay_ms(unsigned int n) {
    unsigned int  i,j;
    for(i=0; i<n; i++)
        for(j=0; j<123; j++);
}
/* demo
	//���ڳ�ʼ��
	uart_init();
	EA = 1;
		//������ʾ
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x03,0,VOICE_INIT);//��ӭʹ���������ӳ�
	Delay_ms(500);
	while(1)
	{
		...
		Uart_SendCMD(0x03,0,(dat/100));//��λ
		Delay_ms(100);
		Uart_SendCMD(0x03,0,12);//��
		Delay_ms(100);		
	}
*/
#endif

/********************SHT11 *********************/
#if CONFIG_SHT11 == ENABLED
#define noACK 0				//�����������ݣ������ж��Ƿ����ͨѶ
#define ACK   1             //�������ݴ��䣻
							//��ַ  ����  ��/д
#define STATUS_REG_W 0x06   //000   0011    0
#define STATUS_REG_R 0x07   //000   0011    1
#define MEASURE_TEMP 0x03   //000   0001    1
#define MEASURE_HUMI 0x05   //000   0010    1
#define RESET        0x1e   //000   1111    0
//д�ֽڳ���
char s_write_byte(unsigned char value)   
{ 
	unsigned char i,error=0; 
	for (i=0x80;i>0;i>>=1)             //��λΪ1��ѭ������
	{ 
		if (i&value) DATA=1;          //��Ҫ���͵������룬���Ϊ���͵�λ
    	else DATA=0;                        
    	SCK=1;                          
    	_nop_();_nop_();_nop_();        //��ʱ3us 
    	SCK=0;
	}
	DATA=1;                           //�ͷ�������
	SCK=1;                            
	error=DATA;                       //���Ӧ���źţ�ȷ��ͨѶ����
	_nop_();_nop_();_nop_();
	SCK=0;        
	DATA=1;
	return error;                     //error=1 ͨѶ����
}
//���ֽڳ���
char s_read_byte(unsigned char ack)
{ 
	unsigned char i,val=0;
	DATA=1;                           //�ͷ�������
	for(i=0x80;i>0;i>>=1)             //��λΪ1��ѭ������
	{ 
		SCK=1;                         
    	if(DATA) val=(val|i);        //��һλ�����ߵ�ֵ 
    	SCK=0;       
	}
	DATA=!ack;                        //�����У�飬��ȡ������ͨѶ��
	SCK=1;                            
	_nop_();_nop_();_nop_();          //��ʱ3us 
	SCK=0;   
	_nop_();_nop_();_nop_();       
	DATA=1;                           //�ͷ�������
	return val;
}
//��������
void s_transstart(void)
// generates a transmission start 
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
{ 
   	DATA=1; SCK=0;                   //׼��
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
//���Ӹ�λ
void s_connectionreset(void)
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
{ 
	unsigned char i; 
	DATA=1; SCK=0;                    //׼��
	for(i=0;i<9;i++)                  //DATA���ָߣ�SCKʱ�Ӵ���9�Σ������������䣬ͨѸ����λ
	{ 
		SCK=1;
    	SCK=0;
	}
	s_transstart();                   //��������
}
//��λ����
char s_softreset(void)
// resets the sensor by a softreset 
{ 
	unsigned char error=0; 
	s_connectionreset();              //�������Ӹ�λ
	error+=s_write_byte(RESET);       //���͸�λ����
	return error;                     //error=1 ͨѶ����
}          
//��ʪ�Ȳ���
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode)
// �����¶Ȼ���ʪ��ת�����ɲ���mode����ת�����ݣ�
{ 
//	enum {TEMP,HUMI};		 //�Ѿ���ͷ�ļ��ж���
	unsigned error=0;
	unsigned int i;

	s_transstart();                   //��������
	switch(mode)                     //ѡ��������
    {	
		case TEMP : error+=s_write_byte(MEASURE_TEMP); break;		   //�����¶�
    	case HUMI : error+=s_write_byte(MEASURE_HUMI); break;		   //����ʪ��
    	default     : break; 
	}
	for (i=0;i<65535;i++) if(DATA==0) break; //�ȴ���������
	if(DATA) error+=1;                // �����ʱ��������û�����ͣ�˵���������� 
	*(p_value) =s_read_byte(ACK);    //����һ���ֽڣ����ֽ� (MSB)
	*(p_value+1)=s_read_byte(ACK);    //���ڶ����ֽڣ����ֽ� (LSB)
	*p_checksum =s_read_byte(noACK); //read CRCУ����
	return error;					 // error=1 ͨѶ����
}
//��ʪ��ֵ��ȱ任���¶Ȳ���
void calc_sth10(float *p_humidity ,float *p_temperature)
{ 
	
	const float C1=-8.0;              // 12λʪ�Ⱦ��� ������ʽ
	const float C2=+0.0405;           // 12λʪ�Ⱦ��� ������ʽ
	const float C3=-0.0000028;        // 12λʪ�Ⱦ��� ������ʽ
	const float T1=+0.01;             // 14λ�¶Ⱦ��� 5V����  ������ʽ
	const float T2=+0.00008;          // 14λ�¶Ⱦ��� 5V����  ������ʽ
	
	float rh=*p_humidity;             // rh:      12λ ʪ�� 
	float t=*p_temperature;           // t:       14λ �¶�
	float rh_lin;                     // rh_lin: ʪ�� linearֵ
	float rh_true;                    // rh_true: ʪ�� tureֵ
	float t_C;                        // t_C   : �¶� ��
	
	t_C=t*0.01 - 40;                  //�����¶�
	rh_lin=C3*rh*rh + C2*rh + C1;     //���ʪ�ȷ����Բ���
	rh_true=1*(T1+T2*rh)+rh_lin;   //���ʪ�ȶ����¶������Բ���
	if(rh_true>100)rh_true=100;       //ʪ���������
	if(rh_true<0.1)rh_true=0.1;       //ʪ����С����

	*p_temperature=t_C;               //�����¶Ƚ��
	*p_humidity=rh_true;              //����ʪ�Ƚ��
}

/*demo
void main()
{
	unsigned int temp,humi;		//�����¶Ⱥ�ʪ�ȱ���
	value humi_val,temp_val;		//����������ͬ�壬һ������ʪ�ȣ�һ�������¶�
	unsigned char error;		    //���ڼ����Ƿ���ִ���
	unsigned char checksum;			//CRC			 
	uchar wendu[6];				 	//���ڼ�¼�¶�
	uchar shidu[6];				 	//���ڼ�¼ʪ��	
	value humi_val,temp_val;		//����������ͬ�壬һ������ʪ�ȣ�һ�������¶�
	while(1)
	{
		error=0;					   //��ʼ��error=0����û�д���
		error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP); //�¶Ȳ���
		error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI); //ʪ�Ȳ���
    if(error!=0) 
			s_connectionreset();                 ////�����������ϵͳ��λ		
		else
		{
				humi_val.f=(float)humi_val.i;                   //ת��Ϊ������
     		temp_val.f=(float)temp_val.i;                   //ת��Ϊ������
     		calc_sth10(&humi_val.f,&temp_val.f);            //�������ʪ�ȼ��¶�
//   		dew_point=calc_dewpoint(humi_val.f,temp_val.f); //����e dew_point
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
		//��ʱ������forѭ��		  
		if(U8FLAG==1)break;
		//�ж�����λ��0����1	 

		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 

		U8comdata<<=1;
		U8comdata|=U8temp;        //0
	}//rof

}

	//--------------------------------
	//-----ʪ�ȶ�ȡ�ӳ��� ------------
	//--------------------------------
	//----���±�����Ϊȫ�ֱ���--------
	//----�¶ȸ�8λ== U8T_data_H------
	//----�¶ȵ�8λ== U8T_data_L------
	//----ʪ�ȸ�8λ== U8RH_data_H-----
	//----ʪ�ȵ�8λ== U8RH_data_L-----
	//----У�� 8λ == U8checkdata-----
	//----��������ӳ�������----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

char DHT11_RH(unsigned char* arry)
{
	unsigned char U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
	//��������18ms 
	DTH_PIN=0;
	Delay(180);
	DTH_PIN=1;
	//������������������ ������ʱ20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//������Ϊ���� �жϴӻ���Ӧ�ź� 
	DTH_PIN=1;
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	if(!DTH_PIN)		 //T !	  
	{
		U8FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
		while((!DTH_PIN)&&U8FLAG++);
		U8FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
		while((DTH_PIN)&&U8FLAG++);
		//���ݽ���״̬		 
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
		//����У�� 

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
		Lcd1602_Display_Three_bit(0,0,RH_Value[0]);//������ʪ�ȣ�ֻȡ��������
		Lcd1602_Display_Three_bit(1,0,RH_Value[2]);
	}
}
*/
#endif


/********************LCD12864 *********************/
#if CONFIG_LCD12864_LIB == ENABLED

/********************************************
Description:  LCD12864 ���� ,���ô��з�ʽ,
********************************************/ 


#define BIT(n)	(1<<(n))
#define SID_0   Lcd_Rw=0;
#define SID_1   Lcd_Rw=1; 
#define SCLK_0  Lcd_En=0;
#define SCLK_1  Lcd_En=1; 
//15�� PSB �ӵ͵�ƽ

//����  delay(uchar z)
//������  ��ʱ

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
    Lcd_WriteCom(0x34);//�������ã�һ����8λ���ݣ�����ָ�
    Lcd_WriteCom(0x30);//0000,1100  ������ʾ���α�off���α�λ��off
    Lcd_WriteCom(0x01);//0000,0001 ��DDRAM
    Lcd_WriteCom(0x06);//0000,0010 DDRAM��ַ��λ
    Lcd_WriteCom(0x0c);//1000,0000 �趨DDRAM 7λ��ַ000��0000����ַ������AC//     
}

/*****************************
�����ַ���
*****************************/
//void show_str(uchar const *s)//��AVRȥ��const
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
		 unsigned char ta[]={0,0,'\0'};	  //��һ��������װ��
	   list=list &0x07;			       //������ 0-7��
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//��һ��
				case 2:   Lcd_WriteCom(0x90+list);break;	//�ڶ���
				case 3:   Lcd_WriteCom(0x88+list);break;	//������
				case 4:   Lcd_WriteCom(0x98+list);break;	//������
				default : break;
	
	   }
	 for(i=2;i>0;i--)
	 {							  //ѭ���Ĵΰ��ĸ����Ӹߵ���װ��ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 
void Lcd_Display3data(unsigned char line,unsigned char list,unsigned int Date)
{
		unsigned char i;
		 unsigned char ta[]={0,0,0,0,'\0'};	  //��һ��������װ��
	   list=list &0x07;			       //������ 0-7��
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//��һ��
				case 2:   Lcd_WriteCom(0x90+list);break;	//�ڶ���
				case 3:   Lcd_WriteCom(0x88+list);break;	//������
				case 4:   Lcd_WriteCom(0x98+list);break;	//������
				default : break;
	
	   }
	 for(i=3;i>0;i--)
	 {							  //ѭ���Ĵΰ��ĸ����Ӹߵ���װ��ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 


 

 ////////////////////////////////////////////////////////////////////
//����	  Lcd_init(uchar com)
//����    ��ȷ��Ļ��ʾ�ַ���
//����    line  Һ�����ĵڼ���  list  �ڼ���λ�ÿ�ʼд �����8���У�  *pҪд���ַ���
void  Lcd_ShowSring(unsigned char line,unsigned char list,unsigned char *p)
{
	 switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//��һ��
				case 2:   Lcd_WriteCom(0x90+list);break;	//�ڶ���
				case 3:   Lcd_WriteCom(0x88+list);break;	//������
				case 4:   Lcd_WriteCom(0x98+list);break;	//������
				default : break;
	
	   }

	    Lcd_String(p);

}

/*demo

  LCDInit();	//lcd12864��ʼ��
	Lcd_ShowSring(1,0,"������ʪ�ȹ���");
  Lcd_ShowSring(2,0,"�¶�:");
	Lcd_ShowSring(3,0,"ʪ��:");
	Lcd_ShowSring(4,0,"���:");
	while(1);

*/
#endif


/********************ESP8266*********************/
#if CONFIG_ESP8266 == ENABLED
unsigned char a;
bit UART0_TXD_BUSY = 0;
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
//*********������*****************
//9600bps
void ESP8266_uart_init()
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
}
void UartSendByte(unsigned char byte)
{
	SBUF = byte;
  UART0_TXD_BUSY = 1;	
	while(UART0_TXD_BUSY);	//�ȴ����ͳɹ�
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
	if(TI)
	{
		TI=0;
		UART0_TXD_BUSY = 0;		
	}	
}


/******************************************************************** 
���ƣ�WIFIģ�����ú���  ����: ����ģ�飬�Ա����ʵ�����߽���Ϳ���  
********************************************************************/ 
void ESP8266_Set(unsigned char *puf) 
	{                        	// ����ָ��*pufָ���ַ�������
    while(*puf!='\0') 
		{  		//�����ո�����ѭ��
        UartSendByte(*puf);  		//��WIFIģ�鷢�Ϳ���ָ�
        Esp8266_Delay_Ms(5);
        puf++;
    }
    Esp8266_Delay_Ms(5);
    UartSendByte('\r'); 			//�س�
    Esp8266_Delay_Ms(5);
    UartSendByte('\n');   			//����
}
void Esp8266_init()
{
		ESP8266_uart_init();
		Esp8266_Delay_Ms(100);
	  ESP8266_Set("AT+CWMODE=2"); 							//����·����ģʽ1 station,ģʽ2 AP,ģʽ3 station+AP���ģʽ   ����ǰwifi�Ĳ��������ó�9600
    Esp8266_Delay_Ms(300);
//    ESP8266_Set("AT+RST"); 									//��������wifiģ��
    Esp8266_Delay_Ms(300);
//    ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  ����ģ��SSID:WIFI, PWD:���� ����ȫ���ͼ���ģʽ��WPA2-PSK��
    ESP8266_Set("AT+CWSAP=\"wifi_yuxia\",\"12345678\",11,4");
    Esp8266_Delay_Ms(300);
//    ESP8266_Set("AT+CIPMUX=1");								//����������ģʽ�����������ͻ��˽���
    ESP8266_Set("AT+CIPMUX=1");								//����������ģʽ
    Esp8266_Delay_Ms(300);
    ESP8266_Set("AT+CIPSERVER=1,5000");  					//����TCP/IP ʵ�ֻ�������//���� 	ESP8266_Set("AT+CIPSERVER=1,5000");
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
		ESP8266_Set("AT+CIPSEND=0,34\r\n");	   ////�����ַ�����  
	}else if(Cnt1 >= 40)
	{
		Cnt1 = 0;
		buff[0]= 'H';
		buff[1]= ':';
		buff[2]= Temp_Value/100%10+0x30;
		buff[3]= Temp_Value/10%10+0x30;
		buff[4]= Temp_Value%10+0x30;
		buff[5]= ',';
		buff[6]= RH/100%10+0x30;
		buff[7]= RH/10%10+0x30;
		buff[8]= ',';
		buff[9]= RH%10+0x30;
		buff[10]= ',';
		buff[11]= PH_Value/100%10+0x30;
		buff[12]= PH_Value/10%10+0x30;
		buff[13]= PH_Value%10+0x30;
		buff[14]= ',';
   	buff[15]= zt+0x30;
		buff[16]= ',';
   	buff[17]= tempH+0x30;
		buff[18]= ',';	
   	buff[19]= tempL+0x30;
		buff[20]= ',';	
   	buff[21]= waterH+0x30;
		buff[22]= ',';	
   	buff[23]= waterR+0x30;
		buff[24]= ',';			
		buff[25]= 'E';	
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

void delayms(unsigned char ms)// ��ʱ�ӳ��� 
{      
	unsigned char j;
	while(ms--)
	{
		for(j = 0; j < 120; j++);
	}
}
bit flag_xh = 0;
////////////////���������ӳ��򣬷�����ַ��ADDR����////
void play(unsigned int addr)
{
	unsigned char y;
	flag_xh = 0;
	SS=0;
	MOSI=0;//���Ϳ�ʼ
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
	}//���ͽ���
	SS=1;//�ϵ����
	delayms(50);
	SS=0;
	MOSI=0;//���͵�ַ
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
	}//���͵�ַ����
	MOSI=0;//����
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
	MOSI=0;//����
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
//////////////////////////lu�������ӳ��򣬵�ַ��ADDR����/////////////////////////
void rec(unsigned int addr)                
{
 	unsigned int y;	
	SS=0;
	MOSI=0;//���Ϳ�ʼ
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
	}//���ͽ���
	SS=1;//�ϵ����
	delayms(50);
	SS=0;
	MOSI=0;//���Ϳ�ʼ
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
	}//���ͽ���
	SS=1;//�ϵ����
	delayms(50);
	delayms(50);
	SS=0;
	MOSI=0;//���͵�ַ
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
	}//���͵�ַ����
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
	MOSI=0;//����
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
//-----------����ģ��ϵͳ����-----------------------------------------------------------
//------------------------------------------------------------------------------------
// ���������볣��
#define GAP_ZERO     0x00
#define GAP_VSMALL   0x01
#define GAP_SMALL    0x02
#define GAP_MEDIUM   0x03
#define GAP_BIG      0x04
// ��������������
#define TURN_ZERO    0x80
#define TURN_VSMALL  0x81
#define TURN_SMALL   0x82
#define TURN_MEDIUM  0x83
#define TURN_BIG     0x84



//-----------����ģ��ϵͳ����-----------------------------------------------------------
//------------------------------------------------------------------------------------
//unsigned char Temp_H,Temp_L;

//unsigned int sum;			  //10��ADֵ���ۺϱ���
//unsigned char RH,RH_H=12,RH_L=8,state,ms,cs;  //��ǰˮλ��  ˮλ���ޣ����ޣ�  �����������50ms����   ��cs Ϊ�ƴ�������    ��
//bit beep1,zt,s1;	  //������־λ��   ����ģʽ��־λ��   ��˸��־λ

//int Temperature;
 


//-----------����ģ��ϵͳ����-----------------------------------------------------------
//------------------------------------------------------------------------------------
//-------------���峣��----------------------------------------------------------------
#define MU_MAX 0XFF            //ģ���ȵ����ֵΪ0XFF������1
#define RULE_TOT 10            //����������
#define MF_TOT 5               //��Ա�����ĸ���
#define IO_NUM 0x07
#define LABEL_NUM 0x70
#define DEFAULT_VALUE 0x00
//----------------�������ݿ�-----------------------------------------------------------
unsigned char code output_memf[MF_TOT]={0, 15, 35, 60, 102};// OUTPUT TURNING NUMBER:
                                                            // ZERO, VSMALL, SMALL, MEDIUM, BIG
                                                            // ���빦�ܺ����Ե�бʽ��ʽ�洢. ��һά��Ա������ŵڶ�ά�ǵ�бʽ����
unsigned char code input_memf[MF_TOT][4]={                  //���빦�ܺ���
                                            { 0x00, 0x00, 0x00, 0x0d }, // VSLOW
                                            { 0x00, 0x0d, 0x14, 0x0d }, // SLOW
                                            { 0x1e, 0x0d, 0x32, 0x0d }, // MEDIUM
                                            { 0x3C, 0x0d, 0x50, 0x0d }, // FAST
                                            { 0x50, 0x09, 0x6e, 0x00 }  // VFAST
                                          };

//-----------����ģ��ϵͳ����-----------------------------------------------------------
//------------------------------------------------------------------------------------
//-----------����ģ��ϵͳ����-----------------------------------------------------------
unsigned char code rules[RULE_TOT]={ 
                                        // if...  then...
                                        GAP_ZERO,TURN_ZERO,
                                        GAP_VSMALL,TURN_VSMALL,
                                        GAP_SMALL,TURN_SMALL,
                                        GAP_MEDIUM,TURN_MEDIUM,
                                        GAP_BIG,TURN_BIG
                                   };


 //-----------����ģ��ϵͳ����-----------------------------------------------------------
//------------------------------------------------------------------------------------
 //-----------���������-----------------------------------------------------------------
unsigned char outputs[MF_TOT],fuzzy_out;  //ģ�����muֵ
//-----------�ӳ�����ͷ����-----------------------------------------------------------
void fuzzy_engine(unsigned char);
unsigned char compute_memval(unsigned char,unsigned char);
void defuzzify(void);

/***************************************************************************************************************/
unsigned char compute_memval(unsigned char input,unsigned char label)
 {
    int data temp;
    if (input < input_memf[label][0])
    {                                 // ������벻��������uֵΪ0
         return 0;
    }
    else
    {
        if (input < input_memf[label][2])
        {
             temp=input;              // �õ�бʽ����mu
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
             {                     // ������������1
                return temp;       // ���ؼ�����
             }
             else
             {
                return MU_MAX;     // ȷ��muֵ�ڷ�Χ��
             }
        }
        else
        {                           // �������ڵڶ���б����
            temp=input;               // �õ�бʽ�������� mu
            temp-=input_memf[label][2];
            temp*=input_memf[label][3];
            temp=MU_MAX-temp;
            if (temp < 0)
            {                      // ȷ�������С��0
                  return 0;
            }
            else
            {
                  return temp;        // muΪ�� �C ���ؽ��
            }
        }
    }
    return 0;
}
/*******************************************************************************
Function: defuzzify
Description: ����ģ����������Ĳ����ú�������
             ת���ɿɱ�ϵͳʹ�õ������
Parameters: ��.
Returns: ��.
Side Effects: outputs[][] ���鱻����.
*******************************************************************************/
void defuzzify(void)
{
    unsigned long numerator, denominator;
    unsigned char j;
    numerator=0;                         // �ָ�����ֵ
    denominator=0;
    for (j=0; j<MF_TOT; j++)
    {                                // �����ܺ�ֵ
        numerator+=(outputs[j]*output_memf[j]);
        denominator+=outputs[j];
        outputs[j]=0;                        // ���������Ϊ�ο�ʹ��
        if (denominator)
        {                                     // ȷ����ĸ��0�����������
            fuzzy_out=numerator/denominator;  // ȷ�� COG
        }
        else
        {
            fuzzy_out=DEFAULT_VALUE;         // û�й��򱻴���
        }
    }
}
/*******************************************************************************
Function: fuzzy_engine
Description: ʵʩ������еĹ���
Parameters: ��
Returns: ��.
Side Effects: ��
********************************************************************************/
unsigned char bdata clause_val;                        // ���浱ǰ�ķ�֧���п��ٷ���
sbit clause_type = clause_val^7;                       // ��ʾ��֧�Ƿ���������֧�����ǽ����֧
void fuzzy_engine(unsigned char input)
{
    bit then;                                       // �����ڷ������ʱ��λ
    unsigned char if_val,                           // ���浱ǰ������������֧�е�ֵ
                  clause,                           // ������е�ǰ�ķ�֧
                      mu,                           // ���浱ǰ��֧�е�ֵ
                 label=0;                           // ������ʹ�õĳ�Ա����
                  then=0;                           // ���һ����֧��������֧
           if_val=MU_MAX;                           // max out mu for the first rule
    for (clause=0; clause<RULE_TOT; clause++)
    {                                               // ����ÿ������
        clause_val=rules[clause];                   // ���뵱ǰ�ķ�֧
        if (!clause_type)
        {                                           // ��ǰ�ķ�֧�ǲ���������֧
            if (then)
            {                                       // �Ƿ����ڷ������...
                then=0;
                if_val=MU_MAX;                      // ��λmu
            }
            mu=compute_memval(input, label);        // �õ�������֧��ֵ
            if_val=mu;
            label++;
        }
        else
        {                                       // ��ǰ��֧�ǽ��
            then=1;            // ��λ��־λ,�����ǰ�����mu�Ȳο���ֵҪ��,�������ֵ��Ϊ�µ�ģ�����
            if (outputs[clause_val&0x07] < if_val)
            {
                outputs[clause_val&0x07]=if_val;
            }
        }
    }
    defuzzify(); // ��COG��������ģ������ͷ�ģ�����
 }

/*demo
		if(Temperature <= Temp_L)//С���趨ֵʱ������ģ������
		{
						
		 //ģ������
			fuzzy_engine((Temp_L - Temperature)*10);
		 
		 if(fuzzy_out)  //����ģ�����������������״̬
		 {
				LED_3_BUF = led_3=0;		//��ʾ��Ӧ��ָʾ��
		 }
		 else
		 {
			 LED_3_BUF = led_3=0;		//��ʾ��Ӧ��ָʾ�� 
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
	EX0=1;     //���ж�0
	IT0=1;     //�ж�0Ϊ���ش���
	EA=1;     //�����ж�
	EX0_Process = T_Process;
}

void EX1_INIT(EX0_1_Process T_Process)
{
	EX1=1;     //���ж�0
	IT1=1;     //�ж�0Ϊ���ش���
	EA=1;     //�����ж�
	EX1_Process = T_Process;
}


//�ⲿ0�ж��Ӻ���
void wb0() interrupt 0  //����ʱ�俪ʼ/��ͣ
{
	EX0_Process();
}
//�ⲿ1�ж��Ӻ���
void wb1() interrupt 2   //24s����ʱ���¿�ʼ
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



//��ʱ����
void delay(unsigned char t)
{
	unsigned char i,j;
	for(i=0;i<t;i++)
		for(j=0;j<10;j++);
}

//д�����
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
//д���ݺ���
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

//��������
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
��λ��������λһ���֣�
����pagΪ����0~3��
colΪ������col=16i��i=0~8
*hzkΪҪ��ʾ�����ݣ�
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
��λ��������λһ���ֽڣ�
����pagΪ����0~3��
colΪ������col=8i��i=0~16
*hzkΪҪ��ʾ�����ݣ�
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

//lcd��ʼ������
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

//�軨�Զ���ˮϵͳ
char code pen[]={
0x20,0x20,0x10,0x08,0x94,0x72,0x10,0x90,0x13,0xF4,0x08,0x10,0x20,0x60,0x20,0x00,
0x40,0x40,0x7D,0x45,0x44,0x7C,0x44,0x44,0x45,0x7C,0x44,0x44,0x7E,0x44,0x40,0x00
};

char code jiao[]={
0x10,0x21,0x62,0x06,0x80,0x08,0x88,0x8B,0x5C,0x24,0x54,0x84,0x86,0xE4,0x00,0x00,
0x04,0x04,0xFE,0x01,0x80,0x82,0x42,0x3E,0x02,0x02,0x7E,0x82,0x82,0x82,0xE0,0x00
};


//��ʾ��0������1������2������3������4������5������6������7������8������9��
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
	unsigned int temp,humi;		//�����¶Ⱥ�ʪ�ȱ���
	value humi_val,temp_val;		//����������ͬ�壬һ������ʪ�ȣ�һ�������¶�
	unsigned char error;		    //���ڼ����Ƿ���ִ���
	unsigned char checksum;			//CRC			 
	unsigned char  wendu[6];				 	//���ڼ�¼�¶�
	unsigned char  shidu[6];				 	//���ڼ�¼ʪ��		
void System_Show()		//��Ϣ��ʾ
{
	cs1=1;cs2=0;
	hz_disp16(0,0,pen);		//�軨�Զ�

			 
	cs1=0;cs2=1;
	hz_disp16(0,0,jiao);	//��ˮϵͳ


}
void main()
{
	Lcd_Init();
	
	while(1)
	{
		error=0;					   //��ʼ��error=0����û�д���
		error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP); //�¶Ȳ���
		error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI); //ʪ�Ȳ���
		if(error!=0)
			s_connectionreset();                 ////�����������ϵͳ��λ
		else
		{ 		
		humi_val.f=(float)humi_val.i;                   //ת��Ϊ������
		temp_val.f=(float)temp_val.i;                   //ת��Ϊ������
		calc_sth10(&humi_val.f,&temp_val.f);            //�������ʪ�ȼ��¶�
		//   		dew_point=calc_dewpoint(humi_val.f,temp_val.f); //����e dew_point
		temp=temp_val.f*10;
		humi=humi_val.f*10;	

      		wendu[0]=(temp/1000)/1000;     		//�¶Ȱ�λ 
      		wendu[1]=(temp%1000)/100;     	//�¶�ʮλ	
   			  wendu[2]=(temp%100)/10;			//�¶ȸ�λ
      		wendu[3]=0x2E;						//С����
   			  wendu[4]=temp%10;				//�¶�С������һλ		
			 
			    shidu[0]=(humi/1000)/1000;     		//ʪ�Ȱ�λ
      		shidu[1]=(humi%1000)/100;     	//ʪ��ʮλ	
   			  shidu[2]=(humi%100)/10;			//ʪ�ȸ�λ
      		shidu[3]=0x2E;						//С����
   			  shidu[4]=humi%10;				//ʪ��С������һλ	 

					cs1=0;cs2=1;
					hz_disp8(2,0,base_num[wendu[0]]);	//��ʾ�¶�
					hz_disp8(2,8,base_num[wendu[1]]);
					hz_disp8(2,16,base_num[wendu[2]]);
					hz_disp8(2,24,base_num[14]);
					hz_disp8(2,32,base_num[wendu[4]]);
					hz_disp8(2,40,base_num[12]);

					hz_disp8(4,0,base_num[shidu[0]]);	//��ʾʪ��
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


//���ⷢ��ܵ��������
static bit OP;
//��ʱ������
static unsigned int count;
//��ֹ��ʱ������
static unsigned int  endcount;
//���ⷢ�ͱ�־
static unsigned char flag;
//16λ��ַ ��һ�ֽ�
char iraddr1;
//16λ��ַ �ڶ��ֽ�
char iraddr2;

unsigned char Menu_Count =0;

//��ʱ��0�жϴ�����
void timeint(void) interrupt 1
{
	//�趨��ʱ����ֵ
	TH0=0xff;
	TL0=0xe6;
	
	//�жϼ����ۼ�
	count++;
	if(flag==1)
	{
		OP=~OP;
	}
	else
	{
		OP=0;
	}
	HL=OP;
}

//�������ݺ���
//���͵���ʱʱ�������(endcount)������12MHZ��ֵ
void SendIRdata(char p_irdata)
{
	int i;
	char irdata=p_irdata;
	
	//����9ms����ʼ��
	endcount=223;
	flag=1;
	count=0;
	while(count<endcount);

	//����4.5ms�Ľ����
	endcount=117;
	flag=0;
	count=0;
	do{}while(count<endcount);

	//����16λ��ַ��ǰ��λ
	irdata=iraddr1;
	for(i=0;i<8;i++)
	{
		//�ȷ���0.56ms��38K���Ⲩ(�������е�0.56ms�ĵ͵�ƽ��
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//ֹͣ���ͺ����ź�(�������еĸߵ�ƽ)
		if(irdata-(irdata/2)*2)//�ж϶����Ƶĸ�λ��1����0
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

	//����16λ��ַ�ĺ��λ
	irdata=iraddr2;
	for(i=0;i<8;i++)
	{
		//�ȷ���0.56ms��38K���Ⲩ(�������е�0.56ms�ĵ͵�ƽ��
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//ֹͣ���ͺ����ź�(�������еĸߵ�ƽ)
		if(irdata-(irdata/2)*2)//�ж϶����Ƶĸ�λ��1����0
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


	//����8λ����
	irdata=p_irdata;
	for(i=0;i<8;i++)
	{
		//�ȷ���0.56ms��38K���Ⲩ(�������е�0.56ms�ĵ͵�ƽ��
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//ֹͣ���ͺ����ź�(�������еĸߵ�ƽ)
		if(irdata-(irdata/2)*2)//�ж϶����Ƶĸ�λ��1����0
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


	//����8λ���ݷ���
	irdata=~p_irdata;
	for(i=0;i<8;i++)
	{
		//�ȷ���0.56ms��38K���Ⲩ(�������е�0.56ms�ĵ͵�ƽ��
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//ֹͣ���ͺ����ź�(�������еĸߵ�ƽ)
		if(irdata-(irdata/2)*2)//�ж϶����Ƶĸ�λ��1����0
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
	//������Ϣ
	endcount=13;
	flag=1;
	count=0;
	do{}while(count<endcount);
	flag=0;
}


void IR_SEND_INIT()
{
	//��ʼ��
	count=0;
	flag=0;
	OP=0;
	HL=0;
	//����ܳ�ʼ��
	//���жϿ�
	EA=1;
	//���ö�ʱ��0��1Ϊ16λģʽ
	TMOD=0x11;
	//��ʱ��0�ж�����
	ET0=1;
	//�趨��ʱ��С 38K �ȼ��� 26us�ж�һ��             
	TH0=0xff;
	TL0=0xe6;
	//��ʼ����
	TR0=1;
	
	//д16λ��ַ
	iraddr1=0;
	iraddr2=255;
}



#endif

#if CONFIG_IR_REVICE == ENABLED

unsigned char ir_num;	
#define Imax 14000    //�˴�Ϊ����Ϊ11.0592ʱ��ȡֵ, 
#define Imin 8000    //��������Ƶ�ʵľ���ʱ,û
#define Inum1 1450    //Ҫ�ı���Ӧ��ȡֵ��
#define Inum2 700 
#define Inum3 3000 

unsigned long f=0;
unsigned long m,Tc;	  // ��������
unsigned char IrOK;		// ��������
unsigned char Im[4]={0x00,0x00,0x00,0x00};	 //IRCOM[0]~IRCOM[3]����ַ�롢��ַ���롢�����롢��������(����ʮ������)

/*******************************************************************/
void IR_Init(void)
{
	TMOD|=0x01;		//��ʱ��0�Ͷ�ʱ��1���Ƿ�ʽ1,16λ��ʱ��
	TL0 = 0xb0;     
	TH0 = 0x3c;     //��ʱ�������ֵ
	IT0=1,//�½��ش���
	EX0=1;//�ⲿ�ж�0     ʹ��λ	
	TR0=1;
	//ET0 = 1;        //����ʱ��0��
	EA=1;//	���ж�
} 



void Timer0_ISR (void) interrupt 1 using 1
{

	TH0=0X3C;							//�ظ���ֵ
	TL0=0XBA;

}
void int0() interrupt 0	using 1  		//�ⲿ�ж�0 ����
{
	Tc=TH0*256+TL0; //��ʱ�����ֻ��TC ֵ                                              //��ȡ�ж�ʱ����ʱ��
	TH0=0; 
	TL0=0;              //��ʱ�ж���������

	if((Tc>Imin)&&(Tc<Imax))//�������ж� ����ʱ��Ա�0.9MS	
	{  
		m=0;
		f=1;
		//ET0 = 1;

		return;
	}       //�ҵ���ʼ��

	if(f==1)
	{
		if(Tc>Inum1&&Tc<Inum3) //�ж���0�û���1 ��0 1.125MS ��1  2.25MS
		{
		Im[m/8]=Im[m/8]>>1|0x80; m++;  //��0
		}
		if(Tc>Inum2&&Tc<Inum1) 
		{
		Im[m/8]=Im[m/8]>>1; m++; //	��1
		}
		if(m==32) 	//32λ�洢���
		{
		m=0;  
		f=0;
		if(Im[2]==~Im[3])  //������
		{	 
		IrOK=1; 	//OK ���
		}
		else IrOK=0;   //ȡ����ɺ��ж϶����Ƿ���ȷ
		}
		//׼������һ��
	}
	if(IrOK)
	{
		switch(Im[2])
		{
			case (0x45): ir_num=1;break;
			case (0x46): ir_num=2;break;
			case (0x47): ir_num=3;break;
			case (0x44): ir_num=4;break;	 //
			case (0x40): ir_num=5;break;		
			case (0x43): ir_num=6;break;
			case (0x07): ir_num=7;break;	  
		}
	}	

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

#if CONFIG_LCD12864_PLUS== ENABLED


#if CONFIG_CH == ENABLED
unsigned char code zm8x16_index[]="0123456789: |-+.<";//�ִ�����
unsigned char code zm8x16_Table[][16]={
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
unsigned char code zm8x16_index[]="0123456789: |-+.<abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//�ִ�����
unsigned char code zm8x16_Table[][16]={
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
unsigned char code zm16x16_index[]="  ��ӭʹ������������������";//�ִ�����
unsigned char code zm16x16_Table[][32]={
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
/** LCMæ��� **/
void busy12864(){
	lcdDat=0xff;    //������1����ֹ����
	rs=0; rw=1;	   //�á��������ģʽ
	//en=1; while(lcdDat&0x80); en=0;//æ�ȴ�
}
/** д���� ������comDatΪҪ���͵����� **/
void WriteCom(unsigned char comDat){  
    busy12864();     		//æ����ȴ�
	rs=0;rw=0;				//�á����д��ģʽ
    lcdDat=comDat;en=1;en=0;//�ͳ������ʹ֮��Ч
}
/** д���� ������datΪҪ���͵����� **/
void WriteDat(unsigned char dat){  
    busy12864();  		 	//æ����ȴ�
	rs=1;rw=0;			  	//�á����ݡ�д��ģʽ
    lcdDat=dat;en=1;en=0;	//�ͳ����ݣ���ʹ֮��Ч
}
/** ��ʼ��12864 **/
void Init12864(){
	lcdDat=0xff;   //������1����ֹ����
	rs=0; rw=1;	   //�á��������ģʽ
	//en=1; while(lcdDat&0x10); en=0;//�ȴ���λ���
	WriteCom(0x3f);	  //����ʾ
	WriteCom(addZ0);	  //������ʾ��ʼ��
}

/******** ����ߴ������ʾ���� ***********|
|��������ʾλ�ã�rowҳ����col�кţ�		  |
|	   �ַ���С��x�������أ�y����ҳ��	  |
|	   ��ʾ���ݣ�tab��ģ��          ******/
void showXY(unsigned char row,unsigned char col,unsigned char x,unsigned char y,unsigned char *tab){
	unsigned char i,j;
	bit right;
	if(col<64){right=0;} //����������־
	else {col-=64;right=1;}	
	for(i=0;i<y;i++){
		if(right)cs2=0,cs1=1;
		else  cs2=1,cs1=0;
		WriteCom(addX0+row+i); //��
		WriteCom(addY0+col);   //��
		for(j=0;j<x;j++){
			if(col+j<64)WriteDat(tab[i*x+j]); //δ����
			else if(right==0){		  //������������
				 cs2=0,cs1=1;		  //ѡ������
				 WriteCom(addX0+row+i);	   //������
				 WriteCom(addY0+(col+j-64));
				 WriteDat(tab[i*x+j]);
			}						 //������Խ�粻��ʾ
		}
	}
}

/* ����һ��8*16�ַ�����λ�� */					
unsigned char enN(unsigned char *s){
	unsigned char i;
	for(i=0;zm8x16_index[i]!=0;i++)if(zm8x16_index[i]==s[0])break;
	return i;	
}
/* ����һ��16*16�ַ�����λ�� */
unsigned char cnN(unsigned char *s){
	unsigned char i;
	for(i=0;zm16x16_index[i]!=0;i+=2)
		if(zm16x16_index[i]==*s&&zm16x16_index[i+1]==*(s+1))break ;
	return i/2;
}
/* ��ʾ��Ӣ���ַ��� */
void showStr(unsigned char row,unsigned char col,unsigned char *s){
	 unsigned char i;
	 for(i=0;s[i]!=0;i++){
	 	if(s[i]<0x80){ 	//Ӣ��
			showXY(row,col,8,2,zm8x16_Table[enN(&s[i])]);
			col+=8;
		}else{			
			showXY(row,col,16,2,zm16x16_Table[cnN(&s[i])]);	
			col+=16;i+=1;		
		}
		if(col>120){	 //���д���
			col=0;
			row+=2;
		}
	 }
}
/* ��ʾ���� */
void showNum(unsigned char row,unsigned char col,unsigned char s){
	showXY(row,col,8,2,zm8x16_Table[s]);
}
void showThreeNum(unsigned char row,unsigned char col,unsigned int s)
{
	showNum(row,col,s/100%10);
	showNum(row,col+8,s/10%10);
	showNum(row,col+16,s%10);
}
#if CONFIG_DS18b02 == ENABLED
void showDS18B02Num(unsigned char row,unsigned char col,unsigned int s)
{
	showNum(row,col,s/100%10);
	showNum(row,col+8,s/10%10);
	showStr(row,col+16,".");
	showNum(row,col+24,s%10);
}
#endif
#if CONFIG_DS1302 == ENABLED
void Ds13b02_DisPlay_12864(unsigned char row,unsigned char col,unsigned char shi,unsigned char fen,unsigned char miao)
{

	showNum(row,col,shi%100/10);		// ʮλ
	showNum(row,col+8,shi%10);				// ��λ
	showStr(row,col+8*2,":");
	showNum(row,col+8*3,fen%100/10);		// ʮλ
	showNum(row,col+8*4,fen%10);				// ��λ
	showStr(row,col+8*5,":");
	showNum(row,col+8*6,miao%100/10);		// ʮλ
	showNum(row,col+8*7,miao%10);				// ��λ

}
#endif
#endif

#if CONFIG_KEY_MAP_2== ENABLED

void key_Map_delay(unsigned int i){ while(i--);}
unsigned char key_get(){
    unsigned char k=16;
    col0=col1=col2=col3=row0=row1=row2=row3=1;
    row0=0; k=col0==0?0:col1==0?1:col2==0?2:col3==0?3:k; row0=1;
    row1=0; k=col0==0?4:col1==0?5:col2==0?6:col3==0?7:k; row1=1;
		row2=0; k=col0==0?8:col1==0?9:col2==0?10:col3==0?11:k; row2=1;
		row3=0; k=col0==0?12:col1==0?13:col2==0?14:col3==0?15:k; row3=1;
    return k;  //���ؼ�ֵ
}
bit keyFlag=0;
void Key_Map(pKey_Map_Process key_Map_Process)
{
	if(key_get()!=16&&keyFlag==0)
	{
		key_Map_delay(200);
		if(key_get()!=16)
		{
			keyFlag=1;
			key_Map_Process(key_get());
		}
	}
	if(key_get()==16&&keyFlag==1)keyFlag=0;	//���ͷ�
}
#endif

#if CONFIG_MAX6675== ENABLED

void MAX6675_Delay(void)
{
	_nop_();	
	_nop_();	
	_nop_();	
}

//volatile unsigned short MAX6675_Temp[4] = {0,0,0,0};

void MAX6675_Processing(unsigned char CH,unsigned short *MAX6675_Temp)
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
	MAX6675_SCK = 0;     
	MAX6675_Delay();
	
	for(i=0; i<16; i++)		//get D15-D0 from 6675  
	{      
		MAX6675_SCK = 1; 
		MAX6675_Delay();    
		dat = dat<<1;  
		
		if(  SO == 1 )   
			dat = dat|0x01;  
		
		MAX6675_SCK = 0;   
		MAX6675_Delay();		
	} 
	
	switch(CH){case 0:CS1  = 1; break;case 1: CS2 = 1;break;case 2: CS3 = 1;break;case 3: CS4 = 1;break;}
	
	MAX6675_Delay();  
	
	t = dat;
	

  Flag_connect = t&0x04;		 	//�������ݵ�D2λ���ȵ�ż���߱�־λ����λΪ1��ʾ���ߣ���λΪ0��ʾ����
  Flag_connect = Flag_connect>>2; 	//MAX6675�Ƿ�����

	t = t<<1;					   	//�����������ݵ�D3~D14���¶�ֵ
	t = t>>4;
	
	MAX6675_Temp[CH] = (t/4)-5;				//��õ��¶ȵ�λ��0.25������Ҫ����0.25��������4�����ܵõ��Զ�Ϊ��λ���¶�ֵ
		
}
#endif

#if CONFIG_GSM== ENABLED

void GSM_delay_ms(unsigned int z)
{
	unsigned int i1,j1;
		for(i1=z;i1>0;i1--)
			for(j1=110;j1>0;j1--);
}
void Uart_init()
{
	TMOD|= 0X21;		//T1  ��ʽ2  ��8λ   �Զ���װ   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600

	ET0=1;
	TR1=1; 		    // ��ʱ��1����  
	SM0=0;	    // ���ô��ڵĹ���ģʽ
	SM1=1; 	    //��ʽ1
	REN=1; 		 // �����ڽ������� 	 
	ES=1; 	     // �����ж�Ӧ�� 
	EA=1;		 // �����ж�
}

void SendASC(unsigned char d)
{
	
	SBUF=d;
	while(!TI);

	TI=0;
}
void SendString(unsigned char *str)	
{
	while(*str)
	{
		SendASC(*str) ;
		str++;
	}
}
void SendNum(unsigned char num)
{
	SendASC('0');
	SendASC('0');
	SendASC('3');
	SendASC(0x30+num);	
}
void SendNum_char(unsigned char num)
{
	SendASC('0');
	SendASC('0');
	SendASC('3');
	SendASC(num);	
}
void SendTwoNum(unsigned char num)
{
		if(num>=100)
		   num = 99;
		SendNum(num/10);
		SendNum(num%10);	
}
void Gsm_init()
{
	Uart_init();
	GSM_delay_ms(500);
}
#if 0
/*********************************************************************
 *                  C51���ַ�������������                            *
 ** ��������    : strsearch ()
 ** ��������    : ��ָ���������������ҵ���ͬ������
 ** ��ڲ���   �� ptr2=Ҫ�ҵ�����, ptr1 ��ǰ����
 **** ���ڲ��� �� 0-û�� �ҵ�   >1 ���ҵ�
 *********************************************************************/
//����������������ַ���*ptr2�Ƿ���ȫ������*ptr1��
//����:  0  û���ҵ�
//       1-255 �ӵ�N���ַ���ʼ��ͬ
unsigned char strsearch(unsigned char *ptr2,unsigned char *ptr1_at)//���ַ���*ptr2��*ptr1�е�λ��

{
	unsigned int i2,j2,k2;
	if(ptr2[0]==0)
	return(0);

	for(i2=0,j2=0;i2<RsBuf_N;i2++)
	{
		if(ptr1_at[i2]==ptr2[j2])
		{//��һ���ַ���ͬ
			k2=i2;
			do {
			if(ptr2[j2]=='\0')//�Ƚ���ȷ
			return(i2+1);               //����ֵ������������0
			if(ptr1_at[k2]!=ptr2[j2])
			break;
			k2++;j2++ ;	 
			}
			while(k2<RsBuf_N) ;
			j2=0;
		}
	}
	return(0);
}
#endif
//  ͨѶ�жϽ��ճ���   �жϺ����޷���ֵ
void uart_rx()  interrupt 4	using 3	  //�������� �ͷ���main����������һ����
{
	RI=0;
}
#endif

#if CONFIG_STEPMOTO== ENABLED

static MotoTimer2_Process  Moto_Interrp_Process;

unsigned char MotoTimeCtr;

void MotoTimer2_init_Demo(MotoTimer2_Process T_Process)
{
	RCAP2H = (0XFFFF - TIME_HAPPEND)/256;
	RCAP2L = (0XFFFF - TIME_HAPPEND)%256;
	T2CON =0;
	IE |=0xA0;
	
	Moto_Interrp_Process = T_Process;
	TR2 = 1;
}

void timer2() interrupt 5
{
	TF2 = 0;
	MotoTimeCtr++;
	if(MotoTimeCtr >= TIME_COUNT)
	{
		MotoTimeCtr =0;
		Moto_Interrp_Process();
	}
		
}


void DelayMoto(unsigned int i)//��ʱ
{
	while(--i);
}
/***********************��ת****************************/
void zheng(unsigned char dat)
{
	switch(dat)
	{
		case 0: dj1=1;dj2=0;dj3=0;dj4=0; break;
		case 1: dj1=0;dj2=1;dj3=0;dj4=0; break;
		case 2: dj1=0;dj2=0;dj3=1;dj4=0; break;
		case 3: dj1=0;dj2=0;dj3=0;dj4=1; break;
	}
}

/***********************��ת****************************/
void fan(unsigned char dat)
{
	switch(dat)
	{
		case 0: dj1=0;dj2=0;dj3=0;dj4=1; break;
		case 1: dj1=0;dj2=0;dj3=1;dj4=0; break;
		case 2: dj1=0;dj2=1;dj3=0;dj4=0; break;
		case 3: dj1=1;dj2=0;dj3=0;dj4=0; break;
	}
}
void stop()
{
	dj1=0;dj2=0;dj3=0;dj4=0;
}
void MotoStepSpeed(unsigned char status,unsigned int speed,unsigned int count)
{
	unsigned char i;
	unsigned int j;
	if(status == 0)
	{
		for(j=0;j<count;j++)
		{
			for(i=0;i<4;i++)
			{
				zheng(i);
				DelayMoto(speed);
			}			
		}

	}else
	{
		for(j=0;j<count;j++)
		{
			for(i=0;i<4;i++)
			{
				fan(i);
				DelayMoto(speed);
			}			
		}		
	}
}

#endif

#if CONFIG_7BIT_4_LED== ENABLED
#if 0
typedef void (*Num_Process)();
sbit LED_A = P0^0;
sbit LED_B = P0^1;
sbit LED_C = P0^2;
sbit LED_D = P0^3;
sbit LED_E = P0^4;
sbit LED_F = P0^5;
sbit LED_G = P0^6;
sbit LED_H = P0^7;
sbit LED_S1 = P2^0;
sbit LED_S2 = P2^1;
sbit LED_S3 = P2^2;
sbit LED_S4 = P2^3;
#define NUM_0 {LED_A=0;LED_B=0;LED_C=0;LED_D=0;LED_E=0;LED_F=0;LED_G=1;LED_H=1;}
#define NUM_1 {LED_A=1;LED_B=0;LED_C=0;LED_D=1;LED_E=1;LED_F=1;LED_G=1;LED_H=1;}

void numProcess_0(){NUM_0}
Num_Process numProcess[10]={numProcess_0};
#endif
/**demo

static Timer2_Process  Interrp_Process;


void Timer2_init_Demo(Timer2_Process T_Process)
{
	RCAP2H = (0XFFFF - 5000)/256;
	RCAP2L = (0XFFFF - 5000)%256;
	T2CON =0;
	IE |=0xA0;
	TR2 = 1;
	Interrp_Process = T_Process;
}

void timer2() interrupt 5
{
	TF2 = 0;
	Interrp_Process();
	}
		
}

//P0~7,��Ӧ����ܵ�abcdefgh
//uchar code  LEDData[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xff,0xc6,0x88,0x86};//0123456789CAE
//p0~7,��Ӧ���ݹܵ�afbedhcg,����Ҫȡ��~LEDData[]
uchar code  LEDData[]={0x5F,0x44,0x9D,0xD5,0xC6,0xD3,0xDB,0x47,0xDF,0xD7,0xCF,0xDA,0x9B,0xDC,0x9B,0x8B,};//0123456789ABCDE
void Timer2_Process2()
{
	P2=0xff;
	P0 = DisplayNum[DisplayBit];
	switch(DisplayBit)
	{
		case 0:
			P2 = 0XFD;//��Ӧ�������Ƭѡ��������
		break;
		case 1:
			P2 = 0XF7;
		break;
		case 2:
			P2 = 0xDF;
		break;
		case 3:
			P2 = 0x7F;
		break;			
	}	
	DisplayBit++;
	if(DisplayBit>=4)
	{	
		DisplayBit=0;
	}
		
	
}
void main()
{
	Timer2_init_Demo(Timer2_Process2);
	DisplayNum[0] = ~LEDData[10];
	DisplayNum[1] = ~LEDData[1];
	DisplayNum[2] = ~LEDData[0];
	DisplayNum[3] = ~LEDData[12];	
	while(1);
}
**/
#endif

#if CONFIG_BULETOOTH == ENABLED
unsigned char *a;
bit UART0_TXD_BUSY = 0;
void Bluetooth_Delay_Ms(int cnt)
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
//*********������*****************
//9600bps
void Bluetooth_uart_init(unsigned char *buff)
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
	a= buff;
}
void Bluetooth_UartSendByte(unsigned char byte)
{
	SBUF = byte;
  UART0_TXD_BUSY = 1;	
	while(UART0_TXD_BUSY);	//�ȴ����ͳɹ�
}


void Bluetooth_UartSendString(unsigned char *string)
{
	while(*string)
	{
		Bluetooth_UartSendByte(*string++);
	}
}


void ser() interrupt 4
{
	if(RI)
	{
		RI = 0;
		*a = SBUF;
	}
	if(TI)
	{
		TI=0;
		UART0_TXD_BUSY = 0;		
	}	
}
 
/**demo 

//���յ�������
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

#if CONFIG_PCF8591 == ENABLED
bit PCF859_ack;                 /*Ӧ���־λ*/
   
/*******************************************************************
                     �����ߺ���               
����ԭ��: void  Start_I2c();  
����:     ����I2C����,������I2C��ʼ����.  
********************************************************************/
void PCF8591_Start()
{
	PCF8591_SDA=1;         /*������ʼ�����������ź�*/
	_Nop();
	PCF8591_SCL=1;
	_Nop();        /*��ʼ��������ʱ�����4.7us,��ʱ*/
	_Nop();_Nop();_Nop();_Nop();    
	PCF8591_SDA=0;         /*������ʼ�ź�*/
	_Nop();        /* ��ʼ��������ʱ�����4��s*/
	_Nop();_Nop();_Nop();_Nop();       
	PCF8591_SCL=0;       /*ǯסI2C���ߣ�׼�����ͻ�������� */
	_Nop();_Nop();
}
/*******************************************************************
                      �������ߺ���               
����ԭ��: void  Stop_I2c();  
����:     ����I2C����,������I2C��������.  
********************************************************************/
void PCF8591_Stop()
{
  PCF8591_SDA=0;      /*���ͽ��������������ź�*/
  _Nop();       /*���ͽ���������ʱ���ź�*/
  PCF8591_SCL=1;      /*������������ʱ�����4��s*/
  _Nop();_Nop();_Nop();_Nop();_Nop();
  PCF8591_SDA=1;      /*����I2C���߽����ź�*/
  _Nop();_Nop();_Nop();_Nop();
}
/*******************************************************************
                 �ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:     ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
          ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0)     
           ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
********************************************************************/
void  PCF8591_SendByte(unsigned char  c)
{
 unsigned char  BitCnt; 
 for(BitCnt=0;BitCnt<8;BitCnt++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
     if((c<<BitCnt)&0x80)PCF8591_SDA=1;   /*�жϷ���λ*/
       else  PCF8591_SDA=0;                
     _Nop();
     PCF8591_SCL=1;               /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
      _Nop(); _Nop();             /*��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/
      _Nop();_Nop();_Nop();         
     PCF8591_SCL=0; 
    } 
    _Nop();_Nop();
    PCF8591_SDA=1;                /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
    _Nop();_Nop();   
    PCF8591_SCL=1;
    _Nop();_Nop();_Nop();
    if(PCF8591_SDA==1)PCF859_ack=0;     
       else PCF859_ack=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
    PCF8591_SCL=0;
    _Nop();_Nop();
}
/*******************************************************************
                 �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����:        �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
          ���������Ӧ����Ӧ��ӻ���  
********************************************************************/    
unsigned char  PCF8591_RcvByte()
{
  unsigned char  retc;
  unsigned char  BitCnt;
  
  retc=0; 
  PCF8591_SDA=1;                     /*��������Ϊ���뷽ʽ*/
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        PCF8591_SCL=0;                  /*��ʱ����Ϊ�ͣ�׼����������λ*/
        _Nop();_Nop();                 /*ʱ�ӵ͵�ƽ���ڴ���4.7��s*/
        _Nop();_Nop();_Nop();
        PCF8591_SCL=1;                  /*��ʱ����Ϊ��ʹ��������������Ч*/
        _Nop();_Nop();
        retc=retc<<1;
        if(PCF8591_SDA==1)retc=retc+1;  /*������λ,���յ�����λ����retc�� */
        _Nop();_Nop(); 
      }
  PCF8591_SCL=0;    
  _Nop();_Nop();
  return(retc);
}
/********************************************************************
                     Ӧ���Ӻ���
����ԭ��:  void Ack_I2c(bit a);
����:      ����������Ӧ���ź�(������Ӧ����Ӧ���źţ���λ����a����)
********************************************************************/
void PCF8591_Ack(bit a)
{
  
  if(a==0)PCF8591_SDA=0;              /*�ڴ˷���Ӧ����Ӧ���ź� */
  else PCF8591_SDA=1;
  _Nop();_Nop();_Nop();      
  PCF8591_SCL=1;
  _Nop();_Nop();                    /*ʱ�ӵ͵�ƽ���ڴ���4��s*/
  _Nop();_Nop();_Nop();  
  PCF8591_SCL=0;                     /*��ʱ���ߣ�ǯסI2C�����Ա��������*/
  _Nop();_Nop();    
}

///////////////////////////////
/*******************************************************************
DAC �任, ת������               
*******************************************************************/
bit PCF8591_DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   PCF8591_Start();              //��������
   PCF8591_SendByte(sla);            //����������ַ
   if(PCF859_ack==0)return(0);
   PCF8591_SendByte(c);              //���Ϳ����ֽ�
   if(PCF859_ack==0)return(0);
   PCF8591_SendByte(Val);            //����DAC����ֵ  
   if(PCF859_ack==0)return(0);
   PCF8591_Stop();               //��������
   return(1);
}

/*******************************************************************
ADC�����ֽ�[����]���ݺ���               
*******************************************************************/
bit PCF8591_ISendByte(unsigned char sla,unsigned char c)
{
   PCF8591_Start();              //��������
   PCF8591_SendByte(sla);            //����������ַ
   if(PCF859_ack==0)return(0);
   PCF8591_SendByte(c);              //��������
   if(PCF859_ack==0)return(0);
   PCF8591_Stop();               //��������
   return(1);
}

/*******************************************************************
ADC���ֽ����ݺ���               
*******************************************************************/
unsigned char PCF8591_IRcvByte(unsigned char sla)
{  unsigned char c;

   PCF8591_Start();          //��������
   PCF8591_SendByte(sla+1);      //����������ַ
   if(PCF859_ack==0)return(0);
   c=PCF8591_RcvByte();          //��ȡ����0

   PCF8591_Ack(1);           //���ͷǾʹ�λ
   PCF8591_Stop();           //��������
   return(c);
}


#endif

#if CONFIG_SPEAK_RING == ENABLED



//////////////////////////////////////////////
unsigned char timer0h,timer0l,time;//timer0h,timer0lΪ��ʱ��T0�ĸߵ�λ��ֵ,timeΪ��Ӧ�Ľ���ʱ��
signed char fre;                   //��ӦƵ�����ݱ�ĵ�ַ
unsigned char music_num,num;       //music_numΪ�������,music_num=0��ʾ�տ���ʱ��״̬,num�ǲ��Ҹ������ݱ�ĵ�ַ
//���̻����䡷
unsigned char code song1[]={
     5,2,1, 3,2,1, 2,2,2, 2,2,4, 3,2,1, 1,2,1, 2,2,1, 3,2,4, 
	 5,2,1, 3,2,1, 2,2,2, 2,2,2, 5,1,1, 3,2,1, 4,2,1, 3,2,4, 
	 3,2,1, 3,2,1, 7,2,1, 3,2,1, 2,2,2, 1,2,1, 7,1,1, 1,2,1, 
	 2,2,1, 3,2,1, 6,2,3, 6,1,1, 1,2,1, 3,2,1, 2,2,1, 6,1,1, 
	 1,2,1, 7,1,1, 5,1,1, 6,1,6, 5,2,1, 3,2,1, 2,2,2, 2,2,1, 
	 2,2,1, 3,2,1, 1,2,1, 2,2,1, 3,2,4, 5,2,1, 3,2,1, 2,2,2, 
	 2,2,1, 2,2,1, 5,1,1, 3,2,1, 4,2,1, 3,2,4, 3,2,1, 3,2,1, 
	 7,2,3, 3,2,1, 2,2,2, 1,2,1, 7,1,1, 1,2,1, 2,2,1, 3,2,1, 
	 6,2,3, 6,1,1, 1,2,1, 3,2,1, 2,2,1, 6,1,1, 1,2,1, 7,1,2, 
	 5,1,2, 6,1,6, 0,0,0 };

//������ѩ��
unsigned char code song2[]={
     5,1,1, 2,2,1, 3,2,2, 2,2,1, 3,2,1, 5,2,1, 6,2,1, 5,2,3, 1,2,1, 2,2,1, 
	 3,2,1, 6,2,1, 5,2,1, 3,2,1, 5,2,3, 5,2,1, 6,2,1, 1,3,2, 6,2,1, 5,2,1, 
	 3,2,1, 5,2,1, 3,2,2, 1,2,1, 2,2,1, 3,2,1, 1,2,1, 6,1,1, 3,2,1, 2,2,1, 
	 5,1,1, 2,2,1, 3,2,2, 2,2,1, 3,2,1, 5,2,1, 6,2,1, 5,2,3, 1,2,1, 2,2,1, 
	 3,2,1, 6,2,1, 5,2,3, 5,2,1, 6,2,1, 1,3,2, 6,2,1, 
	 5,2,1, 3,2,1, 5,2,1, 3,2,2, 1,2,1, 6,1,1, 3,2,1, 2,2,1, 1,2,1, 6,1,1, 
	 1,2,1, 2,2,1, 2,2,1, 1,2,4, 0,0,0 };

//���򵥰���
unsigned char code song3[]={
     5,1,1, 1,2,1, 2,2,1, 3,2,1, 2,2,1, 3,2,1, 4,2,1, 5,2,1, 5,2,1, 5,2,1, 
	 4,2,1, 3,2,1, 2,2,3, 5,1,1, 1,2,1, 2,2,1, 3,2,1, 4,2,1, 5,2,1, 5,2,1, 
	 5,2,1, 6,2,1, 5,2,2, 2,2,1, 3,2,1, 1,2,2, 1,2,1, 6,1,1, 2,2,1, 2,2,1, 
	 3,2,1, 3,2,1, 1,2,1, 5,2,1, 1,2,1, 5,2,1, 1,2,1, 7,1,1, 1,2,1, 1,2,1, 6,1,1, 
	 2,2,1, 2,2,1, 3,2,1, 3,2,1, 5,2,1, 5,2,1, 
	 5,2,1, 6,2,1, 5,2,2, 2,2,1, 3,2,1, 1,2,2,  
	 5,1,1, 1,2,1, 2,1,2, 3,2,1, 2,2,1, 3,2,1, 4,2,1, 5,2,1, 5,2,1, 5,2,1, 
	 4,2,1, 3,2,1, 2,2,3, 5,1,1, 1,2,1, 2,2,1, 3,2,1, 2,2,1, 3,2,1, 4,2,1, 
	 5,2,1, 5,2,1, 5,2,2, 2,2,1, 3,2,1, 1,2,2, 1,2,1, 6,1,1, 2,2,1, 2,2,1, 
	 3,2,1, 3,2,1, 1,2,2, 5,2,1, 1,2,1, 5,2,1, 5,2,1, 7,1,1, 1,2,1, 0,0,0 };

//������ֻ������á�
unsigned char code song4[]={
     6,2,3, 5,2,1, 3,2,2, 5,2,2, 1,3,2, 6,2,1,
	 //6,2,3����6,����,3������;
	 //5,2,1����5,����,1������;
	 //3,2,2����3,����,2������;
	 //5,2,2����5,����,2������;
	 //1,3,2����1,����,2������;
	 //...
     5,2,1,6,2,4, 3,2,2, 5,2,1, 6,2,1, 5,2,2, 3,2,2, 1,2,1,6,1,1, 5,2,1, 
	 3,2,1, 2,2,4, 2,2,3, 3,2,1, 5,2,2, 5,2,1, 6,2,1, 3,2,2, 2,2,2, 
	 1,2,4, 5,2,3, 3,2,1,2,2,1, 1,2,1, 6,1,1, 1,2,1, 5,1,6, 0,0,0};

//������µ��������˭��
unsigned char code song5[]={
     3,2,2, 3,2,1, 4,2,1, 3,2,2, 2,2,1, 1,2,1,  2,2,2, 5,2,2, 2,2,2, 2,2,3,
	 1,2,2, 1,2,1, 2,2,1, 1,2,2, 7,1,1, 6,1,1, 7,1,2, 3,2,2, 7,1,2, 7,1,3, 
	 6,1,2, 2,2,1, 3,2,1, 2,2,1, 1,2,1, 6,1,2, 5,1,2, 2,2,1, 3,2,1, 2,2,1, 
	 1,2,1, 6,1,2, 6,1,2, 2,2,1, 3,2,1, 2,2,1, 1,2,1, 6,1,1, 7,1,1, 1,2,6, 0,0,0 };

//�����С·��
unsigned char code song6[]={
     3,1,2, 3,1,1, 3,1,1, 6,0,1, 6,0,1, 1,1,2,
     6,0,1, 5,0,1, 6,0,4, 6,0,2, 6,0,1 ,6,0,1, 6,0,2, 6,0,1, 1,1,1, 
     2,1,2, 2,1,1, 3,1,1, 2,1,4, 3,1,1, 3,1,1, 3,1,1, 2,1,1, 4,1,2,
     4,1,2, 3,1,2, 2,1,1, 1,1,1, 2,1,4, 7,0,1, 7,0,1, 7,0,1, 6,0,1, 
     5,0,1, 5,0,1, 6,0,1, 7,0,1, 7,0,1, 6,0,1, 5,0,1, 6,0,4, 6,1,2,
     3,1,1, 6,1,1, 7,1,1, 6,1,1, 5,1,1, 5,1,2, 5,1,1, 2,1,1, 5,1,1, 
     6,1,1, 5,1,1, 4,1,1, 4,1,2, 4,1,1, 3,1,1, 2,1,2, 1,1,1, 2,1,1, 
     3,1,1, 2,1,1, 1,1,1, 2,1,1, 3,1,4, 6,1,2, 3,1,1, 6,1,1, 7,1,1, 
	 6,1,1, 5,1,1, 5,1,2, 2,1,1, 5,1,1, 6,1,1, 5,1,1, 4,1,1, 0,0,0};     

//���ͱ�
unsigned char code song7[]={
     5,1,2, 3,1,3, 5,1,1, 1,2,3, 6,1,2, 1,2,2, 
     5,1,4, 5,1,2, 1,1,1, 2,1,1, 3,1,2, 2,1,1, 1,1,1, 2,1,4, 5,1,2, 
	 3,1,1, 5,1,1, 1,2,2, 7,1,1, 6,1,2, 1,2,2, 5,1,4, 5,1,2, 2,1,1, 
	 3,1,1, 4,1,2, 7,0,1, 1,1,4, 6,1,2, 1,2,2, 1,2,4, 7,1,2, 6,1,1,
	 7,1,1, 1,2,4, 6,1,1, 7,1,1, 1,2,1, 6,1,1, 6,1,1, 5,1,1, 3,1,1, 
	 1,1,1, 2,1,8, 5,1,2, 3,1,1, 5,1,1, 1,2,2, 7,1,1, 6,1,2, 1,2,2, 
	 5,1,4, 5,1,2, 2,1,1, 3,1,1, 4,1,2, 7,0,2, 1,1,4, 0,0,0};

//�����������¡�
unsigned char code song8[]={
     5,1,1, 6,1,1, 1,2,1, 6,1,2, 6,1,1, 5,1,1, 6,1,1, 5,1,1, 3,1,1, 5,1,5, 
	 5,1,1, 6,1,1, 1,2,1, 6,1,2, 6,1,1, 5,1,1, 6,1,1, 5,1,1, 6,1,1, 1,1,5, 
	 1,1,1, 2,1,1, 3,1,1, 2,1,1, 2,1,1, 2,1,1, 1,1,1, 2,1,1, 1,1,1, 6,1,1, 
	 3,1,2, 2,1,3, 5,1,1, 6,1,1, 1,2,1, 6,1,2, 6,1,1, 5,1,1, 6,1,1, 5,1,1, 
	 6,1,1, 1,1,5, 1,1,1, 2,1,1, 3,1,1, 4,1,2, 4,1,1, 5,1,1, 6,1,1, 6,1,1, 
	 5,1,1, 6,1,2, 1,2,1, 6,1,3, 1,2,1, 6,1,1, 5,1,1, 5,1,4, 1,1,1, 6,1,1, 
	 5,1,5, 5,1,1, 6,1,1, 1,2,1, 3,1,1, 2,1,1, 3,1,1, 1,1,6, 0,0,0}; 

// Ƶ��-���������ݱ� �߰�λ  ���������ĸ��˶ȵ�28��Ƶ������
unsigned char code FREQH[]={
    0xF2, 0xF3, 0xF5, 0xF5, 0xF6, 0xF7, 0xF8,    //����1234567
    0xF9, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFC, 0xFC,//1,2,3,4,5,6,7,i
    0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE,            //���� 234567
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF};   //������ 1234567

// Ƶ��-���������ݱ� �Ͱ�λ
unsigned char code FREQL[]={
    0x42, 0xC1, 0x17, 0xB6, 0xD0, 0xD1, 0xB6,    //����1234567
    0x21, 0xE1, 0x8C, 0xD8, 0x68, 0xE9, 0x5B, 0x8F, //1,2,3,4,5,6,7,i
    0xEE, 0x44, 0x6B, 0xB4, 0xF4, 0x2D,             //���� 234567
    0x47, 0x77, 0xA2, 0xB6, 0xDA, 0xFA, 0x16};   //������ 1234567  
	
void timer0(void) interrupt 1  //T0�жϳ���,���Ʒ���������
{
	speaker=!speaker;//�������, ����
	TH0=timer0h;	 //�´ε��ж�ʱ��,���ʱ����������ߵ�
	TL0=timer0l;
 }



void delay(unsigned char t)	    //��ʱ�Ӻ���,���Ʒ�����ʱ�䳤��,ÿ������0.4S
{
	unsigned char t1;
	unsigned long t2;
	for(t1=0;t1<t;t1++)	       //Ƕ��ѭ��, ����ʱt������
	{
		for(t2=0;t2<8000;t2++) //��ʱ�ڼ�, �ɽ���T0�ж�ȥ����
		{
			;
		}
	}
	TR0=0;		               //�ر�T0, ֹͣ����
}
void song(void)  	//����һ������
{
	TH0=timer0h;    //��������
	TL0=timer0l;
	TR0=1;		    //����T0, ��T0�����������
	delay(time);    //ÿ������������ʱ��
}
 
void speak_ring_init()
{
	TMOD|=0x11; //T0 T1 ���ڹ�����ʽ1
	ET0=1;  //T0���ж�
	EA=1;   //CPU���ж�	 
}
void speak_play()
{
	fre=song6[num]+7*song6[num+1]-1;
	timer0h=FREQH[fre];
		timer0l=FREQL[fre];
		time=song6[num+2];
		num+=3;
	if(fre==-1)
	{

		num=0;
	}
	song();		
}
#endif

#if CONFIG_RC522 == ENABLED


void delay_ns(unsigned int ns)
{
	unsigned int i;
	for(i=0;i<ns;i++)
	{	   
		_nop_();
		_nop_();
		_nop_();
	}
}

//------------------------------------------
// ��SPI���� 
//------------------------------------------
unsigned char SPIReadByte(void)
{
	unsigned char SPICount;                                       // Counter used to clock out the data
	unsigned char SPIData; 
	                 
	SPIData = 0;
	for (SPICount = 0; SPICount < 8; SPICount++)                  // Prepare to clock in the data to be read
	{
		SPIData <<=1;                                               // Rotate the data
		CLR_SPI_CK; //nop();//nop();                                         // Raise the clock to clock the data out of the MAX7456
		if(STU_SPI_MISO)
		{
 			SPIData|=0x01;
		}
		SET_SPI_CK;   //nop();//nop();                                               // Drop the clock ready for the next bit
	}                                                             // and loop back
	return (SPIData);                              // Finally return the read data
} 
//------------------------------------------
// дSPI���� 
//------------------------------------------
void SPIWriteByte(unsigned char SPIData)
{
	unsigned char SPICount;                                       // Counter used to clock out the data
	for (SPICount = 0; SPICount < 8; SPICount++)
	{
		if (SPIData & 0x80)
		{
			SET_SPI_MOSI;
		}
		else
		{
			CLR_SPI_MOSI;
		} 
		_nop_();_nop_();
		CLR_SPI_CK;nop();nop();
		SET_SPI_CK;nop();nop();
		SPIData <<= 1;
	}         	
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC632�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//��    �أ�������ֵ
/////////////////////////////////////////////////////////////////////
unsigned char ReadRawRC(unsigned char Address)
{
	unsigned char ucAddr;
    unsigned char ucResult=0;
	CLR_SPI_CS;
    ucAddr = ((Address<<1)&0x7E)|0x80;
	SPIWriteByte(ucAddr);
	ucResult=SPIReadByte();
	SET_SPI_CS;
	return ucResult;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�дRC632�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//          value[IN]:д���ֵ
/////////////////////////////////////////////////////////////////////
void WriteRawRC(unsigned char Address, unsigned char value)
{  
    unsigned char ucAddr;

	CLR_SPI_CS;
    ucAddr = ((Address<<1)&0x7E);
	SPIWriteByte(ucAddr);
	SPIWriteByte(value);
	SET_SPI_CS;
}   

/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
/////////////////////////////////////////////////////////////////////
void ClearBitMask(unsigned char reg,unsigned char mask)  
{
    char tmp = 0x00;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  // clear bit mask
} 


/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
/////////////////////////////////////////////////////////////////////
void SetBitMask(unsigned char reg,unsigned char mask)  
{
    char tmp = 0x00;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp | mask);  // set bit mask
}

/////////////////////////////////////////////////////////////////////
//��MF522����CRC16����
/////////////////////////////////////////////////////////////////////
void CalulateCRC(unsigned char *pIndata,unsigned char len,unsigned char *pOutData)
{
    unsigned char i,n;
    ClearBitMask(DivIrqReg,0x04);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    for (i=0; i<len; i++)
    {   WriteRawRC(FIFODataReg, *(pIndata+i));   }
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
    pOutData[0] = ReadRawRC(CRCResultRegL);
    pOutData[1] = ReadRawRC(CRCResultRegM);
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�ͨ��RC522��ISO14443��ͨѶ
//����˵����Command[IN]:RC522������
//          pInData[IN]:ͨ��RC522���͵���Ƭ������
//          InLenByte[IN]:�������ݵ��ֽڳ���
//          pOutData[OUT]:���յ��Ŀ�Ƭ��������
//          *pOutLenBit[OUT]:�������ݵ�λ����
/////////////////////////////////////////////////////////////////////
char PcdComMF522(unsigned char idata Command, 
                 unsigned char idata *pInData, 
                 unsigned char idata InLenByte,
                 unsigned char idata *pOutData, 
                 unsigned int idata *pOutLenBit)
{
    char idata status = MI_ERR;
    unsigned char idata irqEn   = 0x00;
    unsigned char idata waitFor = 0x00;
    unsigned char idata lastBits;
    unsigned char idata n;
    unsigned int idata i;
    switch (Command)
    {
        case PCD_AUTHENT:
			irqEn   = 0x12;
			waitFor = 0x10;
			break;
		case PCD_TRANSCEIVE:
			irqEn   = 0x77;
			waitFor = 0x30;
			break;
		default:
			break;
    }
   
    WriteRawRC(ComIEnReg,irqEn|0x80);
    ClearBitMask(ComIrqReg,0x80);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    
    for (i=0; i<InLenByte; i++)
    {   
		WriteRawRC(FIFODataReg, pInData[i]);    
	}
    WriteRawRC(CommandReg, Command);
   
    if (Command == PCD_TRANSCEIVE)
    {    
		SetBitMask(BitFramingReg,0x80);  
	}
    
    //i = 600;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
	i = 2000;
    do 
    {
        n = ReadRawRC(ComIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor));
    ClearBitMask(BitFramingReg,0x80);

    if (i!=0)
    {    
        if(!(ReadRawRC(ErrorReg)&0x1B))
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {   status = MI_NOTAGERR;   }
            if (Command == PCD_TRANSCEIVE)
            {
               	n = ReadRawRC(FIFOLevelReg);
              	lastBits = ReadRawRC(ControlReg) & 0x07;
                if (lastBits)
                {   
					*pOutLenBit = (n-1)*8 + lastBits;   
				}
                else
                {   
					*pOutLenBit = n*8;   
				}
                if (n == 0)
                {   
					n = 1;    
				}
                if (n > MAXRLEN)
                {   
					n = MAXRLEN;   
				}
                for (i=0; i<n; i++)
                {   
					pOutData[i] = ReadRawRC(FIFODataReg);    
				}
            }
        }
        else
        {   
			status = MI_ERR;   
		}
        
    }
   
    SetBitMask(ControlReg,0x80);           // stop timer now
    WriteRawRC(CommandReg,PCD_IDLE); 
    return status;
}
                      
/////////////////////////////////////////////////////////////////////
//��    �ܣ�Ѱ��
//����˵��: req_code[IN]:Ѱ����ʽ
//                0x52 = Ѱ��Ӧ�������з���14443A��׼�Ŀ�
//                0x26 = Ѱδ��������״̬�Ŀ�
//          pTagType[OUT]����Ƭ���ʹ���
//                0x4400 = Mifare_UltraLight
//                0x0400 = Mifare_One(S50)
//                0x0200 = Mifare_One(S70)
//                0x0800 = Mifare_Pro(X)
//                0x4403 = Mifare_DESFire
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdRequest(unsigned char req_code,unsigned char *pTagType)
{
	char status;  
	unsigned int unLen;
	unsigned char ucComMF522Buf[MAXRLEN]; 

	ClearBitMask(Status2Reg,0x08);
	WriteRawRC(BitFramingReg,0x07);
	SetBitMask(TxControlReg,0x03);
 
	ucComMF522Buf[0] = req_code;

	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);

	if ((status == MI_OK) && (unLen == 0x10))
	{    
		*pTagType     = ucComMF522Buf[0];
		*(pTagType+1) = ucComMF522Buf[1];
	}
	else
	{   
		status = MI_ERR;   
	}
   
	return status;
}


/////////////////////////////////////////////////////////////////////
//��    �ܣ�����ײ
//����˵��: pSnr[OUT]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////  
char PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i,snr_check=0;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    

    ClearBitMask(Status2Reg,0x08);
    WriteRawRC(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
 
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK)
	{
		for (i=0; i<4; i++)
		{   
			*(pSnr+i)  = ucComMF522Buf[i];
			snr_check ^= ucComMF522Buf[i];
		}
		if (snr_check != ucComMF522Buf[i])
   		{   
			status = MI_ERR;    
		}
    }
    
    SetBitMask(CollReg,0x80);
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�ѡ����Ƭ
//����˵��: pSnr[IN]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdSelect(unsigned char *pSnr)
{
    char idata status;
    unsigned idata   i;
    unsigned int idata unLen;
    unsigned char idata ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for (i=0; i<4; i++)
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
  
    ClearBitMask(Status2Reg,0x08);

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    
    if ((status == MI_OK) && (unLen == 0x18))
    {   
		status = MI_OK;  
	}
    else
    {   
		status = MI_ERR;    
	}

    return status;
}


/////////////////////////////////////////////////////////////////////
//��    �ܣ���λRC522
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdReset(void)
{
	SET_RC522RST;
    delay_ns(10);
	CLR_RC522RST;
    delay_ns(10);
	SET_RC522RST;
    delay_ns(10);
    WriteRawRC(CommandReg,PCD_RESETPHASE);
    delay_ns(10);
    
    WriteRawRC(ModeReg,0x3D);            //��Mifare��ͨѶ��CRC��ʼֵ0x6363
    WriteRawRC(TReloadRegL,30);           
    WriteRawRC(TReloadRegH,0);
    WriteRawRC(TModeReg,0x8D);
    WriteRawRC(TPrescalerReg,0x3E);
	
	WriteRawRC(TxAutoReg,0x40);//����Ҫ
   
    return MI_OK;
}
//////////////////////////////////////////////////////////////////////
//����RC632�Ĺ�����ʽ 
//////////////////////////////////////////////////////////////////////
char M500PcdConfigISOType(unsigned char type)
{
   if (type == 'A')                     //ISO14443_A
   { 
       ClearBitMask(Status2Reg,0x08);
       WriteRawRC(ModeReg,0x3D);//3F
       WriteRawRC(RxSelReg,0x86);//84
       WriteRawRC(RFCfgReg,0x7F);   //4F
   	   WriteRawRC(TReloadRegL,30);//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
	   WriteRawRC(TReloadRegH,0);
       WriteRawRC(TModeReg,0x8D);
	   WriteRawRC(TPrescalerReg,0x3E);
	   delay_ns(1000);
       PcdAntennaOn();
   }
   else{ return -1; }
   
   return MI_OK;
}

/////////////////////////////////////////////////////////////////////
//��������  
//ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
/////////////////////////////////////////////////////////////////////
void PcdAntennaOn(void)
{
    unsigned char i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}


/////////////////////////////////////////////////////////////////////
//�ر�����
/////////////////////////////////////////////////////////////////////
void PcdAntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}

void init_rc522(void)
{
  PcdReset();
  PcdAntennaOff();  
  PcdAntennaOn();
  M500PcdConfigISOType( 'A' );
}

char read_id(unsigned char *pTagType)
{

	if( PcdRequest( PICC_REQIDL, &pTagType[0] ) != MI_OK )//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�	
	{
		if( PcdRequest( PICC_REQIDL, &pTagType[0] ) != MI_OK )//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�	
		{
	 	
			return 0;
		}	
	}

	if( PcdAnticoll( &pTagType[2] ) != MI_OK ) //����ײ�����ؿ������к� 4�ֽ� 
	{
		return 0;	
	}

	if( PcdSelect( &pTagType[2] ) != MI_OK )//ѡ��
	{
		return 0;
	}
  return 1;	
}
#endif

#if CONFIG_MPU6050 == ENABLED



//************************************************************************************************
//��ʱ5΢��(STC90C52RC@12M)
//��ͬ�Ĺ�������,��Ҫ�����˺���
//ע�⵱����1T��MCUʱ,���������ʱ����
//************************************************************************************************
void Delay5us()
{
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}
//*************************************************************************************************
//I2C��ʼ�ź�
//*************************************************************************************************
void I2C_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}
//*************************************************************************************************
//I2Cֹͣ�ź�
//*************************************************************************************************
void I2C_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}
//**************************************************************************************************
//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
//**************************************************************************************************
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}
//****************************************************************************************************
//I2C����Ӧ���ź�
//****************************************************************************************************
bit I2C_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
    return CY;
}
//*****************************************************************************************************
//��I2C���߷���һ���ֽ�����
//*****************************************************************************************************
void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    I2C_RecvACK();
}
//*****************************************************************************************************
//��I2C���߽���һ���ֽ�����
//******************************************************************************************************
unsigned char I2C_RecvByte()
{
    unsigned char i;
    unsigned char dat = 0;
    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}
//*****************************************************************************************************
//��I2C�豸д��һ���ֽ�����
//*****************************************************************************************************
void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    I2C_Start();                  //��ʼ�ź�
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
    I2C_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                   //����ֹͣ�ź�
}
//*******************************************************************************************************
//��I2C�豸��ȡһ���ֽ�����
//*******************************************************************************************************
unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress+1);  //�����豸��ַ+���ź�
	REG_data=I2C_RecvByte();       //�����Ĵ�������
	I2C_SendACK(1);                //����Ӧ���ź�
	I2C_Stop();                    //ֹͣ�ź�
	return REG_data;
}
//******************************************************************************************************
//��ʼ��MPU6050
//******************************************************************************************************
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//�������״̬
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//******************************************************************************************************
//�ϳ�����
//******************************************************************************************************
int GetData(unsigned char REG_Address)
{
	unsigned char H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return ((H<<8)+L);   //�ϳ�����
}

//******????************
float Accel_ax;
float Accel_az;             //X???????
float Angle;         //????????
unsigned char value;                 //????????
//*********************************************************
// ????(?????)
//*********************************************************

float Angle_Calcu(void)         
{
		Accel_ax  = GetData(ACCEL_YOUT_H);          //??X????
		Accel_az  = GetData(ACCEL_ZOUT_H);          //??X????
		Angle = (int)(atan(Accel_ax/Accel_az)*180/3.14);
		return Angle;                                                                                                          
} 


#endif
#if CONFIG_OLED == ENABLED
/************************************6*8�ĵ���************************************/
const unsigned char code F6x8[][6] =		
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp

};
/****************************************8*16�ĵ���************************************/
const unsigned char code F8X16[]=	  
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// 0
  0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1
  0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2
  0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3
  0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4
  0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5
  0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6
  0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7
  0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8
  0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9
  0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10
  0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14
  0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16
  0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17
  0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18
  0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19
  0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20
  0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21
  0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22
  0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23
  0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25
  0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26
  0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 27
  0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28
  0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 29
  0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30
  0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 31
  0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 32
  0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33
  0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34
  0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35
  0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38
  0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40
  0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41
  0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42
  0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43
  0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44
  0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45
  0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47
  0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49
  0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50
  0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51
  0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53
  0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54
  0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55
  0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56
  0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57
  0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58
  0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59
  0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60
  0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61
  0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63
  0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65
  0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66
  0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67
  0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69
  0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71
  0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72
  0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73
  0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74
  0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75
  0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77
  0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79
  0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80
  0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81
  0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83
  0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84
  0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86
  0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87
  0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89
  0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90
  0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91
  0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92
  0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93
  0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94
};
unsigned char code Hzk[][32]={

{0x00,0x40,0x42,0x44,0x58,0x40,0x40,0x7F,0x40,0x40,0x50,0x48,0xC6,0x00,0x00,0x00},
{0x00,0x40,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFF,0x00,0x00,0x00},/*"?",0*/


};

void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}
/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

void IIC_Wait_Ack()
{

	//GPIOB->CRH &= 0XFFF0FFFF;	//����PB12Ϊ��������ģʽ
	//GPIOB->CRH |= 0x00080000;
//	OLED_SDA = 1;
//	delay_us(1);
	//OLED_SCL = 1;
	//delay_us(50000);
/*	while(1)
	{
		if(!OLED_SDA)				//�ж��Ƿ���յ�OLED Ӧ���ź�
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//����PB12Ϊͨ���������ģʽ
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

   Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}


}

/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//��������

	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//��ʼ��SSD1306					    
void OLED_Init(void)
{ 	
 
OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  


#endif

#if CONFIG_BMP180 == ENABLED
#include  <INTRINS.H> //Keil library  
#include  <math.h>    //Keil library 
typedef unsigned char  BYTE;
typedef unsigned short WORD;

void delay(unsigned int k)	
{						
unsigned int i,j;				
for(i=0;i<k;i++)
{			
for(j=0;j<121;j++)			
{;}}						
}
/**************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
��ʼ�ź�
**************************************/
void BMP180_Start(uchar channal)
{
		if(channal==0)
		{
			SDA(0) = 1;                    //����������
			SCL(0) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			SDA(0) = 0;                    //�����½���
			Delay5us();                 //��ʱ
			SCL(0) = 0;                    //����ʱ����			
		}else
		{
			SDA(1) = 1;                    //����������
			SCL(1) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			SDA(1) = 0;                    //�����½���
			Delay5us();                 //��ʱ
			SCL(1) = 0;                    //����ʱ����					
		}

}

/**************************************
ֹͣ�ź�
**************************************/
void BMP180_Stop(uchar channal)
{
		if(channal==0)
		{
			SDA(0) = 0;                    //����������
			SCL(0) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			SDA(0) = 1;                    //����������
			Delay5us();                 //��ʱ		
		}else
		{
			SDA(1) = 0;                    //����������
			SCL(1) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			SDA(1) = 1;                    //����������
			Delay5us();                 //��ʱ			
		}	

}
/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BMP180_SendACK(bit ack,uchar channal)
{
		if(channal==0)
		{
			SDA(0) = ack;                  //дӦ���ź�
			SCL(0) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			SCL(0) = 0;                    //����ʱ����
			Delay5us();                 //��ʱ
		}else
		{
			SDA(1) = ack;                  //дӦ���ź�
			SCL(1) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			SCL(1) = 0;                    //����ʱ����
			Delay5us();                 //��ʱ		
		}		

}
/**************************************
����Ӧ���ź�
**************************************/
bit BMP180_RecvACK(uchar channal)
{  	
		if(channal==0)
		{
			SCL(0) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			CY = SDA(0) ;                   //��Ӧ���ź�
			SCL(0) = 0;                    //����ʱ����
			Delay5us();                 //��ʱ
		}else
		{
			SCL(1) = 1;                    //����ʱ����
			Delay5us();                 //��ʱ
			CY = SDA(1) ;                   //��Ӧ���ź�
			SCL(1) = 0;                    //����ʱ����
			Delay5us();                 //��ʱ		
		}	
		return CY;	
}
/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BMP180_SendByte(BYTE dat,uchar channal)
{
    BYTE i;
		if(channal==0)
		{
			for (i=0; i<8; i++)         //8λ������
			{
					dat <<= 1;              //�Ƴ����ݵ����λ
					SDA(0) = CY;               //�����ݿ�
					SCL(0) = 1;                //����ʱ����
					Delay5us();             //��ʱ
					SCL(0) = 0;                //����ʱ����
					Delay5us();             //��ʱ
			}
		}else
		{
			for (i=0; i<8; i++)         //8λ������
			{
					dat <<= 1;              //�Ƴ����ݵ����λ
					SDA(1) = CY;               //�����ݿ�
					SCL(1) = 1;                //����ʱ����
					Delay5us();             //��ʱ
					SCL(1) = 0;                //����ʱ����
					Delay5us();             //��ʱ
			}		
		}	

    BMP180_RecvACK(channal);
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE BMP180_RecvByte(uchar channal)
{
    BYTE i;
    BYTE dat = 0;		
		if(channal==0)
		{

			SDA(0) = 1;                    //ʹ���ڲ�����,׼����ȡ����,
			for (i=0; i<8; i++)         //8λ������
			{
					dat <<= 1;
					SCL(0) = 1;                //����ʱ����
					Delay5us();             //��ʱ
					dat |= SDA(0);             //������               
					SCL(0) = 0;                //����ʱ����
					Delay5us();             //��ʱ
			}
		}else
		{
			SDA(1) = 1;                    //ʹ���ڲ�����,׼����ȡ����,
			for (i=0; i<8; i++)         //8λ������
			{
					dat <<= 1;
					SCL(1) = 1;                //����ʱ����
					Delay5us();             //��ʱ
					dat |= SDA(1);             //������               
					SCL(1) = 0;                //����ʱ����
					Delay5us();             //��ʱ
			}		
		}			
		
    return dat;
}

//*********************************************************
//����BMP180�ڲ�����,��������
//*********************************************************
short Multiple_read(uchar ST_Address,uchar channal)
{   
		uchar msb, lsb;
		short _data;
    BMP180_Start(channal);                          //��ʼ�ź�
    BMP180_SendByte(BMP180_SlaveAddress,channal);    //�����豸��ַ+д�ź�
    BMP180_SendByte(ST_Address,channal);             //���ʹ洢��Ԫ��ַ
    BMP180_Start(channal);                          //��ʼ�ź�
    BMP180_SendByte(BMP180_SlaveAddress+1,channal);         //�����豸��ַ+���ź�

    msb = BMP180_RecvByte(channal);                 //BUF[0]�洢
    BMP180_SendACK(0,channal);                       //��ӦACK
    lsb = BMP180_RecvByte(channal);     
		BMP180_SendACK(1,channal);                       //���һ��������Ҫ��NOACK

    BMP180_Stop(channal);                           //ֹͣ�ź�
    Delay5ms();
    _data = msb << 8;
		_data |= lsb;	
		return _data;
}
//********************************************************************
long bmp180ReadTemp(uchar channal)
{

    BMP180_Start(channal);                  //��ʼ�ź�
    BMP180_SendByte(BMP180_SlaveAddress,channal);   //�����豸��ַ+д�ź�
    BMP180_SendByte(0xF4,channal);	          // write register address
    BMP180_SendByte(0x2E,channal);       	// write register data for temp
    BMP180_Stop(channal);                   //����ֹͣ�ź�
		delay(10);	// max time is 4.5ms
	
	return (long) Multiple_read(0xF6,channal);
}

long bmp180ReadPressure(uchar channal)
{
	long pressure = 0;

    BMP180_Start(channal);                   //��ʼ�ź�
    BMP180_SendByte(BMP180_SlaveAddress,channal);   //�����豸��ַ+д�ź�
    BMP180_SendByte(0xF4,channal);	          // write register address
    BMP180_SendByte(0x34,channal);       	  // write register data for pressure
    BMP180_Stop(channal);                    //����ֹͣ�ź�
	delay(10);    	                  // max time is 4.5ms
	
	pressure = Multiple_read(0xF6,channal);
	pressure &= 0x0000FFFF;
	
	return pressure;	
	//return (long) bmp085ReadShort(0xF6);
}
//��ʼ��BMP180��������Ҫ��ο�pdf�����޸�**************
void Init_BMP180(uchar channal,_bmp180* tBmpValue)
{
	tBmpValue->AC1 = Multiple_read(0xAA,channal);
	tBmpValue->AC2 = Multiple_read(0xAC,channal);
	tBmpValue->AC3 = Multiple_read(0xAE,channal);
	tBmpValue->AC4 = Multiple_read(0xB0,channal);
	tBmpValue->AC5 = Multiple_read(0xB2,channal);
	tBmpValue->AC6 = Multiple_read(0xB4,channal);
	tBmpValue->B1 =  Multiple_read(0xB6,channal);
	tBmpValue->B2 =  Multiple_read(0xB8,channal);
	tBmpValue->MB =  Multiple_read(0xBA,channal);
	tBmpValue->MC =  Multiple_read(0xBC,channal);
	tBmpValue->MD =  Multiple_read(0xBE,channal);
}
long bmp180Convert(uchar channal,_bmp180 tBmpValue)
{
	long ut;
	long up;
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;
	long  temperature;
	long  pressure;
	
	ut = bmp180ReadTemp(channal);
	ut = bmp180ReadTemp(channal);	   // ��ȡ�¶�
	up = bmp180ReadPressure(channal);
	up = bmp180ReadPressure(channal);  // ��ȡѹǿ
	
	x1 = ((long)ut - tBmpValue.AC6) * tBmpValue.AC5 >> 15;
	x2 = ((long) tBmpValue.MC << 11) / (x1 + tBmpValue.MD);
	b5 = x1 + x2;
	 temperature = (b5 + 8) >> 4;
	 
     //*************
	
	b6 = b5 - 4000;
	x1 = (tBmpValue.B2 * (b6 * b6 >> 12)) >> 11;
	x2 = tBmpValue.AC2 * b6 >> 11;
	x3 = x1 + x2;
	b3 = (((long)tBmpValue.AC1 * 4 + x3) + 2)/4;
	x1 = tBmpValue.AC3 * b6 >> 13;
	x2 = (tBmpValue.B1 * (b6 * b6 >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (tBmpValue.AC4 * (unsigned long) (x3 + 32768)) >> 15;
	b7 = ((unsigned long) up - b3) * (50000 >> OSS);
	if( b7 < 0x80000000)
	     p = (b7 * 2) / b4 ;
           else  
		    p = (b7 / b4) * 2;
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	 pressure = (p + ((x1 + x2 + 3791) >> 4))/10;
	 return pressure;
}
#endif

