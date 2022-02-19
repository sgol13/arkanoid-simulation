cmake_minimum_required(VERSION 3.10.2)
project(arkanoid-simulation)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Wconversion -Wextra -Wshadow -Werror -g")


add_executable(simulation 
    src/main.cpp 
    src/board.cpp 
    src/game_objects.cpp 
    src/player.cpp
)

target_include_directories(simulation PRIVATE include)

target_link_libraries(simulation ncurses pthread)