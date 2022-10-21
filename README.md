# ESE519_lab2B


## LED
The following link is the LED gif of our breadboard in action: 
![](https://media.giphy.com/media/joMgdCdvrxvvOjSpzw/giphy.gif)

## PROPOSAL: Balanced Board
- An outline of what you plan to build, and why you think it’s cool.

  - What we gonna do: 
Using IMU to detect the title of the board and reflect it by the luminance of the LED located at 4 directions(corners). 

  - Why we do this: 
This is the fundamental part of the drone, we plan to use it to keep the drone balance and measuring the degree of balance of the drone. 

- Components requested from Detkin (after confirming availability).
    - Servo: Micro servo SD-90 [servo](https://www.digikey.com/en/products/detail/gearbox-labs/PART%2520MICRO%2520SERVO%2520SG-90%2520ANALOG/16159912?utm_adgroup=Motors%20-%20AC%2C%20DC&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Motors%2C%20Solenoids%2C%20Driver%20Boards%2FModules_NEW&utm_term=&utm_content=Motors%20-%20AC%2C%20DC&gclid=CjwKCAjwwL6aBhBlEiwADycBIKHGbRNoXgU73AqBxXqaXLsZl-pzncPgMMfCcFZEfmzbnrYH58MbdxoCAd8QAvD_BwE)

  - Display: 128*32 OLED SSD1306 [Display](https://www.adafruit.com/product/2900)

  - IMU: 
    - MPU6050 (may out of stock for Adafruit)[MPU6050](https://www.adafruit.com/product/3886)
    - (Available on Amazon for another version):[MPU60502](https://www.amazon.com/HiLetgo-MPU-6050-Accelerometer-Gyroscope-Converter/dp/B01DK83ZYQ?th=1)
    - [MMA8451](https://learn.adafruit.com/adafruit-mma8451-accelerometer-breakout)

- Any questions about your design or component selection.
RP2040 only has two I2C ports (one on the QT connector, one on the breakout pads), but what if the final project we want to build needs more I2C or GPIO ports?

