#ifndef _GPSCAR_H
#define _GPSCAR_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include <math.h>

/*----------definitions----------------*/

// COMPASS
#define compass 0x1A

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;

	extern uint16_t repeated_time,count,pre_count;
	
	//float pre_count, count;
	
	extern uint16_t pre_count_right, count_right;
	
	extern float  period, pre_period, sample_time;
	
	extern float stable_time;
	
	extern float actual_speed_right, PWM, PWM_right;
	
	
	extern float calculate(float repeated_time, float desired_speed, float actual_speed, float coup);
	extern float calculate_angle(float repeated_time, float desired_angle, float actual_angle);

//functions
void compassWrite(uint8_t data, uint8_t size);
void compassInit();
void readAxis(uint8_t compassData[6]);
float convert(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis, uint8_t compassData[6]);

//manual control
void forward();
void backward();
void left();
void right();
void stop();
void speed();

//motor
float speedCalc(float count, uint8_t time);
void PID();
float PIDAngle(float goal,float heading);

#endif


