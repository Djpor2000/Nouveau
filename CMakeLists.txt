cmake_minimum_required(VERSION 3.10)

project(Game VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SDL2_DIR "E:/C++/Nouveau/lib/cmake/SDL2")
set(SDL2_NO_MWINDOWS true)
set(SDL2_USE_STATIC_LIBS OFF)

# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h

find_package(SDL2 REQUIRED)

add_executable(Game main.cpp glad.c stbimage.h)

target_include_directories(Game PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(Game ${SDL2_LIBRARIES})