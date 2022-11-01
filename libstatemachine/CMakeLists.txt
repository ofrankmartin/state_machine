cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME statemachine)

set (CMAKE_CXX_STANDARD 11)

project(${TARGET_NAME} C)

SET(SOURCES 
    state_ctrl.c
)

SET(HEADERS
    state_ctrl.h
)

add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${TARGET_NAME} PUBLIC .)
