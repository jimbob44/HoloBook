
#ifdef _WIN32
#include windows.h
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
#define BOOK_SELECTOR_TIMER_COUNT 2


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
#include <experimental/filesystem>
#include <mutex>
#include <algorithm>
#include <deque>
#include <thread>
#include <Magick++.h>

using namespace std;
using namespace cv;

extern "C" int QRCodeScan(unsigned int maxSize, char* retBuf);

