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

#define Sgpio_Set(pGpio, pX) (pGpio)->port->BSRR = (pGpio)->pin << (!(pX) * 16)
#define Sgpio_Get(pGpio) ((pGpio)->port->IDR & (pGpio)->pin)

#define SGPIO_High(g) Sgpio_Set(g, true)
#define SGPIO_Low(g) Sgpio_Set(g, false)

#endif //DVD_F411_SMALLGPIO_H
