cmake_minimum_required(VERSION 3.5)
project("smalldeflate-cli")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(smallinflate "smallinflate.cc" "shared.hh")
add_executable(smalldeflate "smalldeflate.cc" "shared.hh")

install(TARGETS smallinflate smalldeflate
    DESTINATION bin
)
