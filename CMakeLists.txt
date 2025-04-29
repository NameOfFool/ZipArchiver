cmake_minimum_required(VERSION 3.24)
project(ZipArchiver)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
add_subdirectory(thirdparty/libzip)
add_subdirectory(thirdparty/zlib)


find_package(zlib REQUIRED)
find_package(libzip REQUIRED PATHS "${CMAKE_SOURCE_DIR}/thirdparty/libzip-new")




add_executable(zip_archiver 
    src/main.cpp
)
include_directories(${LIBZIP_INCLUDE_DIRS})


target_link_libraries(zip_archiver PRIVATE zlib libzip::zip)