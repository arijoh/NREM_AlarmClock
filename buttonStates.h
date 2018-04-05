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
int alarmM;//notum þessar variables í checkAlarm
int alarmH;
int loopa;

ISR (INT0_vect);

void setAlarmState(); //set alarm state
void setAlarmH(); //set alarm hour
void setAlarmM(); //set alarm min
void setTimeState();//change time functions
void changeTime();
void changeTimeH(); //change hour
void changeTimeM(); //change min
void ConfirmTimechange(); //confirm change
void resetTime(); //sets time after confirm
void setDateSet();
void setYear();
void setMonth();
void setDateDate();
void datePrint(int data,int month,int date);
void RegisterSetter(int data, int reg, int hvad); //sets RTC registers, hvad is what type of data (time, day..), reg is the register
void setDayState();
void setDayDay();
void setAcc(); //set motion detection
void accOn(); //set motion detection, follower of setAcc
#endif /* BUTTONSTATES_H_ */
