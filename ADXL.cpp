#include "ADXL.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



ADXL::ADXL()
{
	i2c = wiringPiI2CSetup(ADXL345_ADDRESS);

	// Reset the registers
	wiringPiI2CWriteReg8(i2c, 0x31, 0x0b);
	wiringPiI2CWriteReg8(i2c, 0x2d, 0x08);
	//wiringPiI2CWriteReg8(i2c, 0x2e, 0x00); A
	wiringPiI2CWriteReg8(i2c, 0x1e, 0x00);
	wiringPiI2CWriteReg8(i2c, 0x1f, 0x00);
	wiringPiI2CWriteReg8(i2c, 0x20, 0x00);

	wiringPiI2CWriteReg8(i2c, 0x21, 0x00);
	wiringPiI2CWriteReg8(i2c, 0x22, 0x00);
	wiringPiI2CWriteReg8(i2c, 0x23, 0x00);

	wiringPiI2CWriteReg8(i2c, 0x24, 0x01);
	wiringPiI2CWriteReg8(i2c, 0x25, 0x0f);
	wiringPiI2CWriteReg8(i2c, 0x26, 0x2b);
	wiringPiI2CWriteReg8(i2c, 0x27, 0x00);

	wiringPiI2CWriteReg8(i2c, 0x28, 0x09);
	wiringPiI2CWriteReg8(i2c, 0x29, 0xff);
	wiringPiI2CWriteReg8(i2c, 0x2a, 0x80);
	wiringPiI2CWriteReg8(i2c, 0x2c, 0x0a);
	wiringPiI2CWriteReg8(i2c, 0x2f, 0x00);
	wiringPiI2CWriteReg8(i2c, 0x38, 0x9f);
}

void ADXL::setDataRate(dataRate_t dataRate)
{
	unsigned short format = dataRate & 0x0F;
	wiringPiI2CWriteReg8(i2c, ADXL345_REG_DATA_FORMAT, format);
	return;
}

void ADXL::setRange(range_t range)
{
	unsigned short format = ((wiringPiI2CReadReg8(i2c, ADXL345_REG_DATA_FORMAT) & ~0x0F) | range | 0x08);
	wiringPiI2CWriteReg8(i2c, ADXL345_REG_DATA_FORMAT, format);
}

acceleration_data ADXL::readDataPoint()
{

	int x0, y0, z0, x1, y1, z1;
	
	// X-Axis Data 0 
	x0 = 0xff - wiringPiI2CReadReg8(i2c, 0x32);
	
	// X - Axis Data 1
	x1 = 0xff - wiringPiI2CReadReg8(i2c, 0x33);
	
	// Y-Axis Data 0
	y0 = 0xff - wiringPiI2CReadReg8(i2c, 0x34);
	
	// Y-Axis Data 1 
	y1 = 0xff - wiringPiI2CReadReg8(i2c, 0x35);
	
	// Z-Axis Data 0 
	z0 = 0xff - wiringPiI2CReadReg8(i2c, 0x36);
	
	// Z-Axis Data 1
	z1 = 0xff - wiringPiI2CReadReg8(i2c, 0x37);

	int x = (x1 << 8) + x0;
	int y = (y1 << 8) + y0;
	int z = (z1 << 8) + z0;
	acceleration_data data;
	data.x = x;
	data.y = y;
	data.z = z;

	return data;
}
