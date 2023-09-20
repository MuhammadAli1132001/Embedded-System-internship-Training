#ifndef LCD_H
#define LCD_H

#include <stdio.h> 
#define Lcd_data_port P0

//lcd control pins
sbit rw=P2^5;
sbit rs=P2^6;
sbit enable=P2^7;

//delay function
void msdelay(unsigned int milliseconds)
{
	   unsigned int a,b;
	   for(a=0;a<milliseconds;a++)
	   for(b=0;b<112;b++);
}

//lcd sending command to LCD_DATA_PORT as command
lcd_cmd(unsigned int command)
{
	Lcd_data_port=command;
	rs=0;//
	rw=0;//write mode
	enable=1;
	msdelay(1);
	enable=0;
}

//lcd sending command to LCD_DATA_PORT as dataa 
lcd_data(unsigned int display_data)
{
	Lcd_data_port=display_data;
	rs=1;
	rw=0;
	enable=1;
	msdelay(1);
	enable=0;
}
lcd_init()//commands for lcd intialization
{
	lcd_cmd(0x38);
	msdelay(10);
	lcd_cmd(0x0C);
	msdelay(10);
	lcd_cmd(0x80);
}
void lcd_string(const unsigned char *str) {
    while (*str) {
        lcd_data(*str);
        str++;
    }
}
/*
void lcd_num(int num) {
    unsigned char buffer[16];
    sprintf(buffer, "%d", num);  // Convert number to string
    lcd_string(buffer);
}
*/
#endif // LCD_H

