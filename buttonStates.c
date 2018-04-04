#include "buttonstates.h"
#include "delay.h"

int state = 1;


#define confirmButton (PIND & (1 << PD7))
#define plusButton (PIND & (1 << PD6))
#define minusButton (PIND & (1 << PD5))
#define interruptButton PIND & (1 << PD2)


int loopa = 0;
int counter;
int hour;
int min;
int sound;
int year = 18;
int month = 1;
int date = 1;


int newdayint;
int dayint = 1;

int oldyear = 3, oldmonth = 3, olddate = 3;



ISR (INT0_vect) {
	msDelay(50);
	if (interruptButton)
	{
		state++;
	}
	if (state > 6)
		state = 1;
}


int alarmH = 0;
int alarmM = 0;

void setAlarmState()
{
	clearLCD();
	printString("Set alarm?");
	LCDline(1);
	msDelay(50);

	if (confirmButton) {
		setAlarmH();
	}
}

void setAlarmH() {

	loopa = 1;

	clearLCD();
	printString("Set alarm hour:");

	while(loopa == 1){
		if ((PIND & (1 << PD6))) {
			alarmH++;
			msDelay(100);
		}

		if (minusButton) {
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

		if (confirmButton) {
			msDelay(50);
			if (confirmButton) {
				msDelay(50);
				if (confirmButton) {
					LCDline(0);
					printString("Hour set!      ");
					msDelay(1000);
					clearLCD();
					printString("Set alarm min:");
					setAlarmM();
				}
			}
		}
	}
}

void setAlarmM() {

	while(loopa == 1){

		if (plusButton) {
			alarmM++;
			msDelay(100);
		}

		DDRD &= ~(1 << PD5);
		if (minusButton) {
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

		if (confirmButton) {
			msDelay(50);
			if (confirmButton) {
				LCDline(0);
				printString("Minute set!   ");
				msDelay(1000);
				LCDline(0);
				printString("Alarm set!  ");
				sound = 1;
				msDelay(3000);
				clearLCD();
				loopa = 0;
				state = 1;
			}
		}
	}
}

int oldalarmH = 3;
int oldalarmM = 3;


void alarmPrint(int alarmH, int alarmM)
{

	if (alarmM != oldalarmM) {
		msDelay(50);
		LCDline(1);

		if (alarmH < 10) {
			printInt(0);
			printInt(alarmH);
		} else if (alarmH >= 10) {
			printInt(alarmH);
		}

		printString(":");

		if (alarmM < 10) {
			printInt(0);
			printInt(alarmM);
		} else if (alarmM >= 10) {
			printInt(alarmM);
		}
	}
	oldalarmH = alarmH;
}

void setTimeState()
{
	clearLCD();
	printString("Change time?");
	LCDline(1);
	msDelay(50);

	if (confirmButton) {
		msDelay(50);
		if (confirmButton) {
			changeTimeH();
		}
	}
}

void changeTimeH()
{
	//get time variables
	loopa = 1;

	clearLCD();
	printString("Set new hour:");

	while(loopa == 1){

		DDRD &= ~(1 << PD6);
		if (plusButton) {
			hour++;
			msDelay(100);
		}

		DDRD &= ~(1 << PD5);
		if (minusButton) {
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


		if (confirmButton) {
			msDelay(50);
			if (confirmButton) {
				LCDline(0);
				printString("New hour set!     ");
				msDelay(1000);
				clearLCD();
				printString("Set new min:");
				changeTimeM();
			}
		}
	}
}


void changeTimeM()
{
	while(loopa == 1){
		if (plusButton) {
			min++;
			msDelay(100);
		}

		DDRD &= ~(1 << PD5);
		if (minusButton) {
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


		if (confirmButton) {
			msDelay(50);
			if (confirmButton) {
				LCDline(0);
				printString("New minute set!   ");
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
	clearLCD();
	printString("Confirm change?");
	LCDline(1);
	alarmPrint(hour,min);

	while (counter < 50){
		if (confirmButton) {
			msDelay(150);
			if (confirmButton) {
				clearLCD();
				printString("Time changed!");
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
		clearLCD();
		printString("Time not changed!");
		msDelay(3000);
		state = 1;
	}
}

void resetTime()
{
	RegisterSetter(hour, 1, 1); //set hours
	RegisterSetter(min, 2, 1); //set minutes
	RegisterSetter(0, 3, 1); //set seconds always as 0
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
		writeTime(newdata, reg);
	else if (hvad == 2)
		writeDays(newdata, reg);
	else if (hvad == 3)
		writeWeekday(newdata);
}


void setDateState()
{
	clearLCD();
	printString("Set date?");
	LCDline(1);
	msDelay(50);

	if (confirmButton) {
		msDelay(150);
		if (confirmButton) {
			setDateDate();
		}
	}
}

void setYear()
{



	clearLCD();
	printString("Set year");

	while(loopa == 1){
		if (plusButton) {
			year++;
			msDelay(100);
		}

		if (minusButton) {
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

		if (confirmButton) {
			msDelay(50);

			if (confirmButton) {
				LCDline(0);
				printString("Year set!      ");
				RegisterSetter(year,1,2);
				RegisterSetter(month,2,2);
				RegisterSetter(date,3,2);
				msDelay(3000);
				clearLCD();
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
		LCDline(1);


		if (date < 10) {
			printInt(0);
			printInt(date);
		}
		else if (date >= 10) {
			printInt(date);
		}

		printString(".");

		if (month < 10) {
			printInt(0);
			printInt(month);
		}
		else if (month >= 10) {
			printInt(month);
		}

		printString(".");

		if (year < 10) {
			printInt(0);
			printInt(year);
		}
		else if (year >= 10) {
			printInt(year);
		}
	}

	oldyear = year;
	oldmonth = month;
	olddate = date;
}

void setMonth()
{
	clearLCD();
	printString("Set Month");

	while(loopa == 1){
		if (plusButton) {
			month++;
			msDelay(100);
		}

		if (minusButton) {
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

		if (confirmButton) {
			msDelay(50);
			if (confirmButton) {
				msDelay(50);
				if (confirmButton) {
					LCDline(0);
					printString("Month set!     ");
					msDelay(1000);
					clearLCD();
					printString("Set Date:");
					setYear();
				}
			}
		}
	}
}


void setDateDate()
{

	clearLCD();
	printString("Set Date");

	loopa = 1;

	while(loopa == 1){
		if (plusButton) {
			date++;
			msDelay(100);
		}

		if (minusButton) {
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

		if (confirmButton) {
			msDelay(50);
			if (confirmButton) {
				msDelay(50);
				if (confirmButton) {
					LCDline(0);
					printString("Date set!    ");
					msDelay(1000);
					clearLCD();
					printString("Set Month:");
					setMonth();

				}
			}
		}
	}
}

void setDayState()
{
	clearLCD();
	printString("Set weekday?");
	LCDline(1);
	msDelay(50);

	if (confirmButton) {
		clearLCD();
		msDelay(150);
		if (confirmButton) {
			msDelay(200);
			setDayDay();
		}
	}
}

void setDayDay()
{


	printString("Set day");
	LCDline(1);
	loopa = 1;

	while(loopa == 1){

		if (plusButton) {
			dayint++;
			msDelay(100);
			LCDline(1);
		}

		if (minusButton) {
			dayint--;
			msDelay(100);
			LCDline(1);
		}

		if (newdayint != dayint){
			switch (dayint)
			{
			case 1: //Monday
				printString("MON");
				msDelay(100);
				break;
			case 2: //Tuesday
				printString("TUE");
				msDelay(100);
				break;
			case 3: //Wednesday
				printString("WED");
				msDelay(100);
				break;
			case 4: //Thursday
				printString("THU");
				msDelay(100);
				break;
			case 5: //Friday
				printString("FRI");
				msDelay(100);
				break;
			case 6: //Saturday
				printString("SAT");
				msDelay(100);
				break;
			case 7: //Sunday
				printString("SUN");
				msDelay(100);
				break;
			case 8:
				dayint = 1;
				msDelay(100);
				break;
			}
		}

		newdayint = dayint;

		if (confirmButton) {
			msDelay(150);
			if (confirmButton) {
				RegisterSetter(dayint, 3, 3);
				LCDline(0);
				printString("Weekday set! ");
				msDelay(3000);
				state = 1;
				loopa = 0;
				clearLCD();
			}
		}

	}
}

void setAcc()
{
	clearLCD();
	printString("NonREM On/Off");
	LCDline(1);
	printString("Off!");
	msDelay(50);


	if (confirmButton) {
		msDelay(50);
			accOn();
	}
}

void accOn()
{
	loopa = 1;
	AccOn = 1;
	clearLCD();
	LCDline(0);
	printString("NonREM On/Off");
	LCDline(1);
	printString("On!");
	msDelay(5000);
	loopa = 0;
	clearLCD();
	state = 1;
}
