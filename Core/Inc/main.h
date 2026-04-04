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

#include <impl/smallgpio.h>

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
#define USR_TIM_SCLK &htim4
#define USR_TIM_FS &htim2
#define USR_TIM_MCLK &htim3
#define USR_CODEC_DBG 1
#define USR_TIM_DBG_LED &htim11
#define USR_TIM_DBG_LED_RAW TIM11
#define CODEC_MCLK_Pin GPIO_PIN_3
#define CODEC_MCLK_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_4
#define LCD_RST_GPIO_Port GPIOA
#define LCD_CLK_Pin GPIO_PIN_5
#define LCD_CLK_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOA
#define LCD_DAT_Pin GPIO_PIN_7
#define LCD_DAT_GPIO_Port GPIOA
#define CODEC_LRCK_Pin GPIO_PIN_12
#define CODEC_LRCK_GPIO_Port GPIOB
#define CODEC_SCLK_Pin GPIO_PIN_13
#define CODEC_SCLK_GPIO_Port GPIOB
#define CODEC_OUT_Pin GPIO_PIN_14
#define CODEC_OUT_GPIO_Port GPIOB
#define CODEC_IN_Pin GPIO_PIN_15
#define CODEC_IN_GPIO_Port GPIOB
#define CODEC_RST_Pin GPIO_PIN_8
#define CODEC_RST_GPIO_Port GPIOA
#define BTN_BNKM_Pin GPIO_PIN_4
#define BTN_BNKM_GPIO_Port GPIOB
#define BTN_BNKP_Pin GPIO_PIN_5
#define BTN_BNKP_GPIO_Port GPIOB
#define BTN_VOLM_Pin GPIO_PIN_6
#define BTN_VOLM_GPIO_Port GPIOB
#define BTN_VOLP_Pin GPIO_PIN_7
#define BTN_VOLP_GPIO_Port GPIOB
#define BTN_PREM_Pin GPIO_PIN_8
#define BTN_PREM_GPIO_Port GPIOB
#define BTN_PREP_Pin GPIO_PIN_9
#define BTN_PREP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

extern sgpio SGPIO_CODEC_RST;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
