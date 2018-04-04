#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#define MMA_Address 0x3A
#define X_MSB 0x01 //x stefna - register.

int hours_temp;
int minutes_temp;
int seconds_temp;
char string[3];
char accHour[3];
char accMin[3];
char accSec[3];

int counter;
int oldhour;


void UART_Transmit_String (char s[]);
void sendTime();
void movement();
void compare();

#endif /* ACCELEROMETER_H_ */
