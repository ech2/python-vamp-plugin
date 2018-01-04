cmake_minimum_required(VERSION 3.9)
project(python-vamp-plugin)

set(CMAKE_CXX_STANDARD 14)
set(PYBIND11_CPP_STANDARD -std=c++14)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(pybind11 REQUIRED)

include_directories(
        ${PYTHON_INCLUDE_DIRS}
        /usr/include)

add_subdirectory(src/cpp)
add_subdirectory(src/python)
add_subdirectory(test)


