cmake_minimum_required(VERSION 3.24)


project(ZipArchiver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#set(ZLIB_USE_STATIC_LIBS ON)

set(ZLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/zlib-install")
set(LIBZIP_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libzip-install")
add_library(zip SHARED IMPORTED)

if(WIN32)
set(ZLIB_LIBRARY "${ZLIB_ROOT}/lib/windows/zlibstatic.lib")
set_target_properties(zip PROPERTIES
    IMPORTED_LOCATION "${LIBZIP_ROOT}/bin/zip.dll" 
    IMPORTED_IMPLIB "${LIBZIP_ROOT}/lib/zip.lib"
)  
elseif(UNIX)
    set(ZLIB_LIBRARY "${ZLIB_ROOT}/lib/linux/libz.a")
    set_target_properties(zip PROPERTIES

    IMPORTED_IMPLIB "${LIBZIP_ROOT}/lib/libzip.a"
    IMPORTED_LOCATION "${LIBZIP_ROOT}/lib/libzip.so" 
) 
endif()


find_path(ZLIB_INCLUDE_DIR
    NAMES zlib.h
    PATHS "${ZLIB_ROOT}/include"
    REQUIRED
)

set(LIBZIP_INCLUDE_DIR "${LIBZIP_ROOT}/include" REQUIRED)
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${LIBZIP_INCLUDE_DIR})



add_executable("${CMAKE_PROJECT_NAME}"
    src/main.cpp
)
if(WIN32)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying runtime dependencies..."
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}>"
            "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>"
        COMMAND_EXPAND_LISTS
    )
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${ZLIB_LIBRARY}" zip)
