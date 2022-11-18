#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "neopixel.h"
#include "repl.h"
#include "ws2812.pio.h" // pio0
#include <inttypes.h>

#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/structs/bus_ctrl.h"
#include "hardware/gpio.h"

#define QTPY_BOOT_PIN 21

#define READ 'r'
#define WRITE 'W'
#define record 's'
#define replay 'g'

uint SHIFT_REG_WIDTH = 32;

typedef struct {
    uint32_t command;
    uint32_t button_is_pressed;
    uint32_t light_color;
} Sequencer; 

void logic_analyser_init(PIO pio, uint sm, uint pin_base, float div) {
    // Load a program to capture n pins. This is just a single `in pins, n`
    // instruction with a wrap.
    uint16_t capture_prog_instr = pio_encode_in(pio_pins, 1);
    struct pio_program capture_prog = {
            .instructions = &capture_prog_instr,
            .length = 1,
            .origin = -1
    };
    uint offset = pio_add_program(pio, &capture_prog);

    // Configure state machine to loop over this `in` instruction forever,
    // with autopush enabled.
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_in_pins(&c, pin_base);
    sm_config_set_wrap(&c, offset, offset);
    sm_config_set_clkdiv(&c, div);
    // Note that we may push at a < 32 bit threshold if pin_count does not
    // divide 32. We are using shift-to-right, so the sample data ends up
    // left-justified in the FIFO in this case, with some zeroes at the LSBs.
    sm_config_set_in_shift(&c, true, true, SHIFT_REG_WIDTH);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX);
    pio_sm_init(pio, sm, offset, &c);
}

void logic_analyser_arm(PIO pio, uint sm, uint dma_chan, uint32_t *capture_buf, size_t capture_size_words,
                        uint trigger_pin, bool trigger_level) {
    pio_sm_set_enabled(pio, sm, false);
    // Need to clear _input shift counter_, as well as FIFO, because there may be
    // partial ISR contents left over from a previous run. sm_restart does this.
    pio_sm_clear_fifos(pio, sm);
    pio_sm_restart(pio, sm);

    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    channel_config_set_dreq(&c, pio_get_dreq(pio, sm, false));

    dma_channel_configure(dma_chan, &c,
        capture_buf,        // Destination pointer
        &pio->rxf[sm],      // Source pointer
        capture_size_words, // Number of transfers
        true                // Start immediately
    );

    pio_sm_set_enabled(pio, sm, true);
}

bool get_gpio(const uint32_t *buf, uint pin){
    uint bit_index = pin + 1;
    uint word_index = bit_index / SHIFT_REG_WIDTH;
    uint word_mask = 1u << (bit_index % SHIFT_REG_WIDTH);
    return(buf[word_index] & word_mask ? true : false);
}

int main() {

    stdio_init_all();
    // gpio_init(QTPY_BOOT_PIN);
    // gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();

    uint buf_size_words = SHIFT_REG_WIDTH;
    uint32_t *capture_buf = malloc(buf_size_words * sizeof(uint32_t));
    hard_assert(capture_buf);

    PIO pio = pio0;
    uint sm = 1;
    uint dma_chan = 0;

    logic_analyser_init(pio, sm, QTPY_BOOT_PIN, 1.f);

    Sequencer status;
    status.command =  0x00000000;
    status.button_is_pressed = 0x00000000;
    status.light_color =   0x000000ff; //Blue
    uint32_t flag = 0x00000000;

    while (true) {
        status.button_is_pressed = 0x00000000;
        logic_analyser_arm(pio, sm, dma_chan, capture_buf, buf_size_words, QTPY_BOOT_PIN, false);
        status.command = getchar_timeout_us(0); // don't block main loop
        switch(status.command) { // poll every cycle
            case 'r':
                printf("r\n");
                neopixel_set_rgb(0x00ff0000); //Red
                Rread();
                break;
            case 'w':
                printf("w\n");
                neopixel_set_rgb(0x00ffffff); //White
                Rwrite();
                break;
            case 's':
                printf("s\n");
                while (true){
                    status.button_is_pressed = 0x00000000;
                    logic_analyser_arm(pio, sm, dma_chan, capture_buf, buf_size_words, QTPY_BOOT_PIN, false);
                    flag = 0x00000000;
                    flag = getchar_timeout_us(0);
                    if (get_gpio(capture_buf,QTPY_BOOT_PIN)) { // poll every cycle, 0 = "pressed"
                        printf("1\n");
                        status.button_is_pressed = 0x00000000;
                        status.light_color = 0x000000ff;
                    } else {
                        printf("2\n");
                        status.button_is_pressed = 0x00000001;
                    }
                    if (status.button_is_pressed) { // poll every cycle
                        neopixel_set_rgb(status.light_color);
                    } else {
                        neopixel_set_rgb(0x00000000);
                    }
                    if(flag=='N'){
                        break;
                    }
                    sleep_ms(10);
                }
                break;
            case 'g':
                while(true){
                    flag = 0x00000000;
                    flag = getchar_timeout_us(0);
                    if(flag == 'p'){
                        neopixel_set_rgb(0x000000ff);
                    }
                    if(flag == 'n'){
                        neopixel_set_rgb(0x00000000);
                    }
                    if (flag == 'N') {
                        break;
                    }
                    sleep_ms(10); 
                }
                break;
        }
        if (gpio_get(QTPY_BOOT_PIN)) { // poll every cycle, 0 = "pressed"
            status.button_is_pressed = 0x00000000;
            status.light_color = 0x000000ff;
        } else {
            status.button_is_pressed = 0x00000001;
        }
        if (status.button_is_pressed) { // poll every cycle
            neopixel_set_rgb(status.light_color);
        } else {
            neopixel_set_rgb(0x00000000);
        }
        sleep_ms(10); // don't DDOS the serial console
    }
}   
