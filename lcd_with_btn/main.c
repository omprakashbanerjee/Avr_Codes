#define F_CPU 16000000UL 
#define D4 PSen_PORTD4
#define D5 PSen_PORTD5
#define D6 PSen_PORTD6
#define D7 PSen_PORTD7
#define RS PSen_PORTC6
#define EN PSen_PORTC7


#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h" 

int main(void)
{
  DDRD = 0xF3;
  DDRC = 0xFF;
  PORTD |=(1<<PD1);
  PORTD &=~(1<<PD0);
  Lcd4_Clear();
  Lcd4_Init();
  while(1)
  {
  
    if(bit_is_clear(PIND,1))
	{
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("btn low");
	}
	
	else if(PIND &(1<<PD0))
	{
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("btn high");
    
	}
	else Lcd4_Clear();
 }
}