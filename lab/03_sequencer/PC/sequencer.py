import serial
import time
import io


def file_to_list(file_path, data_list):
    print("get data")
    with open(file_path, 'rb+') as f:
        data = f.readline()
        while data:
            data_list.append(data.decode().replace('\n', ''))
            data = f.readline()
    f.close()
    print("write to list")
    return data_list


def slowdown(data_list, data_new):
    for data in data_list:
        data_new.append(data)
        data_new.append(data)
    return data_new


def speedup(data_list, data_new):
    for i in range(len(data_list)):
        if i % 2 == 0:
            data_new.append(data_list[i])
    return data_new


def part(data_list, data_new, original, begin, end):
    i = len(data_list)/original * begin
    j = len(data_list)/original * end
    for a in range(len(data_list)):
        if i < a < j:
            data_new.append(data_list[a])
    return data_new


if __name__ == "__main__":
    print("init")
    pressed = b'p'
    no_press = b'n'
    data_in = []
    # Write the corresponding test file to the folder one level above the current directory
    path = './test.txt'
    recent = 5
    try:
        qtpy = serial.Serial('/dev/tty.usbmodem2101', 115200)
        print(qtpy.name)
        sio = io.TextIOWrapper(io.BufferedRWPair(qtpy, qtpy))
    except Exception as e:
        print("COM can not open,Exception=", e)

    while True:
        command = input()
        if command == 'record':
            print("how long you want to record?")
            period = input()
            period = int(period)
            recent = period
            qtpy.write(b's')
            print("read from qtpy")
            start = time.time()
            while time.time() - start < period:
                line = qtpy.readline()
                line = line.decode().replace('\r\n', '\n')
                data_in.append(line)
            qtpy.write(b'N')
            with open(path, 'wb+') as f:
                for item in data_in:
                    f.write(item.encode('utf-8'))
                f.close()
            print("success write to txt")
            print("recording time is: " + str(period) + " s")

        if command == 'replay':
            data_out = []
            file_to_list(path, data_out)
            print("how you want to replay? normal/slowdown/speed up/part\n")
            ans = input()
            data_final = []
            if ans == 'normal':
                data_final = data_out
            if ans == 'slowdown':
                data_final = slowdown(data_out, data_final)
            if ans == 'speed up':
                data_final = speedup(data_out, data_final)
            if ans == 'part':
                print("original time is: " + str(recent) + "s")
                print("the begining time you want is: ")
                begint = input()
                begint = int(begint)
                print("the end time you wand is: ")
                endt = input()
                endt = int(endt)
                data_final = part(data_out,data_final,recent,begint,endt)
            print("begin replay")
            qtpy.write(b'g')
            for item in data_final:
                if item == '1':
                    qtpy.write(no_press)
                if item == '2':
                    qtpy.write(pressed)
            qtpy.write(b'N')
            print("replay successfully")
