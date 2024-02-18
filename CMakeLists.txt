cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME TMH)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
main.cpp
Route.cpp
Route.h
Time.h
)
