### TODO:

Use the capabilities of your sequencer to implement the ADPS9960 protocol and control the sensor.

The approach of this lab is to implement the APDS9960 protocol directly using the PIO module, instead of using the I2C hardware module. This include drive for APDS9960 for I2C.

We plan to combining the regular i2c code with pio-i2c code and write our own protocol. 

The group designed a self implemented APDS9960.c file and enable the serial to read the APDS9960 protocol from the sensor and read the proximity data

The demo is for proximity part is given as follows:
![](https://github.com/anniepan8215/ESE519_lab2B/blob/main/Media/lab9_proximity.gif)