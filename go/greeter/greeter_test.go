package greeter_test

// External test: separate package, uses the public API plus two external
// modules (testify, google.golang.org/protobuf) and the generated proto.

import (
	"testing"

	"github.com/bcr-smoke-test/bcr-smoke-test/go/greeter"
	"github.com/bcr-smoke-test/bcr-smoke-test/go/greetingpb"
	"github.com/google/uuid"
	"github.com/stretchr/testify/require"
	"google.golang.org/protobuf/proto"
)

func TestGreeting(t *testing.T) {
	require.Equal(t, "Hello, Bazel!", greeter.Greeting("bazel"))
	require.Equal(t, "Hello, World!", greeter.Greeting(""))
}

func TestNewID(t *testing.T) {
	id, err := uuid.Parse(greeter.NewID())
	require.NoError(t, err)
	require.Equal(t, uuid.Version(4), id.Version())
}

func TestGreetingProtoRoundTrip(t *testing.T) {
	msg := &greetingpb.Greeting{Name: "Bazel", Message: greeter.Greeting("Bazel")}
	data, err := proto.Marshal(msg)
	require.NoError(t, err)

	var got greetingpb.Greeting
	require.NoError(t, proto.Unmarshal(data, &got))
	require.True(t, proto.Equal(msg, &got))
	require.Equal(t, "Hello, Bazel!", got.GetMessage())
}
