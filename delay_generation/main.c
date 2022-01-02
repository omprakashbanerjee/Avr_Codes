#include<avr/io.h>
#define LED PD4
int main(void)
{
	unsigned int Count=0;
	DDRD=0xFF;
	TCNT0=0x00;
	TCCR0 =(1<<CS00 | 1<<CS02);
	while(1)
		{
			while((TIFR & 0x01)==0);
			{
			TCNT0=0x01;
			TIFR=0x01;
			Count++;
			if(Count>=6)
			{
				PORTD^=(1<<PD4);
				Count=0;
			}
		    }
        }
}