target_include_directories(${PROJECT_NAME} PRIVATE
    include
)
target_sources(${PROJECT_NAME} PRIVATE
    Renderer.cpp
    RendererDefault.cpp
)