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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "er_tft040.h"
#include "font_6_12.h"
#include "stdio.h"
// #include "test_pic.h"
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
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
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
                                 .fontColor = CONVERT_24BIT_COLOR(0xFF0000),
                                 .backgroundColor = CONVERT_24BIT_COLOR(0xFFFFFF)};

    ER_TFT040_textProps text2 = {.font = fontData,
                                 .text = "Font size 1",
                                 .posX = 10,
                                 .posY = 20,
                                 .fontSize = 1,
                                 .fontColor = CONVERT_24BIT_COLOR(0xFFFFFF),
                                 .backgroundColor = CONVERT_24BIT_COLOR(0xFF00FF)};
    ER_TFT040_textProps text3 = {.font = fontData,
                                 .text = "Font size 2",
                                 .posX = 20,
                                 .posY = 32,
                                 .fontSize = 2,
                                 .fontColor = CONVERT_24BIT_COLOR(0xFFFFFF),
                                 .backgroundColor = CONVERT_24BIT_COLOR(0x0000FF)};
    ER_TFT040_textProps text4 = {.font = fontData,
                                 .text = "Font size 3",
                                 .posX = 30,
                                 .posY = 56,
                                 .fontSize = 3,
                                 .fontColor = CONVERT_24BIT_COLOR(0xFFFFFF),
                                 .backgroundColor = CONVERT_24BIT_COLOR(0x00FF00)};
    ER_TFT040_textProps text5 = {.font = fontData,
                                 .text = "Font size 4",
                                 .posX = 40,
                                 .posY = 92,
                                 .fontSize = 4,
                                 .fontColor = CONVERT_24BIT_COLOR(0xFFFFFF),
                                 .backgroundColor = CONVERT_24BIT_COLOR(0xFF0000)};

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
    MX_I2C2_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    ER_TFT040_init();

    ER_TFT040_clearLCD(CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_clearLCD(CONVERT_24BIT_COLOR(0x00FF00));
    ER_TFT040_clearLCD(CONVERT_24BIT_COLOR(0x0000FF));
    ER_TFT040_clearLCD(CONVERT_24BIT_COLOR(0x222222));

    ER_TFT040_drawPixel(239, 400, CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_drawPixel(240, 400, CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_drawPixel(241, 400, CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_drawPixel(240, 399, CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_drawPixel(240, 401, CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_drawLine(10, 400, 200, 700, CONVERT_24BIT_COLOR(0x00FF00));
    ER_TFT040_fillRectangle(320, 620, 160, 180, CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_drawRectangle(300, 600, 160, 180, CONVERT_24BIT_COLOR(0x0000FF));
    ER_TFT040_drawCircle(240, 400, 166, CONVERT_24BIT_COLOR(0xFF0000));
    ER_TFT040_fillCircle(240, 400, 64, CONVERT_24BIT_COLOR(0x00FF00));
    ER_TFT040_textTest();

    // ER_TFT040_drawPicture(200, 120, 200, 120, PIC);

    char textBuffer[16];
    uint16_t counter = 0;
    sprintf(textBuffer, " Counter: %u", counter);

    ER_TFT040_textProps counterText = {.font = fontData,
                                       .text = textBuffer,
                                       .posX = 10,
                                       .posY = 200,
                                       .fontSize = 2,
                                       .fontColor = CONVERT_24BIT_COLOR(0xFF0000),
                                       .backgroundColor = CONVERT_24BIT_COLOR(0xFFFFFF)};

    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

        sprintf(textBuffer, " Counter: %u", counter++);
        counterText.text = textBuffer;

        ER_TFT040_drawText(&counterText);

        HAL_Delay(100);
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
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void) {
    /* USER CODE BEGIN I2C2_Init 0 */

    /* USER CODE END I2C2_Init 0 */

    /* USER CODE BEGIN I2C2_Init 1 */

    /* USER CODE END I2C2_Init 1 */
    hi2c2.Instance = I2C2;
    hi2c2.Init.Timing = 0x20303E5D;
    hi2c2.Init.OwnAddress1 = 0;
    hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c2.Init.OwnAddress2 = 0;
    hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c2) != HAL_OK) {
        Error_Handler();
    }

    /** Configure Analogue filter
     */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK) {
        Error_Handler();
    }

    /** Configure Digital filter
     */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C2_Init 2 */

    /* USER CODE END I2C2_Init 2 */
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
    huart1.Init.BaudRate = 38400;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
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
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB,
                      DATA_0_Pin | DATA_1_Pin | DATA_2_Pin | DATA_10_Pin | DATA_11_Pin | DATA_12_Pin | DATA_13_Pin |
                          DATA_14_Pin | DATA_15_Pin | DATA_3_Pin | DATA_4_Pin | DATA_5_Pin | DATA_6_Pin | DATA_7_Pin |
                          DATA_8_Pin | DATA_9_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, DISPLAY_RESET_Pin | DISPLAY_CSX_Pin | DISPLAY_DC_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, DISPLAY_WR_Pin | DISPLAY_RD_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : DATA_0_Pin DATA_1_Pin DATA_2_Pin DATA_10_Pin
                             DATA_11_Pin DATA_12_Pin DATA_13_Pin DATA_14_Pin
                             DATA_15_Pin DATA_3_Pin DATA_4_Pin DATA_5_Pin
                             DATA_6_Pin DATA_7_Pin DATA_8_Pin DATA_9_Pin */
    GPIO_InitStruct.Pin = DATA_0_Pin | DATA_1_Pin | DATA_2_Pin | DATA_10_Pin | DATA_11_Pin | DATA_12_Pin | DATA_13_Pin |
                          DATA_14_Pin | DATA_15_Pin | DATA_3_Pin | DATA_4_Pin | DATA_5_Pin | DATA_6_Pin | DATA_7_Pin |
                          DATA_8_Pin | DATA_9_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : DISPLAY_RESET_Pin DISPLAY_CSX_Pin DISPLAY_DC_Pin */
    GPIO_InitStruct.Pin = DISPLAY_RESET_Pin | DISPLAY_CSX_Pin | DISPLAY_DC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : DISPLAY_WR_Pin DISPLAY_RD_Pin */
    GPIO_InitStruct.Pin = DISPLAY_WR_Pin | DISPLAY_RD_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
