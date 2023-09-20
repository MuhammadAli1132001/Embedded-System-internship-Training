// Define LCD control pins
#include <reg52.h>
#include "lcd.h"

unsigned int i = 0;
unsigned int j = 0;
unsigned int digit = 0;

sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;



void delay_ms(unsigned int ms) {
  unsigned int i, j;
  for (i = 0; i < ms; i++)
    for (j = 0; j < 127; j++);
}

void lcd_write_byte(unsigned char dataa, unsigned char rs) {
	
  RS = rs;
  EN = 1;
  delay_ms(10);
	
	port0 = dataa;
//  D0 = (dataa & 0x01);
//  D1 = (dataa & 0x02) >> 1;
//  D2 = (dataa & 0x04) >> 2;
//  D3 = (dataa & 0x08) >> 3;
//  D4 = (dataa & 0x10) >> 4;
//  D5 = (dataa & 0x20) >> 5;
//  D6 = (dataa & 0x40) >> 6;
//  D7 = (dataa & 0x80) >> 7;
  delay_ms(10);
  EN = 0;
}

void lcd_write_command(unsigned char command) {
	RW = 0;
  lcd_write_byte(command, 0);
}

void lcd_write_data(unsigned char dataa) {
	RW = 0;
  lcd_write_byte(dataa, 1);
}

void lcd_clear(void) {
  lcd_write_command(LCD_CLEAR_DISPLAY);
}

void lcd_blink_cursor(void){
			
		  lcd_write_command(0x0E);

}

void lcd_init(void) {
//	unsigned char i;
  lcd_write_command(LCD_FUNCTION_SET);
	  delay_ms(20);

  lcd_write_command(LCD_DISPLAY_ON);
	  delay_ms(20);
	
  lcd_write_command(LCD_FUNCTION_SET_8BIT);
	  delay_ms(20);

  lcd_write_command(LCD_FUNCTION_SET_2LINE );
	  delay_ms(20);

  lcd_write_command(LCD_FUNCTION_SET_5X8DOTS);
	  delay_ms(20);

	lcd_write_command(LCD_DISPLAY_ON_OFF_CONTROL);
	  delay_ms(20);
	
   lcd_clear();
    delay_ms(20);
	
	
//  for (i = 0; i <8; i++) {
//    lcd_write_symbol(i, specialcharacter[i]);
//  }
                                                                             // Entry mode set
  lcd_write_command(LCD_ENTRY_MODE_SET);
	//lcd_write_command(LCD_ENTRY_MODE_SET_INCREMENT);


}

void lcd_set_cursor(unsigned char row, unsigned char col) {
	
  unsigned char address;
  if (row == 0) {
    address = LCD_SET_DDRAM_ADDRESS | col;
  } else {
    address = LCD_SET_DDRAM_ADDRESS | (0x40 + col);
  }
  lcd_write_command(address);
}

void lcd_disp_numb(unsigned int Numb, unsigned char Length)
{
    unsigned int divisor = 1;
		unsigned char q;
	
    for (i = 1; i < Length; i++) {
        divisor *= 10;
    }

    for (q = 0; q < Length; q++) {
        digit = (Numb / divisor) % 10;
        lcd_write_data(digit + '0');
        divisor /= 10;
    }
}


void lcd_write_string(char *str) {
  unsigned int i = 0;
  while (str[i] != '\0') {
    lcd_write_data(str[i]);
    i++;
  }
}

