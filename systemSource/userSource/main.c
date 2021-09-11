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
    UserTaskInit();
    __enable_irq();

    while(1);
}