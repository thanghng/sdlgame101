cmake_minimum_required(VERSION 3.20)

project(engine101 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

set(ENGINE_101_LIB_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
include_directories(${ENGINE_101_LIB_INCLUDE_PATH})

if(BUILD_SHARED_LIBS)
  set(ENGINE_101_BUILD_SHARED_LIB ${BUILD_SHARED_LIBS})
endif(BUILD_SHARED_LIBS)

file(GLOB_RECURSE ENGINE_101_SOURCES
    src/*.cpp)
file(GLOB_RECURSE ENGINE_101_LIBRARY_HEADERS
    include/*.h)
file(GLOB_RECURSE ENGINE_101_PRIV_SOURCES
    src/*.h)

set(ENGINE_101_ALL_SOURCES
    ${ENGINE_101_SOURCES}
    ${ENGINE_101_PLATFORM_SOURCES}
    ${ENGINE_101_LIBRARY_HEADERS}
    ${ENGINE_101_PRIV_SOURCES}
    ${ENGINE_101_PLATFORM_HEADERS})

if(ENGINE_101_BUILD_SHARED_LIB)
  add_definitions(-DENGINE_101_SHARED_LIBRARY)
endif()

if(ENGINE_101_BUILD_SHARED_LIB)
  add_library(${PROJECT_NAME} SHARED ${ENGINE_101_ALL_SOURCES})
else()
  add_library(${PROJECT_NAME} STATIC ${ENGINE_101_ALL_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} INTERFACE
                           ${ENGINE_101_LIB_INCLUDE_PATH}
                           ${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE 
                      SDL2::SDL2
                      SDL2::SDL2main
                      SDL2_image::SDL2_image)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
