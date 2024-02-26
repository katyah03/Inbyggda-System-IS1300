/**
******************************************************************************
@brief test, test functions for the traffic crossing
@file test.c
@author Katya Holmberg
@version 1.0
@date 4-December-2023
@brief tests for the functions of the traffic crossing
******************************************************************************
*/

#include "spi.h"
#include "gpio.h"
#include "leds.h"
#include "main.h"
#include "inputs.h"
#include "states.h"
#include "freertos.h"

#include <stdio.h>
#include <stdbool.h>


/**
@brief Test_Led_on, test for the different lights to turn on
@param none
@return void
*/
void Test_Led_on(void){
	uint8_t data[3];
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++){
			data[i % 3] <<= 1;
			data[i % 3] |= 1;
			Led_On(data);
			HAL_Delay(500);
		}
	}
	data[1] |= 0x18;
	data[2] |= 0x18;
	Led_On(data);

	for(int i = 1; i < 3; i++){
		data[i] |= 0x20;
		Led_On(data);
		HAL_Delay(500);
	}
}

/**
@brief Test_UserButtons, test for the two buttons on the shield
@param none
@return void
*/
void Test_UserButtons(void){
	uint8_t data[3];
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	Led_On(data);
	while(1){
		if(UserButton_1()){
			data[2] = 0x20;
		} else {
			data[2] = 0;
		}
		if(UserButton_2()){
			data[1] = 0x20;
		} else {
			data[1] = 0;
		}
		Led_On(data);
	}
}

/**
@brief Test_TL_State_Get, test for the get state function on the north and south traffic light
@param none
@return void
*/
void Test_TL_State_Get(void){
	Set_TL_North_State(_TL_Green);
	Set_TL_North_State(_TL_Red);
	Set_TL_North_State(_TL_Orange);
	Set_TL_South_State(_TL_Green);
	Set_TL_South_State(_TL_Red);
	Set_TL_South_State(_TL_Orange);

	if(Get_TL_North_State(_TL_Green) && Get_TL_North_State(_TL_Red) && Get_TL_North_State(_TL_Orange)){
		Led_On(Get_State());
	}

	if(Get_TL_South_State(_TL_Green) && Get_TL_South_State(_TL_Red) && Get_TL_South_State(_TL_Orange)){
			Led_On(Get_State());
	}
}


/**
@brief Test_PL_State_Get, test for the get state function on the pedestrian traffic light
@param none
@return void
*/
void Test_PL_State_Get(void){
	Led_Reset();
	Set_PL_State(_PL_Green);
	Set_PL_State(_PL_Red);
	Set_PL_State(_PL_Blue);

	if(Get_PL_State(_PL_Green) && Get_PL_State(_PL_Red)){
		Led_On(Get_State());
	}
}

/**
@brief Test_TL_State_Set, test for the set state function on the cars traffic lights
@param none
@return void
*/
void Test_TL_State_Set(void){
	Set_TL_North_State(_TL_Green);
	Set_TL_North_State(_TL_Red);
	Set_TL_North_State(_TL_Orange);
	Set_TL_South_State(_TL_Green);
	Set_TL_South_State(_TL_Red);
	Set_TL_South_State(_TL_Orange);


	Led_On(Get_State());
}

/**
@brief Test_PL_State_Set, test for the set state function on the pedestrian traffic light
@param none
@return void
*/
void Test_PL_State_Set(void){
	Set_PL_State(_PL_Green);
	Set_PL_State(_PL_Red);
	Set_PL_State(_PL_Blue);

	Led_On(Get_State());
}

/**
@brief Test_PL_State_Reset, test for the reset state function on the pedestrian traffic light
@param none
@return void
*/
void Test_PL_Reset(void){
	Set_PL_State(_PL_Green);
	Set_PL_State(_PL_Red);
	Set_PL_State(_PL_Blue);

	Reset_PL_State(_PL_Green);
	Led_On(Get_State());
}

/**
@brief Test_TL_State_Reset, test for the reset state function on the car traffic lights
@param none
@return void
*/
void Test_TL_Reset(void){
	Set_TL_North_State(_TL_Green);
	Set_TL_North_State(_TL_Red);
	Set_TL_North_State(_TL_Orange);
	Set_TL_South_State(_TL_Green);
	Set_TL_South_State(_TL_Red);
	Set_TL_South_State(_TL_Orange);
	Led_On(Get_State());

	Reset_TL_North_State(_TL_Green);
	Reset_TL_North_State(_TL_Red);
	Reset_TL_North_State(_TL_Orange);
	Reset_TL_South_State(_TL_Green);
	Reset_TL_South_State(_TL_Red);
	Reset_TL_South_State(_TL_Orange);
}

/**
@brief Run_All_Tests, function that calls on the different test functions
@param none
@return void
*/
void Run_All_Tests(){
	Test_Led_on();
	Test_UserButtons();
	Test_TL_State_Get();
	Test_PL_State_Get();
	Test_TL_State_Set();
	Test_PL_State_Set();
	Test_TL_State_Reset();
	Test_PL_State_Reset();
}

