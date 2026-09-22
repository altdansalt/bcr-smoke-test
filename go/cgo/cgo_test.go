package cgo

import "testing"

func TestSquare(t *testing.T) {
	if got := Square(7); got != 49 {
		t.Fatalf("Square(7) = %d, want 49", got)
	}
}
