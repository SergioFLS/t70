# SDL_GPU does have a CMakeLists file, but IDK how to use it
# Copy-pasted from upstream TIC-80

set(SDLGPU_DIR ${THIRDPARTY_DIR}/sdl-gpu/src)
set(SDLGPU_SRC
	${SDLGPU_DIR}/renderer_GLES_2.c
	${SDLGPU_DIR}/SDL_gpu.c
	${SDLGPU_DIR}/SDL_gpu_matrix.c
	${SDLGPU_DIR}/SDL_gpu_renderer.c
	${SDLGPU_DIR}/externals/stb_image/stb_image.c
	${SDLGPU_DIR}/externals/stb_image_write/stb_image_write.c
	${SDLGPU_DIR}/renderer_GLES_1.c
	${SDLGPU_DIR}/renderer_GLES_3.c
	${SDLGPU_DIR}/renderer_OpenGL_1.c
	${SDLGPU_DIR}/renderer_OpenGL_1_BASE.c
	${SDLGPU_DIR}/renderer_OpenGL_2.c
	${SDLGPU_DIR}/renderer_OpenGL_3.c
	${SDLGPU_DIR}/renderer_OpenGL_4.c
	${SDLGPU_DIR}/SDL_gpu_shapes.c
	${SDLGPU_DIR}/externals/glew/glew.c
)


add_library(sdlgpu STATIC ${SDLGPU_SRC})
target_compile_definitions(sdlgpu PRIVATE GLEW_STATIC SDL_GPU_DISABLE_GLES SDL_GPU_DISABLE_OPENGL_3 SDL_GPU_DISABLE_OPENGL_4)

target_include_directories(sdlgpu PUBLIC ${THIRDPARTY_DIR}/sdl-gpu/include)
target_include_directories(sdlgpu PRIVATE ${THIRDPARTY_DIR}/sdl-gpu/src/externals/glew)
target_include_directories(sdlgpu PRIVATE ${THIRDPARTY_DIR}/sdl-gpu/src/externals/glew/GL)
target_include_directories(sdlgpu PRIVATE ${THIRDPARTY_DIR}/sdl-gpu/src/externals/stb_image)
target_include_directories(sdlgpu PRIVATE ${THIRDPARTY_DIR}/sdl-gpu/src/externals/stb_image_write)

if(WIN32)
	target_link_libraries(sdlgpu opengl32)
endif()

target_link_libraries(sdlgpu SDL2::SDL2-static)
