#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "pybind11/embed.h"

struct PythonTestCaseInitializer : Catch::TestEventListenerBase {
    using TestEventListenerBase::TestEventListenerBase;

    void testCaseStarting(Catch::TestCaseInfo const &testInfo) override {
        pybind11::initialize_interpreter();
    }

    void testCaseEnded(Catch::TestCaseStats const &testCaseStats) override {
        pybind11::finalize_interpreter();
    }
};

CATCH_REGISTER_LISTENER(PythonTestCaseInitializer)
