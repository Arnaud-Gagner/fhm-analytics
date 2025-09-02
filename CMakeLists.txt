cmake_minimum_required(VERSION 3.15...3.31)
project(fhm-analytics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/CsvParser.cpp
    src/CsvRow.cpp
    src/Player.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
