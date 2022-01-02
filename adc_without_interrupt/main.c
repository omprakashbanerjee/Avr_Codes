#define F_CPU 16000000UL 
#define D4 PSen_PORTD4
#define D5 PSen_PORTD5
#define D6 PSen_PORTD6
#define D7 PSen_PORTD7
#define RS PSen_PORTC6
#define EN PSen_PORTC7

#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#include"lcd.h"
#include<avr/interrupt.h>
uint16_t ADC_val;
uint16_t adc_read(void);
char ch[4];
int main(void)
{	DDRB |=(1<<PB0)|(1<<PB1);
	DDRC |=(1<<PC6)|(1<<PC7);
	DDRD =0xF0;
		Lcd4_Clear();
		Lcd4_Init();
		ADMUX |=(1<<REFS0);
		sei();
		
		ADCSRA |=(1<<ADIE)|(3<<ADPS0)|(1<<ADEN);
		
		while(1)
		{
			ADC_val=adc_read();
			itoa(ADC_val,ch,10);
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String(ch);
			
		}
}
uint16_t adc_read()
{ int Ain,AinLow;
	
	ADMUX&=~ (1<<MUX0);
	ADCSRA|=(1<<ADSC); //start conversion
	while((ADCSRA&(1<<ADIF))==0);
	AinLow = (int)ADCL;				/*read lower byte*/
	Ain = (int)ADCH*256;			/*read higher 2 bits, Multiply with weightage*/
	Ain = Ain + AinLow;				
	return(Ain);			

}
//this program doesnt work