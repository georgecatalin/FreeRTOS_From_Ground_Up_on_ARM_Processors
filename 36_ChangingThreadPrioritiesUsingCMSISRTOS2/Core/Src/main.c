/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"


/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

typedef uint32_t TaskProfiler;

TaskProfiler OrangeTaskProfiler, WhiteTaskProfiler, BlackTaskProfiler, RedTaskProfiler;
#define STACK_SIZE 128 // In CMSIS RTOS2 STACK SIZE IS MEASURED IN BYTES

osThreadId_t orange_id, white_id, black_id, red_id;

int __io_putchar(int ch);

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);

void orangeTask(void *pvParams);
void whiteTask(void *pvParams);
void blackTask(void *pvParams);
void redTask(void *pvParams);


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{


  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  /* Configure the system clock */
  SystemClock_Config();



  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();

  /* Init scheduler */
  osKernelInitialize();

  /* Create the thread(s) */

  //Create Threads
  osThreadAttr_t  orange_attributes = { .name="Orange Task", .priority=osPriorityNormal, .stack_size = STACK_SIZE};
  orange_id= osThreadNew(orangeTask, NULL, &orange_attributes);

  osThreadAttr_t white_attributes =  { .name="White Task", .priority=osPriorityNormal, .stack_size = STACK_SIZE};
  white_id=osThreadNew(whiteTask, NULL, &white_attributes);

  osThreadAttr_t black_attributes =  { .name="Black Task", .priority=osPriorityNormal, .stack_size = STACK_SIZE};
  black_id=osThreadNew(blackTask, NULL, &black_attributes);

  osThreadAttr_t red_attributes =  { .name="Red Task", .priority=osPriorityNormal, .stack_size = STACK_SIZE};
  red_id=osThreadNew(redTask, NULL, &red_attributes);


  /* Start scheduler */
  osKernelStart();


  while (1)
  {

  }

}


void orangeTask(void *pvParams)
{
	int i=0;

	while(1)
	{
		OrangeTaskProfiler++;
		for(i; i<100000; i++){}
	}
}
void whiteTask(void *pvParams)
{
	int i=0;

	while(1)
	{
		WhiteTaskProfiler++;
		for(i; i<100000; i++){}
		osThreadSetPriority(orange_id, osPriorityAboveNormal);
	}
}

void blackTask(void *pvParams)
{
	int i=0;

	while(1)
	{
		BlackTaskProfiler++;
		for(i; i<100000; i++){}
	}
}

void redTask(void *pvParams)
{
	int i=0;

	while(1)
	{
		RedTaskProfiler++;
		for(i; i<100000; i++){}
	}
}


int uart3_write(int ch)
{
	while(!(USART3->SR & USART_SR_TXE))
	{

	}

	USART3->DR = (ch & 0xFF); // 0xFF = 1111 1111 enforce content to 1 byte = 8 bits
	return ch;
}

int __io_putchar(int ch)
{
	uart3_write(ch);
	return ch;
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
