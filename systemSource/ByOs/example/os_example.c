/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version: provides example for creating basic tasks.
 * 2021-12-30       baifeiq         Reorganize the coding style
 */


#include "os_example.h"
#include "os_task.h"
#include "os_scheduler.h"
#include "os_systick.h"

by_task_t tTask0;
by_task_t tTask1;
by_task_t tTask2;
by_task_t tTask3;
by_task_t tTask4;
by_task_t tTask5;
by_task_t tTask6;
by_task_t tTask30;


by_uint32_t tTask0Env[1024/4];
by_uint32_t tTask1Env[1024/4];
by_uint32_t tTask2Env[1024/4];
by_uint32_t tTask3Env[1024/4];
by_uint32_t tTask4Env[1024/4];
by_uint32_t tTask5Env[1024/4];
by_uint32_t tTask6Env[1024/4];
by_uint32_t tTask30Env[1024/4];


void task0(void *param);
void task1(void *param);
void task2(void *param);
void task3(void *param);
void task4(void *param);
void task5(void *param);
void task6(void *param);
void task30(void *param);



int user_task_init(void)
{
	ost_init(&tTask0, task0, (void *)0x00000000, 0, &tTask0Env[1024/4]);
	ost_init(&tTask1, task1, (void *)0x11111111, 1, &tTask1Env[1024/4]);
	ost_init(&tTask2, task2, (void *)0x22222222, 2, &tTask2Env[1024/4]);
	ost_init(&tTask3, task3, (void *)0x33333333, 3, &tTask3Env[1024/4]);
	ost_init(&tTask4, task4, (void *)0x44444444, 4, &tTask4Env[1024/4]);
	ost_init(&tTask5, task5, (void *)0x55555555, 5, &tTask5Env[1024/4]);
	ost_init(&tTask6, task6, (void *)0x66666666, 6, &tTask6Env[1024/4]);
	ost_init(&tTask30, task30, (void *)0x66666666, 30, &tTask30Env[1024/4]);

    sys_tick_init();
	ost_startup_init();
	
	return 0;
}


void task0(void *param)
{
	while(1)
	{
 		ost_delay(50);
	}
}

void task1(void *param)
{
	while(1)
	{
		ost_delay(100);
	} 
}

void task2(void *param)
{
	while(1)
	{
		ost_delay(200);
	} 
}

void task3(void *param)
{
	while(1)
	{
		ost_delay(300);
	} 
}

void task4(void *param)
{
	while(1)
	{
		ost_delay(400);
	} 
}

void task5(void *param)
{
	while(1)
	{
//        Cy_GPIO_Inv(USER_LED_PORT, USER_LED_PIN);
		ost_delay(500);
	} 
}

void task6(void *param)
{
	while(1)
	{
		ost_delay(600);
	} 
}

void task30(void *param)
{
	while(1)
	{
 		ost_delay(10);
	} 	
}

