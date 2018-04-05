#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
typedef uint8_t byte;

#define SEND (1 << TWINT) | (1 << TWEN) //send condition
#define START (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) //start condition
#define STOP() TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) //stop condition

byte writeAddress (byte data);
void writeRegister(byte address, byte reg, byte data);
byte readRegister(byte address, byte reg);
byte startI2C(byte address);

#endif /* I2C_H_ */
