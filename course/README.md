# Sample app

## Building the app

If you haven't built your docker image, just visit the [docker readme](../docker/README.md).

To run the application, taking `{REPO_PATH}` as the base repository path, run the following:

```bash
cd {REPO_PATH}/course
mkdir build
cd build
cmake ..
make
./cpp_course
```

## To change the library name

Just go to `{REPO_PATH}/CMakeLists.txt` and replace, in `add_library` macro,
`foo` by your `library_name`.

## To add new source files

Just go to `{REPO_PATH}/CMakeLists.txt` and add, under `LIBRARY_SOURCES`, your
new file.
