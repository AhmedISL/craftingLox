# CraftingLox

## Build Steps:

a folder named build should be created all following commands must be while in build

```bash
  mkdir build
  cd build
```

Build project using cmake, required version > 3.2
Using "Unix makefiles" as a generator

```bash
  cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
  make all
```

Run CraftingLox

```bash
  ./src/CraftingLox
```

Make (if needed) and Run the tests

```bash
  make CraftingLox_test
  ./test/CraftingLox
```

this folder structure is based on https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html
