package com.example.shout

import org.junit.Assert.assertEquals
import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.JUnit4

@RunWith(JUnit4::class)
class ShoutTest {
    @Test
    fun shoutUppercasesTheJavaGreeting() {
        assertEquals("HELLO, KOTLIN!", Shout.shout("kotlin"))
    }

    @Test
    fun shoutAllJoins() {
        assertEquals("HELLO, A! HELLO, B!", Shout.shoutAll(listOf("a", "b")))
    }
}
