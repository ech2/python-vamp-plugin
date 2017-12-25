from abc import ABCMeta, abstractmethod
from enum import Enum
from typing import List, Dict

import numpy as np


class InputDomain(Enum):
    Time = 0
    Frequency = 1


class SampleType(Enum):
    OneSamplePerStep = 0,
    FixedSampleRate = 1,
    VariableSampleRate = 2


class RealTime:
    def __init__(self, sec: int = 0, nsec: int = 0):
        self.sec = sec
        self.nsec = nsec


class OutputDescriptor:
    def __init__(self,
                 identifier: str,
                 name: str,
                 description: str = '',
                 unit: str = 'unknown',
                 has_fixed_bin_count: bool = False,
                 bin_count: int = 0,
                 bin_names: List[str] = None,
                 has_known_extents: bool = False,
                 min_value: float = 0,
                 max_value: float = 0,
                 is_quantized: bool = False,
                 quantize_step: float = 0,
                 sample_type: int = 0,
                 sample_rate: float = 0,
                 has_duration: bool = False):
        if bin_names is None:
            bin_names = []

        self.identifier = identifier
        self.name = name
        self.description = description
        self.unit = unit
        self.has_fixed_bin_count = has_fixed_bin_count
        self.bin_count = bin_count
        self.bin_names = bin_names
        self.has_known_extents = has_known_extents
        self.min_value = min_value
        self.max_value = max_value
        self.is_quantized = is_quantized
        self.quantize_step = quantize_step
        self.sample_type = sample_type
        self.sample_rate = sample_rate
        self.has_duration = has_duration


class Feature(object):
    def __init__(self,
                 has_timestamp: bool = False,
                 timestamp: RealTime = RealTime(),
                 has_duration: bool = False,
                 duration: RealTime = RealTime(),
                 values: List[float] = None,
                 label: str = 'default_label'):
        if values is None:
            values = []
        self.has_timestamp = has_timestamp
        self.timestamp = timestamp
        self.has_duration = has_duration
        self.duration = duration
        self.values = values
        self.label = label


class VampPluginInterface(metaclass=ABCMeta):
    @abstractmethod
    def __init__(self, sr):
        pass

    """ Plugin """

    @abstractmethod
    def get_identifier(self) -> str:
        pass

    @abstractmethod
    def initialise(self, input_channels: int,
                   step_size: int, block_size: int) -> bool:
        pass

    @abstractmethod
    def reset(self):
        pass

    @abstractmethod
    def get_input_domain(self) -> int:
        pass

    @abstractmethod
    def get_output_descriptors(self) -> List[OutputDescriptor]:
        pass

    @abstractmethod
    def process(self, input_buffers: List[np.array],
                sec: int, nsec: int) -> Dict[int, List[Feature]]:
        pass

    @abstractmethod
    def get_remaining_features(self) -> Dict[int, List[Feature]]:
        pass

    """ PluginBase """

    @abstractmethod
    def get_name(self) -> str:
        pass

    @abstractmethod
    def get_description(self) -> str:
        pass

    @abstractmethod
    def get_maker(self) -> str:
        pass

    @abstractmethod
    def get_copyright(self) -> str:
        pass

    @abstractmethod
    def get_plugin_version(self) -> int:
        pass
