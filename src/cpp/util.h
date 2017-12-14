//
// Created by ech on 12/13/17.
//

#ifndef PYTHON_VAMP_PLUGIN_UTIL_H
#define PYTHON_VAMP_PLUGIN_UTIL_H

#include <list>
#include <vector>
#include "pybind11/cast.h"
#include "vamp-sdk/vamp-sdk.h"
#include "PythonPlugin.h"

namespace vplug {
namespace util {

using VampFeature = Vamp::Plugin::Feature;
using VampRealTime = Vamp::RealTime;
using VampOutputDescriptor = Vamp::Plugin::OutputDescriptor;
template<typename T> using opt = std::experimental::optional<T>;
namespace py = pybind11;


template<typename T>
static opt<T> fromPyObj(const py::object &o);


template<>
opt<VampFeature> fromPyObj<VampFeature>(const py::object &o) {
    try {
        auto v = VampFeature();
        v.hasTimestamp = o.attr("has_timestamp").cast<bool>();
        v.timestamp = o.attr("timestamp").cast<VampRealTime>();
        v.hasDuration = o.attr("has_duration").cast<bool>();
        v.duration = o.attr("duration").cast<VampRealTime>();
        auto values = o.attr("values").cast<std::list<float>>();
        v.values = std::vector<float>{
                std::make_move_iterator(values.begin()),
                std::make_move_iterator(values.end())
        };
        v.label = o.attr("label").cast<std::string>();
        return opt<VampFeature>(v);
    } catch (py::cast_error &e) {
        std::cerr << e.what() << std::endl;
        return opt<VampFeature>();
    } catch (py::error_already_set &e) {
        std::cerr << e.what() << std::endl;
        return opt<VampFeature>();
    }
}


template<>
opt<VampOutputDescriptor> fromPyObj<VampOutputDescriptor>(const py::object &o) {
    try {
        auto v = VampOutputDescriptor();
        v.identifier = o.attr("identifier").cast<std::string>();
        v.name = o.attr("name").cast<std::string>();
        v.description = o.attr("description").cast<std::string>();
        v.unit = o.attr("unit").cast<std::string>();
        v.unit = o.attr("has_fixed_bin_count").cast<bool>();
        v.binCount = o.attr("bin_count").cast<size_t>();
        auto binNames = o.attr("bin_names").cast<std::list<std::string>>();
        v.binNames = std::vector<std::string>{
                std::make_move_iterator(binNames.begin()),
                std::make_move_iterator(binNames.end())
        };
        v.hasKnownExtents = o.attr("has_known_extents").cast<bool>();
        v.minValue = o.attr("min_value").cast<float>();
        v.maxValue = o.attr("max_value").cast<float>();
        v.isQuantized = o.attr("is_quantized").cast<bool>();
        v.quantizeStep = o.attr("quantize_step").cast<float>();
        v.sampleRate = static_cast<VampOutputDescriptor::SampleType>(
                o.attr("sample_type").cast<int>()
        );
        v.sampleRate = o.attr("sample_rate").cast<float>();
        v.hasDuration = o.attr("has_duration").cast<bool>();
        return opt<VampOutputDescriptor>(v);
    } catch (py::cast_error &e) {
        std::cerr << e.what() << std::endl;
        return opt<VampOutputDescriptor>();
    } catch (py::error_already_set &e) {
        std::cerr << e.what() << std::endl;
        return opt<VampOutputDescriptor>();
    }
}


template<>
opt<VampRealTime> fromPyObj<VampRealTime>(const py::object &o) {
    try {
        auto msec = o.attr("msec").cast<int>();
        auto nsec = o.attr("nsec").cast<int>();
        return opt<VampRealTime>(VampRealTime{msec, nsec});
    } catch (py::cast_error &e) {
        std::cerr << e.what() << std::endl;
        return opt<VampRealTime>();
    } catch (py::error_already_set &e) {
        std::cerr << e.what() << std::endl;
        return opt<VampRealTime>();
    }
}

}
}

#endif //PYTHON_VAMP_PLUGIN_UTIL_H
