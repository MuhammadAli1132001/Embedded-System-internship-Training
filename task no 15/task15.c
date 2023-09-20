#include <reg51.h>

void delay(unsigned int t);
void UART_Init();
void UART_Receive(); 

void UART_senddata(unsigned char dataa);
void UART_sendstring( char *str);


void main()
{
    UART_Init();      // Initialize UART

    while(1)
    {
			UART_sendstring("Salam\r\n");   //send msg cursor to the new position 
			delay(1000);
       // UART_Receive();               // Receivedata from UART
    }
}



void delay(unsigned int t){
	unsigned int i,j;
	
	for(i = 0; i<t; i++){
		for(j = 0; j<127; j++);
	}
}
void UART_Init()
{
    TMOD = 0x20;    // Timer 1 mode 2: 8-bit auto-reload
    TH1 = 0xFD;     // Set baud rate to 9600 bps for 11.0592 MHz crystal
    SCON = 0x50;    // 8-bit data, 1 stop bit, REN = 1
    TR1 = 1;        // Start timer
}

void UART_senddata(unsigned char dataa)
{
	    //receivedData = SBUF;   // Store receiveddata
	  SBUF = dataa;
    while (TI == 0);        // Wait until reception is complete
    TI = 0;                // Clear reception flag
}

void UART_sendstring( char *str)
{
	int i = 0;
    while (str[i] != '\0'){     // Wait until reception is complete
		UART_senddata(str[i]);
	  i++;
		}
}

//void UART_Receive()
//{
//    while (RI == 0);        // Wait until reception is complete
//    receivedData = SBUF;   // Store receiveddata
//    RI = 0;                // Clear reception flag
//}
