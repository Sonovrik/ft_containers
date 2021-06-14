cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

include_directories(list)
include_directories(utils)
include_directories(vector)


add_executable(ft_containers
#        vector/vector.hpp
#        vector/main.cpp
#        vector/VectorIterator.hpp
#        vector/ReverseIterator.hpp
#        support_classes.hpp
        list_test/list.hpp
        list_test/main.cpp
        list_test/ListIterator.hpp
        ReverseIterator.hpp
        )
