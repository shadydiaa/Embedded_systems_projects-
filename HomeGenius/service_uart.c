/*
 * service_uart.c
 *
 * Created: 13/01/2020 19:56:31
 *  Author: SHADY
 */ 

#include "service_uart.h"

void UART_Receiver_Int_Enable(void)
{
	UCSR0B|=(1<<RXCIE);
}

uint8 UART_RecieveByte(void)
{

	return UDR0;
}

void UART_SendStr(uint8* str)
{
	uint8 i =0;
	while(str[i])
	{
		UART_SendData(str[i]);
		i++;
	}
}

void UART_RecieveStr(uint8* str)
{
	uint8 i=0;
	str[i]=UART_RecieveByte();
	
	while(str[i] != '#')
	{
		i++;
		str[i]=UART_RecieveData();
		
		
	}
	str[i]='\0';
}

void UART_SendProtocal(uint8* str)
{
	
	uint8 i=0,j;
	uint16 sum=0;
	while(str[i] !='\0')
	{
		sum+=str[i];
		i++;
	}
	UART_SendData(i);
	for(j=0;j<i; j++)
	{
		UART_SendData(str[j]) ;
	}
	UART_SendData(sum);

}

uint8 recieve_str(uint8* buff)
{
	uint8 counter=UART_RecieveData(),i;
	uint16 sum=0;
	for(i=0;i<counter; i++)
	{
		buff[i] =UART_RecieveData();
		sum+=buff[i];
	}
	uint16 recieved_sum = UART_RecieveData();

	if(sum==recieved_sum)
	{
		return 1 ;
	}
	else
	{
		return 0;
	}
}