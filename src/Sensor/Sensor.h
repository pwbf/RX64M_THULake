#ifndef SENSOR_H
#define SENSOR_H

uint8_t sensorSend(uint8_t func);
void sensorRead(uint8_t status);

#define HOST_SEND_LENGTH		(8)
#define SENS_ECHO_LENGTH		(8)
#define SENS_READ_LENGTH		(15)

#define SENS_FUNC_ECHO			(0x06)		//Function Code: Echo
#define SENS_FUNC_READ			(0x04)		//Function Code: Request Data

#define SENS_ADDR				(0x01)		//Address
#define SENS_REG_ECHO_STARTH	(0x00)		//Register Start High(For Echo function)
#define SENS_REG_ECHO_STARTL	(0x02)		//Register Start Low(For Echo function)
#define SENS_REG_READ_STARTH	(0x00)		//Register Start High(For Read function)
#define SENS_REG_READ_STARTL	(0x07)		//Register Start Low(For Read function)
#define SENS_REG_COUNTH			(0x00)		//Register Count High
#define SENS_REG_COUNTL			(0x05)		//Register Count Low

#endif