#include "setup.h"
#include "stateRunner.h"
#include "accelerometer.h"




int main(void)
{
	setup();
	while(1)
	{
		//Current state check in which state the clock is, state is changes when red button is pressed
		currentState();
		//Movement checks for movement
		movement();
	}
}
