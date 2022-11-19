#define ENABLE_REG _u(0x80)
#define ALS_REG _u(0x81)
#define PDATA_REG _u(0x9C)
#define CDATAL _u(0x94)
const int apds_addr = 0x39;

void APDS9960_init(PIO pio, uint sm);
void readProximity(PIO pio, uint sm, uint32_t* proximity);
void readRGBC(PIO pio, uint sm, uint32_t* r, uint32_t* g, uint32_t* b, uint32_t* c);