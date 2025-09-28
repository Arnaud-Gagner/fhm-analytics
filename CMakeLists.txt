cmake_minimum_required(VERSION 3.15...3.32)
project(fhm-analytics LANGUAGES CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if(ipo_supported)
    set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "IPO (LTO) not supported: ${ipo_error}")
endif()

# Higher optmization levels
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

# Add warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()