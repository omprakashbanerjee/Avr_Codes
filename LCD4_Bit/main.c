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
  DDRD = 0xFF;
  DDRC = 0xFF;
  int i;
  Lcd4_Clear();
  Lcd4_Init();
  while(1)
  {
    /*Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Welcome To....");
	Lcd4_Set_Cursor(2,0);
    Lcd4_Write_String("IECTElectronics");
	_delay_ms(2000);*/
    
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,1);Lcd_Write("OM");
    Lcd4_Set_Cursor(2,1);
    Lcd_Write("OM"); //for this program ony i have changed string printing function to Lcd_Write("");
    Lcd_Write("PRAKASH");
	//Lcd4_Write_String("OM");
	/*for(i=0;i<=15;i++)
    {
      _delay_ms(300);
      Lcd4_Shift_Left();
    }
	for(i=0;i<15;i++)
    {
      _delay_ms(300);
      Lcd4_Shift_Right();
    }*/ 
    _delay_ms(2000);
  }
}