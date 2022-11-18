## Instructions
| command | description | details |
| :--| :--  |:-- |
| 'record' | record|Running Python file 'sequencer.py' and store the record sequence in 'test.txt', push the 'BOOT' button in RP2040|
| 'repaly' | replay|Replay by reading the file with 'rb' format and replay the recorded sequence of LED lighting|
| 'normal' | replay in a normal speed|orginal speed which you could set when record (like 5 or 10 s)|
| 'slowdown' | replay in a slower speed|velocity = 0.5|
| 'speed up' | replay in a faster speed|velocity = 2|
| 'part' | replay only a part of original sequence|you could input any time slice you want|
| 't' | record(in c)|Store the record sequence in a buffer|
| 'p' | replay(in c)|Replay the latest recording in giving speed|
## What it does
We create two ways to record the boot button sequence and replay it. 

1. Use python and C to record and replay, python will save the sequence into a `.txt` file, and you could replay it in any speed and could choose any part to replay. Since it stored in PC, you could define how long you want to record, like 10s, 50s....

**Related folder:** `PC` and `sequencer`

2. Only use C in rp2040, you could record the latest sequence, and repaly it in 2/3/4... speed. But since it records in buffer and the SRAM of RP2040 is limitted, you may not record too long time. But in this way, you do not need run another .py file.

**Related folder:** `C`

## Demo

### Normal Speed

![](https://github.com/anniepan8215/ESE519_lab2B/blob/main/Media/Normal_Speed.gif)

### slowdown
![](https://github.com/anniepan8215/ESE519_lab2B/blob/main/Media/Lower_Speed.gif)

### speed up

![](https://github.com/anniepan8215/ESE519_lab2B/blob/main/Media/Faster_Speed.gif)

### part

The original recording time is 5s, and we replay it only from 1-4s.

![](https://github.com/anniepan8215/ESE519_lab2B/blob/main/Media/Cut_Period.gif)
