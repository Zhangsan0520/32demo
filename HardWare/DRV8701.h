#ifndef __DRV8701_H__
#define __DRV8701_H__

#include "stdint.h"
#include "stm32g4xx_hal.h"

#define DRV8701_MAX_DUTY 1000

typedef enum
{
   MOTOR_A = 0,
   MOTOR_B = 1,
   MOTOR_C = 2,
   MOTOR_D = 3,
   MOTOR_COUNT = 4
}DRV8701_Motor_t;



#endif 