//
// Created by lovro on 11/5/25.
//

#include "smallgpio.h"

void sgpioSet(sgpio* pGpio, bool pX)
{
    pGpio->port->BSRR = pGpio->pin << (!pX * 16);
}
