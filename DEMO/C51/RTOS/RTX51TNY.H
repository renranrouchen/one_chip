/*--------------------------------------------------------------------------
RTX51TNY.H

Prototypes for RTX51 Tiny Real-Time Operating System Version 2.02
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __RTX51TNY_H__
#define __RTX51TNY_H__


/* 函数任务等待的事件类型 */
#define K_SIG      0x01              /* 等待一个信号 */
#define K_TMO      0x02              /* 等待一个以滴答值为单位的超时 */
#define K_IVL      0x80              /* 等待滴答值为单位的时间间隔   */

/* function return values 函数返回值 */
#define NOT_OK     0xFF              /* 无效操作 */
#define TMO_EVENT  0x08              /* 超时完成或时间间隔到*/
#define SIG_EVENT  0x04              /* 收到一个信号 */
#define RDY_EVENT  0x80    /* 任务的就绪标志位是被os_set_ready或isr_set_ready置位的 */

extern unsigned char os_create_task     (unsigned char task_id);/*添加任务到列表，并标记为就绪*/
extern unsigned char os_delete_task     (unsigned char task_id);/*停止任务task_id，并从任务列表中删除*/
/*数挂起当前任务，并等待一个或几个事件*/
extern unsigned char os_wait            (unsigned char typ,   /*要等待的事件*/
                                         unsigned char ticks, /*要等待的周期数*/
                                         unsigned int dummy); /*无用参数*/
extern unsigned char os_wait1           (unsigned char typ);  /*要等待的事件*/
extern unsigned char os_wait2           (unsigned char typ,	  /*要等待的事件*/
                                         unsigned char ticks);/*要等待的周期数*/

extern unsigned char os_send_signal     (unsigned char task_id);/*向任务task_id发送一个信号*/
extern unsigned char os_clear_signal    (unsigned char task_id);/*清除任务task_id的信号标志*/
extern unsigned char isr_send_signal    (unsigned char task_id);/*向任务task_id发送一个信号*/

extern void          os_set_ready       (unsigned char task_id);/*将任务task_id置为就绪状态*/
extern void          isr_set_ready      (unsigned char task_id);/*将任务task_id置为就绪状态*/

extern unsigned char os_running_task_id (void);	 /*获取当前正在执行的任务的任务ID*/
extern unsigned char os_switch_task     (void);  /*停止当前任务，运行另一个任务*/
/*纠正由于os_wait函数同时等待K_IVL和K_SIG事件而产生的时间问题*/
extern void          os_reset_interval  (unsigned char ticks);

#endif
