cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(list)
include_directories(utils)

add_executable(ft_containers
        list/list.hpp
        list/main.cpp
        utils/iterators.hpp
        utils/utils.hpp)
