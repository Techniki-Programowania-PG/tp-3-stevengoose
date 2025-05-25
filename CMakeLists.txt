cmake_minimum_required(VERSION 3.15)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1) #generates compile_commands.json for clangd to pick up on
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Fetching newest release of matplotplusplus
include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG v1.2.2)
FetchContent_MakeAvailable(matplotplusplus)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

file(GLOB source src/*.cpp)
file(GLOB headers src/*.h)
pybind11_add_module(tp3 ${source} ${headers})
target_link_libraries(tp3 PUBLIC matplot)

install(TARGETS tp3 LIBRARY DESTINATION .)
