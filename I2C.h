#include "LCD.h"

#ifndef I2C_H_
#define I2C_H_
//komment




// I2C (TWI) ROUTINES
//
// On the AVRmega series, PA4 is the data line (SDA) and PA5 is the clock (SCL
// The standard clock rate is 100 KHz, and set by I2C_Init. It depends on the AVR osc. freq.
#define F_SCL 100000L // I2C clock speed 100 KHz
#define READ 1
#define TW_START 0xA4 // send start condition (TWINT,TWSTA,TWEN)
#define TW_STOP 0x94 // send stop condition (TWINT,TWSTO,TWEN)
#define TW_ACK 0xC4 // return ACK to slave
#define TW_NACK 0x84 // don't return ACK to slave
#define TW_SEND 0x84 // send data (TWINT,TWEN)
#define TW_READY (TWCR & 0x80) // ready when TWINT returns to logic 1.
#define TW_STATUS (TWSR & 0xF8) //
#define I2C_Stop() TWCR = TW_STOP // inline macro for stop condition

#endif /* I2C_H_ */


//-----------------------------------------------------------functions


void I2C_Init();
// at 16 MHz, the SCL frequency will be 16/(16+2(TWBR)), assuming prescalar of 0.
// so for 100KHz SCL, TWBR = ((F_CPU/F_SCL)-16)/2 = ((16/0.1)-16)/2 = 144/2 = 72.
byte I2C_Detect(byte addr); // look for device at specified address; return 1=found, 0=not found
byte I2C_FindDevice(byte start); // returns with address of first device found; 0=not found
void I2C_Start (byte slaveAddr);
byte I2C_Write (byte data); // sends a data byte to slave
byte I2C_ReadACK (); // reads a data byte from slave
byte I2C_ReadNACK (); // reads a data byte from slave
void I2C_WriteByte(byte busAddr, byte data);
void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data);
byte I2C_ReadRegister(byte busAddr, byte deviceRegister);


