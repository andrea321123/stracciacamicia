project(stracciacamicia C)
cmake_minimum_required(VERSION 3.16)

add_definitions("-Wall -Wextra -O2")

add_executable(${PROJECT_NAME}
    src/main.c
    src/permutations.c
    src/queue.c
    src/game.c
)

