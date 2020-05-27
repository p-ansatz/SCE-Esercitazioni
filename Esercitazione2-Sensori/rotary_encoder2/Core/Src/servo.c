/* Includes */
#include "servo.h"

/* Initilization */
void SERVO_init(SERVO_t* servo_struct, TIM_HandleTypeDef* htim){
	// Save the i2c handler internally
	servo_struct->PWM_timer_handler = htim;
}

/*
 * Set degree for SERVO
 * 		pulse_width = (MAX – MIN) * degree/180 + MIN
 */
void SERVO_set_degree(SERVO_t* servo_struct, float degree){
	int pulse_width = ceil((SERVO_MAX_MS - SERVO_MIN_MS)*degree/180 + SERVO_MIN_MS);
	SERVO_set_ms(servo_struct, pulse_width);
}

/*
 * Set millisecond for SERVO
 * 		pulse_wdith must be between MIN and MAX
 */
void SERVO_set_ms(SERVO_t* servo_struct, int pulse_width){
	if(pulse_width < SERVO_MIN_MS){
		pulse_width = SERVO_MIN_MS;
	}else if(pulse_width > SERVO_MAX_MS){
		pulse_width = SERVO_MAX_MS;
	}
	TIM_HandleTypeDef* htim = servo_struct->PWM_timer_handler;
	htim->Instance->CCR2 = pulse_width;
}
