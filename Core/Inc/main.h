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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TIM2_usage "PCM SCKI"
#define PCM_RST_Pin GPIO_PIN_3
#define PCM_RST_GPIO_Port GPIOA
#define I2S_OUT_LR_Pin GPIO_PIN_4
#define I2S_OUT_LR_GPIO_Port GPIOA
#define LCD_SCK_Pin GPIO_PIN_5
#define LCD_SCK_GPIO_Port GPIOA
#define LCD_SDA_Pin GPIO_PIN_7
#define LCD_SDA_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_0
#define LCD_CS_GPIO_Port GPIOB
#define LCD_CD_Pin GPIO_PIN_1
#define LCD_CD_GPIO_Port GPIOB
#define LCD_VCC_Pin GPIO_PIN_2
#define LCD_VCC_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_10
#define LCD_RST_GPIO_Port GPIOB
#define I2S_IN_LR_Pin GPIO_PIN_12
#define I2S_IN_LR_GPIO_Port GPIOB
#define I2S_IN_BCK_Pin GPIO_PIN_13
#define I2S_IN_BCK_GPIO_Port GPIOB
#define I2S_IN_DAT_Pin GPIO_PIN_15
#define I2S_IN_DAT_GPIO_Port GPIOB
#define PCM_SCKI_Pin GPIO_PIN_15
#define PCM_SCKI_GPIO_Port GPIOA
#define I2S_OUT_BCK_Pin GPIO_PIN_3
#define I2S_OUT_BCK_GPIO_Port GPIOB
#define I2S_OUT_DAT_Pin GPIO_PIN_5
#define I2S_OUT_DAT_GPIO_Port GPIOB
#define PCM_SCL_Pin GPIO_PIN_6
#define PCM_SCL_GPIO_Port GPIOB
#define PCM_SDA_Pin GPIO_PIN_7
#define PCM_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
