/*******************************************************************************
 * @file     os_scheduler.c
 * @brief    start the first task of ByOs, and monitor the TaskOder.
 * @version  V1.0.0
 * @date     2021/07/12
 * @author   Baifeiq
 * @note     nothing
 ******************************************************************************/

#include "os_task.h"
#include "os_scheduler.h"
#include "os_tasklink.h"
#include "os_config.h"

#if defined (ARMCM4)
  #include "ARMCM4.h"
#elif defined (ARMCM4_FP)
  #include "ARMCM4_FP.h"
#else
  #error device not specified!
#endif

extern void tTaskRunFirst(void);    //Interface of running the first task, which is define in os_context.s
extern void trigerPendSVC(void);    //Interface of creatting the PendSVC interrupt, which is define in os_context.s


// #define NVIC_INT_CTRL			0xE000ED04
// #define NVIC_PENDSVSET			0x10000000
// #define NVIC_SYSPRI2			    0xE000ED22
// #define NVIC_PENDSV_PRI			0x000000FF

tTask *currentTask;
tTask *nextTask;
static uint8_t TaskSchedLock;

tTask tTaskIdle;
tTaskStack tTaskIdleEnv[1024/4];

void taskIdle(void *param)
{
	while(1){;}
}


uint32_t _osEnterCritical(void)
{
    uint32_t os_PRIMASK = __get_PRIMASK ();

    //ARMCM4 CMSIS API
    __disable_irq();

    return os_PRIMASK;
}


void _osQuitCritical(uint32_t os_PRIMASK)
{
    //ARMCM4 CMSIS API
    __set_PRIMASK (os_PRIMASK);
}


void _tTaskSchedEnable()
{
    uint32_t os_PRIMASK = _osEnterCritical();

    if (TaskSchedLock < 255)
    {
        TaskSchedLock++;
    }
    
    _osQuitCritical(os_PRIMASK );
}


void _tTaskSchedDisable()
{
    uint32_t os_PRIMASK = _osEnterCritical();

    if (TaskSchedLock > 0)
    {
        TaskSchedLock--;
        if (0 == TaskSchedLock)
        {
            _tTaskSched();
        }
    }

    _osQuitCritical(os_PRIMASK);
}

//tTask *currentTask asm("ScurrentTask");       //gcc
//tTask *nextTask asm("SnextTask");             //gcc

/*  //Keil MDK
__asm void PendSV_Handler(void)              
{
    IMPORT currentTask
    IMPORT nextTask

    MRS R0, PSP 
    CBZ R0, PendSVHander_nosave
    
    STMDB   R0!, {R4-R11}
    LDR R1, =currentTask
    LDR R1, [R1]
    STR R0, [R1]
    NOP
    
PendSVHander_nosave
    LDR R0, =currentTask
    LDR R1, =nextTask
    LDR R2, [R1]
    STR R2, [R0]

    LDR R0, [R2]
    LDMIA R0!,  {R4-R11}

    MSR PSP, R0
    ORR LR, LR, #0X04
    BX LR
}*/

/*  //gcc
void PendSV_Handler(void)   
{
    asm("EXTERN currentTask"); 
    asm("EXTERN nextTask");


    asm("MRS R0, PSP"); 
    asm("CBZ R0, PendSVHander_nosave");
    
    asm("STMDB   R0!, {R4-R11}");
    asm("LDR R1, =currentTask");
    //asm volatile("bx %0" : : "r" (currentTask));
    asm("LDR R1, [R1]");
    asm("STR R0, [R1]");
    asm("NOP");
    
    asm("PendSVHander_nosave:");
    asm("LDR R0, =currentTask");
    //asm volatile("bx %0" : : "r" (currentTask));
    asm("LDR R1, =nextTask");

    asm("LDR R2, [R1]");
    asm("STR R2, [R0]");

    asm("LDR R0, [R2]");
    asm("LDMIA R0!,  {R4-R11}");

    asm("MSR PSP, R0");
    asm("ORR LR, LR, #0X04");
    asm("BX LR");
}*/

/*
void trigerPendSVC(void)
{
 	MEM8(NVIC_SYSPRI2)		=	NVIC_PENDSV_PRI;
 	MEM32(NVIC_INT_CTRL)	=	NVIC_PENDSVSET;
}*/

void _tTaskSched(void)
{
    uint32_t os_PRIMASK = _osEnterCritical();

    if (TaskSchedLock > 0)
    {
        _osQuitCritical(os_PRIMASK);
        return;
    }

    //1.This method increases the CPU consumption of switching interrupts and stacking.
    // __disable_irq();
    // nextTask = GetnextTask();
    // __enable_irq();

    //2.This method reduces the CPU consumption of switching interrupts and stacking. 
    //  Task switching should reduce the consumption of CPU
    nextTask = taskTable[GetTaskOderPro(TaskOder)]; 
    
    if (currentTask != nextTask)
    {
        trigerPendSVC();
    }    

    _osQuitCritical(os_PRIMASK);
}

void _tTaskRunFirst(void)
{
    _tTaskInit(&tTaskIdle, taskIdle, (void *)0x33333333, OS_TASK_MAX, &tTaskIdleEnv[1024/4]);
    
    //
    _taskOrderLink_Init(&tTaskIdle);

    //__set_PSP(0);             //CMSIS
    // asm("MOV r0, #0");       //gcc, iar
    // asm("MSR PSP, r0");      //gcc, iar

    // MEM8(NVIC_SYSPRI2)       = NVIC_PENDSV_PRI;
    // MEM32(NVIC_INT_CTRL)     = NVIC_PENDSVSET;

    //1.This method increases the CPU consumption of switching interrupts and stacking.
    // __disable_irq();
    // nextTask = GetnextTask();
    // __enable_irq();

    //2.This method reduces the CPU consumption of switching interrupts and stacking. 
    //  Task switching should reduce the consumption of CPU
    nextTask = taskTable[GetTaskOderPro(TaskOder)]; 

    tTaskRunFirst();
}


int osScheduler(void)
{
	tTask *p_count_task;

	unsigned int count_node = _taskOrderLink.count_node;

	_NULL_CHECK(_taskOrderLink.head_node);
    p_count_task = _taskOrderLink.head_node->next_node;
    _NULL_CHECK(p_count_task);
	
	do
	{
        p_count_task->timer--;

        if (!p_count_task->timer)
        {
            p_count_task->status = OS_READY;
            SetBit(p_count_task->pro);
            _tOutputLink(p_count_task);            
        }

		p_count_task = p_count_task->next_node;


	}while(--count_node);

	_tTaskSched();
	return 0;
}

