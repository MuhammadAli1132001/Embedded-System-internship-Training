#include <reg51.h>
#include <stdio.h>
#include <intrins.h>

#include "lcd.h"
#include "temp.h"
#include "cal.h"
#include "RTC.h"

char scan_key(void);
unsigned char s[30]={"ENTER 1 NO= "};
unsigned char s1[30]={"ENTER 2 NO= "};
unsigned char s2[30]={"OPERATOR = "};
unsigned char s3[30]={"Result = "};

sbit r0=P1^0;
sbit r1=P1^1;
sbit r2=P1^2;
sbit r3=P1^3;
sbit c0=P1^4;
sbit c1=P1^5;
sbit c2=P1^6;
sbit c3=P1^7;

void getAndDisplayKeysForCalculator();
void processRealTimeClock();
void processTemperatureMonitor();
char scan_Key();


typedef enum {
    STATE_CALCULATOR,
    STATE_RTC,
    STATE_TEMPERATURE
} AppState;

AppState currentState = STATE_CALCULATOR;             //initial state


void getAndDisplayKeysForCalculator()
  {
		
   while(1){
   unsigned int k=0,m=0,n=0,r=0;
	 int k2,k1;
	 char key,key1;
	 unsigned char ch2;
		 
			lcd_init();
			
		while(s[k]!='\0')
		{
			lcd_write_data(s[k]);
			k++;
		}
			key=scan_key();
			k2=get_num(key);
			lcd_write_data(key);
			lcd_clear();
			
		while(s2[n]!='\0')
		{
			lcd_write_data(s2[n]);
			n++;
		}
			ch2=scan_key();
			lcd_write_data(ch2);
			lcd_clear();
			
		while(s1[m]!='\0')
		{
			lcd_write_data(s1[m]);
			m++;
		}
			key1=scan_key();
			k1=get_num(key1);
			lcd_write_data(key1);
			lcd_clear();
			
		while(s3[r]!='\0')
		{
			lcd_write_data(s3[r]);
			r++;
		}
			
			switch(ch2)
			{
				case '+':
				disp_num(k1+k2);
				break;
				case '-':
				disp_num(k2-k1);
				break;
				case '*':
				disp_num(k2*k1);
				break;
				case '/':
				disp_num(k2/k1);
				break;
		 }
		}
	}

	
void  processTemperatureMonitor(){
	 float temperature;
   char temperatureString[10];
	
	 lcd_init();

	while(1)
		{

			//init_ds18b20();
							
			temperature = readTemperature();
			sprintf(temperatureString, "%.2f", temperature);
			
			//clear_lcd();
			lcd_set_cursor(0,0);
			lcd_write_string("tempreture");
			
			lcd_set_cursor(1,0);
			lcd_write_string(temperatureString);
			delay_ms(1000);
	}
	
}

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

void main() {
        char key;                                   // Initialize hardware and peripherals
    
    while (1) {
			
			
        switch (currentState) {
            case STATE_CALCULATOR:
                getAndDisplayKeysForCalculator();
                break;
            case STATE_RTC:
                processRealTimeClock();
                break;
            case STATE_TEMPERATURE:
                processTemperatureMonitor();
                break;
        }
				
				
		  //  while(key != 0);         //key naye press shawe no hissam mako
				
				 key = scan_key();
				
        // Check for On/C key press to switch between applications
        if (key == 'C') {
            currentState = (currentState + 1) % 3; // Cycle through states
          //  lcd_clear();
            delay_ms(200);
        }
    }
}

