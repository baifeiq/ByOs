/*******************************************************************************
 * @file     os_task.c
 * @brief    The management of rtos task for ByOs
 * @version  V1.0.0
 * @date     2021/07/12
 * @author   Baifeiq
 * @note     nothing
 ******************************************************************************/

#include "os_type.h"
#include "os_task.h"
#include "os_scheduler.h"
#include "os_tasklink.h"


tTask *taskTable[OS_TASK_MAX + 1];  //OS_TASK_MAX is user's task num, 1 is the idle task.

uint32_t TaskOder = 0x00;
static const uint8_t TaskOderBit[256] = 
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


void os_set_bit(uint8_t numBit)
{
	TaskOder |= (0x01 << numBit);
}


void os_reset_bit(uint8_t numBit)
{
	TaskOder &= ~(0x01 << numBit);
}


uint8_t os_get_oder_pro(uint32_t value)
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


int8_t ost_init(tTask *task, void (*entry)(void *), void *param, uint8_t Pro, tTaskStack *stack)
{
	_NULL_CHECK(task);
	_NULL_CHECK(stack);
	if (Pro > OS_TASK_MAX)
	{
		return -1;
	}
	
	*(--stack) = (unsigned long)(1<<24);		//xPSR
	*(--stack) = (unsigned long)entry;			//PC,R13
	*(--stack) = (unsigned long)0x14;			//LR
	*(--stack) = (unsigned long)0x12;			//R12
	*(--stack) = (unsigned long)0x03;			//R3
	*(--stack) = (unsigned long)0x02;			//R2
	*(--stack) = (unsigned long)0x01;			//R1
	*(--stack) = (unsigned long)param;			//R0
	*(--stack) = (unsigned long)0x11;			//R11
	*(--stack) = (unsigned long)0x10;			//R10
	*(--stack) = (unsigned long)0x09;			//R9
	*(--stack) = (unsigned long)0x08;			//R8
	*(--stack) = (unsigned long)0x07;			//R7
	*(--stack) = (unsigned long)0x06;			//R6
	*(--stack) = (unsigned long)0x05;			//R5
	*(--stack) = (unsigned long)0x04;			//R4

	task->stack	= stack;
	task->pro = Pro;
	task->status = OS_READY;
	task->timer = 0;
	task->last_node = _NULL;
	task->next_node = _NULL;

	taskTable[Pro] = task;
	
	os_set_bit(Pro);

	return 0;
}


void ost_delay(unsigned int ms)
{
	currentTask->timer = ms;
	currentTask->status = OS_ORDER;
	//ResetBit(GetTaskOderPro(TaskOder));
    os_reset_bit(currentTask->pro);

	os_input_link(currentTask);
	os_sched();
}


// tTask * GetnextTask(void)
// {
// 	return (taskTable[GetTaskOderPro(TaskOder)]);
// }
