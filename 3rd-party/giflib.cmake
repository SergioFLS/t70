set(GIFLIB_DIR ${THIRDPARTY_DIR}/giflib)

add_library(giflib STATIC
	${GIFLIB_DIR}/dgif_lib.c
	${GIFLIB_DIR}/egif_lib.c
	${GIFLIB_DIR}/gifalloc.c
	${GIFLIB_DIR}/gif_err.c
	${GIFLIB_DIR}/gif_font.c
	${GIFLIB_DIR}/gif_hash.c
	${GIFLIB_DIR}/openbsd-reallocarray.c
)

target_include_directories(giflib PUBLIC ${GIFLIB_DIR})
