#include "PythonPlugin.h"
#include <list>
#include <map>
#include "PythonCasting.h"
#include "pybind11/numpy.h"

using namespace vplug;

PythonPlugin::PythonPlugin(float inputSampleRate, py::object pyClass)
        : Vamp::Plugin(inputSampleRate) {
    try {
        pyobj = pyClass(m_inputSampleRate);
    } catch (py::error_already_set &e) {
        py::print(e.what());
    }
}

PythonPlugin::~PythonPlugin() = default;


/* PluginBase */

bool PythonPlugin::initialise(size_t inputChannels_, size_t stepSize_, size_t blockSize_) {
    callPythonMethod("initialise", inputChannels_, stepSize_, blockSize_);
    inputChannels = inputChannels_;
    stepSize = stepSize_;
    blockSize = blockSize_;
}

void PythonPlugin::reset() {
    callPythonMethod("reset");
}

Vamp::Plugin::InputDomain PythonPlugin::getInputDomain() const {
    int d = callPythonMethod<int>("get_input_domain").value_or(0);
    if (d == 0) {
        return Vamp::Plugin::TimeDomain;
    } else {
        return Vamp::Plugin::FrequencyDomain;
    }
}

Vamp::Plugin::OutputList PythonPlugin::getOutputDescriptors() const {
    using VampOutputDescriptor = Vamp::Plugin::OutputDescriptor;
    auto d_py = callPythonMethod<std::list<py::object>>("get_output_descriptors")
            .value_or(std::list<py::object>());
    auto d_vec = std::vector<VampOutputDescriptor>();
    for (const auto &i : d_py) {
        auto d = util::fromPyObj<VampOutputDescriptor>(i);
        if (d) {
            d_vec.push_back(d.value());
        } else {
            std::cerr << "Skipped output descriptor " << std::endl;
            py::print(i);
        }
    }
    return d_vec;
}

Vamp::Plugin::FeatureSet PythonPlugin::process(const float *const *inputBuffers,
                                               Vamp::RealTime timestamp) {
    using PyFeatureSet = std::map<int, std::list<py::object>>;

    py::list chanlist(inputChannels);
    for (int i = 0; i < inputChannels; i++) {
        auto *buf = (void *) inputBuffers[i];
        auto bufInfo = py::buffer_info(
                buf,
                sizeof(float),
                py::format_descriptor<float>::format(),
                (size_t) 1,
                std::vector<size_t>{blockSize, 0},
                std::vector<size_t>{sizeof(float) * blockSize, 0}
        );
        auto dt = py::dtype(bufInfo);
        py::array arr(dt, bufInfo.shape, bufInfo.strides, bufInfo.ptr);
        chanlist.append(arr);
    }

    auto pyres = callPythonMethod<PyFeatureSet>("process", chanlist, timestamp.sec, timestamp.nsec)
            .value_or(PyFeatureSet());

    Vamp::Plugin::FeatureSet res;
    for (auto const &i : pyres) {
        std::vector<Feature> fvec;
        for (auto const &o : i.second) {
            auto f = util::fromPyObj<Feature>(o);
            if (f) {
                fvec.push_back(f.value());
            } else {
                std::cerr << "Skipped output descriptor" << std::endl;
                py::print(f);
            }
        }
        res[i.first] = fvec;
    };

    return res;
}


Vamp::Plugin::FeatureSet PythonPlugin::getRemainingFeatures() {
    using PyFeatureSet = std::map<int, std::list<py::object>>;

    auto pyres = callPythonMethod<PyFeatureSet>("get_remaining_features").value_or(PyFeatureSet());

    Vamp::Plugin::FeatureSet res;
    for (auto const &i : pyres) {
        std::vector<Feature> fvec;
        for (auto const &o : i.second) {
            auto f = util::fromPyObj<Feature>(o);
            if (f) {
                fvec.push_back(f.value());
            } else {
                std::cerr << "Skipped output descriptor" << std::endl;
                py::print(f);
            }
        }
        res[i.first] = fvec;
    };

    return res;
}

/* PluginBase */

std::string PythonPlugin::getName() const {
    auto name = callPythonMethod<std::string>("get_name");
    return name.value_or(std::string());
}

std::string PythonPlugin::getIdentifier() const {
    auto id = callPythonMethod<std::string>("get_identifier");
    return id.value_or(std::string());
}

std::string PythonPlugin::getDescription() const {
    auto d = callPythonMethod<std::string>("get_description");
    return d.value_or(std::string());
}

std::string PythonPlugin::getMaker() const {
    auto m = callPythonMethod<std::string>("get_maker");
    return m.value_or(std::string());
}

std::string PythonPlugin::getCopyright() const {
    auto c = callPythonMethod<std::string>("get_copyright");
    return c.value_or(std::string());
}

int PythonPlugin::getPluginVersion() const {
    return callPythonMethod<int>("get_plugin_version").value_or(0);
}

/* Python call helpers */

template<typename ...Args>
void PythonPlugin::callPythonMethod(const char *methodName, Args &&...args) {
    try {
        pyobj.attr(methodName)(args...);
    } catch (py::error_already_set &e) {
        std::cerr << e.what() << std::endl;
    }
}


template<typename RetType, typename ...Args>
opt<RetType> PythonPlugin::callPythonMethod(
        const char *methodName, Args &&...args) {
    try {
        py::object o = pyobj.attr(methodName)(args...);
        return opt<RetType>(o.cast<RetType>());
    } catch (py::error_already_set &e) {
        std::cerr << e.what() << std::endl;
    }
    return opt<RetType>();
}

template<typename RetType, typename... Args>
opt<RetType> PythonPlugin::callPythonMethod(
        const char *methodName, Args &&...args) const {
    return const_cast<PythonPlugin *>(this)->callPythonMethod<RetType>(methodName, args...);
}

