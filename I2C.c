#include "i2C.h"

void setupI2C()
{
 TWSR = (1 << TWPS1) && (1 << TWPS0); //set prescalar to zero         //was TWST = 0
 TWBR = ((Clock_frequency/SCL_frequency)-16)/2; // set SCL frequency in TWI bit register
}


byte I2C_SendAdress(byte addr)
// look for device at specified address; return 1=found, 0=not found
{
 TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);// send start condition (page 228 data sheet)

 while (!TW_READY); // wait
 TWDR = addr; // load device's bus address
 TWCR = (1 << TWINT) | (1 << TWEN); // and send it
 while (!TW_READY); // wait
 return (TW_STATUS==0x18); // return 1 if found; 0 otherwise
}


byte I2C_FindDevice(byte start)
// returns with address of first device found; 0=not found
{
 for (byte addr=start;addr<0xFF;addr++) // search all 256 addresses
 {
 if (I2C_SendAdress(addr)) // I2C detected?
 return addr; // leave as soon as one is found
 }
 return 0; // none detected, so return 0.
}


void I2C_Start (byte slaveAddr)
{
 I2C_SendAdress(slaveAddr);
}


byte I2C_Write (byte adress) // sends a data byte to slave
{
 TWDR = adress; // load data to be sent
 TWCR  = (1 << TWINT) | (1 << TWEN); // and send it
 while (!TW_READY); // wait
 return (TW_STATUS!=0x28);
}



byte I2C_ReadNACK () // reads a data byte from slave
{
 TWCR = TW_NACK; // nack = not reading more data
 while (!TW_READY); // wait
 return TWDR;
 //return (TW_STATUS!=0x28);
}


void I2C_WriteByte(byte busAddr, byte data)
{
 I2C_Start(busAddr); // send bus address
 I2C_Write(data); // then send the data byte
 I2C_Stop();
}


void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data)
{
 I2C_Start(busAddr); // send bus address
 I2C_Write(deviceRegister); // first byte = device register address
 I2C_Write(data); // second byte = data for device register
 I2C_Stop();
}


byte I2C_ReadRegister(byte busAddr, byte deviceRegister)
{
 byte data = 0;
 I2C_Start(busAddr); // send device address
 I2C_Write(deviceRegister); // set register pointer
 I2C_Start(busAddr+READ); // restart as a read operation
 data = I2C_ReadNACK(); // read the register data
 I2C_Stop(); // stop
 return data;
}
