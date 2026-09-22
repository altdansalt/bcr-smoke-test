// pybind11 extension module: one function and one small class.
// Adapted from pybind11_bazel/examples/basic/basic.cpp (BSD-3-Clause,
// https://github.com/pybind/pybind11_bazel).
#include <pybind11/pybind11.h>

namespace {

int add(int i, int j) { return i + j; }

class Counter {
 public:
  void increment(int by) { value_ += by; }
  int value() const { return value_; }

 private:
  int value_ = 0;
};

}  // namespace

PYBIND11_MODULE(fastmath, m) {
  m.doc() = "bcr-smoke-test pybind11 extension";
  m.def("add", &add, "Add two integers");
  pybind11::class_<Counter>(m, "Counter")
      .def(pybind11::init<>())
      .def("increment", &Counter::increment)
      .def_property_readonly("value", &Counter::value);
}
