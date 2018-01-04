set(VPLUG_PYTHON_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

function(vplug_copy_python_package dest_dir)
    add_custom_command(TARGET tests PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${VPLUG_PYTHON_SRC_DIR}/vplug
            ${dest_dir}/vplug)
endfunction()
