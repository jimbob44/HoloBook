cmake_minimum_required(VERSION 3.10)

find_package(OpenCV REQUIRED )

file(GLOB_RECURSE ZXING_SRC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/zxing/*.h)
file(GLOB_RECURSE ZXING_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/zxing/*.cpp)
file(GLOB BIGINT_SRC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/bigint/*.hh)
file(GLOB BIGINT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/bigint/*.cc)

#message("ZXing source is ${ZXING_SRC_HEADERS}" )


add_library(QROpenCVScanDll STATIC
            main.h            
            main.cpp
            ${ZXING_SRC_HEADERS}
            ${ZXING_SRC_FILES} 
            ${BIGINT_SRC_HEADERS}
            ${BIGINT_SRC_FILES}                    
            )

message("OpenCV location is ${OpenCV_INCLUDE_DIRS}" )
message("source directory is ${CMAKE_CURRENT_SOURCE_DIR}")
#message("OpenCV_libs location is ${OpenCV_LIBS}")
message("project source dir is ${PROJECT_SOURCE_DIR}")

target_include_directories(QROpenCVScanDll PUBLIC 
                      ${OpenCV_INCLUDE_DIRS}
                      ${CMAKE_CURRENT_SOURCE_DIR}/
                      )

target_link_libraries(QROpenCVScanDll ${OpenCV_LIBS})


