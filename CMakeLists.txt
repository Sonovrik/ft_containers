cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

include_directories(list)
include_directories(utils)
include_directories(vector)
include_directories(map)
include_directories(queue)
include_directories(stack)



add_executable(ft_containers
        vector/vector.hpp
        vector/VectorIterator.hpp
        list/list.hpp
        list/ListIterator.hpp
        stack/stack.hpp
        queue/queue.hpp
        map/map.hpp
        map/MapIterator.hpp
        support_classes.hpp
        ReverseIterator.hpp
        map/map_base.hpp
#        list/main.cpp
#        vector/main.cpp
#        stack/main.cpp
#        queue/main.cpp
        map/main.cpp
        )
