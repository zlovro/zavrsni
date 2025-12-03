//
// Created by lovro on 03/12/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

#ifndef SOUND_IO_H
#define SOUND_IO_H

#include <stm32f4xx_hal.h>
#include <stdint.h>

#define BUFFER_FULL_SIZE_SAMPLES 256
#define BUFFER_HALF_SIZE_SAMPLES (BUFFER_FULL_SIZE_SAMPLES / 2)

extern int32_t gDacFrontBuf[BUFFER_HALF_SIZE_SAMPLES];
extern int32_t gDacBackBuf[BUFFER_HALF_SIZE_SAMPLES];
extern int16_t gAdcBackBuf[BUFFER_FULL_SIZE_SAMPLES];
extern int16_t gAdcFrontBuf[BUFFER_HALF_SIZE_SAMPLES];

extern I2S_HandleTypeDef* gSoundIoI2s;

void soundIoInit(I2S_HandleTypeDef* pI2s);
void soundIoApplyEffects();

#endif //SOUND_IO_H
