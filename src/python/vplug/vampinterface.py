from abc import ABCMeta, abstractmethod
import inspect, sys


class VampPlugin(metaclass=ABCMeta):
    @abstractmethod
    def __init__(self, sr):
        pass

    @abstractmethod
    def reset(self):
        pass


class PlugExample(VampPlugin):
    def __init__(self, sr):
        self.sr = sr

    def reset(self):
        print("WOW, you’ve just reset me!")
        print("And btw, I use sampling rate {}.".format(self.sr))
