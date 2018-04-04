#include "stateRunner.h"
#include "buttonStates.h"
#include "delay.h"
#include "checkAlarm.h"

void currentState()
{
	if(state == 1) {
		clearLCD();
		LCD_TimeDate(); // put time & date on LCD
		checkAlarm();
	}

	else if  (state == 2)
	{
		setAlarmState();
	}
	else if (state == 3)
	{
		setTimeState();
	}
	else if (state == 4){
		setDateState();
	}
	else if (state == 5){
		setDayState();
	}
	else if (state == 6)
	{
		setAcc();
	}

}
