# HoloBook
Projector Book E-Reader

This project is a prototype proof of concept utilising OpenCV and a C++ port of ZXing to create a QR scanner. This QR scanner is then used with a physical book to create a
projection of each page of a digital book. It is a way to build an e-reader using an existing computer, webcam and projector.

For a short video demonstration of the prototype in action click the link below.

https://youtube.com/shorts/ifT_lcoJkRU?feature=share

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
visual studio or any other compiler other than minGW so not sure if there will be issues compiling with this.

## Set up instructions

In order to use the holobook you will need the following

- Blank exercise book or art book
- Access to printer
- Software to generate QR codes (There are many available on the internet)
- A webcam
- A projector

### Setting up the Physical Book

1. Generate QR codes with the following text "Page #" for each page of the book. i.e Page 1, Page 2, Page 3 etc
2. Print these QR codes onto a sheet of paper
3. Cut out these QR codes and glue them to the top left hand corner of each page of your blank book
4. Mount a webcam so that it is constantly pointing at the top left hand corner of the book so that when you turn the page the camera will see the new QR code
5. Mount a projector so that it is pointing at the page in a way that displays the corresponding page

### Setting up the digital library

As this project is purely a proof of concept at this stage the digital library is very basic and requires some preprocessing before you can add books. In future I may improve this so that PDF or e-pub files can be directly added to the library without preprocessing.
In the same folder as the compiled executable is a folder named Books. In this folder each book has its own subfolder. The title of the subfolder should be the same as the title of the book. In this folder there should be a .jpg file for each page of the book to display. These .jpg files must be named test-#.jpg, where # corresponds to the page number. i.e test-1.jpg, test-2.jpg, test-3.jpg etc

To create these file names from a PDF I used ImageMagick on a linux machine. Refer to weblink below for instructions on how to do this.

https://jdhao.github.io/2019/11/20/convert_pdf_to_image_imagemagick/

Note the code has the first 10 pages of 2 out of copyright charles dickens novels (Oliver Twist and A Tale of Two Cities) already set up as a demonstration.
