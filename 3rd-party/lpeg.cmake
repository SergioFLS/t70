set(LPEG_DIR ${THIRDPARTY_DIR}/lpeg)

add_library(lpeg STATIC ${LPEG_DIR}/lpvm.c ${LPEG_DIR}/lpcap.c ${LPEG_DIR}/lptree.c ${LPEG_DIR}/lpcode.c ${LPEG_DIR}/lpprint.c ${LPEG_DIR}/lpcset.c)
target_include_directories(lpeg PRIVATE ${LUA_DIR})
