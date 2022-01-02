#include<avr/io.h>
#include<util/delay.h>
 int main(void)
 {
	DDRB |=(1<<PB0)|(1<<PB1);
	DDRB &=~(1<<PB6);  //pullup button is connected to pin6 of portb
	PORTB |=(1<<PB6);// PB6 is pullup through software already
	PORTB^=(1<<PB0); //if we dont do this then both led will be at same state each time we press the button
//unsigned int count=0; 
	
	while(1)
	{
		if(bit_is_clear(PINB,6)) //when we press the button PB6 willget 0v input
		{ _delay_ms(50); //small delay to ignore the bouncing time
			if(PINB &(1<<PB6)) // then on releasing the button task will be done
			{PORTB^=(1<<PB0)|(1<<PB1);}
	 
		}
	}
 }