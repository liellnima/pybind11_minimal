cmake_minimum_required(VERSION 3.22)

project(${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  DESCRIPTION "A C++ filereader for the Snow Sound Pen"
  # HOMEPAGE_URL ""
  LANGUAGES CXX
)

if(${SKBUILD_PROJECT_NAME}_BUILD_TESTING)
  enable_testing()
endif()

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED HINTS "${Python3_SITELIB}")


add_library(ops
  src/multiply.cpp
  src/string_example.cpp
  src/custom_class/src/my_class.cpp
)


pybind11_add_module(_core
  src/run_sspy.cpp
)


target_compile_features(ops PUBLIC cxx_std_20)
target_compile_features(_core PUBLIC cxx_std_20)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PUBLIC)
target_include_directories(ops PUBLIC)

target_link_libraries(_core PRIVATE ops)

install(TARGETS _core DESTINATION sspy)

if(${SKBUILD_PROJECT_NAME}_BUILD_TESTING)
  add_subdirectory(tests)
endif()
