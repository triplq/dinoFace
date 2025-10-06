cmake_minimum_required(VERSION 3.24)
project(gamee LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_ROOT "/opt/homebrew/opt/sfml")

include_directories(${SFML_ROOT}/include)
link_directories(${SFML_ROOT}/lib)

add_executable(gamee main.cpp Character.cpp Character.h Dino.cpp Dino.h Background.cpp Background.h Level.cpp Level.h)

target_link_libraries(gamee PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
