/*
 * uart.c
 *
 * Created: 13/01/2020 20:04:17
 *  Author: SHADY
 */ 

/*
 * uart.c
 *
 * Created: 31/12/2019 01:18:41 ã
 *  Author: PC
 */ 
#include "uart.h"
#include "bit_handle.h"

volatile static void (*u_funPtr)(void);

void UART_Init(void)
{
	/* Normal speed */ 
	clearBit(UCSR0A,U2X0);
	
	/* set 8-bit data */
	setBit(UCSR0C,UCSZ00);
	setBit(UCSR0C,UCSZ01);
	
	/* for parity */
	#if(parity==EVEN)
	{
		clearBit(UCSR0C,UPM00);
		setBit(UCSR0C,UPM01);
	}
	#elif(parity==ODD)
	{
		setBit(UCSR0C,UPM00);
		setBit(UCSR0C,UPM01);
		
	}
	#elif(parity==NOPARITY)
	{
		clearBit(UCSR0C,UPM00);
		clearBit(UCSR0C,UPM01);
		
	}
	#endif
	
	
	/* for 9600 baud rate for frequency 8 MHz*/
	
	UBRR0H=0;
	UBRR0L=51;
	
	
	
	
	/* Enable of Tx or Rx */
	setBit(UCSR0B,RXEN0);
	setBit(UCSR0B,TXEN0);
		
	
}

void UART_SendData(const uint8 data)
{
	while(!(getBit(UCSR0A,UDRE)));
	UDR0=data;
}
uint8 UART_RecieveData(void)
{
	
	while(!(getBit(UCSR0A,RXC)));
	
	return UDR0;
}

uint8 UART_RecieveData_NoBlock(uint8* pdata)
{
	uint8 status=0;
	if(getBit(UCSR0A,RXC))
	{
		*pdata=UDR0;
		status=1;
	}
	else
	{
		status=0;
	}
	return status;
	
}
void uart_setCallback(void(*funPtr)(void))
{
	u_funPtr = funPtr;
}

ISR(USART0_RX_vect)
{
	g_uartDataReg=UART_RecieveByte();
	(*u_funPtr)();
	
}