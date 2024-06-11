# witsmlparser
WITSML 1.4.1.x and 1.3.1.x to BSON parser

# Install requirements

- Make >= 4.3
- GCC >= 7
- Node-gyp for compiling node
- Python >= 3

# Compiling dependencies (compile once)

## Compiling third-party

Compiling Mongo c library

```sh
make -j4 install_bson
```
You need compiling this step once

## Compiling gSoap WITSML C code

```sh
make -j4 pre && make -j4 pre_shared
```

WITSML has many object and compiling this step can take a little longer ~ 40 minutes

You need compiling this step once

# Building libraries

## Build C example code

```sh
make clean && make -j4
```

## Build Python module

```sh
make clean && make -j4 py
```

## Build NodeJS library

```sh
make clean && make -j4 nodejs
```

## Build Java library

```sh
make clean && make -j4 jni
```

# Cleaning

## Cleaning project

```sh
make clean
```

## Removing WITSML pre compiled objects

```sh
make pre_remove
```

## Removing Mongo C BSON library

```sh
make remove_bson
```

# Running examples

## NodeJS example

```sh
make node_example
```

## Python3 example

```sh
make py_example
```

## Cleaning examples

```sh
make clean_examples
```

# Memory management

**default: 30 MB**

You can edit [_SOAP_MAXALLOCSIZE_](https://github.com/devfabiosilva/witsmlparser/blob/master/include/stdsoap2.h#L1253) in file _include/stdsoap2.h_ to modify max memory allocation for each instance

# LICENSES

This project is fully open source (MIT) **BUT** it depends on gSoap library that is GPLv2. See [Genivia website](https://www.genivia.com/products.html)

