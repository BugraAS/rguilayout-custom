target_include_directories(${PROJECT_NAME} PRIVATE
    include
)
target_sources(${PROJECT_NAME} PRIVATE
    GUI.cpp
    Button.cpp
)

add_subdirectory(Data)