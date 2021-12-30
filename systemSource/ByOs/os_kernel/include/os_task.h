/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version: Define structure of task.
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#ifndef	OS_TASK_H__
#define OS_TASK_H__

#include "os_type.h"

#define OS_TASK_MAX         32   //The max number of ByOs's tasks

typedef enum
{
	OS_RUN,
	OS_ORDER,
	OS_READY,
}task_status_t;

typedef struct by_task
{
	by_uint32_t		*stack_addr;
	by_uint8_t		pro;
	task_status_t	status;
	by_uint32_t		timer;
	struct by_task	*next_node;
	struct by_task	*last_node;
}by_task_t;

extern by_task_t *task_table[OS_TASK_MAX + 1];  //OS_TASK_MAX is user's task num, 1 is the idle task.

extern by_uint32_t task_oder;

extern void os_bit_set(by_uint8_t numBit);
extern void os_bit_reset(by_uint8_t numBit);
extern by_uint8_t os_get_oder_pro(by_uint32_t value);
// extern by_task_t *GetnextTask(void);

extern void ost_delay(unsigned int ms);
extern by_int32_t ost_init(by_task_t *task, void (*entry)(void *), void *param, by_uint8_t Pro, by_uint32_t *stack_addr);


#endif	//OS_TASK_H__

