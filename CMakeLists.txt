cmake_minimum_required(VERSION 2.8)

project(io_fat_lib)

add_subdirectory(tests)

file(GLOB FAT_IO_LIB_SRCS "fat*.c")
add_library(fat_io_lib ${FAT_IO_LIB_SRCS})
