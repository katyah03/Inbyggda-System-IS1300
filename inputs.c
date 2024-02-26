/**
******************************************************************************
@brief inputs, input functions for the traffic crossing
@file inputs.c
@author Katya Holmberg
@version 1.0
@date 5-December-2023
@brief functions for the inputs of the traffic crossing
******************************************************************************
*/

#include "main.h"
#include "gpio.h"
#include "spi.h"
#include <stdbool.h>

/**
@brief UserButton_1, Checks the state of User Button 1
@param none
@return true if User Button 1 is pressed, false otherwise
*/
bool UserButton_1(void){
	return !HAL_GPIO_ReadPin(PL1_Switch_GPIO_Port, PL1_Switch_Pin);
}

/**
@brief UserButton_2, Checks the state of User Button 2
@param none
@return true if User Button 2 is pressed, false otherwise
*/
bool UserButton_2(void){
	return !HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin);
}

/**
@brief Get_Userbutton_State,  Returns the combined state of both user buttons
@param none
@return true if either User Button 1 or User Button 2 is pressed, false otherwise
*/
bool Get_Userbutton_State(void){
	return HAL_GPIO_ReadPin(PL1_Switch_GPIO_Port, PL1_Switch_Pin);
}
