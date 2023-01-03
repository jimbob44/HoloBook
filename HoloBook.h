
/*
 *  HoloBook.h
 *
 *  Copyright 2023 James Smith All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>

#endif // _WIN32

//#define PI 1 // uncomment this line to compile on the raspberry pi

#ifdef PI
#define SCAN_NO sizeofscan
#define WAIT_KEY_TIME 5000
#else
#define SCAN_NO string::npos
#define WAIT_KEY_TIME 1000
#endif // PI

#define MAX_COMMAND_LIST_SIZE 50
#define BOOK_SELECTOR_TIMER_COUNT 10


#if WIN32
  #include <windows.h>
#else
  #include <X11/Xlib.h>
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <windows.h>
#include <string>
#include <exception>
#include <stdlib.h>
#include <iostream>

#if WIN32 //using mingw version 12+ on my windows system. filesystem is now apart of std on this compiler
    #include <filesystem>
    #define DIRECTORY_ITERATOR std::filesystem::directory_iterator(s)
#else //using gcc 9.4 on linux system. filesystem is apart of experimental/filesystem
    #include <experimental/filesystem>
    #define DIRECTORY_ITERATOR experimental::filesystem::directory_iterator(s)
#endif


#include <mutex>
#include <algorithm>
#include <deque>
#include <thread>

using namespace std;
using namespace cv;

extern "C" int QRCodeScan(unsigned int maxSize, char* retBuf);

