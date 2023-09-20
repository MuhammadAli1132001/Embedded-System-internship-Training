
#ifndef temprature_monitor_H
#define temprature_monitor_H


// Function prototypes
unsigned char reset();
void ow_write_bit(unsigned char Bit);
unsigned char ow_read_bit();
void ow_write_byte(unsigned char byte);
unsigned char ow_read_byte();
float readTemperature();

void delay_us(unsigned int us);


#endif