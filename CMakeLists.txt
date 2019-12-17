#TODO: stop all shared libraries from being created 
#   have makefiles automatically copy /shaders and /resources to build/bin/

cmake_minimum_required(VERSION 3.0)
project(render)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(render "")

add_subdirectory(${render_SOURCE_DIR}/src)
target_include_directories(render PUBLIC ${render_SOURCE_DIR}/include)

add_subdirectory(${render_SOURCE_DIR}/deps)

target_link_directories(render PUBLIC ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(render pthread)
target_link_libraries(render glfw)
target_link_libraries(render assimp)

if(MODE STREQUAL "wasm")

    if(NOT DEFINED ENV{EMSDK})
        message(FATAL_ERROR "emscripten environment is NOT loaded")
    endif()

    set_target_properties(render 
        PROPERTIES SUFFIX ".js"
        LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1 -s ASSERTIONS=1 --preload-file ../shaders")

elseif(MODE STREQUAL "native")
    message(STATUS "building for: ${CMAKE_SYSTEM_NAME}")

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        #nothing yet
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_link_libraries(render GL X11 dl)
    else()
        message(FATAL_ERROR "Operating System \"${CMAKE_SYSTEM_NAME}\" not supported.")
    endif()
endif()
