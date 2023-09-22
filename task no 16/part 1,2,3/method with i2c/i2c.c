#include "i2c.h" 

sbit SDA = P3^5;
sbit SCL = P3^4;

// Generate a start condition on the I2C bus
void i2c_start() {
    SDA = 1; // Set SDA line high
    _nop_(); // Small delay
    SCL = 1; // Set SCL line high
    _nop_(); // Small delay
    SDA = 0; // Generate a low-to-high transition on SDA while SCL is high (start condition)
    _nop_(); // Small delay
    SCL = 0; // Release SCL line
}

// Generate a stop condition on the I2C bus
void i2c_stop() {
    SDA = 0; // Set SDA line low
    _nop_(); // Small delay
    SCL = 1; // Set SCL line high
    _nop_(); // Small delay
    SDA = 1; // Generate a low-to-high transition on SDA while SCL is high (stop condition)
    _nop_(); // Small delay
}

// Write a byte of Data to the I2C bus
void i2c_write(unsigned char  Data) {
    unsigned char  i;
    for (i = 0; i < 8; i++) {
        if (Data & 0x80) // Check the MSB of the Data
            SDA = 1; // Set SDA line high
        else
            SDA = 0; // Set SDA line low

        _nop_(); // Small delay
        SCL = 1; // Set SCL line high
        _nop_(); // Small delay
        SCL = 0; // Release SCL line
        Data <<= 1; // Shift Data to the left
    }
}

// Read Data byte from I2C bus with ACK
unsigned char  i2c_read_ack() {
    unsigned char  i, Data = 0;
    SDA = 1; // Set SDA line high
    for (i = 0; i < 8; i++) {
        _nop_(); // Small delay
        SCL = 1; // Set SCL line high
        _nop_(); // Small delay
        Data <<= 1; // Shift Data to the left
        if (SDA)
            Data |= 1; // Set the LSB of Data if SDA is high
        SCL = 0; // Release SCL line
    }
    return Data;
}

// Read Data byte from I2C bus with NACK
unsigned char  i2c_read_nack() {
    unsigned char  i, Data = 0;
    SDA = 1; // Set SDA line high
    for (i = 0; i < 8; i++) {
        _nop_(); // Small delay
        SCL = 1; // Set SCL line high
        _nop_(); // Small delay
        Data <<= 1; // Shift Data to the left
        if (SDA)
            Data |= 1; // Set the LSB of Data if SDA is high
        SCL = 0; // Release SCL line
    }
    SDA = 0; // Set SDA line low for NACK
    _nop_(); // Small delay
    SCL = 1; // Set SCL line high
    _nop_(); // Small delay
    SCL = 0; // Release SCL line
    return Data;
}
