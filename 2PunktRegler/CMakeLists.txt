cmake_minimum_required(VERSION 4.3)
project(2PunktRegler C)

set(CMAKE_C_STANDARD 99)

add_executable(2PunktRegler temperatur.c heizung.c
        heizung.c)
