#include "i2C.h"
#include "delay.h"

byte startI2C(byte address) 
{
	TWCR = START; // send start condition (page 228 data sheet)
	while (!(TWCR & 0x80)); // wait for TWINT to return to 1.
	TWDR = address; //slave address assigned to the TW data register
	TWCR = SEND;
	while (!(TWCR & 0x80)); // wait for TWINT to return to 1.
	return ((TWSR & 0xF8) ==0x18); //1 for success, 0 for failure in communications.
}

byte writeAddress (byte address) //write to address
{
	TWDR = address; //address put to data register and..
	TWCR  = SEND; //..sent by putting send condition in control register
	while (!(TWCR & 0x80)); //wait for reply
	return ((TWSR & 0xF8) !=0x28); //1 for success, 0 for failure in communications.
}

void writeRegister(byte busAddr, byte reg, byte data)
{
	startI2C(busAddr);
	writeAddress(reg); // first byte = device register address
	writeAddress(data); // second byte = data for device register
	STOP();
}

byte readRegister(byte address, byte reg)
{
	byte data = 0;
	startI2C(address); //Send to address
	writeAddress(reg); // write to register
	startI2C(address+1); // write to address+1 = read mode
	//data = readNack(); //receive data by looking for NACK reply
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & 0x80));
	data = TWDR;
	STOP();  //Stop communications
	return data;
}
