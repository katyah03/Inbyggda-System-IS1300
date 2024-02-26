/* USER CODE BEGIN Header */

/**
******************************************************************************
@brief freertos, code for freertos applications
@file freertos.c
@author Katya Holmberg
@version 1.0
@date 15-December-2023
@brief Functions, logic and structures for program project
******************************************************************************
*/

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stdbool.h>
#include "states.h"
#include "leds.h"
#include "inputs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
	bool should_blink = 0;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for BlinkTask */
osThreadId_t BlinkTaskHandle;
const osThreadAttr_t BlinkTask_attributes = {
  .name = "BlinkTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task2 */
osThreadId_t Task2Handle;
const osThreadAttr_t Task2_attributes = {
  .name = "Task2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Mutex1 */
osMutexId_t Mutex1Handle;
const osMutexAttr_t Mutex1_attributes = {
  .name = "Mutex1"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Blue_Toggle(void *argument);
void Crossing_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of Mutex1 */
  Mutex1Handle = osMutexNew(&Mutex1_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of BlinkTask */
  BlinkTaskHandle = osThreadNew(Blue_Toggle, NULL, &BlinkTask_attributes);

  /* creation of Task2 */
  Task2Handle = osThreadNew(Crossing_Task, NULL, &Task2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Blue_Toggle */
/**
* @brief Function implementing the BlinkTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Blue_Toggle */

/**
@brief Blue_Toggle, turn the blue light on and off to toggle
@param none
@return void
*/
void Blue_Toggle(void *argument)
{
  /* USER CODE BEGIN Blue_Toggle */
	TickType_t xLastWakeTime;
	const TickType_t toggleFreq = pdMS_TO_TICKS(200);
	xLastWakeTime = xTaskGetTickCount();

  /* Infinite loop */
  for(;;)
  {
	  if(osMutexAcquire(Mutex1Handle, 10) == 0){
		  if(should_blink){
			  PL_Blue_Toggle();
		  } else {
			  Reset_PL_State(_PL_Blue);
		  }
		  Led_On(Get_State());
		  osMutexRelease(Mutex1Handle);
	  }
	  vTaskDelayUntil( &xLastWakeTime, toggleFreq );
  }
  /* USER CODE END Blue_Toggle */
}

/* USER CODE BEGIN Header_Crossing_Task */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Crossing_Task */
/**
@brief Crossing_Task, switch cases that implement the main logic of the project
@param none
@return void
*/
void Crossing_Task(void *argument)
{
  /* USER CODE BEGIN Crossing_Task */

	TickType_t orangeDelay = pdMS_TO_TICKS(3000);
	TickType_t walkingDelay = pdMS_TO_TICKS(4000);
	TickType_t plDelay = pdMS_TO_TICKS(3000);

  /* Infinite loop */
	enum State selectedState = Start;
  for(;;)
  {
	switch(selectedState){
		case Start:
			Set_PL_State(_PL_Red);
			Set_TL_North_State(_TL_Green);
			Set_TL_South_State(_TL_Green);
			Led_On(Get_State());
			osMutexAcquire(Mutex1Handle, 10);
			if(UserButton_2()){
				should_blink = 1;
				selectedState = TL_To_Red;
			}
			osMutexRelease(Mutex1Handle);
			break;
		case TL_To_Red:
			Reset_TL_North_State(_TL_Green);
			Reset_TL_South_State(_TL_Green);
			Set_TL_North_State(_TL_Orange);
			Set_TL_South_State(_TL_Orange);
			Led_On(Get_State());
			osDelay(orangeDelay);
			Reset_TL_North_State(_TL_Orange);
			Reset_TL_South_State(_TL_Orange);
			Set_TL_South_State(_TL_Red);
			Set_TL_North_State(_TL_Red);
			Led_On(Get_State());
			osDelay(plDelay);
			selectedState = PL_Green;
			break;
		case PL_Green:
			Reset_PL_State(_PL_Red);
			Set_PL_State(_PL_Green);
			should_blink = 0;
			Led_On(Get_State());
			osDelay(walkingDelay);
			selectedState = TL_To_Green;
			break;
		case TL_To_Green:
			Reset_PL_State(_PL_Green);
			Set_PL_State(_PL_Red);
			Reset_TL_North_State(_TL_Red);
			Reset_TL_South_State(_TL_Red);
			Set_TL_North_State(_TL_Orange);
			Set_TL_South_State(_TL_Orange);
			Led_On(Get_State());
			osDelay(orangeDelay);
			Reset_TL_North_State(_TL_Orange);
			Reset_TL_South_State(_TL_Orange);
			Set_TL_South_State(_TL_Green);
			Set_TL_North_State(_TL_Green);
			Led_On(Get_State());
			selectedState = Start;
		break;
	}
	osDelay(1);
  }
  /* USER CODE END Crossing_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

