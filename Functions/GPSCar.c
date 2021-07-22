#include "GPSCar.h"


void compassWrite(uint8_t data, uint8_t size)
{
		HAL_I2C_Master_Transmit(&hi2c1, compass, &data, size, 10);
}

void compassInit()
{
		uint8_t write_data;
		
		write_data=0x01;
		HAL_I2C_Mem_Write(&hi2c1, compass, 0x0B, 1, &write_data, 1,100);
	
		write_data=0x01;
		HAL_I2C_Mem_Write(&hi2c1, compass, 0x09, 1, &write_data, 1,100); // write 0s to pwr_mng_reg	

}

void readAxis(uint8_t compassData[6])
{
	HAL_I2C_Mem_Read(&hi2c1, compass, 0x00, 1, compassData, 6, 200);
}


float convert(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis, uint8_t compassData[6])
{
	float heading;
	*x_axis = ((uint16_t)compassData[1]<<8)|compassData[0];
	*y_axis = ((uint16_t)compassData[3]<<8)|compassData[2];
	*z_axis = ((uint16_t)compassData[5]<<8)|compassData[4];
	
	heading = atan2f((float)*x_axis, (float)*y_axis) *180/3.14;
	if(heading<0.0)
	{
		heading+=360.0;
	}
	
	return heading;
}

//car speed
float speedCalc(float count, uint8_t time)
{
	float speed = (count/334)*(1000/time)*3.14*0/0.07;
	return speed;
}

void forward()
{
	speed();
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,0);// trái
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,0);//phai
}

void backward()
{
	speed();
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);// trái
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,1);//phai
}

 void left()
 {
		htim1.Instance->CCR1=8000;
	htim1.Instance->CCR2=10000;
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,1);// trái
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,0);//phai
 }
 
 void right()
 {
		htim1.Instance->CCR1=8000;
	htim1.Instance->CCR2=10000;
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,0);// trái
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,1);//phai
 }
 
 void stop()
 {
	htim1.Instance->CCR1=0;
	htim1.Instance->CCR2=0;
 }
 
 void speed()
{
	htim1.Instance->CCR1=9000;
	htim1.Instance->CCR2=9000;
}

void PID()
{
		stable_time=HAL_GetTick();
		
		
		//lay so dem ban dau cho tinh toan toc do
		pre_count	=	TIM2->CNT;
		pre_count_right	=	TIM3->CNT;
		pre_period=HAL_GetTick();
		HAL_Delay(10);
		
		//lay so dem sau va tinh toan thoi gian
		count	=	TIM2->CNT;
		count_right	=	TIM3->CNT;
		period=HAL_GetTick();
		sample_time=period-pre_period;
		
		//tinh toan toc do cho ca 2 dong co
		actual_speed_right=((float)(count_right-pre_count_right))/334*((1000/sample_time)*3.14*0.07);
		//actual_speed=((float)(count-pre_count))/334*((1000/sample_time)*3.14*0.07);
			//actual_speed_right = speedCalc((float)(pre_count_right-count_right), sample_time);
			//actual_speed = speedCalc((float)(pre_count-count), sample_time);
		
		// tinh toan PID cho dong co neu nhu khong co sai so o encoder.
		//if((count<60000) ) 
		//{
		period=HAL_GetTick();
		PWM=calculate((float)(period-pre_period)/1000, 0.9, actual_speed_right,0);
		PWM_right=PWM;		
		//}
}

float PIDAngle(float goal,float heading)
{
		
	
		pre_period=HAL_GetTick();
		HAL_Delay(10);
		period=HAL_GetTick();
		sample_time=period-pre_period;

		
		return calculate_angle(sample_time, goal, heading);
		
}

