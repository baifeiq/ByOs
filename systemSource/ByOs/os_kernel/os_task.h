#ifndef	__OS_TASK_H__
#define __OS_TASK_H__

#include "os_type.h"

#define OS_TASK_MAX         32   //The max number of ByOs's tasks

typedef uint32_t tTaskStack;
typedef enum
{
	OS_RUN,
	OS_ORDER,
	OS_READY,
}taskStatus;

typedef struct tTask
{
	tTaskStack *stack;
	uint8_t pro;
	taskStatus status;
	uint32_t timer;
	struct tTask *next_node;
	struct tTask *last_node;
}tTask;

extern tTask *taskTable[OS_TASK_MAX + 1];  //OS_TASK_MAX is user's task num, 1 is the idle task.

extern uint32_t TaskOder;

extern void SetBit(uint8_t numBit);
extern void ResetBit(uint8_t numBit);
extern uint8_t GetTaskOderPro(uint32_t value);
// extern tTask *GetnextTask(void);

extern void _taskDelay(unsigned int ms);
extern int8_t _tTaskInit(tTask *task, void (*entry)(void *), void *param, uint8_t Pro, tTaskStack *stack);


#endif	//__OS_TASK_H__

