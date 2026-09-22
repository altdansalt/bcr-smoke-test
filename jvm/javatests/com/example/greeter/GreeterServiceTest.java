// Adapted from grpc-java examples/src/test/java/io/grpc/examples/helloworld/HelloWorldServerTest.java
// (https://github.com/grpc/grpc-java, Apache-2.0).
package com.example.greeter;

import static org.junit.Assert.assertEquals;

import com.example.greeter.proto.GreeterGrpc;
import com.example.greeter.proto.HelloReply;
import com.example.greeter.proto.HelloRequest;
import io.grpc.inprocess.InProcessChannelBuilder;
import io.grpc.inprocess.InProcessServerBuilder;
import io.grpc.testing.GrpcCleanupRule;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class GreeterServiceTest {
  @Rule public final GrpcCleanupRule grpcCleanup = new GrpcCleanupRule();

  @Test
  public void sayHelloOverInProcessChannel() throws Exception {
    String serverName = InProcessServerBuilder.generateName();
    grpcCleanup.register(
        InProcessServerBuilder.forName(serverName)
            .directExecutor()
            .addService(new GreeterService())
            .build()
            .start());
    GreeterGrpc.GreeterBlockingStub stub =
        GreeterGrpc.newBlockingStub(
            grpcCleanup.register(
                InProcessChannelBuilder.forName(serverName).directExecutor().build()));

    HelloReply reply = stub.sayHello(HelloRequest.newBuilder().setName("grpc").build());

    assertEquals("Hello, grpc!", reply.getMessage());
  }
}
