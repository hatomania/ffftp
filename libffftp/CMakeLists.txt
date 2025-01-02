cmake_minimum_required(VERSION 3.16)

project(libffftp LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Multimedia)
find_package(TBB CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED
    ../common.h

    common_libffftp.hpp
    libffftp_windows.hpp
    common.cpp
    sockets.hpp
    sockets.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE .)
target_include_directories(${PROJECT_NAME} PRIVATE ..)
target_include_directories(${PROJECT_NAME} PRIVATE ../boost-regex/include)
target_include_directories(${PROJECT_NAME} PRIVATE ../gsl/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
)
target_link_libraries(${PROJECT_NAME} PRIVATE TBB::tbb TBB::tbbmalloc)

target_compile_definitions(${PROJECT_NAME} PRIVATE LIBFFFTP)
