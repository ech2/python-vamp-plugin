import inspect
import sys

from .vampinterface import *


def find_plugins():
    return [c[1] for c
            in inspect.getmembers(sys.modules['vplug'], inspect.isclass)
            if issubclass(c[1], VampPluginInterface) and c[1] is not VampPluginInterface]
