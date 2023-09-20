#include <reg51.h>
#include <stdio.h>
#include <string.h>
#include "LCDh.h"

void UART_Init();
void UART_Receive();
void displayTimeOnLCD(char *strTime);
void displayDateOnLCD(char *strDate);

unsigned char receivedData;  // Variable to store received data
char receivedMessage[100];   // Buffer to store the received message
unsigned int index = 0;      // Index for storing received characters in the buffer
bit msgreceived = 0;
void main()
{
    //unsigned char hour, minute, second;  // Variables to store hour, minute, and second values

    lcd_init();       // Initialize LCD
    UART_Init();      // Initialize UART

    while(1)
    {
        UART_Receive();  // Receive data from UART
			
			if (msgreceived)
		{
        if (receivedData == 'n')  // Check if the receiveddata is a line feed
        {
            receivedMessage[index] = '\0';  // Add null terminator to mark the end of the received message

            // Message received completely
            // Process the received message to extract hour, minute, and second values
					
            // Display the time on the LCD
					
					if (receivedMessage[0]== 't'){
						
            displayTimeOnLCD(&receivedMessage[1]);
					}
					
					 //Display the Date on the LCD
					
				  else if (receivedMessage[0]== 'd'){
						
            displayDateOnLCD(&receivedMessage[1]);
					}

            // Reset the buffer and index for receiving the next message
            index = 0;
            memset(receivedMessage, 0, sizeof(receivedMessage));
					  msgreceived = 0;
        }
				
        else
        {
            // Message not complete, continue receiving
            // Store the received character in the buffer
            receivedMessage[index] = receivedData;
            index++;
        }
			}
		
		else
		{
			lcd_write_string("nodata");
		}
  }
}

void UART_Init()
{
    TMOD = 0x20;    // Timer 1 mode 2: 8-bit auto-reload
    TH1 = 0xFD;     // Set baud rate to 9600 bps for 11.0592 MHz crystal
    SCON = 0x50;    // 8-bit data, 1 stop bit, REN = 1
    TR1 = 1;        // Start timer
}

void UART_Receive()
{
    while (RI == 0);        // Wait until reception is complete
    RI = 0;                // Clear reception flag
    receivedData = SBUF;   // Store received data
	msgreceived = 1;
}

void displayTimeOnLCD(char *timestring)
{
    char timeformatted[10];  // Buffer to store the formatted time string
		unsigned int hour,minute, second;
	  sscanf(timestring, "%hhu:%hhu:%hhu", &hour, &minute, &second);

    // Format the time string in "hh:mm:ss" format
    sprintf(timeformatted, "%02u:%02u:%02u", hour, minute, second);
	
//	  delay_ms(60000);
//		second++;
//	
//		 if(second>60){
//			 second = 0;
//			 minute++;
//			 
//			 if (minute>60){
//				 minute = 0;
//				 hour++;
//			 }
//			 if (hour>12){
//				 hour = 0;
//				 
//		 }
    // Clear the LCD and display the time string
   // lcd_clear();
	  lcd_set_cursor(0,0);
		lcd_write_string("Time:");
		lcd_set_cursor(0,5);
    lcd_write_string(timeformatted);

}

void displayDateOnLCD(char *datestring)
{
    char dateformatted[12];  // Buffer to store the formatted time string
		unsigned int Day,Month,Year;
	  sscanf(datestring, "%hhu:%hhu:%hhu", &Day, &Month,&Year);

    // Format the time string in "hh:mm:ss" format
    sprintf(dateformatted, "%02u:%02u:%04u", Day, Month, Year);

		
    // Clear the LCD and display the time string
    //lcd_clear();
	  lcd_set_cursor(1,0);
		lcd_write_string("Date:");
		lcd_set_cursor(1,5);
    lcd_write_string(dateformatted);

}
