cmake_minimum_required(VERSION 3.29)
project(ecetype C)

set(CMAKE_C_STANDARD 11)

add_executable(ecetype main.c
        vaisseau.c
        vaisseau.h
        interface.c
        interface.h
        ennemis.c
        ennemis.h)
target_link_libraries(ecetype -lmingw32 -lalleg44)
