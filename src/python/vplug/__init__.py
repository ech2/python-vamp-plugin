from .vampinterface import *


def find_plugins():
    return [c[1] for c
            in inspect.getmembers(sys.modules['vplug'], inspect.isclass)
            if issubclass(c[1], VampPlugin) and c[1] is not VampPlugin]
