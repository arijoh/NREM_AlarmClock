#include "delay.h"

void msDelay(long unsigned int miS ) //delay function for ms
{
	unsigned volatile long ulMax , ulCount ;
	ulMax = 380 * miS ;
	ulCount=0;
	while (ulCount != ulMax ) {
		ulCount++;
	}
}

void usDelay(long unsigned int uiS ) //delay function for us
{
	unsigned volatile long ulMax , ulCount ;
	ulMax = 19 * uiS ;
	ulCount=0;
	while (ulCount != ulMax ) {
		ulCount++;
	}
}
