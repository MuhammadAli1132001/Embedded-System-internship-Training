#include <reg51.h>
#include "LCDh.h"
#include <stdio.h>
#include <intrins.h>

sbit DS1302_CE = P3^5; // DS1302 chip enable pin
sbit DS1302_CLK = P3^6; // DS1302 clock pin
sbit DS1302_IO = P3^4; // DS1302 data I/O pin

// DS1302 commands
#define DS1302_READ_BURST 0xBF
#define DS1302_WRITE_BURST 0xBE
#define DS1302_SECONDS 0x80
#define DS1302_SECONDS_read 0x81
#define DS1302_MINUTES 0x82
#define DS1302_MINUTES_read 0x83
#define DS1302_HOURS   0x84
#define DS1302_HOURS_read  0x85
#define DS1302_DATE    0x86
#define DS1302_MONTH   0x88
#define DS1302_DAY     0x8A
#define DS1302_YEAR    0x8C
#define DS1302_CONTROL 0x8E
#define DS1302_CHARGER 0x90
#define DS1302_RAMBURST_READ 0xFF
#define DS1302_RAMBURST_WRITE 0xFE
#define CLK_DELAY 10



void Write_Byte(unsigned int Value);
unsigned char Read_Byte(unsigned char cmd);
void DS1302_SetTime(unsigned char hour,  unsigned char minute, unsigned char second);
void DS1302_SetDate(unsigned char day,  unsigned char month,  unsigned char year);
void DS1302_GetTime(void);
void DS1302_GetDate(void);
void Send_Bit(unsigned int bitt);
void DS1302_init();
void DS1302_ReadByte();

    unsigned char hour, minute, second;
    unsigned char day, month, year;
		unsigned char timeString[9];
    int datestring[12]; 
    unsigned char decimalSecond;	
	  unsigned char decimalMinute;
    unsigned char decimalHour;
    unsigned int read_bytes[12];

void main()
{

	  lcd_init();         // Initialize the LCD
	  DS1302_init();        // Initialize ds1302
	
	   // Set initial time and date
     DS1302_SetTime(0x23, 0x59, 0x50); 
     DS1302_SetDate(0x30, 0x09, 0x23); 

    while (1)
    {	  
				DS1302_CE = 1;
			  DS1302_ReadByte();
				DS1302_CE = 0;

        DS1302_GetTime();
			  DS1302_GetDate();

    }
}

void SCLK_Pulse()
{
    DS1302_CLK = 1;
    DS1302_CLK = 0;
}

void Send_Bit(unsigned int bitt)// Function to send a bit to the DS1302
{
		if(bitt != 0)
			{
		
			DS1302_IO = 1;
		}
		else
			{
			DS1302_IO = 0;
		}
}


void write_byte(unsigned int byte)
{
    unsigned int i,Bit;
    
    for (i = 0; i < 8; i++)
    {
        Bit = byte & (1 << i); // Get each bit
        Send_Bit(Bit);         // Send the bit
        SCLK_Pulse();        // Generate clock pulse
    }
}

unsigned char read_byte(unsigned char cmd)
{
	  unsigned int j,dat = 0;
	  write_byte(cmd);

     for (j = 0; j < 8; j++)
      {
        dat >>= 1;
        if (DS1302_IO)
        {
            dat |= 0x80;     // Set the corresponding bit in R
        }
        else
        {
            dat &= 0x7F;    // Clear the corresponding bit in R
        }

        SCLK_Pulse();       // Generate clock pulse
			}
    return dat;
}
			

// Function to write a byte to the DS1302unsigned char cmd,
void DS1302_WriteByte(unsigned char cmd, unsigned char Value)
{
   
	  DS1302_CE = 1;
    write_byte(cmd);
	  write_byte(Value);
    DS1302_CE = 0;
}


// Function to read a byte from the DS1302
void DS1302_ReadByte()
{
    unsigned int dat=0, j,i;
	
    DS1302_CE = 1;
	  write_byte(DS1302_READ_BURST);

	for( i = 0; i<8; i++){
		
		dat = 0;
		
    for (j = 0; j < 8; j++)          // Receive the data byte
    {
        dat >>= 1;
        if (DS1302_IO)
        {
            dat |= 0x80;     // Set the corresponding bit in R
        }
        else
        {
            dat &= 0x7F;    // Clear the corresponding bit in R
        }

        SCLK_Pulse();       // Generate clock pulse
    }
		
		read_bytes[i] = dat;
		
	}
    DS1302_CE = 0;

}

