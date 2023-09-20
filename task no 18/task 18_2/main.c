#include <reg51.h>
#include <intrins.h>
#include "lcd.h"
#include <stdio.h>


#define EEPROM_ADDRESS 0xA0

sbit SDA = P2^0; // I2C Data pin
sbit SCL = P2^1; // I2C Clock pin

sbit disp_5 = P2^5;
sbit disp_4 = P2^4;

typedef unsigned char uchar;
typedef unsigned int iint;

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_Write(uchar dat);
unsigned char I2C_ReadACK();

void EEPROM_WriteByte(uchar address,uchar Data);
unsigned char EEPROM_ReadByte(uchar address);

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

void displaynumber(uchar num){
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

	disp_5 = 0;

	P0 = digitPatterns[num];

}

void main() {
	  
	
		while(1){
			
			displaynumber(counterLow);
			counterLow++;
			
			EEPROM_WriteByte(0x00, counterHigh);
			EEPROM_WriteByte(0x01, counterLow);


 delay_ms(1000);

  }
}

