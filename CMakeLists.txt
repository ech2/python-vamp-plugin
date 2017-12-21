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

add_library(
        python_vamp_plugin STATIC
        src/cpp/PythonPlugin.cpp
        src/cpp/PythonPlugin.h
        src/cpp/PythonCasting.h
        src/cpp/PythonPluginAdapter.cpp
        src/cpp/PythonPluginAdapter.h src/cpp/plugin.cpp)


add_executable(
        simple_test
        test/simple_test.cpp
        src/cpp/PythonPlugin.h)


target_link_libraries(
        simple_test PUBLIC python_vamp_plugin
        ${PYTHON_LIBRARIES}
        /usr/lib/libvamp-sdk.so
        /usr/lib/libvamp-hostsdk.so)



configure_file(
        src/python/vplug/__init__.py
        ${CMAKE_CURRENT_BINARY_DIR}/vplug/__init__.py
        COPYONLY)
configure_file(
        src/python/vplug/vampinterface.py
        ${CMAKE_CURRENT_BINARY_DIR}/vplug/vampinterface.py
        COPYONLY)
