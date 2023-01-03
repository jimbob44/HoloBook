# HoloBook
Projector Book Scanner

This project is a prototype proof of concept utilising OpenCV and a C++ port of ZXing to create a QR scanner. This QR scanner is then used with a physical book to create a
projection of each page of a digital book.

For a demonstration of the project refer video here.


## Build instructions

Project has been tested on both Linux Mint 20.1 using GCC and Windows 10 using MinGW version 12

Project is built with CMake and is dependent on OpenCV. Ensure you have a working installation of OpenCV installed.

### Linux 
Open a terminal and go to directory where source is and type following commands

mkdir build 

cd build

cmake ..

cmake --build .

### Windows

Use the Cmake GUI ensure that it has found the install location of OpenCV then generate and build using preferred build system. Note I have not tried building this with
visual studio or any other compiler other an minGW so not sure if there will be issues compiling with this.
