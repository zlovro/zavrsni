//
// Created by lovro on 13/11/2025.
// Copyright (c) 2025 lovro. All rights reserved.
//

#ifndef UC1609C_H
#define UC1609C_H

#include <stm32f4xx_hal.h>

#include "smolgpio.h"

#define LCD_WIDTH 192
#define LCD_HEIGHT 64
#define LCD_FRAME_SIZE (LCD_WIDTH * LCD_HEIGHT / 8)

extern sgpio *            gLcdGpioCd;
extern sgpio *            gLcdGpioCs;
extern SPI_HandleTypeDef *gLcdSpi;
extern const uint8_t      gLcdTestImage[LCD_FRAME_SIZE];

void lcdInit(SPI_HandleTypeDef *pSpi, sgpio *pGpioVcc, sgpio *pGpioRst, sgpio *pGpioCd, sgpio *pGpioCs, bool pInvertColors, bool pMirrorX, bool pMirrorY);
void lcdSetBias(int pBias);
void lcdClearScreen();

void        lcdSendFrame(uint8_t *pFrame);
extern void lcdDmaStartFrame(uint8_t *pFrame);
#define lcdDmaEndFrame() sgpioHigh(gLcdGpioCs) // call in DMA SPI cplt callback

/**
 *
 * @param pUp range [0, 64>
 */
void lcdScroll(int pUp);

#endif //UC1609C_H
