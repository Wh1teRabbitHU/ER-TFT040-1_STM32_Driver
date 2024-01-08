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

#include "fatfs.h"
#include "libjpeg.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "er_tft040.h"
#include "font_6_12.h"
#include "jpeg_view.h"
#include "stdio.h"
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
SD_HandleTypeDef hsd;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SDIO_SD_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void ER_TFT040_textTest() {
    ER_TFT040_textProps text1 = {.font = fontData,
                                 .text = "Welcome to the 4 inch TFT LCD module!",
                                 .posX = 30,
                                 .posY = 5,
                                 .fontSize = 1,
                                 .fontColor = 0xFF0000,
                                 .backgroundColor = 0xFFFFFF};

    ER_TFT040_textProps text2 = {.font = fontData,
                                 .text = "Font size 1",
                                 .posX = 10,
                                 .posY = 20,
                                 .fontSize = 1,
                                 .fontColor = 0xFFFFFF,
                                 .backgroundColor = 0xFF00FF};
    ER_TFT040_textProps text3 = {.font = fontData,
                                 .text = "Font size 2",
                                 .posX = 20,
                                 .posY = 32,
                                 .fontSize = 2,
                                 .fontColor = 0xFFFFFF,
                                 .backgroundColor = 0x0000FF};
    ER_TFT040_textProps text4 = {.font = fontData,
                                 .text = "Font size 3",
                                 .posX = 30,
                                 .posY = 56,
                                 .fontSize = 3,
                                 .fontColor = 0xFFFFFF,
                                 .backgroundColor = 0x00FF00};
    ER_TFT040_textProps text5 = {.font = fontData,
                                 .text = "Font size 4",
                                 .posX = 40,
                                 .posY = 92,
                                 .fontSize = 4,
                                 .fontColor = 0xFFFFFF,
                                 .backgroundColor = 0xFF0000};

    ER_TFT040_drawText(&text1);
    ER_TFT040_drawText(&text2);
    ER_TFT040_drawText(&text3);
    ER_TFT040_drawText(&text4);
    ER_TFT040_drawText(&text5);
}

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

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_SDIO_SD_Init();
    MX_USART1_UART_Init();
    MX_LIBJPEG_Init();
    MX_FATFS_Init();
    /* USER CODE BEGIN 2 */

    ER_TFT040_init();
    ER_TFT040_clearLCD(0x000000);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    char textBuffer[16];
    uint16_t counter = 0;
    sprintf(textBuffer, " Counter: %u", counter);

    ER_TFT040_textProps counterText = {.font = fontData,
                                       .text = textBuffer,
                                       .posX = 10,
                                       .posY = 200,
                                       .fontSize = 2,
                                       .fontColor = 0xFF0000,
                                       .backgroundColor = 0xFFFFFF};

    while (1) {
        jpeg_display("/", "IMG01.jpg", 0, 0);
        HAL_Delay(2000);
        jpeg_display("/", "IMG03.jpg", 0, 0);
        HAL_Delay(2000);
        jpeg_display("/", "IMG04.jpg", 0, 0);
        HAL_Delay(2000);
        jpeg_display("/", "IMG05.jpg", 0, 0);
        HAL_Delay(2000);
        jpeg_display("/", "IMG06.jpg", 0, 0);
        HAL_Delay(2000);
        jpeg_display("/", "IMG07.jpg", 0, 0);
        HAL_Delay(2000);
        jpeg_display("/", "IMG08.jpg", 0, 0);
        HAL_Delay(2000);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 90;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    RCC_OscInitStruct.PLL.PLLR = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief SDIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_SDIO_SD_Init(void) {
    /* USER CODE BEGIN SDIO_Init 0 */

    /* USER CODE END SDIO_Init 0 */

    /* USER CODE BEGIN SDIO_Init 1 */

    /* USER CODE END SDIO_Init 1 */
    hsd.Instance = SDIO;
    hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
    hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd.Init.ClockDiv = 1;
    /* USER CODE BEGIN SDIO_Init 2 */

    /* USER CODE END SDIO_Init 2 */
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {
    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA,
                      DISPLAY_D16_Pin | DISPLAY_D17_Pin | DISPLAY_D18_Pin | DISPLAY_D19_Pin | DISPLAY_D20_Pin |
                          DISPLAY_D21_Pin | DISPLAY_D22_Pin | DISPLAY_D23_Pin | DISPLAY_DC_Pin | DISPLAY_D11_Pin |
                          DISPLAY_RD_Pin | DISPLAY_WR_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB,
                      DISPLAY_D0_Pin | DISPLAY_D1_Pin | DISPLAY_D2_Pin | DISPLAY_D10_Pin | DISPLAY_D12_Pin |
                          DISPLAY_D13_Pin | DISPLAY_D14_Pin | DISPLAY_D15_Pin | DISPLAY_D3_Pin | DISPLAY_D4_Pin |
                          DISPLAY_D5_Pin | DISPLAY_D6_Pin | DISPLAY_D7_Pin | DISPLAY_D8_Pin | DISPLAY_D9_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, DISPLAY_RESET_Pin | DISPLAY_CSX_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : SD_CD_Pin */
    GPIO_InitStruct.Pin = SD_CD_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SD_CD_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : DISPLAY_D16_Pin DISPLAY_D17_Pin DISPLAY_D18_Pin DISPLAY_D19_Pin
                             DISPLAY_D20_Pin DISPLAY_D21_Pin DISPLAY_D22_Pin DISPLAY_D23_Pin
                             DISPLAY_DC_Pin DISPLAY_D11_Pin DISPLAY_RD_Pin DISPLAY_WR_Pin */
    GPIO_InitStruct.Pin = DISPLAY_D16_Pin | DISPLAY_D17_Pin | DISPLAY_D18_Pin | DISPLAY_D19_Pin | DISPLAY_D20_Pin |
                          DISPLAY_D21_Pin | DISPLAY_D22_Pin | DISPLAY_D23_Pin | DISPLAY_DC_Pin | DISPLAY_D11_Pin |
                          DISPLAY_RD_Pin | DISPLAY_WR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : DISPLAY_D0_Pin DISPLAY_D1_Pin DISPLAY_D2_Pin DISPLAY_D10_Pin
                             DISPLAY_D12_Pin DISPLAY_D13_Pin DISPLAY_D14_Pin DISPLAY_D15_Pin
                             DISPLAY_D3_Pin DISPLAY_D4_Pin DISPLAY_D5_Pin DISPLAY_D6_Pin
                             DISPLAY_D7_Pin DISPLAY_D8_Pin DISPLAY_D9_Pin */
    GPIO_InitStruct.Pin = DISPLAY_D0_Pin | DISPLAY_D1_Pin | DISPLAY_D2_Pin | DISPLAY_D10_Pin | DISPLAY_D12_Pin |
                          DISPLAY_D13_Pin | DISPLAY_D14_Pin | DISPLAY_D15_Pin | DISPLAY_D3_Pin | DISPLAY_D4_Pin |
                          DISPLAY_D5_Pin | DISPLAY_D6_Pin | DISPLAY_D7_Pin | DISPLAY_D8_Pin | DISPLAY_D9_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : DISPLAY_RESET_Pin DISPLAY_CSX_Pin */
    GPIO_InitStruct.Pin = DISPLAY_RESET_Pin | DISPLAY_CSX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
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
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
