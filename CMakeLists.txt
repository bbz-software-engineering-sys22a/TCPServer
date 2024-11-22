cmake_minimum_required(VERSION 3.24)
project(Raw_Sockets)

set(CMAKE_CXX_STANDARD 17)

link_libraries(ws2_32 wsock32)

add_executable(Raw_Sockets main.cpp stdafx.cpp stdafx.h targetver.h)
