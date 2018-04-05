#include "accelerometer.h"
#include "I2C.h"
#include "itoa.h"
#include "delay.h"
#include "checkAlarm.h"
#include "buttonStates.h"

//Uart is being used to track motion detection and alarm to see how precise the alarm clock is.
//uart will not be part of the alarm clock once it is developed

int counter = 0;
int oldhour = 0;

void movement(){
	if (AccOn == 1) {
		int a_data, b_data;
		a_data = readRegister(0x3A, 0x01); //read registers of accelerometer
		b_data = readRegister(0x3A, 0x01); //read again
		//a_data and b_data are then compared to see if any motion has been detected

		if (((a_data - b_data) > 2) | ((b_data - a_data) > 2)) //if magnitude of movement is more than abs 2
		{
			sendTime(); //sent time through uart
			msDelay(5);
			int magnitude = a_data-b_data;
			int_itoa(magnitude, string) ;
			UART_Transmit_String(string); //sent magnitude throuth uart
			msDelay(5);
			UDR0 = '\r'; //start new line
			UDR0 = '\n';
		}
	}
	msDelay(5);
}

void UART_Transmit_String (char s[])
{
	char cIndex=0;
	while (s[cIndex]!=0)
	{
		UDR0 = s[cIndex] ;
		cIndex++;
	}
}

void sendTime()
{
	//taka inn gildi fyrir klukku
	readTime(&hours_temp,&minutes_temp,&seconds_temp);

	BCD_HEX(hours_temp, accHour);
	BCD_HEX(minutes_temp, accMin);
	BCD_HEX(seconds_temp, accSec);

	compare(accHour, accMin);

	UART_Transmit_String(accHour);
	msDelay(5);
	UDR0 = 0x09; //for tab between data
	msDelay(5);
	UART_Transmit_String(accMin);
	msDelay(5);
	UDR0 = 0x09;
	msDelay(5);
	UART_Transmit_String(accSec);
	msDelay(5);
	UDR0 = 0x09;

}

//takes in hour of trigge rand compares to wake up time
void compare(char triggerHour[], char triggerMin[])
{
	int i_triggerHour = toString(triggerHour);
	int i_triggerMin = toString(triggerMin);

	int deltaMin = alarmM - i_triggerMin;
	int deltaHour = alarmH - i_triggerHour;

	int delta = 100;

	//triggerHour == alarmHour -> skoða mun á mínótum
	if (deltaHour == 0)
		delta = deltaMin;


	//triggerHour < alarmHour -> ef munur á mínútum er 0 þá er munur á klukkutímum tekinn*60 = mín í alarm
	// annars er tekið mun á (klukutímum -1) + deltamin
	else if (deltaHour >= 1)
	{
		if (deltaMin > 0)
			delta = deltaHour*60+deltaMin;
		if (deltaMin < 0)
			delta = (deltaHour-1)*60 + (60+deltaMin);
		if (deltaMin == 0)
		{
			delta = deltaHour*60;
		}
	}

	if (oldhour == i_triggerHour)
	{
		counter++;
	}
	else
		counter = 0;

	oldhour = i_triggerHour;

	if ((delta < 60) & (counter >= 3)) //if 60 min or less until alarm and 3 or more movements in the same hour -> alarm
	{
		alarm();
		UART_Transmit_String("W"); //sends W with uart to mark when alarm was triggered
		msDelay(5);
	}
	else
	{

	}
}

int toString(char a[]) {
	int c, sign, offset, n;

	offset = 0;
	n = 0;

	for (c = offset; a[c] != '\0'; c++) {
		n = n * 10 + a[c] - '0';
	}

	return n;
}

