# Building on mingw-w64 (from MSYS2):
## wren
If not using Nesbox's mod, apply this patch: https://github.com/wren-lang/wren/pull/620

Then run `make static`

Your library should be on `lib/libwren.a`

## SDL2
Create a prefix directory somewhere. This is for building sdl_gpu later on.

* `./configure --prefix=[your prefix path goes here]`
* `make`
* `make install`

Your library should be on `[your prefix path goes here]/lib/libSDL2.dll.a` (and main + SDL2.dll)

## sdl_gpu
* `cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -B build -DCMAKE_INSTALL_PREFIX=[your prefix path goes here]`
* `cmake --build build`

Your library should be on `build/SDL_gpu-MINGW/lib/libSDL2_gpu_s.a`

## Lua
Run `make liblua.a MYCFLAGS="-std=c99 -DLUA_COMPAT_5_2" MYLDFLAGS="" MYLIBS=""`

Your library should be on `liblua.a`

## lpeg
* `make LUADIR=../lua lpvm.o lpcap.o lptree.o lpcode.o lpprint.o lpcset.o`
* `ar rcu liblpeg.a *.o`

Your library should be on `liblpeg.a`

## zlib
Run `make -f win32/Makefile.gcc`

Your library should be on `libz.a`

## giflib
Run `make libgif.a`

Your library should be on `libgif.a`

