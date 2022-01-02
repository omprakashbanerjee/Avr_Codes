#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

int main(void){

DDRD &=~((1<<PD2)|(1<<PD3));
PORTD |=(1<<PD2)|(1<<PD3);
DDRD |=(1<<PB4)|(1<<PB5);

while(1)
{
if(bit_is_clear(PIND,2))
  { _delay_ms(50);
	if(PIND &(1<<PD2))
	{
		GICR =(1<<INT0);
		MCUCR=(1<<ISC00)|(ISC01);
		sei();
	}
}
else if(bit_is_clear(PIND,3))
{ _delay_ms(50);
	if(PIND &(1<<PD3))
	{
		GICR =(1<<INT1);
		MCUCR=(1<<ISC10)|(ISC11);
		sei();
	}
}
else
	{
		PORTB ^=(1<<PB4);
		PORTB ^=(1<<PB5);
		_delay_ms(200);
	}
 }
}


ISR(INT0_vect)
{
	
	PORTB &=~(1<<PB4);
}

ISR(INT1_vect)
{
	PORTB &=~(1<<PB5);
}


