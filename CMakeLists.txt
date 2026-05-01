cmake_minimum_required(VERSION 3.20)
project(rlsl C)
set(CMAKE_C_STANDARD 11)

# directories
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(OBJ_DIR "${OUT_DIR}/obj")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# source
file(GLOB_RECURSE RLSL_SRC "${SRC_DIR}/*.c")
set(SRC ${RLSL_SRC})

# binaries
set(LIBRARY "rlsl")
add_library(${LIBRARY} ${SRC})

# incudes
target_include_directories(${LIBRARY} PRIVATE ${LIB_DIR} PUBLIC ${SRC_DIR})