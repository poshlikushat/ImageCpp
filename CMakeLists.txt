cmake_minimum_required(VERSION 3.10)
project(ImageCpp
        VERSION 0.1.0
        DESCRIPTION "ImageCpp"
        LANGUAGES CXX)
include(CTest)
add_subdirectory(external)
add_subdirectory(src)
