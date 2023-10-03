/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SD_CD_Pin GPIO_PIN_0
#define SD_CD_GPIO_Port GPIOC
#define DISPLAY_D16_Pin GPIO_PIN_0
#define DISPLAY_D16_GPIO_Port GPIOA
#define DISPLAY_D17_Pin GPIO_PIN_1
#define DISPLAY_D17_GPIO_Port GPIOA
#define DISPLAY_D18_Pin GPIO_PIN_2
#define DISPLAY_D18_GPIO_Port GPIOA
#define DISPLAY_D19_Pin GPIO_PIN_3
#define DISPLAY_D19_GPIO_Port GPIOA
#define DISPLAY_D20_Pin GPIO_PIN_4
#define DISPLAY_D20_GPIO_Port GPIOA
#define DISPLAY_D21_Pin GPIO_PIN_5
#define DISPLAY_D21_GPIO_Port GPIOA
#define DISPLAY_D22_Pin GPIO_PIN_6
#define DISPLAY_D22_GPIO_Port GPIOA
#define DISPLAY_D23_Pin GPIO_PIN_7
#define DISPLAY_D23_GPIO_Port GPIOA
#define DISPLAY_D0_Pin GPIO_PIN_0
#define DISPLAY_D0_GPIO_Port GPIOB
#define DISPLAY_D1_Pin GPIO_PIN_1
#define DISPLAY_D1_GPIO_Port GPIOB
#define DISPLAY_D2_Pin GPIO_PIN_2
#define DISPLAY_D2_GPIO_Port GPIOB
#define DISPLAY_D10_Pin GPIO_PIN_10
#define DISPLAY_D10_GPIO_Port GPIOB
#define DISPLAY_D12_Pin GPIO_PIN_12
#define DISPLAY_D12_GPIO_Port GPIOB
#define DISPLAY_D13_Pin GPIO_PIN_13
#define DISPLAY_D13_GPIO_Port GPIOB
#define DISPLAY_D14_Pin GPIO_PIN_14
#define DISPLAY_D14_GPIO_Port GPIOB
#define DISPLAY_D15_Pin GPIO_PIN_15
#define DISPLAY_D15_GPIO_Port GPIOB
#define DISPLAY_RESET_Pin GPIO_PIN_6
#define DISPLAY_RESET_GPIO_Port GPIOC
#define DISPLAY_CSX_Pin GPIO_PIN_7
#define DISPLAY_CSX_GPIO_Port GPIOC
#define DISPLAY_DC_Pin GPIO_PIN_8
#define DISPLAY_DC_GPIO_Port GPIOA
#define DISPLAY_D11_Pin GPIO_PIN_11
#define DISPLAY_D11_GPIO_Port GPIOA
#define DISPLAY_RD_Pin GPIO_PIN_12
#define DISPLAY_RD_GPIO_Port GPIOA
#define DISPLAY_WR_Pin GPIO_PIN_15
#define DISPLAY_WR_GPIO_Port GPIOA
#define DISPLAY_D3_Pin GPIO_PIN_3
#define DISPLAY_D3_GPIO_Port GPIOB
#define DISPLAY_D4_Pin GPIO_PIN_4
#define DISPLAY_D4_GPIO_Port GPIOB
#define DISPLAY_D5_Pin GPIO_PIN_5
#define DISPLAY_D5_GPIO_Port GPIOB
#define DISPLAY_D6_Pin GPIO_PIN_6
#define DISPLAY_D6_GPIO_Port GPIOB
#define DISPLAY_D7_Pin GPIO_PIN_7
#define DISPLAY_D7_GPIO_Port GPIOB
#define DISPLAY_D8_Pin GPIO_PIN_8
#define DISPLAY_D8_GPIO_Port GPIOB
#define DISPLAY_D9_Pin GPIO_PIN_9
#define DISPLAY_D9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
