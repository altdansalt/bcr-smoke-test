# Slimmed from rules_foreign_cc examples/cmake_hello_world_lib/static
# (https://github.com/bazel-contrib/rules_foreign_cc, Apache-2.0).
cmake_minimum_required(VERSION 3.10)
project(greet C)

add_library(greet STATIC greet.c)
install(TARGETS greet ARCHIVE DESTINATION lib)
install(FILES greet.h DESTINATION include)
