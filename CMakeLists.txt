cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories(list)
include_directories(utils)
include_directories(vector)


add_executable(ft_containers
        list/list.hpp
#        list/main.cpp
        utils/iterators.hpp
        utils/utils.hpp
        utils/const_iterator.hpp
        utils/reverse_iterator.hpp
        utils/const_reverse_iterator.hpp
        vector/vector.hpp
        vector/main.cpp
        vector/VectorIterator.hpp
        vector/ReverseIterator.hpp)
