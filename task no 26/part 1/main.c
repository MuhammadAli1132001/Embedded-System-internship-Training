////In 8051-based system, the crystal oscillator has a frequency of 11.0592 MHz when C/T bit of TMOD is 0. 
////Each machine cycle is made up of 12 clock cycles. Hence for a single machine cycle, the frequency becomes 1/12 × 11.0529 MHz = 921.6 KHz.

////timer count  by internal interrupt
////counter count  by external interrupt

#include <reg52.h>
#include "lcd.h"

sbit fucntion_generator = P3^4;
bit overflow = 0;

unsigned int frequency = 0;

void timer_counter(){
	      
	      TMOD = 0x16;
				TH0 = 0x00;
				TL0 = 0x00;
				
				TR0 = 1;
}

void ms_delay(unsigned int time)        // da sahi ms delay da, total Delay = 1ms * Value   
{
 unsigned int j;
	   
	for (j=0; j<time ;j++)
	{  
		
		TH1=0xFC;
		TL1=0x19;
		TF1=0;
		TR1=1;
		while(TF1==0){
			
			if(TH1 == 0xFF && TL1 == 0xFF){        //chi timer overflow she
				
				overflow = 1;
				break;
			}
		}
		
		 TF1=0;
		 TR1=0;
	}
}


void main() 
{
		fucntion_generator  = 1;
	
		lcd_init();
	
		lcd_set_cursor(0,1);
		lcd_write_string("Frequency");
		
		lcd_set_cursor(1,10);
		lcd_write_string("Hz");

    while (1) 
			{
				
				timer_counter();
				
				ms_delay(900);            //900ms delay
				TR0 = 0;                 //stop timer
				
				frequency = (TH0*255) + TL0;                  
				lcd_set_cursor(1,5);
				
				if(overflow){
					
					lcd_write_string("Error....");
					
				}
				
				else {
					
				lcd_disp_numb(frequency,4);
					
				}
				
			overflow = 0;
		}
}


//When using Timer 0 in mode 1 (16-bit timer with auto-reload),
//	the maximum frequency that can be accurately counted depends on the clock frequency and the timer's
//	resolution. In mode 1, Timer 0 is a 16-bit timer,
//	which means it can count from 0 to 65535 (2^16 - 1) before overflowing and restarting from 0.

//To calculate the maximum frequency that can be accurately counted, you can use the following formula:

//Maximum Frequency = Clock Frequency / (Maximum Timer Count + 1)

//For example, assuming a clock frequency of 11.0592 MHz (as mentioned in your previous comment),
//	you can calculate the maximum frequency as follows:

//Maximum Frequency = 11.0592 MHz / (65535 + 1)

//Maximum Frequency ˜ 168.75 Hz

//So, with Timer 0 in mode 1 and a clock frequency of 11.0592 MHz,
//	you can accurately count frequencies up to approximately 168.75 Hz.
//If the input frequency exceeds this value, you may encounter timer overflows,
//	and the accuracy of frequency measurement will be compromised.
















