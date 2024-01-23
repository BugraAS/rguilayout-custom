add_subdirectory(deps/googletest)

enable_testing()

add_executable(mytests "")

get_target_property(TARGET_SOURCES ${PROJECT_NAME} SOURCES)
get_target_property(TARGET_INCLUDES ${PROJECT_NAME} INCLUDE_DIRECTORIES)
get_target_property(TARGET_LIBRARIES ${PROJECT_NAME} LINK_LIBRARIES)

target_sources(mytests PRIVATE
    InputHandler.cpp
    ${TARGET_SOURCES}
)
target_include_directories(mytests PRIVATE
    ${TARGET_INCLUDES}
)
target_link_libraries(mytests PRIVATE
    gtest
    GTest::gtest_main
    ${TARGET_LIBRARIES}
)

include(GoogleTest)
gtest_discover_tests(mytests)

add_test(
    NAME mytests
    COMMAND node "${CMAKE_CURRENT_BINARY_DIR}/mytests.js"
)