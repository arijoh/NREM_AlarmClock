#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#define MMA_Address 0x3A
#define X_MSB 0x01

void movement();

int shours, sminutes, sseconds;

char string[3];
void UART_Transmit_String (char s[]);
void sendTime();

char accHour[3];
char accMin[3];
char accSec[3];


#endif /* ACCELEROMETER_H_ */
