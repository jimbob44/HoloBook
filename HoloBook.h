
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

