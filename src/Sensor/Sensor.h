#ifndef SENSOR_H
#define SENSOR_H


// void sensorInitvoid;
uint8_t sensorSend(uint8_t func);
void sensorRead(uint8_t status);

const uint8_t HOST_SEND_LENGTH = 8;
const uint8_t SENS_ECHO_LENGTH = 8;
const uint8_t SENS_READ_LENGTH = 15;

#define SENS_FUNC_ECHO		(0x06);		//Function Code: Echo
#define SENS_FUNC_READ		(0x04);		//Function Code: Request Data

const uint8_t SENS_ADDR				= 0x01;		//Address
const uint8_t SENS_REG_STARTH		= 0x00;		//Register Start High;
const uint8_t SENS_REG_STARTL		= 0x02;		//Register Start Low;
const uint8_t SENS_REG_COUNTH		= 0x00;		//Register Count High;
const uint8_t SENS_REG_COUNTL		= 0x05;		//Register Count Low;
const uint8_t SENS_CRC_H			= 0x29;		//CRC High Byte
const uint8_t SENS_CRC_L			= 0xCC;		//CRC Low Byte
const uint8_t SENS_ADDR_STARTH		= 0x00;		//Address Start High;
const uint8_t SENS_ADDR_STARTL		= 0x02;		//Address Start Low;

#endif