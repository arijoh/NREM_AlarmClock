#include "accelerometer.h"
#include "I2C.h"
#include "itoa.h"
#include "delay.h"
#include "checkAlarm.h"



void movement(){

	int a_data, b_data;

	a_data = I2C_ReadRegister(0x3A, 0x01);
	b_data = I2C_ReadRegister(0x3A, 0x01);

	if (((a_data - b_data) > 2) | ((b_data - a_data) > 2))
	{
		sendTime();

		int_itoa(b_data, string) ;
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

	GetTime(&shours,&sminutes,&sseconds);

	BCD_HEX(shours, accHour);
	BCD_HEX(sminutes, accMin);
	BCD_HEX(sseconds, accSec);

	msDelay(25);

	int counter=0;

	while (counter>=3)
	{
		UDR0 = accHour[counter];
		counter++;
	}

	msDelay(5);



}


