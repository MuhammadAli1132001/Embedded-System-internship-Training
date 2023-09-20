//
sbit pin_1W=P3^7;
//delay  function for smaall delaay
void delay(unsigned int i)
{
    while(i--);
}

//variables declerations
signed int temp;
char display_buffer[33];
float currentTemp;
unsigned char sensorBuffer[2];
//init dataa pin
void init_1W(void)
{
    pin_1W = 1;
    delay(100);
    pin_1W = 0;
    delay(100);
    pin_1W = 1;
    delay(100);
}
//read byte
unsigned char readByte_1W(void)
{
    unsigned int i=0;
    unsigned char dataa = 0;
    for (i=8;i>0;i--)
    {
      pin_1W = 0;
      pin_1W = 1;
			dataa>>=1;
      if(pin_1W==1)
      dataa|=0x80;//biit wise OR 
      delay(10);
    }
    return(dataa);
}
//write byte
void writeByte_1W(unsigned char dataa)
{
    unsigned int i=0;
    for (i=8; i>0; i--)
    {
      pin_1W = 0;
      pin_1W = dataa&0x01;//biit wise AND 
      delay(10);
      pin_1W = 1;
      dataa>>=1;
    }
}
//read_sensor
void read_sensor(void)
{
    init_1W();
    writeByte_1W(0xCC); //skip ROM
    writeByte_1W(0x44); //convert T
    init_1W();
    writeByte_1W(0xCC); //skip ROM
    writeByte_1W(0xBE); //read scratchpad
	
    sensorBuffer[0]=readByte_1W();
    sensorBuffer[1]=readByte_1W();
}
void display_temp(){
	read_sensor();
		temp = sensorBuffer[0];
		temp &= 0x00FF;
		//temp= 00_sensorBuffer[0];
		temp |= (sensorBuffer[1] << 8);
		//temp= sensorBuffer[1]_sensorBuffer[0];
		currentTemp = temp * 0.0625;//converting from raw form
		//converting currunt temp into string and storing in dsiplaydata upto 2 decimal point 
		sprintf(display_buffer, "Temp is= %.2f", currentTemp);
		lcd_cmd(0x80);
		lcd_string(display_buffer);
  	lcd_cmd(0x8F);
		lcd_data('C');
		delay(500000);
}