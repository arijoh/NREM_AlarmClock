#include "LCD.h"
#include "RTC.h"

#ifndef BUTTONSTATES_H_
#define BUTTONSTATES_H_

#include <avr/interrupt.h>

extern int alarmM;//notum þessar variables í checkAlarm
extern int alarmH;

extern int state;
extern int sound;



void setupInterrupt();//interrupt functions
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

#endif /* BUTTONSTATES_H_ */
