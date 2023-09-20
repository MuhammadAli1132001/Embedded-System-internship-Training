#include <reg51.h>
#include <intrins.h>
#include "lcd.h"

#define KEYPAD_PORT P1
#define DISP_PORT P2
#define SegmentDisp P0

sbit disp_2 = P0^2;

char keypad[4][4] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'s','0','=', '+'}
};

typedef enum {
    KEY_IDLE,
    KEY_PRESSED,
    KEY_CONFIRMED
} KeyState;

KeyState keyStates[4][4];
    unsigned int row,col;


void initializeKeyStates() {
	int row,col;
    for ( row = 0; row < 4; row++) {
        for ( col = 0; col < 4; col++) {
            keyStates[row][col] = KEY_IDLE;
        }
    }
}

void displayOnSevenSegment(char key) {
    char digitPatterns[] = {
    0x3F, // 0b00111111 - 0
    0x06, // 0b00000110 - 1
    0x5B, // 0b01011011 - 2
    0x4F, // 0b01001111 - 3
    0x66, // 0b01100110 - 4
    0x6D, // 0b01101101 - 5
    0x7D, // 0b01111101 - 6
    0x07, // 0b00000111 - 7
    0x7F, // 0b01111111 - 8
    0x6F  // 0b01101111 - 9

};

	disp_2 = 0;
  P0 = digitPatterns[key - '0'];
	delay_ms(1000);
	disp_2 = 1;
}

void displayOnLCD(char key) {
    lcd_clear();
    lcd_write_string("KeyPressed:");
    lcd_set_cursor(1, 1);
    lcd_write_data(key);
}

void main() {
    lcd_init(); // Initialize LCD
    initializeKeyStates();
    
	
    while (1) {
        // Non-blocking keypad scanning
        for (row = 0; row < 4; row++) {
            KEYPAD_PORT = ~(1 << row);
            _nop_();
            
            for ( col = 0; col < 4; col++) {
                if (!(KEYPAD_PORT & (1 << (col + 4)))) {
                    if (keyStates[row][col] == KEY_IDLE) {
                        keyStates[row][col] = KEY_PRESSED;
                    } else if (keyStates[row][col] == KEY_PRESSED) {
                        keyStates[row][col] = KEY_CONFIRMED;
                    }
                } else {
                    keyStates[row][col] = KEY_IDLE;
                }
            }
        }
        
        // Check key states
        for ( row = 0; row < 4; row++) {
            for ( col = 0; col < 4; col++) {
                if (keyStates[row][col] == KEY_CONFIRMED) {
                    char key = keypad[row][col];
                    
                    // Display the pressed key on the LCD
                    displayOnLCD(key);
                    
                    // Display the pressed key on the 7-segment display
                    displayOnSevenSegment(key);
                    
                    // Reset the state machine
                    keyStates[row][col] = KEY_IDLE;
                }
            }
        }
        
        // Continue with other non-blocking tasks
    }
}
