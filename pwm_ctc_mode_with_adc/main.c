/*program for changing frequency based on adc value*/
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
void pwm_init(void);
/* 
this part of the program is actually useless


#define FREQ 16000000UL // crsytal freqeuncy
#define PRESCALER 8 
#define F_OUT 10000 // output frequency
#define OCR0_VALUE ((FREQ/(2*PRESCALER*F_OUT))-1)  //this expression results in  a  nmber which is greater than the range of integer
*/

uint16_t ADC_val;
volatile uint8_t duty;

int main(void)
{ 
	sei(); // enable global interrupts
	ADMUX |=(1<<REFS0)|(0<<MUX0);
	ADCSRA |=(1<<ADIE)|(3<<ADPS0)|(1<<ADEN)|(1<<ADATE);
		pwm_init(); // timer initialize

	ADCSRA|=(1<<ADSC);
	while(1);
}
 
void pwm_init()
{
	// WGM0[1:0]= 10, for CTC mode
	// COM0[1:0]= 01, to toggle OC0 on compare match

	TCCR0=(1<<WGM01)|(1<<COM00)|(5<<CS00);// CS0[2:0] =010. for prescaler 8
	DDRB|=(1<<PB3)|(1<<PB0); // select as output pin 
	TIMSK|=(1<<OCIE0); //enable output compare interrupt 
	OCR0=99;
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
	//duty=(uint8_t)ADC_val/4; bcz of this (type_casting) our result value was coming in between 0 to 63
	duty=ADC_val/4;
	//OCR0=duty;
	//_delay_ms(10);
	
	ADCSRA |=1<<ADSC;
}

ISR(TIMER0_COMP_vect) // interrupt subroutine
{
	OCR0=duty;
	PORTB ^=(1<<PB0);//OCR0=duty; //put OCR value
}
