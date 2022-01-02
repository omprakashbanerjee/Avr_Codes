#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
void t0_init(void);
/* 
this part of the program is actually useless


#define FREQ 16000000 // crsytal freqeuncy
#define PRESCALER 8 
#define F_OUT 10000 // output frequency
#define OCR0_VALUE ((FREQ/(2*PRESCALER*F_OUT))-1)  //this expression results in  a  nmber which is greater than the range of integer

*/

int main(void)
{ 
t0_init(); // timer initialize
sei(); // enable global interrupts
while(1);
}
 
void t0_init()
{
// WGM0[1:0]= 10, for CTC mode
// COM0[1:0]= 01, to toggle OC0 on compare match
// CS0[2:0] =010. for prescaler 8
 
TCCR0=(1<<WGM01)|(1<<COM00)|(1<<CS01);
DDRB|=(1<<PB3); // select as output pin 
TIMSK|=(1<<OCIE0); //enable output compare interrupt 
}
 
ISR(TIMER0_COMP_vect) // interrupt subroutine
{
OCR0=OCR0_VALUE; //put OCR value
OCR0=49;

}