//
// Created by lovro on 05/04/2026.
// Copyright (c) 2026 lovro. All rights reserved.
//

#ifndef DSP_H
#define DSP_H

#include <types.h>

#define DSP_BUF_SAMPLE_COUNT 256

// times 2 because we dont use the right channel
extern u32 DSP_TxRawBuf[DSP_BUF_SAMPLE_COUNT * 2 * 2];
extern u32 DSP_TxWorkBuf[DSP_BUF_SAMPLE_COUNT];
extern u32 DSP_RxRawBuf[DSP_BUF_SAMPLE_COUNT * 2 * 2];
extern u32 DSP_RxWorkBuf[DSP_BUF_SAMPLE_COUNT];


#endif //DSP_H
