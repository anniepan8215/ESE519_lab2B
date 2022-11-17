add_executable(pioscope)

target_sources(pioscope PRIVATE pioscope.c)

target_link_libraries(pioscope PRIVATE pico_stdlib hardware_pio hardware_dma hardware_i2c)

pico_add_extra_outputs(pioscope)

pico_enable_stdio_usb(pioscope 1) # PICO SDK (USB)
pico_enable_stdio_uart(pioscope 0) # PICO SDK (USB)

