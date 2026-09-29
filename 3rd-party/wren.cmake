set(WREN_DIR ${THIRDPARTY_DIR}/wren)

add_library(wren STATIC
	${WREN_DIR}/src/optional/wren_opt_meta.c
	${WREN_DIR}/src/optional/wren_opt_random.c
	${WREN_DIR}/src/vm/wren_compiler.c
	${WREN_DIR}/src/vm/wren_utils.c
	${WREN_DIR}/src/vm/wren_core.c
	${WREN_DIR}/src/vm/wren_value.c
	${WREN_DIR}/src/vm/wren_debug.c
	${WREN_DIR}/src/vm/wren_vm.c
	${WREN_DIR}/src/vm/wren_primitive.c
)
target_include_directories(wren PUBLIC ${WREN_DIR}/src/include)
target_include_directories(wren PRIVATE ${WREN_DIR}/src/optional)
target_include_directories(wren PRIVATE ${WREN_DIR}/src/vm)
