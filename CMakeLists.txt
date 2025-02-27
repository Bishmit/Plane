cmake_minimum_required(VERSION 3.28)
project(Plane LANGUAGES CXX)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
# Fetch SFML
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Gather all source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# Add executable and sources
add_executable(main ${SRC_FILES})

# Define the asset directory
set(ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)

# Link SFML correctly
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)


