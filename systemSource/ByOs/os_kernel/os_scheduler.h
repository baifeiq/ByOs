#ifndef SWITCH_H__
#define SWITCH_H__
#include "os_config.h"

extern tTask *currentTask;
extern tTask *nextTask;

extern void ost_startup_init(void);
extern void os_sched(void);

extern uint32_t os_enter_critical(void);
extern void os_quit_critical(uint32_t os_PRIMASK);

#endif  //SWITCH_H__
