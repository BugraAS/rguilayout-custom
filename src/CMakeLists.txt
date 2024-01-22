cmake_minimum_required(VERSION 3.25.0)

project(rayGuiLayoutEditor LANGUAGES C CXX)

add_executable(${PROJECT_NAME} "")

add_subdirectory(deps)

target_sources(
    ${PROJECT_NAME} PRIVATE
    main.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    include
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    raylib
    raylib_cpp
    raygui
    rpng
    tinyfiledialogs
)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
	# set(WEB_SHELL_FILE ${MISC_DIRECTORY}/minshell.html)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
	# set(EMSCRIPTEN_DIR ${CMAKE_TOOLCHAIN_FILE})
	# cmake_path(REMOVE_FILENAME EMSCRIPTEN_DIR)
	target_link_options(${PROJECT_NAME} PRIVATE
		"-sUSE_GLFW=3"
		"-sASSERTIONS=1"
		"-sWASM=1"
		"-sASYNCIFY"
		# "-sALLOW_MEMORY_GROWTH"
		# "--preload-file=${RESOURCE_DIRECTORY}"
#		"-sMAX_WEBGL_VERSION=2"
		"-sGL_ENABLE_GET_PROC_ADDRESS"
		$<$<NOT:$<CONFIG:Debug>>:--shell-file=${WEB_SHELL_FILE}>
		)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()