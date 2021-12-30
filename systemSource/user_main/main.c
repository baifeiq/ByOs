/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version: main program.
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#include "os_example.h"
#if defined (ARMCM4)
  #include "ARMCM4.h"
#elif defined (ARMCM4_FP)
  #include "ARMCM4_FP.h"
#else
  #error device not specified!
#endif


void main(void)
{
    __disable_irq();
    user_task_init();
    __enable_irq();

    while(1);
}