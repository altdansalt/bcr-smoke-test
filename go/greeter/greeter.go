// Package greeter builds greetings. It exercises an external Go module
// dependency (github.com/google/uuid) resolved through gazelle's go_deps.
package greeter

import (
	"fmt"
	"strings"

	"github.com/google/uuid"
)

// Greeting returns "Hello, <name>!" with the name trimmed and capitalized.
func Greeting(name string) string {
	return fmt.Sprintf("Hello, %s!", normalize(name))
}

// NewID returns a fresh random UUID (v4) string.
func NewID() string {
	return uuid.NewString()
}

func normalize(name string) string {
	name = strings.TrimSpace(name)
	if name == "" {
		return "World"
	}
	return strings.ToUpper(name[:1]) + name[1:]
}
