package com.example.greeter;

import java.util.Arrays;

/** Entry point for the java_binary target. */
public final class Hello {
  private Hello() {}

  public static void main(String[] args) {
    System.out.println(
        Greeter.greetAll(args.length == 0 ? Arrays.asList("world") : Arrays.asList(args)));
  }
}
