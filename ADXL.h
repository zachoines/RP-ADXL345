#pragma once

/* Used with register 0x2C (ADXL345_REG_BW_RATE) to set bandwidth */
typedef enum
{
	ADXL345_DATARATE_3200_HZ = 0b1111, // 1600Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_1600_HZ = 0b1110, //  800Hz Bandwidth    90µA IDD
	ADXL345_DATARATE_800_HZ = 0b1101, //  400Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_400_HZ = 0b1100, //  200Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_200_HZ = 0b1011, //  100Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_100_HZ = 0b1010, //   50Hz Bandwidth   140µA IDD
	ADXL345_DATARATE_50_HZ = 0b1001, //   25Hz Bandwidth    90µA IDD
	ADXL345_DATARATE_25_HZ = 0b1000, // 12.5Hz Bandwidth    60µA IDD
	ADXL345_DATARATE_12_5_HZ = 0b0111, // 6.25Hz Bandwidth    50µA IDD
	ADXL345_DATARATE_6_25HZ = 0b0110, // 3.13Hz Bandwidth    45µA IDD
	ADXL345_DATARATE_3_13_HZ = 0b0101, // 1.56Hz Bandwidth    40µA IDD
	ADXL345_DATARATE_1_56_HZ = 0b0100, // 0.78Hz Bandwidth    34µA IDD
	ADXL345_DATARATE_0_78_HZ = 0b0011, // 0.39Hz Bandwidth    23µA IDD
	ADXL345_DATARATE_0_39_HZ = 0b0010, // 0.20Hz Bandwidth    23µA IDD
	ADXL345_DATARATE_0_20_HZ = 0b0001, // 0.10Hz Bandwidth    23µA IDD
	ADXL345_DATARATE_0_10_HZ = 0b0000  // 0.05Hz Bandwidth    23µA IDD (default value)
} dataRate_t;

/* Used with register 0x31 (ADXL345_REG_DATA_FORMAT) to set g range */
typedef enum
{
	ADXL345_RANGE_16_G = 0b11,   // +/- 16g
	ADXL345_RANGE_8_G = 0b10,   // +/- 8g
	ADXL345_RANGE_4_G = 0b01,   // +/- 4g
	ADXL345_RANGE_2_G = 0b00    // +/- 2g (default value)
} range_t;

typedef struct point
{
	int x;
	int y;
	int z;
} acceleration_data;

class ADXL
{

public:
	// Address
	static const unsigned short ADXL345_ADDRESS = 0x53;

	// Registers
	static unsigned const short ADXL345_REG_DEVID = 0x00;    // Device ID
	static unsigned const short ADXL345_REG_THRESH_TAP = 0x1D;  // Tap threshold
	static unsigned const short ADXL345_REG_OFSX = 0x1E;     // X-axis offset
	static unsigned const short ADXL345_REG_OFSY = 0x1F; // Y-axis offset
	static unsigned const short ADXL345_REG_OFSZ = 0x20; // Z-axis offset
	static unsigned const short ADXL345_REG_DUR = 0x21; // Tap duration
	static unsigned const short ADXL345_REG_LATENT = 0x22; // Tap latency
	static unsigned const short ADXL345_REG_WINDOW = 0x23; // Tap window
	static unsigned const short ADXL345_REG_THRESH_ACT = 0x24; // Activity threshold
	static unsigned const short ADXL345_REG_DATA_FORMAT = 0x32; // Data Format
	static unsigned const short ADXL345_REG_BW_RATE = 0x2C; // Bit output rate


	ADXL();
	void setDataRate(dataRate_t dataRate);
	void setRange(range_t range);
	acceleration_data readDataPoint();
private:
	int i2c = 0;

};

