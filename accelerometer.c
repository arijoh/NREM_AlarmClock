#include "accelerometer.h"
#include "I2C.h"
#include "itoa.h"
#include "delay.h"
#include "checkAlarm.h"

#include "LCD.h" //taka fra a eftir


void movement(){

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

	UART_Transmit_String(accHour);
	msDelay(5);
	UDR0 = ':';
	msDelay(5);
	UART_Transmit_String(accMin);
	msDelay(5);
	UDR0 = ':';
	msDelay(5);
	UART_Transmit_String(accSec);
	msDelay(5);
	UDR0 = 9;




}


