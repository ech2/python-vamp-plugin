//
// Created by ech on 12/21/17.
//

#ifndef PYTHON_VAMP_PLUGIN_PYTHONPLUGINADAPTER_H
#define PYTHON_VAMP_PLUGIN_PYTHONPLUGINADAPTER_H

#include "vamp-sdk/PluginAdapter.h"
#include "pybind11/pybind11.h"


namespace vplug {

namespace py = pybind11;

class PythonPluginAdapter : public Vamp::PluginAdapterBase {
public:
    explicit PythonPluginAdapter(py::object plugClass);

    ~PythonPluginAdapter() override;

    const py::object plugClass;
protected:

    Vamp::Plugin *createPlugin(float inputSampleRate) override;

};

}

#endif //PYTHON_VAMP_PLUGIN_PYTHONPLUGINADAPTER_H
