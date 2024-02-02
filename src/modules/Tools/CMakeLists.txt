target_include_directories(${PROJECT_NAME} PRIVATE
    include
)
target_sources(${PROJECT_NAME} PRIVATE
    Create.cpp
    Delete.cpp
    Group.cpp
    Move.cpp
    Pan.cpp
    Resize.cpp
    Select.cpp
)