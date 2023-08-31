#include <reg51.h>
#include <intrins.h>

sbit button_k1 = P3^1;
sbit led_D1 = P2^0;

unsigned int i,j;


 void delay(unsigned int time){
	
	for (i=0; i<time; i++){
		for (j=0; j<1275; j++);
		
	}
}	
	void main (void){
		
	while(1){
	
		if(button_k1 == 0){
		
			led_D1 = ~led_D1;
			delay(10);
			 
		 }
   }
 }
