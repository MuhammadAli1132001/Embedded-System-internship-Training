#include <reg51.h>
#define D1 0x01
#define D2 0x02
#define D3 0x03
#define D4 0x04
#define D5 0x05
#define D6 0x06
#define D7 0x07
#define D8 0x08


void delay(unsigned int time){
	
	unsigned int i,j;
	
	for (i=0; i<time; i++){
		
		for (j=0; j<1275; j++);
	}
}
void main (void){

	while(1){
		
	P2 =  P2 | 0x55;
	P2 = P2 & ~0xAA;
	delay(100);
		
	P2 = P2 & ~0x55;
	P2 =  P2 | 0xAA;
  delay(100);

		
	}
}
	
	