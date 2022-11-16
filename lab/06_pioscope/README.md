### TODO:

- modify the PIO/DMA logic analyzer example to record a timestamped trace of an RP2040-ADPS9960 exchange while the BOOT button is pressed
- with a partner, connect a second Qt Py to the Stemma Qt bus of an ADPS9960 that's attached to a first Qt Py running the Lab 1 Python code
- record a trace of this exchange

# DMA
DMA maintains a 'counter' for each channel. Each 1-clock pulse for the 'dreq' signal will increment the 'counter'. When nonzero, the channel will request transfer from the DMA's internal arbiter and decrease the value of the counter when the transfered is issued to address FIFOs. 
```c
channel_config_set_dreq(&c, pio_get_dreq(pio, sm, false));
```  
### chaining 

# PIO
Functionality: there's two PIO and each of them can be used for any GPIOs ([1.4.3](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf))
### data flow
Memory -> TXF(auto `PULL`) -> OSR(`OUT`) -> GPIO <br>
Memory <- RXF(auto `PUSH`) <- ISR(`IN`) <- GPIO


# GPIO 
Reading `GPIO_IN` returns all 30 GPIO values  in a single read. Software can then mask out
individual pins it is interested in.
