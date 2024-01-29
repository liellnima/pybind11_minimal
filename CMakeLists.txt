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


add_library(multiply
  src/multiply.cpp
)


pybind11_add_module(_core
  src/run_sspy.cpp
)


target_compile_features(multiply PUBLIC cxx_std_20)
target_compile_features(_core PUBLIC cxx_std_20)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PUBLIC)
target_include_directories(multiply PUBLIC)

target_link_libraries(_core PRIVATE multiply)

install(TARGETS _core DESTINATION sspy)

if(${SKBUILD_PROJECT_NAME}_BUILD_TESTING)
  add_subdirectory(tests)
endif()
