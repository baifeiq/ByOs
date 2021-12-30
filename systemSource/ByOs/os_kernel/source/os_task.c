/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version: The management of rtos task for ByOs.
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#include "os_type.h"
#include "os_task.h"
#include "os_scheduler.h"
#include "os_tasklink.h"


by_task_t *task_table[OS_TASK_MAX + 1];  //OS_TASK_MAX is user's task num, 1 is the idle task.

by_uint32_t task_oder = 0x00;
static const by_uint8_t TaskOderBit[256] = 
{
		/*0 , 			1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, */
/*0*/	OS_TASK_MAX,	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
/*1*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*2*/	5,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*3*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*4*/	6,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*5*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*6*/	5,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*7*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*8*/	7,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*9*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*A*/	5,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*B*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*C*/	6,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*D*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*E*/	5,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
/*F*/	4,    			0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};


void os_bit_set(by_uint8_t numBit)
{
	task_oder |= (0x01 << numBit);
}


void os_bit_reset(by_uint8_t numBit)
{
	task_oder &= ~(0x01 << numBit);
}


by_uint8_t os_get_oder_pro(by_uint32_t value)
{
	if (0 == value)
		return OS_TASK_MAX;

	if (value & 0xFF)
		return TaskOderBit[(value & 0xFF)];

	if (value & 0xFF00)
		return TaskOderBit[(value & 0xFF00)>>8] + 8;

	if ((value & 0xFF0000))
		return TaskOderBit[(value & 0xFF0000)>>16] + 16;

	return TaskOderBit[(value & 0xFF000000)>>24] + 24;
}


by_int32_t ost_init(by_task_t *task, void (*entry)(void *), void *param, by_uint8_t Pro, by_uint32_t *stack_addr)
{
	OS_NULL_CHECK(task);
	OS_NULL_CHECK(stack_addr);
	if (Pro > OS_TASK_MAX)
	{
		return -1;
	}
	
	*(--stack_addr) = (unsigned long)(1<<24);		//xPSR
	*(--stack_addr) = (unsigned long)entry;			//PC,R13
	*(--stack_addr) = (unsigned long)0x14;			//LR
	*(--stack_addr) = (unsigned long)0x12;			//R12
	*(--stack_addr) = (unsigned long)0x03;			//R3
	*(--stack_addr) = (unsigned long)0x02;			//R2
	*(--stack_addr) = (unsigned long)0x01;			//R1
	*(--stack_addr) = (unsigned long)param;			//R0
	*(--stack_addr) = (unsigned long)0x11;			//R11
	*(--stack_addr) = (unsigned long)0x10;			//R10
	*(--stack_addr) = (unsigned long)0x09;			//R9
	*(--stack_addr) = (unsigned long)0x08;			//R8
	*(--stack_addr) = (unsigned long)0x07;			//R7
	*(--stack_addr) = (unsigned long)0x06;			//R6
	*(--stack_addr) = (unsigned long)0x05;			//R5
	*(--stack_addr) = (unsigned long)0x04;			//R4

	task->stack_addr	= stack_addr;
	task->pro = Pro;
	task->status = OS_READY;
	task->timer = 0;
	task->last_node = OS_NULL;
	task->next_node = OS_NULL;

	task_table[Pro] = task;
	
	os_bit_set(Pro);

	return 0;
}


void ost_delay(unsigned int ms)
{
	currentTask->timer = ms;
	currentTask->status = OS_ORDER;
	//ResetBit(GetTaskOderPro(task_oder));
    os_bit_reset(currentTask->pro);

	os_input_link(currentTask);
	os_sched();
}


// by_task_t * GetnextTask(void)
// {
// 	return (task_table[GetTaskOderPro(task_oder)]);
// }
