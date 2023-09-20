#include <reg51.h>
#include "lcd.h"
#include <intrins.h>
#include <stdio.h>
#include "RTC.h"

sbit DS1302_CE = P3^5; // DS1302 chip enable pin
sbit DS1302_CLK = P3^6; // DS1302 clock pin
sbit DS1302_IO = P3^4; // DS1302 data I/O pin



void  processRealTimeClock()
 {
	  unsigned int hour, minute, second;
    unsigned char day, month, year;
		char timeString[9];
    int datestring[12]; 
    unsigned char decimalSecond;	
	  unsigned char decimalMinute;
    unsigned char decimalHour;
	
	  lcd_init();         // Initialize the LCD
	  DS1302_init();        // Initialize ds1302
	
	   // Set initial time and date
     DS1302_SetTime(11, 03, 01); 
     //DS1302_SetDate(10, 11, 2001); 

    while (1)
    {	  

        // Read time from DS1302
        DS1302_GetTime(&hour, &minute, &second);
        DS1302_GetDate(&day, &month, &year);
			  
 		    decimalHour = (hour >> 4) * 10 + (hour & 0x0F);
        decimalMinute = (minute >> 4) * 10 + (minute & 0x0F);
			  decimalSecond = (second >> 4) * 10 + (second & 0x0F);

	      sprintf(timeString, "%02u:%02u:%02u", hour, minute, decimalSecond);
       // lcd_clear();
			  lcd_set_cursor(0, 0);
        //lcd_write_string("Time:");
        //lcd_set_cursor(0, 5);
        lcd_write_string(timeString); 	       // Display the time on the LCD
    		
			
        // Format the date string
        sprintf(datestring, "%02u:%02u:%04u", day, month, year);
       
			  lcd_set_cursor(1, 0);
        lcd_write_string("Date:");
        lcd_set_cursor(1, 5);
        lcd_write_string(datestring);

          delay_ms(1000);                                // Wait for one second

    }
}


void DS1302_init()
{
	
	DS1302_CE = 0;
	DS1302_IO = 1;
	DS1302_CLK = 0;
	
}

// Function to send a bit to the DS1302
void Send_Bit(unsigned int bitt)
{
		if(bitt==1)
			{
		
			DS1302_IO = 1;
		}
		else
			{
			DS1302_IO = 0;
		}
}

// Function to generate a clock pulse
void SCLK_Pulse()
{
    DS1302_CLK = 1;
    _nop_();
    _nop_();
    DS1302_CLK = 0;
    _nop_();
    _nop_();
}


void write_byte(unsigned int byte)
{
    unsigned char i, Bit;
    
    for (i = 0; i < 8; i++)
    {
			  DS1302_CLK = 0;
        Bit = byte & (1 << i); // Get each bit
        Send_Bit(Bit);         // Send the bit
        SCLK_Pulse();        // Generate clock pulse
			  DS1302_CLK = 1;
    }
}


// Function to write a byte to the DS1302unsigned char cmd,
void DS1302_WriteByte(unsigned int cmd, unsigned int Value)
{
    DS1302_CE = 1;
    DS1302_CLK = 0;
	
    write_byte(cmd);
	  write_byte(Value);

    DS1302_CE = 1;
    DS1302_CLK = 1;
}

void read_byte(unsigned int cmd)
{
	    unsigned int j,Bit;

     for (j = 0; j < 8; j++)
    {     
    DS1302_CLK = 1;
			
        Bit = cmd & (1 << j);       // Get each bit of cmd
        Send_Bit(Bit);             // Send the bit
  			SCLK_Pulse();             // Generate clock pulse
        DS1302_CLK = 0;

		}
		
		
	}
// Function to read a byte from the DS1302
unsigned int DS1302_ReadByte(unsigned int cmd)
{
    unsigned int dat=0, j;
    DS1302_CE =1;
    DS1302_CLK = 1;
	
	  write_byte(cmd);

    // Receive the data byte
    for (j = 0; j < 8; j++)
    {
        dat >>= 1;
        if (DS1302_IO)
        {
            dat |= 0x80;     // Set the corresponding bit in R
        }
        else
        {
            dat &= 0x7F;    // Clear the corresponding bit in R
        }

        SCLK_Pulse();       // Generate clock pulse
    }

    DS1302_CE = 1;
    DS1302_CLK = 0;

    DS1302_IO = 0; // Set the I/O pin back to output mode

    return dat;
}



void DS1302_SetTime(unsigned int hour, unsigned int minute, unsigned int second)
{
	   
	
    DS1302_WriteByte(0x8E,0x00); // Control Register Address, Write mode
    //DS1302_WriteByte(0x80,0x80); // Seconds Register Address, Write mode
	  DS1302_WriteByte(DS1302_SECONDS,second);
    DS1302_WriteByte(DS1302_MINUTES,minute);
    DS1302_WriteByte(DS1302_HOURS,hour);
    		
}



// Function to read the time from DS1302
void DS1302_GetTime(unsigned int *hour, unsigned int *minute, unsigned int *second)
{
	   //DS1302_ReadByte();
    *second = DS1302_ReadByte(DS1302_SECONDS);
    *minute = DS1302_ReadByte(DS1302_MINUTES);
    *hour = DS1302_ReadByte(DS1302_HOURS);
}

// Function to set the date in DS1302
void DS1302_SetDate(unsigned int day, unsigned int month, unsigned int year)
{
	
    DS1302_WriteByte(DS1302_DAY, day);
    DS1302_WriteByte(DS1302_MONTH, month);
    DS1302_WriteByte(DS1302_YEAR, year);
}


//// Function to read the date from DS1302
//void DS1302_GetDate(unsigned char *day, unsigned char *month, unsigned char *year)
//{
//    *day = DS1302_ReadByte(DS1302_DATE);
//    *month = DS1302_ReadByte(DS1302_MONTH);
//    *year = DS1302_ReadByte(DS1302_YEAR);
//}

