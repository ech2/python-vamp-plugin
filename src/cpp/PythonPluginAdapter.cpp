//
// Created by ech on 12/21/17.
//

#include "PythonPluginAdapter.h"
#include "PythonPlugin.h"

using namespace vplug;

PythonPluginAdapter::PythonPluginAdapter(py::object plugClass) : plugClass(plugClass) {}

PythonPluginAdapter::~PythonPluginAdapter() = default;

Vamp::Plugin *PythonPluginAdapter::createPlugin(float inputSampleRate) {
    auto p = new PythonPlugin(inputSampleRate, plugClass);
    auto plugin = dynamic_cast<Vamp::Plugin *>(p);
    if (!plugin) {
        std::cerr << "Error creating Python plugin from class "
                  << std::string(py::str(plugClass))
                  << std::endl;
        delete p;
        return 0;
    }
    return plugin;
}

