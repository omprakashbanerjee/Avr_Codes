#include<avr/io.h>
#define LED PD4
int main(void)
{
	unsigned int Count0=0,Count1=0,Count2=0;
	DDRD=0xFF;
	TCNT0=0x00;
	TCCR0 =(1<<CS00 | 1<<CS01);
	
	TCNT1=0x00;
	TCCR1B =(1<<CS10 | 1<<CS11);
	
	TCNT2=0x00;
	TCCR2 =(1<<CS20 | 1<<CS21);
	while(1)
		{
			while((TIFR & (1<<TOV0))==0);
			{
				TCNT0=0x01;
				TIFR=(1<<TOV0);
				Count0++;
				if(Count0>=10)
					{
						PORTD^=(1<<PD4);
						Count0=0;
					}
		    }
			while((TIFR & (1<<TOV1))==0);
			{
				TCNT1=0x01;
				TIFR=(1<<TOV1);
				Count1++;
					if(Count1>=20)
					{
						PORTD^=(1<<PD5);
						Count1=0;
					}
		    }
			
			while((TIFR & (1<<TOV2))==0);
			{
				TCNT2=0x01;
				TIFR=(1<<TOV2);
				Count2++;
				if(Count2>=15)
					{
						PORTD^=(1<<PD6);
						Count2=0;
					}
		    }
        }
}