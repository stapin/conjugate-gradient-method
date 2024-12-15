cmake_minimum_required(VERSION 3.0)
project(conjugate-gradient-method)

include_directories("src")

set(SRC_LIST 
    src/area.cpp
    src/area.hpp
    src/function.cpp
    src/function.hpp
    src/optimization_method.hpp
    src/optimization_method.cpp
    src/optim_method_cli.hpp
    src/optim_method_cli.cpp
    src/stop_criterion.hpp
    src/stop_criterion.cpp
    src/Vector.hpp
    src/Vector.cpp
    src/main.cpp
)

add_executable(main ${SRC_LIST})