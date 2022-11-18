/*
    A simple driver for APDS9960 by Dang0v

    based on PIO.I2C example in PICO_example

*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "string.h"
#include "pio_i2c.h"

#define ENABLE_REG _u(0x80)
#define ALS_REG _u(0x81)
#define PDATA_REG _u(0x9C)
#define CDATAL _u(0x94)
#define GEN 0 //cCorresponidng to gesture enable register
#define AEN 1 //ALS Enable. The field activates ALS function and writing one activates the ALS. Writing a zero disables 
//The ALS detection can detect light intensity data
#define PON 1 //Power ON. This field activiates the internal oscillator to permit the timers and ADC 
//channels to operate. Writing a one activates the oscillator. Writing a zero disables the oscillator 
//and puts the device into a lower power sleep mode. During reads and writes over the I2C interface,
//this bit is temporarily overridden adn the oscillator is enabled, independent of the state of PON.
#define PIEN 1 //Proximity interrupt enable. When asserted, it permits proximity interrupts to be generated, subject to
//the persistence filter settings.
#define ALS_GAIN 0
#define ALS_TIME 219
#define PIN_SDA 22
#define PIN_SCL 23
#define CONFIGURATION (GEN << 6U) | (PIEN << 2u) | (AEN << 1u) | PON
PIO pio = pio0;
uint sm = 0;
const int addr = 0x39; //The device supports a single slave address of 0x39 Hex using 7-bit addressing protocol

void APDS9960_init() {
    uint8_t buf[2];
    //Set the corresponidng register number and initialzie APDS9960
    buf[0] = ENABLE_REG;
    buf[1] = CONFIGURATION;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);
    buf[0] = ALS_REG;
    buf[1] = ALS_TIME;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);
}
void readProximity(int32_t* proximity)
{
    uint8_t buf[1];
    uint8_t proximityReg = PDATA_REG;
    pio_i2c_write_blocking(pio, sm, addr, &proximityReg, 1, true); //try to keep master control of the bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 1, false);
    *proximity = buf[0];

}
void readRGBC(int32_t* r, int32_t* g, int32_t *b, int32_t *c)
{
    //The shape of the buf is(8,2)
    uint8_t buf[2];
    //buf[x,0] is lower byte, buf[x,1] is the higher byte
    //buf[0 2 4 6] corresponding to byte color rgbc lower byte
    //buf[1 3 5 7] corresponding to byte color rgbc higher byte
    uint8_t reg = CDATAL;
    pio_i2c_write_blocking(pio,sm,addr,&reg,1,true);
    pio_i2c_read_blocking(pio,sm,addr,buf,1,false);
    *c = (buf[1] << 8) | buf[0];
    *r = (buf[3] << 8) | buf[2];
    *g = (buf[5] << 8) | buf[4];
    *b = (buf[7] << 8) | buf[6];
}
