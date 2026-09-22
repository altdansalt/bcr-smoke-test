#!/usr/bin/env bats
# bats_test smoke: the data file is passed through env via $(location).

@test "data file is readable" {
  run cat "$A_TXT"
  [ "$status" -eq 0 ]
  [ "$output" = "a" ]
}

@test "arithmetic works" {
  [ $((1 + 1)) -eq 2 ]
}
