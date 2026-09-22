package com.example.shout

fun main(args: Array<String>) {
    println(Shout.shoutAll(args.toList().ifEmpty { listOf("world") }))
}
