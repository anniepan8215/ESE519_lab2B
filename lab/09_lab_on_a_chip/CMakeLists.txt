cmake_minimum_required(VERSION 3.13) # CMAKE (heading)
include(pico_sdk_import.cmake) # CMAKE -> PICO SDK (include)

project(REPL C CXX ASM) # CMAKE ("project")
pico_sdk_init() # PICO SDK (initialization)


add_executable(Part9)

pico_generate_pio_header(Part9 ${CMAKE_CURRENT_LIST_DIR}/i2c.pio ws2812.pio)

target_sources(Part9 PRIVATE
        main.c
        sequencer.c
        pio_i2c.c
        pio_i2c.h
        APDS9960.c
        APDS9960.h
        neopixel.c
        neopixel.h
        )

pico_enable_stdio_usb(Part9 1) # PICO SDK (USB)
pico_enable_stdio_uart(Part9 0) # PICO SDK (USB)
target_link_libraries(Part9 PRIVATE pico_stdlib hardware_pio hardware_dma pico_multicore)
pico_add_extra_outputs(Part9)


