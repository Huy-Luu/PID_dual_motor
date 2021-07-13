#ifndef _GPSCAR_H
#define _GPSCAR_H

//#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include <math.h>

/*----------definitions----------------*/

// COMPASS
#define compass 0x1A

extern I2C_HandleTypeDef hi2c1;


//functions
void compassWrite(uint8_t data, uint8_t size);
void compassInit();
void readAxis(uint8_t compassData[6]);
float convert(int16_t *x_axis, int16_t *y_axis, int16_t *z_axis, uint8_t compassData[6]);

//motor
float speedCalc(float count, uint8_t time);

#endif


