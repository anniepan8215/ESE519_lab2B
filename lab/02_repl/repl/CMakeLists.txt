add_executable(repl repl.c) # CMAKE (target)


target_sources(repl PRIVATE repl.c) # CMAKE -> C (compiler)
target_link_libraries(repl PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)

pico_enable_stdio_usb(repl 1) # PICO SDK (USB)
pico_enable_stdio_uart(repl 0) # PICO SDK (USB)

pico_add_extra_outputs(repl) # PICO SDK (UF2)