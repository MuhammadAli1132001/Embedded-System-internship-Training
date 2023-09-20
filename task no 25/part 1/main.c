#include <reg51.h>
#include "lcd.h"
#include <stdio.h>    

unsigned int second = 0;
unsigned int count = 0;
char seconds_str[3];

void int0_isr(void) interrupt 1
{
	count++;

	if(count==20)
  {
		second++;
		if (second > 60){
				
		    second = 0;
		}
		sprintf(seconds_str, "%02d", second); // Format seconds as two digits
		lcd_set_cursor(0,8);
		lcd_write_string(seconds_str);
	  count = 0;
	}  
	TF0 = 0;
}

void timer_init()
{
	
	TMOD = 0x01;
	TH0 = 0xEF;
	TL0 = 0x41;	
	TR0 = 1;

	ET0 = 1;
	EA = 1;
}


void main(){

	lcd_init();
	lcd_write_string("Second:");
  timer_init();

	while(1){
		
		
	}
	
}