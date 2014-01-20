cmake_minimum_required(VERSION 2.8)
Project(Tiny2D)

set(TEST_SOURCES
    lib/main.cpp
)

set(SOURCES
    lib/Game.cpp
    lib/utils/Logger.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_Package(SDL2 REQUIRED)
find_Package(SDL2_image REQUIRED)

#file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

link_libraries(
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    #SDLmain
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIR}
)

add_executable (
    Tiny2D-Test
    WIN32
    MACOSX_BUNDLE
    ${TEST_SOURCES}
    ${SOURCES}
)

add_library (
    Tiny2D
    SHARED
    ${SOURCES}
)
