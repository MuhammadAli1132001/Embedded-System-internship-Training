#include <reg51.h>
#include "LCDh.h"
#include <string.h>

void UART_Init();
void UART_receivedata();
void UART_send_char(unsigned char character);
void display_on_lcd(char *string);             //send msg cursor to the new position 
//void UART_sendstring(char *string);

unsigned char receivedata;
unsigned char receivemsg[100];
unsigned int index = 0;
bit messagerecieved = 0;
void main()
{
		lcd_init();
    UART_Init();      // Initialize UART

   while(1)
    {
			
		UART_receivedata();
			
		if(messagerecieved){
				
		 	if (receivedata == 'n'){
				receivemsg[index] = '\0';
				lcd_set_cursor(0,0);
				display_on_lcd("sended:"); 
	   	delay_ms(1000);
  			lcd_set_cursor(1,0);		
				display_on_lcd(receivemsg);  

			 index = 0;
			 memset(receivemsg, 0, sizeof(receivemsg));             //clear the buffer to receive another msg
			 messagerecieved = 0;
			}		
				
			
			else {
			  receivemsg[index] = receivedata;
			  index++;
				
			}
		}
			else {
				display_on_lcd("nodata");
			}
   }
}


void UART_Init()
{
    TMOD = 0x20;    // Timer 1 mode 2: 8-bitauto-reload
    TH1 = 0xFD;     // Set baud rate to 9600 bps for 11.0592 MHz crystal
    SCON = 0x50;    // 8-bitdata, 1 stopbit, REN = 1
    TR1 = 1;        // Start timer
}

void UART_receivedata()
{
    while (RI == 0);        // Wait until reception is complete
    RI = 0;                // Clear reception flag
	  receivedata = SBUF;   // Store receiveddata
	messagerecieved = 1;

}


void display_on_lcd(char *string)           //send msg cursor to the new position 
{
	lcd_write_string(string);
}
