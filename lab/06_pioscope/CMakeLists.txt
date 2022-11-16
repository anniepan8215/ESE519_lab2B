cmake_minimum_required(VERSION 3.13) # CMAKE (heading)
include(pico_sdk_import.cmake) # CMAKE -> PICO SDK (include)

project(REPL C CXX ASM) # CMAKE ("project")
pico_sdk_init() # PICO SDK (initialization)

add_executable(Part6) # CMAKE (target)

pico_generate_pio_header(Part6 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated) # PICO SDK (PIO)

target_sources(Part6 PRIVATE logicAnalyzer.c registers.h) # CMAKE -> C (compiler)
target_link_libraries(Part6 PRIVATE pico_stdlib hardware_pio hardware_dma hardware_i2c) # CMAKE -> C (linker)

pico_enable_stdio_usb(Part6 1) # PICO SDK (USB)
pico_enable_stdio_uart(Part6 0) # PICO SDK (USB)

pico_add_extra_outputs(Part6) # PICO SDK (UF2)
