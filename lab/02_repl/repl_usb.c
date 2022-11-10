#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include <tusb.h>

#define numChars  32
const uint LED_PIN = 25;
bool ledVal = false;

char receivedChars[numChars];
bool newData = false;

void recvWithStartEndMarkers();
void showNewData();
unsigned long hash(unsigned char *str);

int main() {
    stdio_init_all();

    while (!tud_cdc_connected()) { sleep_ms(100);  }

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    int i=0;
    while (true){
        recvWithStartEndMarkers();
        if(newData){
            showNewData();
            newData = false;
        }
    }
    return 0;
}

int i=0;
void recvWithStartEndMarkers() {
    static bool recvInProgress = false;
    static int8_t ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    i++;
    int16_t rc = getchar_timeout_us(1);

    while (rc != PICO_ERROR_TIMEOUT && newData == false) {

        if (recvInProgress == true) {
            //Reset index if a new start marker comes in
            if (rc == startMarker) {
            recvInProgress = true;
            ndx = 0;
            }
            //End of the packet
            else if (rc == endMarker) {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
            //Append any data between start and end markers
            else {
                receivedChars[ndx] = (char)rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
            ndx = 0;
        }

        rc = getchar_timeout_us(10);
    }
}	

void showNewData() {
    printf("This just in ... %s  call count = %d\n", receivedChars, i);
    ledVal = !ledVal;
    gpio_put(LED_PIN, ledVal);

    char string[numChars];
    strcpy(string, receivedChars);
    char *found;

    found = strtok(string,",");
    while(found){
		printf("\t'%s'\n",found);
        found = strtok(NULL,",");
    }
}