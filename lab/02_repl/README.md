### TODO:

Create a REPL to let you read and write RP2040 registers from a console. You should be able to:
- select any 32-bit address to read/write (even if not a valid RP2020 address)
- read/write any 32-bit value to this address
- read/write using any of the atomic bit-setting aliases and a 32-bit mask


`.\Code`: Question Q2 code <br>

# REPL
we use `getchar_timeout_us(0)` to achieve read address and value from keyboard. After access the specifc register we then decide to read and write. The final results shown below

### write to register

<img width="330" alt="write" src="https://user-images.githubusercontent.com/87698138/200715962-18c86d05-3e30-4c8b-ab70-64bf34d72705.png">

### read a register

<img width="366" alt="read" src="https://user-images.githubusercontent.com/87698138/200716030-d3833c70-d1b5-485d-8c88-31ea7531d1bc.png">

### Question

Sometimes when we read value from the register we will get some wired string, may need another function to test it.
