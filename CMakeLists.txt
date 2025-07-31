cmake_minimum_required(VERSION 3.12)
project(BigInt CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(PUBLIC 
${CMAKE_SOURCE_DIR}/include
  PRIVATE
${CMAKE_SOURCE_DIR}/include/core_utils
)


add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-march=native;-Wall;-Wextra;-pedantic;-flto;-mavx2;-fomit-frame-pointer;-fno-stack-protector;-fno-unwind-tables;-fno-asynchronous-unwind-tables;-g3>")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(BigInt main.cpp ${SOURCES})


add_custom_target(run 

DEPENDS BigInt

COMMAND ${CMAKE_COMMAND} -E echo 

COMMAND ${CMAKE_CURRENT_BINARY_DIR}/BigInt

COMMAND ${CMAKE_COMMAND} -E echo 

WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

USES_TERMINAL
)
