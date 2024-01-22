cmake_minimum_required(VERSION 3.25.0)

project(rpng LANGUAGES C)

add_library(rpng INTERFACE)

target_include_directories(
    rpng INTERFACE
    .
)