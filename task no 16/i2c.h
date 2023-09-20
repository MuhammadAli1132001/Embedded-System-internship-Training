#ifndef I2C_H
#define I2C_H

#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
// Function prototypes
void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_write(unsigned char dataa);
unsigned char i2c_read();
unsigned char i2c_read_ack();
unsigned char i2c_read_nack();

#endif // I2C_H
