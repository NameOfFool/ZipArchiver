cmake_minimum_required(VERSION 3.24)


project(ZipArchiver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ZLIB_USE_STATIC_LIBS ON)
set(BUILD_SHARED_LIBS OFF)
set(ENABLE_OPENSSL OFF)  
set(ENABLE_GNUTLS OFF) 
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set(ENABLE_MBEDTLS OFF)  
set(ZLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zlib/build/install")


find_library(ZLIB_LIBRARY
    NAMES zlibstatic
    PATHS "${ZLIB_ROOT}/lib"
    REQUIRED
)


find_path(ZLIB_INCLUDE_DIR
    NAMES zlib.h
    PATHS "${ZLIB_ROOT}/include"
    REQUIRED
)
include_directories(${ZLIB_INCLUDE_DIR})
add_subdirectory(thirdparty/libzip)

add_executable("${CMAKE_PROJECT_NAME}"
    src/main.cpp
)


target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${ZLIB_ROOT}/lib/zlibstatic.lib" libzip::zip)


