#include "checkAlarm.h"

void checkAlarm()
{
	GetTime(&hours,&minutes,&seconds);

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



int stringlen(char s[])
{
	int i = 0;
	while (s[i] !=0 )
		i++;
	return i;
}

void reverse(char s[])
{
	int i , j ;
	char c ;

	for (i = 0 , j = stringlen(s) - 1; i<j ; i++, j--) {
		c = s[i] ;
		s[i] = s[j] ;
		s[j] = c;
	}
}

void alarm_itoa( int n , char s[])
{
	int i ,sign;

	if((sign = n) < 0) // record s i gn
		n = -n ; // make n p o s i t i v e

	if (n < 10)
	{
		i = 1;
		s[0] = '0';

		do { // generate digits in reverse order
			s[i++] = n % 10 + '0' ; // get next digit
		} while ((n /= 10) > 0) ; // delete it
		if (sign < 0)
			s[i++] = '-';
		s[i] = '\0' ;
	}
	else
	{
		i = 0 ;

		do { // generate digits in reverse order
			s[i++] = n % 10 + '0' ; // get next digit
		} while ((n /= 10) > 0) ; // delete it
		if (sign < 0)
			s[i++] = '-';
		s[i] = '\0' ;
		reverse(s) ;
	}

}

void alarm()
{
	DDRC = 0xff;           // Configure PORTC as output

	while(sound == 1){
		LCD_Clear();
		LCD_String("Wake up!");
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
