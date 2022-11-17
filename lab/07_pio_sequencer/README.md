## Knowledge Background

### PIO

<img width="500" alt="PIO" src="https://user-images.githubusercontent.com/87698138/202053845-9b1fc7c9-7e43-4745-8665-b60f606b7e16.png">


### DMA

<img width="500" alt="DMA" src="https://user-images.githubusercontent.com/87698138/202053899-606a6459-9b63-4c1a-a43a-dda063421817.png">

### ISR

<img width="500" alt="ISR" src="https://user-images.githubusercontent.com/87698138/202053950-e754dfd9-1913-4d67-9ff9-c2de96abd07b.png">

## What it does

### file:pioscope

We use PIO in to get the status of the boot button, it will capture 0 if you do not press it and return 1 when you press it. Press 'N' to stop!

<img width="180" alt="bootpin" src="https://user-images.githubusercontent.com/87698138/202353599-ff524c45-9037-45d3-9b4e-4dbf3991054c.png">

### file:sequencer

We use `PIO0` and `SM1` to get the output of boot button pin, and still use `PIO0` and `SM0` to set neopiexel. 

Function `bool get_gpio(const uint32_t *buf, uint pin)` is our own pio-io-engine to get the output of a gpio, which replaces the original offical function `gpio_get(QTPY_BOOT_PIN)`. More details could check the code `sequencer.c` in folder sequencer.

```
bool get_gpio(const uint32_t *buf, uint pin){
    uint bit_index = pin + 1;
    uint word_index = bit_index / SHIFT_REG_WIDTH;
    uint word_mask = 1u << (bit_index % SHIFT_REG_WIDTH);
    return(buf[word_index] & word_mask ? true : false);
}
```

## Comment

The using instruction is same with the part 04, the only difference is we use our own pio-io-engine replace the old one. Use 'r' to read a register, use 'w' to wrtie to a register.
