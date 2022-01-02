/*here we have to use two buttons , one will work as on off switch and other one will  work as direction changing switch*/

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned int count=0;
 int main(void)
 {
	DDRB |=(1<<PB3); //left motor1 +input
	DDRB |=(1<<PB4); //left motor1 -input
	DDRB|=(1<<PB5)|(1<<PB6); //pb5 moto2+input , pb6 motor2 -input
	DDRD &=~((1<<PD3)|(1<<PD4));

	void front(void);
	void back(void);
	
	void off(void);
	void right(void);
	void left(void);
	
	while(1)
	{
	front();
	if(PIND&(1<<PD3))//when there is nothing IR sensor gives 1 output
		left();
	else if(PIND&(1<<PD4))
		right();
	
	}
}
void right(void)
	{
	PORTB |=(1<<PB3);//left motor on
	PORTB &=~(1<<PB4);
	PORTB&=~(1<<PB5);
	PORTB &=~(1<<PB6);
	_delay_ms(10);
	
	}
void left(void)
	{
	PORTB &=~(1<<PB3);
	PORTB &=~(1<<PB4);
	PORTB|=(1<<PB5);//right motor on
	PORTB &=~(1<<PB6);
	_delay_ms(10);
	
	}
void front(void)
	{
	PORTB |=(1<<PB3);
	PORTB &=~(1<<PB4);
	PORTB|=(1<<PB5);
	PORTB &=~(1<<PB6);
	_delay_ms(100);
	}
void back(void)
		{ 	
		PORTB &=~(1<<PB3);
		PORTB |=(1<<PB4);
		PORTB&=~(1<<PB5);
		PORTB |=(1<<PB6);
		_delay_ms(100);
		}
void off(void)
	{
		count=0	;
		PORTB &=~(1<<PB3);
		PORTB &=~((1<<PB4)|(1<<PB5)|(1<<PB6));	
		_delay_ms(100);
		}