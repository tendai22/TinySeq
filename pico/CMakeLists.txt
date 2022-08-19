cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

include(example_auto_set_url.cmake)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        -I../zForth/src/zforth
        -I../zForth/src/pico
        -I../xprintf/src
        )

# source code specifications

add_executable(tinyseq
        ./main-pico.c
        ../zForth/src/zforth/zforth.h
        ../zForth/src/zforth/zforth.c
        ../zForth/src/pico/zmain.c
        ../zForth/src/pico/zfconf.h
        ../zForth/forth/core.c
        ../xprintf/src/xprintf.h
        ../xprintf/src/xprintf.c
        )

target_compile_options(tinyseq
        PUBLIC -DMCU_PICO
        )


# pull in common dependencies
target_link_libraries(tinyseq pico_stdlib
        hardware_flash
        hardware_spi
        pico_stdio_uart
        )

# use UART
pico_enable_stdio_uart(tinyseq 0)
pico_enable_stdio_usb(tinyseq 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(tinyseq)

# add url via pico_set_program_url
example_auto_set_url(tinyseq)
