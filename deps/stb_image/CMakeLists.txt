FILE (GLOB SOURCES *.h)

target_sources(render PUBLIC ${SOURCES})
target_include_directories(render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})