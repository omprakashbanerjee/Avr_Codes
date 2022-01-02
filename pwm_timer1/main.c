#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
uint16_t ADC_val;
uint8_t duty;
void PWM_init(void);

void PWM_init(void)
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (3<<WGM00) | (1<<COM01) | (1<<CS00);//no prescaling
	DDRB|=(1<<PB3)|(1<<PB0);  /*set OC0 pin as output*/
	OCR0=50;
}


int main (void)
{
	ADMUX |=(1<<REFS0)|(0<<MUX0);
		sei();
	PWM_init();	
		ADCSRA |=(1<<ADIE)|(3<<ADPS0)|(1<<ADEN)|(1<<ADATE);
		//ADCSRA|=(1<<ADLAR);
		ADCSRA|=(1<<ADSC);
	while (1)
	{}
}

ISR(ADC_vect)
{	/* for ADLAR=1 ADC results will be left adjusted
	uint8_t ADC_low=ADCL;
	uint16_t ADC_val=ADCL>>6 |ADCH<<2;

	*/

	/* for ADLAR=0 ADC results will be right adjusted
	uint8_t ADC_low=ADCL;
	ADC_val=ADCH<<8|ADC_low;
	*/
	ADC_val=ADC; //for adlar=0 ,we can do this too
	uint8_t duty=(uint8_t)ADC_val*(255/1024);
	OCR0=duty;
	
	ADCSRA |=1<<ADSC;
}
