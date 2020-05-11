file( GLOB SOURCE *.cpp )

add_library(engine SHARED ${SOURCE})

target_link_libraries(engine SDL2 SDL2_image SDL2_ttf)