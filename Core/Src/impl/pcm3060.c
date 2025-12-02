//
// Created by lovro on 18/11/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

// ReSharper disable CppRedundantParentheses
#include "pcm3060.h"

#include <stdio.h>

#include "main.h"

sgpio *            gPcmGpioVcc = NULL;
sgpio *            gPcmGpioMs  = NULL;
I2C_HandleTypeDef *gPcmI2c     = NULL;
I2S_HandleTypeDef *gPcmI2sDac  = NULL;
I2S_HandleTypeDef *gPcmI2sAdc  = NULL;

void    pcmWriteRegister(uint8_t pReg, uint8_t pValue);
uint8_t pcmReadRegister(uint8_t pReg);

#define PCM3060_I2C_ADDRESS ((0b01000110 | 0) << 1)

typedef enum : uint8_t
{
    PCM_IF_MODE_SLAVE        = 0b000,
    PCM_IF_MODE_MASTER_768FS = 0b001,
    PCM_IF_MODE_MASTER_512FS = 0b010,
    PCM_IF_MODE_MASTER_384FS = 0b011,
    PCM_IF_MODE_MASTER_256FS = 0b100,
} pcmInterfaceMode;

enum : uint8_t
{
    PCM_DEFAULT_REGISTER_VALUE_64 = 0b11110000,
    PCM_DEFAULT_REGISTER_VALUE_67 = 0b00000000,
    PCM_DEFAULT_REGISTER_VALUE_72 = 0b00000000,
};

void pcmWriteRegister(uint8_t pReg, uint8_t pValue)
{
    uint8_t           data[2] = {pReg, pValue};

    while (true) if (gPcmI2c->State == HAL_I2C_STATE_READY) break;
    HAL_StatusTypeDef ret     = HAL_I2C_Master_Transmit(gPcmI2c, PCM3060_I2C_ADDRESS, data, 2, 1000);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }
}

uint8_t pcmReadRegister(uint8_t pReg)
{
    while (true) if (gPcmI2c->State == HAL_I2C_STATE_READY) break;
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(gPcmI2c, PCM3060_I2C_ADDRESS, &pReg, 1, 1000);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }

    uint8_t val;

    while (true) if (gPcmI2c->State == HAL_I2C_STATE_READY) break;
    ret = HAL_I2C_Master_Receive(gPcmI2c, PCM3060_I2C_ADDRESS, &val, 1, 1000);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }

    return val;
}

/**
 *
 * @param pForDac set interface mode for DAC if this is true, else for ADC
 * @param pMode
 */
void pcmSetInterfaceMode(const bool pForDac, const pcmInterfaceMode pMode)
{
    const uint8_t regIdx = pForDac ? 67 : 72;
    uint8_t       val    = pcmReadRegister(regIdx);

    // set M/S of DAC/ADC
    val = (val & 0b10001111) | pMode << 4;
    pcmWriteRegister(regIdx, val);
}

typedef enum : uint8_t
{
    PCM_IF_FMT_24B_I2S             = 0b00,
    PCM_IF_FMT_24B_LEFT_JUSTIFIED  = 0b01,
    PCM_IF_FMT_24B_RIGHT_JUSTIFIED = 0b10,
    PCM_IF_FMT_16B_RIGHT_JUSTIFIED = 0b11,
} pcmInterfaceFormat;

/**
 *
 * @param pForDac set interface format for DAC if this is true, else for ADC
 * @param pFmt
 */
void pcmSetInterfaceFormat(const bool pForDac, const pcmInterfaceFormat pFmt)
{
    const uint8_t regIdx = pForDac ? 67 : 72;
    uint8_t       regVal = pcmReadRegister(regIdx);

    // set FMT of DAC/ADC
    regVal = (regVal & ~0b11) | pFmt;
    pcmWriteRegister(regIdx, regVal);
}

/**
 *
 * @param pGpioRst
 * @param pSckiTim
 * @param pI2c
 * @param pI2sAdc
 * @param pI2sDac
 */
void pcmInit(sgpio *pGpioRst, TIM_HandleTypeDef *pSckiTim, I2C_HandleTypeDef *pI2c, I2S_HandleTypeDef *pI2sAdc, I2S_HandleTypeDef *pI2sDac)
{
    sgpioLow(pGpioRst);
    HAL_Delay(50);

    sgpioHigh(pGpioRst);
    HAL_Delay(50);

    while (true)
    {
        if (HAL_I2C_IsDeviceReady(pI2c, PCM3060_I2C_ADDRESS, 10, 500))
        {
            break;
        }
    }

    gPcmI2c    = pI2c;
    gPcmI2sAdc = pI2sAdc;
    gPcmI2sDac = pI2sDac;

    sgpioLow(pGpioRst);
    HAL_Delay(50);

    for (int r = 64; r <= 73; r++)
    {
        uint8_t val = pcmReadRegister(r);
        printf("register 0x%02x = 0x%02x\n", r, val);
    }

    pcmWriteRegister(64, PCM_DEFAULT_REGISTER_VALUE_64);
    HAL_Delay(50);

    // clear ADPSV and DAPSV bits (turn on the IC)
    // set DAC to single-ended mode
    pcmWriteRegister(64, (PCM_DEFAULT_REGISTER_VALUE_64 & 0b11001111) | 1);
    sgpioHigh(pGpioRst);

    HAL_TIM_PWM_Start(pSckiTim, 0);
    HAL_Delay(5);

    pcmSetInterfaceMode(true, PCM_IF_MODE_MASTER_256FS);
    pcmSetInterfaceMode(false, PCM_IF_MODE_MASTER_256FS);

    pcmSetInterfaceFormat(true, PCM_IF_FMT_24B_I2S);
    pcmSetInterfaceFormat(false, PCM_IF_FMT_24B_I2S);
}
