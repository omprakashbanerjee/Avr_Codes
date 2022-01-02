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
void ADC_init(void);
void display_temp(void);
char ch[4];
int main(void)
{	DDRB |=(1<<PB0);
	DDRC |=(1<<PC6)|(1<<PC7);
	DDRD =0xF0;
		Lcd4_Clear();
		Lcd4_Init();
		
		sei();
		
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Temp=");
		
		ADC_init();
		while(1)
		{
			display_temp();
			if(ADC_val>30)
			{
				//_delay_ms(100);
				PORTD|=(1<<PD0);
				PORTD&=~(1<<PD1);
				Lcd4_Set_Cursor(2,0);
				Lcd4_Write_String("FAN ON");
				
				
			}
			else
			{
				PORTD|=(1<<PD1);
				PORTD&=~(1<<PD0);
				Lcd4_Set_Cursor(2,0);
				Lcd4_Write_String("FAN OFF");
				
			}
		}
}
ADC_init()
{
	ADMUX |=(1<<REFS0)|(0<<MUX0);
	ADCSRA |=(1<<ADIE)|(3<<ADPS0)|(1<<ADEN)|(1<<ADATE);
	ADCSRA|=(1<<ADSC);
}
ISR(ADC_vect)
{	
	ADC_val=ADC*490/1024;
		
	ADCSRA |=1<<ADSC;
}
void display_temp()
{
			itoa(ADC_val,ch,10);
			Lcd4_Set_Cursor(1,6);
			Lcd4_Write_String(ch);
			Lcd4_Write_String(" ");
}