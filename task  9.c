#include <reg51.h>

sbit D1_led = P2^0;

unsigned int cntr_10ms = 0;

	void timer0(void) interrupt 1
	{
		cntr_10ms++;
		
		    if (cntr_10ms >=37){  					/* toggling led-1 with 10ms  delay */
					
			    D1_led = ~D1_led;
					cntr_10ms = 0;
				}
						
	}
				
				
	void main(void)
		{
			
			
					TMOD = 0x02;          /*  timer0 mode 2 */
    			IE = 0x8A;               /* enable global and timer0 interupt */
			
					TH0 = 0x01;             /* 0.255 ms */
					TR0 = 1;                   /* start timer0 interupt */

		      while (1);
					
	}
		
	