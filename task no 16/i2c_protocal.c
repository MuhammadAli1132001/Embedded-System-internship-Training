 #include<reg52.h>
#include<intrins.h>
#include<stdio.h>
#include "lcd.h"

typedef unsigned char u8;
typedef unsigned int u16;
char day[7][3] = { "SUN", "MON" , "TUE" , "WED" , "THU" , "FRI" , "SAT"};

//*				          I2C SDA SCL										  *


sbit scl=P0^6; //SCL
sbit sda=P0^7; //SDA


//*                       I2C START Condition    							   *

void i2cstart(void)
{
  sda=1;
  _nop_();_nop_();
  scl=1;
  _nop_();_nop_();
  sda=0;
  _nop_();_nop_();
}

//*				           I2C STOP Condition    							    *
void i2cstop(void)
{
  scl=0;
  sda=0;
  scl=1;
  sda=1;
}


//*				                I2C ACK              						    *

void i2cACK(void)
{
  scl=0;
  sda=1;
  scl=1;
  while(sda);
}


//*				                I2C NACK              						    *

void i2cNoAck(void)
{
  scl=0;
  sda=1;
  scl=1;
}

//*				                I2C ReStart Condition  						    *
void i2cRestart()
{
  scl=0;
  sda=1;
  scl=1;
  sda=0;
}

void i2cWrite(u8 dat)
{
  u8 i;
  for(i=0;i<8;i++)
 {
   scl=0;
   sda=(dat&(0x80>>i))?1:0;
   scl=1;
 }
}

u8 i2cRead(void)
{
  u8 i,buff=0;
  for(i=0;i<8;i++)
 {
   scl=0;
   scl=1;
   if(sda)
     buff|=0x80>>i;
 }
  return buff;
}


void i2cDevWrite(u8 sa,u8 buffer,u8 dat)
{
  i2cstart();		   // 1 . Master issue START condition
  i2cWrite(sa&0xfe);   // 2 . Master Send Device Address(8 bites)  fe = 11111110
  i2cACK();			   // 3 . Master Takes ACK from Slave
  i2cWrite(buffer);	   // 4 . Master Send Buffer/Resister Address(8 bites)
  i2cACK();			   // 5 . Master Takes ACK from Slave
  i2cWrite(dat);	   // 6 . master issue data to be Written to Address Location
  i2cACK();			   // 7 . Master Takes ACK from Slave
  i2cstop();		   // 8 . Master issue STOP condition
  delay_ms(10);
}

//*				                I2C Data Read Steps  						    *

u8 i2cDevRead(u8 sa,u8 buffAddr)
{
  u8 buff;			   
  i2cstart();		   // 1 . Master issue START condition
  i2cWrite(sa&0xfe);   // 2 . Master Send Device Address(8 bites)  fe = 11111110
  i2cACK();			   // 3 . Master Takes ACK from Slave
  i2cWrite(buffAddr);  // 4 . Master Send Buffer/Resister Address(8 bites)
  i2cACK();			   // 5 . Master Takes ACK from Slave
  i2cRestart();		   // 6 . Master issue RESTART condition
  i2cWrite(sa|1);	   // 7 . Master issue Slave Address With Write Read Option.
  i2cACK();			   // 8 . Master Takes ACK from Slave
  buff=i2cRead();	   // 9 . Master Reads Data From Slave.
  i2cNoAck();		   // 10 . Master issue NACK 
  i2cstop();		   // 11 . Master issue STOP condition
  return buff;
}

void clock(void)
{ 
  u8 t;
  char day1[3]={0};
  lcd_cmd(0x81);
  //lcd_str("Time:");
  t=i2cDevRead(0xd0,0x02); // Resister Address 02 for Hour
  lcd_data((t/16)+48);
  lcd_data((t%16)+48);
  lcd_data(':');
	
  t=i2cDevRead(0xd0,0x01); // Resister Address 01 for Minites
  lcd_data((t/16)+48);
  lcd_data((t%16)+48);
  lcd_data(':');
 
  t=i2cDevRead(0xd0,0x00); // Resister Address 00 for Seconds
  lcd_data((t/16)+48);
  lcd_data((t%16)+48);

  lcd_cmd(0x8C);
  t=i2cDevRead(0xd0,0x03); // Resister Address 00 for Seconds
  sprintf(day1,"%s",day[t]);
  lcd_str(day1);
	
  lcd_cmd(0xc1);
  //lcd_str("Date:");
  t=i2cDevRead(0xd0,0x04); // Resister Address 04 for Date	  03 for Day
  lcd_data((t/16)+48);
  lcd_data((t%16)+48);
  lcd_data('/');
	
  t=i2cDevRead(0xd0,0x05); // Resister Address 05 for Month
  lcd_data((t/16)+48);
  lcd_data((t%16)+48);
  lcd_data('/');
 
  t=i2cDevRead(0xd0,0x06); // Resister Address 06 for Year
  lcd_str("20");
  lcd_data((t/16)+48);
  lcd_data((t%16)+48);
}


void main(void)
{
  lcd_init();
  lcd_cmd(0x01);
  lcd_cmd(0x80);
  lcd_str("    welcome    ");
  delay_ms(800);
  //lcd_cmd(0x01);
  //lcd_str("Setting Time");
  //i2cDevWrite(0xd0,0x02,0x10);//Hours
  //i2cDevWrite(0xd0,0x01,0x10);//Minute 
  //i2cDevWrite(0xd0,0x00,0x10);//Second
  //i2cDevWrite(0xd0,0x03,0x02);//Day
  //i2cDevWrite(0xd0,0x04,0x02);//Date
  //i2cDevWrite(0xd0,0x05,0x02);//Month 
  //i2cDevWrite(0xd0,0x06,0x22);//Year
  //lcd_cmd(0x01);
  //delay_ms(2000);
 while(1)
 { 
   clock();
   delay_ms(300);
 }
}