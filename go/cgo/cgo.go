// Package cgo exercises rules_go's cgo path: Go calling C compiled by the Bazel C++ toolchain.
package cgo

// #include "square.h"
import "C"

// Square returns n*n via C.
func Square(n int) int { return int(C.square(C.int(n))) }
