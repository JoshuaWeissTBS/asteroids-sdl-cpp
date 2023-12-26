cmake_minimum_required(VERSION 3.5)
project(Asteroids VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES "members/*.cpp" "members/*.hpp" "sdl_components/*.cpp" "sdl_components/*.hpp" "glad/src/glad.c" "entities/*.cpp" "entities/*.hpp"  "engine/*.cpp" "engine/*.hpp")

add_executable(Asteroids main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Find SDL2 library
find_package(SDL2 REQUIRED)

# Include SDL2 headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# Include glad headers
target_include_directories(${PROJECT_NAME} PRIVATE "glad/include")

# # Link glad library
# target_link_libraries(${PROJECT_NAME} PRIVATE "glad/src/glad.c")

target_include_directories(${PROJECT_NAME} PRIVATE "entities")
target_include_directories(${PROJECT_NAME} PRIVATE "engine")
target_include_directories(${PROJECT_NAME} PRIVATE "members")
target_include_directories(${PROJECT_NAME} PRIVATE "sdl_components")