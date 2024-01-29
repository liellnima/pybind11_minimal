#include <pybind11/pybind11.h>

#include "multiply.h"
#include "string_example.h"
#include "custom_class/include/my_class.h"

using std::string;

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
  return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(_core, m){
  m.doc() = R"pbdoc(Pybind11 example)pbdoc";

  // add functions
  m.def("add", &add, R"pbdoc(Add two numbers)pbdoc");
  m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(Subtract two numbers)pbdoc");
  m.def("multiply", multiply, R"pbdoc(Multiply two numbers)pbdoc");
  m.def("string_size", string_size, R"pbdoc(Return size of string)pbdoc");
  m.def("divide", divide, R"pbdoc("Divide two numbers)pbdoc");

  // add classes
  py::class_<Repetitor>(m, "Repetitor")
      .def(py::init<int, string>(), R"pbdoc(Class repeating a string)pbdoc")
      .def("repeat", &Repetitor::repeat, R"pbdoc(Repeat the string)pbdoc");

  #ifdef VERSION_INFO
      m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
  #else
      m.attr("__version__") = "dev";
  #endif

}
