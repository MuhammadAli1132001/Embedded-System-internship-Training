#include <reg51.h>

sbit interrupt_buttonK1 = P3^1;
sbit interrupt_buttonK2 = P3^0;
sbit interrupt_buttonK3 = P3^3;
sbit interrupt_buttonK4= P3^4;



sbit D1_led = P2^0;
sbit D2_led = P2^1;
sbit D3_led = P2^2;
sbit D4_led = P2^3;

unsigned int i,j;


 void delay(unsigned int time){
	
	for(i=0; i<time; i++){
		for (j=0; j<1275; j++);
		
	}
}
 


 void IT0INT(void) interrupt 2
{
		if(interrupt_buttonK1 == 0){
			
     D1_led = ~D1_led;
	   delay(100);
	}
		
}

void main()
{			
		EX1 = 1;
	  EA = 1;

	 interrupt_buttonK3 = 0;
	 //interrupt_buttonK4 = 0; 


	while(1){
	}
}