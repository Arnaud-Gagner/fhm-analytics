cmake_minimum_required(VERSION 4.1)
project(fhm-analytics VERSION 0.4.0 LANGUAGES CXX)

find_package(wxWidgets CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(EXE_OPTION WIN32)
endif()

set (SOURCES
    src/AppConfig.cpp
    src/CsvUtils.cpp
    src/main.cpp
    src/Player.cpp
    src/wxAppConfig.cpp
    src/wxMainWindow.cpp
    src/wxUtils.cpp
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/include/*.h"
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

find_path(TINYTOML_INCLUDE_DIRS "toml/toml.h")
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${TINYTOML_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        wx::core
        wx::base
)

# [Optimization stuff]
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if(ipo_supported)
    set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "IPO (LTO) not supported: ${ipo_error}")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-O3 -march=native -flto>
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/O2 /GL>
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS_RELEASE "/LTCG"
    )
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/configs"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/configs"
    COMMENT "Copying configs folder"
)
