#include <reg51.h>

sbit D1_led = P2^0;
sbit D2_led = P2^1;
sbit D3_led = P2^2;

	unsigned int inc_delay_10ms = 0;
	unsigned int inc_delay_100ms = 0;
	unsigned int inc_delay_1000ms = 0;

	void T0INT() interrupt 1
	{
		inc_delay_10ms ++;

		  if (inc_delay_10ms >=38){            /* toggling led-1 with 10ms  delay */
				
			  D1_led = ~D1_led;
				inc_delay_10ms = 0;
				inc_delay_100ms ++;
			}

				else if(inc_delay_100ms >=10){          /* toggling led-2 with 100ms  delay */
					
					D2_led = ~D2_led;
					inc_delay_100ms = 0;
			    inc_delay_1000ms ++;
				}	
				else if (inc_delay_1000ms >=10){        /* toggling led-3 with 1000ms  delay */
						
						D3_led = ~D3_led;
						inc_delay_1000ms = 0;
					}	
		}
				
		
	void main()
		{
			
			
					TMOD = 0x02;          /*  timer0 mode 2 */
    			IE = 0x8A;               /* enable global and timer0 interupt */
			
					TH0 = 0x01;
					TR0 = 1;                   /* start timer0 interupt */
			
			while (1);
	
	}
		
	