package com.example.greeter;

import com.example.greeter.proto.HelloReply;
import com.example.greeter.proto.HelloRequest;
import com.google.common.base.Joiner;
import com.google.common.collect.ImmutableList;
import com.google.gson.Gson;
import java.util.List;

/** Tiny library that touches Guava, Gson and the generated protobuf messages. */
public final class Greeter {
  private static final Gson GSON = new Gson();

  private Greeter() {}

  public static String greet(String name) {
    return "Hello, " + name + "!";
  }

  public static String greetAll(List<String> names) {
    ImmutableList<String> greetings =
        names.stream().map(Greeter::greet).collect(ImmutableList.toImmutableList());
    return Joiner.on(" ").join(greetings);
  }

  public static HelloReply reply(HelloRequest request) {
    return HelloReply.newBuilder().setMessage(greet(request.getName())).build();
  }

  public static String toJson(HelloReply reply) {
    return GSON.toJson(ImmutableList.of(reply.getMessage()));
  }
}
