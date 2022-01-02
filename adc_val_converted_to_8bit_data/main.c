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
 uint8_t data;
char ch[3];
int main(void)
{	DDRB |=(1<<PB0);
	DDRC |=(1<<PC6)|(1<<PC7);
	DDRD =0xF0;
		Lcd4_Clear();
		Lcd4_Init();
		ADMUX |=(1<<REFS0)|(0<<MUX0);
		sei();
		
		ADCSRA |=(1<<ADIE)|(3<<ADPS0)|(1<<ADEN)|(1<<ADATE);
		//ADCSRA|=(1<<ADLAR);
		Lcd4_Set_Cursor(0,0);
		Lcd4_Write_String("ADC=");
		
		
		ADCSRA|=(1<<ADSC);
		while(1){}
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
	data=ADC_val/4;
	itoa(data,ch,10);
	
	//for(uint8_t i=0;i<4;i++)
		Lcd4_Set_Cursor(1,6);
		Lcd4_Write_String(ch);
		 Lcd4_Write_String(" ");

		
		
		
	ADCSRA |=1<<ADSC;
}
