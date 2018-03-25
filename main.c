//#include "LCD.h"
//#include "RTC.h"
//#include "i2C.h"
//#include "buttonstates.h"
//#include "checkAlarm.h"
#include "setup.h"
#include "stateRunner.h"
//#include "delay.h"
#include "accelerometer.h"



int main(void)
{
	setup();
	while(1)
	{
		currentState();
		//check accelerometer
		movement();
	}
}



