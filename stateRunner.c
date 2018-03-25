#include "stateRunner.h"
#include "buttonStates.h"
#include "delay.h"
#include "checkAlarm.h"

void currentState()
{
	if(state == 1) {
		LCD_Clear();
		LCD_TimeDate(); // put time & date on LCD
		checkAlarm();
		msDelay(1000); // one second between updates
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
	else{
		setDayState();
	}
}
