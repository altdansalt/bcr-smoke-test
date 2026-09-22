package greeter

// Internal test: same package, can reach unexported symbols.

import "testing"

func TestNormalize(t *testing.T) {
	cases := map[string]string{"": "World", "  bazel ": "Bazel", "Go": "Go"}
	for in, want := range cases {
		if got := normalize(in); got != want {
			t.Errorf("normalize(%q) = %q, want %q", in, got, want)
		}
	}
}
