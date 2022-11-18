
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/structs/bus_ctrl.h"
#include "pico/multicore.h"
#include "pico/binary_info.h"
#include "piosequencer.h"
#include "string.h"
#include "pio_i2c.h"
#include "neopixel.h"
#include "APDS9960.h"

const uint CAPTURE_PIN_BASE = 12;
const uint CAPTURE_PIN_COUNT = 1;
const uint CAPTURE_N_SAMPLES = 350000;
const uint TRIGGER_PIN = 21;  //Corresponding to the 'boot' pin

#define PIN_SDA 22
#define PIN_SCL 23

//Core1 keep fetching data from the APDS9960
void core1_main()
{
    uint32_t proximity;
    uint32_t r, g, b, c;
    PIO pio_i2c = pio1;
    uint sm = 0;
    while (true)
    {
        readProximity(pio_i2c, sm, &proximity);
        readRGBC(pio_i2c, sm, &r, &g, &b, &c);
        neopixel_set_rgb((r << 16u | g << 8u | b));
        sleep_ms(10);
    }
}

int main() {
    stdio_init_all();
    uint total_sample_bits = CAPTURE_N_SAMPLES * CAPTURE_PIN_COUNT;
    total_sample_bits += bits_packed_per_word(CAPTURE_PIN_COUNT) - 1;
    uint buf_size_words = total_sample_bits / bits_packed_per_word(CAPTURE_PIN_COUNT);
    uint32_t* capture_buf = malloc(buf_size_words * sizeof(uint32_t));
    hard_assert(capture_buf);

    // Grant high bus priority to the DMA, so it can shove the processors out
    // of the way. This should only be needed if you are pushing things up to
    // >16bits/clk here, i.e. if you need to saturate the bus completely.
    bus_ctrl_hw->priority = BUSCTRL_BUS_PRIORITY_DMA_W_BITS | BUSCTRL_BUS_PRIORITY_DMA_R_BITS;
    //Conduct pio and DMA setting
    PIO pio = pio0;     //pio sm0 is used for logical analyzer
    PIO pio_i2c = pio1; //pio sm0 for i2c APDS9960 initialization and data fetching
    uint sm = 0;
    uint dma_chan = 0;
    //Initialization process
    //The I2C fast mode defines transfer rates up to 400 kbit/s whilst the first I2C specification dated 1982 had a limit of 100 kbit/s.
    logic_analyser_init(pio, sm, CAPTURE_PIN_BASE, CAPTURE_PIN_COUNT, 125000000 / (4 * 400 * 8 * 1000));// double freq of i2c rate. 400kbits/s => 800*8kHz
    logic_analyser_init(pio, sm, CAPTURE_PIN_BASE, CAPTURE_PIN_COUNT, 125000000 / (4 * 400 * 8 * 1000));// double freq of i2c rate. 400kbits/s => 800*8kHz

    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_IN);
    sleep_ms(5000);

    // initialize PIO.I2C and APDS9960
    uint offset = pio_add_program(pio_i2c, &i2c_program);
    i2c_program_init(pio_i2c, sm, offset, PIN_SDA, PIN_SCL);
    APDS9960_init(pio_i2c, sm);// the default i2c rate is set to 400kHz

    neopixel_init();

    multicore_launch_core1(core1_main); //keep fetching data from APDS9960 through core1.

    //-------------------------initialization--------------------------

    while (true) {
        printf("press boot button to arming trigger\n");

        do {} while (gpio_get(TRIGGER_PIN) == 1);

        logic_analyser_arm(pio, sm, dma_chan, capture_buf, buf_size_words, TRIGGER_PIN, false);

        printf("Start recording\n");

        dma_channel_wait_for_finish_blocking(dma_chan);
        printf("Recording done!\n");

        print_capture_buf(capture_buf, CAPTURE_PIN_BASE, CAPTURE_PIN_COUNT, CAPTURE_N_SAMPLES);

        sleep_ms(1000);
    }
}