cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME kakuro)

project(${PROJECT_NAME})

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -Wextra --pedantic -Wno-comment -Werror")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif (CMAKE_BUILD_TYPE MATCHES "Debug")


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Module")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_FILES main.cpp src/Couleur.h src/parser.h src/parser.cpp src/Case.cpp src/Case.h src/csp/csp_variable.cpp src/csp/csp_variable.h src/csp/csp_constraint.cpp src/csp/csp_constraint.h src/csp/algorithm.cpp src/csp/algorithm.h src/csp/algo/algorithm_backtrack.cpp src/csp/algo/algorithm_backtrack.h)

set(EXECUTABLE_NAME ${PROJECT_NAME})

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})