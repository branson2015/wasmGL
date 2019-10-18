#TODO: make this work on windows

cmake_minimum_required(VERSION 3.0)
project(render)

add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)

set(SOURCES src/render.cpp src/glad.cpp)
set(LIBS glfw3 GL X11 pthread dl) #I don't like linking glfw3 this way - want to link against lib/GLFW/libglfw3.a


add_executable(render ${SOURCES})
target_include_directories(render PUBLIC "include")
target_link_libraries(render ${LIBS})

if(MODE STREQUAL "wasm")

    if(NOT DEFINED ENV{EMSDK})
        message(FATAL_ERROR "emscripten environment is NOT loaded")
    endif()

    set_target_properties(render 
        PROPERTIES SUFFIX ".js"
        LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1")

elseif(MODE STREQUAL "native")
    #nothing, yet.
endif()
