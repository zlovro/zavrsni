//
// Created by lovro on 05/04/2026.
// Copyright (c) 2026 lovro. All rights reserved.
//

#include <stm32f4xx.h>
#include "dsp.h"

u32 DSP_TxRawBuf[DSP_BUF_SAMPLE_COUNT * 2 * 2] = {0};
u32 DSP_TxWorkBuf[DSP_BUF_SAMPLE_COUNT]        = {0};
u32 DSP_RxRawBuf[DSP_BUF_SAMPLE_COUNT * 2 * 2] = {0};
u32 DSP_RxWorkBuf[DSP_BUF_SAMPLE_COUNT]        = {0};

static inline void DSP_Unmangle(u32 *src, u32 *dst)
{
    // DSP_RxRawBuf format:
    // CCxxAABB xxxxxxxx
    // when loaded from memory, it becomes BBAAxxCC

    u32 x = *src;
    u32 y = (x & 0xFF00FF) | ((x >> 24) << 8);
    *dst  = y;
}

static inline void DSP_Mangle(u32 *src, u32 *dst)
{
    // src contains xxAABBCC
    // dst needs to contain BBAAxxCC

    u32 x = *src;
    u32 y = (x & 0xFF00FF) | ((x >> 8) << 24);
    *dst  = y;
}

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *)
{
    // copy the first half of DSP_RxRawBuf into DSP_RxWorkBuf and reorder bytes
    for (u32 *src = DSP_RxRawBuf, *dst = DSP_RxWorkBuf; src != ARRAY_HALF(DSP_RxRawBuf); src += 2, dst++)
    {
        DSP_Unmangle(src, dst);
    }

    // the first half of DSP_TxRawBuf was just transferred. fill it up with data
    for (u32 *src = DSP_TxWorkBuf, *dst = DSP_TxRawBuf; src != ARRAY_END(DSP_TxWorkBuf); src++, dst += 2)
    {
        DSP_Mangle(src, dst);
    }
}

void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *)
{
    // copy the second half of DSP_RxRawBuf into DSP_RxWorkBuf and reorder bytes
    for (u32 *src = ARRAY_HALF(DSP_RxRawBuf), *dst = DSP_RxWorkBuf; src != ARRAY_END(DSP_RxRawBuf); src += 2, dst++)
    {
        DSP_Unmangle(src, dst);
    }

    // the second half of DSP_TxRawBuf was just transferred. fill it up with data
    for (u32 *src = DSP_TxWorkBuf, *dst = ARRAY_HALF(DSP_TxRawBuf); src != ARRAY_END(DSP_TxWorkBuf); src++, dst += 2)
    {
        DSP_Mangle(src, dst);
    }
}
