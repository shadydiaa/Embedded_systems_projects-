/*
 * service_uart.h
 *
 * Created: 13/01/2020 20:01:22
 *  Author: SHADY
 */ 


#ifndef SERVICE_UART_H_
#define SERVICE_UART_H_

#include "avr/io.h"
#include "std_Types.h"
#include "uart.h"
#include "avr/interrupt.h"

void UART_SendStr(uint8* str);
void UART_RecieveStr(uint8* str);
void UART_SendProtocal(uint8* str);
uint8 recieve_str(uint8* buff);

uint8 UART_RecieveByte(void);
void UART_Receiver_Int_Enable(void);





#endif /* SERVICE_UART_H_ */