cmake_minimum_required(VERSION 3.16)

project(T70 VERSION 0.70.6 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rd-party)

add_library(blipbuf STATIC ${THIRDPARTY_DIR}/blip-buf/blip_buf.c)
target_include_directories(blipbuf INTERFACE ${THIRDPARTY_DIR}/blip-buf)

add_library(duktape STATIC ${THIRDPARTY_DIR}/duktape/src/duktape.c)
target_include_directories(duktape INTERFACE ${THIRDPARTY_DIR}/duktape/src)

include(${THIRDPARTY_DIR}/wren.cmake)
include(${THIRDPARTY_DIR}/lua.cmake)
include(${THIRDPARTY_DIR}/lpeg.cmake)
include(${THIRDPARTY_DIR}/moonscript.cmake)
include(${THIRDPARTY_DIR}/fennel.cmake)

add_library(t70_core STATIC src/tic80.c src/tic.c src/jsapi.c src/luaapi.c src/wrenapi.c)
target_include_directories(t70_core PUBLIC include)
target_include_directories(t70_core PRIVATE ${MOONSCRIPT_DIR} ${FENNEL_DIR})
target_link_libraries(t70_core PRIVATE blipbuf duktape lua lpeg wren)

add_executable(t70 src/system.c)
target_link_libraries(t70 PRIVATE t70_core)
