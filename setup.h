#ifndef SETUP_H_
#define SETUP_H_

void setup();

#define Clock_frequency 16000000L // run CPU at 16 MHz
#define SCL_frequency 100000L //SCL speed


void setupInterrupt();
void setupI2C();
// at 16 MHz, the SCL frequency will be 16/(16+2(TWBR)), assuming prescalar of 0.
// so for 100KHz SCL, TWBR = ((F_CPU/F_SCL)-16)/2 = ((16/0.1)-16)/2 = 144/2 = 72.
void setupLCD();
void setPorts();
void setupUart();  //set baud rate, enable tx,tx communications
void setupButtons();

#endif /* SETUP_H_ */
