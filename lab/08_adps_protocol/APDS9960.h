#define ENABLE_REG _u(0x80)
#define ALS_REG _u(0x81)
#define PDATA_REG _u(0x9C)
#define CDATAL _u(0x94)
const int apds_addr = 0x39;

void APDS9960_init(Pio pio, uint sm);
void readProximity(PIO pio, uint sm, int32_t* proximity);
void readRGBC(PIO pio, uint sm, int32_t* r, int32_t* g, int32_t* b, int32_t* c);