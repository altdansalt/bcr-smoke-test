package com.example.greeter;

import static org.junit.Assert.assertEquals;

import com.example.greeter.proto.HelloRequest;
import com.google.protobuf.InvalidProtocolBufferException;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class GreeterLiteTest {
  @Test
  public void liteMessageSerializes() throws InvalidProtocolBufferException {
    HelloRequest request = HelloRequest.newBuilder().setName("lite").build();
    assertEquals("lite", HelloRequest.parseFrom(request.toByteArray()).getName());
  }
}
