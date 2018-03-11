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

int year = 18;
int month = 1;
int date = 1;

int oldyear = 3, oldmonth = 3, olddate = 3;

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
	if (state > 4)
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
	RegisterSetter(hour, 1, 1);
	RegisterSetter(min, 2, 1);
	RegisterSetter(0, 3, 1);
}

void RegisterSetter(int data, int reg, int hvad)
{
	int newdata;

	if (data < 10)
		newdata = data;
	else if ((9 < data) && (data <= 19))
		newdata = data + 6;
	else if ((19 < data) && (data <= 29))
		newdata = data + 12;
	else if ((29 < data) && (data <= 39))
		newdata = data + 18;
	else if ((39 < data) && (data <= 49))
		newdata = data + 24;
	else if ((49 < data) && (data <= 59))
		newdata = data + 30;
	else
		newdata = data + 36;

	if (hvad == 1)
		setTime(newdata, reg);
	else if (hvad == 2)
		setDate(newdata, reg);
}


void setDateState()
{
	LCD_Clear();
	LCD_String("Set date?");
	LCD_Cursor(0,1);
	msDelay(50);

	if ((PIND & (1 << PD7))) {
		msDelay(150);
		if ((PIND & (1 << PD7))) {
			//setYear();
			setDateDate();
		}
	}
}

void setYear()
{



	LCD_Clear();
	LCD_String("Set year");

	while(loopa == 1){
		if ((PIND & (1 << PD6))) {
			year++;
			msDelay(100);
		}

		if ((PIND & (1 << PD5))) {
			year--;
			msDelay(100);
		}

		if (year > 99) {
			year = 0;
			msDelay(100);
		}

		else if (year < 0)
		{
			year = 99;
			msDelay(100);
		}

		datePrint(year, month, date);

		if ((PIND & (1 << PD7))) {
			msDelay(50);

			if ((PIND & (1 << PD7))) {
				LCD_Cursor(0,0);
				LCD_String("Year set!      ");
				RegisterSetter(year,1,2);
				RegisterSetter(month,2,2);
				RegisterSetter(date,3,2);
				msDelay(3000);
				LCD_Clear();
				loopa = 0;
				state = 1;
			}

		}
	}

}

void datePrint(int year,int month,int date)
{
	if ((year != oldyear) || (month != oldmonth) || (date != olddate))
	{
		msDelay(50);
		LCD_Cursor(0, 1);


		if (date < 10) {
			LCD_Integer(0);
			LCD_Integer(date);
		}
		else if (date >= 10) {
			LCD_Integer(date);
		}

		LCD_String(".");

		if (month < 10) {
			LCD_Integer(0);
			LCD_Integer(month);
		}
		else if (month >= 10) {
			LCD_Integer(month);
		}

		LCD_String(".");

		if (year < 10) {
			LCD_Integer(0);
			LCD_Integer(year);
		}
		else if (year >= 10) {
			LCD_Integer(year);
		}
	}

	oldyear = year;
	oldmonth = month;
	olddate = date;
}

void setMonth()
{
	LCD_Clear();
	LCD_String("Set Month");

	while(loopa == 1){
		if ((PIND & (1 << PD6))) {
			month++;
			msDelay(100);
		}

		if ((PIND & (1 << PD5))) {
			month--;
			msDelay(100);
		}

		if (month > 12) {
			month = 1;
			msDelay(100);
		}

		else if (month <= 0)
		{
			month = 12;
			msDelay(100);
		}

		datePrint(year, month, date);

		if ((PIND & (1 << PD7))) {
			msDelay(50);
			if ((PIND & (1 << PD7))) {
				msDelay(50);
				if ((PIND & (1 << PD7))) {
					LCD_Cursor(0,0);
					LCD_String("Month set!     ");
					msDelay(1000);
					LCD_Clear();
					LCD_String("Set Date:");
					setYear();
				}
			}
		}
	}
}


void setDateDate()
{

	LCD_Clear();
	LCD_String("Set Date");

	loopa = 1;

	while(loopa == 1){
		if ((PIND & (1 << PD6))) {
			date++;
			msDelay(100);
		}

		if ((PIND & (1 << PD5))) {
			date--;
			msDelay(100);
		}

		if (date > 31) {
			date = 1;
			msDelay(100);
		}

		else if (date <= 0)
		{
			date = 31;
			msDelay(100);
		}

		datePrint(year, month, date);

		if ((PIND & (1 << PD7))) {
			msDelay(50);
			if ((PIND & (1 << PD7))) {
				msDelay(50);
				if ((PIND & (1 << PD7))) {
					LCD_Cursor(0,0);
					LCD_String("Date set!    ");
					msDelay(1000);
					LCD_Clear();
					LCD_String("Set Month:");
					setMonth();

				}
			}
		}
	}
}
