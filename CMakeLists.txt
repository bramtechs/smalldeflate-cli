cmake_minimum_required(VERSION 3.5)
project("smalldeflate-cli")

add_executable(smallinflate "smallinflate.cc" "shared.hh")
add_executable(smalldeflate "smalldeflate.cc" "shared.hh")
