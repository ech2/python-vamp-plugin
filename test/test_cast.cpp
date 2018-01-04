#include <iostream>
#include <vector>
#include "catch.hpp"

#include "common.h"
#include "PythonCasting.h"


using namespace std;
using namespace vplug;
using namespace vplug::util;


TEST_CASE("casting python objects to C++", "[cast]") {
    auto m = py::module::import("vampstructs");

    SECTION("InputDomain (enum)") {
        using V = Vamp::Plugin::InputDomain;

        auto cppTime = Vamp::Plugin::TimeDomain;
        auto cppFreq = Vamp::Plugin::FrequencyDomain;

        auto pyTime = fromPyObj<V>(m.attr("input_domain_time"));
        auto pyFreq = fromPyObj<V>(m.attr("input_domain_freq"));

        CHECK(cppTime == pyTime.value());
        CHECK(cppFreq == pyFreq.value());
    }

    SECTION("SampleType (enum)") {
        using V = VampOutputDescriptor::SampleType;

        auto cppOSPS = VampOutputDescriptor::OneSamplePerStep;
        auto cppFSR = VampOutputDescriptor::FixedSampleRate;
        auto cppVSR = VampOutputDescriptor::VariableSampleRate;

        auto pyOSPS = fromPyObj<V>(m.attr("one_sample_per_step"));
        auto pyFSR = fromPyObj<V>(m.attr("fixed_sample_rate"));
        auto pyVSR = fromPyObj<V>(m.attr("variable_sample_rate"));

        CHECK(cppOSPS == pyOSPS.value());
        CHECK(cppFSR == pyFSR.value());
        CHECK(cppVSR == pyVSR.value());
    }

    SECTION("RealTime (class)") {
        using V = VampRealTime;
        auto cppRT_1 = V{1, 2};
        auto pyRT_1 = fromPyObj<V>(m.attr("realtime"));
        CHECK(cppRT_1 == pyRT_1);
    }

    SECTION("OutputDescriptor (class)") {
        using V = VampOutputDescriptor;

        auto pyOD = fromPyObj<V>(m.attr("od")).value();

        CHECK(pyOD.identifier == "id");
        CHECK(pyOD.name == "name");
        CHECK(pyOD.description == "descr");
        CHECK(pyOD.unit == "unit");
        CHECK(pyOD.hasFixedBinCount == true);
        CHECK(pyOD.binCount == 5);
        CHECK_THAT(pyOD.binNames,
                   Catch::Equals(vector<string>{"1", "2", "3", "4", "5"}));
        CHECK(pyOD.hasKnownExtents == true);
        CHECK(pyOD.minValue == 0);
        CHECK(pyOD.maxValue == 10);
        CHECK(pyOD.isQuantized == true);
        CHECK(pyOD.sampleType == VampOutputDescriptor::FixedSampleRate);
        CHECK(pyOD.sampleRate == 44100);
        CHECK(pyOD.hasDuration == true);
    };

    SECTION("Feature (class)") {
        using V = VampFeature;

        auto pyFeature = fromPyObj<V>(m.attr("feature")).value();

        CHECK(pyFeature.hasTimestamp == true);
        CHECK(pyFeature.timestamp.sec == 10);
        CHECK(pyFeature.timestamp.nsec == 20);
        CHECK(pyFeature.hasDuration == true);
        CHECK(pyFeature.duration.sec == 30);
        CHECK(pyFeature.duration.nsec == 40);
        CHECK_THAT(pyFeature.values,
                   Catch::Equals(vector<float>{0, 0.25, 0.5, 0.75, 1}));
        CHECK(pyFeature.label == "label");
    }
}
