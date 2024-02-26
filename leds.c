/**
******************************************************************************
@brief leds, functions for the traffic lights LED's
@file leds.c
@author Katya Holmberg
@version 1.0
@date 10-December-2023
@brief functions for controlling the LED's in the traffic lights
******************************************************************************
*/
#include <stdint.h>

#include "gpio.h"
#include "spi.h"
#include "leds.h"
#include "states.h"


/**
@brief Led_On, Turns on LED's based on the data using SPI communication
@param uint8_t* data, A pointer to the data specifying whichs LED's to turn on
@return void
*/
void Led_On(uint8_t* data){
	HAL_SPI_Transmit(&hspi3, data, 3, 100);
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_RESET);
}

/**
@brief Led_Reset, Resets all LED's to their default state
@param void
@return void
*/
void Led_Reset(void){S
	HAL_GPIO_WritePin(Reset_GPIO_Port, Reset_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_GPIO_Port, STCP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Reset_GPIO_Port, Reset_Pin, GPIO_PIN_SET);
}









