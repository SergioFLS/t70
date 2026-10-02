# T70

A hard fork of [TIC-80](https://github.com/nesbox/TIC-80) 0.70.6 that aims to add new editor features and better support for modern platforms, while retaining cart compatibility across both versions. Think of it as sorta-LTS version of it.

## Building
Only tested on Windows 10 (MinGW-W64 UCRT64 toolchain from MSYS2) and Ubuntu 26.04:
```sh
$ git clone --recursive ${this repo}
$ # if skipped --recursive: git submodule update --init
$ cmake -B out .
$ cmake --build out # -j ${your number of threads, see CMake documentation}
```

For slightly improved build times, the build script will also use your system's installation of SDL2 (or sdl2-compat) as a dynamic library.