void DS1302_init()
{
	unsigned char r;
	
	    DS1302_CE = 0;
	    DS1302_CLK = 0;
			DS1302_WriteByte(DS1302_CONTROL,0x00);
	    DS1302_WriteByte(DS1302_CHARGER,0xAB);
	
	r = read_byte(DS1302_SECONDS_read);
	
	if ((r & DS1302_SECONDS_read) != 0)
	DS1302_WriteByte(DS1302_SECONDS,0);
			
}
void DS1302_SetTime(unsigned char hour, unsigned char minute, unsigned char second)
{

	  DS1302_WriteByte(DS1302_SECONDS,second);
    DS1302_WriteByte(DS1302_MINUTES,minute);
    DS1302_WriteByte(DS1302_HOURS,hour);
 
}

void LCD_display(unsigned char Number)
{
	lcd_write_data(((Number>>4)&0x0F) + 0x30);
	lcd_write_data((Number&0x0F) + 0x30);
}

void DS1302_GetTime(void)
{
	
	      lcd_set_cursor(0, 0);
	      lcd_write_string("Time:");
	
        lcd_set_cursor(0, 6);
		    LCD_display(read_bytes[2]);	
      	lcd_write_data(':');
	      delay_ms(10);
	
        lcd_set_cursor(0, 9);
		    LCD_display(read_bytes[1]);
		    lcd_write_data(':');
      	delay_ms(10);

	      lcd_set_cursor(0, 12);
	      LCD_display(read_bytes[0]);
  		  delay_ms(10);	
}

// Function to set the date in DS1302
void DS1302_SetDate(unsigned char day, unsigned char month, unsigned char year)
{
	
    DS1302_WriteByte(DS1302_DATE,day);
    DS1302_WriteByte(DS1302_MONTH,month);
    DS1302_WriteByte(DS1302_YEAR,year);
}


 //Function to read the date from DS1302
void DS1302_GetDate()
{
        lcd_set_cursor(1, 0);
	      lcd_write_string("Date:");
	
        lcd_set_cursor(1, 6);
		    LCD_display(read_bytes[3]);	
      	lcd_write_data(':');
	      delay_ms(10);
	
        lcd_set_cursor(1, 9);
		    LCD_display(read_bytes[4]);
		    lcd_write_data(':');
      	delay_ms(10);

	      lcd_set_cursor(1, 12);
		    LCD_display(read_bytes[6]);
		    delay_ms(10);
}



