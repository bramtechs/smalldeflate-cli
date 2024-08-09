cmake_minimum_required(VERSION 3.5)
project("smalldeflate-cli" LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

if (NOT DONT_FETCH_PKGS)
  include(./cmake/ExternalPackages.cmake)
else()
  find_package(cxxopts REQUIRED)
endif()

add_executable(smallinflate "smallinflate.cc" "shared.hh")
add_executable(smalldeflate "smalldeflate.cc" "shared.hh")

target_link_libraries(smallinflate PRIVATE cxxopts::cxxopts)
target_link_libraries(smalldeflate PRIVATE cxxopts::cxxopts)

install(TARGETS smallinflate smalldeflate
    DESTINATION bin
)
