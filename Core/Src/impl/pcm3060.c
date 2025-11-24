//
// Created by lovro on 18/11/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

// ReSharper disable CppRedundantParentheses
#include "pcm3060.h"

#include "main.h"

sgpio *            gPcmGpioVcc = NULL;
sgpio *            gPcmGpioMs  = NULL;
SPI_HandleTypeDef *gPcmSpi     = NULL;
I2S_HandleTypeDef *gPcmI2sDac  = NULL;
I2S_HandleTypeDef *gPcmI2sAdc  = NULL;

void pcmWriteRegister(uint8_t pReg, uint8_t pValue);

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
    uint16_t          encoded = (pValue << 8) | pReg;
    HAL_StatusTypeDef ret     = HAL_SPI_Transmit(gPcmSpi, (uint8_t *) &encoded, 1, 1000);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 *
 * @param pForDac set interface mode for DAC if this is true, else for ADC
 * @param pMode
 */
void pcmSetInterfaceMode(const bool pForDac, const pcmInterfaceMode pMode)
{
    uint8_t regIdx, regVal;
    if (pForDac)
    {
        regIdx = 67;
        regVal = PCM_DEFAULT_REGISTER_VALUE_67;
    }
    else
    {
        regIdx = 72;
        regVal = PCM_DEFAULT_REGISTER_VALUE_72;
    }

    // set M/S of DAC/ADC
    regVal = (regVal & 0b10001111) | pMode << 4;
    pcmWriteRegister(regIdx, regVal);
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
    uint8_t regIdx, regVal;
    if (pForDac)
    {
        regIdx = 67;
        regVal = PCM_DEFAULT_REGISTER_VALUE_67;
    }
    else
    {
        regIdx = 72;
        regVal = PCM_DEFAULT_REGISTER_VALUE_72;
    }

    // set FMT of DAC/ADC
    regVal = (regVal & ~0b11) | pFmt;
    pcmWriteRegister(regIdx, regVal);
}

/**
 *
 * @param pGpioRst
 * @param pGpioMs
 * @param pSckiTim
 * @param pSpi
 * @param pI2sAdc
 * @param pI2sDac
 */
void pcmInit(sgpio *pGpioRst, sgpio *pGpioMs, TIM_HandleTypeDef *pSckiTim, SPI_HandleTypeDef *pSpi, I2S_HandleTypeDef *pI2sAdc, I2S_HandleTypeDef *pI2sDac)
{
    gPcmGpioMs = pGpioMs;
    gPcmSpi    = pSpi;
    gPcmI2sAdc = pI2sAdc;
    gPcmI2sDac = pI2sDac;

    sgpioLow(pGpioRst);
    HAL_Delay(10);
    sgpioHigh(pGpioRst);

    HAL_TIM_PWM_Start(pSckiTim, 0);
    HAL_Delay(5);

    // clear ADPSV and DAPSV bits (turn on the IC)
    // set DAC to single-ended mode
    pcmWriteRegister(64, (PCM_DEFAULT_REGISTER_VALUE_64 & 0b11001111) | 1);

    pcmSetInterfaceMode(true, PCM_IF_MODE_SLAVE);
    pcmSetInterfaceMode(false, PCM_IF_MODE_MASTER_256FS);

    pcmSetInterfaceFormat(true, PCM_IF_FMT_24B_I2S);
    pcmSetInterfaceFormat(false, PCM_IF_FMT_24B_I2S);
}
