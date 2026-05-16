cmake_minimum_required(VERSION 3.20)
project(rlsl C)
set(CMAKE_C_STANDARD 11)

# directories
set(OBJ_DIR "${OUT_DIR}/obj")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CLI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cli")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

# source
file(GLOB_RECURSE RLSL_LIB_SRC "${SRC_DIR}/*.c")
file(GLOB_RECURSE RLSL_CLI_SRC "${CLI_DIR}/*c")
file(GLOB_RECURSE RLSL_TESTS_SRC "${TEST_DIR}/*c")

# binaries
set(RLSLC "rlslc")
set(RLSL_TESTS "rlsl_tests")
set(RLSL_LIB "rlsl")
add_executable(${RLSLC} ${RLSL_LIB_SRC} ${RLSL_CLI_SRC})
add_executable(${RLSL_TESTS} ${RLSL_LIB_SRC} ${RLSL_TESTS_SRC})
add_library(${RLSL_LIB} ${RLSL_LIB_SRC})

# incudes
target_include_directories(${RLSL_TESTS} PRIVATE PUBLIC ${SRC_DIR} ${TEST_DIR})
target_include_directories(${RLSLC} PRIVATE PUBLIC ${SRC_DIR} ${CLI_DIR})
target_include_directories(${RLSL_LIB} PRIVATE PUBLIC ${SRC_DIR})