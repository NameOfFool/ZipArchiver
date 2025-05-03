cmake_minimum_required(VERSION 3.24)


project(ZipArchiver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(ZLIB_USE_STATIC_LIBS ON)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Static build" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-static")


set(ENABLE_OPENSSL OFF)  
set(BUILD_DOC OFF CACHE BOOL "Disable docs")
set(BUILD_EXAMPLES OFF CACHE BOOL "Disable examples")
set(BUILD_REGRESS OFF CACHE BOOL "Disable tests")
set(BUILD_TOOLS OFF CACHE BOOL "Disable CLI tools")
set(ENABLE_GNUTLS OFF) 

set(ZLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zlib-install")

if(WIN32)
    set(ZLIB_LIBRARY "${ZLIB_ROOT}/lib/windows/zlibstatic.lib")
elseif(UNIX)
    set(ZLIB_LIBRARY "${ZLIB_ROOT}/lib/linux/libz.a")
endif()


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

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${ZLIB_LIBRARY}" libzip::zip)