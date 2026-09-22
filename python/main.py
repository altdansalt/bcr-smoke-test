"""py_binary entry point."""

import sys

from python import greeter

if __name__ == "__main__":
    print(greeter.greet(sys.argv[1] if len(sys.argv) > 1 else "world"))
