cmake_minimum_required(VERSION 3.25.0)

project(tinyfiledialogs LANGUAGES C)

add_library(tinyfiledialogs STATIC "")

target_sources(
    tinyfiledialogs PRIVATE
    tinyfiledialogs.c
)

target_include_directories(
    tinyfiledialogs PUBLIC
    include
)