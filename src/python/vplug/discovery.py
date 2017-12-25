import inspect
import os
import platform
from importlib.util import spec_from_file_location, module_from_spec
from os import path
from typing import List, Tuple

import sys

from .vampinterface import VampPluginInterface


def get_vamp_plugins_path() -> List[str]:
    this_os = platform.system().lower()
    if this_os == 'darwin':
        return [
            path.expanduser('~/Library/Audio/Plug-Ins/Vamp'),
            '/Library/Audio/Plug-Ins/Vamp'
        ]
    elif this_os == 'linux':
        return [
            path.expanduser('~/vamp'),
            path.expanduser('~/.vamp'),
            '/usr/local/lib/vamp',
            '/usr/lib/vamp'
        ]
    elif this_os == 'win32':
        pf32 = os.getenv('ProgramFiles(x86)', 'C:\\Program Files (x86)')
        pf64 = os.getenv('ProgramFiles', 'C:\\Program Files')
        return [path.join(p, 'Vamp Plugins') for p in [pf32, pf64]]
    else:
        raise SystemError('You are probably using an unsupported OS')


def find_python_files(dirs: List[str]) -> List[str]:
    return [path.join(dirpath, name)
            for d in dirs
            for dirpath, _, names in os.walk(path.expanduser(d))
            for name in names
            if path.splitext(name)[1].lower() == '.py']


def find_vamp_module_classes(py_files: List[str]) -> List[Tuple[str, type]]:
    specs = [spec_from_file_location(path.basename(f).
                                     replace('.py', '').
                                     replace('.', '').
                                     replace('-', '_'), f)
             for f in py_files]
    classes = []
    for s in specs:
        m = module_from_spec(s)
        s.loader.exec_module(m)
        classes.extend([(n, c) for n, c in inspect.getmembers(m, inspect.isclass)
                        if issubclass(c, VampPluginInterface)
                        and c is not VampPluginInterface])
    return classes


def find_vamp_modules_from_default_path():
    return find_vamp_module_classes(find_python_files(get_vamp_plugins_path()))


def find_test_module():
    from .test import get_test_file
    return find_vamp_module_classes([get_test_file('dummyplugin.py')])
