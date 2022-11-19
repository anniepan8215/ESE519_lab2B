#include "hardware/pio.h"

#ifndef NEOPIXEL_H
#define NEOPIXEL_H

void neopixel_init(PIO pio, uint sm);
void neopixel_set_rgb(PIO pio, uint sm,uint32_t rgb);

#endif
