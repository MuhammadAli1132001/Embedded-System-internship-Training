#include <reg51.h>
#include <intrins.h>
#include "lcd.h"
#include <stdio.h>


#define EEPROM_ADDRESS 0xA0

sbit SDA = P2^0; // I2C Data pin
sbit SCL = P2^1; // I2C Clock pin

sbit disp_1 = P2^2;
sbit disp_2 = P2^3;
sbit disp_3 = P2^4;
sbit disp_4 = P2^5;

typedef unsigned char uchar;
typedef unsigned int iint;
typedef unsigned long ulong;

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_Write(uchar dat);
unsigned char I2C_ReadACK();

void EEPROM_WriteByte(uchar address,uchar Data);
void EEPROM_Write4Byte(uchar address,uchar Data);

unsigned char EEPROM_ReadByte(uchar address);
unsigned long EEPROM_Read4Byte(uchar address);

ulong countValue = 0;
uchar counterLow = 0;
uchar counterHigh = 0;

// I2C Start condition
void I2C_Start() {
    SDA = 1;
    _nop_();
    SCL = 1;
    _nop_();
    SDA = 0;
    _nop_();
    SCL = 0;
    _nop_();_nop_();

}

// I2C Stop condition
void I2C_Stop() {
   
	  SDA = 0;
    _nop_();_nop_();

    SCL = 1;
    _nop_();_nop_();

    SDA = 1;
    _nop_();_nop_();

}

// I2C Initialization
void I2C_Init(){
	
    I2C_Start(); 
    I2C_Stop();
	
}


void I2C_Write(unsigned char dat) {
    unsigned char i;
	
    for (i = 0; i < 8; i++) {
        SDA = (dat & 0x80) ? 1 : 0;
        _nop_();  _nop_();

        SCL = 1;
        _nop_();
        SCL = 0;
        _nop_(); 			

        SCL = 0;
			  dat <<= 1;

    }

    // Wait for ACK from the slave
    SDA = 1;
    _nop_();
    SCL = 1;
    _nop_();
    SCL = 0;
}

unsigned char I2C_ReadACK() {
    uchar i, dat = 0;
		
    SDA = 1;
    for (i = 0; i < 8; i++) {
        _nop_();
        SCL = 1;
        _nop_();
        dat = (dat << 1) | SDA;
        SCL = 0;
    }

//    SDA = 0;                         // Send ACK
//    _nop_();
//    SCL = 1;
//    _nop_();
//    SCL = 0;
    return dat;
}



void EEPROM_WriteByte(uchar address, uchar Data) {
    

    I2C_Start();
		I2C_Write(EEPROM_ADDRESS);
   // I2C_Write(EEPROM_ADDRESS | ((page_address & 0x07) << 1));
    I2C_Write(address);
	  I2C_Write(Data);
    I2C_Stop();
	delay_ms(10);
}


void EEPROM_Write4Bytes(uchar address, ulong value) {
    
	  uchar i;
    for (i = 0; i < 4; i++) {
        EEPROM_WriteByte(address + i, (value >> (i * 8)) & 0xFF);
    }
}



unsigned char EEPROM_ReadByte(uchar address) {
    
    uchar Data;

    I2C_Start();
	  I2C_Write(EEPROM_ADDRESS);
    I2C_Write(address);
	
	  I2C_Start();
    I2C_Write(0xA0);
    Data = I2C_ReadACK();
    I2C_Stop();

    return Data;
}

ulong EEPROM_Read4Bytes(uchar address) {
    ulong value = 0;
    uchar i;
    for (i = 0; i < 4; i++) {
        value |= ((ulong)EEPROM_ReadByte(address + i)) << (i * 8);
    }
    return value;
	}


void displaynumber(ulong value){
	uchar digitPatterns[] = {
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
	
		uchar digits[4];                                              // Array to store individual digits
    
                                                         // Extract individual digits from the 4-byte value
    digits[0] = value % 10;
    digits[1] = (value / 10) % 10;
    digits[2] = (value / 100) % 10;
    digits[3] = (value / 1000) % 10;



    disp_1 = 0; disp_2 = 1; disp_3 = 1; disp_4 = 1;

    P0 = digitPatterns[digits[3]];
		delay_ms(1000);


    disp_1 = 1; disp_2 = 0; disp_3 = 1; disp_4 = 1;
    P0 = digitPatterns[digits[2]];
		delay_ms(1000);

    disp_1 = 1; disp_2 = 1; disp_3 = 0; disp_4 = 1;
    P0 = digitPatterns[digits[1]];
		delay_ms(1000);

    disp_1 = 1; disp_2 = 1; disp_3 = 1; disp_4 = 0;
    P0 = digitPatterns[digits[0]];
		delay_ms(1000);

    // Turn off all displays
        disp_1 = 1;
        disp_2 = 1;
        disp_3 = 1;
        disp_4 = 1;

		 delay_ms(1000);
			
		    
	
}

void main() {
	    
	    lcd_init();
	    I2C_Init();
			
	    countValue = EEPROM_Read4Bytes(0x00); 
			lcd_set_cursor(0,1);
			lcd_write_string("reading");
			lcd_write_data(countValue);
	
		while(1){
			
			displaynumber(countValue);
			countValue++;
			//lcd_write_string();
			EEPROM_Write4Bytes(0x00, countValue);
		 //EEPROM_Write4Byte(0x01, counterLow);
			lcd_set_cursor(1,0);
			lcd_write_string("writing");
			lcd_write_data(countValue);

 delay_ms(1000);

  }
}

