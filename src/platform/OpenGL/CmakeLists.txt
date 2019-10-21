FILE (GLOB SOURCES src/*.cpp)

target_sources(render PUBLIC ${SOURCES})
target_include_directories(render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)