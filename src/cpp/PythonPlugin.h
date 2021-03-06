//
// Created by ech on 12/13/17.
//

#ifndef PYTHON_VAMP_PLUGIN_PYPLUGIN_H
#define PYTHON_VAMP_PLUGIN_PYPLUGIN_H

#include <experimental/optional>
#include "common.h"
#include "PythonCasting.h"

namespace vplug {

using namespace vplug::util;

class PythonPlugin : public Vamp::Plugin {
public:
    PythonPlugin(float inputSampleRate, py::object pyClass);

    ~PythonPlugin() override;

    /* Plugin */

    std::string getIdentifier() const override;

    bool initialise(size_t inputChannels_, size_t stepSize_, size_t blockSize_) override;

    void reset() override;

    InputDomain getInputDomain() const override;

    OutputList getOutputDescriptors() const override;

    FeatureSet process(const float *const *inputBuffers, Vamp::RealTime timestamp) override;

    FeatureSet getRemainingFeatures() override;

    /* PluginBase */

    std::string getName() const override;

    std::string getDescription() const override;

    std::string getMaker() const override;

    std::string getCopyright() const override;

    int getPluginVersion() const override;

protected:
    py::object pyobj;

    template<typename... Args>
    void callPythonMethod(const char *methodName, Args &&...args);

    template<typename RetType, typename... Args>
    opt<RetType> callPythonMethod(const char *methodName, Args &&...args);

    template<typename RetType, typename... Args>
    opt<RetType> callPythonMethod(const char *methodName, Args &&...args) const;

    size_t inputChannels;
    size_t stepSize;
    size_t blockSize;
};

}

#endif //PYTHON_VAMP_PLUGIN_PYPLUGIN_H
