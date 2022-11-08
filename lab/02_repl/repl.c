#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "registers.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#define ADDRESS_LENGTH 8 //32 bits address
#define MSG_LENGTH 8 //32 bits input

// initialize buffer
char addr[8] = {'0'}; // store 8 bytes hex number = 32 bits binary number
char msg[8] = {'0'}; // store 8 bytes hex number = 32 bits binary number
ADDRESS hex_addr = 0; // addr convertor
VALUE hex_msg = 0; // msg convertor
VALUE value = 0; 
int i_addr = 0; //iterator
int i_msg = 0; //iterator

uint16_t get_block(uint8_t *buffer) {
  uint16_t buffer_index= 0;
  while (true) {
    int c = getchar_timeout_us(100);
    if (c != PICO_ERROR_TIMEOUT && buffer_index < BUFFER_LENGTH) {
      buffer[buffer_index++] = (c & 0xFF);
    } else {
      break;
    }
  }
  return buffer_index;
}

int main(){
    stdio_init_all(); //initialization

    while(true){
        printf("-----------\n");
        sleep_ms(1000);
        if(i_addr < ADDRESS_LENGTH){
            printf("Input register address:\n");
            // read from keyboard and store to buffer
            // char c = getchar_timeout_us(1000);
            // if(c!= PICO_ERROR_TIMEOUT){
            //     addr[i_addr] = c;
            //     i_addr++;
            // }
            
            continue;
        }
        if(i_msg < MSG_LENGTH){
            printf("Input value you want to write into the register:\n");
            // read from keyboard and store to buffer
            char c = getchar_timeout_us(1000);
            if(c!= PICO_ERROR_TIMEOUT){
                msg[i_msg] = c;
                i_msg++;
            }
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