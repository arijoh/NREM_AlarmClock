#include "checkAlarm.h"
#include "itoa.h"
#include "buttonStates.h"
#include "delay.h"


void checkAlarm()
{
	readTime(&hours,&minutes,&seconds);

	BCD_HEX(hours, currentHour);
	BCD_HEX(minutes, currentMin);

	alarm_itoa(alarmM, alarmMString);
	alarm_itoa(alarmH, alarmHString);

	if ((alarmMString[0] == currentMin[0]) && (alarmHString[0] == currentHour[0]) &&
			(alarmMString[1] == currentMin[1]) && (alarmHString[1] == currentHour[1]))
	{
		alarm();
	}
}

void BCD_HEX(int data, char s[])
{
	byte temp = data>>4;
	data &= 0x0F;

	s[0] = (temp+'0');
	s[1] = (data+'0');
}



void alarm()
{
	DDRC = 0xff;           // Configure PORTC as output

	while(sound == 1){
		clearLCD();
		printString("Wake up!");
		PORTC = 0xff;        // Turn ON the Buzzer conneted to PORTC
		msDelay(250);      // Wait for some time
		if (PIND & (1 << PD7))
		{
			sound = 0;
		}
		PORTC = 0x00;        // Turn OFF the Buzzer connected to PORTC
		msDelay(250);      // Wait for some time
		if (PIND & (1 << PD7))
		{

			sound = 0;
		}

		//kanski láta timer líka.
	}
}
