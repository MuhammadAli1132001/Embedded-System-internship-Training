#include <reg51.h>
#include <stdio.h>

sbit dis_a = P0^0;
sbit dis_b = P0^1;
sbit dis_c = P0^2;
sbit dis_d = P0^3;
sbit dis_e = P0^4;
sbit dis_f = P0^5;
sbit dis_g = P0^6;
sbit dp = P0^7;


sbit disp1 = P2^7;
sbit disp2 = P2^6;
sbit disp3 = P2^5;
sbit disp4 = P2^4;
sbit disp5 = P2^3;
sbit disp6 = P2^2;
sbit disp7 = P2^1;
sbit disp8 = P2^0;

sbit A = P2^2;
sbit B  = P2^3;
sbit C = P2^4;
unsigned int count_val;


unsigned int digit1;
unsigned int digit2;
unsigned int digit3;
unsigned int digit4;
unsigned int digit5;
unsigned int digit6;
unsigned int digit7;
unsigned int digit8;

void timer_enable(void);
void display_digit(unsigned int);

	void main(void)
		{

		timer_enable();
			
    
		while(1){			
		digit1=1;
		digit2=2;
		digit3=3;
		digit4=4;
		digit5=5;
		digit6=6;
		digit7=7;
		digit8=8;
			
		}
	}
		 
		
		void timer_enable(void)
		{
		
		count_val=1;                              /*Clear Count value*/
		
			
		TMOD = (TMOD & 0x0F) | 0x20;            /* Set Mode (8bit timer with reload) */
		TH1 = 0x06;                            /* 2ms  */
		TL1 = 0x33;
		ET1 = 1;                              /* Enable Timer 1 Interrupts */
		TR1 = 1;                             /* Start Timer 1 Running */
		EA = 1;                              /* Global Interrupt Enable */
		}
		 
		 
	void timer1_ISR (void) interrupt 3
		{
		disp1=0;
		disp2=0;
		disp3=0;
		disp4=0;
		disp5=0;
		disp6=0;
		disp7=0;
		disp8=0;
			dp = 0;
			
	if (count_val==1){
		disp1=1;
		disp2=0;
		disp3=0;
		disp4=0;
		disp5=0;
		disp6=0;
		disp7=0;
		disp8=;
		display_digit(digit1);
		}
	
	else if (count_val==2){
		disp1=0;
		disp2=1;
		disp3=0;
		disp4=0;
		disp5=0;
		disp6=0;
		disp7=0;
		disp8=0;
		display_digit(digit2);
		}
	else if (count_val==3){
		disp1=1;
		disp2=1;
		disp3=0;
		disp4=1;
		disp5=1;
		disp6=1;
		disp7=1;
		disp8=1;
		display_digit(digit3);
		}
	
	else if (count_val==4){
		disp1=1;
		disp2=1;
		disp3=1;
		disp4=0;
		disp5=1;
		disp6=1;
		disp7=1;
		disp8=1;
		display_digit(digit4);
	}
	
	else if (count_val==5){
		disp1=1;
		disp2=1;
		disp3=1;
		disp4=1;
		disp5=0;
		disp6=1;
		disp7=1;
		disp8=1;
			
		display_digit(digit5);
		}
		
	else if (count_val==6){
		disp1=1;
		disp2=1;
		disp3=1;
		disp4=1;
		disp5=1;
		disp6=0;
		disp7=1;
		disp8=1;
		
		display_digit(digit6);	
		}
		
	else if (count_val==7){
		disp1=1;
		disp2=1;
		disp3=1;
		disp4=1;
		disp5=1;
		disp6=1;
		disp7=0;
		disp8=1;
		
		display_digit(digit7);
		}
	
  else if (count_val==8){
		disp1=1;
		disp2=1;
		disp3=1;
		disp4=1;
		disp5=1;
		disp6=1;
		disp7=1;
		disp8=0;

		display_digit(digit8);
		count_val=0;

		}
		count_val++;
	}
		
		/*-------------------------------------------------
		Display thedata passed to this function
		----------------------------------------------------*/
		
	void display_digit(unsigned int digg)
		{
		
	  if (digg==1)
		{
						dp = 1;

		dis_a=1;
		dis_b=0;
		dis_c=0;
		dis_d=1;
		dis_e=1;
		dis_f=1;
		dis_g=1;
		}
		else if (digg==2)
		{
						dp = 1;

		dis_a=0;
		dis_b=0;
		dis_c=1;
		dis_d=0;
		dis_e=0;
		dis_f=1;
		dis_g=0;
		}
		else if (digg==3)
		{
		dis_a=0;
		dis_b=0;
		dis_c=0;
		dis_d=0;
		dis_e=1;
		dis_f=1;
		dis_g=0;
		}
		else if (digg==4)
		{
		dis_a=1;
		dis_b=1;
		dis_c=1;
		dis_d=1;
		dis_e=1;
		dis_f=0;
		dis_g=1;
		}
		else if (digg==5)
		{
		dis_a=0;
		dis_b=1;
		dis_c=1;
		dis_d=1;
		dis_e=0;
		dis_f=0;
		dis_g=0;
		}
		else if (digg==6)
		{
		dis_a=1;
		dis_b=1;
		dis_c=0;
		dis_d=1;
		dis_e=1;
		dis_f=1;
		dis_g=0;
		}
		else if (digg==7)
		{
		dis_a=1;
		dis_b=0;
		dis_c=0;
		dis_d=0;
		dis_e=1;
		dis_f=1;
		dis_g=1;
		}
		else if (digg==8)
		{
		dis_a=1;
		dis_b=1;
		dis_c=1;
		dis_d=1;
		dis_e=1;
		dis_f=1;
		dis_g=1;
		}	
		
}