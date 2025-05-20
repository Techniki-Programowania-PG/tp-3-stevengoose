cmake_minimum_required(VERSION 3.15)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1) #generates compile_commands.json for clangd to pick up on

# Fetching newest release of matplotplusplus
include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG v1.2.2)
FetchContent_MakeAvailable(matplotplusplus)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(example example.cpp)
target_link_libraries(example PUBLIC matplot)

install(TARGETS example LIBRARY DESTINATION .)
