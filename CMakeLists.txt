cmake_minimum_required(VERSION 3.13)

project(HoloBook)

add_subdirectory(QROpenCVScanDll)

add_executable(HoloBook 
               HoloBook.h
               HoloBook.cpp)

find_package(OpenCV REQUIRED )
find_package(X11 REQUIRED)


add_library(QROpenCV SHARED IMPORTED)
set_target_properties(QROpenCV PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libQROpenCVScanDll.so)


target_include_directories(HoloBook PUBLIC ${OpenCV_INCLUDE_DIRS} ${X11_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/QROpenCVScanDll)

target_link_libraries(HoloBook QROpenCVScanDll QROpenCV ${OpenCV_LIBS} ${X11_LIBRARIES} stdc++fs)

set_target_properties(HoloBook PROPERTIES LINK_FLAGS "-lpthread")


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")



