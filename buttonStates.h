#ifndef BUTTONSTATES_H_
#define BUTTONSTATES_H_

#include "LCD.h"
#include "RTC.h"
#include <avr/interrupt.h>

int alarmM;//notum þessar variables í checkAlarm
int alarmH;
int state;
int sound;

ISR (INT0_vect);


void setAlarmState();//set alarm
void setAlarmH();
void setAlarmM();
void alarmPrint();//prints time on lower row on LCD
void setTimeState();//change time functions
void changeTime();
void changeTimeH();
void changeTimeM();
void ConfirmTimechange();
void resetTime();
void setDateSet();
void setYear();
void setMonth();
void setDateDate();
void datePrint(int data,int month,int date);
void RegisterSetter(int data, int reg, int hvad);
void setDayState();
void setDayDay();

#endif /* BUTTONSTATES_H_ */
