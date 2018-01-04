#ifndef PYTHON_VAMP_PLUGIN_COMMON_H
#define PYTHON_VAMP_PLUGIN_COMMON_H

#include <experimental/optional>
#include <pybind11/pybind11.h>
#include <vamp-sdk/vamp-sdk.h>

namespace vplug {
namespace util {

using VampFeature = Vamp::Plugin::Feature;
using VampRealTime = Vamp::RealTime;
using VampOutputDescriptor = Vamp::Plugin::OutputDescriptor;
template<typename T> using opt = std::experimental::optional<T>;
namespace py = pybind11;

}
}

#endif
