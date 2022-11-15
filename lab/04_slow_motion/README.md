## Instructions
| command | description | details |
| :--| :--  |:-- |
| 'record' | record|Running Python file 'sequencer.py' and store the record sequence in 'test.txt', push the 'BOOT' button in RP2040|
| 'repaly' | replay|Replay by reading the file with 'rb' format and replay the recorded sequence of LED lighting|
| 'normal' | replay in a normal speed|orginal speed which you could set when record (like 5 or 10 s)|
| 'slowdown' | replay in a slower speed|velocity = 0.5|
| 'speed up' | replay in a faster speed|velocity = 2|
| 'part' | replay only a part of original sequence|you could input any time slice you want|

## Demo

### Normal Speed

![](Media\Normal_Speed.gif)

### slowdown
![](Media\Lower_Speed.gif)



### speed up

![](Media\Faster_Speed.gif)

### part

The original recording time is 5s, and we replay it only from 1-4s.

![](Media\Cut_Period.gif)
