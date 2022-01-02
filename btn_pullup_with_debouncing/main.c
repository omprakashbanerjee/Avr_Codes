#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
 int main(void)
 {
	DDRB |=(1<<PB0)|(1<<PB1);
	
	DDRB &=~(1<<PB6);
	PORTB |=(1<<PB6) ;
	PORTB^=(1<<PB0);
	unsigned int bounce_high=0,bounce_low=0,pressed=0;
	
	while(1)
	{
		if(bit_is_clear(PINB,6))
		  {
				bounce_high++;
				if(bounce_high>200)
				{
					if(pressed==0)
						{	pressed=1;
							PORTB^=(1<<PB0);
							PORTB^=(1<<PB1);
							bounce_high=0;
						
						}
				}
		}
			else 
			{
				bounce_low++;
					if(bounce_low>200)
					 {
					 pressed=0;
					 bounce_low=0;
					 }
			}
	 
	}
 }