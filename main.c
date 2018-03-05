#include "LCD.h"
#include "RTC.h"
#include "i2C.h"
#include "buttonstates.h"
#include "checkAlarm.h"
//testtest
// ---------------------------------------------------------------------------
// MAIN PROGRAM
int main(void)
{
	setPorts(); // set port output for LCD
	LCD_Init(); // initialize HD44780 LCD controller
	I2C_Init(); // set I2C clock frequency
	LCD_Clear();
	setupInterrupt();
	sei();
	DDRD &= ~(1 << PD2);
	DDRD &= ~(1 << PD7);
	DDRD &= ~(1 << PD6);
	DDRD &= ~(1 << PD5);
	//setTime();
	while(1)
	{
		if(state == 1) {
			LCD_Clear();
			LCD_TimeDate(); // put time & date on LCD
			msDelay(500); // one second between updates
			checkAlarm();
		}

		else if  (state == 2)
		{
			setAlarmState();
		}
		else
		{
			setTimeState();
		}

	}
}



