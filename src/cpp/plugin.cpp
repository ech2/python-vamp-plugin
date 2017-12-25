#include <iostream>
#include <vector>
#include <list>
#include "vamp/vamp.h"
#include "pybind11/embed.h"
#include "pybind11/stl.h"
#include "PythonPluginAdapter.h"

using namespace vplug;

static std::vector<PythonPluginAdapter> *pyPlugins;

static void pyInit() {
    try {
        py::initialize_interpreter();
        auto m = py::module::import("vplug");
        pyPlugins = new std::vector<PythonPluginAdapter>();
        auto classes = m.attr("find_test_module")()
                .cast<std::list<std::tuple<std::string, py::object>>>();
        for (auto &c : classes) {
            (*pyPlugins).push_back(std::move(PythonPluginAdapter{std::get<1>(c)}));
        }
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

    if (index > (*pyPlugins).size() - 1) {
        return nullptr;
    } else {
        return (*pyPlugins)[index].getDescriptor();
    }
}