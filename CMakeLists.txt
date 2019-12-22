
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SYSTEM WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(SYSTEM MACOSX_BUNDLE)
endif()

cmake_minimum_required(VERSION 3.0)
project(render)

set(CMAKE_BUILD_TYPE Debug)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(render ${SYSTEM} "")

add_subdirectory(${render_SOURCE_DIR}/src)
target_include_directories(render PUBLIC ${render_SOURCE_DIR}/include)

add_subdirectory(${render_SOURCE_DIR}/deps)

target_link_directories(render PUBLIC ${CMAKE_BINARY_DIR}/libs)

target_link_libraries(render pthread)
target_link_libraries(render glfw)
target_link_libraries(render assimp)
target_link_libraries(render imgui)

if(MODE STREQUAL "wasm")

    if(NOT DEFINED ENV{EMSDK})
        message(FATAL_ERROR "emscripten environment is NOT loaded")
    endif()

    set_target_properties(render 
        PROPERTIES SUFFIX ".js"
        LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1 -s ASSERTIONS=1 --preload-file ../resources")

elseif(MODE STREQUAL "native")
    message(STATUS "building for: ${CMAKE_SYSTEM_NAME}")

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        #nothing yet
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_link_libraries(render GL X11 dl)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        message(FATAL_ERROR "Operating System \"${CMAKE_SYSTEM_NAME}\" not yet supported.")
    else()
        message(FATAL_ERROR "Operating System \"${CMAKE_SYSTEM_NAME}\" not supported.")
    endif()
endif()

add_custom_command(TARGET render POST_BUILD
    COMMAND
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${render_SOURCE_DIR}/resources $<TARGET_FILE_DIR:render>/resources/
    COMMENT "copying resources to executable"
)