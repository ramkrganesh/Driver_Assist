cmake_minimum_required(VERSION 3.10)

project(Driver_Assist NONE)

set(ARDUINO_FQBN "arduino:avr:nano")

file(GLOB_RECURSE ALL_SOURCE_FILES CONFIGURE_DEPENDS *.h *.ino *.cpp)

add_custom_target(Build_Driver_Assist ALL
    COMMAND arduino-cli compile
    --fqbn ${ARDUINO_FQBN}
    --library "00_CommonLib"
    --library "01_9960_Driver"
    ${CMAKE_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building Driver Assist Project..."
)