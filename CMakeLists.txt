cmake_minimum_required(VERSION 3.0)
project(render)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)

add_executable(render "")

FILE (GLOB SOURCES src/*.cpp)

target_sources(render PUBLIC ${SOURCES})
target_include_directories(render PUBLIC ${render_SOURCE_DIR}/include
    ${render_SOURCE_DIR}/deps/glm)
target_include_directories(render PUBLIC ${render_SOURCE_DIR}/deps/assimp/include)

set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)

add_subdirectory(${render_SOURCE_DIR}/src/platform)
add_subdirectory(${render_SOURCE_DIR}/deps/glad)
add_subdirectory(${render_SOURCE_DIR}/deps/glm)

link_directories(${render_SOURCE_DIR}/libs)
target_link_libraries(render pthread)

if(MODE STREQUAL "wasm")

    if(NOT DEFINED ENV{EMSDK})
        message(FATAL_ERROR "emscripten environment is NOT loaded")
    endif()

    set_target_properties(render 
        PROPERTIES SUFFIX ".js"
        LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1 -s ASSERTIONS=1 --preload-file ../shaders")

elseif(MODE STREQUAL "native")

    message(STATUS "${CMAKE_SYSTEM_NAME}")

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_link_libraries(render GL X11 dl)
    else()
        message(FATAL_ERROR "Operating System \"${CMAKE_SYSTEM_NAME}\" not supported.")
    endif()

    add_subdirectory(${render_SOURCE_DIR}/deps/glfw)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    target_link_libraries(render glfw)

endif()

file(COPY ${render_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
