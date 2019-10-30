cmake_minimum_required(VERSION 3.14)
project(isa_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpper main.cpp Request.cpp Request.h Handler.cpp Handler.h Response.cpp Response.h Dashboard.cpp Dashboard.h Board.cpp Board.h Post.cpp Post.h)