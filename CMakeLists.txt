cmake_minimum_required(VERSION 3.12)

set (CMAKE_CXX_STANDARD 11)

set(TARGET_NAME state_machine)

project(${TARGET_NAME} C)

add_subdirectory(libstatemachine)
add_subdirectory(state_machine_app)
