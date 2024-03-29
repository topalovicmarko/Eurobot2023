/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
bool promenljiva1;
bool promenljiva2;
bool promenljiva3;
bool promenljiva4;
bool promenljiva5;

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	gpio_init();
	sick_init();
	tajmer_init();
	uart_init();
	step_init();
	maxxoni_init();
	odometrija_init();
	pid_init();
	enkoder_init();
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */
	/* USER CODE END 2 */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	//motor1_smer(true);
	//motor2_smer(true);
	while (1) {

		// okretanje_m1(15);
		// okretanje_m2(15);
		//if (promenljiva1 == true)
		// {
		//	  okretanje_m1(0);
		//	  okretanje_m2(0);
		// }

		/*
		 zatvaranje_zadnjh_vrata();
		 loptice_pocetni_polozaj();
		 tajmer_delay(1000);
		 otvaranje_zadnjh_vrata();
		 prva_loptica();
		 tajmer_delay(1000);
		 zatvaranje_zadnjh_vrata();
		 druga_loptica();
		 tajmer_delay(1000);
		 zatvaranje_zadnjh_vrata();
		 treca_loptica();
		 tajmer_delay(1000);
		 */
		/*
		 zatvaranje_zadnjh_vrata();
		 loptice_pocetni_polozaj();
		 tajmer_delay(1000);
		 otvaranje_zadnjh_vrata();
		 tajmer_delay(1000);
		 prva_loptica();
		 tajmer_delay(1000);
		 otvaranje_zadnjh_vrata();
		 druga_loptica();
		 otvaranje_zadnjh_vrata();
		 tajmer_delay(1000);
		 treca_loptica();
		 tajmer_delay(1000);


		 servo_control(6, 200);
		 prednja_desna_vrata_hvatanje();
		 prednja_leva_vrata_hvatanje();
		 tajmer_delay(2000);
		 prednja_desna_vrata_otvorena();
		 prednja_leva_vrata_otvorena();
		 servo_control(6, 240);
		 tajmer_delay(2000);

		 steper_suprotan_ugao();
		 tajmer_delay(2000);
		 steper_pun_ugao();
		 tajmer_delay(2000);
		 */
		//SIKOVE
		promenljiva1 = sickLB();
		promenljiva2 = sickLF();
		promenljiva3 = sickRB();
		promenljiva4 = sickRF();
		promenljiva5 = sickMID();

		//STEPPER
		/*
		 steper_suprotan_ugao();
		 tajmer_delay(2000);
		 steper_pun_ugao();
		 tajmer_delay(2000);
		 */
		//CINC
		/*
		 bool pomocna = cinc_stanje();
		 if (pomocna == true)
		 {
		 gpio_led_stanje(true);
		 }
		 else
		 {
		 gpio_led_stanje(false);
		 }
		 */

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 84;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
