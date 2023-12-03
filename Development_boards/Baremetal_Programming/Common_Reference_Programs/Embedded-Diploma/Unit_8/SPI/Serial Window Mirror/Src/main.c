/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "../Services/Platform_Types.h"
#include "../Services/stm32f103c6.h"
#include "../MCAL/Inc/GPIO.h"
#include "../MCAL/Inc/EXTI.h"
#include "../MCAL/Inc/USART.h"
#include "../MCAL/Inc/SPI.h"
#include "../HAL/Inc/LCD.h"
#include "../HAL/Inc/keypad.h"
#include "../HAL/Inc/SevenSegment.h"

					/* @Config */
/*Choose the desired operation in SPI of you current MCU
 * OPTIONS:
 * --------
 * 1) MCU_Act_As_Master
 * 2) MCU_Act_As_Slave
*/
#define MCU_Act_As_Slave

uint16_t character;
UART_Config_t uart1;
SPI_Config_t  spi1;
GPIO_PinConfig_t nss1;
GPIO_PinConfig_t led = {GPIOB,GPIO_PIN_0,GPIO_MODE_OUTPUT_PP,GPIO_OUTPUT_SPEED_10MHZ};

void SPI1_IRQ_CallBack(void)
{
#ifdef MCU_Act_As_Slave
	//Receive UART - Send UART

	//Receive SPI in MCU2 from SPI in MCU1
	MCAL_SPI_TX_RX(&spi1, &character, UART_Polling_Disable);
	if(character == 'm')
		MCAL_GPIO_TogglePin(&led);
	MCAL_UART_Transmit(&uart1, &character, UART_Polling_Enable);

#endif
}

void UART1_IRQ_CallBack(void)
{

#ifdef MCU_Act_As_Master

	//Receive UART - Send UART for Terminal in MCU1
	MCAL_UART_Receive(&uart1, &character, UART_Polling_Disable);
	MCAL_UART_Transmit(&uart1, &character, UART_Polling_Enable);

	//Send SPI - Receive SPI
	MCAL_GPIO_WritePin(&nss1, GPIO_PIN_CLEAR);
	MCAL_SPI_TX_RX(&spi1, &character, UART_Polling_Enable);
	MCAL_GPIO_WritePin(&nss1, GPIO_PIN_SET);

#endif

}

int main(void)
{

	uart1.USARTx 			= USART1;
	uart1.USART_BaudRate 	= USART_BAUDRATE_115200;
	uart1.USART_WordLength 	= USART_WORD_LENGTH_8;
	uart1.USART_Parity 		= USART_PARITY_DISABLE;
	uart1.USART_StopBits 	= USART_STOP_BIT_1;
	uart1.USART_FlowControl = USART_FLOW_CONTROL_DISABLE;

#ifdef MCU_Act_As_Master
	uart1.USART_Mode 		= USART_MODE_TX_RX;
	uart1.USART_IRQ_EN 		= USART_IE_RXNE;
	uart1.IRQ_CallBackPtr 	= UART1_IRQ_CallBack;
#endif

#ifdef MCU_Act_As_Slave
	uart1.USART_Mode 		= USART_MODE_TX;
	uart1.USART_IRQ_EN 		= USART_IE_DISABLE;
	uart1.IRQ_CallBackPtr 	= NULL_PTR;
#endif

	MCAL_UART_Init(&uart1);
	MCAL_UART_GPIO_SetPins(&uart1);

	//Common Configuration for master & slave
	spi1.SPIx = SPI1;
	spi1.SPI_ClkPhase = SPI_2ND_EDGE_CAPTURE_STROBE;
	spi1.SPI_ClkPolarity = SPI_CLOCK_IDLE_HIGH;
	spi1.SPI_DataSize = SPI_DATA_SIZE_8;
	spi1.SPI_FrameFormat = SPI_FRAME_FORMAT_MSB;
	spi1.SPI_PreScaler = SPI_PRESCALER_DIVISOR_8;


#ifdef MCU_Act_As_Master
	spi1.SPI_CommMode = SPI_FULL_DUPLEX;
	spi1.SPI_Mode = SPI_MODE_MASTER;
	spi1.SPI_SlaveSelect = SPI_SS_SOFTWARE_SET;
	spi1.SPI_IRQ_EN = SPI_IE_DISABLE;
	spi1.IRQ_CallBackPtr = NULL_PTR;

	nss1.GPIO_Port = GPIOA;
	nss1.GPIO_PinNo = GPIO_PIN_4;
	nss1.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	nss1.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(&nss1);
	MCAL_GPIO_WritePin(&nss1, GPIO_PIN_SET);
#endif

#ifdef MCU_Act_As_Slave
	spi1.SPI_CommMode = SPI_FULL_DUPLEX;
	spi1.SPI_Mode = SPI_MODE_SLAVE;
	spi1.SPI_SlaveSelect = SPI_SS_HARDWARE_SLAVE;
	spi1.SPI_IRQ_EN = SPI_IE_RXNE;
	spi1.IRQ_CallBackPtr = SPI1_IRQ_CallBack;
	MCAL_GPIO_Init(&led);
#endif

	MCAL_SPI_Init(&spi1);
	MCAL_SPI_GPIO_SetPins(&spi1);


    while (1)
    {
    }

}
