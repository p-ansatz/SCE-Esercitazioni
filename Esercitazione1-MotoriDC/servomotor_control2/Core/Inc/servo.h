/* Includes */
#include "stm32f4xx_hal.h"
#include <math.h>

// MIN pulse width = 1*Counter/20 if 1ms if MIN for the motor
#define SERVO_MIN_MS	10
// MAX pulse width = 2*Counter/20 if 2ms if MAX for the motor
#define SERVO_MAX_MS	20

/* Structure for SERVO Motor */
typedef struct {
    TIM_HandleTypeDef* PWM_timer_handler;
} SERVO_t;

/* Functions */
void SERVO_init(SERVO_t* servo_struct, TIM_HandleTypeDef* PWM_timer);

void SERVO_set_degree(SERVO_t* servo_struct, float degree);

void SERVO_set_ms(SERVO_t* servo_struct, float pulse_width);
