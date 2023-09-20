#include <reg51.h>
#include <intrins.h>
#include "LCDh.h"
#include <stdio.h>


#define EEPROM_ADDRESS 0xA0
#define PAGE_SIZE 64


sbit SCL = P2^1; // I2C Clock pin
sbit SDA = P2^0; // I2C Data pin
sbit WE = P2^2; // I2C Data pin


void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_Write(unsigned char dat);
unsigned char I2C_ReadACK();
unsigned char I2C_ReadNACK();

void EEPROM_WriteByte(unsigned int address, unsigned char Data);
unsigned char EEPROM_ReadByte(unsigned int address);



void main() {
    unsigned char data_write = 0x0A;
    unsigned char data_read;
    char data_read_string[4];           // Assuming the data_read value is between 0 and 255
	  
	  I2C_Init();
		lcd_init();
    
		while(1){
			
	

    EEPROM_WriteByte(0x0001, data_write);           // Write data to EEPROM at address 0x0100


    data_read = EEPROM_ReadByte(0x0001);          // Read data from EEPROM at address 0x0100


    if (data_write == data_read) {                       // Data match

        
    }
		
		else {                                                // Data mismatch
	
 	
   }
 }
}


// I2C Initialization
void I2C_Init() {
	  SDA = 1;
    SCL = 1;
}

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
    _nop_(); _nop_();
	    SDA = 0;
    _nop_();_nop_();

    SCL = 1;
    _nop_();_nop_();

    SDA = 1;
    _nop_();_nop_();

}


void I2C_Write(unsigned char dat) {
    unsigned char i;
		WE = 0;
	
    for (i = 0; i < 8; i++) {
        SDA = (dat & 0x80) ? 1 : 0;
        _nop_();  _nop_();

        SCL = 1;
        _nop_();  _nop_();

        SCL = 0;
			  dat <<= 1;

    }

    // Wait for ACK from the slave
    SDA = 1;
    _nop_();
    SCL = 1;
    while (SDA);                          // Wait for ACK
    SCL = 0;
}

unsigned char I2C_ReadACK() {
    unsigned char i, dat = 0;
		
    SDA = 1;
    for (i = 0; i < 8; i++) {
        _nop_();
        SCL = 1;
        _nop_();
        dat = (dat << 1) | SDA;
        SCL = 0;
    }

    SDA = 0;                         // Send ACK
    _nop_();
    SCL = 1;
    _nop_();
    SCL = 0;
    return dat;
}



void EEPROM_WriteByte(unsigned char address, unsigned char Data) {
    unsigned char page_address = address / PAGE_SIZE;
    unsigned char page_offset = address % PAGE_SIZE;

    I2C_Start();
		I2C_Write((EEPROM_ADDRESS <<1) | 0x00);
    I2C_Write(EEPROM_ADDRESS | ((page_address & 0x07) << 1));
    I2C_Write(page_address);
	  I2C_Write(page_offset);
    I2C_Write(Data);
    I2C_Stop();
}

unsigned char EEPROM_ReadByte(unsigned char address) {
    unsigned char page_address = address / PAGE_SIZE;
    unsigned char page_offset = address % PAGE_SIZE;
    unsigned char Data;

    I2C_Start();
	  I2C_Write((EEPROM_ADDRESS <<1) | 0x00);
    I2C_Write(EEPROM_ADDRESS | ((page_address & 0x07) << 1));
    I2C_Write(page_address);
    I2C_Write(page_offset);

    I2C_Start();
		I2C_Write((EEPROM_ADDRESS <<1) | 0x01);
    I2C_Write(EEPROM_ADDRESS | ((page_address & 0x07) << 1) | 0x01);
    Data = I2C_ReadACK();
    I2C_Stop();

    return Data;
}

 

