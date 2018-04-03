#include "i2C.h"
#include "delay.h"

byte I2C_Start(byte address)
// look for device at specified address; return 1=found, 0=not found
{
	TWCR = START; // send start condition (page 228 data sheet)
	while (!(TWCR & 0x80)); // wait for TWINT to return to 1.
	TWDR = address; //slave address assigned to the TW data register
	TWCR = SEND; //Send
	while (!(TWCR & 0x80)); // wait for TWINT to return to 1.
	return (TW_STATUS==0x18); //1 for success, 0 for failure in communications.
}

byte I2C_Write (byte address) // sends a data byte to slave
{
	TWDR = address; // load data to be sent
	TWCR  = SEND; // and send it
	while (!(TWCR & 0x80)); // wait
	return (TW_STATUS!=0x28);
}

byte I2C_ReadNACK () // reads a data byte from slave
{
	TWCR = (1<<TWINT)|(1<<TWEN); // nack = not reading more data
	while (!(TWCR & 0x80)); // wait until TWINT is set to logic 1
	return TWDR;
}

void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data)
{
	I2C_Start(busAddr); // send bus address
	I2C_Write(deviceRegister); // first byte = device register address
	I2C_Write(data); // second byte = data for device register
	STOP();
}


byte I2C_ReadRegister(byte busAddr, byte deviceRegister)
{
	byte data = 0;
	I2C_Start(busAddr); // send device address
	I2C_Write(deviceRegister); // set register pointer
	I2C_Start(busAddr+1); // restart as a read operation
	data = I2C_ReadNACK(); // read the register data
	STOP(); // stop
	return data;
}
