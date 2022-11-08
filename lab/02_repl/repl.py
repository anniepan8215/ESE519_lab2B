import usb.core
import usb.util



def send_data_block(uart, bytes, counter):
    length = len(bytes) - counter
    if length > 255: length = 255
    out = bytearray(length + 6)
    out[0] = 0x55                   # Head
    out[1] = 0x3C                   # Sync
    out[2] = 0x01                   # Block Type
    out[3] = length                 # Data length
    # Set the data
    for i in range(0, length):
        out[i + 4] = bytes[counter + i]
    # Compute checksum
    cs = 0
    for i in range (2, length + 6 - 2):
        cs += out[i]
    cs &= 0xFF
    out[length + 6 - 2] = cs        # Checksum
    out[length + 6 - 1] = 0x55      # Trailer
    counter += length
    r = uart.write(out)
    return counter

def await_ack(uart, timeout=2000):
    buffer = bytes()
    now = (time_ns() // 1000000)
    while ((time_ns() // 1000000) - now) < timeout:
        if uart.in_waiting > 0:
            buffer += uart.read(uart.in_waiting)
            if "\n" in buffer.decode():
                show_verbose("RX: " + buffer[:-1].decode())
                return True
    # Error -- No Ack received
    return False

def main():
    # find our device
    dev = usb.core.find(idVendor=0x0000, idProduct=0x0001)

    # was it found?
    if dev is None:
        raise ValueError('Device not found')

    # get an endpoint instance
    cfg = dev.get_active_configuration()
    intf = cfg[(0, 0)]

    outep = usb.util.find_descriptor(
        intf,
        # match the first OUT endpoint
        custom_match= \
            lambda e: \
                usb.util.endpoint_direction(e.bEndpointAddress) == \
                usb.util.ENDPOINT_OUT)

    inep = usb.util.find_descriptor(
        intf,
        # match the first IN endpoint
        custom_match= \
            lambda e: \
                usb.util.endpoint_direction(e.bEndpointAddress) == \
                usb.util.ENDPOINT_IN)

    assert inep is not None
    assert outep is not None

    test_string = "Hello World!"
    outep.write(test_string)
    from_device = inep.read(len(test_string))

    print("Device Says: {}".format(''.join([chr(x) for x in from_device])))