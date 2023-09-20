#include <reg51.h>
#include <stdio.h>
#include <intrins.h>
#include "LCDh.h"

sbit ds18b20 = P3^7;                  // Define the 1-wire bus pin connection

// Function prototypes
unsigned char reset();
void ow_write_bit(unsigned char Bit);
unsigned char ow_read_bit();
void ow_write_byte(unsigned char byte);
unsigned char ow_read_byte();
float readTemperature();

void delay_us(unsigned int us);


void main(){
	 float temperature;
   char temperatureString[10];
	
	 lcd_init();

	while(1)
		{

			//init_ds18b20();
							
			temperature = readTemperature();
			sprintf(temperatureString, "%.2f", temperature);
			
			//clear_lcd();
			lcd_set_cursor(0,0);
			lcd_write_string("tempreture");
			
			lcd_set_cursor(1,0);
			lcd_write_string(temperatureString);
			delay_ms(1000);
	}
	
}



unsigned char reset()
{
			unsigned char presence=0;
			
			ds18b20 = 1;
			delay_us(8);
			
			ds18b20 = 0;
			delay_us(80);

	    ds18b20 = 1;
			delay_us(14);

   	presence = ds18b20;
			 delay_us(20);

			return presence;
}


void ow_write_bit(unsigned char Bit)
 {
	   ds18b20 = 0;		
			delay_us(2);
	 
	 	   ds18b20 = Bit;		

		 ds18b20 = 1;
			delay_us(65);
	} 
		


unsigned char ow_read_bit()
{
    unsigned char bit_value=0;

    ds18b20 = 0;
    		 delay_us(15);

    ds18b20 = 1;
    		 delay_us(15);
	
    bit_value = ds18b20;
   			 //delay_us(60);

    return bit_value;
}

void ow_write_byte(unsigned char byte)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        ow_write_bit(byte & 0x01); 
        byte >>= 1;
    }
		
		delay_us(10);

}

unsigned char ow_read_byte()
{
    unsigned char i, byte_value = 0;

    for (i = 0; i < 8; i++)
    {
     // ds18b20 = 0;

			byte_value >>= 1;
			//ds18b20 = 1;

        if (ow_read_bit())
        {
            byte_value |= 0x80;
   					delay_us(5);

        }
    }

    return byte_value;
}

float readTemperature()
{
    unsigned char temp_lsb, temp_msb;
	  float temperature;
    int temp_val;
	  char temp_buffer[2];

     reset();
//    {
//       
//        return -9.0;  // Presence pulse not detected Return an error
//    }

    ow_write_byte(0xCC);
    ow_write_byte(0x44);

    delay_ms(750);    //750 ms for 12-bit resolution

    reset();

    ow_write_byte(0xCC);
    ow_write_byte(0xBE);    // Read Scratchpad


    // Read the temperature data (LSB and MSB)
    temp_buffer[0] = ow_read_byte();
    temp_buffer[1] = ow_read_byte();

    temp_val = (temp_buffer[0] << 8) | temp_buffer[1];                          //  temperature value cal
    temp_val = (0x02 << 8) | 0x01;                          //  temperature value cal

     temperature = (float)temp_val * 0.0625;                      // Convert the raw temperature value to Celsius


    return temperature;
}


//void temp_conversion_to_digite(unsigned char t, unsigned char d)
//	{
//		
//  }

	void delay_ms(unsigned int ms)
{
   
	unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 114; j++)
        {
        }
    }
}

void delay_us(unsigned int us)
{

		while(us--)
			{
        _nop_();
    }
}

