
from time import sleep
import serial.tools.list_ports


def recv(serial):
    global data
    while True:
        #read up to one hundred bits
        data = serial.read(100)
        if data == '':
            continue
        else:
            break
        sleep(0.02)
    return data


if __name__ == '__main__':

    press_button = b'0x00000001'
    no_button = b'0x00000000'
    pressed = b'p'
    no_press = b'n'
    #Write the corresponding test file to the folder one level above the current directory
    path = './test.txt'
    port_list = list(serial.tools.list_ports.comports())
    #specify the corresponding parameters used for opening the serial port
    ser = serial.Serial()
    ser.port = 'COM10'
    ser.baudrate = 115200
    ser.bytesize = serial.EIGHTBITS
    ser.parity = serial.PARITY_NONE
    ser.xonxoff = 0
    ser.rtscts = 0
    ser.dsrdtr = 0
    ser.stopbits = 1
    ser.timeout = 1
    ser.open()
    i = 0
    if ser.isOpen():
        #Opens a file for both writing and reading in binary format. Overwrites the existing file if the file exists. If the file does not exist, creates a new file for reading and writing.
        recording = open(path, 'wb+')
        print(ser.name + ' is open...')
        while i <= 100:
            data = recv(ser)
            #Write the read data from serial into the file 'test.txt'
            recording.write(data)
            i = i + 1
        recording.close()
        print("beginning")
        recording = open(path,'rb+')
        #reads up to one line
        line = recording.readline()[0:10]
        #[0:10] specify the certain string 
        #corresponding to 0x(8 bits following)
        while line:
        #if we read a line equals to 0x00000001
        #write the corresponding file into serial port
        #light the LED as the effect of the 'BOOT' button
            if line == press_button:
                ser.write(pressed)
            if line == no_button:
                ser.write(no_press)
            line = recording.readline()[0:10]
            sleep(0.01)
        ser.close()
        recording.close()
