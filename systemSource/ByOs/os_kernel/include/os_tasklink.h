/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#ifndef OS_TASKLINK_H__
#define OS_TASKLINK_H__

#include "os_task.h"

typedef struct task_order_link_t
{
	by_task_t *head_node;
	unsigned int count_node;
}task_order_link_t;

extern task_order_link_t t_order_link;

extern int os_input_link(by_task_t * _task);
extern int os_output_link(by_task_t * _task);
extern void os_order_link_init(by_task_t * _task);
#endif //OS_TASKLINK_H__
