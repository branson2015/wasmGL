
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SYSTEM WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    set(CMAKE_BUILD_TYPE Debug)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(SYSTEM MACOSX_BUNDLE)
endif()

#set(X11_LIB_SEARCH_PATH ${X11_LIB_SEARCH_PATH} /usr/lib/x86_64-linux-gnu)
#set(X11_INC_SEARCH_PATH ${X11_INC_SEARCH_PATH} /usr/include/ CACHE PATH "" FORCE)

cmake_minimum_required(VERSION 3.0)
project(render)


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

link_directories(${CMAKE_BINARY_DIR}/libs)

target_link_libraries(render pthread)
target_link_libraries(render glfw)
target_link_libraries(render assimp)
target_link_libraries(render imgui)

if(MODE STREQUAL "wasm")
    
    if(NOT DEFINED ENV{EMSDK})
        message(FATAL_ERROR "emscripten environment is NOT loaded")
    endif()
 
    #SET ( CMAKE_SHARED_LINKER_FLAGS "-O0")# --closure 1
    #SET ( CMAKE_STATIC_LINKER_FLAGS "-O0")
    #SET ( CMAKE_EXE_LINKER_FLAGS "-O0")

    set_target_properties(render 
        PROPERTIES SUFFIX ".js"
        LINK_FLAGS "-g -O0 -std=c++14 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1 -s ASSERTIONS=1 -s TOTAL_MEMORY=536870912 --preload-file ../resources"
    )

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

add_custom_command(TARGET render PRE_BUILD
    COMMAND
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${render_SOURCE_DIR}/resources $<TARGET_FILE_DIR:render>/resources/
    COMMENT "copying resources to executable"
)