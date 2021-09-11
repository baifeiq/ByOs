/*******************************************************************************
 * @file     os_example.c
 * @brief    This file provides Example for creating basic tasks and idle tasks in ByOs
 * @version  V1.0.0
 * @date     2021/07/12
 * @author   Baifeiq
 * @note     nothing
 ******************************************************************************/
//#include "cy_project.h"
//#include "cy_device_headers.h"

#include "os_example.h"
#include "os_task.h"
#include "os_scheduler.h"
#include "os_systick.h"

tTask tTask0;
tTask tTask1;
tTask tTask2;
tTask tTask3;
tTask tTask4;
tTask tTask5;
tTask tTask6;
tTask tTask30;


tTaskStack tTask0Env[1024/4];
tTaskStack tTask1Env[1024/4];
tTaskStack tTask2Env[1024/4];
tTaskStack tTask3Env[1024/4];
tTaskStack tTask4Env[1024/4];
tTaskStack tTask5Env[1024/4];
tTaskStack tTask6Env[1024/4];
tTaskStack tTask30Env[1024/4];


void task0(void *param);
void task1(void *param);
void task2(void *param);
void task3(void *param);
void task4(void *param);
void task5(void *param);
void task6(void *param);
void task30(void *param);



int UserTaskInit(void)
{
	_tTaskInit(&tTask0, task0, (void *)0x00000000, 0, &tTask0Env[1024/4]);
	_tTaskInit(&tTask1, task1, (void *)0x11111111, 1, &tTask1Env[1024/4]);
	_tTaskInit(&tTask2, task2, (void *)0x22222222, 2, &tTask2Env[1024/4]);
	_tTaskInit(&tTask3, task3, (void *)0x33333333, 3, &tTask3Env[1024/4]);
	_tTaskInit(&tTask4, task4, (void *)0x44444444, 4, &tTask4Env[1024/4]);
	_tTaskInit(&tTask5, task5, (void *)0x55555555, 5, &tTask5Env[1024/4]);
	_tTaskInit(&tTask6, task6, (void *)0x66666666, 6, &tTask6Env[1024/4]);
	_tTaskInit(&tTask30, task30, (void *)0x66666666, 30, &tTask30Env[1024/4]);

     SysTickInit();
	_tTaskRunFirst();
	
	return 0;
}


void task0(void *param)
{
	while(1)
	{
 		_taskDelay(50);
	}
}

void task1(void *param)
{
	while(1)
	{
		_taskDelay(100);
	} 
}

void task2(void *param)
{
	while(1)
	{
		_taskDelay(200);
	} 
}

void task3(void *param)
{
	while(1)
	{
		_taskDelay(300);
	} 
}

void task4(void *param)
{
	while(1)
	{
		_taskDelay(400);
	} 
}

void task5(void *param)
{
	while(1)
	{
//        Cy_GPIO_Inv(USER_LED_PORT, USER_LED_PIN);
		_taskDelay(500);
	} 
}

void task6(void *param)
{
	while(1)
	{
		_taskDelay(600);
	} 
}

void task30(void *param)
{
	while(1)
	{
 		_taskDelay(10);
	} 	
}

