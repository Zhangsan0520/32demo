#include "stm32f4xx_hal.h"
#include "main.h"
#include "tim.h"

typedef struct
{
    GPIO_TypeDef *dir_port;
    uint16_t dir_pin;
    GPIO_TypeDef *enable_port;
    uint16_t enable_pin;
    TIM_HandleTypeDef *pwm_timer;
    uint32_t pwm_channel;
    uint8_t direction_inverted;
    int16_t duty;
} DRV8701_Channel_t;

static DRV8701_Channel_t DRV8701_Channels[DRV8701_MOTOR_COUNT] = {
    DRV8701_Channels[MOTOR_A] = {
        .dir_port = MA_DIR_GPIO_Port,
        .dir_pin = MA_DIR_GPIO_Pin,
        .enable_port = MA_ENABLE_GPIO_Port,
        .enable_pin = MA_ENABLE_GPIO_Pin,
        .pwm_timer = &htim2,
        .pwm_channel = TIM_CHANNEL_1,
    },
    DRV8701_Channels[MOTOR_B] = {   
        .dir_port = MB_DIR_GPIO_Port,
        .dir_pin = MB_DIR_GPIO_Pin,
        .enable_port = MB_ENABLE_GPIO_Port,
        .enable_pin = MB_ENABLE_GPIO_Pin,
        .pwm_timer = &htim2,
        .pwm_channel = TIM_CHANNEL_2,
    },
    DRV8701_Channels[MOTOR_C] = {
        .dir_port = MC_DIR_GPIO_Port,
        .dir_pin = MC_DIR_GPIO_Pin,
        .enable_port = MC_ENABLE_GPIO_Port,
        .enable_pin = MC_ENABLE_GPIO_Pin,
        .pwm_timer = &htim2,
        .pwm_channel = TIM_CHANNEL_3,
    },
    DRV8701_Channels[MOTOR_D] = {
        .dir_port = MD_DIR_GPIO_Port,
        .dir_pin = MD_DIR_GPIO_Pin,
        .enable_port = MD_ENABLE_GPIO_Port,
        .enable_pin = MD_ENABLE_GPIO_Pin,
        .pwm_timer = &htim2,
        .pwm_channel = TIM_CHANNEL_4,
    }
};

static uint8_t DRV8701_IsvalidMotor(DRV8701_Motor_t motor)
{
    return (motor >= MOTOR_A && motor < MOTOR_COUNT);
}

static int16_t DRV8701_ClampDuty(int16_t duty)
{
    if (duty > DRV8701_MAX_DUTY)
        return DRV8701_MAX_DUTY;
    else if (duty < -DRV8701_MAX_DUTY)
        return -DRV8701_MAX_DUTY;
    else
        return duty;
}

