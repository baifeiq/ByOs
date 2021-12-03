#ifndef OS_TASKLINK_H__
#define OS_TASKLINK_H__

#include "os_task.h"

typedef struct task_order_link_t
{
	tTask *head_node;
	unsigned int count_node;
}task_order_link_t;

extern task_order_link_t t_order_link;

extern int os_input_link(tTask * _task);
extern int os_output_link(tTask * _task);
extern void os_order_link_init(tTask * _task);
#endif //OS_TASKLINK_H__
