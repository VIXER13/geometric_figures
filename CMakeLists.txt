cmake_minimum_required(VERSION 3.10)

project(geometry)

SET(GEOMETRY_SOURCES "src/main.cpp")
SET(GEOMETRY_HEADERS "geometry2D")

add_executable(geometry ${GEOMETRY_SOURCES})

target_include_directories(geometry PUBLIC ${GEOMETRY_HEADERS})