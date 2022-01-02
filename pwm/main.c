#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


void PWM_init(void)
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (2<<CS00);
	DDRB|=(1<<PB3);  /*set OC0 pin as output*/
}


int main (void)
{
	unsigned char duty;
	
	PWM_init();
	while (1)
	{
		for(duty=10; duty<250; duty++)
		{	
			OCR0=duty;  /*increase the LED light intensity*/
			_delay_ms(8);
		}
		for(duty=250; duty>10; duty--)
		{
			OCR0=duty;  /*decrease the LED light intensity*/
			_delay_ms(8);
		}
	}
}