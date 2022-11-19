#include "hardware/pio.h"
#include "ws2812.pio.h" 

// #define PIO         pio1
// #define SM          2
#define FREQ        800000
#define PIN         12
#define POWER_PIN   11
#define IS_RGBW     true  

void neopixel_init(PIO pio, uint sm) {
    // power up WS2812 on Qt Py, using pin defs from board header file
    // pico-sdk/src/boards/include/boards/adafruit_qtpy_rp2040.h
    gpio_init(POWER_PIN);
    gpio_set_dir(POWER_PIN, GPIO_OUT);
    gpio_put(POWER_PIN, 1);

    // program PIO using helper function from ws2812.pio
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, PIN, FREQ, IS_RGBW);
}
           

void neopixel_set_rgb(PIO pio, uint sm, uint32_t rgb) {
    // convert RGB to GRB
    uint32_t grb = ((rgb & 0xFF0000) >> 8) | ((rgb & 0x00FF00) << 8) | (rgb & 0x0000FF);
    pio_sm_put_blocking(pio, sm, grb << 8u);
}
