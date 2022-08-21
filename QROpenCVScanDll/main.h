#ifndef __MAIN_H__
#define __MAIN_H__

#include <string>
#include <exception>
#include <stdlib.h>
#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include "zxing/Result.h"
#include "zxing/ReaderException.h"
#include "zxing/common/GlobalHistogramBinarizer.h"
#include "zxing/Exception.h"
#include "zxing/common/IllegalArgumentException.h"
#include "zxing/BinaryBitmap.h"
#include "zxing/DecodeHints.h"
#include "zxing/qrcode/QRCodeReader.h"
#include "zxing/MultiFormatReader.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "zxing/MatSource.h"


/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus

#endif

extern "C" int QRCodeScan(unsigned int maxSize, char* retBuf);

#ifdef __cplusplus
#endif

#endif // __MAIN_H__
