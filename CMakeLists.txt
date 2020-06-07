cmake_minimum_required(VERSION 3.16)
project(MyString)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

# More warnings
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# optimizing options
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(${PROJECT_NAME} main.cpp mystring.h mystring.cpp)


