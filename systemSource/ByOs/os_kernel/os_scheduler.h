#ifndef __SWITCH_H__
#define __SWITCH_H__
#include "os_config.h"

extern tTask *currentTask;
extern tTask *nextTask;

extern void _tTaskRunFirst(void);
extern void _tTaskSched(void);

extern uint32_t _osEnterCritical(void);
extern void _osQuitCritical(uint32_t os_PRIMASK);

#endif  //__SWITCH_H__
