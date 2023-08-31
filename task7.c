#include <reg51.h>

sbit K1 = P3^1;
sbit K2 = P3^0;
sbit K3 = P3^2;
sbit K4 = P3^3;

sbit D1_led = P2^0;
sbit D2_led = P2^1;
sbit D3_led = P2^2;
sbit D4_led = P2^3;

unsigned int i,j;

	void delay(unsigned int time){
	
		for(i=0; i<time; i++){
			for(j = 0; j<1275; j++);
	}
}

	void main(){
		
		while(1){
			
			if (K1 == 0){
				
				D1_led = ~D1_led;
				delay(100);
				
			}
			
			else if (K2 == 0){
				
				D2_led = ~D2_led;
				delay(100);
				
			}	
			
			else if (K3 == 0){
				
				D3_led = ~D3_led;
				delay(100);
				
			}	
			
			else if (K4 == 0){
				
				D4_led = ~D4_led;
				delay(100);
				
			}
		}
	}