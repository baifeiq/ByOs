/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#ifndef SWITCH_H__
#define SWITCH_H__
#include "os_config.h"

extern by_task_t *currentTask;
extern by_task_t *nextTask;

extern void ost_startup_init(void);
extern void os_sched(void);

extern by_uint32_t os_critical_enter(void);
extern void os_critical_quit(by_uint32_t os_PRIMASK);

#endif  //SWITCH_H__
