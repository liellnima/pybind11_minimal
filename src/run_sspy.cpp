#include <pybind11/pybind11.h>

#include "multiply.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
  return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(_core, m){
  m.doc() = R"pbdoc(Pybind11 example)pbdoc";
  m.def("add", &add, R"pbdoc(Add two numbers)pbdoc");
  m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(Subtract two numbers)pbdoc");
  m.def("multiply", multiply, R"pbdoc("Multiply two numbers)pbdoc");

  #ifdef VERSION_INFO
      m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
  #else
      m.attr("__version__") = "dev";
  #endif

}