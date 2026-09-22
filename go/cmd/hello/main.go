// Command hello prints a greeting; it is the go_binary of the smoke test.
package main

import (
	"fmt"
	"io"
	"os"

	"github.com/bcr-smoke-test/bcr-smoke-test/go/greeter"
	"github.com/bcr-smoke-test/bcr-smoke-test/go/greetingpb"
)

func run(w io.Writer, name string) error {
	msg := &greetingpb.Greeting{Name: name, Message: greeter.Greeting(name)}
	_, err := fmt.Fprintf(w, "%s (id %s)\n", msg.GetMessage(), greeter.NewID())
	return err
}

func main() {
	name := ""
	if len(os.Args) > 1 {
		name = os.Args[1]
	}
	if err := run(os.Stdout, name); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
