#include "i2C.h"
#include "delay.h"

byte startI2C(byte address)
// look for device at specified address; return 1=found, 0=not found
{
	TWCR = START; // send start condition (page 228 data sheet)
	while (!(TWCR & 0x80)); // wait for TWINT to return to 1.
	TWDR = address; //slave address assigned to the TW data register
	TWCR = SEND;
	while (!(TWCR & 0x80)); // wait for TWINT to return to 1.
	return (TW_STATUS==0x18); //1 for success, 0 for failure in communications.
}

byte writeAddress (byte address) // sends a data byte to slave
{
	TWDR = address; //address put to data register and..
	TWCR  = SEND; //..sent by putting send condition in control register
	while (!(TWCR & 0x80)); //wait for reply
	return (TW_STATUS!=0x28);
}

byte readNack () //data from sensors
{
	TWCR = (1<<TWINT)|(1<<TWEN); //control register set to NACK mode
	while (!(TWCR & 0x80)); //wait for reply
	return TWDR;
}

void writeRegister(byte busAddr, byte deviceRegister, byte data)
{
	startI2C(busAddr);
	writeAddress(deviceRegister); // first byte = device register address
	writeAddress(data); // second byte = data for device register
	STOP();
}

byte readRegister(byte busAddr, byte deviceRegister)
{
	byte data = 0;
	startI2C(busAddr); // send device address
	writeAddress(deviceRegister); // set register pointer
	startI2C(busAddr+1); // restart as a read operation
	data = readNack(); // read the register data
	STOP(); // stop
	return data;
}
