package com.example.shout

import com.example.greeter.Greeter

/** Kotlin code calling into the Java library (Kotlin/Java interop). */
object Shout {
    fun shout(name: String): String = Greeter.greet(name).uppercase()

    fun shoutAll(names: List<String>): String = names.joinToString(" ") { shout(it) }
}
