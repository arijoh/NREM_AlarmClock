#include "accelerometer.h"
#include "I2C.h"
#include "itoa.h"
#include "delay.h"
#include "checkAlarm.h"
#include "buttonStates.h"


void movement(){
	if (AccOn == 1) {
		int a_data, b_data;
		a_data = I2C_ReadRegister(0x3A, 0x01);
		b_data = I2C_ReadRegister(0x3A, 0x01);

		if (((a_data - b_data) > 2) | ((b_data - a_data) > 2))
		{
			sendTime();
			msDelay(5);
			int magnitude = a_data-b_data;
			int_itoa(magnitude, string) ;
			UART_Transmit_String(string);
			msDelay(5);
			UDR0 = '\r';
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
	GetTime(&hours_temp,&minutes_temp,&seconds_temp);

	BCD_HEX(hours_temp, accHour);
	BCD_HEX(minutes_temp, accMin);
	BCD_HEX(seconds_temp, accSec);

	compare(accHour, accMin);

	UART_Transmit_String(accHour);
	msDelay(5);
	UDR0 = 0x09;
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


	if (delta < 90)
	{
		alarm();
		UART_Transmit_String("Woke");
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

