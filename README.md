# IP
Install prerequisites

```
$ sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
```

#### Building the Paho C library

Before building the C++ library, first, build and install the Paho C library, if not already present. Note, this version of the C++ library requires Paho C v1.3.8 or greater.

```
$ git clone https://github.com/eclipse/paho.mqtt.c.git
$ cd paho.mqtt.c
$ git checkout v1.3.8

$ cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
$ sudo cmake --build build/ --target install
$ sudo ldconfig
```

This builds with SSL/TLS enabled. If that is not desired, omit the `-DPAHO_WITH_SSL=ON`.

It also uses the "high performace" option of the C library to disable more extensive internal memory checks. Remove the _PAHO_HIGH_PERFORMANCE_ option (i.e. turn it off) to debug memory issues, but for most production systems, leave it on for better performance.

To install the library to a non-standard location, use the `CMAKE_INSTALL_PREFIX` to specify a location. For example, to install into under the build directory, perhaps for local testing, do this:

```
$ cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON \
    -DCMAKE_INSTALL_PREFIX=./build/_install
```

#### Building the Paho C++ library

An example CMake build session might look like this:

```
$ git clone https://github.com/eclipse/paho.mqtt.cpp
$ cd paho.mqtt.cpp

$ cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
$ sudo cmake --build build/ --target install
$ sudo ldconfig
```

If you did not install Paho C library to a default system location or you want to build against a different version, use the `CMAKE_PREFIX_PATH` to specify its install location. Perhaps something like this:

```
$ cmake -Bbuild -H. -DPAHO_BUILD_DOCUMENTATION=ON -DPAHO_BUILD_SAMPLES=ON \
    -DPAHO_BUILD_STATIC=ON \
    -DCMAKE_PREFIX_PATH=$HOME/mqtt/paho.mqtt.c/build/_install
```

To use another compiler, either the CXX environment variable can be specified in the configuration step:

```
$ CXX=clang++ cmake ..
```

or the `CMAKE_CXX_COMPILER` flag can be used:

```
$ cmake -DCMAKE_CXX_COMPILER=clang++
```

## 
Copy libpistache.so.0.0 inside src direcotory

Build final app
```
cd src
make
```
Run
```
./air-purifier
```
