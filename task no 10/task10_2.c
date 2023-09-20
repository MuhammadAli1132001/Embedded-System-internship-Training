	#include <reg51.h>
	
	int cntr_100ms = 0;         //variable declaration;
	int cntr_1000ms = 0;
	char flag_100_ms = 0;
	char flag_1000_ms = 0;

	sbit LED_D1 = P2^0;      //LED D1 Connected to port P2^0
	sbit LED_D2 = P2^1;      //LED D2 Connected to port P2^1
	sbit LED_D3 = P2^2;      //LED D3 Connected to port P2^2
	sbit LED_D4 = P2^3;      //LED D3 Connected to port P2^3


	void ISR_timer0(void) interrupt 1     //Interrupt service routine of 10ms overflow
	{ 
		cntr_100ms ++ ;
		cntr_1000ms++;
		
		if (cntr_100ms >= 38)                //if counter reaches 10 it means 100 ms have passed
		{
			LED_D1 = ~LED_D1 ;            //toggle the LED D1
			flag_100_ms = 1;	           //raise the 100 ms flag
			cntr_100ms = 0;                    //restart this counter
		}
		
		if (cntr_1000ms >= 10)               //if this counter reaches 100 it means 1000 ms have passed
		{
			LED_D2 = ~LED_D2;                   //toggle the LED D2
			cntr_1000ms = 0;
			flag_1000_ms = 1;				 //raise the 1000 ms flag
		}
			
	}

	void main (void )
	{
		
			TMOD = 0x02;
			IE = 0x82;
		  
		  TH0 = 0x9C;
			TR0 = 1;
			
		
		while(1)
	{
		if(flag_100_ms)
		{
	 		flag_100_ms = 0;
	    LED_D3 =~ LED_D3; 
			
			//toggle the LED D3
			//This block of cOde will execute after every 100 ms
		}

		if(flag_1000_ms)
		{
			flag_1000_ms = 0;
			LED_D4 =~ LED_D4;                   
			
			//toggle the LED D4
			//This block of cOde will execute after every 1000 ms
		}
	 } 
}
