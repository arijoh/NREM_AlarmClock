#ifndef SETUP_H_
#define SETUP_H_

#define Clock_frequency 16000000L // CPU speed
#define SCL_frequency 100000L //SCL speed


void setup();
void setupInterrupt();
void setupI2C();
void setupLCD();
void setPorts();
void setupUart();
void setupButtons();

#endif /* SETUP_H_ */
