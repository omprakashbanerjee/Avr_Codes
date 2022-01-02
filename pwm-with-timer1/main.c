

Skip to content
Using Gmail with screen readers
Meet
New meeting
Join a meeting
Hangouts

Conversations
9.53 GB of 15 GB used
Terms · Privacy · Program Policies
Last account activity: 1 day ago
Details
#include<avr/io.h>
#include<avr/delay.h>
#include<avr/interrupt.h>
ISR(TIMER1_COMPA_vect)
{
PORTB |=(1<<PB0);
}
ISR(TIMER1_COMPB_vect)
{
PORTB &=~ (1<<PB0);

}

ISR(ADC_vect)
{
 uint16_t duty=ADC;
 OCR1B=duty;
}

void PWM_init(void)
{

TCCR1B |= (1<<CS10)|(1<<WGM12);//cs10 means no prescalar n WGM12 means cleartimer on compare match mode is enabl
TIMSK |=(1<<OCIE1A)|(1<<OCIE1B);//timer counter 1 interrupt mask register enables compare A match
OCR1A= 800;
OCR1B=200;
}

void ADC_init(void)
{

ADMUX |=(1<<REFS0)|(1<<MUX0);
ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIF)|(1<<ADIE)|(1<<ADPS1)|(1<<ADPS0);
sei();
}

int main(void)
{

DDRB |=(1<<PB0)|(1<<PB3);
ADC_init();
PWM_init();
while(1)
{
}
}
main.c
Displaying main.c.