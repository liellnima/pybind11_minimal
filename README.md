# Minimal Pybind 11, Scitkit-build-core example

# Setup

## Git repo
Download the repo
```
git clone git@github.com:liellnima/pybind11_minimal.git
```

## C++

Get c++ compiler etc. (gets gcc, make, etc):

```
sudo apt install build-essential
```
After this you can use ``g++``. Check you version with ``g++ --version``.
If you want to install other g++ compilers (optional!), use ``sudo apt install g++-10`` (replace [10] with the desired version).

Get cmake:

```
sudo apt install cmake
```

## Python

### Conda / venv
Set up virtual environment. Install python requirements (see pip section).
```
conda create --name pybind11_minimal python=3.10
conda activate pybind11_minimal
```

### Pip
```
pip install pybind11
pip install scikit-build-core
```
see also requirements.txt

### Pipx
Get pipx.

```
sudo apt install pipx
pipx ensurepath
```

# What is what
Files at root:
- ``CMakeLists.txt``: Where the cmake project is defined. Links libraries, version control, etc.
- ``LICENSE``: license for this repo here
- ``pyproject.toml``: For scikit-build-core, used to create a python package. CMakeLists uses information from that ($SKIBUILD params).
- ``README.md``: You are here.
- ``requirements.txt``: pip requirements for this repo to run (python side)


Dirs at root:
- ``build/``: cmake is putting everything in here
- ``dist/``: not here yet, automatically created by scikit-core-build when running pipx. Note: pip is installing stuff internally. Pipx makes it directly accessible to us instead
- ``src/``: where all the code lives
- ``test/``: not used right now, can be used for testing


src structure:
- ``sspy/``: Just for the python package. Has an __init__.py file that you need to adapt when adding new c++ files etc
- ``custom_class/``: Example of a separate dir structure that contains other classes. Subdir ``include/`` contains the .h headerfiles of the cpp. Subdir ``src/`` contains the cpp implementations of the headerfiles. (e.g. ``my_class.h`` and ``my_class.cpp``)


Example files, directly in src:
- ``multiply.cpp``: c++ implementation of a multiply function
- ``multiply.h``: header for multiply.cpp
- ``run_sspy.cpp``: binding code - glues c++ to python via Pybind11 syntax. Includes also the add and subtract function
- ``string_example.cpp``: example function taking strings as input. example file that has different name than the function it contains.
- ``string_example.h``: header file for string_example.cpp
- ``test.cpp``: a runnable / executable file to test the multiply function directly in c++
- ``test``: created as an output file when compiling test.cpp

# Building the project
These are just different levels of abstraction. You can skip immediately to pip installing.
I am only listing all different steps here because it is easier to debug your code if you increase the abstraction level incrementally.

## C++ build the project
### Compile C++ Code
Attention, you cannot compile the binding code (``run_sspy.cpp``). But we can create a test file (``test.cpp``) to see if we can import the ``multiply.h`` file successfully and use it as intended.
```
cd src
g++ test.cpp multiply.cpp -o test
```
After this you can run the c++ code and see if it works on the C++ level.
```
./test
```
(Output should be 30)

Adapt: the c++ and .h files. Create other test files to test functionality of your C++ code.

### Cmake build the project
Build a C++ package with cmake. This makes it accessible across different platforms.

```
cd build
cmake ../
cmake --build .
make
```
You can find output files in build/CMakeFiles/_core.dir/src. Those files are not executable (permission denied), since they don't have a main and cannot be executed. If you include the test.cpp in the CMakeLists.txt file, you will be able to run that output file afterwards.

Adapt: CMakeLists.txt file(s).

## Python build the project
Pybind11 is binding the C++ code to python.

Scikit-build-core makes actually a python package from that, so we can import and use it. It also ensures cross-plattform accessability.

Adapt: project.toml, CMakeLists, and the `__init__.py` file.

### Developer build - Pipx
We are running it FIRST with pipx, so it's in an environment and completely separated from the rest of the system. If something brakes there, it's okay. This cannot be used to install it and import it for python - use pip install for that.

Run at project root:
```
cd pybind11_minimal
pipx run build
```
This will create its own "dist" directory.

## Users build - Pip
This is to actually install it and use it afterwards.

Run in directory above project root:
```
cd pybind11_minimal
cd ..
pip install ./pybind11_minimal
```
The package will be called sspy, because this is how the project is named in the project_toml and cmake files!


# Usage of python package
In a python file or shell:
```
import sspy
result_add = sspy.add(5, 6)
result_sub = sspy.subtract(5, 6)
result_mul = sspy.multiply(5, 6)
result_div = sspy.divide(5, 6)
str_size = sspy.string_size("hello")
rep = sspy.Repetitor(3, "meow")
rep.repeat()
```

# Helpful Links
cmake links:
https://stackoverflow.com/questions/39598323/how-to-properly-link-libraries-with-cmake
https://stackoverflow.com/questions/21163188/most-simple-but-complete-cmake-example

pybind11 and cmake:
https://ekbanaml.github.io/old_site_data/cpp-references/pybind-reference/

pybind and Scitkit-build
https://github.com/pybind/scikit_build_example/blob/master/src/main.cpp

linking libraries in pybind11:
https://github.com/pybind/pybind11/issues/387

classes in pybind11:
https://pybind11.readthedocs.io/en/stable/classes.html
https://pybind11.readthedocs.io/en/stable/advanced/classes.html
