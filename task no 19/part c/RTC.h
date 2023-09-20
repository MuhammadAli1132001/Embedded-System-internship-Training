#ifndef RTC_H
#define RTC_H


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

void Write_Byte(unsigned char cmd, unsigned int Value);
unsigned char Read_Byte(unsigned char cmd);
void DS1302_SetTime(unsigned int hour, unsigned int minute, unsigned int second);
void DS1302_SetDate(unsigned char day, unsigned char month, unsigned char year);
void DS1302_GetTime(unsigned char *hour, unsigned char *minute, unsigned char *second);
void DS1302_GetDate(unsigned char *day, unsigned char *month, unsigned char *year);
void Send_Bit(unsigned int bitt);
void DS1302_init();

void  processRealTimeClock();
#endif /* DS1302_H */
