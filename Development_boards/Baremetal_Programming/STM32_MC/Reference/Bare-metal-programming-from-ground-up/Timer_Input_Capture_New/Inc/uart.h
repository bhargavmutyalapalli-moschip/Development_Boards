/*
 * uart.h
 *
 *  Created on: 16 Mar 2023
 *  Author: George Calin
 * 	Code for: Nucleo 144 family
 */

#ifndef UART_H_
#define UART_H_

#include <stm32f429xx.h>
#include <stdint.h>

void uart3_tx_init(void);

void uart3_write(int charYouWantToWrite);
int __io_putchar(int myCharacter);
char uart3_rx_read(void);
void uart3_rxtx_init(void);

#endif /* UART_H_ */
