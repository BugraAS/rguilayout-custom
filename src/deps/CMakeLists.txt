add_subdirectory(tinyfiledialogs)
add_subdirectory(rpng)
add_subdirectory(raylib)
add_subdirectory(raylib-cpp)
add_subdirectory(raygui/projects/CMake)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    raygui/styles
)