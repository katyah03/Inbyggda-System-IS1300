/**
******************************************************************************
@brief states, states functions for the traffic lights
@file states.c
@author Katya Holmberg
@version 1.0
@date 15-December-2023
@brief functions and structures for the states of the traffic lights
******************************************************************************
*/

#include "leds.h"
#include "inputs.h"
#include "states.h"
#include <stdio.h>



uint8_t data[3];

#define TL_South_SET(color) (data[1] |= color)
#define TL_North_SET(color) (data[0] |= color << 3)

#define PL_SET(color) (data[1] |= color << 3)

#define TL_South_RESET(color) (data[1] = (data[1] & ~(color)))
#define TL_North_RESET(color) (data[0] = (data[0] & ~(color << 3)))
#define PL_RESET(color) (data[1] = (data[1] & ~(color << 3)))

#define TL_South_GET(color) (data[1] & color)
#define TL_North_GET(color) (data[0] & color)

#define PL_GET(color) (data[1] & (color << 3))

/**
@brief Get_State, Function to get the current state
@param none
@return uint8_t
*/
uint8_t *Get_State(){
	return data;
}

/**
@brief Get_TL_North_State, Function to get the current state of TL_North
@param none
@return uint8_t
*/
uint8_t Get_TL_North_State(enum TL_Color color){
	return TL_North_SET(color);
}

/**
@brief Get_TL_South_State, Function to get the current state of TL_South
@param none
@return uint8_t
*/
uint8_t Get_TL_South_State(enum TL_Color color){
	return TL_South_GET(color);
}

/**
@brief Get_PL_State, Function to get the current state of PL
@param none
@return uint8_t
*/
uint8_t Get_PL_State(enum PL_Color color){
	return PL_GET(color);
}

/**
@brief Set_TL_North_State, Function to set the current state of TL_North
@param none
@return uint8_t
*/
void Set_TL_North_State(enum TL_Color color){
	TL_North_SET(color);
}

/**
@brief Set_TL_South_State, Function to set the current state of TL_South
@param none
@return uint8_t
*/
void Set_TL_South_State(enum TL_Color color){
	TL_South_SET(color);
}

/**
@brief Set_PL_State, Function to set the current state of PL
@param none
@return uint8_t
*/
void Set_PL_State(enum PL_Color color){
	PL_SET(color);
}

/**
@brief Reset_PL_State, Function to reset the current state of PL
@param none
@return uint8_t
*/
void Reset_PL_State(enum PL_Color color){
	PL_RESET(color);
}

/**
@brief Reset_TL_North_State, Function to reset the current state of TL_North
@param none
@return uint8_t
*/
void Reset_TL_North_State(enum PL_Color color){
	TL_North_RESET(color);
}

/**
@brief Reset_TL_South_State, Function to reset the current state of TL_South
@param none
@return uint8_t
*/
void Reset_TL_South_State(enum PL_Color color){
	TL_South_RESET(color);
}


/**
@brief PL_Blue_Toggle, Function to toggle the blue state of the Pedestrian Light
@param none
@return uint8_t
*/
void PL_Blue_Toggle(void){
	if(Get_PL_State(_PL_Blue)){
		Reset_PL_State(_PL_Blue);
		Led_On(Get_State());
	} else {
		Set_PL_State(_PL_Blue);
		Led_On(Get_State());
	}
}



