//
// Created by lovro on 18/11/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

#ifndef PCM3060_H
#define PCM3060_H

#include <stm32f4xx_hal.h>

#include "smallgpio.h"

extern sgpio *            gPcmGpioVcc;
extern sgpio *            gPcmGpioMs;
extern SPI_HandleTypeDef *gPcmSpi;
extern I2S_HandleTypeDef *gPcmI2sDac;
extern I2S_HandleTypeDef *gPcmI2sAdc;

void pcmInit(sgpio *pGpioRst, sgpio *pGpioMs, TIM_HandleTypeDef *pSckiTim, SPI_HandleTypeDef *pSpi, I2S_HandleTypeDef *pI2sAdc, I2S_HandleTypeDef *pI2sDac);

#endif //PCM3060_H
