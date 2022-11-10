add_executable(repl
repl.c) # CMAKE (target)

# pico_generate_pio_header(flashlight ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated) # PICO SDK (PIO)

target_sources(repl PRIVATE repl.c registers.h) # CMAKE -> C (compiler)
target_link_libraries(repl PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)

pico_enable_stdio_usb(repl 1) # PICO SDK (USB)
pico_enable_stdio_uart(repl 0) # PICO SDK (USB)

pico_add_extra_outputs(repl) # PICO SDK (UF2)


add_executable(repl_usb
repl_usb.c) # CMAKE (target)

# pico_generate_pio_header(flashlight ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated) # PICO SDK (PIO)

target_sources(repl_usb PRIVATE repl_usb.c) # CMAKE -> C (compiler)
target_link_libraries(repl_usb PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)

pico_enable_stdio_usb(repl_usb 1) # PICO SDK (USB)
pico_enable_stdio_uart(repl_usb 0) # PICO SDK (USB)

pico_add_extra_outputs(repl_usb) # PICO SDK (UF2)