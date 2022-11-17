cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

set(core_SRCS tree.cc tree.hh game.cc game.hh check_5.cc check_5.hh gomoku.cc gomoku.hh)

add_library(core ${core_SRCS})
add_executable(gomoku main.cc)
target_link_libraries(gomoku core)
