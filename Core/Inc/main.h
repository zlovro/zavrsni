/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define USR_TIM_ADC TIM3
#define DAC_MCLK_Pin GPIO_PIN_3
#define DAC_MCLK_GPIO_Port GPIOA
#define LCD_SCK_Pin GPIO_PIN_5
#define LCD_SCK_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_6
#define LCD_RST_GPIO_Port GPIOA
#define LCD_SDA_Pin GPIO_PIN_7
#define LCD_SDA_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_0
#define LCD_CS_GPIO_Port GPIOB
#define LCD_CD_Pin GPIO_PIN_1
#define LCD_CD_GPIO_Port GPIOB
#define LCD_VCC_Pin GPIO_PIN_2
#define LCD_VCC_GPIO_Port GPIOB
#define DAC_BCLK_Pin GPIO_PIN_10
#define DAC_BCLK_GPIO_Port GPIOB
#define DAC_LRCLK_Pin GPIO_PIN_12
#define DAC_LRCLK_GPIO_Port GPIOB
#define ROT_A_Pin GPIO_PIN_13
#define ROT_A_GPIO_Port GPIOB
#define ROT_A_EXTI_IRQn EXTI15_10_IRQn
#define ROT_B_Pin GPIO_PIN_14
#define ROT_B_GPIO_Port GPIOB
#define DAC_DAT_Pin GPIO_PIN_15
#define DAC_DAT_GPIO_Port GPIOB
#define ROT_SW_Pin GPIO_PIN_8
#define ROT_SW_GPIO_Port GPIOA
#define ROT_SW_EXTI_IRQn EXTI9_5_IRQn
#define PRESET_7_Pin GPIO_PIN_12
#define PRESET_7_GPIO_Port GPIOA
#define PRESET_7_EXTI_IRQn EXTI15_10_IRQn
#define PRESET_6_Pin GPIO_PIN_15
#define PRESET_6_GPIO_Port GPIOA
#define PRESET_6_EXTI_IRQn EXTI15_10_IRQn
#define PRESET_5_Pin GPIO_PIN_3
#define PRESET_5_GPIO_Port GPIOB
#define PRESET_5_EXTI_IRQn EXTI3_IRQn
#define PRESET_4_Pin GPIO_PIN_4
#define PRESET_4_GPIO_Port GPIOB
#define PRESET_4_EXTI_IRQn EXTI4_IRQn
#define PRESET_3_Pin GPIO_PIN_5
#define PRESET_3_GPIO_Port GPIOB
#define PRESET_3_EXTI_IRQn EXTI9_5_IRQn
#define PRESET_2_Pin GPIO_PIN_6
#define PRESET_2_GPIO_Port GPIOB
#define PRESET_2_EXTI_IRQn EXTI9_5_IRQn
#define PRESET_1_Pin GPIO_PIN_7
#define PRESET_1_GPIO_Port GPIOB
#define PRESET_1_EXTI_IRQn EXTI9_5_IRQn
#define PRESET_0_Pin GPIO_PIN_9
#define PRESET_0_GPIO_Port GPIOB
#define PRESET_0_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
