//
// Created by lovro on 13/11/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

#include "uc1609c.h"
#include "math_util.h"
#include "main.h"

sgpio *            gLcdGpioCd;
sgpio *            gLcdGpioCs;
SPI_HandleTypeDef *gLcdSpi;

void lcdCommand(bool pCd, int pDat);
void lcdDoubleCommand(bool pCd, int pDat1, int pDat2);
void lcdTestImage();
void lcdSeekOrigin();

#define lcdWrite(x) lcdCommand(1, x)

void lcdInit(SPI_HandleTypeDef *pSpi, sgpio *pGpioVcc, sgpio *pGpioRst, sgpio *pGpioCd, sgpio *pGpioCs, bool pInvertColors, bool pMirrorX, bool pMirrorY)
{
    gLcdSpi    = pSpi;
    gLcdGpioCs = pGpioCs;
    gLcdGpioCd = pGpioCd;

    sgpioLow(pGpioVcc);
    HAL_Delay(10);

    sgpioHigh(pGpioVcc);
    HAL_Delay(1);

    sgpioLow(pGpioRst);
    HAL_Delay(1);

    sgpioHigh(pGpioRst);
    HAL_Delay(10);

    // display enable
    lcdCommand(0, 0xAF);
    HAL_Delay(50);

    lcdSetBias(180);

    if (pInvertColors)
    {
        lcdCommand(0, 0xA7);
    }

    lcdCommand(0, 0b11000000 | (pMirrorY << 2 | pMirrorX << 1));

    lcdClearScreen();
    lcdTestImage();
}

void lcdSetBias(int pBias)
{
    lcdDoubleCommand(0, 0b10000001, pBias);
}

void lcdClearScreen()
{
    lcdSeekOrigin();
    for (int i = 0; i < LCD_FRAME_SIZE; i++)
    {
        lcdWrite(0);
    }
}

void lcdSendFrame(uint8_t *pFrame)
{
    sgpioHigh(gLcdGpioCd);
    sgpioLow(gLcdGpioCs);
    HAL_SPI_Transmit(gLcdSpi, pFrame, LCD_FRAME_SIZE, 1000);
    sgpioHigh(gLcdGpioCs);
}

inline void lcdDmaStartFrame(uint8_t *pFrame)
{
    sgpioHigh(gLcdGpioCd);
    sgpioLow(gLcdGpioCs);

    HAL_SPI_Transmit_DMA(gLcdSpi, pFrame, LCD_FRAME_SIZE);
}

void lcdScroll(int pUp)
{
    lcdCommand(0, 1 << 6 | pUp);
}

void lcdCommand(bool pCd, int pDat)
{
    sgpioLow(gLcdGpioCs);

    sgpioSet(gLcdGpioCd, pCd);

    HAL_StatusTypeDef ret = HAL_SPI_Transmit(gLcdSpi, (uint8_t *) &pDat, 1, 1000);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }

    sgpioHigh(gLcdGpioCs);
}

void lcdDoubleCommand(bool pCd, int pDat1, int pDat2)
{
    sgpioLow(gLcdGpioCs);

    sgpioSet(gLcdGpioCd, pCd);

    uint8_t           dat[] = {(uint8_t) pDat1, (uint8_t) pDat2};
    HAL_StatusTypeDef ret   = HAL_SPI_Transmit(gLcdSpi, dat, 2, 1000);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }

    sgpioHigh(gLcdGpioCs);
}

void lcdTestImage()
{
    lcdSendFrame(gLcdTestImage);
}

void lcdSeekOrigin()
{
    // wrap settings (12. AC)
    lcdCommand(0, 0b10001011);

    // set column
    lcdCommand(0, 0b00000000);
    lcdCommand(0, 0b00010000);

    // set scroll line
    lcdCommand(0, 0b01000000);

    // set page
    lcdCommand(0, 0b10110000);
}
