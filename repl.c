#include "pico/stdlib.h"
#include <stdio.h>
#include<stdlib.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "registers.h"
#include <strings.h>
#include <string.h>

#define QTPY_BOOT_PIN 21
#ifndef PICO_DEFAULT_WS2812_PIN
#define PICO_DEFAULT_WS2812_PIN 12
#endif

#ifndef PICO_DEFAULT_WS2812_POWER_PIN
#define PICO_DEFAULT_WS2812_POWER_PIN 11
#endif

volatile char *address;
char inputs[8];
char user_input_1;

typedef struct {
    uint32_t reg_address;
    uint32_t reg_value;
} Register_status; 


void render_to_console(Register_status status) {
    // adjust console window height to match 'frame size'
    for (uint8_t i=0; i<10; i++) { 
        printf("\n");
    }
    printf("reg_address:  0x%08x\n",   status.reg_address);
    printf("reg_value:    0x%08x\n",   status.reg_value);
}  

int main() {
    ADDRESS address;
    uint32_t user_input_8; //Stores the inputed reg address
    char user_input_1;     //Stores the user's operation decision
    VALUE register_value;
    uint input;

    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();
    stdio_usb_init();

    Register_status status;
    status.reg_address =  0x00000000;
    status.reg_value =    0x00000000;
    printf("Now the part2 start\n");

    while (true) {
        printf("What register would you like to access?\n");
        sleep_ms(5000);

        //take 8 character inputs(int+char)
        for (int i= 0; i<8; i++ ) {
            user_input_1 = getchar_timeout_us(0);
            inputs[i] = user_input_1;
        }
        //let excessive inputs be discarded
        for (int i= 0; i<8; i++ ) {
            getchar_timeout_us(0);
        }
        //print inputted address
        printf("The address you want to access is: %s\n", inputs);
        
        sleep_ms(1000);

        address = (volatile char *) inputs;
        status.reg_address = inputs;
        status.reg_value = *address;
        render_to_console(status);
        sleep_ms(10);

        // printf("Do you want to write new value to this register? (1 = yes, 0 = no, q = quit)\n");

        // if(user_input_1 == '1'){
        //     printf("Enter the new 8 bit hex value you want to write in this register:\n");
        //     *address = user_input_1;   // put the user input 8-bit value to this address
        //     status.reg_value = *address;
        //     render_to_console(status);
        // }
        // if(user_input_1 = 'q'){
        //     break;
        // }
        // else{
        //     continue;
        // }
        
        // printf("The updated information: \n");
        // render_to_console(status);
        // sleep_ms(10); // don't DDOS the serial console
    }
    return 0;
}                  
