
#include "pybind11/pybind11.h"
#include "../src/cpp/plugin.cpp"
#include "../src/cpp/PythonPlugin.h"

int main(int argc, const char **argv) {
    pyInit();
    auto t = PythonPlugin(44100, (*pyPlugins)[0].plugClass);
    float d[] = {1, 2};
    float **dd;
    dd[0] = d;

    t.initialise(1, 2, 2);
    auto lol = t.process(reinterpret_cast<const float *const *>(dd), Vamp::RealTime{30, 30});
    t.reset();
    py::print("lol");
}