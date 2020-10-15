# C++ terrarium simulator

A C++ implementation of a terrarium simulator. Used mainly for practicing OOP and advanced C++ concepts.

Project structure based on https://github.com/glpuga/cppl1_q12020.

## Project organization

You'll find the following project organization:

- course: Source code.
  - include: Header files.
  - src: Source files.
  - test: Testing files.
- docker: Docker related files.

## Installation

1. Fork and clone this repository.

2. Build docker image and run container, visit [docker readme](./docker/README.md)
for instructions.

3. Build and run the sample app, visit [course readme](./course/README.md) for instructions.

## Building and running the tests

To build and test your code:

```
bash
cd {REPO_PATH}/course
mkdir build
cd build
cmake ..
make
ctest
```