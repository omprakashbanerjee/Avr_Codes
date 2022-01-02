#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>


int main(void){

DDRB|=(1<<PB5)|(1<<PB6)|(1<<PB4);
DDRB &=~(1<<PB2);

DDRD &=~((1<<PD2)|(1<<PD3));

 GICR=1<<INT0|1<<INT1|1<<INT2;
 MCUCR=(1<<ISC00)|(1<<ISC01);
 MCUCR=1<<ISC11|(1<<ISC10);
 MCUCSR=1<<ISC2;
 
 
 sei();
 while(1){
   PORTB ^=(1<<PB5);
    PORTB ^=(1<<PB6);
	 PORTB ^=(1<<PB4);
	 
	 }
	
}
void f1(void){
	
	while(1){
	if(bit_is_clear(PIND,2))
	break;
	else
	PORTB &=~(1<<PB4);
	}

}

void f2(void){
	
	while(1){
	if(bit_is_clear(PIND,3))
	break;
	else
	PORTB &=~(1<<PB5);
}


void f3(void){
	
	while(1){
	if(bit_is_clear(PINB,2))
	break;
	else
	PORTB &=~(1<<PB6);
}

ISR(INT0_vect){f1();}
ISR(INT1_vect){f2();}
ISR(INT2_vect){f3();}