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
} st7920_glyph;

extern sgpio ST7920_PIN_CS;
extern sgpio ST7920_PIN_RST;

extern SPI_HandleTypeDef *st7920_spi;

extern u8 st7920_frontBuf[64 * (7 + 32)];
extern u8 st7920_backBuf[1024];

extern const u8 st7920_font[];

#define st7920_fontGlyphs ((st7920_glyph*) st7920_font)

extern int st7920_cursorX, st7920_cursorY;
extern int st7920_originX, st7920_originY;
extern int st7920_wrapX;

#define ST7920_LINE_HEIGHT 9
#define ST7920_FONT_HEIGHT 8
#define ST7920_FONT_SPACING_X 2

void st7920_Init(SPI_HandleTypeDef *spi);
void st7920_SendCommand(u8 data);
void st7920_ClearBack();
void st7920_BackToFront();
void st7920_SendFrameDMA();

void st7920_SetOrigin(u8 x, u8 y);
void st7920_Seek(u8 x, u8 y);

void st7920_DrawLineHorizontal(u8 x, u8 y, u8 length);
void st7920_DrawLineVertical(u8 x, u8 y, u8 length);
void st7920_DrawRectangle(u8 x, u8 y, u8 width, u8 height, u8 thickness);
void st7920_DrawChar(char chr);
void st7920_DrawStringLen(char *str, u8 length);
void st7920_DrawString(char *str);
void st7920_DrawStringLenCenteredInRect(char *str, u8 length, u8 x, u8 y, u8 width, u8 height, bool vertically, bool horizontally);
void st7920_DrawStringCenteredInRect(char *str, u8 x, u8 y, u8 width, u8 height, bool vertically, bool horizontally);
void st7920_Printf(char *format, ...);
void st7920_PrintfCenteredInRect(char *format, u8 x, u8 y, u8 width, u8 height, bool vertically, bool horizontally, ...);

#endif //ST7920_H
