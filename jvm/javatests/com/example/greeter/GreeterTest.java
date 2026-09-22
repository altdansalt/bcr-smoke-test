package com.example.greeter;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.containsString;
import static org.junit.Assert.assertEquals;

import com.example.greeter.proto.HelloRequest;
import java.util.Arrays;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class GreeterTest {
  @Test
  public void greet() {
    assertEquals("Hello, x!", Greeter.greet("x"));
  }

  @Test
  public void greetAllUsesGuava() {
    assertEquals("Hello, a! Hello, b!", Greeter.greetAll(Arrays.asList("a", "b")));
  }

  @Test
  public void protoRoundTripAndGson() {
    HelloRequest request = HelloRequest.newBuilder().setName("proto").build();
    assertThat(Greeter.toJson(Greeter.reply(request)), containsString("Hello, proto!"));
  }
}
