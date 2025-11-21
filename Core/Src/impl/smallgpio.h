//
// Created by lovro on 11/5/25.
//

#ifndef DVD_F411_SMALLGPIO_H
#define DVD_F411_SMALLGPIO_H

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <stdbool.h>

typedef struct
{
    uint32_t pin;
    GPIO_TypeDef* port;
} sgpio;

#define SGPIO_FROM_MACRO(name) ((sgpio){.pin = name ## _Pin, .port = name ## _GPIO_Port})

void sgpioSet(sgpio* pGpio, bool pX);

#define sgpioHigh(g) sgpioSet(g, true)
#define sgpioLow(g) sgpioSet(g, false)

#endif //DVD_F411_SMALLGPIO_H
