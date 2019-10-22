#TODO: make this work on windows

cmake_minimum_required(VERSION 3.0)
project(render)

add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)

add_executable(render "")

FILE (GLOB SOURCES src/*.cpp)

target_sources(render PUBLIC ${SOURCES})
target_include_directories(render PUBLIC ${render_SOURCE_DIR}/include)

add_subdirectory(${render_SOURCE_DIR}/deps/glad)
add_subdirectory(${render_SOURCE_DIR}/deps/glm)
add_subdirectory(${render_SOURCE_DIR}/src/platform)

target_link_libraries(render GL X11 pthread dl)




if(MODE STREQUAL "wasm")

    if(NOT DEFINED ENV{EMSDK})
        message(FATAL_ERROR "emscripten environment is NOT loaded")
    endif()

    set_target_properties(render 
        PROPERTIES SUFFIX ".js"
        LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1 -s ASSERTIONS=1 --preload-file ../shaders")

elseif(MODE STREQUAL "native")

    add_subdirectory(${render_SOURCE_DIR}/deps/glfw)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    target_link_libraries(render glfw)

endif()
