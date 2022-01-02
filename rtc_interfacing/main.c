#define F_CPU 16000000UL 
#define D4 PSen_PORTD4
#define D5 PSen_PORTD5
#define D6 PSen_PORTD6
#define D7 PSen_PORTD7
#define RS PSen_PORTC6
#define EN PSen_PORTC7


#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "I2C_Master_H_file.h"
#include "lcd.h"

#define Device_Write_address	0xD0	/* Define RTC DS1307 slave write address */
#define Device_Read_address	0xD1	/* Make LSB bit high of slave address for read */
#define TimeFormat12		0x40	/* Define 12 hour format */
#define AMPM			0x20


int second,minute,hour,day,date,month,year;

bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);	/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);/* Repeated start with device read address */

	second = I2C_Read_Ack();	/* Read second */
	minute = I2C_Read_Ack();	/* Read minute */
	hour = I2C_Read_Nack();		/* Read hour with Nack */
	I2C_Stop();			/* Stop i2C communication */
}

void RTC_Read_Calendar(char read_calendar_address)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	day = I2C_Read_Ack();		/* Read day */ 
	date = I2C_Read_Ack();		/* Read date */
	month = I2C_Read_Ack();		/* Read month */
	year = I2C_Read_Nack();		/* Read the year with Nack */
	I2C_Stop();			/* Stop i2C communication */
}

int main(void)
{
	char buffer[20];
	char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

	I2C_Init();			/* Initialize I2C */
	Lcd4_Init();			/* Initialize LCD16x2 */

    while(1)
    {
		RTC_Read_Clock(0);	/* Read clock with second add. i.e location is 0 */
		if (hour & TimeFormat12)	
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			if(IsItPM(hour))
			strcat(buffer, "PM");
			else
			strcat(buffer, "AM");
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String(buffer);
		}
		
		else
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String(buffer);
		}
		RTC_Read_Calendar(3);	/* Read calendar with day address i.e location is 3 */
		sprintf(buffer, "%02x/%02x/%02x %3s ", date, month, year,days[day-1]);
		Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String(buffer);
    }
}