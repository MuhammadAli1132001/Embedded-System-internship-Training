#include <reg52.h>
#include <stdio.h>
#include <lcd.h>
#include <ds18b20.h>
 int b;
 
 void timer0()interrupt 1{
	 		if(currentTemp>30){
				lcd_cmd(0xC0);
			lcd_string("Alert Temp>30");
				lcd_cmd(0xC0);
			msdelay(200);
			lcd_string("            ");
			while(b<=200){
	  P1=~P1;
		delay(20);
		b++;
	  }
   	if(b>200){
		msdelay(250);
		b=0;
  	}}
		if(currentTemp<30){
			lcd_cmd(0xC0);
			lcd_string("               ");
 }
		TR0=0;
		}
void main(){
	EA=1;
	TMOD=0X01;
	TH0=0X00;
	TL0=0X00;
	TR0=1;
	lcd_init();
	while(1){
		display_temp();
}}
