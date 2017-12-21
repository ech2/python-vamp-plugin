#include <iostream>
#include <vector>
#include <list>
#include "vamp/vamp.h"
#include "pybind11/embed.h"
#include "PythonPluginAdapter.h"

namespace py = pybind11;
using namespace vplug;

static std::vector<PythonPluginAdapter> pyPlugins;

static void findPythonVampClasses(std::vector<PythonPluginAdapter> &plugs) {
    auto m = py::module::import("vplug");
    auto classes = m.attr("find_vamp_modules_from_path").cast<std::list<py::object>>();
    for (auto &c : classes) {
        plugs.push_back(std::move(PythonPluginAdapter{c}));
    }
}

static void pyInit() {
    try {
        py::initialize_interpreter();
        findPythonVampClasses(pyPlugins);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/* Vamp plugin entry point */

const VampPluginDescriptor *vampGetPluginDescriptor(unsigned int version, unsigned int index) {
    if (version < 1) {
        return nullptr;
    }
    pyInit();

    if (index > pyPlugins.size() - 1) {
        return nullptr;
    } else {
        return pyPlugins[index].getDescriptor();
    }
}