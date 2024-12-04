cmake_minimum_required(VERSION 3.0)
project(conjugate-gradient-method)

include_directories("src")

set(SRC_LIST 
    src/area.cpp
    src/area.hpp
    src/function.cpp
    src/function.hpp
    src/optimization_method.hpp
    src/stop_criterion.hpp
    src/Vector.hpp
    src/main.cpp
)

add_executable(main ${SRC_LIST})