cmake_minimum_required(VERSION 3.16)

project(T70 VERSION 0.70.6 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(T70_PRO "Build as the Pro version" ON)

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rd-party)

# third-party stuff
add_library(blipbuf STATIC ${THIRDPARTY_DIR}/blip-buf/blip_buf.c)
target_include_directories(blipbuf INTERFACE ${THIRDPARTY_DIR}/blip-buf)

add_library(duktape STATIC ${THIRDPARTY_DIR}/duktape/src/duktape.c)
target_include_directories(duktape INTERFACE ${THIRDPARTY_DIR}/duktape/src)

include(${THIRDPARTY_DIR}/wren.cmake)
include(${THIRDPARTY_DIR}/lua.cmake)
include(${THIRDPARTY_DIR}/lpeg.cmake)
include(${THIRDPARTY_DIR}/moonscript.cmake)
include(${THIRDPARTY_DIR}/fennel.cmake)

add_library(t70_o STATIC src/tic80.c src/tic.c src/jsapi.c src/luaapi.c src/wrenapi.c)
target_include_directories(t70_o PUBLIC include)
target_include_directories(t70_o PRIVATE ${MOONSCRIPT_DIR} ${FENNEL_DIR})
target_link_libraries(t70_o PRIVATE blipbuf duktape lua lpeg wren)

## studio
include(${THIRDPARTY_DIR}/giflib.cmake)

add_library(t70_studio STATIC
	src/studio.c
	src/console.c
	src/run.c
	src/ext/md5.c
	src/ext/gif.c
	src/fs.c
	src/tools.c
	src/start.c
	src/sprite.c
	src/map.c
	src/sfx.c
	src/music.c
	src/history.c
	src/world.c
	src/config.c
	src/code.c
	src/dialog.c
	src/menu.c
	src/surf.c
	src/html.c
)
target_include_directories(t70_studio PUBLIC include)

set(ZLIB_BUILD_TESTING OFF)
set(ZLIB_BUILD_SHARED OFF)
set(ZLIB_BUILD_STATIC ON)
set(ZLIB_INSTALL OFF)
add_subdirectory(${THIRDPARTY_DIR}/zlib EXCLUDE_FROM_ALL)

target_link_libraries(t70_studio PRIVATE lua giflib zlibstatic t70_o)

## system

add_executable(t70 src/system.c src/net.c src/ext/file_dialog.c)
target_link_libraries(t70 PRIVATE t70_studio)

find_package(SDL2)
if(SDL2_FOUND)
	target_link_libraries(t70 PRIVATE SDL2::SDL2)
else()
	set(SDL_SHARED OFF)
	set(SDL_STATIC ON)
	add_subdirectory(${THIRDPARTY_DIR}/SDL2 EXCLUDE_FROM_ALL)
	target_link_libraries(t70 PRIVATE SDL2::SDL2-static)
endif()
if(WIN32)
	target_link_libraries(t70 PRIVATE SDL2::SDL2main)
endif()

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(${THIRDPARTY_DIR}/SDL2_net EXCLUDE_FROM_ALL)

include(${THIRDPARTY_DIR}/sdl-gpu.cmake)

if(UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)
	target_link_libraries(t70 PRIVATE PkgConfig::GTK3 m)
endif()
target_link_libraries(t70 PRIVATE SDL2_net::SDL2_net-static sdlgpu)

# enabling pro version
if(T70_PRO)
	target_compile_definitions(t70_o PUBLIC TIC80_PRO)
endif()
