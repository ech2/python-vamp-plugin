add_library(
        python_vamp_plugin STATIC
        PythonPlugin.h
        PythonPlugin.cpp
        PythonCasting.h
        PythonPluginAdapter.h
        PythonPluginAdapter.cpp
        plugin.cpp common.h)
