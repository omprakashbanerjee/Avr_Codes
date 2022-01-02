/*program for changing  duty cycle based on adc value using timer0*/

#define F_CPU 16000000UL 
#define D4 PSen_PORTD4
#define D5 PSen_PORTD5
#define D6 PSen_PORTD6
#define D7 PSen_PORTD7
#define RS PSen_PORTC6
#define EN PSen_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include<stdlib.h>
#include<avr/interrupt.h>
#include"lcd.h"
uint16_t ADC_val;
char ch[3];
volatile uint8_t duty;
volatile uint8_t adc8bit;
void PWM_init(void);
void duty_cycle(uint8_t duty);

void PWM_init(void)
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 |= (3<<WGM00) | (2<<COM00) | (2<<CS00);//8 prescaling
	DDRB|=(1<<PB3)|(1<<PB0);  /*set OC0 pin as output*/
	TIMSK|=(1<<TOIE0);
	OCR0=50;//initially one value is given randomly but it will be updated later w.r.t adc value
}


int main (void)
{
	DDRC |=(1<<PC6)|(1<<PC7);
	DDRD =0xF0;
	Lcd4_Clear();
	Lcd4_Init();
	sei();
		PWM_init();	
		ADMUX |=(1<<REFS0)|(0<<MUX0);
		ADCSRA |=(1<<ADIE)|(3<<ADPS0)|(1<<ADEN)|(1<<ADATE);
		//ADCSRA|=(1<<ADLAR);
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Duty=");
		ADCSRA|=(1<<ADSC);
	while (1);
	//{}
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
	//duty=(uint8_t)ADC_val/4; bcz of this type_casting our result value was coming in between 0 to 63
	adc8bit=ADC_val/4;
	duty=adc8bit*25/64;
	itoa(duty,ch,10);
	
	//for(uint8_t i=0;i<4;i++)
		Lcd4_Set_Cursor(1,7);
		Lcd4_Write_String(ch);
		 Lcd4_Write_String(" ");

	
	ADCSRA |=1<<ADSC;
}
ISR(TIMER0_OVF_vect)
{
OCR0=adc8bit;
PORTB^=(1<<PB0);
}

/*
void duty_cycle(uint8_t duty)
{
	OCR0=duty;
}
*/