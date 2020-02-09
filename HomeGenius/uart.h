/*
 * uart.h
 *
 * Created: 13/01/2020 20:05:57
 *  Author: SHADY
 */ 


#ifndef UART_H_
#define UART_H_

#include "avr/io.h"
#include "std_Types.h"
#include "avr/interrupt.h"

/* for choose parity */
#define EVEN     0
#define ODD      1
#define NOPARITY 2

/*choose your parity */

#define parity EVEN


void UART_Init(void);
void UART_SendData(const uint8 data);
uint8 UART_RecieveData(void);
uint8 UART_RecieveData_NoBlock(uint8* pdata);


volatile uint8 g_uartDataReg ;




#endif /* UART_H_ */