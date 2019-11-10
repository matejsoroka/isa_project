cmake_minimum_required(VERSION 3.14)
project(isa_project)

set(CMAKE_CXX_STANDARD 17)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

# example usage
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-pedantic")

add_executable(server server.cpp Request.cpp Request.h Handler.cpp Handler.h Response.cpp Response.h Dashboard.cpp
        Dashboard.h Board.cpp Board.h Post.cpp Post.h)

add_executable(client client.cpp Request.cpp Request.h Handler.cpp Handler.h Response.cpp Response.h Dashboard.cpp
        Dashboard.h Board.cpp Board.h Post.cpp Post.h)