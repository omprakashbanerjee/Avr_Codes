#define F_CPU 16000000UL 
#define D4 PSen_PORTD4
#define D5 PSen_PORTD5
#define D6 PSen_PORTD6
#define D7 PSen_PORTD7
#define RS PSen_PORTC6
#define EN PSen_PORTC7


#include <avr/io.h>
#include<stdlib.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"lcd.h"


uint16_t adc_result;//variable to store the result read from ADC
char buffer[4];//array variable to store output of the itoa function

//initialize all Functions used in code
void adc_init(void);//to configure ADC
//uint16_t read_adc(uint8_t channel);//to read analog channel 0
void USART_init(void);//to configure USART/serial
void USART_Trasmit( unsigned char data);// to send char over the serial port
void Serial_putstring(char* StringPtr);

char String[]="Analog value"; 

int main(void)
{
  DDRC |=(1<<PC6)|(1<<PC7);
	DDRD =0xF0;
	Lcd4_Clear();
	Lcd4_Init();
	
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("ADC=");
	USART_init();
	adc_init();
 
 
	while(1){}
 }
 
 
  ISR (ADC_vect)
   {
  adc_result = ADC;
  
  
  itoa(adc_result, buffer, 10);//itoa function converts integer to string
  
  Lcd4_Set_Cursor(1,6);
		Lcd4_Write_String(buffer);
  Serial_putstring(buffer);
  Serial_putstring("                                                            ");
  
  ADCSRA |=1<<ADSC;//CONVERSION START AGAIN
	}
 
   
   void adc_init(void)
   {
   ADCSRA |=((1<<ADPS2)|(1<<ADPS1));
   ADMUX |=(1<<REFS0)|(0<<MUX0);//VOLTAGE REF IS Avcc
   ADCSRA |=(1<<ADEN);//TURN ON adc
   sei();// ENABLE GLOBAL INTERRUPT
   ADCSRA |=(1<<ADIE)|(1<<ADSC);
  
   }
   
   
   void USART_init(void)
   {
    UBRRH=0x00;
	UBRRL=0x67;
	UCSRB=(1<<RXEN)|(1<<TXEN);
	UCSRC=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
	}
	
   void Serial_putstring(char* StringPtr)
   {
   while(*StringPtr != 0x00)
   {
   USART_Transmit(*StringPtr);
   StringPtr++;
   //this function sends each character, one by one ...
   //after a character is sent, we increment  the pointer (++)
   }
   } 
   
  
   
   void USART_Transmit(unsigned char data)
   {
   while(!(UCSRA &(1<<UDRE)));
   UDR=data;
   }
