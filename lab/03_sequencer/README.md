# Instructions
| command | description | details |
| :--| :--  |:-- |
| 'record' | record(in python) |Running Python file 'sequencer.py' and store the record sequence in 'test.txt', push the 'BOOT' button in RP2040|
| 'repaly' | replay(in python) |Replay by reading the file with 'rb' format and replay the recorded sequence of LED lighting|
| 'r' | read address(in C)|read from \<address(8bits)\>|
| 'w' | write address(in C)|write from \<address(8bits)\>|

## Design considerations:
For a easier way reading address via serial, the group use 'line = recording.readline()' to get the sequence with 1 or 2 in 'b' byte form, the drawback of the method is that it may introduce blocking time when reading from serial. After testing, the RP2040 board can basically replay the input sequence correctly within the given period of time designed by users.

## Demo
too big to upload
