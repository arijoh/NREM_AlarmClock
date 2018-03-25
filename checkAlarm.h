#include "buttonstates.h"


#ifndef CHECKALARM_H_
#define CHECKALARM_H_

int hours;
int seconds;
int minutes;

char currentHour[3];
char currentMin[3];

char alarmMString[3];
char alarmHString[3];

void checkAlarm();
void alarm();

void BCD_HEX(int data, char s[]);




#endif /* CHECKALARM_H_ */
