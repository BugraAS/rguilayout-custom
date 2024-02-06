target_include_directories(${PROJECT_NAME} PRIVATE
    include
)
target_sources(${PROJECT_NAME} PRIVATE
    Node.cpp
    Scene.cpp
)
add_subdirectory(Guis)