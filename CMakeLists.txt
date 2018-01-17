cmake_minimum_required(VERSION 2.8)

project(persistent_set)
set(SOURCES main.cpp)
set(HEADERS persistent_set.h)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -pedantic -O2 -std=c++11")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -std=c++1z -fsanitize=address,leak,undefined")
endif()