// /***************************************************************************/ 
//#ifndef _REAL_TIMER_DS1302_2003_7_21_ 
//#define _REAL_TIMER_DS1302_2003_7_21_ 
// 
//#define  DS1302_CLK  P1_7              //ÊµÊ±Ê±ÖÓÊ±ÖÓÏßÒý½Å  
//#define  DS1302_IO  P1_6              //ÊµÊ±Ê±ÖÓÊý¾ÝÏßÒý½Å  
//#define  DS1302_RST  P1_5              //ÊµÊ±Ê±ÖÓ¸´Î»ÏßÒý½Å 
//sbit  ACC0  = ACC^0 ;
//sbit  ACC7  = ACC^7  ;
// 
//typedef struct __SYSTEMTIME__ 
//{ 
//unsigned char Second; 
//unsigned char Minute; 
//unsigned char Hour; 
//unsigned char Week; 
//unsigned char Day; 
//unsigned char Month; 
//unsigned char  Year; 
//unsigned char DateString[9]; 
//unsigned char TimeString[9]; 
//}SYSTEMTIME; //¶¨ÒåµÄÊ±¼äÀàÐÍ 
// 
//#define AM(X) X 
//#define PM(X) (X+12)               // ×ª³É24Ð¡Ê±ÖÆ 
//#define DS1302_SECOND 0x80  
//#define DS1302_SECOND_READ 0x81 
//#define DS1302_MINUTE 0x82
//#define DS1302_MINUTE_READ 0x83 
//#define DS1302_HOUR 0x84
//#define DS1302_HOUR_READ 0x85  
//#define DS1302_WEEK 0x8A
//#define DS1302_WEEK_READ 0x8B
//#define DS1302_DAY 0x86 
//#define DS1302_DAY_READ 0x87 
//#define DS1302_MONTH 0x88 
//#define DS1302_MONTH_READ 0x89 
//#define DS1302_YEAR 0x8C 
//#define DS1302_YEAR_READ    0x8D 
//#define DS1302_RAM(X) (0xC0+(X)*2)    //ÓÃÓÚ¼ÆËã DS1302_RAM µØÖ·µÄºê
// 
// 
//void DS1302InputByte(unsigned char d)  //ÊµÊ±Ê±ÖÓÐ´ÈëÒ»×Ö½Ú(ÄÚ²¿º¯Êý) 
//{  
//    unsigned char i; 
//    ACC = d; 
//    for(i=8; i>0; i–) 
//    { 
//        DS1302_IO = ACC0;            //Ïàµ±ÓÚ»ã±àÖÐµÄ RRC 
//        DS1302_CLK = 1; 
//        DS1302_CLK = 0; 
//        ACC = ACC >> 1;  
//    }  
//} 
// 
//unsigned char DS1302OutputByte(void)  //ÊµÊ±Ê±ÖÓ¶ÁÈ¡Ò»×Ö½Ú(ÄÚ²¿º¯Êý) 
//{  
//    unsigned char i; 
//    for(i=8; i>0; i–) 
//    { 
//        ACC = ACC >>1;          //Ïàµ±ÓÚ»ã±àÖÐµÄ RRC  
//        ACC7 = DS1302_IO; 
//        DS1302_CLK = 1; 
//        DS1302_CLK = 0; 
//    }  
//    return(ACC);  
//} 
// 
//void Write1302(unsigned char ucAddr, unsigned char ucDa) //ucAddr: DS1302µØÖ·, ucData: ÒªÐ´µÄÊý¾Ý 
//{   
//    DS1302_CLK = 0; 
//    DS1302_RST = 1; 
//    DS1302InputByte(ucAddr);        // µØÖ·£¬ÃüÁî  
//    DS1302InputByte(ucDa);        // Ð´1ByteÊý¾Ý  
//    DS1302_CLK = 1; 
//    DS1302_RST = 0;   
//}  
// 
//unsigned char Read1302(unsigned char ucAddr) //¶ÁÈ¡DS1302Ä³µØÖ·µÄÊý¾Ý 
//{ 
//    unsigned char ucData;  
//    DS1302_CLK = 0; 
//    DS1302_RST = 1; 
//    DS1302InputByte(ucAddr);        // µØÖ·£¬ÃüÁî  
//    ucData = DS1302OutputByte();         // ¶Á1ByteÊý¾Ý 
//    DS1302_CLK = 1; 
//    DS1302_RST = 0; 
//    return(ucData); 
//} 
// 
//void DS1302_SetProtect(bit flag)        //ÊÇ·ñÐ´±£»¤ 
//{ 
//if(flag) 
//Write1302(0x8E,0x80); 
//else 
//Write1302(0x8E,0x00); 
//} 
// 
//void DS1302_SetTime(unsigned char Address, unsigned char Value)        // ÉèÖÃÊ±¼äº¯Êý 
//{ 
//DS1302_SetProtect(0);  
//Write1302(Address, ((Value/10)<<4 | (Value%10)));
//DS1302_SetProtect(1); 
//} 
// 
//void DS1302_GetTime(SYSTEMTIME *Time) 
//{ 
//unsigned char ReadValue; 
//ReadValue = Read1302(DS1302_SECOND_READ); 
//Time->Second = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 
//ReadValue = Read1302(DS1302_MINUTE_READ); 
//Time->Minute = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 
//ReadValue = Read1302(DS1302_HOUR_READ); 
//Time->Hour = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 
//ReadValue = Read1302(DS1302_DAY_READ); 
//Time->Day = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 
//ReadValue = Read1302(DS1302_WEEK_READ); 
//Time->Week = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 
//ReadValue = Read1302(DS1302_MONTH_READ); 
//Time->Month = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 
//ReadValue = Read1302(DS1302_YEAR_READ); 
//Time->Year = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 
//} 
// 
//void DateToStr(SYSTEMTIME *Time) 
//{ 
//Time->DateString[0] = Time->Year/10 + '0'; 
//Time->DateString[1] = Time->Year%10 + '0'; 
//Time->DateString[2] = '-'; 
//Time->DateString[3] = Time->Month/10 + '0'; 
//Time->DateString[4] = Time->Month%10 + '0'; 
//Time->DateString[5] = '-'; 
//Time->DateString[6] = Time->Day/10 + '0'; 
//Time->DateString[7] = Time->Day%10 + '0'; 
//Time->DateString[8] = ''; 
//} 
// 
//void TimeToStr(SYSTEMTIME *Time) 
//{ 
//Time->TimeString[0] = Time->Hour/10 + '0'; 
//Time->TimeString[1] = Time->Hour%10 + '0'; 
//Time->TimeString[2] = ':'; 
//Time->TimeString[3] = Time->Minute/10 + '0'; 
//Time->TimeString[4] = Time->Minute%10 + '0'; 
//Time->TimeString[5] = ':'; 
//Time->TimeString[6] = Time->Second/10 + '0'; 
//Time->TimeString[7] = Time->Second%10 + '0'; 
//Time->DateString[8] = ''; 
//} 
// 
///*  
//void Initial_DS1302(void) 
//{ 
//unsigned char Second=Read1302(DS1302_SECOND); 
//if(Second&0x80)    
//DS1302_SetTime(DS1302_SECOND,0); 
//} 
// 
//void BurstWrite1302(unsigned char *pWClock) //ÍùDS1302Ð´ÈëÊ±ÖÓÊý¾Ý(¶à×Ö½Ú·½Ê½) 
//{ 
//    unsigned char i; 
//    Write1302(0x8e,0x00);          // ¿ØÖÆÃüÁî,WP=0,Ð´²Ù×÷? 
//    DS1302_RST = 0; 
//    DS1302_CLK = 0; 
//    DS1302_RST = 1; 
//    DS1302InputByte(0xbe);         // 0xbe:Ê±ÖÓ¶à×Ö½ÚÐ´ÃüÁî 
//    for (i = 8; i>0; i–)      //8Byte = 7Byte Ê±ÖÓÊý¾Ý + 1Byte ¿ØÖÆ 
//    { 
//        DS1302InputByte(*pWClock);  // Ð´1ByteÊý¾Ý 
//        pWClock++; 
//    } 
//    DS1302_CLK = 1; 
//    DS1302_RST = 0; 
//}*/
///******************************************************************************** 
//void BurstRead1302(unsigned char *pRClock) //¶ÁÈ¡DS1302Ê±ÖÓÊý¾Ý(Ê±ÖÓ¶à×Ö½Ú·½Ê½) 
//{ 
//    unsigned char i; 
//    DS1302_RST = 0; 
//    DS1302_CLK = 0; 
//    DS1302_RST = 1; 
//    DS1302InputByte(0xbf);              // 0xbf:Ê±ÖÓ¶à×Ö½Ú¶ÁÃüÁî  
//    for (i=8; i>0; i–)  
//    { 
//       *pRClock = DS1302OutputByte();   // ¶Á1ByteÊý¾Ý  
//       pRClock++; 
//    } 
//    DS1302_CLK = 1; 
//    DS1302_RST = 0; 
//} 
// 
//*/
// 
//void DS1302_TimeStop(bit flag)           // ÊÇ·ñ½«Ê±ÖÓÍ£Ö¹ 
//{ 
//unsigned char Data; 
//Data=Read1302(DS1302_SECOND_READ); 
//DS1302_SetProtect(0); 
//if(flag) 
//Write1302(DS1302_SECOND, Data|0x80); 
//else 
//Write1302(DS1302_SECOND, Data&0x7F); 
//DS1302_SetProtect(1);
//} 
// 
//#endif
// 
 
