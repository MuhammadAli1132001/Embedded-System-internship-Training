#include <reg51.h>
#include <stdio.h>
#include "lcdd.h"


void main() {

  lcd_init();
  delay_ms(20);

	 
  // Set cursor to the first row, first column
  lcd_set_cursor(0, 0);
  lcd_clear();
  delay_ms(20);
	
  // Write a string
  lcd_write_string("Custom Character");
  delay_ms(20);
	
	
  // Set cursor to the second row, first column
  lcd_set_cursor(1, 0);
  delay_ms(20);
  // Write 1st spetial character
  lcd_write_data(0);
  delay_ms(200);
	
	// Set cursor to the second row, third column
  lcd_set_cursor(1, 2);
  delay_ms(20);
  // Write  2nd spetial character
  lcd_write_data(1);
  delay_ms(200);
	
	// Set cursor to the second row, fifth column
  lcd_set_cursor(1, 4);
  delay_ms(20);
  // Write  2nd spetial character
  lcd_write_data(2);
  delay_ms(200);

	// Set cursor to the second row,  7th column
  lcd_set_cursor(1, 6);
  delay_ms(20);
  // Write  2nd spetial character
  lcd_write_data(3);
  delay_ms(200);
	
	// Set cursor to the second row, 9th column
  lcd_set_cursor(1, 8);
  delay_ms(20);
  // Write  2nd spetial character
  lcd_write_data(4);
  delay_ms(200);
	
	// Set cursor to the second row, 11th column
  lcd_set_cursor(1, 10);
  delay_ms(20);
  // Write  2nd spetial character
  lcd_write_data(5);
  delay_ms(200);
	
	// Set cursor to the second row, 13th column
  lcd_set_cursor(1, 12);
  delay_ms(20);
  // Write  2nd spetial character
  lcd_write_data(6);
  delay_ms(200);
	
	// Set cursor to the second row, 15th column
  lcd_set_cursor(1, 14);
  delay_ms(20);
  // Write  2nd spetial character
  lcd_write_data(7);
  delay_ms(200);



  while (1) {

  }
}


