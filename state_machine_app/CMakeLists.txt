cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME state_machine_app)

set (CMAKE_CXX_STANDARD 11)

project(${TARGET_NAME} C)

SET(SOURCES 
    main.c
    states/state_user_setup.c
    states/state_idle.c
    )

set(HEADERS
    states/state_user_setup.h
    states/state_idle.h
    )

add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${TARGET_NAME} statemachine)
