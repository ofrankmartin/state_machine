cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME test_jlmonline)

project(${TARGET_NAME} C)

SET(SOURCES 
    main.c
    libsmachine/smachine.c
    states/state_user_setup.c
    states/state_idle.c
    )

add_executable(${TARGET_NAME} ${SOURCES})
