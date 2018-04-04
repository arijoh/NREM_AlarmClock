#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h> // deal with port registers
typedef uint8_t byte; // I just like byte

#define SEND (1 << TWINT) | (1 << TWEN)
#define START (1<<TWINT) | (1<<TWSTA) | (1<<TWEN)
#define STOP() TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) //stop condition

byte writeAddress (byte data);
void writeRegister(byte busAddr, byte deviceRegister, byte data);
byte readRegister(byte busAddr, byte deviceRegister);
byte startI2C(byte address);

#endif /* I2C_H_ */
