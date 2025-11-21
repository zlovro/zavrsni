//
// Created by lovro on 18/11/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

// ReSharper disable CppRedundantParentheses
#include "pcm3060.h"

#include "main.h"

sgpio *            gPcmGpioVcc = NULL;
I2C_HandleTypeDef *gPcmI2c     = NULL;
I2S_HandleTypeDef *gPcmI2sDac  = NULL;
I2S_HandleTypeDef *gPcmI2sAdc  = NULL;

uint8_t gPcmI2cAddress = 0b10001100;

void    pcmWriteRegister(uint8_t pReg, uint8_t pValue);
uint8_t pcmReadRegister(uint8_t pReg);

typedef enum : uint8_t
{
    PCM_IF_MODE_SLAVE        = 0b000,
    PCM_IF_MODE_MASTER_768FS = 0b001,
    PCM_IF_MODE_MASTER_512FS = 0b010,
    PCM_IF_MODE_MASTER_384FS = 0b011,
    PCM_IF_MODE_MASTER_256FS = 0b100,
} pcmInterfaceMode;

uint8_t pcmReadRegister(uint8_t pReg)
{
    uint8_t           out;
    HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(gPcmI2c, gPcmI2cAddress, pReg, I2C_MEMADD_SIZE_8BIT, &out, 1, 1000);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }

    return out;
}

void pcmWriteRegister(uint8_t pReg, uint8_t pValue)
{
    HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(gPcmI2c, gPcmI2cAddress, pReg, I2C_MEMADD_SIZE_8BIT, &pValue, 1, 1000);
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
    const uint8_t reg = pForDac ? 67 : 72;

    // set M/S of DAC/ADC
    uint8_t val = pcmReadRegister(reg);
    val         = (val & 0b10001111) | pMode << 4;
    pcmWriteRegister(reg, val);
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
    const uint8_t reg = pForDac ? 67 : 72;

    // set FMT of DAC/ADC
    uint8_t val = pcmReadRegister(reg);
    val         = (val & ~0b11) | pFmt;
    pcmWriteRegister(reg, val);
}

/**
 *
 * @param pSckiTim
 * @param pI2c
 * @param pI2sAdc
 * @param pI2sDac
 * @param pGpioAdrSet state of the ADR pin (pin 27) of the PCM3060 IC
 */
void pcmInit(sgpio *pGpioRst, TIM_HandleTypeDef *pSckiTim, I2C_HandleTypeDef *pI2c, I2S_HandleTypeDef *pI2sAdc, I2S_HandleTypeDef *pI2sDac, const bool pGpioAdrSet)
{
    gPcmI2c    = pI2c;
    gPcmI2sAdc = pI2sAdc;
    gPcmI2sDac = pI2sDac;

    gPcmI2cAddress |= pGpioAdrSet << 1;

    sgpioLow(pGpioRst);
    HAL_Delay(10);
    sgpioHigh(pGpioRst);

    HAL_TIM_Base_Start(pSckiTim);
    HAL_Delay(5);

    pcmSetInterfaceMode(true, PCM_IF_MODE_SLAVE);
    pcmSetInterfaceMode(false, PCM_IF_MODE_MASTER_256FS);

    pcmSetInterfaceFormat(true, PCM_IF_FMT_24B_I2S);
    pcmSetInterfaceFormat(false, PCM_IF_FMT_24B_I2S);
}
