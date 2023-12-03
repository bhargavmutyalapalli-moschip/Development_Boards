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
#include "../HAL/Inc/EEPROM.h"

int main(void)
{

	//Test Case 1
	uint8_t ch1[7] = {1,2,3,4,5,6,7};
	uint8_t ch2[7] = {0};

	HAL_EEPROM_Init();
	HAL_EEPROM_WriteNbytes(0xAF, ch1 ,7);
	HAL_EEPROM_ReadNbytes(0xAF, ch2 ,7);

	//Test Case 2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;

	HAL_EEPROM_WriteNbytes(0xFFF, ch1 ,4);
	HAL_EEPROM_ReadNbytes(0xFFF, ch2 ,4);

	//Test Case 3
	ch1[0] = 0xAB;
	
	HAL_EEPROM_WriteNbytes(0x1234, ch1 ,1);
	HAL_EEPROM_ReadNbytes(0x1234, ch2 ,1);
	
    while (1)
    {
    }

}