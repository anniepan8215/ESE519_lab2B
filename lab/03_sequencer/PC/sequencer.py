import serial
from time import sleep
import string
import time
import io


# def recv(ser,sio):
#     # global data
#     ser.write(b'b')
#     info = ""
#     # ser.flush()
#     data = ser.readline()
#     print(data)
#     sleep(0.001)
#     data = ser.readline()
#     print(data)
#     sleep(0.001)
#     # info = hex(data.decode().replace('\r\n',''))
#     # while line in data:
#     #     # print(1)
#     #     #read up to one hundred bits
#     #     # sio.flush()
#     #     # data = ser.readlines()
#     #     # print(data)
#     #     line = line.decode().replace('\r\n','')
#     #     # data = data.decode()
#     #     print(line)
#     #     if data == 's' or 'start':
#     #         continue
#     #     elif data == 'END':
#     #         break
#     #     else:
#     #         info += str(line)
#     #         print(info)
#     #         # sleep(0.02)
#     return info


def recv(ser):
    global data
    while True:
        #read up to one hundred bits
        data = ser.read(14)
        # data = serial.readline()
        if data == '':
            continue
        else:
            break
        sleep(0.02)
    return data


if __name__ == "__main__":
    print("init")
    press_button = b'0x00000001'
    no_button = b'0x00000000'
    pressed = b'p'
    no_press = b'n'
    i=0
    # Write the corresponding test file to the folder one level above the current directory
    path = './test.txt'
    try:
        qtpy = serial.Serial('/dev/tty.usbmodem2101', 115200)
        print(qtpy.name)
        sio = io.TextIOWrapper(io.BufferedRWPair(qtpy, qtpy))
    except Exception as e:
        print("COM can not open,Exception=", e)
    while True:
        command = input()
        if command == 'record':
            # print("how long you want to record?")
            # period = input()
            qtpy.write(b's')
            print("write to qtpy")
            recording = open(path, 'wb+')
            while i <= 100:
                # data = recv(qtpy)
                data = qtpy.readline()
                # Write the read data from serial into the file 'test.txt'
                recording.write(data)
                i = i + 1
            recording.close()
            # recording = open(path, 'wb+')
            # with open(path, 'wb+') as recording:
            #     qtpy.write(b's')
            #     while i <= int(period):
            #         start = time.time()
            #         data = recv(qtpy,sio)
            #         end = time.time()-start
            #         # Write the read data from serial into the file 'test.txt'
            #         recording.write(data)
            #         i = i + 1
            #         print(i, ' ', int(period))
            #         qtpy.write(b'E')
            #     qtpy.write(b'N')
            #     recording.close()
        if command == 'replay':
            print("beginning")
            recording = open(path, 'rb+')
            # reads up to one line
            line = recording.readline()[0:10]
            # [0:10] specify the certain string
            # corresponding to 0x(8 bits following)
            while line:
                # if we read a line equals to 0x00000001
                # write the corresponding file into serial port
                # light the LED as the effect of the 'BOOT' button
                if line == press_button:
                    qtpy.write(pressed)
                if line == no_button:
                    qtpy.write(no_press)
                line = recording.readline()[0:10]
                sleep(0.01)
            qtpy.close()
            recording.close()
