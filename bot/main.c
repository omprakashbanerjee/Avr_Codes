/*here we have to use two buttons , one will work as on off switch and other one will  work as direction changing switch*/

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned int count=0;
 int main(void)
 {
	DDRB |=(1<<PB3);
	DDRD |=(1<<PD4)|(1<<PD5)|(1<<PD7);
	DDRB &=~(1<<PB6); //PB6 declared as input
	PORTB |=(1<<PB6); //PB6 pulled high initially
	
	void front(void);
	void back(void);
	
	void off(void);
	
	while(1)
	{
	if(PINB &(1<<PB6))
	 {_delay_ms(50);
		if(bit_is_clear(PINB,6))
	 		{count++;}
	 }
	switch(count)
		{
			case 1: front();
					break;
			case 2:back();
					break;
			default:off();
					break;
		}
	
	}
}
void front(void)
	{
	PORTB |=(1<<PB3);
	PORTD &=~(1<<PD4);
	PORTD|=(1<<PD5);
	PORTD &=~(1<<PD7);
	_delay_ms(100);
	}
void back(void)
		{ 	
		PORTB &=~(1<<PB3);
		PORTD |=(1<<PD4);
		PORTD&=~(1<<PD5);
		PORTD |=(1<<PD7);
		_delay_ms(100);
		}
void off(void)
	{
		count=0	;
		PORTB &=~(1<<PB3);
		PORTD &=~((1<<PD4)|(1<<PD5)|(1<<PD7));	
		_delay_ms(100);
		}