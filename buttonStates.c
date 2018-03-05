#include "buttonstates.h"

int state = 1;
int alarmH = 0;
int oldalarmH = 3;
int alarmM = 0;
int oldalarmM = 3;
int loopa = 0;
int counter;
int hour;
int min;
int sound;

void setupInterrupt() {
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	// PD2 (PCINT0 pin) is now an input
	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);     // Turns on INT0
}

ISR (INT0_vect) {
	msDelay(50);
	if (PIND & (1 << PD2))
	{
		state++;
	}
	if (state > 3)
		state = 1;
}

void setAlarmState()
{
	LCD_Clear();
	LCD_String("Set alarm?");
	LCD_Cursor(0,1);
	msDelay(50);

	if ((PIND & (1 << PD7))) {
		setAlarmH();
	}
}

void setAlarmH() {

	loopa = 1;

	LCD_Clear();
	LCD_String("Set alarm hour:");

	while(loopa == 1){
		if ((PIND & (1 << PD6))) {
			alarmH++;
			msDelay(100);
		}

		if ((PIND & (1 << PD5))) {
			alarmH--;
			msDelay(100);
		}

		if (alarmH > 24) {
			alarmH = 0;
			msDelay(100);
		}

		else if (alarmH < 0)
		{
			alarmH = 24;
			msDelay(100);
		}

		alarmPrint(alarmH, alarmM);

		if ((PIND & (1 << PD7))) {
			msDelay(50);
			if ((PIND & (1 << PD7))) {
				LCD_Cursor(0,0);
				LCD_String("Hour set!      ");
				msDelay(1000);
				LCD_Clear();
				LCD_String("Set alarm min:");
				setAlarmM();
			}
		}
	}
}

void setAlarmM() {

	while(loopa == 1){
		if ((PIND & (1 << PD6))) {
			alarmM++;
			msDelay(100);
		}

		DDRD &= ~(1 << PD5);
		if ((PIND & (1 << PD5))) {
			alarmM--;
			msDelay(100);
		}

		if (alarmM > 59) {
			alarmM = 0;
			msDelay(100);
		}

		else if (alarmM < 0)
		{
			alarmM = 59;
			msDelay(100);
		}

		alarmPrint(alarmH, alarmM);

		if ((PIND & (1 << PD7))) {
			msDelay(50);
			if ((PIND & (1 << PD7))) {
				LCD_Cursor(0, 0);
				LCD_String("Minute set!   ");
				msDelay(1000);
				LCD_Cursor(0, 0);
				LCD_String("Alarm set!  ");
				sound = 1;
				msDelay(3000);
				LCD_Clear();
				loopa = 0;
				state = 1;
			}
		}
	}
}

void alarmPrint(int alarmH, int alarmM)
{

	if (alarmM != oldalarmM) {
		msDelay(50);
		LCD_Cursor(0, 1);

		if (alarmH < 10) {
			LCD_Integer(0);
			LCD_Integer(alarmH);
		} else if (alarmH >= 10) {
			LCD_Integer(alarmH);
		}

		LCD_String(":");

		if (alarmM < 10) {
			LCD_Integer(0);
			LCD_Integer(alarmM);
		} else if (alarmM >= 10) {
			LCD_Integer(alarmM);
		}
	}
	oldalarmH = alarmH;
}


void setTimeState()
{
	LCD_Clear();
	LCD_String("Change time?");
	LCD_Cursor(0,1);
	msDelay(50);

	if ((PIND & (1 << PD7))) {
		msDelay(50);
		if ((PIND & (1 << PD7))) {
			changeTimeH();
		}
	}
}

void changeTimeH()
{
	//get time variables
	loopa = 1;

	LCD_Clear();
	LCD_String("Set new hour:");

	while(loopa == 1){

		DDRD &= ~(1 << PD6);
		if ((PIND & (1 << PD6))) {
			hour++;
			msDelay(100);
		}

		DDRD &= ~(1 << PD5);
		if ((PIND & (1 << PD5))) {
			hour--;
			msDelay(100);
		}

		if (hour > 24) {
			hour = 0;
			msDelay(100);
		}

		else if (hour < 0)
		{
			hour = 24;
			msDelay(100);
		}

		alarmPrint(hour, min);


		if ((PIND & (1 << PD7))) {
			msDelay(50);
			if ((PIND & (1 << PD7))) {
				LCD_Cursor(0,0);
				LCD_String("New hour set!     ");
				msDelay(1000);
				LCD_Clear();
				LCD_String("Set new min:");
				changeTimeM();
			}
		}
	}
}


void changeTimeM()
{
	while(loopa == 1){
		if ((PIND & (1 << PD6))) {
			min++;
			msDelay(100);
		}

		DDRD &= ~(1 << PD5);
		if ((PIND & (1 << PD5))) {
			min--;
			msDelay(100);
		}

		if (min > 59) {
			min = 0;
			msDelay(100);
		}

		else if (min < 0)
		{
			min = 59;
			msDelay(100);
		}

		alarmPrint(hour, min);


		if ((PIND & (1 << PD7))) {
			msDelay(50);
			if ((PIND & (1 << PD7))) {
				LCD_Cursor(0, 0);
				LCD_String("New minute set!   ");
				msDelay(1000);
				ConfirmTimechange();
				loopa = 0;
			}
		}
	}
}
void ConfirmTimechange()
{
	int counter = 0;
	LCD_Clear();
	LCD_String("Confirm change?");
	LCD_Cursor(0,1);
	alarmPrint(hour,min);

	while (counter < 50){
		if ((PIND & (1 << PD7))) {
			msDelay(150);
			if ((PIND & (1 << PD7))) {
				LCD_Clear();
				LCD_String("Time changed!");
				msDelay(3000);
				state = 1;
				//change time

				resetTime();


				break;
			}
		}
		counter++;
		msDelay(150);
	}

	if (counter >= 50){
		LCD_Clear();
		LCD_String("Time not changed!");
		msDelay(3000);
		state = 1;
	}
}

void resetTime()
{
	int h1, h2, m1, m2;

	if (hour < 10){
		h1 = 0;
		h2 = hour;
	}
	else if (hour >= 10)
	{
		h1 = hour/10;
		h2 = (hour%10);
	}

	if (min < 10){
		m1 = 0;
		m2 = min;
	}
	else if (min >= 10)
	{
		m1 = min/10;
		m2 = (min%10);
	}

	char settingMin[4];
	//char settingHour[4];

	settingMin[0] = '0';
	settingMin[1] = 'x';
	settingMin[2] = (m1+'0');
	settingMin[3] = (m2+'0');


	//LCD_String(settingMin);
	//msDelay(5000);

	//setTime(settingMin, settingMin, settingMin);



	//þarf að nota tvær int tölur á hex formati.
	//eða, sameina tvær int tölur líktog á hex formati og henda þeim saman í int format.
	//setTime(setHour, setMin, setSec);

}

