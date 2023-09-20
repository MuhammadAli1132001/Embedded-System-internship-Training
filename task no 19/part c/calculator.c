#include <reg51.h>
#include "lcd.h"


void disp_num(float num);
int get_num(char ch);

char scan_key(void);
unsigned char s[30]={"ENTER 1 NO= "};
unsigned char s1[30]={"ENTER 2 NO= "};
unsigned char s2[30]={"OPERATOR = "};
unsigned char s3[30]={"Result = "};

//sfr ldata = 0xA0;
sbit rs = P2^6;
sbit rw = P2^5;
sbit en = P2^7;

sbit r0=P1^0;
sbit r1=P1^1;
sbit r2=P1^2;
sbit r3=P1^3;
sbit c0=P1^4;
sbit c1=P1^5;
sbit c2=P1^6;
sbit c3=P1^7;


int getAndDisplayKeysForCalculator()
  {
		
   while(1){
   unsigned int k=0,m=0,n=0,r=0;
	 int k2,k1;
	 char key,key1;
	 unsigned char ch2;
		 
			lcd_init();
			
			while(s[k]!='\0')
			{
			lcd_write_data(s[k]);
			k++;
			}
			key=scan_key();
			k2=get_num(key);
			lcd_write_data(key);
			lcd_clear();
			
			while(s2[n]!='\0')
			{
			lcd_write_data(s2[n]);
			n++;
			}
			ch2=scan_key();
			lcd_write_data(ch2);
			lcd_clear();
			
			while(s1[m]!='\0')
			{
			lcd_write_data(s1[m]);
			m++;
			}
			key1=scan_key();
			k1=get_num(key1);
			lcd_write_data(key1);
			lcd_clear();
			
			while(s3[r]!='\0')
			{
			lcd_write_data(s3[r]);
			r++;
			}
			
			switch(ch2)
			{
				case '+':
				disp_num(k1+k2);
				break;
				case '-':
				disp_num(k2-k1);
				break;
				case '*':
				disp_num(k2*k1);
				break;
				case '/':
				disp_num(k2/k1);
				break;
		 }
			return 0;
		}
	}


char scan_key() {
    char keyPressed = '\0';

    while (!(keyPressed == '0' || keyPressed == '1' || keyPressed == '2' || keyPressed == '3' ||
             keyPressed == '4' || keyPressed == '5' || keyPressed == '6' || keyPressed == '7' ||
             keyPressed == '8' || keyPressed == '9' || keyPressed == '+' || keyPressed == '-' ||
             keyPressed == '=' || keyPressed == 'C' || keyPressed == '*' || keyPressed == '/')) {

        r0 = 0; r1 = 1; r2 = 1; r3 = 1;
        if (c0 == 0 && r0 == 0) { keyPressed = '+'; }
        if (c1 == 0 && r0 == 0) { keyPressed = '-'; }
        if (c2 == 0 && r0 == 0) { keyPressed = '*'; }
        if (c3 == 0 && r0 == 0) { keyPressed = '/'; }

        r0 = 1; r1 = 0; r2 = 1; r3 = 1;
        if (c0 == 0 && r1 == 0) { keyPressed = '='; }
        if (c1 == 0 && r1 == 0) { keyPressed = '3'; }
        if (c2 == 0 && r1 == 0) { keyPressed = '6'; }
        if (c3 == 0 && r1 == 0) { keyPressed = '9'; }

        r0 = 1; r1 = 1; r2 = 0; r3 = 1;
        if (c0 == 0 && r2 == 0) { keyPressed = '0'; }
        if (c1 == 0 && r2 == 0) { keyPressed = '2'; }
        if (c2 == 0 && r2 == 0) { keyPressed = '5'; }
        if (c3 == 0 && r2 == 0) { keyPressed = '8'; }

        r0 = 1; r1 = 1; r2 = 1; r3 = 0;
        if (c0 == 0 && r3 == 0) { keyPressed = 'C'; }
        if (c1 == 0 && r3 == 0) { keyPressed = '1'; }
        if (c2 == 0 && r3 == 0) { keyPressed = '4'; }
        if (c3 == 0 && r3 == 0) { keyPressed = '7'; }
    }

    // Display the key on the LCD if needed
    lcd_write_data(keyPressed);
    delay_ms(1000);

    return keyPressed;
}


int get_num(char ch)         //convert char into int
{
switch(ch)
{
case '0': return 0; break;
case '1': return 1; break;
case '2': return 2; break;
case '3': return 3; break;
case '4': return 4; break;
case '5': return 5; break;
case '6': return 6; break;
case '7': return 7; break;
case '8': return 8; break;
case '9': return 9; break;
}
return 0;
}

void disp_num(float num)            //displays number on LCD
{
unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
unsigned char TenthDigit = 0;  //It will contain 10th position digit of numb
unsigned char decimal = 0;
int j;
int numb;
j=(int)(num*10);
numb=(int)num;
	
	if(numb<0)
		{
		numb = -1*numb;  // Make number positive
		lcd_write_data('-');	// Display a negative sign on LCD
		}

	TenthDigit = (numb/10);	         // Findout Tenth Digit

	if( TenthDigit != 0)	         // If it is zero, then don't display
		lcd_write_data(TenthDigit+0x30);	 // Make Char of TenthDigit and then display it on LCD

		UnitDigit = numb - TenthDigit*10;

		lcd_write_data(UnitDigit+0x30);	 // Make Char of UnitDigit and then display it on LCD
		lcd_write_data('.');
		decimal=(j%10)+0x30;
		lcd_write_data(decimal);
	delay_ms(20000);
}