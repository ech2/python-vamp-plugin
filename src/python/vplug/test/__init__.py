from os.path import abspath, dirname, join


def get_test_file(f: str) -> str:
    return abspath(join(dirname(__file__), f))
