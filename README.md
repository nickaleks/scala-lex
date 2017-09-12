# scala-lex
Scala lexical analysis without parsing literals and identifiers

## Installation

#### Requirements

* CMake 3.6+
* C++ Compiler with C++14 support (GCC 6+, Clang 3.4+)

#### Compilation

This project uses cmake as its build system. CMake automatically generates build files for target platform. If you have POSIX compatible system chances are you are going to use make. Below are the steps to compile program on POSIX system:
1. In project root, create "build" directory. Here all build files and resulting binaries are going to be located.
```
mkdir build
cd build
```

2. Now we need to generate build files. For this CMake needs file name "CMakeLists.txt". It is located in src/ directory, so to generate build files:
```
cmake ../src
```

3. After CMake has finished succesfully, build files are generated. This means that we can use whatever build system we have generated files for. By default CMake generates build files for make. So to build a final executable:
```
make
```
4. Now you have "scala-lex" exeсutable in your directory. You can run it as usual.


## Contribute

Now that you have learned how to build and run the project, you can begin contributing. To learn how to do this, check out CONTRIBUTING.md file.


