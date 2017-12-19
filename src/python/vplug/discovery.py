import inspect
import os
import platform
from importlib.util import spec_from_file_location, module_from_spec
from os import path
from typing import List

from .vampinterface import VampPluginInterface


def get_vamp_plugins_path() -> List[str]:
    if platform.system() == 'darwin':
        return [
            path.expanduser('~/Library/Audio/Plug-Ins/Vamp'),
            '/Library/Audio/Plug-Ins/Vamp'
        ]
    elif platform.system() == 'linux':
        return [
            path.expanduser('~/vamp'),
            path.expanduser('~/.vamp'),
            '/usr/local/lib/vamp',
            '/usr/lib/vamp'
        ]
    elif platform.system() == 'win32':
        pf32 = os.getenv('ProgramFiles(x86)', 'C:\\Program Files (x86)')
        pf64 = os.getenv('ProgramFiles', 'C:\\Program Files')
        return [path.join(p, 'Vamp Plugins') for p in [pf32, pf64]]
    else:
        raise SystemError('You are probably using an unsupported OS')


def find_python_files(dirs: List[str]) -> List[str]:
    return [path.join(dirpath, name)
            for d in dirs
            for dirpath, _, name in os.walk(d)
            if path.splitext(name)[1].lower() == '.py']


def find_vamp_module_classes(py_files: List[str]) -> List[type]:
    specs = [spec_from_file_location(f) for f in py_files]
    mods = [module_from_spec(s) for s in specs]
    return [cls
            for m in mods
            for _, cls in inspect.getmembers(m, inspect.isclass)
            if issubclass(cls, VampPluginInterface)
            and cls is not VampPluginInterface]


def find_vamp_modules_from_path():
    return find_vamp_module_classes(find_python_files(get_vamp_plugins_path()))
