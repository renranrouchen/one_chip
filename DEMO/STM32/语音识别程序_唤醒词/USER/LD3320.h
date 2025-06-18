#ifndef LD_CHIP_H
#define LD_CHIP_H

#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long

//以下五个状态定义用来记录程序是在运行ASR识别过程中的哪个状态
#define LD_ASR_NONE			0x00	 /*表示没有在作ASR识别*/
#define LD_ASR_RUNING		0x01	 /*表示LD3320正在作ASR识别中*/
#define LD_ASR_FOUNDOK		0x10	 /*表示一次识别流程结束后，有一个识别结果*/
#define LD_ASR_FOUNDZERO 	0x11	 /*表示一次识别流程结束后，没有识别结果*/
#define LD_ASR_ERROR	 	0x31	 /*表示一次识别流程中LD3320芯片内部出现不正确的状态*/


#define CLK_IN   		    22.1184	 /*用户注意修改输入的晶振时钟大小*/
#define LD_PLL_11			(uint8)((CLK_IN/2.0)-1)
#define LD_PLL_MP3_19		0x0f
#define LD_PLL_MP3_1B		0x18
#define LD_PLL_MP3_1D   	(uint8)(((90.0*((LD_PLL_11)+1))/(CLK_IN))-1)

#define LD_PLL_ASR_19 		(uint8)(CLK_IN*32.0/(LD_PLL_11+1)-0.51)
#define LD_PLL_ASR_1B 		0x48
#define LD_PLL_ASR_1D 		0x1f

//函数声明
void LD_Reset();
void LD_Init_Common();
void LD_Init_ASR();
uint8 RunASR(void);
void LD_AsrStart();
uint8 LD_AsrRun();
uint8 LD_AsrAddFixed();
uint8 LD_GetResult();

//识别码客户修改处 
#define CODE_START  0
#define CODE_CMD1   1      
#define CODE_CMD2	2	
#define CODE_CMD3	3	   
#define CODE_CMD4   4	
#define CODE_CMD5   5	
#define CODE_CMD6   6		
#define CODE_CMD7   7   
#define CODE_CMD8	8	
#define CODE_CMD9	9	   
#define CODE_CMD10  10		
#define CODE_CMD11  11	
#define CODE_CMD12  12
#define CODE_CMD13  13    
#define CODE_CMD14	14	
#define CODE_CMD15	15	   
#define CODE_CMD16  16		
#define	CODE_CMD17  17
#define	CODE_CMD18  18
#define	CODE_CMD19  19
#define	CODE_CMD20  20
#define	CODE_CMD21  21
#define	CODE_CMD22  22
#define	CODE_CMD23  23
#define	CODE_CMD24  24
#define	CODE_CMD25  25
#define	CODE_CMD26  26
#define	CODE_CMD27  27
#define	CODE_CMD28  28
#define	CODE_CMD29  29
#define	CODE_CMD30  30
#define	CODE_CMD31  31
#define	CODE_CMD32  32
#define	CODE_CMD33  33
#define	CODE_CMD34  34
#define	CODE_CMD35  35
#define	CODE_CMD36  36
#define	CODE_CMD37  37
#define	CODE_CMD38  38
#define	CODE_CMD39  39
#define	CODE_CMD40  40

//数值越大越灵敏识别距离越远，但误识别率就越大， 根据自己的实际情况调节。
#define MIC_VOL 0x55	 //咪头增益（灵敏度调节） 范围：00-7f 
#endif
