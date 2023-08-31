#include <reg51.h>
	sbit led_D1 = P0^0;

void delayin_ms(unsigned int time)
	{
	unsigned int i,j;
	for(i=0; i<time; i++){
		
		for(j= 0; j<1270; j++);
 }
}
void main (void){

	while(1){
	
		P0 =  0xFF;
		delayin_ms(1000);
		P0 = 0x00;
  	delayin_ms(1000);

 }
}
