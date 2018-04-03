#ifndef BUTTONSTATES_H_
#define BUTTONSTATES_H_

#include "LCD.h"
#include "RTC.h"
#include <avr/interrupt.h>

int oldalarmH;
int oldalarmM;

int state;

int sound;
int AccOn;

ISR (INT0_vect);

int alarmM;//notum þessar variables í checkAlarm
int alarmH;

void setAlarmState();
void setAlarmH();
void setAlarmM();
void accOn();

int loopa;

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
void setAcc();

#endif /* BUTTONSTATES_H_ */
