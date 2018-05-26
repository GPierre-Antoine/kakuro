cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME kakuro)

project(${PROJECT_NAME})

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -Wextra --pedantic -Wno-comment -Werror")


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Module")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_FILES main.cpp src/Couleur.h src/kakuro_parser.h src/kakuro_parser.cpp src/Case.cpp src/Case.h src/csp/csp_variable.cpp src/csp/csp_variable.h src/csp/csp_constraint.cpp src/csp/csp_constraint.h src/csp/algorithm.cpp src/csp/algorithm.h src/csp/algo/algorithm_backtrack.cpp src/csp/algo/algorithm_backtrack.h src/ostream.h src/ostream.cpp src/csp/constraint/csp_constraint_sum.cpp src/csp/constraint/csp_constraint_sum.h src/csp/constraint/csp_constraint_difference.cpp src/csp/constraint/csp_constraint_difference.h src/csp/algo/record.cpp src/csp/algo/record.h src/csp/algo/record_type.h src/csp/compare_variables.cpp src/csp/compare_variables.h src/typedefs.h src/forward.h src/forward.cpp src/csp/algo/algorithm_forward_checking.cpp src/csp/algo/algorithm_forward_checking.h src/csp/solution.cpp src/csp/solution.h src/csp/heuristic.cpp src/csp/heuristic.h)

set(EXECUTABLE_NAME ${PROJECT_NAME})

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})