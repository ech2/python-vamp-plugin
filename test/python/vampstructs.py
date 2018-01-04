from vplug import *

# InputDomain
input_domain_time = InputDomain.Time
input_domain_freq = InputDomain.Frequency

one_sample_per_step = SampleType.OneSamplePerStep
fixed_sample_rate = SampleType.FixedSampleRate
variable_sample_rate = SampleType.VariableSampleRate

# RealTime
realtime = RealTime(1, 2)

# OutputDescriptor
od = OutputDescriptor(identifier='id',
                      name='name',
                      description='descr',
                      unit='unit',
                      has_fixed_bin_count=True,
                      bin_count=5,
                      bin_names=['1', '2', '3', '4', '5'],
                      has_known_extents=True,
                      min_value=0,
                      max_value=10,
                      is_quantized=True,
                      quantize_step=1,
                      sample_type=SampleType.FixedSampleRate,
                      sample_rate=44100,
                      has_duration=True)

# Feature
feature = Feature(has_timestamp=True,
                  timestamp=RealTime(10, 20),
                  has_duration=True,
                  duration=RealTime(30, 40),
                  values=[0, 0.25, 0.5, 0.75, 1],
                  label='label')
