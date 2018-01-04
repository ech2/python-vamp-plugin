add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/catch)


set(VPLUG_TEST_SOURCES test_main.cpp test_cast.cpp)

add_executable(tests ${VPLUG_TEST_SOURCES})
target_include_directories(tests PUBLIC ../src/cpp)
target_link_libraries(tests PUBLIC
                      python_vamp_plugin
                      Catch
                      ${PYTHON_LIBRARIES}
                      /usr/lib/libvamp-sdk.so
                      /usr/lib/libvamp-hostsdk.so)


# Copy python files to the tests build directory

add_custom_command(TARGET tests PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/python
                   $<TARGET_FILE_DIR:tests>)

vplug_copy_python_package($<TARGET_FILE_DIR:tests>)
