import time
import board
import digitalio
from adafruit_lsm6ds.lsm6ds3 import LSM6DS3

i2c = board.STEMMA_I2C() # uses board.SCL and board.SDA
sensor = LSM6DS3(i2c)

gyro_x = 0
gyro_y = 0
gyro_z = 0
acc_x = 0
acc_y = 0
acc_z = 0

led1 = digitalio.DigitalInOut(board.A0)
led1.direction = digitalio.Direction.OUTPUT

led2 = digitalio.DigitalInOut(board.A1)
led2.direction = digitalio.Direction.OUTPUT

led3 = digitalio.DigitalInOut(board.A2)
led3.direction = digitalio.Direction.OUTPUT

led4 = digitalio.DigitalInOut(board.A3)
led4.direction = digitalio.Direction.OUTPUT

while True:
    led1.value = False
    led2.value = False
    led3.value = False
    led4.value = False
    print("Acceleration: X:%.2f, Y: %.2f, Z: %.2f m/s^2" % (sensor.acceleration))
    print("Gyro X:%.2f, Y: %.2f, Z: %.2f radians/s" % (sensor.gyro))
    print("")
    acc_x, acc_y, acc_z = sensor.acceleration
    gyro_x, gyro_y, gyro_z = sensor.gyro
    # print(x)
    # print(y)
    # print(z)
    if acc_x < 0:
        led1.value = True
        led2.value = True
    else:
        led3.value = True
        led4.value = True
    
    if acc_y < 0:
        led1.value = True
        led4.value = True
    else:
        led2.value = True
        led3.value = True

    time.sleep(1)

