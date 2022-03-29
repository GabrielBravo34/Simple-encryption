cmake_minimum_required(VERSION 3.18)
set(PROJECT_NAME "simple_encryption")
project(simple_encryption)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    main.cpp
  ${RES_FILES})
  

add_executable(${PROJECT_NAME} ${SOURCE_FILES})