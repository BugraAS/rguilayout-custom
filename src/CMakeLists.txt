cmake_minimum_required(VERSION 3.25.0)

project(rayGuiLayoutEditor LANGUAGES C CXX)

find_package(raylib 5.0 QUIET CONFIG)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()



add_executable(${PROJECT_NAME} "")

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