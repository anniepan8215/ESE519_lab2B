### TODO:

Create a 'sequencer' that allows you to record BOOT button presses and play them on the Neopixel, and also play a sequence of read/write commands. You should be able to:
- record at a least a few seconds of button input to your RP2040 (in RAM)
- replay a recorded sequence on your NeoPixel
- loop a recording
- save a recording to your laptop (the Python Serial library is one way to do this)
- play a recording from your laptop
- record 'macros' (a sequence of console commands) based on keystrokes in your serial console
- hand-edit a list of register read/write commands on your laptop, and play them on the RP2040
- include multiple I/O sources in a recording, and remap among the following:
    - inputs: BOOT button, console commands, register read/write commands
    - outputs: neopixel color, neopixel brightness, data over serial, register read/write commands

-----
# commands
| functions |command |
| :--| :--  |
| record |Running Python file 'main.py' and store the record sequence in 'test.txt'|
| replay |Replay by reading the file with 'rb' format and replay the recorded sequence of LED lighting|
| read address|r \<address(8bits)\>|
| write address|w \<address(8bits)\>|
|Input gpio|< \<gpio>|
|Output gpio|> \<gpio>|

### Design considerations:
For a easier way reading address via serial, the group use 'line = recording.readline()[0:10]' to get the sequence with 1 or 0 in 'b' byte form, the drawback of the method is that it may introduce blocking time when reading from serial. After testing, the RP2040 board can basically replay the input sequence correctly within the given period of time designed by users. (Sequence: Green-> Red-> Blue-> White).

