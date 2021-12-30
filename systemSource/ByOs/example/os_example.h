/*******************************************************************************
 * Copyright (c) baifeiq.
 * 
 * @date            @author         @brief
 * 2021-07-12       baifeiq         First version: Function interface for users with initialization tasks.
 * 2021-12-30       baifeiq         Reorganize the coding style.
 */

#ifndef EXAMPLEOS_H__
#define EXAMPLEOS_H__

#define USER_LED_PORT           CY_LED0_PORT
#define USER_LED_PIN            CY_LED0_PIN
#define USER_LED_PIN_MUX        CY_LED0_PIN_MUX

extern int user_task_init(void);

#endif//EXAMPLEOS_H__