#include "itoa.h"



void int_itoa( int n , char s[])
{
	int i ,sign;

	if((sign = n) < 0) // record s i gn
		n = -n ; // make n p o s i t i v e

	i = 0 ;

	do { // generate digits in reverse order
		s[i++] = n % 10 + '0' ; // get next digit
	} while ((n /= 10) > 0) ; // delete it
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0' ;
	int_reverse(s);
}

int int_stringlen(char s[])
{
	int i = 0;
	while (s[i] !=0 )
		i++;
	return i;
}

void int_reverse(char s[])
{
	int i , j ;
	char c ;

	for (i = 0 , j = int_stringlen(s) - 1; i<j ; i++, j--) {
		c = s[i] ;
		s[i] = s[j] ;
		s[j] = c;
	}
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
