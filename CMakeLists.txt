cmake_minimum_required(VERSION 2.8)

project(graphics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/include/sdl")
link_directories("${PROJECT_SOURCE_DIR}/libs/")

add_subdirectory(include)
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    SDL2
    SDL2_image
    SDL2_ttf
    engine)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

file( GLOB SDL_LIBS "${PROJECT_SOURCE_DIR}/libs/*.dll")
file( COPY ${SDL_LIBS} DESTINATION bin)

file( GLOB RESOURCES "${PROJECT_SOURCE_DIR}/resources/*.*")
file( COPY ${RESOURCES} DESTINATION bin)
