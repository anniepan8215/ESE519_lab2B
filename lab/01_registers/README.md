

`.\Code`: Question Q1 code <br>
Modify neopixel.c and flashlight.c
# Code Setup  

In order to run the flashlight.c example code on your local machine:  

1. Manually create an empty generated/ folder in the OUTPUT_DIR where pico_generate_pio_header is trying to create an output file. 
2. Delete your /build folder.


# High Level Logic

## flashlight.c

In order to use only direct register reads to access the boot button, we define value as the 'unsigned int' type and When the value of the variable 'value' declared using volatile is requested, the system always re-reads the data from the memory where it is located, even if it has just been read from there by a previous instruction. And the read data is immediately saved.   

Then we can define a function and use the given address to directacess the value stored in that address and with the function 'register_write' to change the value stored in the address that the pointer type variable address is pointed to.

```c
VALUE register_read(ADDRESS address) {
    return *address;
}

void register_write(ADDRESS address, VALUE value) {
    *address = value;
}
```  

From the below graph, we can find the QTPY_BOOT_PIN corresponding to GPIO21 pin 
<img src="QT_PY_RP2040_PIN_OUT.PNG" style="zoom:70%"> <br>

In the main program, the PIN 21 can be configured as binary in by executing: 

```c
gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
```   
In the program, we also define a struct structure and use it to contain the last serial byte, the 'int' variable that indicates whether the button is pressed or not and the light color (default as the blue one). 

The structure for the main loop is described as follows:

<img src="flashlightc.drawio.png" style="zoom:70%"> <br>  

In order to direct use the register, we find the user bank IO register's start base address and add a offset to GPIO21_CTRL and find the immediate address that the boot button is corresponding to:

```c
 if (shifted_pin_21_state) { // poll every cycle, 0 = "pressed"
            status.button_is_pressed = 0x00000000;
        }
        else {
            status.button_is_pressed = 0x00000001;
        }
```   

## neopixel.c

In this C file for part1, we mainly defien the corresponding pin for PIO, SM, FREQ and IS_RGBW. The group changes the pin value for the PIN and POWER_PIN into 11, 12 correspoindingly, in order to configure the neopixel properly, the line correspoinding to the changed code is given as follows:

```c
#define PIN         12
#define POWER_PIN   11
```  

The above part is regarding for SDK allowing us to specify other "target boards" besides the Pico by setting the PICO_BOARD environment variable to the name of the board header file. 

Moreover, this c file also contains the function to convert RGB to GRB(encoded as a 24 binary number as expected by the NeoPixel).

```c
void neopixel_set_rgb(uint32_t rgb) {
    // convert RGB to GRB
    uint32_t grb = ((rgb & 0xFF0000) >> 8) | ((rgb & 0x00FF00) << 8) | (rgb & 0x0000FF);
    pio_sm_put_blocking(pio0, 0, grb << 8u);
}
```  

The demo for this part is given as:  

![](https://github.com/anniepan8215/ESE519_lab2B/blob/main/Media/Part1.gif)
