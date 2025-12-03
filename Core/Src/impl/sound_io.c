//
// Created by lovro on 03/12/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

#include "sound_io.h"

#include <string.h>

int32_t gDacFrontBuf[BUFFER_HALF_SIZE_SAMPLES] = {};
int32_t gDacBackBuf[BUFFER_HALF_SIZE_SAMPLES]  = {};
int16_t gAdcBackBuf[BUFFER_FULL_SIZE_SAMPLES]  = {};
int16_t gAdcFrontBuf[BUFFER_HALF_SIZE_SAMPLES] = {};

I2S_HandleTypeDef *gSoundIoI2s;

void soundIoInit(I2S_HandleTypeDef *pI2s)
{
    gSoundIoI2s = pI2s;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    // send DAC data
    HAL_I2S_Transmit_DMA(gSoundIoI2s, gDacFrontBuf, BUFFER_HALF_SIZE_SAMPLES);

    // copy second half of buffer data to front
    memcpy(gAdcFrontBuf, gAdcBackBuf + BUFFER_HALF_SIZE_SAMPLES, sizeof(int16_t) * BUFFER_HALF_SIZE_SAMPLES);

    soundIoApplyEffects();
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    // send DAC data
    HAL_I2S_Transmit_DMA(gSoundIoI2s, gDacFrontBuf, BUFFER_HALF_SIZE_SAMPLES);

    // copy first half of buffer data to front
    memcpy(gAdcFrontBuf, gAdcBackBuf, sizeof(int16_t) * BUFFER_HALF_SIZE_SAMPLES);

    soundIoApplyEffects();
}

void soundIoApplyEffects()
{
    for (int i = 0; i < BUFFER_HALF_SIZE_SAMPLES; ++i)
    {
        gDacBackBuf[i] = gAdcFrontBuf[i] << 12;
    }

    memcpy(gDacFrontBuf, gDacBackBuf, sizeof(uint32_t) * BUFFER_HALF_SIZE_SAMPLES);
}
