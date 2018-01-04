//
// Created by ech on 12/21/17.
//

#ifndef PYTHON_VAMP_PLUGIN_PYTHONPLUGINADAPTER_H
#define PYTHON_VAMP_PLUGIN_PYTHONPLUGINADAPTER_H

#include "common.h"
#include <vamp-sdk/PluginAdapter.h>


namespace vplug {

using namespace vplug::util;

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
