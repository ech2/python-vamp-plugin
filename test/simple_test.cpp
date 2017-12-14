
#include "pybind11/pybind11.h"
#include "pybind11/embed.h"
#include "../src/cpp/PythonPlugin.h"

namespace py = pybind11;

int main(int argc, const char** argv) {
    py::scoped_interpreter python{};

    auto mod = py::module::import("vplug");
    auto plugs = mod.attr("find_plugins")().cast<py::list>();
    auto p = plugs[0];

    vplug::PythonPlugin plug{44100, p};
    plug.reset();
}