cmake_minimum_required(VERSION 3.15)

add_executable(app main.cpp)

target_compile_options(app PRIVATE -Wall -Wextra -Werror -pedantic-errors)
target_link_libraries(app PRIVATE cpp-argparse curl)
