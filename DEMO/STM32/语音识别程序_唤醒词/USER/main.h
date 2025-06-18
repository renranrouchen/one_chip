#ifndef _MAIN_H
#define _MAIN_H

typedef signed           char int8_t;
typedef signed short     int  int16_t;
typedef signed           int  int32_t;
typedef signed long 	 int  int64_t;
typedef unsigned         char uint8_t;
typedef unsigned short   int  uint16_t;
typedef unsigned         int  uint32_t;
typedef unsigned long    int  uint64_t;

#define ENABLE  1
#define DISABLE  0

#include <intrins.h>
#include "STC11XX.h"
#include "LD3320.h"
#include "Reg.h"
#include "usart.h"
sbit LED=P4^2;	//–≈∫≈÷∏ æµ∆

#define TEST		 //≤‚ ‘√¸¡Ó

#endif
