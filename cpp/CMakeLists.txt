cmake_minimum_required (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 

project (DoublePendulum)
add_executable(equation_test DoublePendEquationsTest.cpp DoublePendEquations.cpp FunctionWrapperRK4.cpp)
add_executable(time_test time_test.cpp DoublePendEquations.cpp FunctionWrapperRK4.cpp RK4_time.cpp)
add_executable(print_values print_values.cpp DoublePendEquations.cpp FunctionWrapperRK4.cpp RK4.cpp)