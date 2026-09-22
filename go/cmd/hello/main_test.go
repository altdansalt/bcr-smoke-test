package main

import (
	"strings"
	"testing"
)

func TestRun(t *testing.T) {
	var sb strings.Builder
	if err := run(&sb, "bazel"); err != nil {
		t.Fatal(err)
	}
	if !strings.HasPrefix(sb.String(), "Hello, Bazel! (id ") {
		t.Errorf("unexpected output %q", sb.String())
	}
}
