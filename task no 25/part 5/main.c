#include <reg51.h>
#include "lcd.h"
#include <string.h>
#include <stdio.h>

void UART_Init();
void UART_receivedata();
void UART_send_char(unsigned char character);
void display_on_lcd(char *string);             //send msg cursor to the new position 

unsigned char receivedata;
//unsigned char receivemsg[100];
unsigned int index = 0;
bit messagerecieved = 0;

unsigned int hr, min, sec, day, month, year;
char time_str[12]; 
unsigned int count = 0;



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

void timer_init()
{
    TMOD = 0x01;
    TH0 = 0xFF;               // 100ms delay 
    TL0 = 0x9C;
    TR0 = 1; 
	
  	ET0 = 1;
		EA = 1;
}

void update_lcd() {

	sprintf(time_str, "%02d:%02d:%02d", hr,min,sec);       //initiall values formatted shwe
		
    lcd_set_cursor(0, 0);
	  lcd_write_string("RTC :");
    lcd_write_string(time_str);
}

int is_leaf_year(int year)
	{
	
		if(year % 4 == 0  && year % 100 == 0 || (year % 400 == 0))
		{
			return 1;
		}
		
		else {
			return 0;
		}
}


void int0_isr(void) interrupt 1
{
	count++;                                          // Increment ka counter

	if(count == 10){                                   
		
      sec++;                            // Increment ka second
		  if (sec >= 60){
				  sec = 0;
				  min++; 
				if (min >= 60){
						min = 0;
						hr++;
					if (hr >= 24){
							hr = 0;
							day++;
						}	 
					}
				}
			   

		  update_lcd();
			count = 0;
	}
   TF0 = 0;        // Clear Timer 0 interrupt flag
}


void separate_time(char *timestring)
	{

	  sscanf(timestring, "%hhu:%hhu:%hhu", &hr, &min, &sec);
		
	}


void main(){
    
    lcd_init();
	  lcd_write_string("RTC from port");
	  delay_ms(1000);
		lcd_clear();
	
	  UART_Init();      // Initialize UART

    while(1){
			
		UART_receivedata();
			
			if(messagerecieved){
					
				if (receivedata == 'n'){
					
					 time_str[index] = '\0';
					 separate_time(&time_str[0]);
					
            index = 0;                               // Reset the buffer and index for receiving the next message
            memset(time_str, 0, sizeof(time_str));
					  messagerecieved = 0; 
					
  					timer_init();     //timer initialize sho zaka chi timestring recieve sho os ba counting kege

				}		
					
				else 
					{
					time_str[index] = receivedata;
					index++;	
				 }
					
				
		 }
			
		 else {
				    display_on_lcd("nodata");
			   }
  }
		

}
