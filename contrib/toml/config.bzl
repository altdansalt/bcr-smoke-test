"""toml.bzl 0.4.1 smoke: decode a TOML document at load time and re-encode it.

Example document adapted from https://github.com/jvolkman/toml.bzl README (Apache-2.0).
"""

load("@toml.bzl", "toml")

CONFIG_TOML = """\
title = "bcr smoke"

[database]
server = "192.168.1.1"
ports = [ 8000, 8001, 8002 ]
enabled = true
"""

CONFIG = toml.decode(CONFIG_TOML)

# Lines describing the decoded values, written to a file and diff-tested.
DECODED_LINES = [
    "title=" + CONFIG["title"],
    "server=" + CONFIG["database"]["server"],
    "ports=" + ",".join([str(p) for p in CONFIG["database"]["ports"]]),
    "enabled=" + str(CONFIG["database"]["enabled"]),
    "",  # trailing newline
]

ENCODED = toml.encode(CONFIG)
