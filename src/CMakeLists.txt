cmake_minimum_required(VERSION 3.25.0)

project(rayGuiLayoutEditor LANGUAGES C CXX)

set(MISC_DIRECTORY misc)

add_custom_target(copy_misc ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/${MISC_DIRECTORY}
	${CMAKE_BINARY_DIR}/${MISC_DIRECTORY}
	COMMENT "Copying misc into binary dir"
)

add_executable(${PROJECT_NAME} "")

add_dependencies(${PROJECT_NAME} copy_misc)

add_subdirectory(deps)
add_subdirectory(modules)

target_link_libraries(
	${PROJECT_NAME} PRIVATE
	raylib
	raylib_cpp
	raygui
	rpng
	tinyfiledialogs
)

add_subdirectory(tests)

target_sources(
	${PROJECT_NAME} PRIVATE
	main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
# Web Configurations
if (${PLATFORM} STREQUAL "Web")
	set(WEB_SHELL_FILE ${MISC_DIRECTORY}/minshell.html)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
	# set(EMSCRIPTEN_DIR ${CMAKE_TOOLCHAIN_FILE})
	# cmake_path(REMOVE_FILENAME EMSCRIPTEN_DIR)
	target_link_options(${PROJECT_NAME} PRIVATE
		"-sUSE_GLFW=3"
		"-sASSERTIONS=1"
		"-sWASM=1"
		"-sASYNCIFY"
		"-sALLOW_MEMORY_GROWTH"
		# "--preload-file=${RESOURCE_DIRECTORY}"
#		"-sMAX_WEBGL_VERSION=2"
		# "-sGL_ENABLE_GET_PROC_ADDRESS"
		$<$<NOT:$<CONFIG:Debug>>:--shell-file=${WEB_SHELL_FILE}>
		)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()