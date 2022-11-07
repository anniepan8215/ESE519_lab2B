#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "registers.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#define ADDRESS_LENGTH 8
#define MSG_LENGTH 8

char addr[8] = {'0'};
char msg[8] = {'0'};
ADDRESS hex_addr = 0;
VALUE hex_msg = 0;
VALUE value = 0;
int i_addr = 0;
int i_msg = 0;

int main(){
    stdio_init_all();

    while(true){
        printf("-----------\n");
        sleep_ms(1000);
        if(i_addr < ADDRESS_LENGTH){
            printf("Input register address:\n");
            char c = getchar_timeout_us(1000);
            if(c!= PICO_ERROR_TIMEOUT){
                addr[i_addr] = c;
                i_addr++;
            }
            continue;
        }
        if(i_msg < MSG_LENGTH){
            printf("Input value you want to write into the register:\n");
            char c = getchar_timeout_us(1000);
            msg[i_msg] = c;
            i_msg++;
            continue;
        }
        if(i_addr >= ADDRESS_LENGTH && i_msg >= MSG_LENGTH){
            printf("record address successfully %s\n",addr);
            hex_addr = (ADDRESS)strtol(addr, NULL, 16);
            printf("record message successfully %s\n",msg);
            hex_msg = (VALUE)strtol(msg, NULL, 16);
            printf("Start write:\n");
            register_write(hex_addr,hex_msg);
            printf("Start read:\n");
            value = register_read(hex_addr);
            printf("The value read out is %d\n",value);
            addr[8] = '0';
            msg[8] ='0';
            hex_addr = 0;
            hex_msg = 0;
            value = 0;
            i_addr = 0;
            i_msg = 0;
            continue;
        }
        sleep_ms(500);
    }

}