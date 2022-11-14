#include "hardware/pio.h"
#include "ws2812.pio.h" 

#define PIO         pio0
#define SM          0
#define FREQ        800000
#define PIN         12
#define POWER_PIN   11
#define IS_RGBW     true  


void neopixel_set_rgb(uint32_t rgb) {
    // convert RGB to GRB
    uint32_t grb = ((rgb & 0xFF0000) >> 8) | ((rgb & 0x00FF00) << 8) | (rgb & 0x0000FF);
    pio_sm_put_blocking(pio0, 0, grb << 8u);
}

