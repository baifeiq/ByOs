#ifndef __OS_TASKLINK_H__
#define __OS_TASKLINK_H__

#include "os_task.h"

typedef struct Task_Order_Link_t
{
	tTask *head_node;
	unsigned int count_node;
}Task_Order_Link_t;

extern Task_Order_Link_t _taskOrderLink;

extern int _tInputLink(tTask * _task);
extern int _tOutputLink(tTask * _task);
extern void _taskOrderLink_Init(tTask * _task);
#endif //__OS_TASKLINK_H__
