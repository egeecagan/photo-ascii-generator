cmake_minimum_required(VERSION 3.10)

project(photo-ascii-generator LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(generator src/main.c src/img_reader.c src/img_writer.c)
target_include_directories(generator PRIVATE src libs)