cmake_minimum_required(VERSION 3.24)
project(ZipArchiver)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(zlib REQUIRED)
find_package(libzip REQUIRED)




add_executable(zip_archiver 
    src/main.cpp
)





target_link_libraries(zip_archiver PRIVATE libzip::zip)