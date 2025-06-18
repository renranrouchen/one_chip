#include "main.h"

extern unsigned char idata nAsrStatus;
extern void delay(unsigned long uldata);
unsigned char idata ucRegVal;
void ProcessInt0(void);
/************************************************************************
������������λLDģ��
��ڲ�����none
�� �� ֵ��none
����˵����none
**************************************************************************/
void LD_Reset()
{
	RSTB=1;
	delay(5);
	RSTB=0;
	delay(5);
	RSTB=1;

	delay(5);
	CSB=0;
	delay(5);
	CSB=1;
	delay(5);
}
/************************************************************************
���������� LDģ�������ʼ��
��ڲ����� none
�� �� ֵ�� none
����˵���� �ú���Ϊ�������ã�һ�㲻��Ҫ�޸ģ�
**************************************************************************/
void LD_Init_Common()
{
	LD_ReadReg(0x06);  
	LD_WriteReg(0x17, 0x35); 
	delay(10);
	LD_ReadReg(0x06);  

	LD_WriteReg(0x89, 0x03);  
	delay(5);
	LD_WriteReg(0xCF, 0x43);   
	delay(5);
	LD_WriteReg(0xCB, 0x02);
	
	LD_WriteReg(0x11, LD_PLL_11);       
	LD_WriteReg(0x1E,0x00);
	LD_WriteReg(0x19, LD_PLL_ASR_19); 
	LD_WriteReg(0x1B, LD_PLL_ASR_1B);		
	LD_WriteReg(0x1D, LD_PLL_ASR_1D);
	delay(10);
	
    LD_WriteReg(0xCD, 0x04);
//	LD_WriteReg(0x17, 0x4c); 
	delay(5);
	LD_WriteReg(0xB9, 0x00);
	LD_WriteReg(0xCF, 0x4F); 
	LD_WriteReg(0x6F, 0xFF); 
}
/************************************************************************
����������LDģ�� ASR���ܳ�ʼ��
��ڲ�����none
�� �� ֵ��none
����˵�����ú���Ϊ�������ã�һ�㲻��Ҫ�޸ģ�
**************************************************************************/
void LD_Init_ASR()
{
	LD_Init_Common();
	LD_WriteReg(0xBD,0x00);
	LD_WriteReg(0x17,0x48);
	delay(10);
	LD_WriteReg(0x3C,0x80);    
	LD_WriteReg(0x3E,0x07);
	LD_WriteReg(0x38,0xff);    
	LD_WriteReg(0x3A,0x07);
	LD_WriteReg(0x40,0);          
	LD_WriteReg(0x42,8);
	LD_WriteReg(0x44,0);    
	LD_WriteReg(0x46,8); 
	delay(1);
}
/************************************************************************
�����������жϴ�����
��ڲ�����none
�� �� ֵ��none
����˵������LDģ����յ���Ƶ�ź�ʱ��������ú�����
		  �ж�ʶ���Ƿ��н�������û�д������üĴ���׼����һ�ε�ʶ��
**************************************************************************/
void ProcessInt0(void)
{
	unsigned char nAsrResCount=0;
	EX0=0;
	ucRegVal=LD_ReadReg(0x2B);
	LD_WriteReg(0x29,0);
	LD_WriteReg(0x02,0);
	if((ucRegVal&0x10)&&LD_ReadReg(0xb2)==0x21&&LD_ReadReg(0xbf)==0x35)			/*ʶ��ɹ�*/
	{	
		nAsrResCount=LD_ReadReg(0xba);
		if(nAsrResCount>0&&nAsrResCount<=4) 
		{
			nAsrStatus=LD_ASR_FOUNDOK;
		}
		else
	    {
			nAsrStatus=LD_ASR_FOUNDZERO;
		}	
	}															 /*û��ʶ����*/
	else
	{	 
		nAsrStatus=LD_ASR_FOUNDZERO;
	}		
	LD_WriteReg(0x2b,0);
	LD_WriteReg(0x1C,0);	//д0:ADC������
	LD_WriteReg(0x29,0);
	LD_WriteReg(0x02,0);
	LD_WriteReg(0x2B,0);
	LD_WriteReg(0xBA,0);	
	LD_WriteReg(0xBC,0);	
	LD_WriteReg(0x08,1);	//���FIFO_DATA
	LD_WriteReg(0x08,0);	//���FIFO_DATA���ٴ�д0
	EX0=1;
}
/************************************************************************
��������������ASRʶ������
��ڲ�����none
�� �� ֵ��asrflag��1->�����ɹ��� 0��>����ʧ��
����˵����ʶ��˳������:
						1��RunASR()����ʵ����һ��������ASR����ʶ������
						2��LD_AsrStart()����ʵ����ASR��ʼ��
						3��LD_AsrAddFixed()����ʵ������ӹؼ����ﵽLD3320оƬ��
						4��LD_AsrRun()����������һ��ASR����ʶ������					
						�κ�һ��ASRʶ�����̣�����Ҫ�������˳�򣬴ӳ�ʼ����ʼ��
**************************************************************************/
unsigned char RunASR(void)
{
	unsigned char i=0;
	unsigned char asrflag=0;
	for(i=0;i<5;i++)			//��ֹ����Ӳ��ԭ����LD3320оƬ����������������һ������5������ASRʶ������
	{
		LD_AsrStart();
		delay(50);
		if(LD_AsrAddFixed()==0)
		{
			LD_Reset();			//LD3320оƬ�ڲ����ֲ���������������LD3320оƬ
			delay(50);			//���ӳ�ʼ����ʼ����ASRʶ������
			continue;
		}
		delay(10);
		if(LD_AsrRun()== 0)
		{
			LD_Reset();			//LD3320оƬ�ڲ����ֲ���������������LD3320оƬ
			delay(50);			//���ӳ�ʼ����ʼ����ASRʶ������
			continue;
		}
		asrflag=1;
		break;					//ASR���������ɹ����˳���ǰforѭ������ʼ�ȴ�LD3320�ͳ����ж��ź�
	}
	return asrflag;
}
/************************************************************************
�������������LDģ���Ƿ����
��ڲ�����none
�� �� ֵ��flag��1-> ����
����˵����none
**************************************************************************/
unsigned char LD_Check_ASRBusyFlag_b2()
{
	unsigned char j;
	unsigned char flag = 0;
	for(j=0;j<10;j++)
	{
		if(LD_ReadReg(0xb2)==0x21)
		{
			flag=1;
			break;
		}
		delay(10);		
	}
	return flag;
}
/************************************************************************
��������������ASR
��ڲ�����none
�� �� ֵ��none
����˵����none
**************************************************************************/
void LD_AsrStart()
{
	LD_Init_ASR();
}
/************************************************************************
��������������ASR
��ڲ�����none
�� �� ֵ��1�������ɹ�
����˵����none
**************************************************************************/
unsigned char LD_AsrRun()
{
	EX0=0;
	LD_WriteReg(0x35,MIC_VOL);
	LD_WriteReg(0x1C,0x09);
	LD_WriteReg(0xBD,0x20);
	LD_WriteReg(0x08,0x01);
	delay(1);
	LD_WriteReg(0x08, 0x00);
	delay(1);

	if(LD_Check_ASRBusyFlag_b2()==0)
	{
		return 0;
	}
//	LD_WriteReg(0xB6,0xa); 		//ʶ��ʱ��	 1S
//	LD_WriteReg(0xB5,0x1E); 	//��������ʱ�� 300ms
//	LD_WriteReg(0xB8,10); 		//����ʱ��
//	LD_WriteReg(0x1C,0x07); 	//����˫ͨ����Ƶ�ź���Ϊ�����ź�
	LD_WriteReg(0x1C,0x0b); 	//������˷���Ϊ�����ź�
	LD_WriteReg(0xB2,0xff);
	delay(1);	
	LD_WriteReg(0x37,0x06);
	delay(1);
	LD_WriteReg(0x37,0x06);
	delay(5);
	LD_WriteReg(0x29,0x10);	
	LD_WriteReg(0xBD,0x00);
	EX0=1;
	return 1;
}
/************************************************************************
������������LDģ����ӹؼ���
��ڲ�����none
�� �� ֵ��flag��1->��ӳɹ�
����˵�����û��޸�.
1���������¸�ʽ���ƴ���ؼ��ʣ�ͬʱע���޸�sRecog ��pCode ����ĳ��ȺͶ�Ӧ����k��ѭ���á�ƴ������ʶ������һһ��Ӧ�ġ�
2�������߿���ѧϰ"����ʶ��оƬLD3320�߽��ؼ�.pdf"�й��������������մ�����÷������ṩʶ��Ч����
3����xiao jie �� Ϊ�������ÿ��ʶ��ʱ�������ȷ�һ�����С�ݡ�
**************************************************************************/
unsigned char LD_AsrAddFixed()
{
	unsigned char k, flag;
	unsigned char nAsrAddLength;
	#define DATE_A 41   /*�����ά��ֵ*/
	#define DATE_B 30	/*����һά��ֵ*/
	unsigned char code sRecog[DATE_A][DATE_B]={
"la ji fen lei",\
"can jin zhi",\
"su liao dai",\
"zhen tou",\
"da huo ji",\	
"deng pao",\
"sha chong ji",\
"lao shu yao",\
"you qi tong",\
"gu tou",\
"lan cai ye",\
"sheng fan",\
"guo pi",\
"zhi he",\
"yin liao ping",\
"jin shu",\
"bao zhi"\
};	/*��ӹؼ��ʣ��û��޸�*/
	unsigned char code pCode[DATE_A]={
CODE_START,\
CODE_CMD1,\
CODE_CMD2,\
CODE_CMD3,\
CODE_CMD4,\
CODE_CMD5,\
CODE_CMD6,\
CODE_CMD7,\
CODE_CMD8,\
CODE_CMD9,\
CODE_CMD10,\
CODE_CMD11,\
CODE_CMD12,\
CODE_CMD13,\
CODE_CMD14,\
CODE_CMD15,\
CODE_CMD16,\
CODE_CMD17,\
CODE_CMD18,\
CODE_CMD19,\
CODE_CMD20,\
CODE_CMD21,\
CODE_CMD22,\
CODE_CMD23,\
CODE_CMD24,\
CODE_CMD25,\
CODE_CMD26,\
CODE_CMD27,\
CODE_CMD28,\
CODE_CMD29,\
CODE_CMD30,\
CODE_CMD31,\
CODE_CMD32,\
CODE_CMD33,\
CODE_CMD34,\
CODE_CMD35,\
CODE_CMD36,\
CODE_CMD37,\
CODE_CMD38,\
CODE_CMD39,\
CODE_CMD40
};	/*���ʶ���룬�û��޸�*/	
	flag=1;
	for(k=0;k<DATE_A;k++)
	{			
		if(LD_Check_ASRBusyFlag_b2()==0)
		{
			flag=0;
			break;
		}	
		LD_WriteReg(0xc1,pCode[k]);
		LD_WriteReg(0xc3,0);
		LD_WriteReg(0x08,0x04);
		delay(1);
		LD_WriteReg(0x08,0x00);
		delay(1);
		for(nAsrAddLength=0;nAsrAddLength<DATE_B;nAsrAddLength++)
		{
			if(sRecog[k][nAsrAddLength]==0)
				break;
			LD_WriteReg(0x5,sRecog[k][nAsrAddLength]);
		}
		LD_WriteReg(0xb9,nAsrAddLength);
		LD_WriteReg(0xb2,0xff);
		LD_WriteReg(0x37,0x04);
	}
    return flag;
}
/************************************************************************
������������ȡʶ����
��ڲ�����none
�� �� ֵ��LD_ReadReg(0xc5 )����ȡ�ڲ��Ĵ�������ʶ���롣
����˵����none
**************************************************************************/
unsigned char LD_GetResult()
{		
	return LD_ReadReg(0xc5);
}