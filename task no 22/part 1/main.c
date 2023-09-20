#include <reg51.h>
#include "lcd.h" 


#define PD0 0
#define PD1 1
#define SER_DFR 2
#define MODE 3
#define A0 4
#define A1 5
#define A2 6
#define START 7


sbit Din = P3^4;
sbit cs = P3^5;
sbit Dclk = P3^6;
sbit Dout = P3^7;

sbit in_0 = P3^0;
sbit in_1 = P3^1;

void delay_us(unsigned int t){
	
	while (t--);
}

void ADC_init()
{
	
	cs = 1;
	Dclk = 0;
	delay_us(1);
	cs = 0;
	delay_us(100);
	Dclk = 0;	
	delay_us(10);
	Dclk = 1;	

	
}


void ADC_send()
{
	
	Din = 0x9C;
	in_0 = 0;
	in_1 = 5;
	
}


unsigned char ADC_readdata()
{
	unsigned char i,byte = 0;
	
		Dclk= 0;
		delay_ms(1);
			
		byte>>1;
	  
	  for (i = 1; i<12; i++){
			
			byte = Dout | 0X08;
			
		}
		
		return byte;
}

unsigned char createControlWord(unsigned char channel, unsigned char mode, unsigned char ser_dfr, unsigned char pd1, unsigned char pd0) {
    unsigned char controlWord = 0;

                                                             // Set individual bits in the control word byte
    controlWord |= (1 << START);                                      // Set the START_BIT to indicate the start of the control byte
    controlWord |= (channel << A0);                      // Set the channel bits (A2, A1, A0)
    controlWord |= (mode << MODE);                        // Set the MODE bit
    controlWord |= (ser_dfr << SER_DFR);                       // Set the SER/DFR bit
    controlWord |= (pd1 << PD1);                         // Set PD1 bit
    controlWord |= (pd0 << PD0);                          // Set PD0 bit

    return controlWord;
}

void main() {
	
  unsigned char controlWord;
	unsigned char readbyte;

  controlWord = createControlWord(2, 0, 1, 0, 0);//Example:Create a control word for Channel 2,12-bit mode,single-ended reference,PD1=0, PD0=0

	lcd_init();
	ADC_init();  
			
	  readbyte = ADC_readdata(); 
		lcd_write_data(readbyte);
	while(1)
	{
		

		
	}
}



		