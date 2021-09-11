#ifndef __EXAMPLEOS_H__
#define __EXAMPLEOS_H__

#define USER_LED_PORT           CY_LED0_PORT
#define USER_LED_PIN            CY_LED0_PIN
#define USER_LED_PIN_MUX        CY_LED0_PIN_MUX

extern int UserTaskInit(void);

#endif//__EXAMPLEOS_H__