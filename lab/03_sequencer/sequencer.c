#include "pico/stdlib.h"
#include <stdio.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "repl.h"
#include "ws2812.pio.h" // pio0
#include <inttypes.h>
#define button_pin 21
//Refered to as the base address of user bank IO registers
#define base 0x40014000
volatile uint32_t * boot_pin_address;
uint32_t full_gpio_register_value;
uint32_t pin_21_selection_mask;
uint32_t select_pin_state;
uint32_t shifted_pin_21_state;
#define READ 'r'
#define WRITE 'w'
typedef void (*pattern)(uint len, uint t);
const struct {
    uint32_t color;
    char* name;
} color_table[] = {
        {0x00ff00,  "Green!"},
        {0xff0000,  "Red!"},
        {0x0000ff, "Blue!"},
        {0x00ffff, "New!"},
};

typedef struct {
    uint32_t last_serial_byte;
    uint32_t button_is_pressed;
    uint32_t light_color;
} Flashlight;

//macros - a sequence of console commands based on keystrokes
void macros() {
    int flag = 0;
    while (flag <= 3) {
        set_neopixel_color(color_table[flag].color);
        flag++;
        sleep_ms(500);
    }
}



int main() {
    stdio_init_all();
    neopixel_init();

    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);


    Flashlight status;
    status.last_serial_byte = 0x00000000;
    status.button_is_pressed = 0x00000000;
    status.light_color = 0x000000ff; //Blue color
    int recording_flag = 0;
   
    while (true) {

        status.last_serial_byte = getchar_timeout_us(0);
        switch (status.last_serial_byte) { // poll every cycle
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
        case 'p':
            status.button_is_pressed = 0x00000001;
            recording_flag = 1;
            break;
        case 'n':
            status.button_is_pressed = 0x00000000;
            recording_flag = 0;
            break;
        }
        if (recording_flag == 0) {
            if (gpio_get(button_pin)) { // poll every cycle, 0 = "pressed"
                status.button_is_pressed = 0x00000000;
            }
            else {
                status.button_is_pressed = 0x00000001;
            }
        }
        if (status.button_is_pressed) { // poll every cycle
            macros();
        }
        else {
            set_neopixel_color(0x000000);
        }
        if (recording_flag == 1) {
            status.button_is_pressed = 0x00000000;
            recording_flag = 0;
        }
        printf("0x%08x\n", status.button_is_pressed);
        printf("0x%08x\n", status.light_color);
        sleep_ms(10);
    }

    return 0;
}


