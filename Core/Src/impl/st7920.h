//
// Created by lovro on 24/03/2026.
// Copyright (c) 2026 lovro. All rights reserved.
//

#ifndef ST7920_H
#define ST7920_H

#include <types.h>
#include <impl/smallgpio.h>
#include <main.h>

#define ST7920_MONOSPACE false

typedef pstruct
{
    u8 drawingStartEnd; // first column that isnt empty
    // u8 drawingEnd   : 3; // last non empty column
    // u8 padding      : 2;
    u8 cols[8];
} ST7920_Glyph;

extern sgpio ST7920_PIN_CS;
extern sgpio ST7920_PIN_RST;

extern SPI_HandleTypeDef *ST7920_Spi;

extern u8 ST7920_FrontBuf[64 * (7 + 32)];
extern u8 ST7920_BackBuf[1024];

extern const u8 ST7920_Font[];

#define ST7920_FontGlyphs ((ST7920_Glyph*) ST7920_Font)
#define ST7920_ClearBack() ARRAY_ZERO(ST7920_BackBuf)

extern int ST7920_CursorX, ST7920_CursorY;
extern int ST7920_OriginX, ST7920_OriginY;
extern int ST7920_WrapX;

#define ST7920_LINE_HEIGHT 9
#define ST7920_FONT_HEIGHT 8
#define ST7920_FONT_SPACING_X 2

void ST7920_Init(SPI_HandleTypeDef *spi);
void ST7920_SendCommand(u8 data);
void ST7920_BackToFront();
void ST7920_SendFrameDMA();

void ST7920_SetOrigin(u8 x, u8 y);
void ST7920_Seek(u8 x, u8 y);

void ST7920_DrawLineHorizontal(u8 x, u8 y, u8 length);
void ST7920_DrawLineVertical(u8 x, u8 y, u8 length);
void ST7920_DrawRectangle(u8 x, u8 y, u8 width, u8 height, u8 thickness);
void ST7920_DrawChar(char chr);
void ST7920_DrawStringLen(char *str, u8 length);
void ST7920_DrawString(char *str);
void ST7920_DrawStringLenCenteredInRect(char *str, u8 length, u8 x, u8 y, u8 width, u8 height, bool vertically, bool horizontally);
void ST7920_DrawStringCenteredInRect(char *str, u8 x, u8 y, u8 width, u8 height, bool vertically, bool horizontally);
void ST7920_Printf(char *format, ...);
void ST7920_PrintfCenteredInRect(char *format, u8 x, u8 y, u8 width, u8 height, bool vertically, bool horizontally, ...);

#endif //ST7920_H
