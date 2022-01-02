/**/
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
//ISR(INT0_vect) //other are INT0_vect ,INT1_vect
//ISR(INT1_vect)
ISR(INT2_vect)
	{
	PORTC =~PORTC;
	// PORTC ^=PORTC; this is wrong statement
	_delay_ms(50);
	}
int main(void)
{
	DDRC=0x07;
	PORTC=0;// all at low
	
	/* DDRD=0;
	 PORTD=0x07; // while  declaring by HEX or binary then dont use OR operator
	 GICR=1<<INT0; // while selecting a bit of a register then dont use or operator just assign 1 using left shift operator; 
	 MCUCR=(1<<ISC01) |(1<<ISC00); //for INT0
	 //MCUCR=(1<<ISC01);
	 //MCUCR=(1<<ISC00);
	*/
	
	
	/*
	 DDRD=0;
	 PORTD=0x08;
	 GICR=1<<INT1;// for INT1
	 MCUCR=(1<<ISC11) |(1<<ISC10); //rising edge
	 //MCUCR=(1<<ISC11);//falling edge
	 //MCUCR=(1<<ISC10); //any logical change in edge
	*/
	
	DDRB=0;
	PORTB=0x04; // while  declaring by HEX or binary then dont use OR operator
	
	GICR=1<<INT2;
	MCUCSR=(1<<ISC2); //for INT2
	sei();
	while(1);
}