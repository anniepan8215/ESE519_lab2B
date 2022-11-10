### TODO:

Create a REPL to let you read and write RP2040 registers from a console. You should be able to:
- select any 32-bit address to read/write (even if not a valid RP2020 address)
- read/write any 32-bit value to this address
- read/write using any of the atomic bit-setting aliases and a 32-bit mask


`.\Code`: Question Q2 code <br>

# REPL
we use `getchar_timeout_us(0)` to achieve read address and value from keyboard. After access the specifc register we then decide to read and write and then render the final results to console. The final results shown below

### read a register

<img width="294" alt="read" src="https://user-images.githubusercontent.com/87698138/201214196-9c81d8cb-4a1e-40d5-a19a-7332d002370a.png">


### write to register

<img width="281" alt="write" src="https://user-images.githubusercontent.com/87698138/201214283-75306d2f-06c8-4700-ba77-dd7b8be5f190.png">

