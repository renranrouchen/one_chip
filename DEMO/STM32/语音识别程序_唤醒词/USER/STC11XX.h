sfr ACC  = 0xE0;                                                          
sfr B    = 0xF0;
sfr PSW  = 0xD0; 
sbit CY  = PSW^7;
sbit AC  = PSW^6;
sbit F0  = PSW^5;
sbit RS1 = PSW^4;
sbit RS0 = PSW^3;
sbit OV  = PSW^2;
sbit P   = PSW^0;
sfr SP   = 0x81;                                   
sfr DPL  = 0x82;                                        
sfr DPH  = 0x83;                                  
sfr PCON   = 0x87;
sfr AUXR  = 0x8E;
sfr AUXR1 = 0xA2;
sfr WAKE_CLKO = 0x8F;
sfr CLK_DIV = 0x97;
sfr BUS_SPEED = 0xA1; 
sfr IE      = 0xA8; 
sbit EA       = IE^7;
sbit ELVD     = IE^6; 
sbit EADC     = IE^5;
sbit ES       = IE^4;
sbit ET1      = IE^3;
sbit EX1      = IE^2;
sbit ET0      = IE^1;
sbit EX0      = IE^0;
sfr IE2       = 0xAF;
sfr IP      = 0xB8;
sbit PPCA     = IP^7;
sbit PLVD     = IP^6; 
sbit PADC     = IP^5;
sbit PS       = IP^4;
sbit PT1      = IP^3;
sbit PX1      = IP^2;
sbit PT0      = IP^1;
sbit PX0      = IP^0;                               
sfr IPH   = 0xB7; 
sfr IP2   = 0xB5; 
sfr IPH2  = 0xB6; 
sfr P0   = 0x80; 
sfr P0M0 = 0x94;                   
sfr P0M1 = 0x93;                                                                 
sfr P1   = 0x90;
sfr P1M0 = 0x92; 
sfr P1M1 = 0x91; 
sfr P1ASF = 0x9D;
sfr P2   = 0xA0; 
sfr P2M0 = 0x96;                                                                    
sfr P2M1 = 0x95;                                                                  
sfr P3   = 0xB0; 
sfr P3M0 = 0xB2;                                                                        
sfr P3M1 = 0xB1;                                                                       
sfr P4   = 0xC0; 
sfr P4M0 = 0xB4;                                                                       
sfr P4M1 = 0xB3;                                                                     
sfr P4SW = 0xBB;
sfr P5   = 0xC8;
sfr P5M0 = 0xCA;
sfr P5M1 = 0xC9;
sfr TCON = 0x88;
sbit TF1 = TCON^7;
sbit TR1 = TCON^6;
sbit TF0 = TCON^5;
sbit TR0 = TCON^4;
sbit IE1 = TCON^3;
sbit IT1 = TCON^2;
sbit IE0 = TCON^1;
sbit IT0 = TCON^0;
sfr TMOD = 0x89;
sfr TL0  = 0x8A; 
sfr TH0  = 0x8C;
sfr TL1  = 0x8B;
sfr TH1  = 0x8D; 
sfr SCON = 0x98;
sbit SM0 = SCON^7;
sbit SM1 = SCON^6;
sbit SM2 = SCON^5;
sbit REN = SCON^4;
sbit TB8 = SCON^3;
sbit RB8 = SCON^2;
sbit TI  = SCON^1;
sbit RI  = SCON^0;
sfr SBUF = 0x99;                                               
sfr SADEN = 0xB9;                                                
sfr SADDR = 0xA9;                                                                             
sfr S2CON = 0x9A;
sfr S2BUF = 0x9B;
sfr BRT = 0x9C;
sfr WDT_CONTR = 0xC1; 
sfr CCON   = 0xD8;
sbit CF     = CCON^7; 
sbit CR     = CCON^6;
sbit CCF1   = CCON^1;
sbit CCF0   = CCON^0; 
sfr CMOD  = 0xD9;
sfr CL     = 0xE9;
sfr CH     = 0xF9; 
sfr CCAPM0 = 0xDA;
sfr CCAPM1 = 0xDB; 
sfr CCAP0L = 0xEA;
sfr CCAP0H = 0xFA;
sfr CCAP1L = 0xEB; 
sfr CCAP1H = 0xFB;
sfr PCA_PWM0 = 0xF2;
sfr PCA_PWM1 = 0xF3;
sfr ADC_CONTR = 0xBC;
sfr ADC_RES  = 0xBD;  
sfr ADC_RESL = 0xBE;  
sfr SPCTL  = 0xCE; 
sfr SPSTAT = 0xCD; 
sfr SPDAT  = 0xCF; 
sfr IAP_DATA    = 0xC2;
sfr IAP_ADDRH   = 0xC3;
sfr IAP_ADDRL   = 0xC4;
sfr IAP_CMD     = 0xC5; 
sfr IAP_TRIG    = 0xC6;
sfr IAP_CONTR   = 0xC7;

