cmake_minimum_required(VERSION 3.20)
project(rlsl_tests C)
set(CMAKE_C_STANDARD 11)

# directories
set(OBJ_DIR "${OUT_DIR}/obj")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

add_subdirectory("${CMAKE_SOURCE_DIR}/.." rlsl)

# source
file(GLOB_RECURSE RLSL_TEST_SRC "${SRC_DIR}/*.c")
set(SRC ${RLSL_TEST_SRC})

# binaries
set(EXECUTABLE rlsl_tests)
add_executable(${EXECUTABLE} ${SRC})

# includes
target_include_directories(${EXECUTABLE} PRIVATE ${SRC_DIR})

# library linking
target_link_libraries(${EXECUTABLE} PRIVATE rlsl)