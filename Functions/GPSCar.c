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
	
	return heading = atan2f((float)*x_axis, (float)*y_axis) *180/3.14;
}

//car speed
float speedCalc(float count, uint8_t time)
{
	float speed = (count/334)*(1000/time)*3.14*0/0.07;
	return speed;
}

