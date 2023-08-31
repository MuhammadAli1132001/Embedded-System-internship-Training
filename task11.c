#include <reg51.h>

sbit k1 = P3^1;
unsigned int k1_btn_state = 0;
unsigned int k1_press_cntr = 0;
unsigned int k1_release_cntr = 0;
unsigned int k1_btn_stat = 1;

sbit led_d1 =P2^0;
sbit led_d2 = P2^1;

unsigned int	incr_10ms = 0;

void INTT0 (void) interrupt 1
{
	incr_10ms ++;
	
	if(incr_10ms >= 38)
	{
		//led_d1 = ~led_d1;
		
		if(k1_btn_stat==0 && k1==0){          //press state
			k1_press_cntr ++;
			
				if(k1_press_cntr == 10){         //100ms press
					led_d2 = ~led_d2;
					k1_btn_stat = 1;
					incr_10ms = 0;

		}
	}
		else{
			
				k1_press_cntr =0;
		}
		
	if(k1_btn_stat==1 && k1==1){
			k1_release_cntr ++;
		
			if(k1_release_cntr == 10){
				k1_btn_stat = 0;
   			incr_10ms = 0;
				
		}
	}
		else{
			
				k1_release_cntr =0;
		}
	}
}
void main(void)
{
	TMOD = 0x02;
	IE = 0x82;
	
	TH0 = 0x01;
	TR0 = 1;
	
	while(1);
}
	