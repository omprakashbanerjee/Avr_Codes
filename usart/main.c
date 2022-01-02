#define FOSC 16000000UL// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/(16*BAUD))-1


#include<avr/io.h>
#include<util/delay.h>

unsigned char USART_Receive(void);
void USART_Init(void);
void USART_Transmit( unsigned char data );


unsigned char data='P';
int main( void )
{
	 DDRB |=(1<<PB1);
	 DDRB &=~(1<<PB6);
	 PORTB &=~(1<<PB6);
		USART_Init();
		while(1)
		{
			if(PINB &(1<<PB6)) //when we press the button PB6 willget 5v input
				{ _delay_ms(50); //small delay to ignore the bouncing time
					if(bit_is_clear(PINB,6)) // then on releasing the button task will be done
						{
							PORTB^=(1<<PB1);
							USART_Transmit(data);
						}
	 
				}
			//USART_Receive();
			
		}

}
void USART_Init(void)
{
	/* Set baud rate */
	UBRRH = 0x00; //load 0 in ubrrh
	UBRRL = 0x67; //load 67 in ubrrl this is equivalent to 103 which is for 9600 baud rate 
	/* Enable receiver and transmitter */
	UCSRB |= (1<<RXEN)|(1<<TXEN); // tx rx enbale
	/* Set frame format: 8data, 2stop bit */
	UCSRC |= (1<<URSEL)|(1<<USBS)|(3<<UCSZ0); /* ursel =1 to access ucsrc, usbs=1 for 2 stob bits,
 ucsz0 =3 means ucsz0=1,ucsz1=1 for 8 bit data*/
}



void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}


unsigned char USART_Receive(void)
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}



//void USART_Transmit( unsigned int data )
//{
//	/* Wait for empty transmit buffer */
//	while ( !( UCSRA & (1<<UDRE))) )
	;
//	/* Copy 9th bit to TXB8 */
//	UCSRB &= ~(1<<TXB8);
//	if ( data & 0x0100 )
//	UCSRB |= (1<<TXB8);
//	/* Put data into buffer, sends the data */
//	UDR = data;
//}




// unsigned int USART_Receive( void )
//{
//	unsigned char status, resh, resl;
//	/* Wait for data to be received */
//	while ( !(UCSRA & (1<<RXC)) )
//	;
//	/* Get status and 9th bit, then data */
//	/* from buffer */
//	status = UCSRA;
//	resh = UCSRB;
//	resl = UDR;
//	/* If error, return -1 */
//	if ( status & (1<<FE)|(1<<DOR)|(1<<PE) )
//	return -1;
//	/* Filter the 9th bit, then return */
//	resh = (resh >> 1) & 0x01;
//	return ((resh << 8) | resl);
//}
