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
#        list/list.hpp
#        list/main.cpp
#        list/ListIterator.hpp
#        ReverseIterator.hpp
#        stack/stack.hpp
#        stack/main.cpp
#        queue/queue.hpp
#        queue/main.cpp
        map/map.hpp
        map/main.cpp
        map/MapIterator.hpp
        support_classes.hpp
        ReverseIterator.hpp
        )
