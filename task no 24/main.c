#include <reg51.h>
#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include "lcd.h"

//#define  buzzer P1        // Define a bit for the buzzer

sbit Servo_motor_Pin = P2^0; // Define a bit for the servo motor control pin
sbit column1 = P1^0; // Define columns of the 4x4 keypad
sbit column2 = P1^1;
sbit column3 = P1^2;
sbit column4 = P1^3;

sbit row1 = P1^4; // Define rows of the 4x4 keypad
sbit row2 = P1^5;
sbit row3 = P1^6;
sbit row4 = P1^7;

unsigned char time_string[5] = {"00:00"};
bit oven_started = 0;
sbit door_switch = P3^0;
sbit Relay_in = P2^0;

char keypad[4][4] = {
    {'D', '=', '0', 'C'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A','3','2', '1'}
};


char timestring;

char key_press() {
    char key = 0;
    row1 = 0; row2 = 1;row3 = 1;row4 = 1;
    if (column1 == 0) key = keypad[0][0];
    if (column2 == 0) key = keypad[0][1];
    if (column3 == 0) key = keypad[0][2];
    if (column4 == 0) key = keypad[0][3];
    row1 = 1; // Disable the first row
    
    row1 = 1;   row2 = 0;   row3 = 1;    row4 = 1;

    if (column1 == 0) key = keypad[1][0];
    if (column2 == 0) key = keypad[1][1];
    if (column3 == 0) key = keypad[1][2];
    if (column4 == 0) key = keypad[1][3];
	
    row2 = 1;   row1 = 1;    row2 = 1;    row3 = 0;     row4 = 1;
  
    if (column1 == 0) key = keypad[2][0];
    if (column2 == 0) key = keypad[2][1];
    if (column3 == 0) key = keypad[2][2];
    if (column4 == 0) key = keypad[2][3];
		
    row3 = 1;  row1 = 1;    row2 = 1;    row3 = 1;    row4 = 0;
		
    if (column1 == 0) key = keypad[3][0];
    if (column2 == 0) key = keypad[3][1];
    if (column3 == 0) key = keypad[3][2];
    if (column4 == 0) key = keypad[3][3];
    row4 = 1; // Disable the fourth row
		
		delay_ms(100);
		P1 = 0xFF;
    return key;
}

	
void display_time()
	{
	
				lcd_set_cursor(1,6);
				lcd_write_string(time_string);
				delay_ms(100);
  }


void decrement_time() {                                       // Function to decrement time by 1 
    unsigned char min1 = time_string[0] - '0' ;
    unsigned char min0 = time_string[1] - '0';
    unsigned char sec1 = time_string[3] - '0';
    unsigned char sec0 = time_string[4] - '0';
	
	if (sec0 > 0) {
        sec0--;
    }
	
	else if (sec1 > 0) {
        sec0 = 9;
        sec1--;
    }
	
		else if (min0 > 0) {
        sec0 = 9;
        sec1 = 5;
        min0--;
    }
		
		else if (min1 > 0) {
        sec0 = 9;
        sec1 = 5;
        min0 = 9;
        min1--;
    }
		
		else {
        
        oven_started = 0;                       // Time is already 00:00, stop the oven
    }
 
    time_string[0] = min1 + '0';                 // Update the time_string
		time_string[1] = min0 + '0';
    time_string[3] = sec1 + '0';
    time_string[4] = sec0 + '0';

}

void main()
{
	unsigned char key_count = 0;
  unsigned char key;	
	
	oven_started = 0;
	door_switch = 1;
	Relay_in = 0;
	
	lcd_init();
	
	lcd_clear();
	lcd_set_cursor(0,1);
	lcd_write_string("oven control");
  //lcd_set_cursor(1,6);
	//lcd_write_string("00:00");
				
			
   while (1) {
		 
//    if (door_switch == 0){
//		  Relay_in = 0;
//			delay_ms(5);

//		 }
//		 
//		else {
//			
//		 Relay_in = 1;
//		 delay_ms(5);
//			
//		}
//		
//		 if (Relay_in == 1){
			 
				 key = key_press(); // Get a key press from the keypad
				 
						if (key != '\0' && key != '=' && key != 'C' && key != '*' ) {
							
								key_count++;
							
								if (key_count == 1) {
									
										time_string[4] = key;
										display_time();
								
								}
								
								else if (key_count == 2){
										time_string[3] = time_string[4];							
										time_string[4] = key;
										display_time();
									
									}
								
								else if (key_count == 3){
									
										time_string[1] = time_string[3];							
										time_string[3] = time_string[4];							
										time_string[4] = key;
										display_time();							
									
									}
								
								else if (key_count == 4){
									
										time_string[0] = time_string[1];							
										time_string[1] = time_string[3];		
										time_string[3] = time_string[4];														
										time_string[4] = key;
										display_time();										
									 
									}
						}
						
					else if (key == '=')
					{
						
					 time_string[0] =0 + '0';
					 time_string[1] =0 + '0';
					 time_string[3] =0 + '0';
					 time_string[4] =0 + '0';		
					 display_time();
		       break;				
						
					}
					
					else if (key == 'C') {               // C key press kolo sara oven start kege aw stop kege
						
								if (oven_started) {
										oven_started = 0;             // Pause the oven
										Relay_in = 0;                     
								}
								
								else {
									 if(door_switch == 1){             //door closed
										oven_started = 1;                // Start the oven
										Relay_in = 1;
									}
						 }
					}
					 
					
						
						if (oven_started) {           //oven start sho

								decrement_time();
								delay_ms(10);
								display_time();
								delay_ms(10);
						}
					 delay_ms(100);
	 }
 
}
