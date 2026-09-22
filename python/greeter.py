"""Tiny py_library: pure Python plus two pip deps (six, PyYAML)."""

import six
import yaml


def greet(name: str) -> str:
    return "Hello, {}!".format(six.ensure_str(name))


def greet_all(config_yaml: str) -> list[str]:
    """Reads `names: [..]` from a YAML document and greets each one."""
    doc = yaml.safe_load(config_yaml)
    return [greet(n) for n in doc["names"]]
