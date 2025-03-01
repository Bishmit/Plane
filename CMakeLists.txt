cmake_minimum_required(VERSION 3.5)
project(Plane LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
add_executable(main ${SRC_FILES})
set(ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)